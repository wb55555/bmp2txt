#include"BmpHead.cpp"
#include"ColorTable.cpp"
#include"Data_148.cpp"
#include"Data_24.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
        cout << "you should give one input and one out" << endl;
    else
    {
        BmpHead B;
        B.ReadBmp(argv[1]);
        B.GetFHIH(argv[2]);

        if (B.BitCount != 24)
        {
            ColorTable CT_Data;
            Data_148 D_148;
            CT_Data.GetData(B.BitCount, B.P_fp, argv[2]);
            D_148.GetData(B.Width, B.Height, B.BitCount, B.P_fp, argv[2]);
        }
        else
        {
            Data_24 D_24;
            D_24.GetData(B.Width, B.Height, B.BitCount, B.P_fp, argv[2]);
        }
    }

	return 0;
}
