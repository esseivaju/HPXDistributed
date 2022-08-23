//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHM_H
#define HPXDISTRIBUTED_ALGORITHM_H

#include "EventContext.h"
#include <cmath>
#include <random>
#include <string>
#include <typeindex>
#include <utility>

namespace hpxdistributed::algorithms {
    class Algorithm {
    protected:
        double _meanCpuTime{100.};
        double _rmsCpuTime{5.};
        std::default_random_engine _random;
        std::normal_distribution<double> _distribution;
        std::string _name;
        [[nodiscard]] double burn(unsigned long) const;

    public:
        virtual ~Algorithm() = default;
        explicit Algorithm(decltype(_name));
        Algorithm(decltype(_meanCpuTime), decltype(_rmsCpuTime), decltype(_name));
        using id_t = std::string;
        using status_code = uint8_t;
        enum class StatusCode : status_code {
            SUCCESS = 0,
            FAILURE = 1,
            UNKNOWN = 2
        };
        [[nodiscard]] virtual StatusCode initialize() = 0;
        [[nodiscard]] virtual StatusCode operator()(EventContext<id_t> &);
        [[nodiscard]] const decltype(_name) &get_name() const { return _name; }
    };
}// namespace hpxdistributed::algorithms


#endif//HPXDISTRIBUTED_ALGORITHM_H
