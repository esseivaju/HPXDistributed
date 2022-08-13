//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmD.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmD::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmD::operator()(EventContext &context) {
        return SUCCESS;
    }
    AlgorithmD::AlgorithmD() : Algorithm("AlgorithmD") {}
}// namespace hpxdistributed::algorithms