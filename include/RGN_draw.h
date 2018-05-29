#ifndef __RGN_DRAW_H__
#define __RGN_DRAW_H__

/***
*** a util to draw face rect on ARGB1555 Canvas
*** and can use the drawInfo data to clear the draw
***/
#ifdef _cplusplus
extern .C {
#endif

#define Color2Value(color)   (0x8000|(color))
#define ClearValue            0x0000
#define GetDrawLen(width, height) ((width) <= (height))?((width) >> 2):((height) >> 2)

typedef struct {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
    unsigned short lineWidth;
    unsigned short setValue;
    unsigned short drawLen;
} drawInfo;

typedef struct {
    unsigned short *buf;       //ARGB1555 buf    
    unsigned short width;
    unsigned short height;
} RGN_Info;

#define RGN_Empty(buf, w, h)\
do{\
    memset((void *)buf, 0, 2*w*h);\
} while(0);

#define RGN_Clear(RGN, draw)\
do{\
    (draw)->setValue = ClearValue;\
    RGN_DrawRect(RGN, draw);\
} while(0);

#define RGN_DrawRect(RGN, draw)\
do{\
    RGN_Draw2HLine(RGN, draw);\
    RGN_Draw2VLine(RGN, draw);\
} while(0);

extern int RGN_Draw2HLine(RGN_Info *RGN, drawInfo *draw);
extern int RGN_Draw2VLine(RGN_Info *RGN, drawInfo *draw);

#ifdef _cplusplus
}
#endif

#endif
