#include <algorithm>
#include <chrono>
#include <random>

#include "Algorithm.h"
namespace hpxdistributed::algorithms {
    Algorithm::Algorithm(decltype(_name) name) : Algorithm(1, 1000000, std::move(name)) {
    }
    Algorithm::Algorithm(decltype(_a) a, decltype(_b) b, decltype(_name) name) : _a{a}, _b{b}, _name(std::move(name)) {
    }

    Algorithm::StatusCode Algorithm::operator()(EventContext<id_t> &ec) {
        std::mt19937 _random{static_cast<std::size_t>(_a+_b)};
        std::uniform_int_distribution<int> _distribution{_a, _b};
        std::vector<int> work{};
        work.reserve(_b);
        for(auto i = 0 ; i < _b ; ++i)
            work.push_back(_distribution(_random));
        std::sort(work.begin(), work.end());
        return StatusCode::SUCCESS;
    }
}// namespace hpxdistributed::algorithms
