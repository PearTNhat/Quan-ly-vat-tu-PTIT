#pragma once
#include "Header.h"
#include "Bill_Struct.h"
#define MAX_NV 500
struct NhanVien {
	char maNV[11];
	char ho[9];
	char ten[21];
	char phai[4];
	DS_HoaDon ds_hoadon;
};
struct DS_NhanVien {
	NhanVien *nhan_vien[MAX_NV];
	int length=0;
};