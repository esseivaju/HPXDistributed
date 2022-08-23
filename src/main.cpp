#include "Algorithm.h"
#include "AlgorithmsImpl.h"
#include "EventContext.h"
#include "Scheduler.h"

#include <chrono>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <unordered_map>

#include <hpx/hpx.hpp>
#include <hpx/iostream.hpp>
#include <hpx/wrap_main.hpp>

namespace algs = hpxdistributed::algorithms;
using Inputs = std::vector<std::string>;


void print_dependencies(const std::unordered_map<std::string, Inputs> &dependencies) {
    for (auto &k: dependencies) {
        hpx::cout << "Dependency: " << k.first << " -> ";
        if (!k.second.empty()) {
            for (auto &i: k.second) {
                hpx::cout << i << " ";
            }
            hpx::cout << std::endl;
        } else {
            hpx::cout << "none" << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        hpx::cout << "Usage: " << argv[0] << " <# events>" << std::endl;
        return 1;
    }
    // Build a static, arbitrary dependencies graph.
    // Get each algorithm name
    auto algo_a_name{algs::AlgorithmA{}.get_name()};
    auto algo_b_name{algs::AlgorithmB{}.get_name()};
    auto algo_c_name{algs::AlgorithmC{}.get_name()};
    auto algo_d_name{algs::AlgorithmD{}.get_name()};
    auto algo_e_name{algs::AlgorithmE{}.get_name()};
    //build dependencies graph
    std::unordered_map<std::string, Inputs> dependencies{
            {algo_a_name, {}},
            {algo_b_name, {algo_a_name}},
            {algo_c_name, {algo_a_name}},
            {algo_d_name, {algo_b_name, algo_c_name}},
            {algo_e_name, {algo_b_name}}};
    print_dependencies(dependencies);

    auto n_events = std::stoul(argv[1]);
    auto n_localities = hpx::get_num_localities().get();
    auto n_threads = hpx::get_os_thread_count();
    hpx::cout << "Running with " << n_localities << " localities with " << n_threads << " threads each (" << n_localities * n_threads << " cores)" << std::endl;
    hpx::cout << "Processing " << n_events << " events" << std::endl;

    using Scheduler = hpxdistributed::scheduler::Scheduler;
    Scheduler sched{std::move(dependencies)};
    std::vector<hpx::shared_future<EventContext<Scheduler::algo_id_t>>> futures;
    futures.reserve(n_events);
    auto start{std::chrono::high_resolution_clock::now()};
    for (std::weakly_incrementable auto elem: std::views::iota(0ul, n_events)) {
        futures.emplace_back(sched.schedule_event(EventContext{elem, static_cast<double>(elem), static_cast<double>(elem), std::vector<Scheduler::algo_id_t>{"AlgorithmD", "AlgorithmE"}}));
    }
    auto end_scheduling{std::chrono::high_resolution_clock::now()};
    hpx::wait_all(futures);
    auto end_work{std::chrono::high_resolution_clock::now()};
    //        hpx::cout << "Result: " << std::endl;
    //        for (auto &f: futures) {
    //            hpx::cout << f.get() << std::endl;
    //        }
    hpx::cout << "Total time to schedule: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_scheduling - start).count() << "ms" << std::endl;
    hpx::cout << "Total time to process: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start).count() << "ms" << std::endl;
    hpx::cout << "Time between scheduling end and processing end: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - end_scheduling).count() << "ms" << std::endl;
    hpx::cout << "Average time per event: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end_work - start).count() / static_cast<double>(n_events) << "ms" << std::endl;

    return 0;
}