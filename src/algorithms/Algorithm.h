//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHM_H
#define HPXDISTRIBUTED_ALGORITHM_H

#include "EventContext.h"
#include <string>

namespace hpxdistributed::algorithms {
    class Algorithm {

        std::string _name;

    public:
        virtual ~Algorithm() = default;
        explicit Algorithm(decltype(_name) name) : _name(std::move(name)) {}
        using id_t = decltype(_name);
        using status_code = uint8_t;
        enum class StatusCode : status_code {
            SUCCESS = 0,
            FAILURE = 1,
            UNKNOWN = 2
        };
        virtual StatusCode initialize() = 0;
        virtual StatusCode operator()(EventContext &) = 0;
        [[nodiscard]] const decltype(_name) &get_name() const { return _name; }
    };
}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHM_H
