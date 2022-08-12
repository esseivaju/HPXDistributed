#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/runtime_distributed.hpp>

#include <utility>

namespace hpxdistributed::scheduler {

    void Scheduler::schedule_event(const EventContext &ec) {
        auto result = _workers[_next_worker++ % _workers.size()].schedule_event(ec);
        _futures.insert({ec.id(), std::move(result)});
    }
    hpx::shared_future<EventContext> &Scheduler::retrieve(const EventContext::IDType &id) {
        return _futures.at(id);
    }
    Scheduler::Scheduler(decltype(_algorithms_dependencies) &algorithms_dependencies)
        : _workers{hpx::new_<WorkerClient[]>(hpx::binpacked(hpx::find_all_localities()), hpx::get_num_localities().get(), 200).get()},
          _algorithms_dependencies(algorithms_dependencies) { std::cout << "Scheduler created by copy" << std::endl; }
    Scheduler::Scheduler(decltype(_algorithms_dependencies) &&algorithms_dependencies)
        : _workers{hpx::new_<WorkerClient[]>(hpx::binpacked(hpx::find_all_localities()), hpx::get_num_localities().get(), 200).get()},
          _algorithms_dependencies(std::move(algorithms_dependencies)) {
        std::cout << "Scheduler created by move" << std::endl;
    }
}// namespace hpxdistributed::scheduler
