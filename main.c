#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>

#include	<sndfile.h>
#include <FFTFunctionsHeader.h>
#pragma warning(disable:4996)



int
main(void)
{
	SNDFILE	*file, *filenew;
	SF_INFO	sfinfo, sfinfonew;
	FILE* filetext;
	int		k, alldata;
	double	*buffer;
	
	char filename[16] = "sine.wav", filenamenew[16] = "sine2.wav"; //gdje ce citati
	file = sf_open(filename, SFM_READ, &sfinfo);
	alldata = sfinfo.frames;

	if (!(buffer = malloc(2 * alldata * sizeof(double))))
	{
		printf("Error : Malloc failed.\n");
		return 1;
	};
	
	

	if (!(file = sf_open(filename, SFM_READ, &sfinfo)))
	{
		printf("Error : Not able to open output file.\n");
		free(buffer);
		return 1;
	};
	

	
	sfinfonew.samplerate = sfinfo.samplerate; //kopiranje headera u novi fajl
	sfinfonew.frames = sfinfo.frames;
	sfinfonew.channels = sfinfo.channels;
	sfinfonew.format = sfinfo.format;
	
	printf("%d %d %d %d\n", sfinfonew.samplerate, sfinfonew.frames, sfinfonew.channels, sfinfonew.format); //debugging
	filenew = sf_open(filenamenew, SFM_WRITE, &sfinfonew); //otvara dokument za pisanje, sprema informacije u sfinfonew
	printf("%d\n", sf_error(filenew));
	printf("%d\n", sf_error(file));
	
	sf_read_double(file, buffer, sfinfo.channels * alldata);
	filetext=fopen("audiotextddd.txt", "w");
	if (sfinfo.channels == 1) //mono
	{
		for (k = 0; k < alldata; k++) {
			fprintf(filetext, "%lf\n", buffer[k]);
		}

	}
	else if (sfinfo.channels == 2) //stereo
	{
		for (k = 0; k < alldata; k++)
		{
			fprintf(filetext, "%lf\n", buffer[2 * k]);
		};
	}
	else
	{
		printf("Error :only  mono or stereo files.\n"); //pogreska
		sf_close(file);
		sf_close(filenew);
		free(buffer);
		return 1;
	};
	fclose(filetext);


	sf_write_double(filenew, buffer, sfinfonew.channels * alldata);


	sf_close(file);
	sf_close(filenew);
	free(buffer);
	
	return 0;
} 
