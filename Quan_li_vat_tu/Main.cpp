#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_func.h"
#include "Goods_FuncTree.h"
#include "Goods_Func.h"
#include "Bill_Func.h"
#include "Ss_page.h"
#include "Loading.h"
//xem lai  so 0 trong slt
// xem redender rooi gan khoi tao lai bien co hayb k
// next pae placeholder bi loi
int main() {
	// nhân viên
	string e_search_nv="";
	check_CURD delete_sf;
	check_CURD edit_sf;
	view_page vp_m_sf;
	DS_NhanVien ds_nv;
	bool sf_isEdit = false, sf_isAdd = false;
	read_file_staff(ds_nv);
	//quick_sort_staff(ds_nv, 0, ds_nv.length - 1);
	// vật tư
	string e_search_vt = "";
	check_CURD delete_table_g;
	check_CURD edit_table_g;
	view_page vp_g_table;
	bool g_isEdit = false, g_isAdd = false;

	DS_VatTu* ds_vt = NULL;
	DS_s_VT* ds_s_vt = NULL;
	read_file_goods(ds_vt);
	//coppyVTtoSVT(ds_vt, ds_s_vt);
	//
	PTRHD ds_hd = NULL;
	view_page vp_m_ss;
	string soHD = "";
	//
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
			//------------------------
			//code
		beginning:
		start:
			//Nhat
		batdau:
			//vat tu 
			if (ktVT(20, 10, 220, 50, x, y)) {
				createHeader(header_title);
				highlight_box(20, 10, 220, 50, header_title[0], f_medium, 3, 10, 56);
				g_page = true;
				sf_page = false;
				b_page = false;
				ss_page = false;
				X_page = false;
				delete_after_header();
			}
			if (g_page) {
				
				bool sf_out = g_handleTable(x, y, ds_vt, ds_s_vt, delete_table_g, edit_table_g, vp_g_table, g_isEdit, g_isAdd, e_search_vt);
				if (sf_out || ktVT(20, 10, 220, 50, x, y)) {
					goto beginning;
				}

			}
			// nhan vien
			if (ktVT(320, 10, 520, 50, x, y)) {
				createHeader(header_title);
				highlight_box(320, 10, 520, 50, header_title[1], f_medium, 3, 10, 43);
				g_page = false;
				sf_page = true;
				b_page = false;
				ss_page = false;
				X_page = false;
				delete_after_header();
			}

			if (sf_page) {
				create_sf_header();
				bool sf_out = sf_handleTable(x, y, ds_nv, delete_sf, edit_sf, vp_m_sf, sf_isEdit, sf_isAdd, e_search_nv);
				if (sf_out || ktVT(20, 10, 220, 50, x, y)) {
					goto beginning;
				}
			}
			//Phu
			if (ktVT(620, 10, 820, 50, x, y)) {
				createHeader(header_title);
				highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
				g_page = false;
				sf_page = false;
				b_page = true;
				ss_page = false;
				X_page = false;
				delete_after_header();
			}
			if (b_page) {
				//demoPhu();
				b_create_menu_title();
				bill_page(x, y, ds_nv, ds_vt, ds_s_vt, vp_m_ss, soHD);
				b_page = false;
				goto batdau;


			}
			//Phuong
			if (ktVT(920, 10, 1120, 50, x, y)) {
				createHeader(header_title);
				highlight_box(920, 10, 1120, 50, header_title[3], f_medium, 3, 10, 45);
				g_page = false;
				sf_page = false;
				b_page = false;
				ss_page = true;
				X_page = false;
				delete_after_header();
			}
			else ss_page = false;
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
						if (ktVT(15, 70, 310, 110, x, y)) {
							is_all_valid = true;
							setlinestyle(0, 0, 3);
							delete_after_header();
							create_ss_header();
							highlight_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, 0, XANH_LA_CAY);
							do_hoa_search_hd(vp_m_ss);
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
						xu_li_thong_ke_hd(x, y, is_all_valid, error_dayb, error_monthb, error_yearb, error_daye, error_monthe, error_yeare, day_b, month_b, year_b, day_e, month_e, year_e, thong_ke_hd_pg, ds_nv, vp_m_ss);
						xu_li_tra_cuu_doanh_thu(x, y, is_all_valid, error_year, year_dt, thong_ke_doanh_thu_pg, ds_nv);
						if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y))
							goto start;
					}
				}
			}
			if (ktVT(1140, 10, 1190, 50, x, y)) {
				g_page = false;
				sf_page = false;
				b_page = false;
				ss_page = false;
				X_page = true;
			}
			if (X_page)
			{
				highlight_box(1140, 10, 1190, 50, (char*)"X", f_medium, 4, 5, 14);
				
				announce_board(x, y, 50, 20, "THOAT CHUONG TRINH");
				delay(500);
				announce_board(x, y, 80, 20, "XIN CAM ON");
				delay(1000);
				goto end;
			}
			delay(1);
		}
	}
end:
	deleteTree(ds_vt);
	for (int i = 0; i < ds_nv.length; i++)
	{
		while (ds_nv.nhan_vien[i]->ds_hoadon != NULL)
		{
			while (ds_nv.nhan_vien[i]->ds_hoadon->hoadon.first_cthd != NULL)
			{
				Clearlist_CTHD(ds_nv.nhan_vien[i]->ds_hoadon->hoadon.first_cthd);
			}
			Clearlist_HD(ds_nv.nhan_vien[i]->ds_hoadon);
		}
		delete ds_nv.nhan_vien[i];
	}
	ds_nv.length = 0; // Đặt độ dài của mảng về 0
	closegraph();
	return 0;
}
