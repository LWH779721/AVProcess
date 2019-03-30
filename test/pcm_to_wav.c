#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "wav/wav.h"
#include "wav/wav_util.h"

int main(int argc, char **args)
{
	struct wav_encode *encoder = NULL;
	struct pcm_info pcm_info = {2, 16, 16000};
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
	wav_info_dump(args[2]);
	return 0;
}