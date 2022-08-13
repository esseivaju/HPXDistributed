//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmB.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmB::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmB::operator()(EventContext &context) {
        return SUCCESS;
    }
    AlgorithmB::AlgorithmB() : Algorithm("AlgorithmB") {}

}// namespace hpxdistributed::algorithms