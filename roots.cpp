#include <queue>

#include "complex.hpp"
#include "integrals.hpp"
#include "rectangle.hpp"
#include "roots.hpp"

/*
 * Число корней внутри квадрата
 */
unsigned int numberOfRoots(cmplx (*f)(cmplx), cmplx z1, cmplx z2) {
    cmplx r = 0, z;

    r += integrateLog(f, z1, z = cmplx(z2.real(), z1.imag()));
    r += integrateLog(f, z, z2);
    r += integrateLog(f, z2, z = cmplx(z1.real(), z2.imag()));
    r += integrateLog(f, z, z1);

    return std::abs((int) round(r.imag() / M_PI / 2));
}


cmplxs roots(cmplx (*f)(cmplx), cmplx z1, cmplx z2, double eps) {
    std::queue<rectangle> rects;

    // небольшие сдвиги начальных границ, чтобы корни с меньшей вероятностью
    // легли на границу областей
    rectangle r = {z1 - cmplx(0, eps), z2 + eps};

    auto n = numberOfRoots(f, r.z1, r.z2);
    if (n == 0)
        return {};

    rects.push(r);
    while (!rects.empty() && rects.front().diag() > eps) {
        r = rects.front();
        rects.pop();

        // эта штука считается дважды для каждого прямоугольника
        n = numberOfRoots(f, r.z1, r.z2);
        if (n == 0) continue;

        rectangle r1, r2;
        divide(r, r1, r2);

        auto n1 = numberOfRoots(f, r1.z1, r1.z2);
        auto n2 = numberOfRoots(f, r2.z1, r2.z2);

        /* while (roots1 + roots2 < roots) {} */

        if (n1) rects.push(r1);
        if (n2) rects.push(r2);
    }

    cmplxs roots;
    while (!rects.empty()) {
        auto z = rects.front().center();

        if (std::abs(z.real()) < eps)
            z = cmplx(0, z.imag());
        if (std::abs(z.imag()) < eps)
            z = cmplx(z.real(), 0);

        roots.push_back(z);
        rects.pop();
    }

    return roots;
}


