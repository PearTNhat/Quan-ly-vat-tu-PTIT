#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Staff_Struct.h"

check_CURD delete_sf[ROW_STAFF];
check_CURD edit_sf[ROW_STAFF];
view_page vp_m_sf;



bool s_isEdit = false;
void staff_infor(char mnv[] = {}, char ho[] = {}, char ten[] = {}, char gender[] = {});


void create_sf_header() {
	
	setfillstyle(1, bk_screen);
	setcolor(0);

	text_box(950, 70, 1150, 110, (char*)"Them nhan vien", f_medium, 2, 10, 20, 11);
	setbkcolor(bk_screen);
	setcolor(12);
	settextstyle(f_medium, 0, 3);
	outtextxy(50, 75, (char*)"Danh sach nhan vien");

}
void staff_table(
	char sf_table_header[][20],
	DS_NhanVien ds, // day la danh sach cac phan tu chon kd_lieu cho phu hop
	char curd_o[][20], // "them sua xoa" // k can co the xoa
	view_page& view_page,
	check_CURD edit[],//// k can co the xoa
	check_CURD _delete[],// k can co the xoa
	int num_cols
) {
	delete_after_header();
	create_sf_header();
	// tnh so page co trong trang
	setcolor(0);
	int n = ds.length;
	int page = n / num_cols; 
	int du = n % num_cols;
	view_page.page = du ? page + 1 : page;
	int max_page = n > (num_cols * view_page.current) ? (num_cols * view_page.current) : n;
	// reder page
	int i = num_cols * (view_page.current - 1);
	//header
	int bar_top = 120, bar_bottom = 150;
	int text_top = 125;
	setfillstyle(1, 6);
	setbkcolor(6);
	settextstyle(f_small, 0, 1);
	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	outtextxy(55, text_top, (char *)"STT");
	outtextxy(95, text_top, sf_table_header[0]);
	outtextxy(230, text_top, sf_table_header[1]);
	outtextxy(650, text_top, sf_table_header[2]);
	outtextxy(900, text_top, sf_table_header[3]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	for (; i < max_page; i++)
	{
		if (i % num_cols == 0) {
			bar_top += 30;
			bar_bottom += 40;
			text_top += 35;
		}
		else {
			bar_top += 40;
			bar_bottom += 40;
			text_top += 40;
		}
		// Neu k su dung thi xoa tu day xuong
		//vi tri edit
		edit[e].l = 900;
		edit[e].t = text_top;
		edit[e].r = 978;
		edit[e].b = text_top + 22;
		e++;
		// vi tri delete
		_delete[d].l = 990;
		_delete[d].t = text_top;
		_delete[d].r = 1038;
		_delete[d].b = text_top + 22;
		d++;
		// --------------------------------- xuong day
		
		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i+1).c_str());
		writeText(55, text_top,stt);
		writeText(95, text_top, ds.nhan_vien[i]->maNV);

		string fullName = ds.nhan_vien[i]->ho;
		fullName += " ";
		fullName += ds.nhan_vien[i]->ten;
		char ten[30];
		strcpy_s(ten, fullName.c_str());
		writeText(230, text_top,ten);
		writeText(650, text_top, ds.nhan_vien[i]->phai);

		//------------- k can cos the xoa
		text_box(900, text_top, 978, text_top + 22, curd_o[0], f_small, 1, 1,2);
		text_box(995, text_top, 1038, text_top + 22, curd_o[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete[0].n = d;
	edit[0].n = e;

	// < >
	page_transition(view_page);

}
void sf_handleTable(int &x, int &y, DS_NhanVien ds_nv) {
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// edit
			for (int i = 0; i < edit_sf[0].n; i++)
			{
				if (ktVT(edit_sf[i].l, edit_sf[i].t, edit_sf[i].r, edit_sf[i].b, x, y)) {
					staff_infor(ds_nv.nhan_vien[i]->maNV, ds_nv.nhan_vien[i]->ho, ds_nv.nhan_vien[i]->ten, ds_nv.nhan_vien[i]->phai);
					i_CURD = (vp_m_sf.current - 1) * ROW_STAFF + i;
					s_isEdit = true;
					goto sf_out;
				}
			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_m_sf.current == vp_m_sf.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_m_sf);
				delete_after_header();
				staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, ROW_STAFF);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_m_sf.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_m_sf);
				delete_after_header();
				staff_table(sf_table_header, ds_nv, CURD_o_text, vp_m_sf, edit_sf, delete_sf, ROW_STAFF);
			}
			if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y)) {
				sf_page = false;
				goto sf_out;
			}
		}
		delay(1);
	}
	sf_out:;
	string t_mnv = ds_nv.nhan_vien[i_CURD]->maNV;
	string t_ho = ds_nv.nhan_vien[i_CURD]->ho;
	string t_ten = ds_nv.nhan_vien[i_CURD]->ten;
	string t_gender = ds_nv.nhan_vien[i_CURD]->phai;
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << "\nvi tri x:" << x << " - vi tri y:" << y << endl;
			
			if (s_isEdit) {
				if (ktVT(430, 165, 800, 195,x,y)) { // MNV
					t_mnv=input(430, 165, 800, 195, 5, 6,5, 35,50, t_mnv,10,NULL, COLOR_INFOR_SG);
				}
				if (ktVT(430, 225, 800, 255, x, y)) { // ho
					t_ho = input(430, 225, 800, 255, 5, 6, 5, 35, 50, t_ho, 8, NULL, COLOR_INFOR_SG);
				}
				if (ktVT(430, 285, 800, 315, x, y)) { // ten
					t_ten = input(430, 285, 800, 315, 5, 6, 5, 35, 50, t_ten, 20, NULL, COLOR_INFOR_SG);
				}
				if (ktVT(430, 345, 530, 375, x, y)) {
					t_gender = "Nam";
					text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5, 30, XANH_LA_CAY, 0);
					text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, 15, 0);

				}
				if (ktVT(560, 345, 660, 375, x, y)) {
					t_gender = "Nu";
					text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5, 30, 15, 0);
					text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, XANH_LA_CAY, 0);
				}
				//HUY
				if (ktVT(750, 420, 820, 450, x, y)) {
					s_isEdit = false;
					goto s_start;
				}
				//LUU
				if (ktVT(840, 420, 910, 450, x, y)) {
					strcpy_s(ds_nv.nhan_vien[i_CURD]->maNV, t_mnv.c_str());
					strcpy_s(ds_nv.nhan_vien[i_CURD]->ho, t_ho.c_str());
					strcpy_s(ds_nv.nhan_vien[i_CURD]->ten, t_ten.c_str());
					strcpy_s(ds_nv.nhan_vien[i_CURD]->phai, t_gender.c_str());
					s_isEdit = false;
					goto s_start;
				}

			}
			
		}
		delay(1);

	}
s_start:;
}
void staff_infor(char mnv[], char ho[] , char ten[] , char gender[] ) { 
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin nhan vien", f_medium, 2, 10, 10, 11,0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195,mnv,f_medium,1,6,5,15,0); // chu cao 20
	writeText(260, 170, (char*)"Ma Nhan Vien", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 225, 800, 255, ho, f_medium, 1, 6, 5, 15, 0);
	writeText(260, 230, (char*)"Ho", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, ten, f_medium, 1, 6, 5, 15, 0);
	writeText(260, 290, (char*)"Ten", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"Phai", 2, 0, f_medium, COLOR_INFOR_SG);
	int highlightWoman=15 , highlightMan=15;
	if (string(gender)=="Nam") {
		highlightMan = XANH_LA_CAY;
	}
	else  {
		highlightWoman = XANH_LA_CAY;
	}
	text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5,30, highlightMan, 0);
	text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, highlightWoman, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}