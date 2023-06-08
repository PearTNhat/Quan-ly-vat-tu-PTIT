#pragma once
#include "Staff_Struct.h"
#include "Common.h"
#include "Goods_Struct.h"
#include "Staff_func.h"
void staff_table_normal(
	NhanVien** nhan_vien,
	int length,
	view_page& view_page,
	int num_cols,
	string searchValue
);
void table_searching(int& x, int& y, DS_NhanVien ds_nv);

void search_staffs(DS_NhanVien ds_nv, templeDynamicArray<NhanVien> &arr,string value) {
	value = lowercase(value);
	deleteAllSpace(value);
	for (int i = 0; i < ds_nv.length; i++)
	{
		if (search_string(((string)ds_nv.nhan_vien[i]->ho + (string)ds_nv.nhan_vien[i]->ten), value) >= 0) {
			arr.a[arr.size_current++] = ds_nv.nhan_vien[i];
		}
		else if (search_string(ds_nv.nhan_vien[i]->maNV, value) >= 0) {
			arr.a[arr.size_current++] = ds_nv.nhan_vien[i];
		}
	}
}
void table_searching(int &x,int &y,DS_NhanVien ds_nv) {
	int svt_NULL = 0;
	int search_empty = 0;
	string value;
	view_page searhcing_view;
	templeDynamicArray<NhanVien> fillter_nv(ds_nv.length);
	search_staffs(ds_nv, fillter_nv, value);
	staff_table_normal(fillter_nv.a, fillter_nv.capacity, searhcing_view, 10, (string)"Nhap ten hoac id can tim kiem");
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			//search
			if (ktVT(50, 72, 400, 108, x, y)) {// search
				while (1) {
					value = input_one(x, y, 50, 72, 410, 108, 10, 10, value, 30);
					if (!ktVT(50, 72, 400, 108, x, y)) {
						if (value == "") {
							create_sf_header((string)"  Tro ve", (string)"Nhap ten hoac id can tim kiem");
						}
						break;
					}
					fillter_nv.size_current = 0;
					search_staffs(ds_nv, fillter_nv, value);
					if (value == "") {
						search_empty++;
					}
					else {
						search_empty = 0;
					}
					if (fillter_nv.size_current == 0) {
						svt_NULL++;
					}
					else {
						svt_NULL = 0;
					}
					if (svt_NULL == 1 || search_empty == 1 || (search_empty == 0 && svt_NULL == 0)) {
						staff_table_normal(fillter_nv.a, fillter_nv.size_current, searhcing_view, 10, value);
					}
					delay(1);
				}

			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (searhcing_view.current == searhcing_view.page) {
					continue;
				}
				next_page(650, 565, 685, 600, searhcing_view);
				delete_after_header();
				staff_table_normal(fillter_nv.a, fillter_nv.size_current, searhcing_view, 10, value);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (searhcing_view.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, searhcing_view);
				delete_after_header();
				staff_table_normal(fillter_nv.a, fillter_nv.size_current, searhcing_view, 10,value);
			}
			if (ktVT(950, 70, 1150, 110, x, y) || ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y)) {
				cout << "X ";
				break;
			}
		}
		delay(1);
	}
	delete[]fillter_nv.a;
	fillter_nv.a = nullptr;
}
void staff_table_normal(
	NhanVien** nhan_vien,
	int length,
	view_page& view_page,
	int num_cols,
	string searchValue
) {
	setlinestyle(0, 0, 0);
	delete_after_func();
	create_sf_header((string)"    Tro ve", searchValue);
	// tnh so page co trong trang
	setcolor(0);
	int n = length;
	int page = n / num_cols;
	int du = n % num_cols;
	view_page.page = du ? page + 1 : page;
	if (n == 0) {
		view_page.page = 1;
	}
	if (view_page.current > view_page.page) {
		view_page.current--;
	}
	int max_rows = n > (num_cols * view_page.current) ? (num_cols * view_page.current) : n;
	// reder page
	int i = num_cols * (view_page.current - 1);
	//header
	int bar_top = 120, bar_bottom = 155;
	int text_top = 127;
	setfillstyle(1, COLOR_HEADER_TABLE);
	setbkcolor(COLOR_HEADER_TABLE);
	settextstyle(f_small, 0, 1);
	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(95, text_top, (char*)sf_table_header[0]);
	outtextxy(230, text_top, (char*)sf_table_header[1]);
	outtextxy(550, text_top, (char*)sf_table_header[2]);
	outtextxy(740, text_top, (char*)sf_table_header[3]);
	outtextxy(900, text_top, (char*)sf_table_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
	for (; i < max_rows; i++)
	{
		if (i % num_cols == 0) {
			bar_top += 35;
			bar_bottom += 40;
			text_top += 40;
		}
		else {
			bar_top += 39;
			bar_bottom += 40;
			text_top += 39;
		}
		if (i == max_rows - 1) {
			bar_bottom -= (max_rows - num_cols * (view_page.current - 1)) - 2;
		}
		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, nhan_vien[i]->maNV, 1, 0, 3, 15);
		writeText(230, text_top, nhan_vien[i]->ho, 1, 0, 3, 15);
		writeText(550, text_top, nhan_vien[i]->ten, 1, 0, 3, 15);
		writeText(740, text_top, nhan_vien[i]->phai, 1, 0, 3, 15);
	
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	page_transition(view_page);
}