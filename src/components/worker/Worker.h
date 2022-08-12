#ifndef HPXDISTRIBUTED_WORKER_H
#define HPXDISTRIBUTED_WORKER_H

#include "EventContext.h"
#include <hpx/include/components.hpp>
#include <hpx/future.hpp>
#include <chrono>

namespace hpxdistributed {
    namespace components::details {
        class Worker : public hpx::components::component_base<Worker> {

        public:
            explicit Worker(std::chrono::milliseconds::rep time) : _process_time{time} {}

            EventContext schedule_event(EventContext const& eventContext);

            HPX_DEFINE_COMPONENT_ACTION(Worker, schedule_event, schedule_event_action);
        private:
            std::chrono::milliseconds::rep _process_time;

        };
    }

class WorkerClient : public hpx::components::client_base<WorkerClient, components::details::Worker> {
    public:
        using base_type = hpx::components::client_base<WorkerClient, components::details::Worker>;

        explicit WorkerClient(hpx::future<hpx::id_type> &&id)
                : base_type(std::move(id)) {}

        explicit WorkerClient(hpx::id_type &&f)
                : base_type(std::move(f)) {}

        hpx::shared_future<EventContext> schedule_event(EventContext const& eventContext);
    };
}

HPX_REGISTER_ACTION_DECLARATION(hpxdistributed::components::details::Worker::schedule_event_action,
                                worker_schedule_event_action);

using WorkerServer = hpxdistributed::components::details::Worker;
HPX_REGISTER_COMPONENT(hpx::components::component<WorkerServer>, WorkerComponent);

#endif //HPXDISTRIBUTED_WORKER_H
