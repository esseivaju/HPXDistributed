//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmE.h"

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmE::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmE::operator()(EventContext<id_t> &e){
        volatile float sum = 0;
        Eigen::MatrixXf AB =  (e.matrixA() * e.matrixB()).transpose();
        Eigen::MatrixXf m =  e.matrixA();
        for(int i = 0; i < _nIter ; ++i){
            m *= AB;
            sum += m.norm();
        }
        return SUCCESS;
    }
    AlgorithmE::AlgorithmE() : Algorithm(1, "AlgorithmE") {}
}// namespace hpxdistributed::algorithms