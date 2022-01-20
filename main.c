#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>

#include	<sndfile.h>
#include <FFTFunctionsHeader.h>
#pragma warning(disable:4996)
//#include "FFTFunctionsHeader.h"


//#define		SAMPLE_RATE			44100
//#define		SAMPLE_ALL		(SAMPLE_RATE * 4)	/* 4 seconds */
/*#define		AMPLITUDE			(1.0 * 0x7F000000)
#define		LEFT_FREQ			(344.0 / SAMPLE_RATE)
#define		RIGHT_FREQ			(466.0 / SAMPLE_RATE)*/

int
main(void)
{
	SNDFILE	*file, *filenew;
	SF_INFO	sfinfo, sfinfonew;
	FILE* filetext;
	int		k, alldata;
	double	*buffer;
	//fftw_complex *in_original, *fourier, *out_original;
	char filename[16] = "ddd.wav", filenamenew[16] = "ddd2.wav";
	file = sf_open(filename, SFM_READ, &sfinfo);
	alldata = sfinfo.frames;

	if (!(buffer = malloc(2 * alldata * sizeof(double))))
	{
		printf("Error : Malloc failed.\n");
		return 1;
	};
	
	//buffer = new float(2 * alldata);
	//memset(&sfinfo, 0, sizeof(sfinfo));

	/*sfinfo.samplerate = SAMPLE_RATE;
	sfinfo.frames = SAMPLE_ALL;
	sfinfo.channels = 2;
	sfinfo.format = (SF_FORMAT_WAV | SF_FORMAT_PCM_24);*/

	if (!(file = sf_open(filename, SFM_READ, &sfinfo)))
	{
		printf("Error : Not able to open output file.\n");
		free(buffer);
		return 1;
	};
	

	//memset(&sfinfonew, 0, sizeof(sfinfo));
	sfinfonew.samplerate = sfinfo.samplerate;
	sfinfonew.frames = sfinfo.frames;
	sfinfonew.channels = sfinfo.channels;
	sfinfonew.format = sfinfo.format;
	
	printf("%d %d %d %d\n", sfinfonew.samplerate, sfinfonew.frames, sfinfonew.channels, sfinfonew.format); //debugging
	filenew = sf_open(filenamenew, SFM_WRITE, &sfinfonew); //otvara dokument za pisanje, sprema informacije u sfinfonew
	printf("%d\n", sf_error(filenew));
	printf("%d\n", sf_error(file));
	/*if (sfinfo.channels == 1)
	{
		for (k = 0; k < alldata; k++)
			buffer[k] = (int)(AMPLITUDE * sin(LEFT_FREQ * 2 * k * M_PI));

	}
	else if (sfinfo.channels == 2)
	{
		for (k = 0; k < alldata; k++)
		{
			buffer[2 * k] = (int)(AMPLITUDE * sin(LEFT_FREQ * 2 * k * M_PI));
			buffer[2 * k + 1] = (int)(AMPLITUDE * sin(LEFT_FREQ * 2 * k * M_PI));

		};
	}
	else
	{
		printf("Error : make_sine can only generate mono or stereo files.\n");
		sf_close(file);
		free(buffer);
		return 1;
		};*/

	/*if (sf_write_int(file, buffer, sfinfo.channels * alldata) !=
		sfinfo.channels * alldata)
		puts(sf_strerror(file))*/
	sf_read_double(file, buffer, sfinfo.channels * alldata);
	filetext=fopen("audiotextddd.txt", "w");
	if (sfinfo.channels == 1)
	{
		for (k = 0; k < alldata; k++) {
			//buffer[k] /= 4;
			fprintf(filetext, "%lf\n", buffer[k]);
		}

	}
	else if (sfinfo.channels == 2)
	{
		for (k = 0; k < alldata; k++)
		{
			//buffer[2 * k] /= 4;
			//buffer[2 * k + 1] /= 4;
			fprintf(filetext, "%lf\n", buffer[2 * k]);
		};
	}
	else
	{
		printf("Error :only  mono or stereo files.\n");
		sf_close(file);
		sf_close(filenew);
		free(buffer);
		return 1;
	};
	fclose(filetext);
	/*POKUŠAJ FOURIEROVE ANALIZE*/

	//in_original = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * alldata * 2); //koji ulazi
	//fourier = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * alldata * 2); //ulaz nakon fourierova transforma
	//out_original = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * alldata * 2); //fourierov transform nakon inverznog FT
	//piše double u buffer iz originala
	//fftw_create(in_original, buffer, sfinfo.channels * alldata); //stavlja buffer u format za fftw u in_original
	//fft(in_original, fourier, sfinfo.channels * alldata); //in:original fft u fourier
	/*for (int i = 0; i < sfinfo.channels * alldata; i++) {
		//if(cabs(*(*(fourier + i) + 0), *(*(fourier + i) + 1)) > 0.0001)
		printf("%d: %f %f\n", i,  *(*(fourier + i) + 0) / (sfinfo.channels * alldata), *(*(fourier + i) + 1) /  (sfinfo.channels * alldata));
	}*/
//	filter(fourier, 0, 1000, sfinfo.channels * alldata,  sfinfo.channels * alldata);
	//ifft(fourier, out_original, sfinfo.channels * alldata); //inverz, fourier u out:original, trebao bi biti isti kao 
	//fftw_todouble(out_original, buffer, sfinfo.channels * alldata);
	/*for (int i = 44; i < sfinfo.channels * alldata; i++)
	{
		printf("%d ", buffer[i]);
	}*/

	sf_write_double(filenew, buffer, sfinfonew.channels * alldata);


	sf_close(file);
	sf_close(filenew);
	free(buffer);
	//delete[] buffer;
	//fftw_free(in_original);
	//fftw_free(fourier);
	//fftw_free(out_original);
	return 0;
} /* main */
