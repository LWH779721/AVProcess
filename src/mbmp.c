#include <stdio.h>
#include "mbmp.h"

long mbmp_dump(char *file)
{
    FILE *fp;
    bmpheader h;
    bmpinfo info;
    
    if (NULL == (fp = (fopen(file, "rb"))))
    {
        printf("failed when open bmp file\n");
        return -1;
    }
    
    fread(&h, sizeof h, 1, fp);
    if (h.type != 0x4D42)
    {
        printf("not bmp file\n");
        return -1;
    }
    
    printf("type: %04x, size:%d, offset: %d\n", h.type, h.total_size, h.offset);
    
    if (h.offset != 54)
    {
        printf("unsport \n");
        return -1;
    }
    
    fread(&info, sizeof info, 1, fp);
    
    printf("info_size: %d, width:%d, height: %d, bits: %d, compression: %d, size_image: %d, xpelspermeter: %d, ypelspermeter: %d\n", info.info_size, info.width, info.height, info.bits, info.compression, info.size_image, info.xpelspermeter, info.ypelspermeter);
    fclose(fp);  
    
    return 0;  
}

long mbmp_gen(const char* const file, const int width, const int height)
{
    FILE *fp;
    bmpheader h = {0};
    bmpinfo info = {0};
    int i, j, line_size;
    unsigned char buf[1024] = {0};
    
    if (NULL == (fp = (fopen(file, "wb"))))
    {
        printf("failed when open bmp file\n");
        return -1;
    }
    
    h.type = 0x4D42;
    h.total_size = 3*width*height + 54; 
    h.offset = 54;    
    fwrite(&h, sizeof h, 1, fp);
    
    info.info_size = 40;
    info.width = width;
    info.height = height;
    info.planes = 1;
    info.bits = 24;
    fwrite(&info, sizeof info, 1, fp);
    
    line_size = ((3*width + 3) >> 2) << 2; // 行 需要是 4的倍数
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i <= 60)
            {
                buf[3*j] = 0xFF;
                buf[3*j + 1] = 0xFF;
                buf[3*j + 2] = 0xFF; 
            }
            else
            {
                buf[3*j] = 0x00;
                buf[3*j + 1] = 0x00;
                buf[3*j + 2] = 0x00;    
            }
        }
        fwrite(buf, sizeof(unsigned char), line_size, fp);
    }
    
    fclose(fp);
    return 0;
}

long mbmp_vertical_flip(const char* const src, const char* const dst)
{
    FILE *fpin, *fpout;
    bmpheader h;
    bmpinfo info;
    int tmp;
    unsigned char buf[1024] = {0};
    
    if (NULL == src || NULL == dst)
    {
        printf("failed when param invailed\n");
        return -1;    
    }
        
    if (NULL == (fpin = (fopen(src, "rb"))))
    {
        printf("failed when open src bmp file\n");
        return -1;
    }
    
    if (NULL == (fpout = (fopen(dst, "wb"))))
    {
        printf("failed when open dst bmp file\n");
        return -1;
    }
    
    fread(&h, sizeof h, 1, fpin);
    if (h.type != 0x4D42)
    {
        printf("not bmp file\n");
        goto fail_label;
    }
    
    if (h.offset != 54)
    {
        printf("unsport \n");
        goto fail_label;
    }
    
    fwrite(&h, sizeof h, 1, fpout);
    fread(&info, sizeof info, 1, fpin);
    info.height = -info.height;
    fwrite(&info, sizeof info, 1, fpout);
    
    while((tmp = fread(buf, sizeof(unsigned char), 1024, fpin)) > 0)
    {
        fwrite(buf, sizeof(unsigned char), tmp, fpout);    
    }

fail_label:    
    fclose(fpin);  
    fclose(fpout);
    return 0;  
}

long mbmp_horizontal_flip(const char* const src, const char* const dst)
{
    FILE *fp, *fpout;
    bmpheader h;
    bmpinfo info;
    int tmp, i, line_size;
    unsigned char buf[1024] = {0};
    unsigned char p;
    
    if (NULL == (fp = (fopen(src, "rb"))))
    {
        printf("failed when open bmp file\n");
        return -1;
    }
    
    if (NULL == (fpout = (fopen(dst, "wb"))))
    {
        printf("failed when open bmp file\n");
        return -1;
    }
    
    fread(&h, sizeof h, 1, fp);
    if (h.type != 0x4D42)
    {
        printf("not bmp file\n");
        return -1;
    }
    
    if (h.offset != 54)
    {
        printf("unsport \n");
        return -1;
    }
    
    fwrite(&h, sizeof h, 1, fpout);
    fread(&info, sizeof info, 1, fp);
    fwrite(&info, sizeof info, 1, fpout);
   
    line_size = ((3*info.width + 3) >> 2) << 2; // 行 需要是 4的倍数
    while((tmp = fread(buf, sizeof(unsigned char), line_size, fp)) == line_size)
    {
        for (i = 0; i < (info.width >> 1); i++)
        {
            p = buf[3*i];
            buf[3*i] = buf[3*(info.width - i - 1)];
            buf[3*(info.width - i - 1)] = p;
            
            p = buf[3*i + 1];
            buf[3*i + 1] = buf[3*(info.width - i - 1) + 1];
            buf[3*(info.width - i - 1) + 1] = p;
            
            p = buf[3*i + 2];
            buf[3*i + 2] = buf[3*(info.width - i - 1) + 2];
            buf[3*(info.width - i - 1) + 2] = p;   
        }
        
        fwrite(buf, sizeof(unsigned char), line_size, fpout);    
    }
    
    fclose(fp);  
    fclose(fpout);
    return 0;  
}

int main()
{
    //mbmp_dump("1.bmp");
    //mbmp_gen("2.bmp", 99, 120);
    //mbmp_vertical_flip("2.bmp", "2.ver.bmp");
    mbmp_horizontal_flip("1.bmp", "1.hor.bmp");
	return 0;
}
