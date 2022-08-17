//
// Created by esseivaj on 8/12/22.
//

#ifndef HPXDISTRIBUTED_ALGORITHMB_H
#define HPXDISTRIBUTED_ALGORITHMB_H

#include "Algorithm.h"

namespace hpxdistributed::algorithms {

    class AlgorithmB : public Algorithm {
    public:
        AlgorithmB();
        StatusCode initialize() override;
    };

}// namespace hpxdistributed::algorithms

#endif//HPXDISTRIBUTED_ALGORITHMB_H
