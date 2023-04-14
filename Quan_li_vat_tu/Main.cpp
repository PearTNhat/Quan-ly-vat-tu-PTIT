#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_func.h"
#include "Goods_FuncTree.h"
#include "Goods_Func.h"
#include "Bill_Func.h"
#include "Ss_page.h"
#include "Loading.h"

int main() {
	
	// nhân viên
	check_CURD delete_sf;
	check_CURD edit_sf;
	view_page vp_m_sf;
	bool sf_isEdit = false, sf_isAdd = false;
	DS_NhanVien ds_nv;
	read_file_staff(ds_nv);
	sort_staff(ds_nv);
	// vật tư
	check_CURD delete_table_g;
	check_CURD edit_table_g;
	view_page vp_g_table;
	bool g_isEdit = false, g_isAdd = false;
	
	DS_VatTu* ds_vt=NULL;
	DS_s_VT *ds_s_vt = NULL;
	read_file_goods(ds_vt);
	coppyVTtoSVT(ds_vt, ds_s_vt);
	//lnrSVT(ds_s_vt);
	//
	PTRHD ds_hd = NULL;
	//read_file_DSHD(ds_hd);
	//ds_tmp arr_temp = build_dshd_array(ds_hd);
	int x, y;
	initwindow(1200, 620, "Quan li vat tu");
	cleardevice();
	//Loading(x,y);
	setlinestyle(0, 0, 2);
	setbkcolor(bk_screen);
	cleardevice();
	
	createHeader(header_title);
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << "\nvi tri x-out:" << x << " - vi tri y-out:" << y << endl;
			line(x, y, x + 20, y);
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
				goods_table(g_table_header, ds_vt,ds_s_vt, CURD_o_text, vp_g_table, edit_table_g, delete_table_g,10);
				g_handleTable( x,  y,  ds_vt,ds_s_vt,  delete_table_g,  edit_table_g,  vp_g_table,  g_isEdit,  g_isAdd);
				goto sf_start;

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
				sf_handleTable(x, y, ds_nv, delete_sf,edit_sf,vp_m_sf, sf_isEdit, sf_isAdd);
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
				//demoPhu();
				b_create_menu_title();
				bill_page(x, y, ds_nv, ds_vt);
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
				test_data(ds_nv);
				bool is_error = false;
				bool thong_ke_hd_pg = false;
				bool thong_ke_doanh_thu_pg = false;
				bool is_all_valid = true;
				bool error_dayb = false, error_monthb = false, error_yearb = false, error_daye = false, error_monthe = false, error_yeare = false, error_year = false;
				create_ss_header();
				while (1) { 
					if (ismouseclick(WM_LBUTTONDOWN)) {
						getmouseclick(WM_LBUTTONDOWN, x, y);
					start_again:
						out_table = false;
						if (ktVT(15, 70, 310, 110, x, y)) {
							is_all_valid = true;
							setlinestyle(0, 0, 3);
							delete_after_header();
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
							is_all_valid = true;
							setlinestyle(0, 0, 3);
							delete_after_header();
							create_ss_header();
							highlight_box(320, 70, 640, 110, (char*)"Thong ke doanh thu", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							do_hoa_search_doanh_thu();
							thong_ke_doanh_thu_pg = true;
							thong_ke_hd_pg = false;
							year_dt = "";
						}
						xu_li_tra_cuu_doanh_thu(x, y, is_all_valid, error_year, year_dt, thong_ke_doanh_thu_pg, ds_nv);
						xu_li_thong_ke_hd(x, y, is_all_valid, error_dayb, error_monthb, error_yearb, error_daye, error_monthe, error_yeare, day_b, month_b, year_b, day_e, month_e, year_e, thong_ke_hd_pg, ds_nv);
						if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y))
							goto start;
						if (out_table) goto start_again;
					}
				}
			}
			delay(1);
		}
	}
	delete[] & ds_nv.length;
	getch();
	closegraph();
	return 0;
}
