#include <queue>

#include "complex.hpp"
#include "integrals.hpp"
#include "rectangle.hpp"
#include "roots.hpp"


/*
 * Число корней внутри прямоугольника
 */
unsigned int numberOfRoots(func f, cmplx z1, cmplx z2) {
    cmplx r = 0, z;

    r += integrateLog(f, z1, z = cmplx(z2.real(), z1.imag()));
    r += integrateLog(f, z, z2);
    r += integrateLog(f, z2, z = cmplx(z1.real(), z2.imag()));
    r += integrateLog(f, z, z1);

    return std::abs((int) round(r.imag() / M_PI / 2));
}

unsigned int numberOfRootsArg(func f, cmplx z1, cmplx z2) {
    int n = 100;
    double angle = 0;
    cmplx zs[] = {z1, cmplx(z2.real(), z1.imag()),
                  z2, cmplx(z1.real(), z2.imag()), z1};
    double arg = 0;
    for (int j = 0; j < 4; ++j)
    for (int i = 0; i < n; ++i) {
        auto z = (zs[j] * double(n-i) + zs[j+1] * double(i)) / double(n) ;
        double arg1 = std::arg(f(z));
        if (arg == 0) {
            arg = arg1;
            continue;
        }
        // дополняем старый аргумент до непрерывности с новым
        if (arg1 - arg > M_PI)
            arg += 2.0 * M_PI;
        if (arg - arg1 > M_PI)
            arg -= 2.0 * M_PI;
        angle += arg1 - arg;
        arg = arg1;
    }

    return std::abs((int) round(angle / M_PI / 2));
}


unsigned int numberOfRoots(func f, rectangle r) {
    double x1 = r.z1.real(), x2 = r.z2.real(), y1 = r.z1.imag(), y2 = r.z2.imag();
    cmplx z1 = cmplx(std::min(x1, x2), std::min(y1, y2)),
          z2 = cmplx(std::max(x1, x2), std::max(y1, y2));
    return numberOfRootsArg(f, z1, z2);
}


cmplxs roots(func f, cmplx z1, cmplx z2, double eps) {
    std::queue<rectangle> rects;

    // небольшие сдвиги начальных границ, чтобы корни с меньшей вероятностью
    // легли на границу областей
    rectangle r = {z1 - eps, z2 + eps * cmplx(0, 1)};

    auto n = numberOfRoots(f, r.z1, r.z2);
    if (n == 0)
        return {};

    rects.push(r);
    while (!rects.empty() && rects.front().diag() > eps) {
        r = rects.front();
        rects.pop();

        rectangle r1, r2;
        r.divide(r1, r2);

        auto n1 = numberOfRoots(f, r1);
        auto n2 = numberOfRoots(f, r2);

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


