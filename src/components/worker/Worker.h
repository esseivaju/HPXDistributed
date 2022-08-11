#ifndef HPXDISTRIBUTED_WORKER_H
#define HPXDISTRIBUTED_WORKER_H

#include <hpx/include/components.hpp>

namespace hpxdistributed {
    namespace components::details {
        class Worker : public hpx::components::component_base<Worker> {

        public:
            explicit Worker(int data) : data{data} {}

            int identity() const;

            HPX_DEFINE_COMPONENT_ACTION(Worker, identity, identity_action);
        private:
            int data;

        };
    }

class WorkerClient : public hpx::components::client_base<WorkerClient, components::details::Worker> {
    public:
        using base_type = hpx::components::client_base<WorkerClient, components::details::Worker>;

        explicit WorkerClient(hpx::future<hpx::id_type> &&id)
                : base_type(std::move(id)) {}

        explicit WorkerClient(hpx::id_type &&f)
                : base_type(std::move(f)) {}

        hpx::future<int> identity();
    };
}

HPX_REGISTER_ACTION_DECLARATION(hpxdistributed::components::details::Worker::identity_action,
                                worker_identity_action);

#endif //HPXDISTRIBUTED_WORKER_H
