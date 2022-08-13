//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHMD_H
#define HPXDISTRIBUTED_ALGORITHMD_H

#include "Algorithm.h"

namespace hpxdistributed::algorithms {

    class AlgorithmD : public Algorithm {
    public:
        AlgorithmD();
        StatusCode initialize() override;
        StatusCode operator()(EventContext &context) override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHMD_H
