#include <iostream>
#include <cmath>
#include <complex>

typedef std::complex<double> cmplx;

cmplx f (cmplx z) {
    return sin(z);
}

cmplx g (cmplx z) {
    return 1.0 / f(z);
}

/*
 * интеграл по отрезку в комплексной плоскости
 */
cmplx integrate(cmplx (*f)(cmplx), cmplx z1, cmplx z2) {
    cmplx result = 0;
    for (int i = 0; i < 100; ++i) {
        cmplx z = (double(100 - i) * z1 + double(i) * z2) / 100.0;
        result += f(z) * (z2 - z1) / 100.0;
    }
    return result;
}

/*
 * интеграл по прямоугольному контуру размерами w x h с центром в точке (x0, y0)
 */
cmplx contourIntegral (double x0, double y0, double w, double h) {
    cmplx result = 0;

    double x1 = x0 - w/2,
           x2 = x0 + w/2,
           y1 = y0 - h/2,
           y2 = y0 + h/2;

    cmplx z1 = cmplx(x2, y1);
    cmplx z2 = cmplx(x2, y2);
    cmplx z3 = cmplx(x1, y2);
    cmplx z4 = cmplx(x1, y1);

    result += integrate(g, z1, z2);
    result += integrate(g, z2, z3);
    result += integrate(g, z3, z4);
    result += integrate(g, z4, z1);

    return result;
}

/*
 * Число нулей внутри круга радиуса R с центром в начале координат
 */
int numberOfRoots(cmplx (*f)(cmplx), double R) {
    int result = 0;
    int n = 100;

    double arg = std::arg(f(R));
    double parg = arg;
    for (int i = 1; i <= n; ++i) {
        cmplx z = R * exp(cmplx(0, 2.0 * i * M_PI / n));
        arg = atan2(f(z).imag(), f(z).real());
        if (arg * parg < 0)
            ++result;
        parg = arg;
    }

    // на каждом обороте происходит по 2 смены знака
    // если образ начальной точки будет на оси координат, то эта смена знака
    // потеряется, контроль чётности вернёт её
    if (result % 2)
        ++result;

    return result/2;
}

cmplx integrate_log(cmplx (*f)(cmplx), cmplx z1, cmplx z2){
    cmplx r = 0;
    cmplx z = z1, dz;
    int n = 100;

    dz = 1. / n * (z2 - z1);
    r += 0.25 * (f(z + dz) - f(z - dz)) / f(z);
    for (int i = 1; i < n; ++i) {
        z += dz;
        r += 0.5 * (f(z + dz) - f(z - dz)) / f(z);
    }
    z += dz;
    r += 0.25 * (f(z + dz) - f(z - dz)) / f(z);

    return r;
}
/*
 * Число корней внутри квадрата
 */
int numberOfRoots(cmplx (*f)(cmplx), cmplx z1, cmplx z2) {
    cmplx r = 0, z;

    r += integrate_log(f, z1, z = cmplx(z2.real(), z1.imag()));
    r += integrate_log(f, z, z2);
    r += integrate_log(f, z2, z = cmplx(z1.real(), z2.imag()));
    r += integrate_log(f, z, z1);

    return (int) round(r.imag()/M_PI/2);
}

int numberOfRoots(cmplx (*f)(cmplx), double x0, double y0, double w, double h) {
    double x1 = x0 - w/2,
           x2 = x0 + w/2,
           y1 = y0 - h/2,
           y2 = y0 + h/2;

    return numberOfRoots(f, cmplx(x1, y1), cmplx(x2, y2));
}

int main() {
    std::cout << contourIntegral(0,0,20,20) << std::endl;
    std::cout << numberOfRoots(f, 10.0) << std::endl;
    std::cout << numberOfRoots(f, 0, 0, 20, 20) << std::endl;
}
