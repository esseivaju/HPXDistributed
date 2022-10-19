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
        StatusCode initialize() override;
        StatusCode operator()(EventContext<id_t> &) override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHMC_H
