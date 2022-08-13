#ifndef HPXDISTRIBUTED_WORKER_H
#define HPXDISTRIBUTED_WORKER_H

#include "Algorithm.h"
#include "EventContext.h"
#include <chrono>
#include <hpx/future.hpp>
#include <hpx/include/components.hpp>
#include <iostream>
#include <memory>
#include <utility>

namespace hpxdistributed {
    namespace components::details {
        class Worker : public hpx::components::component_base<Worker> {
        public:
            using algo_id_t = hpxdistributed::algorithms::Algorithm::id_t;

        private:
            std::chrono::milliseconds::rep _process_time;
            std::unordered_map<algo_id_t, std::vector<algo_id_t>> _deps;
            // map of algorithm instances by name
            std::unordered_map<algo_id_t, std::unique_ptr<hpxdistributed::algorithms::Algorithm>> _algorithms;

        public:
            using AlgorithmsDependencies = decltype(_deps);
            Worker(std::chrono::milliseconds::rep time, AlgorithmsDependencies deps);

            EventContext schedule_event(EventContext eventContext, const std::vector<algo_id_t> &requested);

            HPX_DEFINE_COMPONENT_ACTION(Worker, schedule_event, schedule_event_action);
        };
    }// namespace components::details

    class WorkerClient : public hpx::components::client_base<WorkerClient, components::details::Worker> {
    public:
        using base_type = hpx::components::client_base<WorkerClient, components::details::Worker>;

        // Re-expose type for users of this class
        using AlgorithmsDependencies = components::details::Worker::AlgorithmsDependencies;
        using algo_id_t = components::details::Worker::algo_id_t;
        explicit WorkerClient(hpx::future<hpx::id_type> &&id)
            : base_type(std::move(id)) {}

        explicit WorkerClient(hpx::id_type &&f)
            : base_type(std::move(f)) {}

        hpx::shared_future<EventContext> schedule_event(const EventContext &eventContext, const std::vector<algo_id_t> &requested);
    };
}// namespace hpxdistributed

HPX_REGISTER_ACTION_DECLARATION(hpxdistributed::components::details::Worker::schedule_event_action,
                                worker_schedule_event_action);

using WorkerServer = hpxdistributed::components::details::Worker;
HPX_REGISTER_COMPONENT(hpx::components::component<WorkerServer>, WorkerComponent);

#endif//HPXDISTRIBUTED_WORKER_H
