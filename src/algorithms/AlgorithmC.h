//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHMC_H
#define HPXDISTRIBUTED_ALGORITHMC_H

#include "Algorithm.h"
namespace hpxdistributed::algorithms {

    class AlgorithmC : public Algorithm {
    public:
        AlgorithmC();
        StatusCode initialize(EventContext &context) override;
        StatusCode operator()(EventContext &context) override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHMC_H
