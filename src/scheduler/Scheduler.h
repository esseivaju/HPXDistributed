#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "Algorithm.h"
#include "Worker.h"
#include <hpx/iostream.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace hpxdistributed::scheduler {

    class Scheduler {
    private:
        using WorkerClient = hpxdistributed::WorkerClient;
        std::vector<WorkerClient> _workers;
        decltype(_workers)::size_type _next_worker{0};
        std::unordered_map<EventContext::IDType, hpx::shared_future<EventContext>> _futures;
        std::unordered_map<std::string, std::optional<std::vector<std::string>>> _algorithms_dependencies;

    public:
        explicit Scheduler(decltype(_algorithms_dependencies) &algorithms_dependencies);
        explicit Scheduler(decltype(_algorithms_dependencies) &&algorithms_dependencies);
        void schedule_event(const EventContext &event_context);
        hpx::shared_future<EventContext> &retrieve(const EventContext::IDType &id);
    };
}// namespace hpxdistributed::scheduler


#endif//HPXDISTRIBUTED_SCHEDULER_H
