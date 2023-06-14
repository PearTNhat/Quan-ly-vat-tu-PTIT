#pragma once
#include "Staff_func.h"
#include "input_one.h"
#include "Search_Goods.h"
#define COLS_G 10
//
void create_g_header();
void goods_infor(string mvt = "", string tvt = "", string dvt = "", string slt = "");
//
void create_g_header() {
	setfillstyle(1, 15);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);
	text_box(15, 70, 310, 110, (char*)"", f_medium, 3, 10, 40, bk_screen);
	text_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 10, 40, bk_screen);
}
//
void read_file_goods(DS_VatTu*& ds_vt) {
	VatTu temp_vt;
	string t_tt = "";
	ifstream readFile("./Data/goods.txt");
	if (readFile.is_open() && readFile.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "File is empty." << std::endl;
	}
	else {
		while (!readFile.eof()) {
			readFile.getline(temp_vt.maVT, 11, ',');
			readFile.getline(temp_vt.tenVT, 26, ',');
			readFile.getline(temp_vt.DVT, 7, ',');
			getline(readFile, t_tt, ',');
			temp_vt.sldaban = stoi(t_tt);
			readFile >> temp_vt.SLT;
			readFile.ignore();
			insertNode_k_maVT(ds_vt, temp_vt);
		}
	}
	readFile.close();
}
void asign_LNR_Goods(DS_VatTu* ds_vt, templeDynamicArray<DS_VatTu>& arrGoods, int& k) {
	if (ds_vt != NULL) {
		asign_LNR_Goods(ds_vt->left, arrGoods, k);
		arrGoods.a[k++] = ds_vt;
		asign_LNR_Goods(ds_vt->right, arrGoods, k);
	}
}
void selectMiddle(templeDynamicArray<DS_VatTu> arr, int l, int r, ofstream& writeFile, string mvt) {
	int middle = (l + r) / 2;
	if (l <= r) {
		writeFile << arr.a[middle]->vat_tu.maVT << ",";
		writeFile << arr.a[middle]->vat_tu.tenVT << ",";
		writeFile << arr.a[middle]->vat_tu.DVT << ",";
		writeFile << int(arr.a[middle]->vat_tu.sldaban) << ",";
		if (mvt == (string)arr.a[middle]->vat_tu.maVT) {
			writeFile << arr.a[middle]->vat_tu.SLT;
		}
		else {
			writeFile << arr.a[middle]->vat_tu.SLT << endl;
		}
		selectMiddle(arr, l, middle - 1, writeFile, mvt);
		selectMiddle(arr, middle + 1, r, writeFile, mvt);
	}
}
void write_file_goods(DS_VatTu* ds_vt) {
	int k = 0;
	int size = getSizeGoods(ds_vt);
	templeDynamicArray<DS_VatTu> arrGoods(size);
	ofstream writeFile("./Data/goods.txt");
	if (size == 0) {
		writeFile << "";
	}
	else {
		asign_LNR_Goods(ds_vt, arrGoods, k);
		string mvt = getIndexGoods(ds_vt, getSizeGoods(ds_vt))->vat_tu.maVT;
		selectMiddle(arrGoods, 0, arrGoods.capacity - 1, writeFile, mvt);
		delete[]arrGoods.a;
	}
}

void goods_infor(string mvt, string tvt, string dvt, string slt) {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin vat tu", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)mvt.c_str(), f_medium, 1, 6, 5, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma vat tu", 2, 0, f_medium, COLOR_INFOR_SG);
	text_box(820, 165, 920, 195, (char *)"Xem bang", f_medium, 1, 6, 5, 15, 0);

	

	text_box(430, 225, 800, 255, (char*)tvt.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 230, (char*)"Ten vat tu", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, (char*)dvt.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 290, (char*)"Don vi tinh", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"So luong ton", 2, 0, f_medium, COLOR_INFOR_SG);
	text_box(430, 345, 800, 375, (char*)slt.c_str(), f_medium, 1, 6, 5, 15, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}
void goods_table(
	DS_VatTu* ds_vt,
	DS_s_VT* ds_s_vt,
	view_page& view_page,
	check_CURD& edit,
	check_CURD& _delete,
	int num_cols,
	string searchValue="Nhap ten hoac id can tim kiem"
) {
	setlinestyle(0, 0, 0);
	delete_after_header();
	create_sf_header( (string)" Them vat tu", searchValue);
	// tnh so page co trong trang
	setcolor(0);
	int n = getSize_s_VT(ds_s_vt);
	int page = n / num_cols;
	int du = n % num_cols;
	view_page.page = du ? page + 1 : page;
	
	if (n == 0) {
		view_page.page = 1;
	}
	if (view_page.current > view_page.page) {
		view_page.current--;
	}
	int max_rows = n > (num_cols * view_page.current) ? (num_cols * view_page.current) : n;
	// reder page
	int i = num_cols * (view_page.current - 1);
	//header
	int bar_top = 120, bar_bottom = 155;
	int text_top = 127;
	setfillstyle(1, COLOR_HEADER_TABLE);
	setbkcolor(COLOR_HEADER_TABLE);
	settextstyle(f_small, 0, 1);
	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(95, text_top, (char *)g_table_header[0]);
	outtextxy(230, text_top, (char*)g_table_header[1]);
	outtextxy(450, text_top, (char*)g_table_header[2]);
	outtextxy(650, text_top, (char*)g_table_header[3]);
	outtextxy(900, text_top, (char*)g_table_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	s_VT temp;
	VatTu tempVT;
	for (; i < max_rows; i++)
	{
		temp = getNodeByIndex_s_VT(ds_s_vt, i + 1)->vat_tu;
		tempVT = getNodebyId_maVT(ds_vt, (string)temp.maVT)->vat_tu;
		if (i % num_cols == 0) {
			bar_top += 35;
			bar_bottom += 40;
			text_top += 40;
		}
		else {
			bar_top += 39;
			bar_bottom += 40;
			text_top += 39;
		}
		if (i == max_rows - 1) { //
			bar_bottom -= (max_rows - num_cols * (view_page.current - 1)) - 2;
		}
		// Neu k su dung thi xoa tu day xuong
		//vi tri edit
		edit.data[e].key = tempVT.maVT;
		edit.data[e].l = 900;
		edit.data[e].t = text_top - 2;
		edit.data[e].r = 978;
		edit.data[e].b = text_top + 23;
		e++;
		// vi tri delete
		_delete.data[d].key = tempVT.maVT;
		_delete.data[d].l = 995;
		_delete.data[d].t = text_top - 2;
		_delete.data[d].r = 1038;
		_delete.data[d].b = text_top + 23;
		d++;
		// --------------------------------- xuong day

		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[COLS_G];
		strcpy_s(stt,to_string(i + 1).c_str());
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, tempVT.maVT, 1, 0, 3, 15);
		writeText(230, text_top, tempVT.tenVT, 1, 0, 3, 15);
		writeText(450, text_top, tempVT.DVT, 1, 0, 3, 15);

		writeText(650, text_top, (char*)to_string(tempVT.SLT).c_str(), 1, 0, 3, 15);

		//------------- k can cos the xoa
		text_box(900, text_top - 2, 978, text_top + 23, (char*)CURD_o_text[0], f_small, 1, 1, 2);
		text_box(995, text_top - 2, 1038, text_top + 23, (char*)CURD_o_text[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete.n = d;
	edit.n = e;

	// < >
	page_transition(view_page);

}
bool handleInfor_goods(int& x, int& y, DS_VatTu*& ds_vt, DS_s_VT*& ds_s_vt, string& t_mvt, string& t_tvt, string& t_dvt, string& t_slt, string keyCRUD, bool& isEdit, bool& isAdd) {
start:;
	int isBack = false;// lúc bấm huỷ trong trở về vẫn còn báo lỗi
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
		text_box(430, 165, 800, 195, (char*)t_mvt.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mvt

		text_box(430, 345, 800, 375, (char*)t_slt.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); //slt
	}
	bool checkCancle = true;
	bool checkBreak = false;
	
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
		headInfor:;
			if (isEdit) {
				text_box(430, 165, 800, 195, (char*)t_mvt.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mvt

				text_box(430, 345, 800, 375, (char*)t_slt.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); //slt
			}
			if (
				ktVT(20, 10, 220, 50, x, y)
				|| ktVT(320, 10, 520, 50, x, y)
				|| ktVT(620, 10, 820, 50, x, y)
				|| ktVT(920, 10, 1120, 50, x, y)
				|| ktVT(1140, 10, 1190, 50, x, y)
				)
			{
				checkBreak = announce_board(x, y, 40, 0, "Ban co muon huy khong.", "");
				if (checkBreak) {
					isEdit = false;
					isAdd = false;
					return true;
				}
				goods_infor(t_mvt, t_tvt, t_dvt, t_slt);
				x = NULL, y = NULL;
				isBack = true;
				goto headInfor;
			}
			if (ktVT(820, 165, 920, 195, x, y)) { // xem bang
				x = 0; y = 0;
				search_goods_I(x, y, ds_vt);
				goods_infor(t_mvt, t_tvt, t_dvt, t_slt);
				goto headInfor;
			}
			if (isAdd) {
				// vi tri input
				if (ktVT(430, 165, 800, 195, x, y) || isBack ) { // Mvt
					if (isBack == false) {
						t_mvt = input(x, y, 430, 165, 800, 195, 5, 6, 5, 35, 50, t_mvt, 10, "textNumberNoSpace", "upcase", COLOR_INFOR_SG, 430, 225);
					}
					if (searchNode_k_maVT(ds_vt, t_mvt) == 1) {
						checkSubmit[0] = -2;
						warning_msg((char*)"Ma vat tu da ton tai.", 435, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					else if (t_mvt.length() > 0) {
						checkSubmit[0] = 1;
					}
					else {
						checkSubmit[0] = -1;
					}
					if (isBack == false) {
						goto headInfor;
					}
				}
			}
			// vi tri input
			if (ktVT(430, 225, 800, 255, x, y) || isBack ) { // ten vat tu
				
				if (isBack == false) {
					t_tvt = input(x, y, 430, 225, 800, 255, 5, 6, 5, 35, 50, t_tvt, 25, "text", "firstCase", COLOR_INFOR_SG, 430, 285);
				}
				if (isAdd) {
					if (t_tvt.length() > 0) {
						checkSubmit[1] = 1;
					}
					else if (t_tvt.length() == 0) {
						checkSubmit[1] = -1;
					}
					if (check_tvt_k_id(ds_vt, t_tvt) == 1) {
						warning_msg((char*)"Ten vat tu da ton tai.", 435,225 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
						checkSubmit[1] = -2;
					}
				}
				if (isEdit) {
					string test_tvt = getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu.tenVT;
					if (((string)t_tvt != test_tvt) && check_tvt_k_id(ds_vt, t_tvt) == 1) {
						warning_msg((char*)"Ten vat tu da ton tai.", 435, 225 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
						checkSubmit[1] = -2;
					}
					else if (t_tvt.length() == 0) {
						checkSubmit[1] = -1;
					}
					else {
						checkSubmit[1] = 1;
					}
				}
				if (isBack == false) {
					goto headInfor;
				}

			}
			if (ktVT(430, 285, 800, 315, x, y)) { // dvt
				t_dvt = input(x, y, 430, 285, 800, 315, 5, 6, 5, 35, 50, t_dvt, 6, "textNoSpace", "camelCase", COLOR_INFOR_SG, 430, 345);

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
			if (isAdd) {
				if (ktVT(430, 345, 800, 375, x, y)) {
					t_slt = input(x, y, 430, 345, 800, 375, 5, 6, 5, 35, 50, t_slt, 5, "number","formatNumber", COLOR_INFOR_SG, NULL, NULL);
					if (t_slt.length() > 0) {
						checkSubmit[3] = 1;
					}
					else {
						checkSubmit[3] = -1;
					}
					goto headInfor;

				}

			}
			isBack = false;

			//HUY
			if (ktVT(750, 420, 820, 450, x, y)) {
				text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				delay(200);
				text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);

				if (t_mvt != "" || t_tvt != "" || t_dvt != "" || t_slt != "") {
					checkCancle = announce_board(x, y, 50, 0, "Ban co muon huy.", "");
					if (checkCancle) {
						isEdit = false;
						isAdd = false;
						delay(200);
						goto sf_end;
					}
					else {
						goods_infor(t_mvt, t_tvt, t_dvt, t_slt);
						x = NULL, y = NULL;
						isBack = true;
						goto headInfor;
					}
				}
				isAdd = false;
				isEdit = false;
				goto sf_end;
			}
			//LUU
			if (ktVT(840, 420, 910, 450, x, y)) {
				text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				delay(200);
				text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);
				if (checkSubmitEditAdd(checkSubmit, 4) == 0) {
					VatTu vt_temp;
					if (isAdd) {
						vt_temp = {};
						strcpy_s(vt_temp.maVT, t_mvt.c_str());
						strcpy_s(vt_temp.tenVT, t_tvt.c_str());
						strcpy_s(vt_temp.DVT, t_dvt.c_str());
						vt_temp.SLT = stoi(t_slt);
						vt_temp.sldaban = 0;
						insertNode_k_maVT(ds_vt, vt_temp);
						announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
						delay(500);
						goods_infor();
						x = NULL, y = NULL;
						t_mvt = t_dvt = t_slt = t_tvt = "";
						write_file_goods(ds_vt);
						goto start;
					}
					if (isEdit) {
						vt_temp = {};
						strcpy_s(vt_temp.maVT, t_mvt.c_str());
						strcpy_s(vt_temp.tenVT, t_tvt.c_str());
						strcpy_s(vt_temp.DVT, t_dvt.c_str());
						vt_temp.SLT = stoi(t_slt);
						getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu = vt_temp;
				
					}
					isEdit = false;
					isAdd = false;
					write_file_goods(ds_vt);
					announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
					delay(500);
					goto sf_end;

				}
				else {
					int left_error = 630;
					if (checkSubmit[0] == -1) {
						warning_msg("Khong duoc de trong", 435, 165 + 30 + 5, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					if (checkSubmit[0] == -2) {
						warning_msg("Ma vat tu da ton tai", 435, 165 + 30 + 5, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					if (checkSubmit[1] == -1) {
						warning_msg("Khong duoc de trong", 435, 225 + 30 + 5, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					if (checkSubmit[1] == -2) {
						warning_msg("Ten vat tu da ton tai", 435, 225 + 30 + 5, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					if (checkSubmit[2] == -1) {
						warning_msg("Khong duoc de trong", 435, 285 + 30 + 5, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[3] == -1) {
						warning_msg("Khong duoc de trong", 435, 350 + 30, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
				}
			}

		}
		delay(1);
	}
sf_end:;
	return false;
}
bool g_handleTable(int& x, int& y, DS_VatTu*& ds_vt, DS_s_VT*& ds_s_vt, check_CURD& delete_table_g, check_CURD& edit_table_g, view_page& vp_g_table, bool& g_isEdit, bool& g_isAdd,string &e_search) {
	bool check_D_staff = true;
	string keyCRUD = ""; // vị trí để CRUD
	bool checkX = false; // thoát
	int svt_NULL = 0;
	int search_empty = 0;
	string placeholder = e_search=="" ? "Nhap ten hoac id can tim kiem": e_search;
	search_goods(ds_vt, ds_s_vt, e_search);
	goods_table(ds_vt, ds_s_vt, vp_g_table, edit_table_g, delete_table_g, 10);
	if (placeholder.length() > 0) {
		create_sf_header((string)" Them vat tu", placeholder);
	}
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (ktVT(50, 72, 410, 108, x, y)) {// search
				while (1) {
					e_search = input_one(x, y, 50, 72, 410, 108, 10, 10, e_search, 25);
					if (!ktVT(50, 72, 410, 108, x, y)) {
						if (e_search == "") {
							placeholder = "Nhap ten hoac id can tim kiem";
							create_sf_header( (string)" Them vat tu", placeholder);
						}
						break;
					}
					placeholder = e_search;
					deleteTree(ds_s_vt);
					ds_s_vt = NULL;
					search_goods(ds_vt, ds_s_vt, e_search);
					if (e_search == "") { // "" 1 lần search
						search_empty++;
					}
					else {
						search_empty = 0;
					}
					if (ds_s_vt == NULL) { // NULL 1 lần là search
						svt_NULL++;
					}
					else {
						svt_NULL = 0;
					}
					if (svt_NULL == 1 || search_empty == 1 || (search_empty == 0 && svt_NULL == 0)) {
						goods_table(ds_vt, ds_s_vt, vp_g_table, edit_table_g, delete_table_g, 10, placeholder);
					}
					delay(1);
				}
			}
			// them nhan vien moi
			if (ktVT(950, 70, 1150, 110, x, y)) { // them vat tu
				g_isAdd = true;
				goods_infor();
				goto sf_out;
			}
			// edit
			for (int i = 0; i < edit_table_g.n; i++)
			{
				if (ktVT(edit_table_g.data[i].l, edit_table_g.data[i].t, edit_table_g.data[i].r, edit_table_g.data[i].b, x, y)) {
					keyCRUD = edit_table_g.data[i].key;
					VatTu temp;
					temp = getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu;
					// k can edit cây tạm vì lúc search lại là oke rồi
					text_box(edit_table_g.data[i].l, edit_table_g.data[i].t, edit_table_g.data[i].r, edit_table_g.data[i].b, (char*)"Chinh sua", f_small, 1, 1, 2, XANH_LA_CAY, 0);
					delay(200);
					goods_infor(temp.maVT, temp.tenVT, temp.DVT, to_string(temp.SLT));
					g_isEdit = true;
					goto sf_out;
				}
			}
			if (ktVT(1140, 10, 1190, 50, x, y)) {
				return false;
			}
			//delete
			for (int i = 0; i < delete_table_g.n; i++)
			{
				if (ktVT(delete_table_g.data[i].l, delete_table_g.data[i].t, delete_table_g.data[i].r, delete_table_g.data[i].b, x, y)) {
					keyCRUD = delete_table_g.data[i].key;
					VatTu x_vt = getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu;
					if (x_vt.sldaban > 0) {
						announce_board(0, 0, 0, 0, "Vat tu nay dang o trong hoa don khong the xoa.");
						delay(1200);
					}
					else {
						check_D_staff = announce_board(x, y, 40, 0, "Ban co muon xoa khong.", "");
						if (check_D_staff) {
							deleteNode_k_maVT(ds_vt, x_vt.maVT);
							// k can xoa cây tạm vì lúc search lại là oke rồi
							write_file_goods(ds_vt);
						}
					}
					goto sf_out;
				}
			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_g_table.current == vp_g_table.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_g_table);
				delete_after_header();
				goods_table(ds_vt, ds_s_vt, vp_g_table, edit_table_g, delete_table_g, 10, placeholder);

			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_g_table.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_g_table);
				delete_after_header();
				goods_table(ds_vt, ds_s_vt, vp_g_table, edit_table_g, delete_table_g, 10, placeholder);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y)) {
				g_page = false;
				goto sf_end;
			}
			delay(1);
		}
	}
sf_out:;
	if (g_isEdit) {
		VatTu temp = getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu;
		string t_mvt = temp.maVT;
		string t_tvt = temp.tenVT;
		string t_dvt = temp.DVT;
		int slt = temp.SLT;
		string t_slt = to_string(slt);
		checkX = handleInfor_goods(x, y, ds_vt, ds_s_vt, t_mvt, t_tvt, t_dvt, t_slt, keyCRUD, g_isEdit, g_isAdd);
	}
	if (g_isAdd) {
		string t_add_mnt = "";
		string t_add_ho = "";
		string t_add_ten = "";
		string t_add_slt = "";
		checkX = handleInfor_goods(x, y, ds_vt, ds_s_vt, t_add_mnt, t_add_ho, t_add_ten, t_add_slt, "", g_isEdit, g_isAdd);
	}
	deleteTree(ds_s_vt);
	ds_s_vt = NULL;
	if (checkX) { // return false de cho no chay xuong duoi
		return false;
	}
sf_end:;
	return true;
}
