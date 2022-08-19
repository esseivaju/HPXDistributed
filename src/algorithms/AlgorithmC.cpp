//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmC.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmC::initialize() {
        return SUCCESS;
    }
    AlgorithmC::AlgorithmC() : Algorithm(600, 5, "AlgorithmC") {}
}// namespace hpxdistributed::algorithms