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
        int _a{1};
        int _b{1000000};
        std::string _name;

    public:
        virtual ~Algorithm() = default;
        explicit Algorithm(decltype(_name));
        Algorithm(decltype(_a), decltype(_b), decltype(_name));
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
