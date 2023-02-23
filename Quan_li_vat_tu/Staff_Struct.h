#pragma once
#include "Header.h"
#include "Struct_Bill.h"
#define MAX_NV 500
struct NhanVien {
	char maNV[11];
	char ho[9];
	char ten[21];
	int phai = -1;
	DS_HoaDon ds_hoadon;
};
struct DS_NhanVien {
	NhanVien *nhan_vien[MAX_NV];
	int length=0;
};