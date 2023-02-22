#pragma once

#include "Common.h";
#define MAXTITLE 25

char title[5][MAXTITLE] = { "Top", "Ma VT", "Ten Vat Tu", "Don Vi Tinh", "Doanh Thu" };


void create_ss_header() {
	setfillstyle(1, 15);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);

	text_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, bk_screen);
	text_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 3, 10, 40, bk_screen);
}

void create_ss_search(bool isBill) {
	setfillstyle(1, 15);
	setcolor(0);
	bar3d(280, 180, 920, 530, 0, 0);

	// Thanh tieu de
	const char* title;
	if (isBill) title = "Tim Kiem Hoa Don";
	else title = "Tim Top 10 Vat Tu";
	text_box(440, 140, 750, 181, (char*)title, f_medium, 3, 10, 40, 10);
	// Thanh tim kiem
	text_box(310, 480, 890, 520, (char*)"Tim kiem", f_medium, 3, 10, 230, 14);
	// Begin
	text_box(290, 190, 520, 230, (char*)"Tu ngay (begin)", f_medium, 3, 10, 10, 10);
	setfillstyle(1, 15);
	setbkcolor(bk_screen);
	outtextxy(320, 260, (char*)"Ngay");
	bar3d(400, 250, 500, 285, 0, 0);
	outtextxy(530, 260, (char*)"Thang");
	bar3d(610, 250, 710, 285, 0, 0);
	outtextxy(740, 260, (char*)"Nam");
	bar3d(800, 250, 900, 285, 0, 0);
	// End
	text_box(290, 300, 520, 340, (char*)"Den ngay (end)", f_medium, 3, 10, 10, 10);
	text_box(540, 300, 650, 340, (char*)"TODAY", f_medium, 3, 10, 20, COLOR(255, 153, 51));
	setfillstyle(1, 15);
	setbkcolor(bk_screen);
	outtextxy(320, 370, (char*)"Ngay");
	bar3d(400, 360, 500, 395, 0, 0);
	outtextxy(530, 370, (char*)"Thang");
	bar3d(610, 360, 710, 395, 0, 0);
	outtextxy(740, 370, (char*)"Nam");
	bar3d(800, 360, 900, 395, 0, 0);
}

void table_top_10_vattu() {
	setfillstyle(1, 15);
	setcolor(0); 
	bar3d(110, 130, 1090, 590, 0, 0);

	// thanh tieu de
	setfillstyle(1, COLOR(4, 169, 109));
	setcolor(15);
	text_box_no_border(200, 140, 1000, 185, (char*)"DANH SACH TOP 10 VAT TU DOANH THU CAO NHAT", 8, 3, 10, 100, COLOR(4, 170, 109), 15);
	
	// Bang top 10 vat tu

}

