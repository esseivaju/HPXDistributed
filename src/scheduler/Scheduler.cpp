#include "Scheduler.h"
#include <hpx/include/components.hpp>

namespace hpxdistributed::scheduler {
    Scheduler::Scheduler() : client{hpx::new_<WorkerClient>(hpx::find_here(), 12)} {}

    int Scheduler::fetch_id_result() {
        return client.identity().get();
    }
}
