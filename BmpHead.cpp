#include<fstream>
#include<iostream>

#include"BmpHead.h"

using namespace std;

bool BmpHead::ReadBmp(char* bmpname)
{
    P_fp = fopen(bmpname, "rb");
    if (P_fp == 0)
        return 0;

    fread(&FileHead, 1, sizeof(BITMAPFILEHEADER), P_fp);
    fread(&InfoHead, 1, sizeof(BITMAPINFOHEADER), P_fp);

    cout << "-----BmpFileHead-----\n"<< endl;
    cout << "bfType: " << FileHead.bfType <<endl;
    cout << "bfSize: " << FileHead.bfSize << endl;
    cout << "bfReserved1: " << FileHead.bfReserved1 << endl;
    cout << "bfReserved2: " << FileHead.bfReserved2 << endl;
    cout << "bfOffBits: " << FileHead.bfOffBits << endl;

    cout << "\n-----BmpInfoHead-----\n" << endl;
    cout << "biSize: " << InfoHead.biSize << endl;
    cout << "biWidth: " << InfoHead.biWidth << endl;
    cout << "biHeight: " << InfoHead.biHeight << endl;
    cout << "biPlanes: " << InfoHead.biPlanes << endl;
    cout << "biBitCount: " << InfoHead.biBitCount << endl;
    cout << "biCompression: " << InfoHead.biCompression << endl;
    cout << "biSizeImage: " << InfoHead.biSizeImage << endl;
    cout << "biXPelsPerMeter: " << InfoHead.biXPelsPerMeter << endl;
    cout << "biYPelsPerMeter: " << InfoHead.biYPelsPerMeter << endl;
    cout << "biClrUsed: " << InfoHead.biClrUsed << endl;
    cout << "biClrImportant: " << InfoHead.biClrImportant << endl;

    BitCount = InfoHead.biBitCount;
    Width = InfoHead.biWidth;
    Height = InfoHead.biHeight;

    return 1;
}

void BmpHead::GetFHIH(char* txtname)
{
    ofstream outfile;
    outfile.open(txtname, ios::in | ios::trunc);
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
    outfile << "biClrImportant: " << InfoHead.biClrImportant << endl;
}
