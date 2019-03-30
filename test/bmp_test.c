#include <stdio.h>
#include "mbmp.h"

int main()
{
    //mbmp_dump("1.bmp");
    //mbmp_gen("2.bmp", 99, 120);
    //mbmp_vertical_flip("2.bmp", "2.ver.bmp");
    mbmp_horizontal_flip("1.bmp", "1.hor.bmp");
	return 0;
}