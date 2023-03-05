#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_func.h"
#include "Goods_Func.h"
#include"b_phu.h"
#include "Ss_page.h"

int main() {
	for (int i = 0; i < 28; i++)
	{
		ds_nv.nhan_vien[i] = new NhanVien;
		strcpy_s(ds_nv.nhan_vien[i]->maNV, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->ho, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->ten, "hello");
		ds_nv.nhan_vien[i]->phai = 0;
		ds_nv.length++;
	}
	string demo = ""; // bien nay chi la test thoi
	int x, y;
	initwindow(1200, 620, "Quan li vat tu");
	setbkcolor(bk_screen);
	cleardevice();
	createHeader(header_title);
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << "\nvi tri x:" << x << " - vi tri y:" << y << endl;
			line(x, y, x + 20, y);
			//------------------------
			//code
		s_start:
		start:
			//Nhat
		batdau:
			//vat tu 
			if (ktVT(50, 10, 250, 50, x, y)) {
				createHeader(header_title);
				highlight_box(50, 10, 250, 50, header_title[0], f_medium, 3, 10, 56);
				g_page = true;
				sf_page = false;
				b_page = false;
				ss_page = false;
				delete_after_header();
			}
			if (g_page) {
				bar3d(100, 200, 300, 250, 0, 0);
				goods_infor();
				if (ktVT(100, 200, 300, 250, x, y)) {
					string s = input(100, 200, 300, 250, 5, 5, 5, 30, 50, demo, 10);
					demo = s;
				}
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
				staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, COLS_SF);

				while (1) { // chong rerender k can thiet
					if (ismouseclick(WM_LBUTTONDOWN)) {
						getmouseclick(WM_LBUTTONDOWN, x, y);
						cout << "\nvi tri x:" << x << " - vi tri y:" << y << endl;
						// edit
						for (int i = 0; i < edit_sf[0].n; i++)
						{
							if (ktVT(edit_sf[i].l, edit_sf[i].t, edit_sf[i].r, edit_sf[i].b, x, y)) {
								staff_infor(ds_nv.nhan_vien[i]->maNV,ds_nv.nhan_vien[i]->ho, ds_nv.nhan_vien[i]->ten,ds_nv.nhan_vien[i]->phai);
								s_isEdit = true;
							}
						}
						if (s_isEdit) {
							//HUY
							if (ktVT(750, 420, 820, 450, x, y)) {
								s_isEdit = false;
								goto s_start;
							}
							//LUU
							if (ktVT(840, 420, 910, 450, x, y)) {
								s_isEdit = false;
								goto s_start;
							}

						}
						// transition page
						if (ktVT(650, 565, 685, 600, x, y)) {
							if (vp_m_sf.current == vp_m_sf.page) {
								continue;
							}
							next_page(650, 565, 685, 600, vp_m_sf);
							delete_after_header();
							staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, COLS_SF);
						}
						if (ktVT(495, 565, 530, 600, x, y)) {
							if (vp_m_sf.current == 1) {
								continue;
							}
							prev_page(495, 565, 530, 600, vp_m_sf);
							delete_after_header();
							staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, COLS_SF);
						}
						if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y)) {
							sf_page = false;
							goto s_start;
						}
					}
					delay(1);

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
				create_ss_header();
				while (1) {
					if (ismouseclick(WM_LBUTTONDOWN)) {
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if (ktVT(15, 70, 310, 110, x, y)) {
							create_ss_header();
							highlight_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							create_ss_search(1);
						}
						if (ktVT(320, 70, 565, 110, x, y)) {
							create_ss_header();
							highlight_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							create_ss_search(0);
						}
						if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y))
							goto start;
					}
				}
				//table_top_10_vattu();
			}

		}
		delay(1);
	}
	delete[] & ds_nv.length;
	getch();
	closegraph();
	return 0;
}