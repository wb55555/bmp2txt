#include<fstream>
#include<iostream>

#include"Data_24.h"

using namespace std;

void Data_24::GetData(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp, char* txtname)
{
    Line_Byte = (BmpWidth * BitCount / 8 + 3) / 4 * 4;
    P_data = new unsigned char[Line_Byte * BmpHeight];
    fread(P_data, 1, Line_Byte * BmpHeight, P_fp);
    fclose(P_fp);

    P2_outR = new unsigned int* [BmpHeight];
    P2_outG = new unsigned int* [BmpHeight];
    P2_outB = new unsigned int* [BmpHeight];
    for (int i = 0; i<BmpHeight; i++)
    {
        P2_outR[i] = new unsigned int[BmpWidth];
        P2_outG[i] = new unsigned int[BmpWidth];
        P2_outB[i] = new unsigned int[BmpWidth];
    }

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
