/*
 * ToolUnits.cpp
 *
 *  Created on: 2022��7��26��
 *      Author: maochaoqun
 */

#include "ToolUnits.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "stdio.h"
#include <unistd.h>

int FileOp::SaveData(char *szFileName, unsigned char *iBuf,
		unsigned int iLen) {
	FILE *fp;
	fp = fopen(szFileName, "wb");
	if (!fp) {
		return -1;
	}
	if (fwrite(iBuf, 1, iLen, fp) != iLen) {
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

int FileOp::SaveDataApp(char *szFileName, unsigned char *iBuf,
						unsigned int iLen) {
	FILE *fp;
	fp = fopen(szFileName, "ab+");
	if (!fp) {
		return -1;
	}
	if (fwrite(iBuf, 1, iLen, fp) != iLen) {
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

int FileOp::GetDataSize(char *szFileName) {
	FILE *fp;
	fp = fopen(szFileName, ("rb"));
	if (!fp) {
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

int FileOp::ReadData(char *szFileName, unsigned char *oBuf, int iLen) {
	FILE *fp;
	fp = fopen(szFileName, "rb");
	if (!fp) {
		return -1;
	}
	fread(oBuf, 1, iLen, fp);
	fclose(fp);
	return 0;
}

int FileOp::GetCurrentPath(char *exeFullPath, int pathLen) {
	if (!getcwd(exeFullPath, pathLen)) {
		std::cout << "Get path fail!" << std::endl;
		return -1;
	}
	return 0;
}


int64_t systemnanotime() {
	timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec * 1000000000LL + now.tv_nsec;
}