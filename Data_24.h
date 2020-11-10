#ifndef DATA_24_H_INCLUDED
#define DATA_24_H_INCLUDED

class Data_24
{
    public:
        void GetData(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp, char* txtname);

    private:
        int Line_Byte;
        unsigned char* P_data;
        unsigned int** P2_outR;
        unsigned int** P2_outG;
        unsigned int** P2_outB;
};

#endif // DATA_24_H_INCLUDED
