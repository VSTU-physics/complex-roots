#pragma once

#include <vector>
using cmplxs = std::vector<cmplx>;

cmplxs roots(cmplx (*f)(cmplx), cmplx z1, cmplx z2, double eps = 1e-5);
