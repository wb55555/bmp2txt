#include<fstream>
#include<iostream>

#include"Data_148.h"

using namespace std;

void Data_148::GetData(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp, char* txtname)
{
    Line_Byte = (BmpWidth * BitCount / 8 + 3) / 4 * 4;
    P_indata = new unsigned char[Line_Byte * BmpHeight];
    fread(P_indata, 1, Line_Byte * BmpHeight, P_fp);
    fclose(P_fp);

    P2_bytedata = new unsigned int* [BmpHeight];
    for (int i = 0; i<BmpHeight; i++)
        P2_bytedata[i] = new unsigned int[Line_Byte];

    ValidData_Byte = (BmpWidth * BitCount + 7) / 8;
    for (int i = 0; i<BmpHeight; i++)
    {
        for (int j = 0; j<ValidData_Byte; j++)
            P2_bytedata[BmpHeight - 1 - i][j] = P_indata[j + Line_Byte * i ];
    }

    P2_outdata = new unsigned int* [BmpHeight];
    for (int i = 0; i<BmpHeight; i++)
        P2_outdata[i] = new unsigned int[BmpWidth];

    switch(BitCount)
    {
    case 1 :
        for (int i = 0; i<BmpHeight; i++)
        {
            for (int j = 0; j<BmpWidth; j++)
                P2_outdata[BmpHeight - 1 - i][j] = ( ( P2_bytedata[BmpHeight - 1 - i][j/8] >> (j%8) )&(0x1) );
        }
        break;

    case 4 :
        for (int i = 0; i<BmpHeight; i++)
        {
            for (int j = 0; j<BmpWidth; j++)
                P2_outdata[BmpHeight - 1 - i][j] = ( ( P2_bytedata[BmpHeight - 1 - i][j/2] >> 4*(j%2) )&(0xf) );
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
