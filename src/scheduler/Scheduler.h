#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "Worker.h"
#include <hpx/iostream.hpp>

#include <vector>
#include <unordered_map>

namespace hpxdistributed::scheduler {

class Scheduler {
private:
    using WorkerClient = hpxdistributed::WorkerClient;
    std::vector<WorkerClient> workers;
    decltype(workers)::size_type next_worker {0};
    std::unordered_map<EventContext::IDType , hpx::shared_future<EventContext>> futures;
public:
    Scheduler();
    void schedule_event(const EventContext& event_context);
    hpx::shared_future<EventContext> & retrieve(const EventContext::IDType &id);
};
}


#endif //HPXDISTRIBUTED_SCHEDULER_H
