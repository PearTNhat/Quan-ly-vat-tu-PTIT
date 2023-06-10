#pragma once
#include "Header.h"
#include "Bill_Struct.h"
#define MAX_NV 500
struct NhanVien {
	char maNV[11];
	char ho[23];
	char ten[9];
	char phai[4];
	DS_HoaDon *ds_hoadon;
};
struct DS_NhanVien {
	NhanVien *nhan_vien[MAX_NV];	
	int length=0;
};
 
void insertOrderd_Staff(DS_NhanVien &ds_nv,NhanVien *x) {
	string p1 = (string)x->ten + (string)x->ho;
	string p2;
	NhanVien *temp=NULL;
	int index=-1;
	int k = 0;
	if (ds_nv.length<500) {

		for (int i = 0; i < ds_nv.length; i++)
		{
			p2 = (string)ds_nv.nhan_vien[i]->ten + (string)ds_nv.nhan_vien[i]->ho;
			if (p1 < p2 && index==-1) {
				index = i;
			}
			if (index>=0) {
				ds_nv.nhan_vien[ds_nv.length-k] = ds_nv.nhan_vien[ds_nv.length-1-k];
				k++;
			}
		}
		if (index>-1) {
			ds_nv.nhan_vien[index] = x;
		}
		else {
			ds_nv.nhan_vien[ds_nv.length] = x;
		}
	}
	else {
		cout << "list staff are overflow!!";
	}
}