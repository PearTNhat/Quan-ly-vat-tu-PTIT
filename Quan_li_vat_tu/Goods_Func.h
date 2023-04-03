#pragma once

#define COLS_G 10

// xoá root là lôix
// KHI O CO PHAN TU NAO TABLE BI LOI
//--variable
char g_table_header[][20] = { "MaVT","TenVT","So luong ton","Don vi" };

//
void create_g_header();
void goods_infor(string mvt="", string tvt="", string dvt="", int slt=-1); // edit insert
//
void create_g_header() {
	setfillstyle(1, 15);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);

	text_box(15, 70, 310, 110, (char*)"", f_medium, 3, 10, 40, bk_screen);
	text_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 10, 40, bk_screen);
}
void goods_infor(string mvt, string tvt,string dvt,int slt) {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin vat tu", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)"", f_medium, 2, 0, 0, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma nhan vien", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 225, 800, 255, (char*)"", f_medium, 2, 0, 0, 15, 0);
	writeText(260, 230, (char*)"Ten vat tu", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, (char*)"", f_medium, 2, 0, 0, 15, 0);
	writeText(260, 290, (char*)"Don vi tinh", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"So luong ton", 2, 0, f_medium, COLOR_INFOR_SG);
	text_box(430, 345, 800, 375, (char*)"", f_medium, 2, 5, 30, 15, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}
void goods_table(
	char sf_table_header[][20],
	DS_VatTu *ds_vt,
	char curd_o[][20], 
	view_page& view_page,
	check_CURD edit[],
	check_CURD _delete[],
	int num_cols
) {
	delete_after_header();
	create_sf_header();
	// tnh so page co trong trang
	setcolor(0);
	int n = getSizeGoods(ds_vt);
	int page = n / num_cols;
	int du = n % num_cols;
	view_page.page = du ? page + 1 : page;
	int max_rows = n > (num_cols * view_page.current) ? (num_cols * view_page.current) : n;
	// reder page
	int i = num_cols * (view_page.current - 1);
	//header
	int bar_top = 120, bar_bottom = 150;
	int text_top = 125;
	setfillstyle(1, 6);
	setbkcolor(6);
	settextstyle(f_small, 0, 1);
	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(95, text_top, sf_table_header[0]);
	outtextxy(230, text_top, sf_table_header[1]);
	outtextxy(650, text_top, sf_table_header[2]);
	outtextxy(900, text_top, sf_table_header[3]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	DS_VatTu *temp;
	for (; i < max_rows; i++)
	{
		temp = getIndexGoods(ds_vt, i+1);
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
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt,1,0,3,15);
		writeText(95, text_top, temp->vat_tu.maVT, 1, 0, 3, 15);
		writeText(230, text_top, temp->vat_tu.tenVT, 1, 0, 3, 15);
	
		writeText(650, text_top, (char*)to_string(temp->vat_tu.SLT).c_str(), 1, 0, 3, 15);

		//------------- k can cos the xoa
		text_box(900, text_top-2, 978, text_top + 23, curd_o[0], f_small, 1, 1, 2);
		text_box(995, text_top-2, 1038, text_top + 23, curd_o[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete[0].n = d;
	edit[0].n = e;

	// < >
	page_transition(view_page);

}
void handleInfor_goods(int& x, int& y, DS_VatTu *&ds_vt,  string& t_mvt, string& t_tvt, string& t_dvt, int& t_slt, int i_CRUD , bool& isEdit, bool& isAdd) {
	int checkSubmit[4];
	if (isAdd) {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = -1;
		}
	}
	if (isEdit) {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = 1;
		}
	}
	bool checkCancle = true;
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
		headInfor:;
			if (ktVT(430, 165, 800, 195, x, y)) { // MNV
				while (1) {
					t_mvt = input(x, y, 430, 165, 800, 195, 5, 6, 5, 35, 50, t_mvt, 10, "textNumberNoSpace", "upcase", COLOR_INFOR_SG, 430, 225);
					if (searchNode(ds_vt, t_mvt) == -1) {
						break; 
					}
					else {
						warning_msg((char*)"Ma nhan vien da ton tai.", 435, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
				}

				if (isAdd) {
					if (t_mvt.length() > 0) {
						checkSubmit[0] = 1;
					}
					else {
						checkSubmit[0] = -1;
					}
				}
				goto headInfor;
			}
			if (ktVT(430, 225, 800, 255, x, y)) { // ho
				t_tvt = input(x, y, 430, 225, 800, 255, 5, 6, 5, 35, 50, t_tvt, 22, "text", "camelCase", COLOR_INFOR_SG, 430, 285);
				if (isAdd) {
					if (t_tvt.length() > 0) {
						checkSubmit[1] = 1;
					}
					else {
						checkSubmit[1] = -1;
					}
				}
				if (isEdit) {
					if (t_tvt.length() == 0) {
						checkSubmit[1] = -1;
					}
					else {
						checkSubmit[1] = 1;
					}
				}
				goto headInfor;

			}
			if (ktVT(430, 285, 800, 315, x, y)) { // ten
				t_dvt = input(x, y, 430, 285, 800, 315, 5, 6, 5, 35, 50, t_dvt, 8, "textNoSpace", "camelCase", COLOR_INFOR_SG, 430, 345);
				if (isAdd) {
					if (t_dvt.length() > 0) {
						checkSubmit[2] = 1;
					}
					else {
						checkSubmit[2] = -1;
					}
				}
				if (isEdit) {
					if (t_dvt.length() == 0) {
						checkSubmit[2] = -1;
					}
					else {
						checkSubmit[2] = 1;
					}
				}
				goto headInfor;

			}
			// slt
			
			//HUY
			if (ktVT(750, 420, 820, 450, x, y)) {
				text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				if (checkSubmitEditStaff(checkSubmit, 4) < 4) {
					checkCancle = announce_board(x, y, 50, 0, "Ban co muon huy.", "");
				}
				if (checkCancle) {
					isEdit = false;
					isAdd = false;
					delay(200);
					goto sf_end;
				}
				else {
					goods_infor(t_mvt, t_tvt, t_dvt, t_slt);
					x = NULL, y = NULL;
					goto headInfor;
				}

			}
			//LUU
			if (ktVT(840, 420, 910, 450, x, y)) {
				if (checkSubmitEditStaff(checkSubmit, 4) == 0) {
					VatTu vt_temp;
					if (isAdd) {
						vt_temp = {};
						strcpy_s(vt_temp.maVT, t_mvt.c_str());
						strcpy_s(vt_temp.tenVT, t_tvt.c_str());
						strcpy_s(vt_temp.DVT, t_dvt.c_str());
						vt_temp.SLT = t_slt;
						insertNode(ds_vt,vt_temp);
					}
					if (isEdit) {
						vt_temp = {};


					}

					isEdit = false;
					isAdd = false;

					text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
					announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
					delay(500);
					goto sf_end;
				}
				else {
					int left_error = 630;
					if (checkSubmit[0] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[1] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 225 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[2] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 285 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[3] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 350 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

				}
			}


		}
	}
sf_end:;
}
void g_handleTable(int& x, int& y, DS_VatTu *&ds_vt, check_CURD delete_table_g[], check_CURD edit_table_g[], view_page vp_g_table, bool& g_isEdit, bool& g_isAdd) {

	bool break_all = false;
	int i_CRUD = 0;
	bool check_D_staff = true;
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// them nhan vien moi
		start_handle_staff:
			if (ktVT(950, 70, 1150, 110, x, y)) {
				goods_infor();
				g_isAdd = true;
				goto sf_out;
			}
			// edit
			for (int i = 0; i < edit_table_g[0].n; i++)
			{
				if (ktVT(edit_table_g[i].l, edit_table_g[i].t, edit_table_g[i].r, edit_table_g[i].b, x, y)) {
					i_CRUD = (vp_g_table.current - 1) * ROW_STAFF + i;
					i_CRUD += 1;
					DS_VatTu *temp;
					temp = getIndexGoods(ds_vt,i_CRUD);
					goods_infor(temp->vat_tu.maVT, temp->vat_tu.tenVT, temp->vat_tu.DVT, temp->vat_tu.SLT);
					g_isEdit = true;
					goto sf_out;
				}
			}
			//delete
			for (int i = 0; i < delete_table_g[0].n; i++)
			{
				if (ktVT(delete_table_g[i].l, delete_table_g[i].t, delete_table_g[i].r, delete_table_g[i].b, x, y)) {
					check_D_staff = announce_board(x, y, 40, 0, "Ban co muon xoa khong.", "");
					if (check_D_staff) {
						i_CRUD = (vp_g_table.current - 1) * ROW_STAFF + i;
						i_CRUD += 1;
						string mvt = getIndexGoods(ds_vt, i_CRUD)->vat_tu.maVT;
						deleteNode(ds_vt, mvt);
						goto sf_out;
					}
					else {
						goto sf_out;

					}

				}
			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_g_table.current == vp_g_table.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_g_table);
				delete_after_header();
				goods_table(sf_table_header, ds_vt, CURD_o_text, vp_g_table, edit_table_g, delete_table_g, 10);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_g_table.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_g_table);
				delete_after_header();
				goods_table(sf_table_header, ds_vt, CURD_o_text, vp_g_table, edit_table_g, delete_table_g, 10);
			}
			if (ktVT(50, 10, 250, 50, x, y) || ktVT(350, 10, 550, 50, x, y) || ktVT(650, 10, 850, 50, x, y) || ktVT(950, 10, 1150, 50, x, y)) {
				g_page = false;
				goto sf_end;
			}
		}
		delay(1);
	}
sf_out:;
	if (g_isEdit) {

		string t_mvt = getIndexGoods(ds_vt, i_CRUD)->vat_tu.maVT;
		string t_tvt = getIndexGoods(ds_vt, i_CRUD)->vat_tu.tenVT;
		string t_dvt = getIndexGoods(ds_vt, i_CRUD)->vat_tu.DVT;
		int t_slt = getIndexGoods(ds_vt,i_CRUD)->vat_tu.SLT;
		handleInfor_goods(x, y, ds_vt, t_mvt, t_tvt, t_dvt, t_slt, i_CRUD, g_isEdit, g_isAdd);
	}
	if (g_isAdd) {
		string t_add_mnt = "";
		string t_add_ho = "";
		string t_add_ten = "";
		int t_add_slt = 0;
		handleInfor_goods(x, y, ds_vt, t_add_mnt, t_add_ho, t_add_ten, t_add_slt,-1, g_isEdit, g_isAdd);
	}

sf_end:;
}