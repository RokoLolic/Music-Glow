#pragma once
#ifndef FFTUSER
#define FFTUSER

#include <fftw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>

void fft(fftw_complex *, fftw_complex *, int);
void ifft(fftw_complex *, fftw_complex *, int);
double cabs(double, double);
void filter(fftw_complex *, int, int, int);

#endif