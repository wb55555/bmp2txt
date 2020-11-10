#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include <stdint.h>

typedef   struct   tagBITMAPFILEHEADER{
    uint16_t   bfType;                                //2
    uint32_t    bfSize;                                //4
    uint16_t   bfReserved1;                      //2
    uint16_t   bfReserved2;                      //2
    uint32_t    bfOffBits;                           //4
  } __attribute__((packed))BITMAPFILEHEADER;

typedef   struct   tagBITMAPINFOHEADER{
    uint32_t    biSize;                               //4
    int32_t         biWidth;                          //4
    int32_t         biHeight;                         //4
    uint16_t   biPlanes;                            //2
    uint16_t   biBitCount;                         //2
    uint32_t biCompression;                   //4
    uint32_t biSizeImage;                        //4
    int32_t   biXPelsPerMeter;                 //4
    int32_t  biYPelsPerMeter;                  //4
    uint32_t biClrUsed;                            //4
    uint32_t biClrImportant;                     //4
  } __attribute__((packed))BITMAPINFOHEADER;

typedef   struct   tagRGBQUAD{
    uint8_t   rgbBlue;                               //1
    uint8_t   rgbGreen;                            //1
    uint8_t   rgbRed;                               //1
    uint8_t   rgbReserved;                      //1
  } RGBQUAD;

#endif // BMP_H_INCLUDED
