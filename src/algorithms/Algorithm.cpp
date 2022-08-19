#include <chrono>
#include <random>

#include "Algorithm.h"
namespace hpxdistributed::algorithms {
    Algorithm::Algorithm(decltype(_name) name) : Algorithm(100., 5., std::move(name)) {
    }
    Algorithm::Algorithm(decltype(_meanCpuTime) meanCpuTime, decltype(_rmsCpuTime) rmsCpuTime, decltype(_name) name) : _meanCpuTime{meanCpuTime}, _rmsCpuTime{rmsCpuTime}, _random{static_cast<uint32_t>(_meanCpuTime)}, _distribution{std::normal_distribution<double>{_meanCpuTime, _rmsCpuTime}}, _name(std::move(name)) {
    }
    double Algorithm::burn(unsigned long nIterations) const {
        volatile double sum = 0.0;

        double val;

        for (auto idx = 0lu; idx < nIterations; ++idx) {
            val = (double) (idx + 1) / nIterations * 0.7854;
            sum += std::tan(std::log(val));
        }

        return sum;
    }

    Algorithm::StatusCode Algorithm::operator()(EventContext<id_t> &ec) {
        volatile double test_result = 0.0;

        double ms_interval = _distribution(_random);

        std::chrono::duration<float, std::milli> chrono_interval(ms_interval);

        auto start = std::chrono::system_clock::now();

        while (std::chrono::system_clock::now() - start < chrono_interval)
            test_result += burn(5000);
        return StatusCode::SUCCESS;
    }
}// namespace hpxdistributed::algorithms
