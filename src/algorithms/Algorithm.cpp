#include <chrono>
#include <random>

#include "Algorithm.h"
namespace hpxdistributed::algorithms {
    Algorithm::Algorithm(decltype(_name) name) : Algorithm(1000000, std::move(name)) {
    }
    Algorithm::Algorithm(decltype(_nIter) nIter, decltype(_name) name) :  _nIter{nIter}, _name(std::move(name)) {
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
        test_result = burn(_nIter);
        return StatusCode::SUCCESS;
    }
}// namespace hpxdistributed::algorithms
