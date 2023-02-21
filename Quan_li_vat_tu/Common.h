#pragma once
#include "Header.h"
#include "Constant.h"

bool g_page = false, sf_page = false, b_page = false, ss_page = false;
struct view_page {
	int current = 1;
	int page = 1;
};
struct check_CURD {
	int l;
	int t;
	int r;
	int b;
	int n; // luu so luong can check // o vi tri so index = 0 //  
};

bool ktVT(int l, int t, int r, int b, int x, int y) {
	/*cout << l << " " << x << " " << r << "|" << t << " " << y << " " << b << " ";*/
	if (x <= r && x >= l && y >= t && y <= b) return true;
	return false;
}
void text_box (int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8,int bg=11,int tColor=0) {
	setcolor(tColor);
	settextstyle(font, 0, f_size);
	setfillstyle(1, 11);
	bar3d(l, t, r, b, 0, 0);
	setbkcolor(bg);
	outtextxy(l + d_l, t + d_t, s);
}

void text_box_no_border(int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8, int bg = 11, int tColor = 0) {
	setcolor(tColor);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar(l, t, r, b);
	setbkcolor(bg);
	outtextxy(l + d_l, t + d_t, s);
}

void createHeader(char x[][maxTHeader]) {
	setfillstyle(1, 7);
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
void writeText(int x, int y, char text[], int size=1,int tColor=0,int font = f_small,int bg=bk_screen) {
	setcolor(tColor);
	setbkcolor(bg);
	settextstyle(font, 0, size);
	outtextxy(x, y, text);
}
void delete_after_header() {
	setfillstyle(1, bk_screen);
	bar(0, 60, 1200, 900);
}
void page_transition(view_page& view_page) {
	int l_arrow_l = 525, t_arrow_l = 565, r_arrow_l = 560, b_arrow_l = 600;
	int l_arrow_r = 600, t_arrow_r = 565, r_arrow_r = 635, b_arrow_r = 600;
	string s = to_string(view_page.current);
	char num_p[2];
	strcpy_s(num_p, s.c_str());
	setbkcolor(bk_screen);
	settextstyle(f_small, 0, 2);
	outtextxy(575, 570, num_p);
	char arrow_left[] = "<";
	char arrow_right[] = ">";
	if (view_page.current == 1) {
		//>
		setbkcolor(11);
		settextstyle(f_small, 0, 3);
		text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10, 11);

	}
	else if (view_page.current == view_page.page) {
		//<
		setbkcolor(11);
		settextstyle(f_small, 0, 3);
		text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10, 11);
	}
	else  {
		//< >
		settextstyle(f_small, 0, 3);
		setbkcolor(11);
		text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10, 11);
		text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10, 11);

	}
}
void next_page(int l, int t, int r, int b, view_page& check_page,int _delay=200 ,int d_t=5,int d_l=10 ,int bg = 10, int color = 0) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current >= total_page) {
		cout<<"K the next page";
	}
	else {
		check_page.current++;
	}
	highlight_box(l, t, r, b, (char*)">", f_medium, 3, d_t, d_l, color, bg);
	delay(_delay);
}
void prev_page(int l, int t, int r, int b, view_page& check_page, int _delay = 200,int d_t = 5, int d_l = 10,int bg = 10, int color = 0) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current <=1) {
		cout << "K the prev page";
	}
	else {
		check_page.current--;
	}
	highlight_box(l, t, r, b, (char*)"<", f_medium, 3,d_t,d_l,color,bg);
	delay( _delay);
}