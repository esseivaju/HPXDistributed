//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmE.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmE::initialize() {
        return SUCCESS;
    }
    AlgorithmE::AlgorithmE() : Algorithm(1000000, "AlgorithmE") {}
}// namespace hpxdistributed::algorithms