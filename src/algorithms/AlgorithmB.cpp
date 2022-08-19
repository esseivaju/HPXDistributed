//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmB.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmB::initialize() {
        return SUCCESS;
    }
    AlgorithmB::AlgorithmB() : Algorithm(400, 5, "AlgorithmB") {}

}// namespace hpxdistributed::algorithms