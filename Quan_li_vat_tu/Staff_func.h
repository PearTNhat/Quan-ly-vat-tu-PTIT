#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Bill_Struct.h"
#include "Staff_Struct.h";
#include "input_staff_good.h"

// lam xong delete mang
// then chuc nang tim kiem maNV
// khi k thể xoá thì k hiện yes no
// khi delete xong vẫn ở trang đó
// k co row thi se la 0/0 chu k phai la 1/0

//-------------
void create_sf_header(string title = "Danh sach nhan vien", string subTitle = "Them nhan vien");
void staff_infor(string mnv = "", string ho = "", string ten = "", string gender = "");
void delete_staff(DS_NhanVien& ds_nv, int index);
int checkSubmitEditAdd(int arr[], int n);
int search_ID_Staff(DS_NhanVien ds_nv, string ID);
//--------------
void read_file_staff(DS_NhanVien& ds_nv, DS_HoaDon& ds_hdP) {
	ifstream read_file;
	read_file.open("./Data/list_staff.txt", ios_base::in);
	NhanVien* temp;
	HoaDon* tempcthd;

	HoaDon hoadon = {};
	PTRHD ds_hoadon;
	//
	CT_HoaDon temp_cthd;
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
						hoadon.ct_hoadon = NULL;
						temp_cthd = {};
						for (int j = 0; j < stoi(sl_cthd); j++) {
							string tempct;
							read_file.getline(temp_cthd.MAVT, 11, ',');

							getline(read_file, tempct, ',');
							temp_cthd.Soluong = stoi(tempct);
							getline(read_file, tempct, ',');
							temp_cthd.Dongia = stoi(tempct);
							getline(read_file, tempct, ',');
							temp_cthd.VAT = stoi(tempct);
							if (j == stoi(sl_cthd) - 1) {
								getline(read_file, tempct, '\n');
								temp_cthd.TrangThai = stoi(tempct);
							}
							else {
								getline(read_file, tempct, ',');
								temp_cthd.TrangThai = stoi(tempct);
								read_file.ignore();
							}
							Insert_last_d(hoadon.ct_hoadon, temp_cthd);
						}

					}
				}
				temp->ds_hoadon = ds_hoadon; // them vào dshd
				ds_nv.nhan_vien[ds_nv.length++] = temp;// them vào nhân viên i
				Insert_last(ds_hoadon, hoadon);
				
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
	int numOfBill = 0;
	int numOFCTHD = 0;
	DS_HoaDon* dshd_temp;
	DS_CT_HoaDon* dscthd_temp;
	write_file.open("./Data/list_staff.txt");

	for (int i = 0; i < ds_nv.length; i++)
	{
		write_file << ds_nv.nhan_vien[i]->maNV << ",";
		write_file << ds_nv.nhan_vien[i]->ho << ",";
		write_file << ds_nv.nhan_vien[i]->ten << ",";
		write_file << ds_nv.nhan_vien[i]->phai << ",";

		write_file << endl;
		numOfBill = getNumOfBill(ds_nv.nhan_vien[i]->ds_hoadon);
		if (i == ds_nv.length - 1) {
			write_file << numOfBill;
		}
		else {
			write_file << numOfBill << endl;
		}
		for (int z = 0; z < numOfBill; z++) {
			dshd_temp = ds_nv.nhan_vien[i]->ds_hoadon;
			write_file << dshd_temp->hoadon.SoHD << ",";
			write_file << dshd_temp->hoadon.date.ngay << "/";
			write_file << dshd_temp->hoadon.date.thang << "/";
			write_file << dshd_temp->hoadon.date.nam << ",";
			if (z == numOfBill - 1) {
				write_file << dshd_temp->hoadon.Loai << "\n";

			}
			else {
				write_file << dshd_temp->hoadon.Loai << "," << endl;

			}
			numOFCTHD = getNumOfCTHD(ds_nv.nhan_vien[i]->ds_hoadon->hoadon.ct_hoadon);
			if (ds_nv.nhan_vien[i]->ds_hoadon->hoadon.ct_hoadon = NULL) {
				cout << "______NULL_____" << endl;
			}
			else {
				write_file << numOFCTHD << "\n";
			}
			for (int x = 0; x < numOFCTHD; x++) {
				dscthd_temp = dshd_temp->hoadon.ct_hoadon;
				write_file << dscthd_temp->ct_hoadon.MAVT << ',';
				write_file << dscthd_temp->ct_hoadon.Soluong << ',';
				write_file << dscthd_temp->ct_hoadon.Dongia << ',';
				write_file << dscthd_temp->ct_hoadon.VAT << ',';
				if (x == numOFCTHD - 1) {
					write_file << dscthd_temp->ct_hoadon.TrangThai << "\n";
				}
				else {
					write_file << dscthd_temp->ct_hoadon.TrangThai << "," << endl;
				}
				dscthd_temp = dscthd_temp->next;
			}

			dshd_temp = dshd_temp->next;
		}
	}
	write_file.close();

}
void create_sf_header(string title, string subTitle) {
	setfillstyle(1, bk_screen);
	setcolor(0);
	text_box(950, 70, 1150, 110, (char*)subTitle.c_str(), f_medium, 2, 10, 20, 11);
	setbkcolor(bk_screen);
	setcolor(12);
	settextstyle(f_medium, 0, 3);
	outtextxy(500, 75, (char*)title.c_str());
}
void staff_table(
	char sf_table_header[][20],
	DS_NhanVien ds, // day la danh sach cac phan tu chon kd_lieu cho phu hop
	char curd_o[][20], // "them sua xoa" // k can co the xoa
	view_page& view_page,
	check_CURD edit[],//// k can co the xoa
	check_CURD _delete[],// k can co the xoa
	int num_rows
) {
	delete_after_header();
	create_sf_header();
	// tnh so page co trong trang
	setcolor(0);
	int n = ds.length;
	int page = n / num_rows;
	int du = n % num_rows;
	view_page.page = du ? page + 1 : page;
	int max_page = n > (num_rows * view_page.current) ? (num_rows * view_page.current) : n;
	// reder page
	int i = num_rows * (view_page.current - 1);
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
	for (; i < max_page; i++)
	{
		if (i % num_rows == 0) {
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
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, ds.nhan_vien[i]->maNV, 1, 0, 3, 15);
		string fullName = ds.nhan_vien[i]->ho;

		fullName += " ";
		fullName += ds.nhan_vien[i]->ten;

		char ten[30];
		strcpy_s(ten, fullName.c_str());
		writeText(230, text_top, ten, 1, 0, 3, 15);
		writeText(650, text_top, ds.nhan_vien[i]->phai, 1, 0, 3, 15);

		//------------- k can co the xoa
		text_box(900, text_top, 978, text_top + 22, curd_o[0], f_small, 1, 1);
		text_box(995, text_top, 1038, text_top + 22, curd_o[1], f_small, 1, 1);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	_delete[0].n = d;
	edit[0].n = e;

	// < >
	page_transition(view_page);
}
void handleInfor_staff(int& x, int& y, DS_NhanVien& ds_nv, int& i_CRUD, string& t_mnv, string& t_ho, string& t_ten, string& t_gender, string func, bool& sf_isEdit, bool& sf_isAdd) {
	int checkSubmit[4];
	if (func == "add") {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = -1;
		}
	}
	if (func == "edit") {
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
					t_mnv = input(x, y, 430, 165, 800, 195, 5, 6, 5, 35, 50, t_mnv, 10, "textNumberNoSpace", "upcase", COLOR_INFOR_SG, 430, 225);
					if (search_ID_Staff(ds_nv, (string)t_mnv) == -1) {
						break;
					}
					else if (i_CRUD != ds_nv.length && ds_nv.nhan_vien[i_CRUD]->maNV == t_mnv) {
						break;

					}
					else {
						warning_msg((char*)"Ma nhan vien da ton tai.", 435, 165 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
					}
				}

				if (func == "add") {
					if (t_mnv.length() > 0) {
						checkSubmit[0] = 1;
					}
					else {
						checkSubmit[0] = -1;
					}
				}
				if (func == "edit") {
					if (t_mnv.length() == 0) {
						checkSubmit[0] = -1;
					}
					else {
						checkSubmit[0] = 1;
					}
				}
				goto headInfor;
			}
			if (ktVT(430, 225, 800, 255, x, y)) { // ho
				t_ho = input(x, y, 430, 225, 800, 255, 5, 6, 5, 35, 50, t_ho, 22, "text", "camelCase", COLOR_INFOR_SG, 430, 285);
				if (func == "add") {
					if (t_ho.length() > 0) {
						checkSubmit[1] = 1;
					}
					else {
						checkSubmit[1] = -1;
					}
				}
				if (func == "edit") {
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
				if (func == "add") {
					if (t_ten.length() > 0) {
						checkSubmit[2] = 1;
					}
					else {
						checkSubmit[2] = -1;
					}
				}
				if (func == "edit") {
					if (t_ten.length() == 0) {
						checkSubmit[2] = -1;
					}
					else {
						checkSubmit[2] = 1;
					}
				}
				goto headInfor;

			}
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
				if (checkSubmitEditAdd(checkSubmit, 4) < 4) {
					checkCancle = announce_board(x, y, 50, 0, "Ban co muon huy.", "");
				}
				if (checkCancle) {
					sf_isEdit = false;
					sf_isAdd = false;
					delay(200);
					goto sf_end;
				}
				else {
					staff_infor(t_mnv, t_ho, t_ten, t_gender);
					x = NULL, y = NULL;
					goto headInfor;
				}

			}
			//LUU
			if (ktVT(840, 420, 910, 450, x, y)) {
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
					}
					else { // edit
						strcpy_s(ds_nv.nhan_vien[i_CRUD]->maNV, t_mnv.c_str());
						strcpy_s(ds_nv.nhan_vien[i_CRUD]->ho, t_ho.c_str());
						strcpy_s(ds_nv.nhan_vien[i_CRUD]->ten, t_ten.c_str());
						strcpy_s(ds_nv.nhan_vien[i_CRUD]->phai, t_gender.c_str());
					}
					sf_isEdit = false;
					sf_isAdd = false;

					text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
					announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
					delay(500);
					write_file_staff(ds_nv);
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
void sf_handleTable(int& x, int& y, DS_NhanVien& ds_nv, check_CURD delete_sf[], check_CURD edit_sf[], view_page vp_m_sf, bool& sf_isEdit, bool& sf_isAdd) {
	bool break_all = false;
	int i_CRUD = 0;
	bool check_D_staff = true;
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// them nhan vien moi
		start_handle_staff:
			if (ktVT(950, 70, 1150, 110, x, y)) {
				staff_infor();
				sf_isAdd = true;
				goto sf_out;
			}
			// edit
			for (int i = 0; i < edit_sf[0].n; i++)
			{
				if (ktVT(edit_sf[i].l, edit_sf[i].t, edit_sf[i].r, edit_sf[i].b, x, y)) {
					i_CRUD = (vp_m_sf.current - 1) * ROW_STAFF + i;
					staff_infor(ds_nv.nhan_vien[i_CRUD]->maNV, ds_nv.nhan_vien[i_CRUD]->ho, ds_nv.nhan_vien[i_CRUD]->ten, ds_nv.nhan_vien[i_CRUD]->phai);
					sf_isEdit = true;
					goto sf_out;
				}
			}
			//delete
			for (int i = 0; i < delete_sf[0].n; i++)
			{
				if (ktVT(delete_sf[i].l, delete_sf[i].t, delete_sf[i].r, delete_sf[i].b, x, y)) {
					check_D_staff = announce_board(x, y, 40, 0, "Ban co muon xoa khong.", "");
					if (check_D_staff) {
						i_CRUD = (vp_m_sf.current - 1) * ROW_STAFF + i;
						delete_staff(ds_nv, i_CRUD);
						goto sf_out;
					}
					else {
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
				goto sf_end;
			}
		}
		delay(1);
	}
sf_out:;
	if (sf_isEdit) {

		string t_mnv = ds_nv.nhan_vien[i_CRUD]->maNV;
		string t_ho = ds_nv.nhan_vien[i_CRUD]->ho;
		string t_ten = ds_nv.nhan_vien[i_CRUD]->ten;
		string t_gender = ds_nv.nhan_vien[i_CRUD]->phai;
		handleInfor_staff(x, y, ds_nv, i_CRUD, t_mnv, t_ho, t_ten, t_gender, "edit", sf_isEdit, sf_isAdd);
	}
	cout << "______ " << sf_isAdd << endl;
	if (sf_isAdd) {
		string t_add_mnv = "";
		string t_add_ho = "";
		string t_add_ten = "";
		string t_add_gender = "";
		handleInfor_staff(x, y, ds_nv, ds_nv.length, t_add_mnv, t_add_ho, t_add_ten, t_add_gender, "add", sf_isEdit, sf_isAdd);

	}

sf_end:;
}
int checkSubmitEditAdd(int arr[], int n) {
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == -1) count++; // dem so luong k hop le

	}
	return count;
}
void staff_infor(string mnv, string ho, string ten, string gender) {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin nhan vien", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)mnv.c_str(), f_medium, 1, 6, 5, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma Nhan Vien", 2, 0, f_medium, COLOR_INFOR_SG);

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
	if (ds_nv.nhan_vien[index]->ds_hoadon == NULL) {
		for (int i = index; i < ds_nv.length - 1; i++)
		{
			ds_nv.nhan_vien[i] = ds_nv.nhan_vien[i + 1];
		}
		ds_nv.nhan_vien[ds_nv.length - 1] = new NhanVien;
		ds_nv.length--;
		write_file_staff(ds_nv);
	}
	else {
		announce_board(0, 0, 0, 0, "Khong the xoa.");
		delay(1000);
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
void sort_staff(DS_NhanVien& ds_nv) {
	string p1, p2;
	for (int i = 0; i < ds_nv.length - 1; i++)
	{
		for (int j = i + 1; j < ds_nv.length; j++)
		{
			p1 = (string)ds_nv.nhan_vien[i]->ten + (string)ds_nv.nhan_vien[i]->ho;
			p2 = (string)ds_nv.nhan_vien[j]->ten + (string)ds_nv.nhan_vien[j]->ho;
			if (p2 < p1) {
				NhanVien* temp = ds_nv.nhan_vien[j];
				ds_nv.nhan_vien[j] = ds_nv.nhan_vien[i];
				ds_nv.nhan_vien[i] = temp;
			}
		}
	}
}