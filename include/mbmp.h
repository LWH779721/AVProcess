/*
* bmp operate util
*
* author:lwh
*
*/
#ifndef __MBMP_H__
#define __MBMP_H__

#ifdef _Cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

typedef struct{
    unsigned short type;        //default 0x4D42 'BM'
    unsigned int total_size;    //file total size
    unsigned short reserved1;   //unused default 0
    unsigned short reserved2;   //unused default 0
    unsigned int offset;        //raw pic data offset
} bmpheader; 

typedef struct{
    unsigned info_size;         //bmp info size 
    int width;                  //pic width pexel
    int height;                 //pic height pexel
    unsigned short planes;      //default 1
    unsigned short bits;        //bits per pels, 16 , 24 ,32
    unsigned int compression;   //
    unsigned int size_image;
    int xpelspermeter;
    int ypelspermeter;
    unsigned int clrused;
    unsigned int clr_important;
} bmpinfo;

#pragma pack(pop)

#ifdef _Cplusplus
}
#endif

#endif