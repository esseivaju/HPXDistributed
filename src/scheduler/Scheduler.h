#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "Algorithm.h"
#include "Worker.h"

#include <hpx/runtime_distributed.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace hpxdistributed::scheduler {

    class Scheduler {
    private:
        using Worker = hpxdistributed::Worker;
        using AlgorithmsDependencies = Worker::AlgorithmsDependencies;
        AlgorithmsDependencies _algorithms_dependencies;
        std::vector<Worker> _workers;
        std::unordered_map<EventContext::IDType, hpx::shared_future<EventContext>> _futures;
        decltype(_workers)::size_type _next_worker{0};

    public:
        explicit Scheduler(AlgorithmsDependencies algorithms_dependencies);
        hpx::shared_future<EventContext> schedule_event(const EventContext &event_context);
    };
}// namespace hpxdistributed::scheduler


#endif//HPXDISTRIBUTED_SCHEDULER_H
