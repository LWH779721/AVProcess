#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "yuv.h"

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