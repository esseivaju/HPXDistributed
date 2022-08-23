#include "Worker.h"
#include "AlgorithmsImpl.h"

#include <hpx/iostream.hpp>

#include <cassert>
#include <chrono>
#include <concepts>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <type_traits>

HPX_REGISTER_COMPONENT_MODULE()

HPX_REGISTER_ACTION(WorkerServer::process_event_action, worker_process_event_action);

namespace hpxdistributed {

    namespace components::server {

        // y_combinator to recursively call lambda without having to pass it as a parameter every time.
        template<class F>
        class fix {
            F func;

        public:
            fix(F &&f) : func(std::forward<F>(f)) {}

            template<class... Args>
                requires std::invocable<F, std::add_lvalue_reference_t<fix<F>>, Args...> decltype(auto)
            operator()(Args &&...args) {
                return func(*this, std::forward<Args>(args)...);
            }
        };

        EventContext<Worker::algo_id_t> Worker::process_event(EventContext<algo_id_t> eventContext, std::vector<std::string> values) {
            assert(values.size() > 0);
            std::unordered_map<algo_id_t, hpx::shared_future<StatusCode>> scheduled;
            auto schedule_inputs = fix{[&](auto &self, const algo_id_t &algo_id) -> hpx::shared_future<StatusCode> {
                auto deps = _deps.find(algo_id);
                assert(deps != _deps.end() && "Dependency map should have an entry for each algorithm");
                // if we have dependencies, schedule them first
                if (deps->second.size() > 0) {
                    std::vector<hpx::shared_future<StatusCode>> inputs{};
                    inputs.reserve(deps->second.size());
                    // for each dependency, we check if it has already been scheduled
                    for (auto &dep: deps->second) {
                        auto is_dep_scheduled = scheduled.find(dep);
                        if (is_dep_scheduled == scheduled.end()) {
                            // hasn't been scheduled, schedule it and register the future in case other algorithms depend on it
                            scheduled[dep] = self(dep);
                            inputs.push_back(scheduled[dep]);
                        } else {
                            //already scheduled, retrieve the future to wait on it
                            inputs.push_back(is_dep_scheduled->second);
                        }
                    }
                    // returns a future which will only schedule execution of the current algorithm when all the dependencies are ready
                    return hpx::when_all(inputs).then(hpx::unwrapping([&](const auto &container) {
                        // If any of our input failed, do not execute and propagate the failure
                        for (auto status_code_future: container) {
                            auto status_code = status_code_future.get();
                            if (status_code != StatusCode::SUCCESS) {
                                return hpx::make_ready_future(status_code);
                            }
                        }
                        // wrap the algorithm call in a lambda, hpx seems to not be supporting function objects.
                        return hpx::async([&]() { return (*_algorithms[algo_id])(eventContext); });
                    }));
                }
                // we don't have any dependencies, so we can schedule the algorithm and return a future to wait on its execution
                return hpx::async([&]() { return (*_algorithms[algo_id])(eventContext); });
            }};

            // schedule all the algorithms that are requested and wait on them
            std::vector<hpx::shared_future<StatusCode>> to_run{};
            to_run.reserve(eventContext.requested().size());
            for (const auto &algo_id: eventContext.requested()) {
                if (scheduled.find(algo_id) == scheduled.end()) {
                    scheduled[algo_id] = schedule_inputs(algo_id);
                }
                to_run.push_back(scheduled[algo_id]);
            }
            hpx::wait_all(to_run);
            return eventContext;
        }
        Worker::Worker(Worker::AlgorithmsDependencies deps) : _deps{std::move(deps)}, _algorithms{} {
            namespace algs = hpxdistributed::algorithms;
            using enum algs::Algorithm::StatusCode;
            auto insert_algo{[&](std::unique_ptr<algs::Algorithm> &&alg) {
                auto name{alg->get_name()};
                _algorithms.insert({std::move(name), std::move(alg)});
            }};
            // We're using subclasses of Algorithm even though none of them currently overload operator()
            // they eventually should do different things.
            insert_algo(std::make_unique<algs::AlgorithmA>());
            insert_algo(std::make_unique<algs::AlgorithmB>());
            insert_algo(std::make_unique<algs::AlgorithmC>());
            insert_algo(std::make_unique<algs::AlgorithmD>());
            insert_algo(std::make_unique<algs::AlgorithmE>());
            for (auto &algo: _algorithms) {
                if (algo.second->initialize() == FAILURE) {
                    std::stringstream ss;
                    ss << "Failed to initialize algorithm " << algo.first;
                    throw std::runtime_error(ss.str());
                }
            }
        }
    }// namespace components::server

    hpx::shared_future<EventContext<Worker::algo_id_t>> Worker::process_event(const EventContext<algo_id_t> &eventContext) {
        std::vector<std::string> v{"foo", "bar"};
        return hpx::async<WorkerServer::process_event_action>(get_id(), eventContext, std::move(v));
    }
}// namespace hpxdistributed
