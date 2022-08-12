#include "Worker.h"
#include "AlgorithmsImpl.h"

#include <chrono>
#include <iostream>
#include <thread>

HPX_REGISTER_COMPONENT_MODULE()

HPX_REGISTER_ACTION(WorkerServer::schedule_event_action, worker_schedule_event_action);

namespace hpxdistributed {

    namespace components::details {
        EventContext Worker::schedule_event(EventContext eventContext) {
            std::this_thread::sleep_for(std::chrono::milliseconds{_process_time});
            eventContext.eta() *= 2;
            eventContext.phi() *= 2;
            return eventContext;
        }
        Worker::Worker(std::chrono::milliseconds::rep time, Worker::AlgorithmsDependencies deps)  : _process_time{time}, _deps{std::move(deps)}, _algorithms{} {
            namespace algs = hpxdistributed::algorithms;
            auto insert_algo{[&] (std::unique_ptr<algs::Algorithm> alg) {
                auto name {alg->get_name()};
                _algorithms.insert({std::move(name), std::move(alg)});
            }};
            insert_algo(std::make_unique<algs::AlgorithmA>());
            insert_algo(std::make_unique<algs::AlgorithmB>());
            insert_algo(std::make_unique<algs::AlgorithmC>());
            insert_algo(std::make_unique<algs::AlgorithmD>());
            insert_algo(std::make_unique<algs::AlgorithmE>());
        }
    }// namespace components::details

    hpx::shared_future<EventContext> WorkerClient::schedule_event(const EventContext &eventContext) {
        WorkerServer ::schedule_event_action act;
        return hpx::async(act, get_id(), eventContext);
    }
}// namespace hpxdistributed
