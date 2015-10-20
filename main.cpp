#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <queue>

#ifndef M_PI
    #define M_PI		3.14159265358979323846
#endif // M_PI

using cmplx = std::complex<double>;
using cmplxs = std::vector<cmplx>;

struct rectangle {
    cmplx z1, z2;
    unsigned int roots;

    double diag () {return std::abs(z1-z2);}
    cmplx center () {return (z1+z2)/2.;}
};

cmplx f (cmplx z) {
    return z*(z-1.)*(z+1.)*(z+2.);
}

/*
 * интеграл по отрезку в комплексной плоскости
 */
cmplx integrate(cmplx (*f)(cmplx), cmplx z1, cmplx z2, int n = 100) {
    cmplx result = 0;
    cmplx step = (z2 - z1) / double(n);
    for (int i = 0; i < n; ++i) {
        cmplx z = z1 + double(i) * step;
        result += f(z) * step;
    }
    return result;
}

cmplx integrateLog(cmplx (*f)(cmplx), cmplx z1, cmplx z2){
    cmplx r = 0;
    cmplx z = z1, dz;
    int n = 100;

    dz = (z2 - z1) / double(n);
    r += 0.5 * (f(z + dz/2.) - f(z - dz/2.)) / f(z);
    for (int i = 1; i < n; ++i) {
        z += dz;
        r += (f(z + dz/2.) - f(z - dz/2.)) / f(z);
    }
    z += dz;
    r += 0.5 * (f(z + dz/2.) - f(z - dz/2.)) / f(z);

    return r;
}
/*
 * Число корней внутри квадрата
 */
unsigned int numberOfRoots(cmplx (*f)(cmplx), cmplx z1, cmplx z2) {
    cmplx r = 0, z;

    r += integrateLog(f, z1, z = cmplx(z2.real(), z1.imag()));
    r += integrateLog(f, z, z2);
    r += integrateLog(f, z2, z = cmplx(z1.real(), z2.imag()));
    r += integrateLog(f, z, z1);

    return std::abs((int) round(r.imag()/M_PI/2));
}

cmplxs roots(cmplx (*f)(cmplx), cmplx z1, cmplx z2, double eps = 1e-5) {
    rectangle r = {z1, z2, numberOfRoots(f, z1, z2)};
    std::queue<rectangle> rects;

    if (r.roots == 0)
        return {};

    rects.push(r);
    while (!rects.empty() && rects.front().diag() > eps) {
        r = rects.front();
        rects.pop();

        if (r.roots == 0) continue;

        auto width = std::abs((r.z2 - r.z1).real());
        auto height = std::abs((r.z2 - r.z1).imag());

        rectangle r1, r2;
        // вот этот кусок стоит упростить
        if (width > height) {
            auto u1 = r.z1, u2 = r.z2 - (r.z2 - r.z1).real() / 2.;
            r1 = {u1, u2, numberOfRoots(f, u1, u2)};

            u1 = r.z1 + (r.z2 - r.z1).real() / 2., u2 = r.z2;
            r2 = {u1, u2, numberOfRoots(f, u1, u2)};
        } else {
            auto u1 = r.z1, u2 = r.z2 - cmplx(0, (r.z2 - r.z1).imag() / 2.);
            r1 = {u1, u2, numberOfRoots(f, u1, u2)};

            u1 = r.z1 + cmplx(0, (r.z2 - r.z1).imag() / 2.), u2 = r.z2;
            r2 = {u1, u2, numberOfRoots(f, u1, u2)};
        }

        if (r1.roots + r2.roots != r.roots) {
            // нужно придумать магию
        }

        if (r1.roots) rects.push(r1);
        if (r2.roots) rects.push(r2);
    }

    cmplxs roots;
    while (!rects.empty()) {
        roots.push_back(rects.front().center());
        rects.pop();
    }

    return roots;
}

int main() {
    auto answer = roots(f, cmplx(-10.1, -10.1), cmplx(10, 10));
    for (auto i: answer)
        std::cout << i << std::endl;
}
