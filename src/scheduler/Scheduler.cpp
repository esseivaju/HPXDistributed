#include "Scheduler.h"

#include <hpx/include/components.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/runtime_distributed.hpp>
#include <hpx/iostream.hpp>

#include <algorithm>
#include <utility>

namespace hpxdistributed::scheduler {

    hpx::shared_future<EventContext<Scheduler::algo_id_t>> Scheduler::schedule_event(const EventContext<Scheduler::algo_id_t> &ec) {
        if(_throttle && _inflight_events.size() == _max_inflight_events){
            _inflight_events.front().wait();
            _inflight_events.pop();
            while(_inflight_events.front().is_ready())
                _inflight_events.pop();
        }
        auto result = _workers[_next_worker++].process_event(ec);
        _next_worker %= _workers.size();
        if(_throttle) {
            _inflight_events.push(result);
        }
        _futures.insert({ec.id(), std::move(result)});
        return _futures[ec.id()];
    }
    Scheduler::Scheduler(AlgorithmsDependencies algorithms_dependencies, bool throttle)
        : _algorithms_dependencies(std::move(algorithms_dependencies)),
          _workers{hpx::new_<Worker[]>(hpx::binpacked(hpx::find_remote_localities()), std::max(hpx::get_num_localities().get() - 1, 1u), _algorithms_dependencies).get()},
          _throttle{throttle} {
            _max_inflight_events = _workers.size() * 10 * hpx::get_os_thread_count();

            for(auto &worker : _workers)
                hpx::cout << "Worker instantiated on " << worker.loc_name().get() << std::endl;
          }
}// namespace hpxdistributed::scheduler
