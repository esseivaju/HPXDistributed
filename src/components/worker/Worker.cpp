#include "Worker.h"


using Worker = hpxdistributed::components::details::Worker;
HPX_REGISTER_COMPONENT(hpx::components::component<Worker>, Worker);

HPX_REGISTER_ACTION(Worker::identity_action, worker_identity_action);

int Worker::identity() const {
    return data;
}

namespace hpxdistributed {
hpx::future<int> WorkerClient::identity() {
    Worker::identity_action act;
    return hpx::async(act, get_id());
}
}
