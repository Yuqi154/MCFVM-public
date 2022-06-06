#pragma once



#include<stdio.h>


typedef unsigned char BYTE;  // 1bytes





#pragma pack(push)

#pragma pack(1)// 修改默认对齐值

/*位图文件文件头结构体*/

#pragma pack(pop)



/*位图文件信息头结构体*/



/*位图文件调色板结构体*/

typedef struct tagRGBQUADl {

	BYTE	rgbBlue;

	BYTE	rgbGreen;

	BYTE	rgbRed;

	BYTE	rgbReserved;

}RGBQUADl;



/*像素点RGB结构体*/

typedef struct tagRGBl {

	BYTE blue;

	BYTE green;

	BYTE red;

}RGBDATAl;

int h = -1, w = -1, m = 1;

RGBDATAl** createMatrix(int width, int height);

RGBDATAl** readBmpDataToArr(FILE* fp) {

	int i = 0, j = 0;

	int width = 0, height = 0;

	fseek(fp, 18L, SEEK_SET);
	fread(&width, sizeof(width), 1, fp);

	fread(&height, sizeof(height), 1, fp);

	w = width;

	h = height;


	fseek(fp, 54L, SEEK_SET);

	RGBDATAl** data = createMatrix(width, height);

	RGBQUADl* rgbQuad = (RGBQUADl*)malloc(sizeof(RGBQUADl));

	fread(rgbQuad, sizeof(rgbQuad), 1, fp);

	for (i = 0; i < height; i++) {

		for (j = 0; j < width; j++) {

			fread(&data[i][j], sizeof(RGBDATAl), 1, fp);

		}

	}

	return data;

}



RGBDATAl** createMatrix(int width, int height) {

	//动态创建二维数组

	RGBDATAl** Matrix;

	int i;



	Matrix = (RGBDATAl**)malloc(sizeof(RGBDATAl*) * height);




	for (i = 0; i < height; i++) {

		Matrix[i] = (RGBDATAl*)malloc(sizeof(RGBDATAl) * width);


	}

	return(Matrix);

}
