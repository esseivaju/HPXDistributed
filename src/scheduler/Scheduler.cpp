#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/runtime_distributed.hpp>

#include <utility>

namespace hpxdistributed::scheduler {

    hpx::shared_future<EventContext<Scheduler::algo_id_t>> Scheduler::schedule_event(const EventContext<Scheduler::algo_id_t> &ec) {
        //TODO: get algorithms to run dynamically
#ifdef SINGLE_WORKER
        auto result = _worker.process_event(ec);
#else
        auto result = _workers[_next_worker++ % _workers.size()].process_event(ec);
#endif
        _futures.insert({ec.id(), std::move(result)});
        return _futures[ec.id()];
    }
    Scheduler::Scheduler(AlgorithmsDependencies algorithms_dependencies)
        : _algorithms_dependencies(std::move(algorithms_dependencies)),
#ifdef SINGLE_WORKER
        _worker{hpx::new_<Worker>(hpx::find_here(), _algorithms_dependencies)}
#else
        _workers{hpx::new_<Worker[]>(hpx::binpacked(hpx::find_all_localities()), hpx::get_num_localities().get(), _algorithms_dependencies).get()}
#endif
        {}
}// namespace hpxdistributed::scheduler
