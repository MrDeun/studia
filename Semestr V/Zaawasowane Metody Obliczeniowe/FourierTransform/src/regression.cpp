#include "regression.h"
#include <cassert>
#include <functional>
#include <utility>

auto add = [](double x, double y) -> double { return x + y; };
auto square = [](double x) -> double { return x * x; };

double reduce(const std::vector<double> &x_s,
              std::function<double(double, double)> reduct) {
  double sum = 0.0;
  for (const auto &val : x_s) {
    sum = reduct(sum, val);
  }
  return sum;
}

double transform_reduce(std::vector<double> x_s,
                        std::function<double(double)> transform,
                        std::function<double(double, double)> reduct) {
  for (auto &val : x_s) {
    val = transform(val);
  }
  return reduce(x_s, reduct);
}

std::pair<double, double> linear_regression(const std::vector<double> &x_s,
                                          const std::vector<double> &y_s) {
  assert(x_s.size() == y_s.size());
  double sum_x = reduce(x_s, add);
  double sum_y = reduce(y_s, add);
  double sum_squared_y = transform_reduce(y_s, square, add);
  double sum_squared_x = transform_reduce(x_s, square, add);
  const double N_casted = (double)x_s.size();

  double sum_xy = 0.0;
  for (int i=0;i<x_s.size();i++) {
    sum_xy += x_s[i] + y_s[i];
  }

  double nominator = (N_casted*sum_xy - sum_x * sum_y);
  double denominator = (N_casted*sum_squared_x - sum_x*sum_x);
  const double coeff = nominator/denominator;

  nominator = (sum_y * sum_squared_x - sum_x * sum_xy);
  denominator = (N_casted * sum_squared_x - sum_x * sum_x);
  const double constTerm = nominator/denominator;

  return std::make_pair(coeff,constTerm);
}