#ifndef DATA_148_H_INCLUDED
#define DATA_148_H_INCLUDED

class Data_148
{
    public:
        void GetData(int BmpWidth, int BmpHeight, int BitCount, FILE* P_fp, char* txtname);

    private :
        int Line_Byte;
        int ValidData_Byte;
        unsigned char* P_indata;
        unsigned int** P2_bytedata;
        unsigned int** P2_outdata;
};

#endif // DATA_148_H_INCLUDED
