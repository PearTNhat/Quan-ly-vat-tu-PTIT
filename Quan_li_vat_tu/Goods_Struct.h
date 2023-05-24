#pragma once
struct VatTu {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
	int sldaban; // so luong hoadon 
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
template <typename T>
struct templeDynamicArray {
	T** a;
	int capacity;
	int size_current = 0;
	templeDynamicArray(int size) {
		capacity = size;
		a = new T * [capacity];
	}
	
};