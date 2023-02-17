#pragma once
#include "Header.h"
#include "Constant.h"

bool ktVT(int l, int t, int r, int b, int x, int y) {
	/*cout << l << " " << x << " " << r << "|" << t << " " << y << " " << b << " ";*/
	if (x <= r && x >= l && y >= t && y <= b) return true;
	return false;
}
void text_box (int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8) {
	setcolor(0);
	settextstyle(font, 0, f_size);
	setfillstyle(1, 11);
	bar3d(l, t, r, b, 0, 0);
	setbkcolor(11);
	outtextxy(l + d_l, t + d_t, s);
}
void createHeader(char x[][maxTHeader]) {
	setfillstyle(1, 11);
	setcolor(0);
	bar3d(0, 0, 1200, 60,0,0);
	text_box(50, 10, 250, 50, x[0], f_medium, 3, 10, 56);
	text_box(350, 10,550 , 50, x[1], f_medium, 3, 10, 43);
	text_box(650, 10, 850, 50, x[2], f_medium, 3, 10, 35);
	text_box(950, 10, 1150, 50, x[3], f_medium, 3, 10, 45);
}
void highlight_box(int l, int t, int r, int b, char s[], int font, int f_size,int kct, int kcl, int color=0 ,int bg_hl= HIGHLIGHT_BOX) {
	setcolor(color);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg_hl);
	bar3d(l, t, r, b, 0, 0);
	setbkcolor(bg_hl);
	outtextxy(l + kcl, t + kct, s);
}