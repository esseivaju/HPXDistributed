#include "EventContext.h"
#include "Scheduler.h"

#include <chrono>
#include <iostream>
#include <ranges>

#include <hpx/hpx.hpp>
#include <hpx/iostream.hpp>
#include <hpx/wrap_main.hpp>

int main(int argc, char *argv[]) {
    auto n_localities = hpx::get_num_localities().get();
    auto n_threads = hpx::get_os_thread_count();
    auto n_events = n_threads * n_localities;
    hpx::cout << "Running with " << n_localities << " localities with " << n_threads << " threads each" << std::endl;

    using Scheduler = hpxdistributed::scheduler::Scheduler;
    Scheduler sched{};
    std::vector<hpx::shared_future<EventContext>> futures;
    futures.reserve(n_events);
    auto start{std::chrono::high_resolution_clock::now()};
    for (std::weakly_incrementable auto elem: std::views::iota(0ul, n_events)) {
        sched.schedule_event(EventContext{elem, static_cast<double>(elem), static_cast<double>(elem)});
        futures.emplace_back(sched.retrieve(elem));
    }
    auto end_scheduling{std::chrono::high_resolution_clock::now()};
    hpx::wait_all(futures);
    auto end_work{std::chrono::high_resolution_clock::now()};
    hpx::cout << "Result: " << std::endl;
    for (auto &f: futures) {
        hpx::cout << f.get() << std::endl;
    }
    hpx::cout << "Total time to schedule: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_scheduling - start).count() << "ms\n";
    hpx::cout << "Total time to process: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start).count() << "ms\n";
    hpx::cout << "Time between scheduling end and processing end: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - end_scheduling).count() << "ms\n";

    return 0;
}