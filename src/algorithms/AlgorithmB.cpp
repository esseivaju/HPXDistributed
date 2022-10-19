//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmB.h"
#include <Eigen/Dense>
#include <hpx/iostream.hpp>
#include <iostream>

namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmB::initialize() {
        return SUCCESS;
    }

    Algorithm::StatusCode AlgorithmB::operator()(EventContext<id_t> &e){
        volatile float sum = 0;
        Eigen::MatrixXf AB =  e.matrixA() * e.matrixB();
        Eigen::MatrixXf m =  e.matrixA();
        for(int i = 0; i < _nIter ; ++i){
            m *= AB;
            sum += m.norm();
        }
        return SUCCESS;
    }

    AlgorithmB::AlgorithmB() : Algorithm(1, "AlgorithmB") {}

}// namespace hpxdistributed::algorithms