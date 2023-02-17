#include "Header.h"
#include "Common.h"
#include "Constant.h"
int main() {
	int x, y;
	bool g_page = false,sf_page=false,b_page=false,ss_page=false;
	initwindow(1200, 620,"Quan li vat tu");
	setbkcolor(bk_screen);
	cleardevice();
	createHeader(header_title);
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// phat hien click chuot			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << "\nvi tri x:" << x << " - vi tri y:" << y << endl;
			// duong nay giup thay vi tri click
			line(x, y, x + 20, y);
			//code
			//Nhat
			
			//vat tu 
			if (ktVT(50, 10, 250, 50, x,y)) {
				createHeader(header_title);
				highlight_box(50, 10, 250, 50, header_title[0], f_medium, 3,10,56);
				g_page = true;
				sf_page = false;
				b_page = false;
				ss_page = false;
			}
			if (g_page) {

			}
			// nhan vien
			if (ktVT(350, 10, 550, 50, x, y)) {
				createHeader(header_title);
				highlight_box(350, 10, 550, 50, header_title[1], f_medium, 3, 10, 43);
				g_page = false;
				sf_page = true;
				b_page = false;
				ss_page = false;
			}
			if (sf_page) {

			}
			//Phu
			if (ktVT(650, 10, 850, 50, x, y)) {
				createHeader(header_title);
				highlight_box(650, 10, 850, 50, header_title[2], f_medium, 3, 10, 35);
				g_page = false;
				sf_page = false;
				b_page = true;
				ss_page = false;
			}
			if (b_page) {



			}
			//Phuong
			if (ktVT(950, 10, 1150, 50, x, y)) {
				createHeader(header_title);
				highlight_box(950, 10, 1150, 50, header_title[3], f_medium, 3, 10, 45);
				g_page = false;
				sf_page = false;
				b_page = false;
				ss_page = true;
			}
			if (ss_page) {

			}

		}
		delay(1);
	}

		getch();
		closegraph();
	return 0;
}