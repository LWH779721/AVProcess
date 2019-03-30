#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "yuv.h"

int YUV_RGBTOYUV(YUV_Color *dst, RGB888 *src)
{
        	
}

int YUV_420spDrawLine(unsigned char *sp, int width, int height)
{
    int len = width * height, i, j;
    unsigned char *Y, *UV;
    
    Y = sp;
    UV = sp + len;
    for (i = 500; i < 1500; i++)
    {
        for (j = 500; j < 504; j++)
        {
            Y[j*width + i] = 154;
            if ((i & 0x1) == 0
                && (j & 0x1) == 0)
                
            {    
                UV[((j/2)*(width/2) + (i/2))*2] = 72;
                UV[((j/2)*(width/2) + (i/2))*2 + 1] = 24;
            }
        }    
    }    
}

int YUV_420spDrawRect(unsigned char *sp, int width, int height)
{
    int len = width * height, i, j;
    unsigned char *Y, *UV;
    
    Y = sp;
    UV = sp + len;
    for (i = 100; i < 1500; i++)
    {
        for (j = 100; j < 800; j++)
        {
            Y[j*width + i] = 154;
            if ((i & 0x1) == 0
                && (j & 0x1) == 0)
            {    
                UV[((j/2)*(width/2) + (i/2))*2] = 72;
                UV[((j/2)*(width/2) + (i/2))*2 + 1] = 24;
            }
        }    
    }
}

int YUV_420pDrawRect(YUV *p, int x, int y, int width, int height, YUV_Color *color)
{
    int len = p->width * p->height, i, j;
    unsigned char *Y, *U, *V;
    int xend, yend;
    
    xend = x + width;
    yend = y + height;
    Y = p->buf;
    U = p->buf + len;
    V = p->buf + len + (len >> 2);

    for (i = x; i < xend; i++)
    {
        for (j = y; j < yend; j++)
        {
            Y[j*p->width + i] = color->Y;
            if ((i & 0x1) == 0
                && (j & 0x1) == 0)
            {    
                U[j*p->width/4 + i/2] = color->U;
                V[j*p->width/4 + i/2] = color->V;
            }
        }    
    }
}

int YUV_420spTo420p(YUV *dst, YUV *src)
{
    int len = src->width * src->height, i;
    char *dst_Y, *dst_U, *dst_V, *src_Y, *src_UV;
    
    src_Y = src->buf;
    src_UV = src_Y + len;
    
    dst->width = src->width;
    dst->height = src->height;
    
    dst_Y = dst->buf;
    dst_U = dst_Y + len;
    dst_V = dst_U + (len >> 2);
    
    memcpy(dst_Y, src->buf, len);
    len = (len >> 2);
    for (i = 0; i < len; i++)
    {
        dst_U[i] = src_UV[i*2];
        dst_V[i] = src_UV[i*2 + 1];
    }
    
    return 0;        
}
