#pragma once
#include "Header.h"
#define max_staff 500
struct Staff {
	char maNV[11];
	char tenNV[26];
	char phai[4];
	// ds hd
};
struct List_staff {
	Staff *A_staff [500];
	int length=0;
};