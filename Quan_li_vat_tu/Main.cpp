#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_func.h"
#include"b_phu.h"
int main() {
	for (int i = 0; i < 28; i++)
	{
		ds_nv.nhan_vien[i] = new NhanVien;
		strcpy_s(ds_nv.nhan_vien[i]->maNV, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->tenNV, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->phai, to_string(i).c_str());
		ds_nv.length++;
	}
	int x, y;
	initwindow(1200, 620,"Quan li vat tu");
	setbkcolor(bk_screen);
	cleardevice();
	createHeader(header_title);
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// phat hien click chuot
			cout << "\nvi tri x:" << x << " - vi tri y:" << y << endl;
			// duong nay giup thay vi tri click
			line(x, y, x + 20, y);
			//code
			//Nhat
			batdau:
			//vat tu 
			if (ktVT(50, 10, 250, 50, x,y)) {
				createHeader(header_title);
				highlight_box(50, 10, 250, 50, header_title[0], f_medium, 3,10,56);
				g_page = true;
				sf_page = false;
				b_page = false;
				ss_page = false;
				delete_after_header();
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
				delete_after_header();
			}
			if (sf_page) {
				create_sf_header();
				staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf,COLS_SF);
				if (ktVT(600, 565, 635, 600, x, y)) {
					next_page(600, 565, 635, 600,vp_m_sf);
					delete_after_header();
					staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, COLS_SF);
				}
				if (ktVT(525,565,560,600,x,y)) {
					prev_page(525, 565, 560, 600,vp_m_sf);
					delete_after_header();
					staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, COLS_SF);
				}
			}
			//Phu
			if (ktVT(650, 10, 850, 50, x, y)) {
				createHeader(header_title);
				highlight_box(650, 10, 850, 50, header_title[2], f_medium, 3, 10, 35);
				g_page = false;
				sf_page = false;
				b_page = true;
				ss_page = false;
				delete_after_header();
			}
			if (b_page) {
				b_create_menu_title();
				b_ktVT(x, y);
				b_page = false;
				goto batdau;


			}
			//Phuong
			if (ktVT(950, 10, 1150, 50, x, y)) {
				createHeader(header_title);
				highlight_box(950, 10, 1150, 50, header_title[3], f_medium, 3, 10, 45);
				g_page = false;
				sf_page = false;
				b_page = false;
				ss_page = true;
				delete_after_header();
			}
			if (ss_page) {

			}

		}
		delay(1);
	}
	delete[] &ds_nv.length;
		getch();
		closegraph();
	return 0;
}