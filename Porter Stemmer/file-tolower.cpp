#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdio>

using namespace std;
int main()
{
FILE *fp1,*fp2;
fp1=fopen("text.txt","r");
fp2=fopen("file2.txt","w");
char ch;
while(feof(fp1)==0)
{

    ch=fgetc(fp1);
    if(!feof(fp1)){
        if(ch>=65 &&ch<=92)
        {
            ch=ch+32;
        }
        fputc(ch,fp2);
     }
}
fclose(fp1);
fclose(fp2);
return 0;
}
