//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmC.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmC::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmC::operator()(EventContext<id_t> &e){
        volatile float sum = 0;
        Eigen::MatrixXf AB =  e.matrixA() + e.matrixB();
        Eigen::MatrixXf m =  e.matrixA();
        for(int i = 0; i < _nIter ; ++i){
            m += AB;
            sum += m.norm();
        }
        return SUCCESS;
    }
    AlgorithmC::AlgorithmC() : Algorithm(1, "AlgorithmC") {}
}// namespace hpxdistributed::algorithms