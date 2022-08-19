//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmD.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmD::initialize() {
        return SUCCESS;
    }
    AlgorithmD::AlgorithmD() : Algorithm(800, 5, "AlgorithmD") {}
}// namespace hpxdistributed::algorithms