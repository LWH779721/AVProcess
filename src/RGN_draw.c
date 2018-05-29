#include <stdio.h>
#include "RGN_draw.h"

int RGN_Draw2VLine(RGN_Info *RGN, drawInfo *draw)
{
    int i, line;
    int start, end;
    int index1, index2;

    index1 = draw->x;
    index2 = draw->x + draw->width - draw->lineWidth;

    start = draw->y + draw->lineWidth;
    end = draw->y + draw->drawLen;
	for (i = start; i <= end; i++)
	{
		for (line = 0; line < draw->lineWidth; line++) 
        {
			RGN->buf[RGN->width * i + index1 + line] = 
            RGN->buf[RGN->width * i + index2 + line] = draw->setValue;
		}
	}

    start = draw->y + draw->height - draw->drawLen;
    end = draw->y + draw->height - draw->lineWidth;
    for (i = start; i <= end; i++)
	{
		for (line = 0; line < draw->lineWidth; line++) 
        {
			RGN->buf[RGN->width * i + index1 + line] = 
            RGN->buf[RGN->width * i + index2 + line] = draw->setValue;
		}
	} 
    
    return 0;
}

int RGN_Draw2HLine(RGN_Info *RGN, drawInfo *draw)
{
    int i, line;
    int start, end;
    int index1, index2;

    index1 = draw->y;
    index2 = draw->y + draw->height - draw->lineWidth;

    start = draw->x;
    end = draw->x + draw->drawLen;
	for (i = start; i <= end; i++)
	{
		for(line = 0; line < draw->lineWidth; line++) 
        {
			RGN->buf[RGN->width * (index1 + line) + i] = 
            RGN->buf[RGN->width * (index2 + line) + i] = draw->setValue;
		}
	}

    start = draw->x + draw->width - draw->drawLen;
    end = draw->x + draw->width;
    for (i = start; i <= end ; i++)
	{
		for(line = 0; line < draw->lineWidth; line++) 
        {
			RGN->buf[RGN->width * (index1 + line) + i] = 
            RGN->buf[RGN->width * (index2 + line) + i] = draw->setValue;
		}
	} 
    
    return 0;
}
