#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/runtime_distributed.hpp>
#include <hpx/modules/distribution_policies.hpp>

#include <utility>

namespace hpxdistributed::scheduler {
    Scheduler::Scheduler() : workers{hpx::new_<WorkerClient[]>(hpx::binpacked(hpx::find_all_localities()), hpx::get_num_localities().get(), 100).get()} {
    }

    void Scheduler::schedule_event(const EventContext& ec) {
        auto result = workers[next_worker++ % workers.size()].schedule_event(ec);
        futures.insert({ec.id(), std::move(result)});
    }
    hpx::shared_future<EventContext> &Scheduler::retrieve(const EventContext::IDType &id) {
        return futures.at(id);
    }
}
