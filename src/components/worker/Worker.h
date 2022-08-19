#ifndef HPXDISTRIBUTED_WORKER_H
#define HPXDISTRIBUTED_WORKER_H

#include "Algorithm.h"
#include "EventContext.h"
#include <chrono>
#include <hpx/future.hpp>
#include <hpx/config.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>
#include <iostream>
#include <memory>
#include <utility>

namespace hpxdistributed {
    namespace components::server {
        class Worker : public hpx::components::component_base<Worker> {
        public:
            using algo_id_t = hpxdistributed::algorithms::Algorithm::id_t;

        private:
            std::unordered_map<algo_id_t, std::vector<algo_id_t>> _deps;
            // map of algorithm instances by name
            std::unordered_map<algo_id_t, std::unique_ptr<hpxdistributed::algorithms::Algorithm>> _algorithms;

        public:
            using AlgorithmsDependencies = decltype(_deps);
            explicit Worker(AlgorithmsDependencies deps);

            EventContext schedule_event(EventContext eventContext, const std::vector<algo_id_t> &requested);

            HPX_DEFINE_COMPONENT_ACTION(Worker, schedule_event);
        };
    }// namespace components::server

    class Worker : public hpx::components::client_base<Worker, components::server::Worker> {
    public:
        using base_type = hpx::components::client_base<Worker, components::server::Worker>;

        // Re-expose type for users of this class
        using AlgorithmsDependencies = components::server::Worker::AlgorithmsDependencies;
        using algo_id_t = components::server::Worker::algo_id_t;
        explicit Worker(hpx::future<hpx::id_type> &&id)
            : base_type(std::move(id)) {}

        explicit Worker(hpx::id_type &&f)
            : base_type(std::move(f)) {}

        hpx::shared_future<EventContext> schedule_event(const EventContext &eventContext, const std::vector<algo_id_t> &requested);
    };
}// namespace hpxdistributed

HPX_REGISTER_ACTION_DECLARATION(hpxdistributed::components::server::Worker::schedule_event_action,
                                worker_schedule_event_action);

using WorkerServer = hpxdistributed::components::server::Worker;
HPX_REGISTER_COMPONENT(hpx::components::component<WorkerServer>, WorkerComponent);

#endif//HPXDISTRIBUTED_WORKER_H
