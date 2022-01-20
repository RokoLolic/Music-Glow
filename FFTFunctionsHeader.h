#pragma once
#ifndef FFTUSER
#define FFTUSER

#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fft(fftw_complex *, fftw_complex *, int);
void ifft(fftw_complex *, fftw_complex *, int);
double cabs(double, double);
void filter(fftw_complex *, int, int, int);
void fftw_create(fftw_complex* , double* , int );
void fftw_todouble(fftw_complex* , double* , int );
#endif