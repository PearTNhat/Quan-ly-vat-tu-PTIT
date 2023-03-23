#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#define CLL COLOR(42, 193, 219)

void DrawRecTangle(int x1, int y1, int x2, int y2, int mau, int size) {
	setcolor(mau);
	setlinestyle(0, 0, size);
	rectangle(x1, y1, x2, y2);
}

void DrawBar(int x1, int y1, int x2, int y2, int maunen) {
	setfillstyle(1, maunen);
	bar(x1, y1, x2, y2);
}

void DrawLoading(int x1, int y1, int x2, int y2,int t) {
	
	int kc = 20;
	int i = 1;
	int j = x1;
	while ((x1 + (i - 1) * kc) < x2) {
		DrawBar(x1, y1 + 3, x1 + kc * i , y2 - 3, RED);
		i++;
		delay(t);
	}
}

void Loading(int& x, int& y)
{
	text_box_no_border(0, 0, 1200, 900, (char*)"QUAN LY VAT TU", 4, 7, 100, 200, CLL, 0);
	text_box_no_border(200, 200, 300, 300, (char*)"LE TUAN NHAT", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 240, 300, 340, (char*)"DO NGUYEN PHUONG", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 280, 300, 380, (char*)"HO VAN PHU", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(600, 350, 900, 390, (char*)"GV: LUU NGUYEN KY THU", 4, 2, 0, 8, CLL, 0);
	text_box(480, 470, 700, 510, (char*)"BAT DAU", 4, 4, 5, 8, COLOR(240, 89, 179), 0);
	//text_box(480, 470, 700, 510, (char*)"BAT DAU", 4, 4, 5, 8, COLOR(33, 97, 145), 0);
	while (1)
	{
		batdau:
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (ktVT(480, 470, 700, 510, x, y))
			{
				//lan 1
				DrawRecTangle(200, 420, 985, 450, RED, 2);
				text_box_no_border(480, 470, 700, 510, (char*)"", 4, 5, 0, 8, CLL, 0);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				DrawLoading(200, 420, 278.5, 450, 15);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				// lan 2
				
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);
				DrawLoading(278.5, 420, 592.5, 450, 15);
				
				//lan 3
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				DrawLoading(592.5, 420, 906.5, 450, 15);

				//lan 4
			
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, CLL);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading.", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading..", 4, 1, 0, 8, CLL, 0);
				delay(150);
				text_box_no_border(250, 390, 300, 410, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				delay(150);

				DrawLoading(906.5, 420, 985, 450, 50);
				delay(200);
				setlinestyle(0, 0, 1);
			}
			else
				goto batdau;
			break;
			
		}
	}
	
}