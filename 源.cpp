#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64encode() {
	FILE* fpout = fopen("./2.txt", "r+");
	FILE* fpin = fopen("./1.txt", "r+");
	char a[4]={};
	int flag=0;
	char text[5] = {};
	while (1)
	{
		//输入判断
		fgets(a, 4, fpin);
		if (a[0] == '\n' || a[0] == 0)
		{
			fputc('\n', fpout);
			break;
		}
		if (a[1] == '\n' || a[1] == 0)
			flag = 1;
		if (a[2] == '\n' || a[2] == 0)
			flag = 2;
		//加密
		if (flag == 1)
		{
			text[0] = table[(a[0] >> 2) % 64];
			text[1] = table[((a[0] & 3) << 4)];
			text[2] = '=';
			text[3] = '=';
			fputs(text, fpout);
			fputc('\n', fpout);
			break;
		}
		if (flag == 2)
		{
			text[0] = table[(a[0] >> 2) % 64];
			text[1] = table[((a[0] & 3) << 4) | ((a[1] & 0xF0) >> 4)];
			text[2] = table[(a[1] & 0xF) << 2];
			text[3] = '=';
			fputs(text, fpout);
			fputc('\n', fpout);
			break;
		}
		text[0] = table[(a[0] >> 2)];
		text[1] = table[((a[0] & 3) << 4) | (a[1] >> 4)];
		text[2] = table[((a[1] & 0xF) << 2) | (a[2] >> 6)];
		text[3] = table[a[2] & 0x3F];
		//输出
		fputs(text, fpout);
	}
	fclose(fpin);
	fclose(fpout);
}

void base64decode() 
{
	FILE* fpout = fopen("./2.txt", "r+");
	FILE* fpin = fopen("./1.txt", "r+");
	//求下标的首部
	char* base = strchr(table, 'A');
	while (true)
	{
		char a[5] = {};
		char text[4] = {};
		int flag = 0;
		fgets(a, 5,fpin);
		if (a[0] == '\n')
		{
			fputc('\n', fpout);
			break;
		}
		//求每一位对应的下标
		for(int i=0;i<4;i++)
		{
			if (a[2] == '=')
			{
				a[0] = strchr(table, a[0]) - table;
				a[1] = strchr(table, a[1]) - table;
				flag = 1;
				break;
			}
			if (a[3] == '=')
			{
				a[0] = strchr(table, a[0]) - base;
				a[1] = strchr(table, a[1]) - base;
				a[2] = strchr(table, a[2]) - base;
				flag = 2;
				break;
			}
			a[i] = strchr(table, a[i])- base;
		}
		//解密
		if (flag == 1)
		{
			text[0] = a[0] << 2 | a[1] >> 6;
			fputs(text, fpout);
			fputc('\n', fpout);
			break;
		}
		if (flag == 2)
		{
			text[0] = a[0] << 2 | a[1] >> 6;
			text[1] = (a[1] & 0x3F) << 4 | a[2] >> 2;
			fputs(text, fpout);
			fputc('\n', fpout);
			break;
		}
		text[0] = a[0] << 2 | a[1] >> 4;
		text[1] = (a[1] & 0x3F) << 4 | a[2] >> 2;
		text[2] = (a[2] & 3) << 6 | a[3];

		fputs(text, fpout);
	}
	fclose(fpin);
	fclose(fpout);
}

void getcode() {
	FILE* fpin = fopen("./1.txt", "r+");
	char in = 0;
	while (in != '\n')
	{
		in = getchar();
		fputc(in, fpin);
	}
	fclose(fpin);
}

void putcode() {
	FILE* fpout = fopen("./2.txt", "r+");
	char b;
	while (1)
	{
		b = fgetc(fpout);
		if (b=='\n')
			break;
		printf("%c", b);
	}
	fclose(fpout);
}

int main()
{
	int i = 0;
	printf("Please chose the mode:\n1.base64encode\n2.base64decode\n");
	scanf("%d", &i);
	getchar();
	printf("Please input you code:\n");
	getcode();
	switch (i)
	{
	case 1:
		base64encode(); break;
	case 2:
		base64decode();break;
	}
	putcode();
	
	return 0;
}
