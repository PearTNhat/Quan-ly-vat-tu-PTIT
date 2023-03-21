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
				string day_b = "";
				string month_b = "";
				string year_b = "";
				string day_e = "";
				string month_e = "";
				string year_e = "";
				string year = "";
				bool is_error = false;
				bool thong_ke_hd_pg = false;
				bool thong_ke_doanh_thu_pg = false;
				bool is_all_valid = true;
				bool error_dayb = false, error_monthb = false, error_yearb = false, error_daye = false, error_monthe = false, error_yeare = false;
				create_ss_header();
				while (1) {
					if (ismouseclick(WM_LBUTTONDOWN)) {
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if (ktVT(15, 70, 310, 110, x, y)) {
							create_ss_header();
							highlight_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							do_hoa_search_hd();
							thong_ke_hd_pg = true;
							thong_ke_doanh_thu_pg = false;
							day_b = "";
							month_b = "";
							year_b = "";
							day_e = "";
							month_e = "";
							year_e = "";
						}
						if (ktVT(320, 70, 640, 110, x, y)) {
							delete_after_header();
							create_ss_header();
							highlight_box(320, 70, 640, 110, (char*)"Thong ke doanh thu", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							do_hoa_search_doanh_thu();
							thong_ke_doanh_thu_pg = true;
							thong_ke_hd_pg = false;
							year = "";
						}
						xu_li_tra_cuu_doanh_thu(x, y, year, thong_ke_doanh_thu_pg);
						xu_li_thong_ke_hd(x, y, is_all_valid, error_dayb, error_monthb, error_yearb, error_daye, error_monthe, error_yeare, day_b, month_b, year_b, day_e, month_e, year_e, thong_ke_hd_pg);
						if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y))
							goto start;
					}
				}
			}

		}
		delay(1);
	}
	delete[] & ds_nv.length;
	getch();
	closegraph();
	return 0;
}