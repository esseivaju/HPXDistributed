#include "Scheduler.h"

#include <iostream>

#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

int main(int argc, char *argv[])
{
    using Scheduler = hpxdistributed::scheduler::Scheduler;
    Scheduler sched{};
    hpx::cout << "Hello " << sched.fetch_id_result() << std::endl;


}