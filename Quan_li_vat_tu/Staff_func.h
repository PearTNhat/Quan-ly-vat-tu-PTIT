#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Bill_Struct.h"
#include "Staff_Struct.h"
#include "input_staff_goods.h"
#include "input_one.h"
#include "Goods_Struct.h"
void create_sf_header( string subTitle = "Them nhan vien", string search = "Nhap ten hoac id can tim kiem");
#include "Search_staffs.h"
//-------------
void staff_infor(string mnv = "", string ho = "", string ten = "", string gender = "", bool isAdd = false);
void delete_staff(DS_NhanVien& ds_nv, int index);
int checkSubmitEditAdd(int arr[], int n);
int search_ID_Staff(DS_NhanVien ds_nv, string ID);
//--------------
void read_file_staff(DS_NhanVien& ds_nv) {
	ifstream read_file;
	read_file.open("./Data/list_staff.txt", ios_base::in);
	NhanVien* temp;
	HoaDon hoadon = {};
	PTRHD ds_hoadon;
	CT_HoaDon temp_cthd;
	//
	if (read_file.is_open() && read_file.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "File is empty." << std::endl;
	}
	else {
		while (!read_file.eof()) {
			temp = new NhanVien;

			ds_hoadon = NULL;
			read_file.getline(temp->maNV, 11, ',');
			read_file.getline(temp->ho, 23, ',');
			read_file.getline(temp->ten, 9, ',');
			read_file.getline(temp->phai, 4, ',');
			read_file.ignore();
			string sl_hd;

			getline(read_file, sl_hd, '\n');
			if (stoi(sl_hd) > 0) {

				for (int i = 0; i < stoi(sl_hd); i++)
				{ // doc tung hoá đơn
					read_file.getline(hoadon.SoHD, 21, ',');
					string tempDate;
					getline(read_file, tempDate, '/');
					hoadon.date.ngay = stoi(tempDate);
					getline(read_file, tempDate, '/');
					hoadon.date.thang = stoi(tempDate);
					getline(read_file, tempDate, ',');
					hoadon.date.nam = stoi(tempDate);
					if (i == stoi(sl_hd) - 1) {
						read_file.getline(hoadon.Loai, 2, '\n');
					}
					else {
						read_file.getline(hoadon.Loai, 2, ',');
						read_file.ignore();
					}
					string sl_cthd;
					getline(read_file, sl_cthd, '\n');
					if (stoi(sl_cthd) > 0) {
						hoadon.first_cthd = NULL;
						temp_cthd = {};
						for (int j = 0; j < stoi(sl_cthd); j++) {
							string tempct;
							read_file.getline(temp_cthd.MAVT, 11, ',');

							getline(read_file, tempct, ',');
							temp_cthd.Soluong = stoi(tempct);
							getline(read_file, tempct, ',');
							temp_cthd.Dongia = stoi(tempct);
							getline(read_file, tempct, ',');
							temp_cthd.VAT = stof(tempct);
							if (j == stoi(sl_cthd) - 1) {
								getline(read_file, tempct, '\n');
								int	myInt = stoi(tempct);
								temp_cthd.TrangThai = myInt != 0;
							}
							else {
								getline(read_file, tempct, ',');
								int myInt = stoi(tempct);
								temp_cthd.TrangThai = myInt != 0;
								read_file.ignore();
							}
							Insert_last_CTHD(hoadon.first_cthd, temp_cthd);
						}
					}
					Insert_last_HD(ds_hoadon, hoadon);
				}
			}
			temp->ds_hoadon = ds_hoadon;
			ds_nv.nhan_vien[ds_nv.length++] = temp;
		}
	}
	temp = NULL;
	delete temp;
	read_file.close();
}

void write_file_staff(DS_NhanVien ds_nv) {
	ofstream write_file;
	int numOfBill;
	int numOfCTHD;
	write_file.open("./Data/list_staff.txt");
	if (ds_nv.length == 0) {
		write_file << "";
	}
	else {

		for (int i = 0; i < ds_nv.length; i++)
		{
			write_file << ds_nv.nhan_vien[i]->maNV << ",";
			write_file << ds_nv.nhan_vien[i]->ho << ",";
			write_file << ds_nv.nhan_vien[i]->ten << ",";
			write_file << ds_nv.nhan_vien[i]->phai << ",";

			write_file << endl;

			if (ds_nv.nhan_vien[i]->ds_hoadon != NULL) {
				numOfBill = getNumOfBill(ds_nv.nhan_vien[i]->ds_hoadon);
			}
			else numOfBill = 0;

			if (i == ds_nv.length - 1 && numOfBill == 0) write_file << numOfBill;
			else write_file << numOfBill << endl;

			if (numOfBill > 0) {
				DS_HoaDon* nodeIt_HD = ds_nv.nhan_vien[i]->ds_hoadon;
				while (nodeIt_HD != NULL) {
					write_file << nodeIt_HD->hoadon.SoHD << ",";
					write_file << nodeIt_HD->hoadon.date.ngay << "/" << nodeIt_HD->hoadon.date.thang << "/" << nodeIt_HD->hoadon.date.nam << ",";
					if (nodeIt_HD->next != NULL) {
						write_file << nodeIt_HD->hoadon.Loai << "," << endl;
					}
					else write_file << nodeIt_HD->hoadon.Loai << endl;
					if (nodeIt_HD->hoadon.first_cthd != NULL) {
						DS_CT_HoaDon* nodeIt_CT = nodeIt_HD->hoadon.first_cthd;
						write_file << getNumOfCTHD(nodeIt_CT) << endl;
						while (nodeIt_CT != NULL) {
							write_file << nodeIt_CT->ct_hoadon.MAVT << ",";
							write_file << nodeIt_CT->ct_hoadon.Soluong << ",";
							write_file << nodeIt_CT->ct_hoadon.Dongia << ",";
							write_file << nodeIt_CT->ct_hoadon.VAT << ",";
							if (nodeIt_CT->next != NULL) {
								write_file << nodeIt_CT->ct_hoadon.TrangThai << "," << endl;
							}
							else {
								if (i == ds_nv.length - 1) write_file << nodeIt_CT->ct_hoadon.TrangThai;
								else write_file << nodeIt_CT->ct_hoadon.TrangThai << endl;
							}
							nodeIt_CT = nodeIt_CT->next;
						}
					}
					else write_file << "0" << endl;
					nodeIt_HD = nodeIt_HD->next;
				}
			}
		}
	}
	write_file.close();
}
void create_sf_header(string subTitle,string search) {
	int colorsearch = 0;
	if (search=="Nhap ten hoac id can tim kiem") {
		colorsearch =COLOR(153, 150, 150);
	}
	text_box(50, 72, 410, 108, (char*)search.c_str(), f_medium, 1, 10, 10, WHITE, colorsearch);
	setcolor(0);
	setfillstyle(1, bk_screen);
	text_box(950, 70, 1150, 110, (char*)subTitle.c_str(), f_medium,2 , 10, 20, 11);
	setbkcolor(bk_screen);
	setcolor(12);
	settextstyle(f_medium,0, 5);
}
void staff_table(
	NhanVien ** nhan_vien,
	int length,// day la danh sach cac phan tu chon kd_lieu cho phu hop
	view_page& view_page,
	check_CURD& edit,//// k can co the xoa
	check_CURD& _delete,// k can co the xoa
	int num_cols,
	string searchValue = "Nhap ten hoac id can tim kiem"
) {
	setlinestyle(0, 0, 0);
	delete_after_header();
	
	create_sf_header((string)"Them nhan vien", searchValue);
	// tnh so page co trong trang
	setcolor(0);
	int n = length;
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
	outtextxy(95, text_top, (char*)sf_table_header[0]);
	outtextxy(230, text_top, (char*)sf_table_header[1]);
	outtextxy(550, text_top, (char*)sf_table_header[2]);
	outtextxy(740, text_top, (char*)sf_table_header[3]);
	outtextxy(900, text_top, (char*)sf_table_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	for (; i < max_rows; i++)
	{
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
		if (i == max_rows - 1) {
			bar_bottom -= (max_rows - num_cols * (view_page.current - 1)) - 2;
		}
		// Neu k su dung thi xoa tu day xuong
		//vi tri edit
		edit.data[e].key =(string)nhan_vien[i]->maNV;
		edit.data[e].l = 900;
		edit.data[e].t = text_top;
		edit.data[e].r = 978;
		edit.data[e].b = text_top + 23;
		e++;
		// vi tri delete
		_delete.data[d].key = (string)nhan_vien[i]->maNV;
		_delete.data[d].l = 995;
		_delete.data[d].t = text_top;
		_delete.data[d].r = 1038;
		_delete.data[d].b = text_top + 23;
		d++;
		// --------------------------------- xuong day

		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, nhan_vien[i]->maNV, 1, 0, 3, 15);
	
		writeText(230, text_top, nhan_vien[i]->ho, 1, 0, 3, 15);
		writeText(550, text_top, nhan_vien[i]->ten, 1, 0, 3, 15);
		writeText(740, text_top, nhan_vien[i]->phai, 1, 0, 3, 15);

		//------------- k can co the xoa
		text_box(900, text_top, 978, text_top + 23, (char*)CURD_o_text[0], f_small, 1, 1, 2);
		text_box(995, text_top, 1038, text_top + 23, (char*)CURD_o_text[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete.n = d;
	edit.n = e;

	// < >
	page_transition(view_page);
}
bool handleInfor_staff(int& x, int& y, DS_NhanVien& ds_nv, templeDynamicArray<NhanVien> &fillter_nv, int& i_CRUD, string& t_mnv, string& t_ho, string& t_ten, string& t_gender, bool& sf_isEdit, bool& sf_isAdd,string e_search="") {
start:;
	int checkSubmit[4];
	bool isBack = false;
	if (sf_isAdd) {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = -1;
		}
	}
	if (sf_isEdit) {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = 1;
		}
		text_box(430, 165, 800, 195, (char*)t_mnv.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mnv
	}
	bool checkCancle = true;
	bool checkBreak = false;
	while (1) { 
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
		headInfor:;
			if (sf_isEdit) {
				text_box(430, 165, 800, 195, (char*)t_mnv.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mnv
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
					sf_isEdit = false;
					sf_isAdd = false;
					return true;
				}
				staff_infor(t_mnv, t_ho, t_ten, t_gender,sf_isAdd);
				if (sf_isEdit) {
				text_box(430, 165, 800, 195, (char*)t_mnv.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mnv
				}
				x = NULL, y = NULL;
				goto headInfor;

			}
			if (ktVT(820, 165, 920, 195, x, y) && sf_isAdd) {
				delete_after_header();
				table_searching(x, y, ds_nv);
				staff_infor(t_mnv, t_ho, t_ten, t_gender, sf_isAdd);
				goto headInfor;
			}
			if (ktVT(430, 165, 800, 195, x, y) || isBack) { // MNV

				if (sf_isAdd) {
					if (isBack == false) {
						t_mnv = input(x, y, 430, 165, 800, 195, 5, 6, 5, 35, 50, t_mnv, 10, "textNumberNoSpace", "upcase", COLOR_INFOR_SG, 430, 225);
					}
					if (search_ID_Staff(ds_nv, (string)t_mnv) != -1) {
						checkSubmit[0] = -2;
						warning_msg((char*)"Ma nhan vien da ton tai.", 435, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					else if (t_mnv.length() > 0) {
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
			if (ktVT(430, 225, 800, 255, x, y)) { // ho
				t_ho = input(x, y, 430, 225, 800, 255, 5, 6, 5, 35, 50, t_ho, 22, "text", "camelCase", COLOR_INFOR_SG, 430, 285);
				if (sf_isAdd) {
					if (t_ho.length() > 0) {
						checkSubmit[1] = 1;
					}
					else {
						checkSubmit[1] = -1;
					}
				}
				if (sf_isEdit) {
					if (t_ho.length() == 0) {
						checkSubmit[1] = -1;
					}
					else {
						checkSubmit[1] = 1;
					}
				}
				goto headInfor;

			}
			if (ktVT(430, 285, 800, 315, x, y)) { // ten
				t_ten = input(x, y, 430, 285, 800, 315, 5, 6, 5, 35, 50, t_ten, 8, "textNoSpace", "camelCase", COLOR_INFOR_SG, 430, 345);
				if (x==430 && y==345) {
					x = 430; y = 345;
					if (t_gender == "Nu" ) {
						x = 560;
					}
				}
				if (sf_isAdd) {
					if (t_ten.length() > 0) {
						checkSubmit[2] = 1;
					}
					else {
						checkSubmit[2] = -1;
					}
				}
				if (sf_isEdit) {
					if (t_ten.length() == 0) {
						checkSubmit[2] = -1;
					}
					else {
						checkSubmit[2] = 1;
					}
				}
				goto headInfor;

			}
			isBack = false;
			// nam
			if (ktVT(430, 345, 530, 375, x, y)) {
				setfillstyle(1, COLOR_INFOR_SG);
				bar(435, 385, 850, 385 + 25);
				t_gender = "Nam";
				checkSubmit[3] = 1;
				text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5, 30, XANH_LA_CAY, 0);
				text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, 15, 0);

			}
			// nu
			if (ktVT(560, 345, 660, 375, x, y)) {
				setfillstyle(1, COLOR_INFOR_SG);
				bar(435, 385, 850, 385 + 25);
				t_gender = "Nu";
				checkSubmit[3] = 1;
				text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5, 30, 15, 0);
				text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, XANH_LA_CAY, 0);
			}
			//HUY
			if (ktVT(750, 420, 820, 450, x, y)) {
				text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				if (t_gender != "" || t_ten != "" || t_ho != "" || t_mnv != "") {
					checkCancle = announce_board(x, y, 50, 0, "Ban co muon huy.", "");
					if (checkCancle) {
						sf_isEdit = false;
						sf_isAdd = false;
						delay(200);
						goto sf_end;
					}
					else {
						staff_infor(t_mnv, t_ho, t_ten, t_gender,sf_isAdd);
						isBack = true;
						x = NULL, y = NULL;
						goto headInfor;
					}
				}
				sf_isEdit = false;
				sf_isAdd = false;
				goto sf_end;
				

			}
			//LUU
			if (ktVT(840, 420, 910, 450, x, y)) {
				text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				delay(200);
				text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);
				if (checkSubmitEditAdd(checkSubmit, 4) == 0) {
					if (sf_isAdd) { //add
						NhanVien* nv_temp = new NhanVien;
						nv_temp->ds_hoadon = NULL;
						strcpy_s(nv_temp->maNV, t_mnv.c_str());
						strcpy_s(nv_temp->ho, t_ho.c_str());
						strcpy_s(nv_temp->ten, t_ten.c_str());
						strcpy_s(nv_temp->phai, t_gender.c_str());
						insertOrderd_Staff(ds_nv, nv_temp);
						ds_nv.length++;

						announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
						write_file_staff(ds_nv);
						delay(500);
						x = NULL, y = NULL;
						staff_infor("","","","", sf_isAdd);
						t_gender = t_ho = t_mnv = t_ten = "";
						write_file_staff(ds_nv);
						goto start;
					}
					else { // edit
						cout << fillter_nv.size_current << endl;
						for (int i = 0; i < ds_nv.length; i++)
						{
							if ((string)fillter_nv.a[i_CRUD]->maNV== (string)ds_nv.nhan_vien[i]->maNV) {
								strcpy_s(ds_nv.nhan_vien[i]->ho, t_ho.c_str());
								strcpy_s(ds_nv.nhan_vien[i]->ten, t_ten.c_str());
								strcpy_s(ds_nv.nhan_vien[i]->phai, t_gender.c_str());
								break;
							}
						}
					}

					text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
					announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
					write_file_staff(ds_nv);
					delay(500);
					sf_isEdit = false;
					sf_isAdd = false;
					goto sf_end;
				}
				else {
					int left_error = 630;
					if (checkSubmit[0] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
					if (checkSubmit[0] == -2) {
						warning_msg("Ma nhan vien da ton tai", 430 + 5, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
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
	return false;
}
bool sf_handleTable(int& x, int& y,DS_NhanVien& ds_nv, check_CURD delete_sf, check_CURD edit_sf, view_page& vp_m_sf, bool& sf_isEdit, bool& sf_isAdd,string &e_search) {
	// sua lai table nhan vien chua hop le
	bool break_all = false;
	int i_CRUD = 0;
	bool check_D_staff = true;
	bool checkX = false;
	int svt_NULL = 0;
	int search_empty = 0;
	string placeholder = e_search == "" ? "Nhap ten hoac id can tim kiem" : e_search;
	templeDynamicArray<NhanVien> fillter_nv(ds_nv.length);
	search_staffs(ds_nv, fillter_nv, e_search);
	staff_table(fillter_nv.a, fillter_nv.size_current, vp_m_sf, edit_sf, delete_sf, 10);
	if (placeholder.length() > 0) {
		create_sf_header((string)" Them nhan vien", placeholder);
	}
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			//search
			if (ktVT(50, 72, 410, 108, x, y)) {// search
				while (1) {
					e_search = input_one(x, y, 50, 72, 410, 108, 10, 10, e_search, 30);
					placeholder = e_search;
					if (!ktVT(50, 72, 410, 108, x, y)) {
						if (e_search == "") {
							create_sf_header( (string)"Them nhan vien", (string)"Nhap ten hoac id can tim kiem");
						}
						break;
					}
					
					fillter_nv.size_current = 0;
					search_staffs(ds_nv, fillter_nv, e_search);
					if (e_search == "") {
						search_empty++;
					}
					else {
						search_empty = 0;
					}
					if (fillter_nv.size_current == 0) {
						svt_NULL++;
					}
					else {
						svt_NULL = 0;
					}
					if (svt_NULL == 1 || search_empty == 1 || (search_empty == 0 && svt_NULL == 0)) {
						staff_table(fillter_nv.a, fillter_nv.size_current, vp_m_sf, edit_sf, delete_sf, 10,e_search);
					}
					delay(1);
				}

			}
			// them nhan vien moi
			if (ktVT(950, 70, 1150, 110, x, y)) {
				sf_isAdd = true;
				staff_infor("","","","", sf_isAdd);
				goto sf_out;
			}
			if (ktVT(1140, 10, 1190, 50, x, y)) {
				return false;
			}
			// edit
			for (int i = 0; i < edit_sf.n; i++)
			{
				if (ktVT(edit_sf.data[i].l, edit_sf.data[i].t, edit_sf.data[i].r, edit_sf.data[i].b, x, y)) {
					i_CRUD = (vp_m_sf.current - 1) * ROW_STAFF + i;
					text_box(edit_sf.data[i].l, edit_sf.data[i].t, edit_sf.data[i].r, edit_sf.data[i].b, (char*)"Chinh sua", f_small, 1, 1, 2, XANH_LA_CAY, 0);
					delay(200);
					staff_infor(fillter_nv.a[i_CRUD]->maNV, fillter_nv.a[i_CRUD]->ho, fillter_nv.a[i_CRUD]->ten, fillter_nv.a[i_CRUD]->phai);
					sf_isEdit = true;
					goto sf_out;
				}
			}
			//delete
			for (int i = 0; i < delete_sf.n; i++)
			{
				if (ktVT(delete_sf.data[i].l, delete_sf.data[i].t, delete_sf.data[i].r, delete_sf.data[i].b, x, y)) {
					i_CRUD = (vp_m_sf.current - 1) * ROW_STAFF + i;
					text_box(delete_sf.data[i].l, delete_sf.data[i].t, delete_sf.data[i].r, delete_sf.data[i].b, (char*)"Xoa", f_small, 1, 1, 6, XANH_LA_CAY, 0);
					delay(200);
					if (fillter_nv.a[i_CRUD]->ds_hoadon == NULL) {
						check_D_staff = announce_board(x, y, 40, 0, "Ban co muon xoa khong.", "");
						if (check_D_staff) {
							delete_staff(ds_nv, i_CRUD);
							goto sf_out;
						}
						goto sf_out;
					}
					else {
						announce_board(0, 0, 0, 0, "Nhan vien dang quan li hoa don khong the xoa.");
						delay(1500);
						goto sf_out;
					}

				}
			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_m_sf.current == vp_m_sf.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_m_sf);
				delete_after_header();
				staff_table(fillter_nv.a, fillter_nv.size_current, vp_m_sf, edit_sf, delete_sf, ROW_STAFF,placeholder);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_m_sf.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_m_sf);
				delete_after_header();
				staff_table(fillter_nv.a, fillter_nv.size_current, vp_m_sf, edit_sf, delete_sf, ROW_STAFF, placeholder);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x,y)) {
				sf_page = false;
				goto sf_end;
			}
		}
		delay(1);
	}
sf_out:;
	if (sf_isEdit) {
		string t_mnv = fillter_nv.a[i_CRUD]->maNV;
		string t_ho = fillter_nv.a[i_CRUD]->ho;
		string t_ten = fillter_nv.a[i_CRUD]->ten;
		string t_gender = fillter_nv.a[i_CRUD]->phai;
		checkX=handleInfor_staff(x, y, ds_nv, fillter_nv,i_CRUD, t_mnv, t_ho, t_ten, t_gender,  sf_isEdit, sf_isAdd);
	}
	if (sf_isAdd) {
		string t_add_mnv = "";
		string t_add_ho = "";
		string t_add_ten = "";
		string t_add_gender = "";
		checkX=handleInfor_staff(x, y, ds_nv, fillter_nv,ds_nv.length, t_add_mnv, t_add_ho, t_add_ten, t_add_gender, sf_isEdit, sf_isAdd,e_search);

	}
	delete[]fillter_nv.a;
	fillter_nv.a = nullptr;
	//checkX == true la break ngay lap luc
	if (checkX) {
		return false; // cho break ra ngoai// khong lap lai nua
	}
sf_end:;
	return true;
}
int checkSubmitEditAdd(int arr[], int n) {
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < 0) count++; // dem so luong k hop le

	}
	return count;
}
void staff_infor( string mnv, string ho, string ten, string gender, bool isAdd) {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin nhan vien", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)mnv.c_str(), f_medium, 1, 6, 5, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma Nhan Vien", 2, 0, f_medium, COLOR_INFOR_SG);
	if (isAdd) {
	text_box(820, 165, 920, 195, (char*)"Xem bang", f_medium, 1, 6, 5, 15, 0);

	}
	text_box(430, 225, 800, 255, (char*)ho.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 230, (char*)"Ho", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, (char*)ten.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 290, (char*)"Ten", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"Phai", 2, 0, f_medium, COLOR_INFOR_SG);
	int highlightWoman = 15, highlightMan = 15;
	if (string(gender) == "Nam") {
		highlightMan = XANH_LA_CAY;
	}
	else if (string(gender) == "Nu") {
		highlightWoman = XANH_LA_CAY;
	}
	text_box(430, 345, 530, 375, (char*)"Nam", f_medium, 2, 5, 30, highlightMan, 0);
	text_box(560, 345, 660, 375, (char*)"Nu", f_medium, 2, 5, 35, highlightWoman, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}
void delete_staff(DS_NhanVien& ds_nv, int index) {
	if (ds_nv.length>0) {
		for (int i = index; i < ds_nv.length - 1; i++)
		{
			ds_nv.nhan_vien[i] = ds_nv.nhan_vien[i + 1];
		}
		ds_nv.nhan_vien[ds_nv.length - 1]=nullptr;
		ds_nv.length--;
		write_file_staff(ds_nv);
	}
	else {
		cout << "Mang rong k the xoa";
	}
}
int search_ID_Staff(DS_NhanVien ds_nv, string ID) {

	for (int i = 0; i < ds_nv.length; i++)
	{
		if (ID == ds_nv.nhan_vien[i]->maNV) {
			return i;
		}
	}
	return -1;
}
void swapStaff(NhanVien *&n1, NhanVien *&n2) {
	NhanVien *temp = n1;
	n1 = n2;
	n2 = temp;
}
void quick_sort_staff(DS_NhanVien& ds_nv,int left,int right) {
	int l = left, r = right;
	int piviot = (l + r) / 2;
	string p1, p2,target;
	do {
		while (
			((string)ds_nv.nhan_vien[l]->ten + (string)ds_nv.nhan_vien[l]->ho)
			<
			((string)ds_nv.nhan_vien[piviot]->ten + (string)ds_nv.nhan_vien[piviot]->ho)
			) 
		{
			l++;
		}
		while (
			((string)ds_nv.nhan_vien[r]->ten + (string)ds_nv.nhan_vien[r]->ho)
			>
			((string)ds_nv.nhan_vien[piviot]->ten + (string)ds_nv.nhan_vien[piviot]->ho)
			)
		{
			r--;
		}
		if (l<= r) {
			swapStaff(ds_nv.nhan_vien[l], ds_nv.nhan_vien[r]);
			l++;
			r--;
		}
	} while (l <= r);
	if (l<right) {
		quick_sort_staff(ds_nv, l, right);
	}
	if (r>left) {
		quick_sort_staff(ds_nv, left, r);

	}

}