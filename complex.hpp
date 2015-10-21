#pragma once

#include <complex>
#include <cmath>
#include <functional>

using cmplx = std::complex<double>;
using func = std::function<cmplx (cmplx)>;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif // M_PI
