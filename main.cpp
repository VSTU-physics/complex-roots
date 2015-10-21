#include <iostream>

#include "complex.hpp"
#include "roots.hpp"


void test(const char* name, func f, cmplx z1, cmplx z2) {
    std::cout << name << " в прямоугольнике " << z1 << " " << z2 << std::endl;
    auto answer = roots(f, z1, z2);
    for (auto i: answer)
        std::cout << i << std::endl;

    std::cout << std::endl;
}

int main() {
    test("1/z",     [](cmplx z){return 1. / z;}, cmplx(-0.1, -0.2), cmplx(1., 2.));
    test("z",       [](cmplx z){return z;}, cmplx(-0.1, -0.2), cmplx(1., 2.));
    test("z + 1/z", [](cmplx z){return z + 1. / z;}, cmplx(-1, -2), cmplx(1., 2.));
    test("sin z",   [](cmplx z){return sin(z);}, cmplx(-10, -10), cmplx(10, 10));
    test("sinh z",  [](cmplx z){return sinh(z);}, cmplx(-10, -10), cmplx(10, 10));
}
