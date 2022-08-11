#ifndef HPXDISTRIBUTED_SCHEDULER_H
#define HPXDISTRIBUTED_SCHEDULER_H

#include "Worker.h"

namespace hpxdistributed::scheduler {

class Scheduler {
private:
    using WorkerClient = hpxdistributed::WorkerClient;
    WorkerClient client;

public:
    Scheduler();
    int fetch_id_result();
};
}


#endif //HPXDISTRIBUTED_SCHEDULER_H
