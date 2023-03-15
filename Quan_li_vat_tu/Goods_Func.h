#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Goods_tree.h"

#define COLS_G 10

//--variable
char g_table_header[][20] = { "MaVT","TenVT","So luong ton","Don vi" };

DS_VatTu* ds_vt;
VatTu vatu;
TempArr arrGoods;
check_CURD delete_table_g[COLS_G];
check_CURD edit_table_g[COLS_G];
view_page vp_g_table;

//

void create_g_header();
void goods_infor(); // edit insert
void goods_table(
	//char sf_table_header[][20],
	TempArr ds, // day la danh sach cac phan tu chon kd_lieu cho phu hop
	char curd_o[][20], // "them sua xoa" // k can co the xoa
	view_page& view_page,
	check_CURD edit[],//// k can co the xoa
	check_CURD _delete[],// k can co the xoa
	int num_cols
);
void create_g_header() {
	setfillstyle(1, 15);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);

	text_box(15, 70, 310, 110, (char*)"", f_medium, 3, 10, 40, bk_screen);
	text_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 10, 40, bk_screen);
}
void goods_infor() {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin vat tu", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)"", f_medium, 2, 0, 0, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma nhan vien", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 225, 800, 255, (char*)"", f_medium, 2, 0, 0, 15, 0);
	writeText(260, 230, (char*)"Ten vat tu", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, (char*)"", f_medium, 2, 0, 0, 15, 0);
	writeText(260, 290, (char*)"Don vi tinh", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"So luong ton", 2, 0, f_medium, COLOR_INFOR_SG);
	text_box(430, 345, 800, 375, (char*)"", f_medium, 2, 5, 30, 15, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}
void goods_table(
	char sf_table_header[][20],
	TempArr ds, 
	char curd_o[][20], 
	view_page& view_page,
	check_CURD edit[],
	check_CURD _delete[],
	int num_cols
) {
	delete_after_header();
	create_sf_header();
	// tnh so page co trong trang
	setcolor(0);
	int n = ds.n;
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
	outtextxy(55, text_top, (char*)"STT");
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
		//vi tri edit
		edit[e].l = 900;
		edit[e].t = text_top;
		edit[e].r = 978;
		edit[e].b = text_top + 22;
		e++;
		// vi tri delete
		_delete[d].l = 990;
		_delete[d].t = text_top;
		_delete[d].r = 1038;
		_delete[d].b = text_top + 22;
		d++;
		// --------------------------------- xuong day

		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt);
		writeText(95, text_top, ds.vat_tu[i].maVT);
		writeText(230, text_top, ds.vat_tu[i].tenVT);
	
		writeText(650, text_top, (char*)to_string(ds.vat_tu[i].SLT).c_str());

		//------------- k can cos the xoa
		text_box(900, text_top, 978, text_top + 22, curd_o[0], f_small, 1, 1, 2);
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