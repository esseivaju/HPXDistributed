//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmA.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmA::initialize(EventContext &context) {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmA::operator()(EventContext &context) {
        return SUCCESS;
    }
    AlgorithmA::AlgorithmA() : Algorithm("AlgorithmA") {}
}// namespace hpxdistributed::algorithms