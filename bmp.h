#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include<iostream>
#include<fstream>
#include <stdint.h>

using namespace std;

class BITMAPFILEHEADER{
    public:

        uint16_t   bfType;                                //2
        uint32_t    bfSize;                                //4
        uint16_t   bfReserved1;                      //2
        uint16_t   bfReserved2;                      //2
        uint32_t    bfOffBits;                           //4
  } __attribute__((packed));

class BITMAPINFOHEADER{
    public:

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
  };

template<int BIT>
class bmp
{
    public:

        int load(char* filename)
        {
            load_head(filename);
            load_data(filename);
        }
        int load_head(char* filename);
        int load_data(char* filename);
        int save_head(char* txtname);
        int save_data(char* txtname);
        int get_width();
        int get_height();
        int get_r(int v, int h);
        int get_g(int v, int h);
        int get_b(int v, int h);
        ~bmp();

    private:

        FILE* P_fp;
        BITMAPFILEHEADER FileHead;
        BITMAPINFOHEADER InfoHead;
        int bitcount;
        int width;
        int height;
        unsigned int** rbuf;
        unsigned int** gbuf;
        unsigned int** bbuf;
};

template<int BIT>
int bmp< BIT>::load_head(char* filename)
{
    P_fp = fopen(filename, "rb");
    if (P_fp == 0)
        cout << "no file input" << endl;

    //get datas of header
    fread(&FileHead, 1, 14, P_fp);
    fread(&InfoHead, 1, 40, P_fp);

    bitcount = InfoHead.biBitCount;
    width = InfoHead.biWidth;
    height = InfoHead.biHeight;

    return 0;
}

template<int BIT>
int bmp< BIT>::load_data(char* filename)
{
    //initialize the rgb data array
    rbuf = new unsigned int* [width];
    gbuf = new unsigned int* [width];
    bbuf = new unsigned int* [width];
    for (int i= 0; i < width; i++)
    {
        rbuf[i] = new unsigned int[height];
        gbuf[i] = new unsigned int[height];
        bbuf[i] = new unsigned int[height];
    }
    //bmpfile will zeroize to be 4 bytes' integral multiple
    int width_byte = (width * bitcount / 8 + 3) / 4 * 4;
    unsigned char* P_indata = new unsigned char[width_byte * height];


    if (bitcount != 24)
    {
        int ct_num = 1;
        for (int i = 0; i < bitcount; i++)
            ct_num *= 2;

        unsigned char* P_colortable = new unsigned char[4 * ct_num];
        fread(P_colortable, 1, 4 * ct_num, P_fp);

        unsigned int* P_ctr = new unsigned int[ct_num];
        unsigned int* P_ctg = new unsigned int[ct_num];
        unsigned int* P_ctb = new unsigned int[ct_num];
        for (int i = 0; i < ct_num; i++)
        {
            P_ctr[i] = P_colortable[4 * i+2];
            P_ctg[i] = P_colortable[4 * i+1];
            P_ctb[i] = P_colortable[4 * i];
        }

        //load datas
        fread(P_indata, 1, width_byte * height, P_fp);
        fclose(P_fp);
        //valid data bytes
        int valid_byte = (width * bitcount + 7) / 8;
        unsigned int** P2_valid_data = new unsigned int* [valid_byte];
        for (int i = 0; i < valid_byte; i++)
            P2_valid_data[i] = new unsigned int[height];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < valid_byte; j++)
                P2_valid_data[j][height - 1 - i] = P_indata[j + width_byte * i ];
        }

        unsigned int** P2_index = new unsigned int* [width];
        for (int i = 0; i < width; i++)
            P2_index[i] = new unsigned int[height];

        switch(bitcount)
        {
        case 1 :    //bitcount = 1, 1byte has 8 pixel's indexs
            for (int i = 0; i<height; i++)
            {
                for (int j = 0; j < width; j++)
                   P2_index[j][i] = ( ( P2_valid_data[j/8][i] >> (j%8) )&(0x1) );
            }
            break;

        case 4 :    //bitcount = 4, 1 byte has 2 pixel's indexs
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                    P2_index[j][i] = ( ( P2_valid_data[j/2][i] >> 4*(j%2) )&(0xf) );
            }
            break;

        case 8 :    //bitcount = 8, 1 byte has 1 pixel's index
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                    P2_index[j][i] = P2_valid_data[j][i];
            }
            break;
        }
        //get rgb datas by indexs
        for (int i= 0; i < height; i++)
        {
            for (int j= 0; j < width; j++)
            {
                rbuf[j][height - 1 - i] = P_ctr[ P2_index[j][i] ];
                gbuf[j][height - 1 - i] = P_ctg[ P2_index[j][i] ];
                bbuf[j][height - 1 - i] = P_ctb[ P2_index[j][i] ];
            }
        }

        delete[]P_colortable;
        delete[]P_ctr;
        delete[]P_ctg;
        delete[]P_ctb;
        delete[]P2_valid_data;
        delete[]P2_index;
    }

    else if (bitcount == 24)
    {
        //load datas
        fread(P_indata, 1, width_byte * height, P_fp);
        fclose(P_fp);

        rbuf = new unsigned int* [height];
        gbuf = new unsigned int* [height];
        bbuf = new unsigned int* [height];
        for (int i = 0; i<height; i++)
        {
            rbuf[i] = new unsigned int[width];
            gbuf[i] = new unsigned int[width];
            bbuf[i] = new unsigned int[width];
        }
        //get rgb datas
        for (int i = 0; i<height; i++)
        {
            for (int j = 0; j<width; j++)
            {
                rbuf[j][height - 1 - i] = P_indata[j * 3 + width * i * 3 + 2];
                gbuf[j][height - 1 - i] = P_indata[j * 3 + width * i * 3 + 1];
                bbuf[j][height - 1 - i] = P_indata[j * 3 + width * i * 3];
            }
        }
    }

    else
        cout << "this file is not bmpfile";

    delete[]P_indata;
    fclose(P_fp);
    return 0;
}

template<int BIT>
int bmp< BIT>::save_head(char* txtname)
{
    ofstream outfile;

        outfile.open(txtname, ios::out | ios::trunc);
        if(!outfile)
            cout << "error" << endl;

        outfile << "-----BmpfileHead-----\n"<< endl;
        outfile << "bfType: " << FileHead.bfType <<endl;
        outfile << "bfSize: " << FileHead.bfSize << endl;
        outfile << "bfReserved1: " << FileHead.bfReserved1 << endl;
        outfile << "bfReserved2: " << FileHead.bfReserved2 << endl;
        outfile << "bfOffBits: " << FileHead.bfOffBits << endl;

        outfile << "\n-----BmpInfoHead-----\n" << endl;
        outfile << "biSize: " << InfoHead.biSize << endl;
        outfile << "biWidth: " << InfoHead.biWidth << endl;
        outfile << "biHeight: " << InfoHead.biHeight << endl;
        outfile << "biPlanes: " << InfoHead.biPlanes << endl;
        outfile << "biBitCount: " << InfoHead.biBitCount << endl;
        outfile << "biCompression: " << InfoHead.biCompression << endl;
        outfile << "biSizeImage: " << InfoHead.biSizeImage << endl;
        outfile << "biXPelsPerMeter: " << InfoHead.biXPelsPerMeter << endl;
        outfile << "biYPelsPerMeter: " << InfoHead.biYPelsPerMeter << endl;
        outfile << "biClrUsed: " << InfoHead.biClrUsed << endl;
        outfile << "biClrImportant: " << InfoHead.biClrImportant << endl << endl;

        outfile.close();



        return 0;
}

template<int BIT>
int bmp< BIT>::save_data(char* txtname)
{
    ofstream outfile;
    outfile.open(txtname, ios::in | ios::ate);

    if(!outfile)
        cout << "error" << endl;

    outfile << "\n(v , h)\tR\tG\tB" << endl;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                outfile << dec << "( " << j + 1 << " , " << i + 1 << " )\t"<< hex << rbuf[j][i] << "\t" << gbuf[j][i] << "\t" << bbuf[j][i] << endl;
            }

    outfile.close();
    return 0;
}

template<int BIT>
int bmp< BIT>::get_width()
{
    return width;
}

template<int BIT>
int bmp< BIT>::get_height()
{
    return height;
}

template<int BIT>
int bmp< BIT>::get_r(int v, int h)
{
    return rbuf[v][h];
}

template<int BIT>
int bmp< BIT>::get_g(int v, int h)
{
    return gbuf[v][h];
}

template<int BIT>
int bmp< BIT>::get_b(int v, int h)
{
    return bbuf[v][h];
}

template<int BIT>
bmp< BIT>::~bmp()
{
    delete[]rbuf;
    delete[]gbuf;
    delete[]bbuf;
}

#endif // BMP_H_INCLUDED
