#include "complex.hpp"
#include "rectangle.hpp"
#include "integrals.hpp"

void divide(const rectangle & r, rectangle & r1, rectangle & r2, double ratio){
    auto width = (r.z2 - r.z1).real();
    auto height = (r.z2 - r.z1).imag();

    // вот этот кусок стоит упростить
    if (width > height) {
        auto u1 = r.z1, u2 = r.z2 - (r.z2 - r.z1).real() / (1. + ratio);
        r1 = {u1, u2};

        u1 = r.z1 + (r.z2 - r.z1).real() * ratio / (1. + ratio), u2 = r.z2;
        r2 = {u1, u2};
    } else {
        auto u1 = r.z1, u2 = r.z2 - cmplx(0, (r.z2 - r.z1).imag() / (1. + ratio));
        r1 = {u1, u2};

        u1 = r.z1 + cmplx(0, (r.z2 - r.z1).imag() * ratio / (1. + ratio)), u2 = r.z2;
        r2 = {u1, u2};
    }
}


