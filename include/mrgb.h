/*
* RGB operate util
*
* author:lwh
*
*/
#ifndef __MRGB_H__
#define __MRGB_H__

#ifdef _Cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

typedef struct{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB888; 

#pragma pack(pop)

#ifdef _Cplusplus
}
#endif

#endif