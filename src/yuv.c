#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "YUV.h"

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

int main(int argc, char **args)
{
    FILE *fpin, *fpout;
    int len, width, height;
    
    if (NULL == (fpin = fopen(args[1], "rb"))
        || NULL == (fpout = fopen(args[2], "wb")))
    {
        printf("failed when open %s", args[1]);
        return -1;
    }
    
    width = atoi(args[3]);
    height = atoi(args[4]);
    len = width*height;
    len += (len >> 1); 
    
    YUV *src, *dst;
    if (NULL == (src = malloc(sizeof(YUV) + len))
        || NULL == (dst = malloc(sizeof(YUV) + len)))
    {
        printf("failed when malloc\n");
        return -1;    
    }
    
    dst->width = 
    src->width = width;
    dst->height = 
    src->height = height;
    
    fread(src->buf, 1, len, fpin);
#if 0   
    YUV_Color color = {
        .Y = 154,
        .U = 72,
        .V = 24
    };
    YUV_420pDrawRect(src, 100, 200, 1000, 600, &color);
#else
    YUV_420spTo420p(dst, src);
#endif    
    //YUV_420spDrawLine(sp, width, height);
    //YUV_420spTo420p(p, sp, width, height);
    
    //YUV_420spDrawRect(sp, width, height);
    //YUV_420spTo420p(p, sp, width, height);
    fwrite(dst->buf, 1, len, fpout);
    
    free(src);
    free(dst);
    fclose(fpin); 
    fclose(fpout);   
    return 0;
}