#pragma once
#include "Header.h"
struct VatTu {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
};
// mang tam
struct TempArr {
	VatTu vat_tu[500];
	int n = 0;
};
// tree
struct DS_VatTu {
	VatTu vat_tu;
	DS_VatTu* left;
	DS_VatTu* right;
};
