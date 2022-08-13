//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmE.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmE::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmE::operator()(EventContext &context) {
        return SUCCESS;
    }
    AlgorithmE::AlgorithmE() : Algorithm("AlgorithmE") {}
}// namespace hpxdistributed::algorithms