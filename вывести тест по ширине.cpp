#include <stdio.h>
#include<iostream>
#include<cstdio>
#include<fstream>


using namespace std;

void maxLine(FILE* laba, int& str, int& maxline)
{
    do
    {
        while ((getc(laba) != '\n') && (!feof(laba)))
            str++;
        if (str > maxline) {
            maxline = str;
        }
        str = 0;
    } while (!feof(laba));
}

int main()
{
    FILE* laba;
    fopen_s(&laba, "proga.txt", "rb");
    
    int maxline = 0, str = 0;
    //шукаємо найдовший рядочок
    maxLine(laba, str, maxline);

    rewind(laba);
    FILE* file_out;

    fopen_s(&file_out, "output.txt", "w");

    int whitespace, len, startline; 
    char symbol;
    do
    {
        whitespace = len = 0;
        startline = ftell(laba);
        //шукаємо кількість пробілів
        while (((symbol = getc(laba)) != '\n') && (!feof(laba)))
        {
            if (symbol == ' ') whitespace++;
            len++;
        }

        fseek(laba, startline, SEEK_SET);

        while (((symbol = getc(laba)) != '\n') && (!feof(laba)))
        {
            if (symbol != ' ') {
                fprintf(file_out, "%c", symbol);
            }
            else
            {                
                if ((maxline - len) % whitespace) 
                {
                    str = (maxline - len) / (whitespace +2); 
                }
                else str = (maxline - len) / (whitespace +1); 
                for (int i = 0; i < str + 1; i++) {
                    fprintf(file_out, " ");
                }
            }
        }
        fprintf(file_out, "\n");

    } while (!feof(laba));

    fclose(laba);
    fclose(file_out);
    return 0;
}