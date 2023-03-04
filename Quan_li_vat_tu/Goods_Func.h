#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
void create_g_header();
void goods_infor(); // edit insert

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