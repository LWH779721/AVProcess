#ifndef __WAV_H__
#define __WAV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct __wav_head__ {
	uint32_t ChunkID;	/* "RIFF" */
	uint32_t ChunkSize;	/* 36 + Subchunk2Size */
	uint32_t Format;	/* "WAVE" */
 
	/* sub-chunk "fmt" */
	uint32_t Subchunk1ID;	/* "fmt " */
	uint32_t Subchunk1Size;	/* 16 for PCM */
	uint16_t AudioFormat;	/* PCM = 1*/
	uint16_t NumChannels;	/* Mono = 1, Stereo = 2, etc. */
	uint32_t SampleRate;	/* 8000, 44100, etc. */
	uint32_t ByteRate;		/* = SampleRate * NumChannels * BitsPerSample/8 */
	uint16_t BlockAlign;	/* = NumChannels * BitsPerSample/8 */	
	uint16_t BitsPerSample;	/* 8bits, 16bits, etc. */
 
	/* sub-chunk "data" */
	uint32_t Subchunk2ID;	/* "data" */
	uint32_t Subchunk2Size;	/* data size */
}; 

struct pcm_info {
	unsigned short channels;
	unsigned short sampleBits;
	unsigned int sampleRate;
};

struct wav_encode {
	struct __wav_head__ head;
	
	FILE *fp;
	uint32_t data_size; //data size
};	

extern struct wav_encode * wav_init(struct pcm_info *pcm_info, char *fname);
extern int wav_append(struct wav_encode *encoder, unsigned char *pcm_buf, unsigned int pcm_size);
extern int wav_finish(struct wav_encode *encoder);
#ifdef __cplusplus
}
#endif
#endif