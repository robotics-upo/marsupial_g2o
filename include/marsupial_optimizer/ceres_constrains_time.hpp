#ifndef CERES_CONSTRAINS_TIME_HPP
#define CERES_CONSTRAINS_TIME_HPP


#include "ceres/ceres.h"
#include "glog/logging.h"
#include "Eigen/Core"

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;



class TimeFunctor {

public:
  TimeFunctor(double weight_factor, double init_time_): wf_(weight_factor), it_(init_time_) {}

  template <typename T>
  bool operator()(const T* const stateT, T* residual) const 
  {
    residual[0] =  wf_ * exp(stateT[1] - it_);

    return true;
  }

 double wf_, it_;

 private:
};


#endif