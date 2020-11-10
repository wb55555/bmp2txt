#ifndef BMPHEAD_H_INCLUDED
#define BMPHEAD_H_INCLUDED

#include"bmp.h"

class BmpHead
{
    public:
        bool ReadBmp(char* bmpname);
        void GetFHIH(char* txtname);

        FILE* P_fp;
        int BitCount;
        int Width;
        int Height;

    private:
        BITMAPFILEHEADER FileHead;
        BITMAPINFOHEADER InfoHead;
};

#endif // BMPHEAD_H_INCLUDED
