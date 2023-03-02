#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_Struct.h"

check_CURD delete_sf[COLS_SF];
check_CURD edit_sf[COLS_SF];
view_page vp_m_sf;

DS_NhanVien ds_nv;

void create_sf_header() {
	
	setfillstyle(1, bk_screen);
	setcolor(0);

	text_box(950, 70, 1150, 110, (char*)"Them nhan vien", f_medium, 2, 10, 20, 11);
	setbkcolor(bk_screen);
	setcolor(12);
	settextstyle(f_medium, 0, 3);
	outtextxy(50, 75, (char*)"Danh sach nhan vien");

}
void staff_table(
	char sf_table_header[][20],
	DS_NhanVien ds, // day la danh sach cac phan tu chon kd_lieu cho phu hop
	char curd_o[][20], // "them sua xoa" // k can co the xoa
	view_page& view_page,
	check_CURD edit[],//// k can co the xoa
	check_CURD _delete[],// k can co the xoa
	int num_cols
) {
	create_sf_header();
	// tnh so page co trong trang
	setcolor(0);
	int n = ds.length;
	int page = n / num_cols; 
	int du = n % num_cols;
	view_page.page = du ? page + 1 : page;
	int max_page = n > (num_cols * view_page.current) ? (num_cols * view_page.current) : n;
	// reder page
	int i = num_cols * (view_page.current - 1);
	//header
	int bar_top = 120, bar_bottom = 150;
	int text_top = 125;
	setfillstyle(1, 6);
	setbkcolor(6);
	settextstyle(f_small, 0, 1);
	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	outtextxy(55, text_top, (char *)"STT");
	outtextxy(95, text_top, sf_table_header[0]);
	outtextxy(230, text_top, sf_table_header[1]);
	outtextxy(650, text_top, sf_table_header[2]);
	outtextxy(900, text_top, sf_table_header[3]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	for (; i < max_page; i++)
	{
		if (i % num_cols == 0) {
			bar_top += 30;
			bar_bottom += 40;
			text_top += 35;
		}
		else {
			bar_top += 40;
			bar_bottom += 40;
			text_top += 40;
		}
		// Neu k su dung thi xoa tu day xuong
		// vi tri delete
		_delete[d].l = 905;
		_delete[d].t = text_top;
		_delete[d].r = 948;
		_delete[d].b = text_top + 22;
		d++;
		//vi tri edit
		edit[e].l = 810;
		edit[e].t = text_top;
		edit[e].r = 888;
		edit[e].b = text_top + 22;
		e++;
		// --------------------------------- xuong day
		
		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i+1).c_str());
		writeText(55, text_top,stt);
		writeText(95, text_top, ds.nhan_vien[i]->maNV);
		writeText(230, text_top, ds.nhan_vien[i]->tenNV);
		writeText(650, text_top, ds.nhan_vien[i]->phai);

		//------------- k can cos the xoa
		text_box(900, text_top, 978, text_top + 22, curd_o[0], f_small, 1, 1,2);
		text_box(995, text_top, 1038, text_top + 22, curd_o[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete[0].n = d;
	edit[0].n = e;

	// < >
	page_transition(view_page);

}
