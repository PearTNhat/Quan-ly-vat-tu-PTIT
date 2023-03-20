#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_func.h"
#include "Goods_Func.h"
#include "Bill_Func.h"
#include "Ss_page.h"
#include "Goods_tree.h"

int main() {
	DS_NhanVien ds_nv;
	for (int i = 0; i < 28; i++)
	{
		ds_nv.nhan_vien[i] = new NhanVien;
		strcpy_s(ds_nv.nhan_vien[i]->maNV, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->ho, "hello");
		strcpy_s(ds_nv.nhan_vien[i]->ten, ("hello"+to_string(i)).c_str());
		strcpy_s(ds_nv.nhan_vien[i]->phai, "Nam");
		ds_nv.length++;
	}
	//initNode(ds_vt);
	//strcpy_s(vatu.tenVT, "MEW MEO");
	//strcpy_s(vatu.DVT, "kg");
	//vatu.SLT = 1234;
	//strcpy_s(vatu.maVT, "VT060");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT015");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT007");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT002");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT001");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT005");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT012");
	//insertNode(ds_vt, vatu);
	//strcpy_s(vatu.maVT, "VT016");
	//insertNode(ds_vt, vatu);
	//copy_to_arr(ds_vt, arrGoods);
	int x, y;
	initwindow(1200, 620, "Quan li vat tu");
	setbkcolor(bk_screen);
	cleardevice();
	createHeader(header_title);
	while (1) {
		cout << "white: ";
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << "\nvi tri x-out:" << x << " - vi tri y-out:" << y << endl;
			line(x, y, x + 20, y);
			cout << "table";
			//------------------------
			//code
		sf_start:
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
				create_g_header();

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
				staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, ROW_STAFF);
				sf_handleTable(x, y,ds_nv);
				goto sf_start;
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
							do_hoa_search_hd();
						}
						//---------------------------------
						// Kiem tra vi tri input
						if (ktVT(400, 250, 500, 285, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(400, 250, 500, 285, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						}
						else if (ktVT(610, 250, 710, 285, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(610, 250, 710, 285, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						}
						else if (ktVT(800, 250, 900, 285, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(800, 250, 900, 285, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						} 
						else if (ktVT(400, 360, 500, 395, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(400, 360, 500, 395, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						}
						else if (ktVT(610, 360, 710, 395, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(610, 360, 710, 395, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						}
						else if (ktVT(800, 360, 900, 395, x, y)) {
							string demo = "";
							cout << "Tien hanh nhap input";
							string s = ss_page_input(800, 360, 900, 395, 40, 8, 5, 30, 50, demo, 2, 1);
							demo = s;
						}
						//----------------------------------
						if (ktVT(320, 70, 640, 110, x, y)) {
							delete_after_header();
							create_ss_header();
							highlight_box(320, 70, 640, 110, (char*)"Thong ke doanh thu", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							do_hoa_search_doanh_thu();
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