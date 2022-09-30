#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "EventContext.h"
#include "Worker.h"

#include <hpx/runtime_distributed.hpp>

#include <optional>
#include <unordered_map>
#include <vector>
#include <queue>

namespace hpxdistributed::scheduler {

    class Scheduler {
    public:
        using algo_id_t = hpxdistributed::Worker::algo_id_t;

    private:
        using Worker = hpxdistributed::Worker;
        using AlgorithmsDependencies = Worker::AlgorithmsDependencies;
        AlgorithmsDependencies _algorithms_dependencies;
        std::vector<Worker> _workers;
        std::size_t _max_inflight_events {0};
        bool _throttle {false};
        std::queue<hpx::shared_future<EventContext<algo_id_t>>> _inflight_events;
        decltype(_workers)::size_type _next_worker{0};

    public:
        explicit Scheduler(AlgorithmsDependencies algorithms_dependencies, bool throttle);
        hpx::shared_future<EventContext<algo_id_t>> schedule_event(const EventContext<algo_id_t> &event_context);
    };
}// namespace hpxdistributed::scheduler


#endif//HPXDISTRIBUTED_SCHEDULER_H
