#include "FFTFunctionsHeader.h"

void fft(fftw_complex *in, fftw_complex *out, int N) {
	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p); /* repeat as needed */

	fftw_destroy_plan(p);
}

void ifft(fftw_complex *in, fftw_complex *out, int N) {
	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

	fftw_execute(p); /* repeat as needed */

	fftw_destroy_plan(p);
}

double cabs(double real, double imaginary) {
	return sqrt(real*real + imaginary * imaginary);
}
void filter(fftw_complex *in, int lowerbound, int upperbound, int length) {
	for (int i = 0; i < lowerbound; i++) {
		*(*(in + i) + 0) = 0;
		*(*(in + i) + 1) = 0;
	}
	for (int i = upperbound; i < length /2; i++){
		*(*(in + i) + 0) = 0;
		*(*(in + i) + 1) = 0;
	}

	for (int i = length/2; i < length - upperbound + 1; i++) {
		*(*(in + i) + 0) = 0;
		*(*(in + i) + 1) = 0;
	}
	for (int i = length-lowerbound; i < length; i++) {
		*(*(in + i) + 0) = 0;
		*(*(in + i) + 1) = 0;
	}

	/*for (int i = lenght - upperbound; i < lenght ; i++) {
		*(*(in + i) + 0) = 0;
		*(*(in + i) + 1) = 0;
	}*/
	//for (int i=0; i++)
}