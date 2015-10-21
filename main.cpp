#include <iostream>

#include "complex.hpp"
#include "roots.hpp"

cmplx f (cmplx z) {
    return z + 1. / z;
}

int main() {
    auto answer = roots(f, cmplx(-0.01, -0.02), cmplx(0.1, 0.2));
    for (auto i: answer)
        std::cout << i << std::endl;
}
