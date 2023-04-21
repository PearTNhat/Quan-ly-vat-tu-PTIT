#pragma once
struct VatTu {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
	int sldaban;
};
// tree
struct DS_VatTu {
	VatTu vat_tu;
	DS_VatTu* left=NULL;
	DS_VatTu* right=NULL;
};
// tempTVT
struct s_VT {
	char maVT[11];
	char tenVT[26];
};
// ds small vt
struct DS_s_VT { 
	s_VT vat_tu;
	DS_s_VT* left = NULL;
	DS_s_VT* right = NULL;
};
struct templeGoods {
    DS_VatTu** a;
    int capacity;
    templeGoods(int size) {
        capacity = size;
        a = new DS_VatTu * [capacity];
    }
};