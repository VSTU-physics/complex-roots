#include "complex.hpp"
#include "integrals.hpp"

/*
 * интеграл по отрезку в комплексной плоскости
 */
cmplx integrate(func f, cmplx z1, cmplx z2, int n) {
    cmplx result = 0;
    cmplx step = (z2 - z1) / double(n);
    for (int i = 0; i < n; ++i) {
        cmplx z = z1 + double(i) * step;
        result += f(z) * step;
    }
    return result;
}

cmplx integrateLog(func f, cmplx z1, cmplx z2){
    cmplx r = 0;
    cmplx z = z1, dz;
    int n = 100;
    double zero = 1e-9;

    dz = (z2 - z1) / double(n);

    if(std::abs(f(z)) > zero)
        r += 0.5 * (f(z + dz / 2.) - f(z - dz / 2.)) / f(z);

    for (int i = 1; i < n; ++i, z += dz) {
        if(std::abs(f(z)) > zero)
            r += (f(z + dz / 2.) - f(z - dz / 2.)) / f(z);
    }

    z += dz;

    if(std::abs(f(z)) > zero)
        r += 0.5 * (f(z + dz / 2.) - f(z - dz / 2.)) / f(z);

    return r;
}
