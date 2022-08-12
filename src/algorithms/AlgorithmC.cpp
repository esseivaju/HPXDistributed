//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmC.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmC::initialize(EventContext &context) {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmC::operator()(EventContext &context) {
        return SUCCESS;
    }
    AlgorithmC::AlgorithmC() : Algorithm("AlgorithmC") {}
}// namespace hpxdistributed::algorithms