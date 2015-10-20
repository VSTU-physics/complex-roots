#pragma once

cmplx integrate(cmplx (*f)(cmplx), cmplx z1, cmplx z2, int n = 100);
cmplx integrateLog(cmplx (*f)(cmplx), cmplx z1, cmplx z2);
