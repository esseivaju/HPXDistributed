#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/runtime_distributed.hpp>

#include <utility>

namespace hpxdistributed::scheduler {

    void Scheduler::schedule_event(const EventContext &ec) {
        //TODO: get algorithms to run dynamically
        auto result = _workers[_next_worker++ % _workers.size()].schedule_event(ec, {"AlgorithmD", "AlgorithmE"});
        _futures.insert({ec.id(), std::move(result)});
    }
    hpx::shared_future<EventContext> &Scheduler::retrieve(const EventContext::IDType &id) {
        return _futures.at(id);
    }
    Scheduler::Scheduler(AlgorithmsDependencies algorithms_dependencies)
        : _algorithms_dependencies(std::move(algorithms_dependencies)),
          _workers{hpx::new_<WorkerClient[]>(hpx::binpacked(hpx::find_all_localities()), hpx::get_num_localities().get(), _algorithms_dependencies).get()} {}
}// namespace hpxdistributed::scheduler
