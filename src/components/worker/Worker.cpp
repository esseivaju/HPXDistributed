#include "Worker.h"

#include <iostream>
#include <thread>
#include <chrono>

HPX_REGISTER_COMPONENT_MODULE()

HPX_REGISTER_ACTION(WorkerServer::schedule_event_action, worker_schedule_event_action);

namespace hpxdistributed {

namespace components::details {
    EventContext Worker::schedule_event(const EventContext &eventContext) {
        std::this_thread::sleep_for(std::chrono::milliseconds{_process_time});
        return EventContext{eventContext.id(), eventContext.eta() * 2, eventContext.phi() * 2};
    }
}

    hpx::shared_future<EventContext> WorkerClient::schedule_event(const EventContext &eventContext) {
        WorkerServer ::schedule_event_action act;
        return hpx::async(act, get_id(), eventContext);
    }
}// namespace hpxdistributed
