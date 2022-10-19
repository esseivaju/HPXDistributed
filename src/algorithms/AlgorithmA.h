//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHMA_H
#define HPXDISTRIBUTED_ALGORITHMA_H

#include "Algorithm.h"

namespace hpxdistributed::algorithms {

    class AlgorithmA : public Algorithm {
    public:
        AlgorithmA();
        StatusCode initialize() override;
        StatusCode operator()(EventContext<id_t> &) override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHMA_H
