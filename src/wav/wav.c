#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav/wav.h"

struct wav_encode * wav_init(struct pcm_info *pcm_info, char *fname)
{
	struct wav_encode *encoder = NULL;
	
	if (NULL == pcm_info)
	{
		printf("failed when malloc \n");
		return NULL;	
	}
	
	if (NULL == (encoder = malloc(sizeof(struct wav_encode))))
	{
		printf("failed when malloc \n");
		return NULL;
	}
	
	encoder->data_size = 0;
	if (NULL == (encoder->fp = fopen(fname, "wb+")))
	{
		printf("failed when file open\n");
		goto failed;
	}

	rewind(encoder->fp);
	memcpy((void *)&encoder->head.ChunkID, "RIFF", 4);
	memcpy((void *)&encoder->head.Format, "WAVE", 4);
	memcpy((void *)&encoder->head.Subchunk1ID, "fmt ", 4);
	memcpy((void *)&encoder->head.Subchunk2ID, "data", 4);

	encoder->head.AudioFormat = 1;
	encoder->head.Subchunk1Size = 16;
	encoder->head.NumChannels = pcm_info->channels;
	encoder->head.SampleRate = pcm_info->sampleRate;
	encoder->head.BitsPerSample = pcm_info->sampleBits;
	encoder->head.BlockAlign = encoder->head.NumChannels * encoder->head.BitsPerSample/8;
	encoder->head.ByteRate = encoder->head.SampleRate * encoder->head.BlockAlign; 
	encoder->head.ChunkSize = 0;
	encoder->head.Subchunk2Size = 0;

	fwrite(&encoder->head, 1, sizeof(encoder->head), encoder->fp);
	
	return encoder;
failed:
	
	free(encoder);
	return NULL;
}

int wav_append(struct wav_encode *encoder, unsigned char *pcm_buf, unsigned int pcm_size)
{
	unsigned int write = 0;
	int ret;

	while (write < pcm_size)
	{
		ret = fwrite(pcm_buf + write, sizeof(char), pcm_size - write, encoder->fp);
		if (ret > 0)
		{
			write += ret;			
		}			
	}	

	encoder->data_size += write;
	return encoder->data_size;
}

int wav_finish(struct wav_encode *encoder)
{
	encoder->head.ChunkSize = 36 + encoder->data_size;
	encoder->head.Subchunk2Size = encoder->data_size;

	rewind(encoder->fp);
	fwrite(&encoder->head, 1, sizeof(encoder->head), encoder->fp);
	fclose(encoder->fp);
	
	return 0;
}
#if 0
int wav_init(char *pcmfname)
{
	struct wav_head head = {
		.ChunkSize = 1953828,
		.Subchunk1Size = 16,
		.AudioFormat = 1,
		.NumChannels = 1,
		.SampleRate = 44100,
		.ByteRate = 88200,
		.BlockAlign = 2,
		.BitsPerSample = 16,
		.Subchunk2Size = 1953792,
	};
	
	memcpy((void *)&head.ChunkID, "RIFF", 4);
	memcpy((void *)&head.Format, "WAVE", 4);
	memcpy((void *)&head.Subchunk1ID, "fmt ", 4);
	memcpy((void *)&head.Subchunk2ID, "data", 4);
	FILE *fp = NULL, *fpdst = NULL;
	
	if (NULL == (fp = fopen(pcmfname, "rb"))
		|| NULL == (fpdst = fopen("b.wav", "wb+")))
	{
		printf("failed when file open\n");
		return -1;
	}
	
	rewind(fp);
	rewind(fpdst);
	fwrite(&head, 1, sizeof(head), fpdst);
	printf("sizeof head: %ld\n", sizeof(head));
	char buf[2];
	int i = 0;
	while (!feof(fp))
	{
		fread(buf, 1, 2, fp);
		if (feof(fp))
		{
			break;
		}
		fwrite(buf, 1, 2, fpdst);
		i++;
	}
	printf("i: %d\n", i);
	fclose(fp);
	fclose(fpdst);
	return 0;
}
#endif