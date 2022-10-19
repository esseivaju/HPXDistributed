//
// Created by esseivaj on 8/12/22.
//

#include "AlgorithmA.h"
#include <Eigen/Dense>
#include <random>


namespace hpxdistributed::algorithms {
    using enum Algorithm::StatusCode;
    Algorithm::StatusCode AlgorithmA::initialize() {
        return SUCCESS;
    }
    Algorithm::StatusCode AlgorithmA::operator()(EventContext<id_t> &e){
        // see https://eigen.tuxfamily.org/dox/TopicMultiThreading.html#title1
        std::default_random_engine generator;
        std::uniform_real_distribution<float> distribution(-1.0, 1.0);
        auto uniform = [&] () {return distribution(generator);};
        // two matrices of 64x64 float fit perfectly in L1 dcache of perlmutter CPUs (32Kb)
        constexpr size_t MATRIX_SZ{1000};
        Eigen::MatrixXf mA = Eigen::MatrixXf::NullaryExpr(MATRIX_SZ, MATRIX_SZ, uniform);
        e.matrixA() = mA;
        Eigen::MatrixXf mB = Eigen::MatrixXf::NullaryExpr(MATRIX_SZ, MATRIX_SZ, uniform);
        e.matrixB() = mB;
        return SUCCESS;
    }
    AlgorithmA::AlgorithmA() : Algorithm(1, "AlgorithmA") {}
}// namespace hpxdistributed::algorithms