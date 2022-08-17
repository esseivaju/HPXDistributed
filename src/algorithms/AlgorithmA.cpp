//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmA.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmA::initialize() {
        return SUCCESS;
    }
    AlgorithmA::AlgorithmA() : Algorithm(20, 5, "AlgorithmA") {}
}// namespace hpxdistributed::algorithms