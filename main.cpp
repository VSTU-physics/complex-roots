#include <iostream>
#include <cmath>
#include <complex>

using cmplx = std::complex<double>;

cmplx f (cmplx z) {
    return sin(z);
}

cmplx g (cmplx z) {
    return 1.0 / f(z);
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
 *
 * Считаем изменение аргумента вдоль образа окружности
 * Разделив на 2пи получаем число оборотов, равное числу корней внутри круга
 */
int numberOfRoots(cmplx (*f)(cmplx), double R, cmplx center = cmplx(0,0)) {
    int n = 100;
    
    int result = 0;
    double angle = 0;
    cmplx e = exp(cmplx(0, 2.0 * M_PI / n));
    
    cmplx z = R;
    double arg = std::arg(f(center + z));

    for (int i = 0; i < n; ++i) {
        z *= e;
        double arg1 = std::arg(f(center + z));
        // дополняем старый аргумент до непрерывности с новым
        if (arg1 - arg > M_PI)
            arg += 2.0 * M_PI;
        if (arg - arg1 > M_PI)
            arg -= 2.0 * M_PI;
        angle += arg1 - arg;
        arg = arg1;
    }
    
    result = round(angle / 2.0 / M_PI);
    return result;
}

int main() {
    std::cout << contourIntegral(0,2,3,3) << std::endl;
    std::cout << numberOfRoots(f, 4, cmplx(0, 2.0)) << std::endl;
}
