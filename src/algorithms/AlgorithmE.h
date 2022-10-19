//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHME_H
#define HPXDISTRIBUTED_ALGORITHME_H

#include "Algorithm.h"

namespace hpxdistributed::algorithms {

    class AlgorithmE : public Algorithm {
    public:
        AlgorithmE();
        StatusCode initialize() override;
        StatusCode operator()(EventContext<id_t> &) override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHME_H
