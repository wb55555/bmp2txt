#ifndef COLORTABLE_H_INCLUDED
#define COLORTABLE_H_INCLUDED

class ColorTable
{
    public:
        void GetData(int BitCount, FILE* P_fp, char* txtname);

    private:
        double dou_BC;
        int CT_Num;
        unsigned char* P_inColorTable;
        unsigned int* P_outR;
        unsigned int* P_outG;
        unsigned int* P_outB;
};

#endif // COLORTABLE_H_INCLUDED
