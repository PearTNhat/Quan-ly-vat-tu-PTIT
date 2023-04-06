#pragma once
struct VatTu {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
};
// tree
struct DS_VatTu {
	VatTu vat_tu;
	DS_VatTu* left;
	DS_VatTu* right;
};
