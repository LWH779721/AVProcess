#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "wav/wav.h"

int main(int argc, char **args)
{
	FILE *Lfp, *Rfp, *dstfp;
	
	if (NULL == (Lfp = fopen(args[1], "rb"))
		|| NULL == (Rfp = fopen(args[2], "rb"))
		|| NULL == (dstfp = fopen(args[3], "wb")))
	{
		printf("failed when file open\n");
		return -1;
	}
	
	short Lv, Rv, dstv;
	
	while (1)
	{
		fread((char *)&Lv, 1, 2, Lfp);
		fread((char *)&Rv, 1, 2, Rfp);
		if (feof(Lfp) || feof(Rfp))
		{
			break;
		}

		dstv = ((int)Lv + (int)Rv) >> 1;
		fwrite(&dstv, 1, 2, dstfp);
	}
	
	fclose(Lfp);
	fclose(Rfp);
	fclose(dstfp);
	
	return 0;
}
#if 0
int main(int argc, char **args)
{
	struct wav_encode *encoder = NULL;
	struct pcm_info pcm_info = {1, 16, 44100};
	FILE *fp = NULL;
	
	encoder = wav_init(&pcm_info, args[2]);
	if (NULL == (fp = fopen(args[1], "rb")))
	{
		printf("failed when file open\n");
		return -1;
	}

	rewind(fp);
	char buf[2];
	
	while (!feof(fp))
	{
		fread(buf, 1, 2, fp);
		if (feof(fp))
		{
			break;
		}

		wav_append(encoder, buf, 2);
	}

	fclose(fp);
	wav_finish(encoder);
	
	return 0;
}
#endif