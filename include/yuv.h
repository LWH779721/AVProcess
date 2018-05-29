#ifndef __YUV_H__
#define __YUV_H__

#ifdef C_plusplus
extern "C" {
#endif

typedef struct {
    unsigned width;
    unsigned height;
    unsigned char buf[0];
} YUV;

typedef struct {
    unsigned char Y;
    unsigned char U;
    unsigned char V;
} YUV_Color;

typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGB888;

#ifdef C_plusplus
}
#endif

#endif