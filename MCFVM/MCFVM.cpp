#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<io.h>
#include<sys/stat.h>
#include<math.h>
#include"bmp.h"
#include <direct.h>

//#include<winsock2.h>

FILE* fsp;

struct libtag {
	char name[50];
	char replace[50];
	struct rgbtag {
		BYTE r;
		BYTE g;
		BYTE b;
	}rgb;
};

libtag* libbush;


int liblen;

int readpcess() {
	int tmp=0;
	FILE* fp = fopen("process.tmp", "rb");
	if (fp == NULL) {
		return 0;
	}
	fscanf(fp, "%u", &tmp);
	fclose(fp);
	return tmp;
}

void writepcess(int now) {
	FILE* fp = fopen("process.tmp", "wb");
	fprintf(fp,"%d",now);
	fclose(fp);
}





struct cfg {
	struct langt {
		char lang[6];
		char path[50];
	} lang;
	struct post {
		int x;
		int y;
		int z;
	} pos;
	struct xyt {
		int h;
		int w;
	}xy;
	struct libt {
		int libver;
		char libpath;
	} libn;
	struct filet {
		char path[80];
		char name[40] = "NULL";
	} file;
	struct dllt {
		char funcname[10] = "vp";
	} dll;
	int dir;
	char workpath[100];
	int importf;
	bool mem;
	int updaterver;
	bool enableupdate;
	struct libcfgtag {
		char path[50];
		char name[50];
		char auther[50];
		char version[50];
		char gversion[50];
		BYTE libfont;
		int libsize;
	}lib;
};

int scanfile(cfg cfgi, bool p);
 
void start(cfg cfgi) {
	FILE* fp; char n[200];

	sprintf(n, "%s\\functions\\start\\add.mcfunction\0", cfgi.workpath);
	fp = fopen(n, "w+");
	fprintf(fp, "scoreboard players add @p Frame 1\nscoreboard players add @p Frame_min 1\n");
	fclose(fp);
	memset(n, 0, 200);
	sprintf(n, "%s\\functions\\start\\ready.mcfunction\0", cfgi.workpath);
	fp = fopen(n, "w+");
	fprintf(fp, "scoreboard objectives add Frame dummy Frame\n");
	fprintf(fp, "scoreboard objectives add Frame_min dummy Frame\n");
	fprintf(fp, "scoreboard players set @p Frame -2\n");
	fprintf(fp, "scoreboard players set @p Frame_min -2\n");
	fprintf(fp, "kill @e[type=armor_stand,name=tp]\n");
	fprintf(fp, "summon minecraft:armor_stand ~-1 ~-0.5 ~ {Invisible:0,CustomName:tp}\n");
	fprintf(fp, "gamerule doDaylightCycle false\n");
	fprintf(fp, "gamerule doMobSpawning false\n");
	fprintf(fp, "gamerule doWeatherCycle false\n");
	fprintf(fp, "time set day\n");
	fprintf(fp, "kill @e[type=!palyer]\n");
	fprintf(fp, "kill @e[type=item]\n");
	fprintf(fp, "gamerule maxCommandChainLength 10000000\n");
	fclose(fp);
}

int dll(cfg cfgi)
{
	FILE* fip;
	int a;
	long int j = 0; m = 0; char n[200] = "";
	a = mkdir("functions");
	a = mkdir("functions\\start");
	start(cfgi);
	sprintf(n, "functions\\%s\0", cfgi.dll.funcname);
	a = mkdir(n);



	m = scanfile(cfgi, FALSE);


	sprintf(n, "%s\\functions\\start\\video.mcfunction\0", cfgi.workpath);

	fip = fopen(n, "w");

	for (j = 0; j < m; j++) {
		fprintf(fip, "execute @e[score_Frame=%d,score_Frame_min=%d] ~ ~ ~ execute @e[name=tp] ~-108 ~+5 ~+54 function %s:video%04d\n", j, j, cfgi.dll.funcname, j);
	}

	fclose(fip);
	return m;


}

int scanfile(cfg cfgi, bool p) {
	char n[100] = ""; int i = 0; bool x = TRUE; struct stat buf;
	for (i = 0; x == TRUE; i++) {
		\
			sprintf(n, "%s\\BMP\\%s%04d.bmp\0", cfgi.workpath, cfgi.file.name, i);
		if (stat(n, &buf) == -1) {
			x = FALSE;
		}
		memset(n, 0, sizeof(n) / sizeof(char));
	}
	if (p == TRUE) {
		printf("自动搜索完毕\n一共%d帧", i);
	}
	Sleep(500);
	return i-1;
}

int prline(int jd) {
	jd = jd / 5;
	printf("[");
	for (int i = 0; i < jd; i++) {
		printf("=");
	}
	printf(">");
	for (; jd < 19; jd++) {
		printf("-");
	}
	printf("]  ");
	return 0;
}

libtag *libreader(cfg cfgi){
	FILE* libp; char full[50] = ""; libtag *libtmp=(libtag*)calloc(256,sizeof(libtag*));
	int i, j = 0, c = 0, m = 0, n = 0; int np = 0; char chtmp[50]=""; bool replace,in;
	char tmp[2000] = ""; int rgb = 0, chp = 0, x = 0;
	sprintf(full,"%s\\lib\\%s\0",cfgi.workpath,cfgi.lib.name);
	//tmp = (char*)malloc(2000); 
	char tmpc;
	libp = fopen(full,"r");
	i = 0;
	tmpc = fgetc(libp);
	while (tmpc != EOF) {
		//memcpy(&tmp[i], &tmpc, 1);
		tmp[i] = tmpc;
		tmpc = fgetc(libp);
		i++;
	}


	if (tmp[0] == '[' && tmp[4] == ']' && tmp[5] == '\n') {
		np = 6;
	}
	else {
		for (j = 0; j < 10; j++) {
			printf("%d", tmp[j]);
		}
		printf("\nlibreader error:head form error\n"); system("pause");
		return 0;
	}


	for (;np<i; np++) {
		switch (tmp[np])
		{
		case '\'':
			if (in) {
				strcpy(libtmp[x].name, chtmp);
				memset(chtmp, 0, sizeof(chtmp)); chp = 0;
				in = FALSE;
				continue;
			}
			else {
				memset(chtmp, 0, sizeof(chtmp));
				in = TRUE;
				continue;
			}
			[[fallthrough]];
		case '=':
			memset(chtmp, 0, sizeof(chtmp)); rgb = 1; chp = 0;
			continue;
		case ',':
		case ';':
			switch (rgb)
			{
			case 1:
				libtmp[x].rgb.r = atoi(chtmp); rgb++;
				memset(chtmp, 0, sizeof(chtmp)); chp = 0;
				continue;
			case 2:
				libtmp[x].rgb.g = atoi(chtmp); rgb++;
				memset(chtmp, 0, sizeof(chtmp)); chp = 0;
				continue;
			case 3:
				libtmp[x].rgb.b = atoi(chtmp); rgb = 0;
				memset(chtmp, 0, sizeof(chtmp)); chp = 0;
				continue;
			}
		case '\"':
			if (replace) {
				strcpy(libtmp[x].replace, chtmp);
				memset(chtmp, 0, sizeof(chtmp)); chp = 0;
				replace = FALSE;
				continue;
			}
			else {
				memset(chtmp, 0, sizeof(chtmp));
				replace = TRUE;
				continue;
			}
			[[fallthrough]];
		case '\n':
			x++;
			memset(chtmp, 0, sizeof(chtmp));
			rgb = 0;
			replace = FALSE;
			in = FALSE;
			chp = 0;
			break;
		default:
			chtmp[chp] = tmp[np];
			chp++;
			continue;
		}
	}
	liblen = x;
	return libtmp;
}


BYTE **collectmemforflag(int h,int w) {
	BYTE** tmp;
	tmp = (BYTE**)malloc(sizeof(BYTE*) * h);
	for (int i = 0; i < h; i++) {
		tmp[i] = (BYTE*)malloc(sizeof(BYTE) * w);
	}
	return tmp;
}








int main(int avge, char* argv[]) {

	FILE* config;
	cfg cfgi = {}; int enh = 360, enw = 540;
	int itemp[6]; int c = 0, ci = 0, l = 0, t = 0; cfgi.pos.x = 10, cfgi.pos.y = 10, cfgi.pos.z = 10; int ch[10]; char chc;
	int xi = 0, yi = 0, zi = 0; cfgi.dir = 0; cfgi.mem = 1; double timec, speed, timeleave;
	BYTE brgb[100][3]; int value = 0, flag; int jd, a = 0;
	clock_t start = 0, finish = 0; libtag* lib=(libtag*)calloc(256,sizeof(libbush));
	int flame = 0;
	int flamem = 0;
	char fonname[200];
	char filename[80];
	cfgi.importf = 72;
	//for (int a = 0; a < 255; a++) {
	//	libbush = (libtag*)malloc(sizeof(libtag*));
	//}
	system("mode con cols=60 lines=15");
	if (getcwd(cfgi.workpath, 100)) {

	}

	if (1) {
		ch[0] = 1;
		while (ch[0] == 1) {
			ch[0] = 0;
			system("cls");
			if (1) {
				ch[9] = scanfile(cfgi, FALSE);
				enh = cfgi.xy.h;
				enw = cfgi.xy.w;
				printf("-----------------------------------------------------------\n");
				printf("|               MCFVM0.4.5b1     by yuqijun               |\n");
				printf("|           0   更新记录                                  |\n");
				printf("|           1   函数设置    当前函数名:%-15s    |\n", cfgi.dll.funcname);
				printf("|           2   坐标设置    当前x=%-4d y=%-4d z=%-4d      |\n", cfgi.pos.x, cfgi.pos.y, cfgi.pos.z);
				printf("|           3   方向设置    当前选择  %-3d                 |\n", cfgi.dir);
				printf("|           4   画面设置    当前高度%-4d 宽度%-4d         |\n", enh, enw);
				printf("|           5   文件设置    已扫描文件数:%-4d             |\n", ch[9]);
				printf("|           6   关键帧设置  当前每隔%02d帧一个关键帧        |\n", cfgi.importf);
				printf("|           7   加载配置                                  |\n");
				printf("|           8   保存配置                                  |\n");
				printf("|           9   加载方块                                  |\n");
				printf("|           10  开始生成                                  |\n");
				printf("-----------------------------------------------------------\n");
			}
			scanf_s("%d", &ch[1]);
			switch (ch[1]) {
			case 0:
				system("cls");
				printf("更新UI\n更新自动扫描\n0.4.4\n\n");
				printf("更新函数设置\n允许外加载library\n中断继续\n0.4.5\n\n");
				chc=getchar();
				chc=getchar();
				ch[0] = 1;
				break;
			case 1:
				system("cls");
				printf("-------------------------------\n");
				printf("|           函数设置          |\n");
				printf("|   当前函数名:%-10s     |\n", cfgi.dll.funcname);
				printf("-------------------------------\n");
				//scanf_s("%d", &ch[8]);
				//switch (ch[8]) {
				std::cin >> cfgi.dll.funcname;
				//}
				ch[0] = 1;
				break;
			case 2:
				if (1) {
					system("cls");
					printf("-------------------------------\n");
					printf("|           坐标设置          |\n");
					printf("|  当前x=%-4d y=%-4d z=%-4d   |\n", cfgi.pos.x, cfgi.pos.y, cfgi.pos.z);
					printf("|       0      默认           |\n");
					printf("|       1      自定义         |\n");
					printf("-------------------------------\n");
					scanf_s("%d", &ch[2]);
					if (ch[2] == 0) {
						cfgi.pos.x = 10; cfgi.pos.y = 10; cfgi.pos.z = 10;
					}
					if (ch[2] == 1) {
						printf("坐标x=");
						scanf_s("%d", &cfgi.pos.x);
						printf("坐标y=");
						scanf_s("%d", &cfgi.pos.y);
						printf("坐标z=");
						scanf_s("%d", &cfgi.pos.z);
					}
				}
				ch[0] = 1;
				break;
			case 3:
				if (1) {
					system("cls");
					printf("-------------------------------\n");
					printf("|           方向设置          |\n");
					printf("|      当前选择  %d            |\n", cfgi.dir);
					printf("|       0      竖立z+         |\n");
					printf("|       1      竖立x+         |\n");
					printf("|       2      平铺z+         |\n");
					printf("|       3      平铺x+         |\n");
					printf("-------------------------------\n");
					scanf_s("%d", &cfgi.dir);
					if (cfgi.dir > 3) {
						cfgi.dir = 0;
					}
				}
				ch[0] = 1;
				break;
			case 4:
				if (1) {
					system("cls");
					printf("-------------------------------\n");
					printf("|           画面设置          |\n");
					printf("|   最大高度%-4d 宽度%-4d     |\n", enh, enw);
					printf("|       0      自动调整       |\n");
					printf("|       1      手动调整       |\n");
					printf("-------------------------------\n");
					scanf_s("%d", &ch[3]);
					if (ch[3] == 0) {
						enh = 360; enw = 540;
					}
					if (ch[3] == 1) {
						printf("最大高度=");
						scanf_s("%d", &enh);
						printf("最大宽度=");
						scanf_s("%d", &enw);
					}
					cfgi.xy.h = enh;
					cfgi.xy.w = enw;
				}
				if (ch[3] == 0) {
					m = 0;
				}
				ch[0] = 1;
				break;
			case 5:
				if (1) {
					system("cls");
					printf("-------------------------------\n");
					printf("|           文件设置          |\n");
					printf("-------------------------------\n");
					printf("文件名:%sxxxx.bmp\n更改为", cfgi.file.name);
					std::cin >> cfgi.file.name;
				}
				ch[0] = 1;
				break;
			case 6:
				if (1) {
					system("cls");
					printf("-------------------------------\n");
					printf("|         关键帧设置          |\n");
					printf("|   当前每隔%02d帧一个关键帧    |\n", cfgi.importf);
					printf("-------------------------------\n");
					std::cin >> cfgi.importf;
				}
				ch[0] = 1;
				break;
			case 7:
				config = fopen("config.dat", "r");
				fread(&cfgi, sizeof(cfgi), 1, config);
				system("cls");
				fclose(config);
				printf("加载成功");
				Sleep(200);
				ch[0] = 1;
				break;
			case 8:
				config = fopen("config.dat", "w+");
				fwrite(&cfgi, sizeof(cfgi), 1, config);
				system("cls");
				fclose(config);
				printf("保存成功");
				Sleep(200);
				ch[0] = 1;
				break;
			case 9:
				sprintf(cfgi.lib.name, "lib.ini");
				lib = libreader(cfgi);
				//FILE *libop = fopen("readlib.ini", "w+");
				//fprintf(libop, "[lib]\n");
				//for (int sdf = 0; sdf < 8; sdf++) {
					//printf("\'%s\'=%d,%d,%d,\"%s\"\n", lib[sdf].name, lib[sdf].rgb.r, lib[sdf].rgb.g, lib[sdf].rgb.b, lib[sdf].replace);
					//fprintf(libop,"\'%s\'=%d,%d,%d,\"%s\"\n",lib[sdf].name, lib[sdf].rgb.r, lib[sdf].rgb.g, lib[sdf].rgb.b, lib[sdf].replace);
				//}
				//system("pause");
				//fclose(libop);
				ch[0] = 1;
				c = 2;
			}
		}
		system("cls");
		if (l == 0) {
			printf("版本 0.4.5 beta 1\n游戏版本1.12.2\n感谢您使用我的程序\n联系我 https://space.bilibili.com/295235386 \n\n");
			//printf("版本 0.4.4 release\n感谢您使用我的程序\n联系我 https://space.bilibili.com/295235386 \n\n");
		}
		Sleep(300);
	}
	//UI界面

	//下面是方块颜色赋值 r				g				b
	/*
	if (c == 1) {
		brgb[0][0] = 73; brgb[0][1] = 73; brgb[0][2] = 73;
		brgb[1][0] = 240; brgb[1][1] = 238; brgb[1][2] = 235;
		brgb[2][0] = 174; brgb[2][1] = 159; brgb[2][2] = 118;
		brgb[3][0] = 153; brgb[3][1] = 80; brgb[3][2] = 43;
		brgb[4][0] = 44; brgb[4][1] = 46; brgb[4][2] = 143;
		brgb[5][0] = 26; brgb[5][1] = 174; brgb[5][2] = 53;
		brgb[6][0] = 211; brgb[6][1] = 150; brgb[6][2] = 39;
		brgb[7][0] = 77; brgb[7][1] = 98; brgb[7][2] = 32;
		brgb[8][0] = 193; brgb[8][1] = 193; brgb[8][2] = 193;
		brgb[9][0] = 44; brgb[9][1] = 105; brgb[9][2] = 207;
		brgb[10][0] = 101; brgb[10][1] = 175; brgb[10][2] = 24;
		brgb[11][0] = 177; brgb[11][1] = 56; brgb[11][2] = 167;
		brgb[12][0] = 232; brgb[12][1] = 104; brgb[12][2] = 7;
		brgb[13][0] = 218; brgb[13][1] = 223; brgb[13][2] = 224;
		brgb[14][0] = 203; brgb[14][1] = 100; brgb[14][2] = 142;
		brgb[15][0] = 149; brgb[15][1] = 34; brgb[15][2] = 33;
		brgb[16][0] = 245; brgb[16][1] = 185; brgb[16][2] = 28;
		brgb[17][0] = 242; brgb[17][1] = 176; brgb[17][2] = 22;
		brgb[18][0] = 185; brgb[18][1] = 133; brgb[18][2] = 36;
		brgb[19][0] = 255; brgb[19][1] = 255; brgb[19][2] = 255;
		brgb[20][0] = 142; brgb[20][1] = 61; brgb[20][2] = 47;
		brgb[21][0] = 143; brgb[21][1] = 33; brgb[21][2] = 33;
		brgb[22][0] = 224; brgb[22][1] = 96; brgb[22][2] = 0;
		brgb[23][0] = 229; brgb[23][1] = 117; brgb[23][2] = 155;
		brgb[24][0] = 160; brgb[24][1] = 78; brgb[24][2] = 79;
		brgb[25][0] = 150; brgb[25][1] = 88; brgb[25][2] = 55;
		brgb[26][0] = 209; brgb[26][1] = 177; brgb[26][2] = 161;
		brgb[27][0] = 221; brgb[27][1] = 217; brgb[27][2] = 203;
		brgb[28][0] = 12; brgb[28][1] = 14; brgb[28][2] = 18;
		brgb[29][0] = 47; brgb[29][1] = 50; brgb[29][2] = 148;
		brgb[30][0] = 222; brgb[30][1] = 210; brgb[30][2] = 163;

	}*/
	//1.14.4

	if (c == 0) {
		brgb[0][0] = 158; brgb[0][1] = 164; brgb[0][2] = 176;
		brgb[1][0] = 240; brgb[1][1] = 238; brgb[1][2] = 235;
		brgb[2][0] = 174; brgb[2][1] = 159; brgb[2][2] = 118;
		brgb[3][0] = 153; brgb[3][1] = 80; brgb[3][2] = 43;
		brgb[4][0] = 44; brgb[4][1] = 46; brgb[4][2] = 143;
		brgb[5][0] = 95; brgb[5][1] = 233; brgb[5][2] = 133;
		brgb[6][0] = 235; brgb[6][1] = 204; brgb[6][2] = 57;
		brgb[7][0] = 53; brgb[7][1] = 71; brgb[7][2] = 27;
		brgb[8][0] = 193; brgb[8][1] = 193; brgb[8][2] = 193;
		brgb[9][0] = 44; brgb[9][1] = 105; brgb[9][2] = 207;
		brgb[10][0] = 101; brgb[10][1] = 175; brgb[10][2] = 24;
		brgb[11][0] = 177; brgb[11][1] = 56; brgb[11][2] = 167;
		brgb[12][0] = 232; brgb[12][1] = 104; brgb[12][2] = 7;
		brgb[13][0] = 218; brgb[13][1] = 223; brgb[13][2] = 224;
		brgb[14][0] = 203; brgb[14][1] = 100; brgb[14][2] = 142;
		brgb[15][0] = 149; brgb[15][1] = 34; brgb[15][2] = 33;
		brgb[16][0] = 245; brgb[16][1] = 185; brgb[16][2] = 28;
		brgb[17][0] = 242; brgb[17][1] = 176; brgb[17][2] = 22;
		brgb[18][0] = 127; brgb[18][1] = 127; brgb[18][2] = 127;
		brgb[19][0] = 255; brgb[19][1] = 255; brgb[19][2] = 255;
		brgb[20][0] = 227; brgb[20][1] = 38; brgb[20][2] = 12;
		brgb[21][0] = 143; brgb[21][1] = 33; brgb[21][2] = 33;
		brgb[22][0] = 224; brgb[22][1] = 96; brgb[22][2] = 0;
		brgb[23][0] = 108; brgb[23][1] = 35; brgb[23][2] = 162;
		brgb[24][0] = 160; brgb[24][1] = 78; brgb[24][2] = 79;
		brgb[25][0] = 142; brgb[25][1] = 60; brgb[25][2] = 46;
		brgb[26][0] = 209; brgb[26][1] = 177; brgb[26][2] = 161;
		brgb[27][0] = 221; brgb[27][1] = 217; brgb[27][2] = 203;
		brgb[28][0] = 12; brgb[28][1] = 14; brgb[28][2] = 18;
		brgb[29][0] = 47; brgb[29][1] = 50; brgb[29][2] = 148;
		brgb[30][0] = 222; brgb[30][1] = 210; brgb[30][2] = 163;
		brgb[31][0] = 132; brgb[31][1] = 132; brgb[31][2] = 123;
		brgb[32][0] = 57; brgb[32][1] = 61; brgb[32][2] = 65;
		brgb[33][0] = 96; brgb[33][1] = 60; brgb[33][2] = 32;
		brgb[34][0] = 104; brgb[34][1] = 78; brgb[34][2] = 47;
		brgb[35][0] = 255; brgb[35][1] = 255; brgb[35][2] = 255;
		if (cfgi.dir > 1) {
			brgb[1][0] = 198; brgb[1][1] = 176; brgb[1][2] = 117;
		}
	}

	if (c == 2) {
		for (int i = 0; i < liblen; i++) {
			brgb[i][0] = lib[i].rgb.r;
			brgb[i][1] = lib[i].rgb.g;
			brgb[i][2] = lib[i].rgb.b;
		}
	}

	char** blockname=(char**)calloc(50,liblen);
	for (int i = 0; i < liblen; i++) {
		blockname[i] = lib->name;
	}

	
	//1.12.2
	BYTE** oflag = collectmemforflag(enh, enw);
	flamem = dll(cfgi);
	start = clock();
	system("CLS");







	for (flame = readpcess(); flame < flamem; flame++) {

		timec = (finish - start) / CLOCKS_PER_SEC;
		jd = (flame * 100) / flamem;
		speed = flame / timec;
		timeleave = ((double)flamem - (double)flame) / speed;


		sprintf(fonname, "%s\\functions\\%s\\video%04d.mcfunction\0", cfgi.workpath, cfgi.dll.funcname, flame);
		//输出文件名
		sprintf(filename, "%s\\BMP\\%s%04d.bmp\0", cfgi.workpath, cfgi.file.name, flame);
		//输入文件名
		if (((int)timec - (int)t) > 0) {
			system("CLS");
			if (l == 0) {
				printf("当前进度：第%d帧\n总帧数:%d\n", flame, flamem);
				printf("速度：%2.2f帧每秒\n", speed);
				printf("剩余时间：%2.0f秒\n", timeleave);
				//printf("输入：%s\n", filename);
				//printf("输出：%s\n", fonname);
				prline(jd); printf("%d%%", jd);
				writepcess(flame);
			}
			//状态显示
			t = (int)timec;
		}

		fsp = fopen(fonname, "w+");
		FILE* fp = fopen(filename, "rb");
		RGBDATAl** data = readBmpDataToArr(fp);



		for (itemp[1] = 0; itemp[1] < w; itemp[1]++) {

			for (itemp[2] = 0; itemp[2] < h; itemp[2]++) {

				for (itemp[3] = 0; itemp[3] < 35; itemp[3]++) {

					value = abs(brgb[itemp[3]][0] - data[itemp[2]][itemp[1]].red) + abs(brgb[itemp[3]][1] - data[itemp[2]][itemp[1]].green) + abs(brgb[itemp[3]][2] - data[itemp[2]][itemp[1]].blue);

					if (value < itemp[4]) {
						itemp[4] = value;
						flag = itemp[3];
					}
				}
				cfgi.mem = 1;
				if (flame % cfgi.importf == 0) {
					cfgi.mem = 0;

				}
				if (cfgi.mem == 0 || oflag[itemp[2]][itemp[1]] != flag) {//节省资源
				//下面将flag转为指令
					switch (cfgi.dir)
					{
					case 0:
						yi = itemp[2];
						zi = itemp[1];
						break;
					case 1:
						yi = itemp[2];
						xi = itemp[1];
						break;
					case 2:
						xi = itemp[2];
						zi = -itemp[1];
						break;
					case 3:
						zi = itemp[2];
						xi = -itemp[1];
						break;
					default:
						yi = itemp[2];
						zi = itemp[1];
						break;
					}
					//方向转换
					if (c == 2) {
						fprintf(fsp, "setblock %d %d %d %s\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi,blockname[flag]);

					}
					if (c == 1) {
						/*
						switch (flag) {
						case 0:
							fprintf(fsp, "setblock %d %d %d acacia_log\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 1:
							fprintf(fsp, "setblock %d %d %d birch_log\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 2:
							fprintf(fsp, "setblock %d %d %d birch_planks\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 3:
							fprintf(fsp, "setblock %d %d %d acacia_planks\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 4:
							fprintf(fsp, "setblock %d %d %d blue_concrete\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 5:
							fprintf(fsp, "setblock %d %d %d emerald_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 6:
							fprintf(fsp, "setblock %d %d %d gold_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 7:
							fprintf(fsp, "setblock %d %d %d green_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 8:
							fprintf(fsp, "setblock %d %d %d iron_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 9:
							fprintf(fsp, "setblock %d %d %d light_blue_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 10:
							fprintf(fsp, "setblock %d %d %d lime_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 11:
							fprintf(fsp, "setblock %d %d %d magenta_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 12:
							fprintf(fsp, "setblock %d %d %d orange_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 13:
							fprintf(fsp, "setblock %d %d %d white_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 14:
							fprintf(fsp, "setblock %d %d %d pink_concrete\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 15:
							fprintf(fsp, "setblock %d %d %d red_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 16:
							fprintf(fsp, "setblock %d %d %d yellow_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 17:
							fprintf(fsp, "setblock %d %d %d yellow_concrete\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 18:
							fprintf(fsp, "setblock %d %d %d yellow_terracotta\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 19:
							fprintf(fsp, "setblock %d %d %d snow_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 20:
							fprintf(fsp, "setblock %d %d %d red_terracotta\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 21:
							fprintf(fsp, "setblock %d %d %d red_concrete\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 22:
							fprintf(fsp, "setblock %d %d %d orange_concrete\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 23:
							fprintf(fsp, "setblock %d %d %d pink_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 24:
							fprintf(fsp, "setblock %d %d %d pink_terracotta\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 25:
							fprintf(fsp, "setblock %d %d %d stripped_acacia_log\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 26:
							fprintf(fsp, "setblock %d %d %d white_terracotta\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 27:
							fprintf(fsp, "setblock %d %d %d chiseled_quartz_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 28:
							fprintf(fsp, "setblock %d %d %d black_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 29:
							fprintf(fsp, "setblock %d %d %d blue_wool\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 30:
							fprintf(fsp, "setblock %d %d %d cut_sandstone\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						default:
							break;
						}*/
					}//1.14.4
					if (c == 0) {
						switch (flag)
						{
						case 0:
							fprintf(fsp, "setblock %d %d %d clay\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 1:
							fprintf(fsp, "setblock %d %d %d log 2\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 2:
							fprintf(fsp, "setblock %d %d %d planks 2\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 3:
							fprintf(fsp, "setblock %d %d %d planks 4\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 4:
							fprintf(fsp, "setblock %d %d %d concrete 11\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 5:
							fprintf(fsp, "setblock %d %d %d emerald_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 6:
							fprintf(fsp, "setblock %d %d %d gold_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 7:
							fprintf(fsp, "setblock %d %d %d wool 13\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 8:
							fprintf(fsp, "setblock %d %d %d iron_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 9:
							fprintf(fsp, "setblock %d %d %d wool 3\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 10:
							fprintf(fsp, "setblock %d %d %d wool 5\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 11:
							fprintf(fsp, "setblock %d %d %d wool 10\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 12:
							fprintf(fsp, "setblock %d %d %d wool 1\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 13:
							fprintf(fsp, "setblock %d %d %d wool 0\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 14:
							fprintf(fsp, "setblock %d %d %d wool 6\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 15:
							fprintf(fsp, "setblock %d %d %d wool 14\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 16:
							fprintf(fsp, "setblock %d %d %d wool 4\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 17:
							fprintf(fsp, "setblock %d %d %d concrete 4\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 18:
							fprintf(fsp, "setblock %d %d %d stone\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 19:
							fprintf(fsp, "setblock %d %d %d snow\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 20:
							fprintf(fsp, "setblock %d %d %d redstone_block\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 21:
							fprintf(fsp, "setblock %d %d %d concrete 14\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 22:
							fprintf(fsp, "setblock %d %d %d concrete 1\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 23:
							fprintf(fsp, "setblock %d %d %d wool 2\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 24:
							fprintf(fsp, "setblock %d %d %d stained_hardened_clay 6\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 25:
							fprintf(fsp, "setblock %d %d %d stained_hardened_clay 14\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 26:
							fprintf(fsp, "setblock %d %d %d stained_hardened_clay 0\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 27:
							fprintf(fsp, "setblock %d %d %d quartz_block 1\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 28:
							fprintf(fsp, "setblock %d %d %d wool 15\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 29:
							fprintf(fsp, "setblock %d %d %d wool 11\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 30:
							fprintf(fsp, "setblock %d %d %d sandstone 2\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 31:
							fprintf(fsp, "setblock %d %d %d wool 8\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 32:
							fprintf(fsp, "setblock %d %d %d wool 7\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 33:
							fprintf(fsp, "setblock %d %d %d concrete 12\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 34:
							fprintf(fsp, "setblock %d %d %d planks 5\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						case 35:
							fprintf(fsp, "setblock %d %d %d air\n", cfgi.pos.x + xi, cfgi.pos.y + yi, cfgi.pos.z + zi);
							break;
						default:
							break;
						}
					}//1.12.2
					oflag[itemp[2]][itemp[1]] = flag;
				}
				flag = 0;
				itemp[4] = 128;
				//重置循环
			}
		}//一帧
		fclose(fsp);
		fclose(fp);
		free(data);
		//重置指针
		memset(fonname, 0, sizeof(fonname) / sizeof(char));
		memset(filename, 0, sizeof(filename) / sizeof(char));
		finish = clock();
	}
	system("cls");
	system("del /Q process.tmp");
	if (l == 0) {
		printf("总帧数:%d\n完毕!\nbilibili 虞骐菌 制作\nQQ交流群499254385\n", flamem);
	}
	system("pause");
	return 0;
}
