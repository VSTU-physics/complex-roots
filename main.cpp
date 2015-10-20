#include <iostream>

#include "complex.hpp"
#include "roots.hpp"

cmplx f (cmplx z) {
    return sin(z) + z;
}

int main() {
    auto answer = roots(f, cmplx(-10., -10.), cmplx(10., 10.));
    for (auto i: answer)
        std::cout << i << std::endl;
}
