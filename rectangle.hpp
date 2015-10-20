#pragma once

struct rectangle {
    cmplx z1, z2;

    double diag () {return std::abs(z1 - z2);}
    cmplx center () {return (z1 + z2) / 2.;}
};


void divide(const rectangle & r, rectangle & r1, rectangle & r2, double ratio = 1.0);
