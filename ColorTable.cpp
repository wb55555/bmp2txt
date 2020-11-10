#include<fstream>
#include<iostream>
#include<cmath>

#include"ColorTable.h"

using namespace std;

void ColorTable::GetData(int BitCount, FILE* P_fp, char* txtname)
{
    dou_BC = BitCount;
    CT_Num = pow (2.0,dou_BC);
    P_inColorTable = new unsigned char[4 * CT_Num];
    fread(P_inColorTable, 1, 4 * CT_Num, P_fp);

    P_outR = new unsigned int[CT_Num];
    P_outG = new unsigned int[CT_Num];
    P_outB = new unsigned int[CT_Num];

    for (int i = 0; i < CT_Num; i++)
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
    for (int i = 0; i < CT_Num; i++)
    {
        outfile << "color"<< dec << i + 1 << ":\t" << hex <<  P_outR[i] << "\t" << P_outG[i] << "\t" << P_outB[i] << endl;
    }
    delete[]P_inColorTable;
    delete[]P_outR;
    delete[]P_outG;
    delete[]P_outB;
}
