#pragma once
struct VatTu {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
	bool trangThai=false;	 // 0 là chưa có trong hoá đơn // 1 là có trong hoá đơn
};
// tree
struct DS_VatTu {
	VatTu vat_tu;
	DS_VatTu* left;
	DS_VatTu* right;
};
struct templeGoods {
    DS_VatTu** a;
    int capacity;
    templeGoods(int size) {
        capacity = size;
        a = new DS_VatTu * [capacity];
    }
};