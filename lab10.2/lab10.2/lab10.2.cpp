// lab.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>



using namespace std;
int const n = 128;


char Mass1251[n] =
{
    //!@&$^
   '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
   '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x2D', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
   '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xB3', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
   '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xA3', '\x23', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
   //от А-Я а-я   таблица символов 1251
   '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
   '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDD', '\xDD', '\xDE', '\xDF',
   '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
   '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF',

};


char koi8rMassTo1251[n] =
{
    //!@&$^
   '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
   '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x2D', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
   '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xB3', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
   '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xA3', '\x23', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
   //от А-Я а-я   таблица символов кои-8р, переставленная под 1251
   '\xE1', '\xE2', '\xF7', '\xE7', '\xE4', '\xE5', '\xF6', '\xFA', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF', '\xF0',
   '\xF2', '\xF3', '\xF4', '\xF5', '\xE6', '\xE8', '\xE3', '\xFE', '\xFB', '\xFD', '\xFF', '\xF9', '\xF8', '\xFC', '\xE0', '\xF1',
   '\xC1', '\xC2', '\xD7', '\xC7', '\xC4', '\xC5', '\xD6', '\xDA', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF', '\xD0',
   '\xD2', '\xD3', '\xD4', '\xD5', '\xC6', '\xC8', '\xC3', '\xDE', '\xDB', '\xDD', '\xDF', '\xD9', '\xD8', '\xDC', '\xC0', '\xD1'
};



int findCharIndx(char mass[], int const n, char ch) {
    for (int i = 0; i < n; i++)
    {
        if (mass[i] == ch)
            return i;
        else
            NULL;

    }
}


int main()
{

    setlocale(LC_ALL, "Russian_Russia.20866"); // koi8-r

    string vvod;
    int j = 0;
    cin >> vvod;

    cout << "START";
    for (int i = 0; i < 128; i++)
    {
        if (vvod[j] == koi8rMassTo1251[i]) {
            j++;
            cout << koi8rMassTo1251[i] << "";
            i = 0;
        }
    }
    cout << "END";
    cout << endl;






    setlocale(LC_ALL, "Russian_Russia.1251"); // cp-1251
    //setlocale(LC_ALL, "Russian_Russia.20866"); // koi8-r
    char   symb = 0;

    FILE* inFile = fopen("code_1251.txt", "rb");
    FILE* outFile = fopen("code_KOI-8R.txt", "wb");

    if (!inFile || !outFile)// проверка что оба файла открыты
    {
        //ошибка
        return -1;
    }

    int symbIndx = 0;
    int i = 0;
    while (feof(inFile) == 0)// feof() корректно* проверяет конец файла    EOF ломается на букве 'я'
    {
        symb = fgetc(inFile);

        cout << symb << " ";
        symbIndx = findCharIndx(Mass1251, n, symb);
        cout << symbIndx << "-I ";


        if (symbIndx >= 64 && symbIndx < 128 && symb != EOF) { //конец в Кириллице EOF = 'я'
            fputc(koi8rMassTo1251[symbIndx], outFile);
        }
        else {

            if (symb != EOF) fputc(symb, outFile);
            cout << "\nNE RUS\n";
        }


    }

    cout << "END";

    fclose(inFile);
    fclose(outFile);

    return 0;
}
