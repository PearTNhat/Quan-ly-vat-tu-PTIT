#pragma once
#include "Staff_Struct.h"
#include "Common.h"
#include "Goods_Struct.h"
void search_staffs(DS_NhanVien ds_nv, templeDynamicArray<NhanVien> &arr,string value) {
	value = lowercase(value);
	deleteAllSpace(value);
	for (int i = 0; i < ds_nv.length; i++)
	{
		if (search_string(((string)ds_nv.nhan_vien[i]->ho + (string)ds_nv.nhan_vien[i]->ten), value) >= 0) {
			arr.a[arr.size_current++] = ds_nv.nhan_vien[i];
			cout << "thay ";

		}
		else if (search_string(ds_nv.nhan_vien[i]->maNV, value) >= 0) {
			arr.a[arr.size_current++] = ds_nv.nhan_vien[i];
			cout << "thay ";

		}
	}
}
