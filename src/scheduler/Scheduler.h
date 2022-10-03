#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "EventContext.h"
#include "Worker.h"

#include <hpx/runtime_distributed.hpp>
#include <hpx/semaphore.hpp>

#include <vector>

namespace hpxdistributed::scheduler {

    constexpr std::ptrdiff_t MAX_IN_FLIGHT = 40 * 128 * 2;
    class Scheduler {
    public:
        using algo_id_t = hpxdistributed::Worker::algo_id_t;

    private:
        using Worker = hpxdistributed::Worker;
        using AlgorithmsDependencies = Worker::AlgorithmsDependencies;
        AlgorithmsDependencies _algorithms_dependencies;
        std::vector<Worker> _workers;
        hpx::counting_semaphore<MAX_IN_FLIGHT> _inflight;
        bool _throttle {false};
        decltype(_workers)::size_type _next_worker{0};

    public:
        explicit Scheduler(AlgorithmsDependencies algorithms_dependencies, bool throttle);
        hpx::shared_future<EventContext<algo_id_t>> schedule_event(const EventContext<algo_id_t> &event_context);
    };
}// namespace hpxdistributed::scheduler


#endif//HPXDISTRIBUTED_SCHEDULER_H
