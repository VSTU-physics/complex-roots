#include "complex.hpp"
#include "rectangle.hpp"

void rectangle::divide(rectangle & r1, rectangle & r2, double ratio){
    auto width = (z2 - z1).real();
    auto height = (z2 - z1).imag();

    // вот этот кусок стоит упростить
    if (width > height) {
        auto u1 = z1, u2 = z2 - (z2 - z1).real() / (1. + ratio);
        r1 = {u1, u2};

        u1 = z1 + (z2 - z1).real() * ratio / (1. + ratio), u2 = z2;
        r2 = {u1, u2};
    } else {
        auto u1 = z1, u2 = z2 - cmplx(0, (z2 - z1).imag() / (1. + ratio));
        r1 = {u1, u2};

        u1 = z1 + cmplx(0, (z2 - z1).imag() * ratio / (1. + ratio)), u2 = z2;
        r2 = {u1, u2};
    }
}


