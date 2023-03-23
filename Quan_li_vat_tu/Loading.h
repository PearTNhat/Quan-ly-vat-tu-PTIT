#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#define CLL COLOR(240, 163, 223)

void DrawRecTangle(int x1, int y1, int x2, int y2, int mau, int size) {
	setcolor(mau);
	setlinestyle(0, 0, size);
	rectangle(x1, y1, x2, y2);
}

void DrawBar(int x1, int y1, int x2, int y2, int maunen) {
	setfillstyle(1, maunen);
	bar(x1, y1, x2, y2);
}

void DrawLoading(int x1, int y1, int x2, int y2) {
	DrawRecTangle(x1, y1, x2, y2, RED, 2);
	int kc = 20;
	int i = 1;
	int j = x1;
	while ((x1 + (i - 1) * kc) < x2) {
		DrawBar(x1 + 3, y1 + 3, x1 + kc * i - 18, y2 - 3, RED);
		i++;
		delay(15);
	}
}

void Loading(int& x, int& y)
{
	text_box_no_border(0, 0, 1200, 900, (char*)"QUAN LY VAT TU", 4, 7, 100, 200, CLL, 0);
	text_box_no_border(200, 200, 300, 300, (char*)"LE TUAN NHAT", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 240, 300, 340, (char*)"DO NGUYEN PHUONG", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 280, 300, 380, (char*)"HO VAN PHU", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(600, 350, 900, 390, (char*)"GV: LUU NGUYEN KY THU", 4, 2, 0, 8, CLL, 0);
	text_box_no_border(480, 450, 700, 490, (char*)"BAT DAU", 4, 4, 0, 8, COLOR(240, 89, 179), 0);
	while (1)
	{
		batdau:
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (ktVT(480, 450, 700, 490, x, y))
			{
				text_box_no_border(480, 450, 700, 500, (char*)"", 4, 5, 0, 8, CLL, 0);
				text_box_no_border(250, 400, 300, 420, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
				DrawLoading(200, 420, 985, 450);
				//rectangle(200, 420, 985, 450);

			}
			else
				goto batdau;
			break;
			
		}
	}
	
}