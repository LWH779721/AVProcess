#include <faac.h>
#include <stdio.h>
 
typedef unsigned long   ULONG;
typedef unsigned int    UINT;
typedef unsigned char   BYTE;
 
int main(int argc, char * argv[])
{
    ULONG nSampleRate = 44100;  // 采样率
    UINT nChannels = 1;         // 声道数
    UINT nPCMBitSize = 16;      // 单样本位数
    ULONG nInputSamples = 0;
    ULONG nMaxOutputBytes = 0;
 
    int nRet;
    faacEncHandle hEncoder;
    faacEncConfigurationPtr pConfiguration;
 
    int nBytesRead;
    int nPCMBufferSize;
    BYTE* pbPCMBuffer;
    BYTE* pbAACBuffer;
 
    FILE* fpIn; // WAV file for input
    FILE* fpOut; // AAC file for output
 
    fpIn = fopen("L.pcm", "rb");//  resample.pcm
    fpOut = fopen("test.aac", "wb");//  resample.aac
	
	printf("1 -------------------------------\n");
    // (1) Open FAAC engine
    hEncoder = faacEncOpen(nSampleRate, nChannels, &nInputSamples, &nMaxOutputBytes);
    if(hEncoder == NULL)
    {
        printf("[ERROR] Failed to call faacEncOpen()\n");
        return -1;
    }
	
	printf("2 -------------------------------\n");
    nPCMBufferSize = nInputSamples * nPCMBitSize / 8;
    pbPCMBuffer = new BYTE [nPCMBufferSize];
    pbAACBuffer = new BYTE [nMaxOutputBytes];
 
    // (2.1) Get current encoding configuration
    pConfiguration = faacEncGetCurrentConfiguration(hEncoder);
    printf("3 -------------------------------\n"); 
	
	pConfiguration->aacObjectType = LOW;    //LC编码
	pConfiguration->mpegVersion = MPEG4;  //
	pConfiguration->useTns   = 1 ;                   //时域噪音控制,大概就是消爆音
	pConfiguration->allowMidside = 0 ;            //
	pConfiguration->bitRate  = 0;
	pConfiguration->bandWidth  = 0 ;              //频宽
	pConfiguration->outputFormat = 1;  //输出是否包含ADTS头
	pConfiguration->inputFormat = FAAC_INPUT_16BIT;
	//faacCfg->shortctl = 0 ;
	pConfiguration->quantqual = 100 ;

    // (2.2) Set encoding configuration
    nRet = faacEncSetConfiguration(hEncoder, pConfiguration);
	printf("4 -------------------------------\n");
    for(int i = 0; 1; i++)
    {
        // 读入的实际字节数，最大不会超过nPCMBufferSize，<br data-filtered="filtered">      
		nBytesRead = fread(pbPCMBuffer, 1, nPCMBufferSize, fpIn);
        // 输入样本数，用实际读入字节数计算，一般只有读到文件尾时才不是nPCMBufferSize/(nPCMBitSize/8);
        nInputSamples = nBytesRead / (nPCMBitSize / 8);
		printf("%d .... %d\n", nBytesRead, nInputSamples);
        // (3) Encode
        nRet = faacEncEncode(
            hEncoder, (int*) pbPCMBuffer, nInputSamples, pbAACBuffer, nMaxOutputBytes);
		printf("5 -------------------------------\n");
        fwrite(pbAACBuffer, 1, nRet, fpOut);
 
        printf("%d: faacEncEncode returns %d\n", i, nRet);
 
        if(nBytesRead <= 0)
        {
            break;
        }
    }
 
    nRet = faacEncClose(hEncoder);
 
    delete[] pbPCMBuffer;
    delete[] pbAACBuffer;
    fclose(fpIn);
    fclose(fpOut);
 
    return 0;
}