#include <iostream>
#include<fstream>
#include"bmp.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
        cout << "you should give one inputname.bmp and one outputname.txt" << endl;

    else
    {
        bmp<1> bmp1;
        bmp1.load(argv[1]);
        bmp1.save_head(argv[2]);

        cout << "do you want save the datafile?(y/n)" << endl;
        char anwser1 = 0;
        cin >> anwser1;
        while ((anwser1 != 'y') && (anwser1 != 'n'))
        {
            cin.clear();
            cin.ignore();
            cout << "please input y or n" << endl;
            cin >> anwser1;
        }

        if (anwser1 == 'y')
        {
            cout << "how do  you want save the datafile? add or cover (a/c)" << endl;
            char anwser2 = 0;
            cin >> anwser2;
            while ((anwser2 != 'a') && (anwser2 != 'c'))
            {
                cin.clear();
                cin.ignore();
                cout << "please input a or c" << endl;
                cin >> anwser2;
            }

            FILE* fp;
            switch(anwser2)
            {
            case 'a':
                fp = fopen(argv[2], "a");
                break;

            case 'c':
                fp = fopen(argv[2], "w");
                break;

            default:
                break;
            }

            fprintf(fp, "-----Data Info-----\n");
            fprintf(fp, "(   v,   h) R\tG\tB\n\n");
            for(int h = 0; h < bmp1.get_height(); h++)
            {
                for(int v = 0; v < bmp1.get_width(); v++)
                {
                    int rdata = bmp1.get_r(v, h);
                    int gdata = bmp1.get_g(v, h);
                    int bdata = bmp1.get_b(v, h);

                    fprintf(fp, "(%4d,%4d) %02x\t%02x\t%02x\n", v + 1, h + 1, rdata, gdata, bdata);
                }
            }

            fclose(fp);
        }

        else
            return 0;
    }
    return 0;
}
