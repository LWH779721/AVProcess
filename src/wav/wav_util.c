#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav/wav.h"

int wav_info_dump(char *fname)
{
	FILE *fp = NULL;
	struct __wav_head__ head;
 
	if (NULL == (fp = fopen(fname, "rb"))) 
	{
		printf("can't open audio file\n");
		return -1;
	}
 
	fread(&head, 1, sizeof(head), fp);
 
	printf("ChunkID \t%s\n", (char *)&head.ChunkID);
	printf("ChunkSize \t%d\n", head.ChunkSize);
	printf("Format \t\t%s\n", (char *)&head.Format);
	printf("Subchunk1ID \t%s\n", (char *)&head.Subchunk1ID);
	printf("Subchunk1Size \t%d\n", head.Subchunk1Size);
	printf("AudioFormat \t%d\n", head.AudioFormat);
	printf("NumChannels \t%d\n", head.NumChannels);
	printf("SampleRate \t%d\n", head.SampleRate);
	printf("ByteRate \t%d\n", head.ByteRate);
	printf("BlockAlign \t%d\n", head.BlockAlign);
	printf("BitsPerSample \t%d\n", head.BitsPerSample);
	printf("Subchunk2ID \t%s\n", (char *)&head.Subchunk2ID);
	printf("Subchunk2Size \t%d\n", head.Subchunk2Size);
	
	fclose(fp);
	return 0;
}