#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/runtime_distributed.hpp>

#include <algorithm>
#include <utility>

namespace hpxdistributed::scheduler {

    hpx::shared_future<EventContext<Scheduler::algo_id_t>> Scheduler::schedule_event(const EventContext<Scheduler::algo_id_t> &ec) {
        //TODO: get algorithms to run dynamically
        auto result = _workers[_next_worker++ % _workers.size()].process_event(ec);
        _futures.insert({ec.id(), std::move(result)});
        return _futures[ec.id()];
    }
    Scheduler::Scheduler(AlgorithmsDependencies algorithms_dependencies)
        : _algorithms_dependencies(std::move(algorithms_dependencies)),
          _workers{hpx::new_<Worker[]>(hpx::binpacked(hpx::find_remote_localities()), std::max(hpx::get_num_localities().get() - 1, 1u), _algorithms_dependencies).get()} {}
}// namespace hpxdistributed::scheduler
