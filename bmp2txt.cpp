#include<fstream>
#include<iostream>
#include<stdint.h>
#include<cmath>
#include"bmp.h"

using namespace std;

void showBmpFileHead(BITMAPFILEHEADER File);
void showBmpInfoHead(BITMAPINFOHEADER Info);
void ColorTable(int BitCount, FILE* P_fp);
void Data_148(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp);
void Data_24(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp);
bool readBmp(char *bmpName);

void showBmpFileHead(BITMAPFILEHEADER File)
{
    cout << "-----BmpFileHead-----\n"<< endl;
	cout << "bfType: " << File.bfType <<endl;
	cout << "bfSize: " << File.bfSize << endl;
	cout << "bfReserved1: " << File.bfReserved1 << endl;
	cout << "bfReserved2: " << File.bfReserved2 << endl;
	cout << "bfOffBits: " << File.bfOffBits << endl;
}

void showBmpInfoHead(BITMAPINFOHEADER Info)
{
	cout << "\n-----BmpInfoHead-----\n" << endl;
	cout << "biSize: " << Info.biSize << endl;
	cout << "biWidth: " << Info.biWidth << endl;
	cout << "biHeight: " << Info.biHeight << endl;
	cout << "biPlanes: " << Info.biPlanes << endl;
	cout << "biBitCount: " << Info.biBitCount << endl;
	cout << "biCompression: " << Info.biCompression << endl;
	cout << "biSizeImage: " << Info.biSizeImage << endl;
	cout << "biXPelsPerMeter: " << Info.biXPelsPerMeter << endl;
	cout << "biYPelsPerMeter: " << Info.biYPelsPerMeter << endl;
	cout << "biClrUsed: " << Info.biClrUsed << endl;
	cout << "biClrImportant: " << Info.biClrImportant << endl;
}

void ColorTable(int BitCount, FILE* P_fp, char* txtname)
{
        double dou_BC = BitCount;
        int CT_num = pow (2.0,dou_BC);
        unsigned char* P_inColorTable;
        P_inColorTable = new unsigned char[4 * CT_num];
        fread(P_inColorTable, 1, 4 * CT_num, P_fp);

        unsigned int* P_outR;
        unsigned int* P_outG;
        unsigned int* P_outB;
        P_outR = new unsigned int[CT_num];
        P_outG = new unsigned int[CT_num];
        P_outB = new unsigned int[CT_num];


        for (int i = 0; i < CT_num; i++)
        {
                P_outR[i] = P_inColorTable[4 * i+2];
                P_outG[i] = P_inColorTable[4 * i+1];
                P_outB[i] = P_inColorTable[4 * i];
        }

        ofstream outfile;
        outfile.open(txtname, ios::in | ios::ate);
        if(!outfile)
            cout << "error" << endl;

        outfile << "\n-----RGBQUAD-----\n" << endl;
        outfile << "colorx:\tR\tG\tB\n";
        for (int i = 0; i < CT_num; i++)
        {
            outfile << "color"<< dec << i + 1 << ":\t" << hex <<  P_outR[i] << "\t" << P_outG[i] << "\t" << P_outB[i] << endl;
        }
        delete[]P_inColorTable;
        delete[]P_outR;
        delete[]P_outG;
        delete[]P_outB;
}

void Data_148(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp, char* txtname)
{
    unsigned char* P_indata;
    int Line_Byte = (BmpWidth * BitCount / 8 + 3) / 4 * 4;
    P_indata = new unsigned char[Line_Byte * BmpHeight];
    fread(P_indata, 1, Line_Byte * BmpHeight, P_fp);
    fclose(P_fp);

    unsigned int** P2_bytedata;
	P2_bytedata = new unsigned int* [BmpHeight];
	for (int i = 0; i<BmpHeight; i++)
		P2_bytedata[i] = new unsigned int[Line_Byte];

    int ValidData_Byte = (BmpWidth * BitCount + 7) / 8;
    for (int i = 0; i<BmpHeight; i++)
    {
        for (int j = 0; j<ValidData_Byte; j++)
            P2_bytedata[BmpHeight - 1 - i][j] = P_indata[j + Line_Byte * i ];
    }

    unsigned int** P2_outdata;
    P2_outdata = new unsigned int* [BmpHeight];
    for (int i = 0; i<BmpHeight; i++)
		P2_outdata[i] = new unsigned int[BmpWidth];

    switch(BitCount)
    {
    case 1 :
        for (int i = 0; i<BmpHeight; i++)
        {
            for (int j = 0; j<BmpWidth; j++)
                P2_outdata[BmpHeight - 1 - i][j] = ( ( P2_bytedata[BmpHeight - 1 - i][j/8] >> (j%8) )&(0x00000001) );
        }
        break;
    case 4 :
        for (int i = 0; i<BmpHeight; i++)
        {
            for (int j = 0; j<BmpWidth; j++)
                P2_outdata[BmpHeight - 1 - i][j] = ( ( P2_bytedata[BmpHeight - 1 - i][j/2] >> 4*(j%2) )&(0x0f) );
        }
        break;
    case 8 :
        for (int i = 0; i<BmpHeight; i++)
        {
            for (int j = 0; j<BmpWidth; j++)
                P2_outdata[BmpHeight - 1 - i][j] =P2_bytedata[BmpHeight - 1 - i][j];
        }
        break;
    }

	ofstream outfile;
	outfile.open(txtname, ios::in | ios::ate);
	if(!outfile)
        cout << "error" << endl;

    outfile << "\n-----Data Info-----\n" << endl;
    outfile << "(W,H)\tIndex" << endl;
    for (int i = 0; i<BmpHeight; i++)
    {
        for (int j = 0; j<BmpWidth; j++)
        {
            outfile << dec << "(" << BmpHeight - i << "," << j + 1 << ")\t"
            << hex << P2_outdata[BmpHeight - 1 - i][j] << " "<< endl;
        }
        //outfile << "\n";
    }

    delete[]P_indata;
    delete[]P2_bytedata;
    delete[]P2_outdata;
}

void Data_24(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp,char* txtname)
{
    unsigned char* P_data;
    int Line_Byte = (BmpWidth * BitCount / 8 + 3) / 4 * 4;
    P_data = new unsigned char[Line_Byte * BmpHeight];
    fread(P_data, 1, Line_Byte * BmpHeight, P_fp);
    fclose(P_fp);

	unsigned int** P2_outR;
    unsigned int** P2_outG;
    unsigned int** P2_outB;

	P2_outR = new unsigned int* [BmpHeight];
	for (int i = 0; i<BmpHeight; i++)
		P2_outR[i] = new unsigned int[BmpWidth];

	P2_outG = new unsigned int* [BmpHeight];
	for (int i = 0; i<BmpHeight; i++)
		P2_outG[i] = new unsigned int[BmpWidth];

	P2_outB = new unsigned int* [BmpHeight];
	for (int i = 0; i<BmpHeight; i++)
		P2_outB[i] = new unsigned int[BmpWidth];

    for (int i = 0; i<BmpHeight; i++)
    {
        for (int j = 0; j<BmpWidth; j++)
        {
            P2_outR[BmpHeight - 1 - i][j] = P_data[j * 3 + BmpWidth * i * 3 + 2];
            P2_outG[BmpHeight - 1 - i][j] = P_data[j * 3 + BmpWidth * i * 3 + 1];
            P2_outB[BmpHeight - 1 - i][j] = P_data[j * 3 + BmpWidth * i * 3];
        }
    }

	ofstream outfile;
	outfile.open(txtname, ios::in | ios::ate);
	if(!outfile)
        cout << "error" << endl;

    outfile << "\n-----Data Info-----\n" << endl;
    outfile << "(W,H)\tR\tG\tB" << endl;
    for (int i = 0; i<BmpHeight; i++)
    {
        for (int j = 0; j<BmpWidth; j++)
        {
            outfile << dec << "(" << BmpHeight - i << "," << j  +1 <<")\t"
            << hex << P2_outR[i][j] << "\t" << P2_outG[i][j] << "\t" << P2_outB[i][j] << endl;
        }
        //outfile << "\n";
    }

    delete[]P_data;
    delete[]P2_outR;
    delete[]P2_outG;
    delete[]P2_outB;
}

bool readBmp(char* bmpname, char* txtname)
{
	FILE* P_fp = fopen(bmpname, "rb");
    if (P_fp == 0)
		return 0;

	BITMAPFILEHEADER FileHead;
	fread(&FileHead, 1, sizeof(BITMAPFILEHEADER), P_fp);
	showBmpFileHead(FileHead);

	BITMAPINFOHEADER InfoHead;
	fread(&InfoHead, 1, sizeof(BITMAPINFOHEADER), P_fp);
	showBmpInfoHead(InfoHead);

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

	if (InfoHead.biBitCount != 24)
    {
    ColorTable(InfoHead.biBitCount,  P_fp, txtname);
     Data_148(InfoHead.biWidth, InfoHead.biHeight, InfoHead.biBitCount, P_fp, txtname);
    }

    else
    {
        Data_24(InfoHead.biWidth, InfoHead.biHeight, InfoHead.biBitCount, P_fp, txtname);
    }

    return 1;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
        cout << "you should give one input and one out" << endl;
    if (argc == 3)
        readBmp(argv[1], argv[2]);
	return 0;
}
