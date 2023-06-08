#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Bill_Struct.h"
#include "input_bill.h"
#include "Staff_func.h"
#include "Goods_Func.h"
#include "input_one.h"


char table_in_HD_header[][20] = { "Ten vat tu", "So luong", "Don gia", "%VAT", "Trang Thai", "Thanh tien (VND)" };

void highlight_box_b(int l, int t, int r, int b, char s[], int font, int f_size, int kct, int kcl, int bg = HIGHLIGHT_BACKGROUND, int color = 0) {
	setcolor(0);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar(l, t, r, b);
	setbkcolor(bg);
	setcolor(color);
	outtextxy(l + kcl, t + kct, s);
}

void b_taokhungxanhla(int l, int t, int r, int b)
{
	setcolor(10);
	rectangle(l, t, r, b);
}

void b_taokhungden(int l, int t, int r, int b)
{
	setcolor(0);
	rectangle(l, t, r, b);
}

void b_duongthang(int x1, int y1, int x2, int y2)
{
	setcolor(10);
	line(x1, y1, x2, y2);
}

void b_create_menu_title()
{
	setfillstyle(1, bk_screen);
	setcolor(0);
	text_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(685, 70, 980, 110, (char*)"In hoa don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
}

void b_delete_after_create() {
	setfillstyle(1, bk_screen);
	bar(0, 119, 1200, 620);
}

void khung_b_nhd()
{
	b_taokhungden(10, 120, 110, 220);
	b_taokhungden(110, 120, 980, 220);
	b_taokhungden(980, 120, 1180, 220);
	b_taokhungden(10, 120, 110, 220);
	b_taokhungden(20, 130, 100, 170);
	b_taokhungden(20, 170, 100, 210);
	b_taokhungden(110, 120, 590, 145);//sohd
	b_taokhungden(110, 145, 270, 170);
	b_taokhungden(270, 145, 430, 170);
	b_taokhungden(430, 145, 590, 170);
	b_taokhungden(590, 120, 980, 145);
	b_taokhungden(110, 170, 430, 195);
	b_taokhungden(110, 195, 350, 220);
	b_taokhungden(350, 195, 590, 220);
	b_taokhungden(430, 170, 590, 195);
	b_taokhungden(620, 145, 770, 170);//them vt
	b_taokhungden(800, 145, 950, 170);
	b_taokhungden(590, 170, 980, 195);
	b_taokhungden(590, 195, 980, 220);
}

bool checktrungshd(DS_NhanVien& ds_nv, string d)
{

	for (int i = 0; i < ds_nv.length; i++)
	{
		DS_HoaDon* curr_hd = ds_nv.nhan_vien[i]->ds_hoadon; // trỏ đến danh sách hóa đơn của nhân viên hiện tại
		while (curr_hd != NULL) // duyệt từng hóa đơn trong danh sách
		{
			if (strcmp(curr_hd->hoadon.SoHD, d.c_str()) == 0) // nếu trùng số hóa đơn
			{
				return true; // trả về true
			}
			curr_hd = curr_hd->next; // chuyển đến hóa đơn tiếp theo trong danh sách
		}
	}
	return false; // nếu không trùng thì trả về false
}

bool checktrungmanv(DS_NhanVien& ds_nv, string d)
{
	for (int i = 0; i < ds_nv.length; i++) // duyệt từng nhân viên trong danh sách
	{
		if (ds_nv.nhan_vien[i]->maNV == d) // nếu mã nhân viên trùng với d
		{
			return true; // trả về true
		}
	}
	return false; // nếu không trùng thì trả về false
}

bool checktrungmavt(DS_VatTu* root, string x) {
	DS_VatTu* p = root;
	while (p != NULL) {
		if (string(p->vat_tu.maVT) == x) { // nếu maVT của nút hiện tại khớp với x, trả về true
			return true;
		}
		else if (x > string(p->vat_tu.maVT)) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return false; // nếu không tìm thấy nút có maVT khớp với x, trả về false
}

bool checktrungmavthoadonhientai(HoaDon& hd, string mavt)
{
	dscthd current = hd.first_cthd;
	while (current != NULL) {
		if (current->ct_hoadon.MAVT == mavt) {
			return false;
		}
		current = current->next;
	}
	return true;
}

bool checksoluong(DS_VatTu* root, char* mvt, string x) {
	DS_VatTu* p = root;
	while (p != NULL) {
		if (strcmp(p->vat_tu.maVT, mvt) == 0) { // so sánh trường maVT trước
			if (stoi(x) <= p->vat_tu.SLT) { // so sánh trường SLT nếu maVT khớp
				return true;
			}
			else {
				return false;
			}
		}
		else if (strcmp(mvt, p->vat_tu.maVT) > 0) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return false; // trả về false nếu không tìm thấy nút có maVT khớp
}

bool checksoluongnhap(DS_VatTu* root, char* mvt, string x) {
	DS_VatTu* p = root;
	while (p != NULL) {
		if (strcmp(p->vat_tu.maVT, mvt) == 0) { // so sánh trường maVT trước
			if (stoi(x) + p->vat_tu.SLT > 99999 ) { // so sánh trường SLT nếu maVT khớp
				return false;
			}
			else {
				return true;
			}
		}
		else if (strcmp(mvt, p->vat_tu.maVT) > 0) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return false; // trả về false nếu không tìm thấy nút có maVT khớp
}

bool checkSLT(DS_VatTu* root, string mvt) {
	DS_VatTu* p = root;
	while (p != NULL) {
		if (p->vat_tu.maVT == mvt) { // so sánh trường maVT trước
			if (0 == p->vat_tu.SLT) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (mvt > p->vat_tu.maVT) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return true;
}

bool checkSLTfull(DS_VatTu* root, string mvt) {
	DS_VatTu* p = root;
	while (p != NULL) {
		if (p->vat_tu.maVT == mvt) { // so sánh trường maVT trước
			if (p->vat_tu.SLT == 99999) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (mvt > p->vat_tu.maVT) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	return false;
}


void resetbaoloi()
{
	text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 2, 1, 5, 14, 0);
}

void in_hoa_don_table(
	char table_in_HD_header[][20],
	DS_info* nodeInfo,
	DS_VatTu* root,
	view_page& view_page,
	int num_per_pg
) {
	b_delete_after_create();
	b_create_menu_title();

	// tinh so page co trong trang

	DS_CT_HoaDon* ds = nodeInfo->hoadon.first_cthd;

	int n = getNumOfCTHD(ds);
	int page = n / num_per_pg;
	int du = n % num_per_pg;
	view_page.page = du ? page + 1 : page;
	int max_rows = n > (num_per_pg * view_page.current) ? (num_per_pg * view_page.current) : n;
	// reder page
	int i = num_per_pg * (view_page.current - 1);
	setfillstyle(1, 15);
	bar(0, 121, 1200, 800);
	// create table title
	writeText(10, 130, (char*)"CONG TY TNHH NHAT PHU PHUONG", 3, COLOR(51, 51, 51), f_medium, 15);
	writeText(800, 130, (char*)"HOA DON BAN HANG", 4, COLOR(51, 51, 51), BOLD_FONT, 15); // bk_screen
	// create bar	
	//setlinestyle(0, 0, 2);
	rectangle(-2, 160, 500, 290);
	rectangle(500, 160, 1200, 290);
	setfillstyle(1, COLOR(221, 221, 221));
	setbkcolor(COLOR(221, 221, 221));
	bar(-2, 161, 500, 200);
	settextstyle(3, 0, 3);
	string soHD = "No:  ";
	soHD += nodeInfo->hoadon.SoHD;
	outtextxy(10, 170, (char*)soHD.c_str());
	setbkcolor(15);
	line(0, 200, 500, 200);
	string date = "Ngay lap:  ";
	date += to_string(nodeInfo->hoadon.date.ngay);
	date += " / ";
	date += to_string(nodeInfo->hoadon.date.thang);
	date += " / ";
	date += to_string(nodeInfo->hoadon.date.nam);
	outtextxy(10, 213, (char*)date.c_str());
	string loai;
	if (!strcmp(nodeInfo->hoadon.Loai, "N")) loai = "Loai:  Hoa don nhap";
	else loai = "Loai:  Hoa don xuat";
	outtextxy(10, 250, (char*)loai.c_str());
	string nguoilap = "Nhan vien ban hang:  ";
	nguoilap += nodeInfo->hoTenNV;
	outtextxy(520, 170, (char*)nguoilap.c_str());
	string maNV = "Ma NV:  ";
	maNV += nodeInfo->maNV;
	outtextxy(520, 200, (char*)maNV.c_str());
	// header num_cols
	int bar_top = 300, bar_bottom = 332;
	int text_top = 305;
	setcolor(0);
	setfillstyle(1, COLOR(221, 221, 221));
	setbkcolor(COLOR(221, 221, 221));
	bar3d(0, bar_top, 1200, bar_bottom, 0, 0);
	setcolor(0);
	settextstyle(f_small, 0, 2);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(130, text_top, table_in_HD_header[0]);
	outtextxy(270, text_top, table_in_HD_header[1]);
	outtextxy(470, text_top, table_in_HD_header[2]);
	outtextxy(660, text_top, table_in_HD_header[3]);
	outtextxy(830, text_top, table_in_HD_header[4]);
	outtextxy(1000, text_top, table_in_HD_header[5]);
	setfillstyle(1, 15);
	setbkcolor(15);
	for (; i < max_rows; i++)
	{
		if (i % num_per_pg == 0) {
			bar_top += 30;
			bar_bottom += 40;
			text_top += 35;
		}
		else {
			bar_top += 40;
			bar_bottom += 40;
			text_top += 40;
		}
		// row
		setcolor(0);
		bar3d(0, bar_top, 1200, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(70, text_top, stt, 1, 0, 3, 15);
		DS_CT_HoaDon* tempNodeCT = getIndexCTHD(ds, i);
		string tenVT;
		//DS_VatTu* nodeVT = searchVT(root, tempNodeCT->ct_hoadon.MAVT);
		//if (nodeVT != NULL) tenVT = nodeVT->vat_tu.tenVT;
		//else tenVT = "Unknown";
		DS_VatTu* nodeVT = getNodebyId_maVT(root, tempNodeCT->ct_hoadon.MAVT);
		if (nodeVT != NULL) tenVT = nodeVT->vat_tu.tenVT;
		else tenVT = "Unknown";
		writeText(135, text_top, (char*)tenVT.c_str(), 1, 0, 3, 15);
		string soluong = to_string(tempNodeCT->ct_hoadon.Soluong);
		writeText(290, text_top, (char*)soluong.c_str(), 1, 0, 3, 15);
		string dongia = formatNumber(tempNodeCT->ct_hoadon.Dongia);
		writeText(470, text_top, (char*)dongia.c_str(), 1, 0, 3, 15);
		stringstream s;
		s << tempNodeCT->ct_hoadon.VAT;
		string VAT = s.str();
		writeText(680, text_top, (char*)VAT.c_str(), 1, 0, 3, 15);
		if (tempNodeCT->ct_hoadon.TrangThai == 1)
			writeText(833, text_top, (char*)"Khach mua", 1, 0, 3, 15);
		else
			writeText(833, text_top, (char*)"Khach tra", 1, 0, 3, 15);
		long double thanhtien = ((long double)tempNodeCT->ct_hoadon.Soluong * (long double)tempNodeCT->ct_hoadon.Dongia) + ((long double)tempNodeCT->ct_hoadon.Soluong * (long double)tempNodeCT->ct_hoadon.Dongia * (long double)tempNodeCT->ct_hoadon.VAT / 100);
		writeText(1010, text_top, (char*)formatNumber(thanhtien).c_str(), 1, 0, 3, 15);
	}


	// In tong gia
	bar_bottom += 10;
	if (view_page.page == view_page.current) {
		setfillstyle(1, COLOR(221, 221, 221));
		setbkcolor(COLOR(221, 221, 221));
		bar(860, bar_bottom + 16, 1110, bar_bottom + 16 + 50);
		line(860, bar_bottom + 16, 1110, bar_bottom + 16);
		line(860, bar_bottom + 16 + 50, 1110, bar_bottom + 16 + 50);
		settextstyle(f_small, 0, 2);
		outtextxy(870, bar_bottom + 15 + 13, (char*)"Tong gia");
		DS_CT_HoaDon* nodeIt = ds;
		long double tonggia = 0;
		while (nodeIt != NULL) {
			if (nodeIt->ct_hoadon.TrangThai == 1) {
				long double giagoc = (long double)nodeIt->ct_hoadon.Soluong * (long double)nodeIt->ct_hoadon.Dongia;
				long double thue = (long double)nodeIt->ct_hoadon.Soluong * (long double)nodeIt->ct_hoadon.Dongia * (long double)nodeIt->ct_hoadon.VAT / 100;
				tonggia += giagoc + thue;
			}
			nodeIt = nodeIt->next;
		}
		int indent = 0;
		if (to_string(tonggia).length() > 9) indent += 50;
		outtextxy(1010 - indent, bar_bottom + 16 + 13, (char*)formatNumber((long long)tonggia).c_str());
		settextstyle(3, HORIZ_DIR, 2);
		setbkcolor(15);
		string bangchu = "Bang chu:  ";
		bangchu += convertToText(tonggia);
		indent = 0;
		if (bangchu.length() > 34) indent = bangchu.length() * bangchu.length() * 1.96 / 34;
		outtextxy(850 - indent, bar_bottom + 16 + 13 + 50, (char*)bangchu.c_str());
	}
	// < >
	page_transition(view_page, true);
}

void handle_in_HD_table(int& x, int& y, DS_info* ds, DS_VatTu* root, view_page& vp_m_print) {
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_m_print.current == vp_m_print.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_m_print, true);

				delete_after_header();
				in_hoa_don_table(table_in_HD_header, ds, root, vp_m_print, 4);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_m_print.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_m_print, true);
				delete_after_header();
				in_hoa_don_table(table_in_HD_header, ds, root, vp_m_print, 4);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y))  {
				ss_page = false;
				goto ss_end;
			}
			if (ktVT(15, 70, 310, 110, x, y) || ktVT(320, 70, 640, 110, x, y)) {
				// reset view_page
				vp_m_print.current = 1;
				vp_m_print.page = 1;
				out_table = true;
				goto ss_end;
			}
		}
		delay(1);
	}
ss_end:;
}

void xu_li_tra_cuu_hoa_don(int& x, int& y, bool& error_sohd, string& soHD, bool page, DS_NhanVien ds_nv, DS_VatTu* root, view_page& vp_m_print) {
	if (ktVT(620, 285, 845, 320, x, y) && page) {
		cout << "Tien hanh nhap input SoHD";
		soHD = input_soHD(error_sohd, x, y, 620, 285, 845, 320, 70, 7, 5, 45, 50, soHD, 10, "textNumberNoSpace", "upcase", COLOR_INFOR_SS, 430, 225);
	}
	if (error_sohd) return;
	if (ktVT(450, 410, 750, 450, x, y) && page) {
		cout << "Click button tim kiem" << endl;
		// check empty 
		if (soHD == "") {
			text_box(620, 285, 845, 320, (char*)"Trong!", f_medium, 2, 8, 80, 15, COLOR(255, 0, 0));
		}
		else {
			cout << "Tien hanh kiem tra so hoa don" << endl;
			DS_info* result_info = new DS_info();
			result_info = NULL;
			char ho_ten[40];
			for (int i = 0; i < ds_nv.length; i++) {
				NhanVien* nv = ds_nv.nhan_vien[i];
				DS_HoaDon* nodeHD = nv->ds_hoadon;
				while (nodeHD != NULL && strcmp(nodeHD->hoadon.SoHD, soHD.c_str())) nodeHD = nodeHD->next;
				if (nodeHD != NULL) {
					DS_info* temp = new DS_info();
					temp->hoadon = nodeHD->hoadon;
					strcpy(ho_ten, nv->ho);
					strcat(ho_ten, " ");
					strcat(ho_ten, nv->ten);
					strcpy_s(temp->hoTenNV, ho_ten);
					strcpy_s(temp->maNV, nv->maNV);
					result_info = temp;
					break;
				}
			}
			if (result_info == NULL) {
				writeText(460, 370, (char*)"So hoa don khong ton tai!", 2, COLOR(255, 0, 0), 8, COLOR_INFOR_SS);
			}
			else {
				in_hoa_don_table(table_in_HD_header, result_info, root, vp_m_print, 4);
				handle_in_HD_table(x, y, result_info, root, vp_m_print);
			}
		}
	}
}


void do_hoa_in_hoadon(bool& is_error, view_page& vp_m_print) {
	vp_m_print = {};
	setfillstyle(1, COLOR_INFOR_SS);
	setcolor(0);
	bar3d(280, 180, 920, 490, 0, 0);

	// Thanh tieu de
	setlinestyle(0, 0, 1);
	const char* title = "IN HOA DON";
	text_box(470, 140, 720, 181, (char*)title, 10, 3, 10, 58, COLOR(51, 51, 51), 15); // font 8
	// Thanh tim kiemi
	text_box(450, 410, 750, 450, (char*)"Tim hoa don", f_medium, 3, 10, 70, COLOR(255, 153, 51), 0);
	// User input 
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SS);
	outtextxy(360, 290, (char*)"Nhap so hoa don:");
	bar3d(620, 285, 845, 320, 0, 0);
}

void khunglan2(char(&c_sohoadon)[21], char(&c_mannhanvien)[11], bool& nhap, bool& xuat)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string curr_date = to_string(ltm->tm_mday);
	string curr_month = to_string(1 + ltm->tm_mon);
	string curr_year = to_string(1900 + ltm->tm_year);

	text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
	text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);

	text_box_no_border(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(250, 121, 590, 145, (char*)c_sohoadon, f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 145, 270, 170, (char*)"ngay:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(180, 146, 265, 168, (char*)curr_date.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(270, 145, 430, 170, (char*)"thang:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(350, 146, 425, 168, (char*)curr_month.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(430, 145, 590, 170, (char*)"nam:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(480, 146, 585, 168, (char*)curr_year.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(590, 120, 980, 145, (char*)"Ma nhan vien:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(750, 121, 980, 145, (char*)c_mannhanvien, f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 170, 430, 195, (char*)"Ma vat tu:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(350, 195, 590, 220, (char*)"Don gia:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(430, 170, 590, 195, (char*)"%VAT: 10", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
	text_box_no_border(800, 145, 950, 170, (char*)"Luu hoa don", f_medium, 2, 1, 5, 11, 0);

	text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 2, 1, 5, 14, 0);
	khung_b_nhd();

	if (nhap == true)
	{
		text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14);
		text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
		khung_b_nhd();
	}
	if (xuat == true)
	{
		text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
		text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
		khung_b_nhd();
	}
}

void khunglan1()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string curr_date = to_string(ltm->tm_mday);
	string curr_month = to_string(1 + ltm->tm_mon);
	string curr_year = to_string(1900 + ltm->tm_year);

	text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
	text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);

	text_box_no_border(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 145, 270, 170, (char*)"ngay:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(180, 146, 265, 168, (char*)curr_date.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(270, 145, 430, 170, (char*)"thang:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(350, 146, 425, 168, (char*)curr_month.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(430, 145, 590, 170, (char*)"nam:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(480, 146, 585, 168, (char*)curr_year.c_str(), f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(590, 120, 980, 145, (char*)"Ma nhan vien:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 170, 430, 195, (char*)"Ma vat tu:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(350, 195, 590, 220, (char*)"Don gia:", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(430, 170, 590, 195, (char*)"%VAT: 10", f_medium, 2, 1, 5, 9, 0);
	text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
	text_box_no_border(800, 145, 950, 170, (char*)"Luu hoa don", f_medium, 2, 1, 5, 11, 0);
	text_box_no_border(590, 170, 980, 195, (char*)"TONG CONG", f_medium, 2, 5, 130, 15, 0);
	text_box_no_border(590, 195, 980, 220, (char*)"", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 2, 1, 5, 14, 0);
	khung_b_nhd();
}

void themvttamthoi(HoaDon& hd, int& n, char(&c_mavattu)[11], char(&c_soluong)[11], char(&c_dongia)[11], char(&c_vat)[6], bool& nhap, bool& xuat)
{
	CT_HoaDon cthoadon = {};
	strcpy(cthoadon.MAVT, c_mavattu);
	cthoadon.Soluong = stoi(c_soluong);
	cthoadon.Dongia = stoi(c_dongia);
	cthoadon.VAT = stof(c_vat);
	cthoadon.TrangThai = 1;
	Insert_last_CTHD(hd.first_cthd, cthoadon);
	n++;
}

char* timTenVT(DS_VatTu* root, char MAVT[11]) {
	if (root == NULL) { // nếu cây rỗng
		return NULL;
	}
	if (strcmp(root->vat_tu.maVT, MAVT) == 0) { // nếu tìm thấy MAVT trong nút hiện tại
		return root->vat_tu.tenVT; // trả về tenVT tương ứng
	}
	if (strcmp(root->vat_tu.maVT, MAVT) < 0) { // nếu MAVT cần tìm nằm bên phải nút hiện tại
		return timTenVT(root->right, MAVT); // tiếp tục tìm kiếm bên phải
	}
	else { // nếu MAVT cần tìm nằm bên trái nút hiện tại
		return timTenVT(root->left, MAVT); // tiếp tục tìm kiếm bên trái
	}
}

char* timDvtVT(DS_VatTu* root, char MAVT[11]) {
	if (root == NULL) { // nếu cây rỗng
		return NULL;
	}
	if (strcmp(root->vat_tu.maVT, MAVT) == 0) { // nếu tìm thấy MAVT trong nút hiện tại
		return root->vat_tu.DVT; // trả về DVT tương ứng
	}
	if (strcmp(root->vat_tu.maVT, MAVT) < 0) { // nếu MAVT cần tìm nằm bên phải nút hiện tại
		return timDvtVT(root->right, MAVT); // tiếp tục tìm kiếm bên phải
	}
	else { // nếu MAVT cần tìm nằm bên trái nút hiện tại
		return timDvtVT(root->left, MAVT); // tiếp tục tìm kiếm bên trái
	}
}

DS_VatTu* TimKiemNode(DS_VatTu* ds_vt, char* maVT) {
	if (ds_vt == NULL) {
		return NULL;
	}
	if (strcmp(ds_vt->vat_tu.maVT, maVT) == 0) {
		return ds_vt;
	}
	DS_VatTu* found = TimKiemNode(ds_vt->left, maVT);
	if (found == NULL) {
		found = TimKiemNode(ds_vt->right, maVT);
	}
	return found;
}

void chuyentrangthaixuat(HoaDon& hd, DS_VatTu*& ds_vt)
{
	dscthd current = hd.first_cthd;
	while (current != NULL)
	{
		TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.sldaban++;
		TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.SLT = TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.SLT - current->ct_hoadon.Soluong;
		write_file_goods(ds_vt);
		current = current->next;
	}
}

void chuyentrangthainhap(HoaDon& hd, DS_VatTu*& ds_vt)
{
	dscthd current = hd.first_cthd;
	while (current != NULL)
	{
		TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.sldaban++;
		TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.SLT = TimKiemNode(ds_vt, current->ct_hoadon.MAVT)->vat_tu.SLT + current->ct_hoadon.Soluong;
		write_file_goods(ds_vt);
		current = current->next;
	}
}

long double thanhtien1vt(int& soluong, int& dongia, float& VAT)
{
	long double a = 0;
	a = (long double)soluong * (long double)dongia + (long double)soluong * (long double)dongia * (long double)(VAT / 100);
	return a;
}

long double tongPhanTuDSLKD(HoaDon& hd) {
	long double sum = 0;
	dscthd current = hd.first_cthd;
	while (current != NULL) {
		sum += thanhtien1vt(current->ct_hoadon.Soluong, current->ct_hoadon.Dongia, current->ct_hoadon.VAT);
		current = current->next;
	}
	return sum;
}

long double tongtrangthai0(HoaDon hd)
{
	long double sum = 0;
	dscthd current = getNodesByTrangThai(hd.first_cthd, 0);
	while (current != NULL) {
		sum += thanhtien1vt(current->ct_hoadon.Soluong, current->ct_hoadon.Dongia, current->ct_hoadon.VAT);
		current = current->next;
	}
	return sum;
}

long double tongtrangthai1(HoaDon hd)
{
	long double sum = 0;
	dscthd current = getNodesByTrangThai(hd.first_cthd, 1);
	while (current != NULL) {
		sum += thanhtien1vt(current->ct_hoadon.Soluong, current->ct_hoadon.Dongia, current->ct_hoadon.VAT);
		current = current->next;
	}
	return sum;
}

void delete_bill_table()
{
	setfillstyle(1, bk_screen);
	bar(9, 229, 1181, 900);
}

void bill_nhd_table(
	HoaDon& hd,
	view_page& view_page,
	check_CURD& edit,
	check_CURD& _delete,
	int num_rows,
	int& n,
	DS_VatTu*& ds_vt
) {
	dscthd p;
	p = hd.first_cthd;

	setlinestyle(0, 0, 0);
	delete_bill_table();
	setcolor(0);
	int page = n / num_rows;
	int du = n % num_rows;
	view_page.page = du ? page + 1 : page;
	if (view_page.current > view_page.page)
	{
		view_page.current--;
	}
	if (n == 0) {
		view_page.page = 1;
	}
	int max_page = n > (num_rows * view_page.current) ? (num_rows * view_page.current) : n;
	// reder page
	int i = num_rows * (view_page.current - 1);
	//header
	int bar_top = 230, bar_bottom = 260;
	int text_top = 235;
	setfillstyle(1, COLOR_HEADER_TABLE);
	setbkcolor(COLOR_HEADER_TABLE);
	settextstyle(f_small, 0, 1);
	bar3d(10, bar_top, 1180, bar_bottom, 0, 0);
	outtextxy(16, text_top, (char*)"STT");
	outtextxy(75, text_top, (char*)bill_table_header[0]);
	outtextxy(200, text_top, (char*)bill_table_header[1]);
	outtextxy(350, text_top, (char*)bill_table_header[2]);
	outtextxy(450, text_top, (char*)bill_table_header[3]);
	outtextxy(560, text_top, (char*)bill_table_header[4]);
	outtextxy(680, text_top, (char*)bill_table_header[5]);
	outtextxy(780, text_top, (char*)bill_table_header[6]);
	outtextxy(1030, text_top, (char*)bill_table_header[7]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	for (; i < max_page; i++)
	{
		p = getNodeByIndexdscthd(hd.first_cthd, i);
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
		//edit.data[e].key =string( );
		edit.data[e].l = 1030;
		edit.data[e].t = text_top;
		edit.data[e].r = 1108;
		edit.data[e].b = text_top + 22;
		e++;
		// vi tri delete
		//_delete.data[d].key = string(ct->ct_hoadon.MAVT);
		_delete.data[d].l = 1130;
		_delete.data[d].t = text_top;
		_delete.data[d].r = 1178;
		_delete.data[d].b = text_top + 22;
		d++;
		// --------------------------------- xuong day
		// row
		setcolor(0);
		bar3d(10, bar_top, 1180, bar_bottom, 0, 0);
		// title header

		int SL = p->ct_hoadon.Soluong;
		char SL_char[10];
		sprintf(SL_char, "%d", SL);

		int DG = p->ct_hoadon.Dongia;
		char DG_char[10];
		sprintf(DG_char, "%d", DG);

		float VAT = p->ct_hoadon.VAT;
		char VAT_char[8];
		snprintf(VAT_char, sizeof(VAT_char), "%.2f", VAT);

		long double TT = 0.00;
		TT = thanhtien1vt(SL, DG, VAT);
		char TT_char[20];
		snprintf(TT_char, sizeof(TT_char), "%.2Lf", TT);

		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(16, text_top, stt, 1, 0, 3, 15);
		writeText(75, text_top, p->ct_hoadon.MAVT, 1, 0, 3, 15);
		char* TENVT = timTenVT(ds_vt, p->ct_hoadon.MAVT);
		writeText(200, text_top, TENVT, 1, 0, 3, 15);
		char* DVT = timDvtVT(ds_vt, p->ct_hoadon.MAVT);
		writeText(350, text_top, DVT, 1, 0, 3, 15);
		writeText(450, text_top, SL_char, 1, 0, 3, 15);
		writeText(560, text_top, DG_char, 1, 0, 3, 15);
		writeText(680, text_top, VAT_char, 1, 0, 3, 15);
		writeText(780, text_top, (char*)formatNumber(long long(TT)).c_str(), 1, 0, 3, 15);
		//writeText(780, text_top, TT_char, 1, 0, 3, 15);

		text_box(1030, text_top, 1108, text_top + 23, (char*)CURD_o_text[0], f_small, 1, 1, 2);
		text_box(1130, text_top, 1178, text_top + 23, (char*)CURD_o_text[1], f_small, 1, 1, 6);
		setfillstyle(1, 15);
		setbkcolor(15);

		p = p->next;
	}
	//------------- k can cos the xoa
	_delete.n = d;
	edit.n = e;
	// < >
	page_transition(view_page);
}

void bill_infor(string mvt, string tvt, string dvt, string vat) {
	delete_after_header();
	text_box(430, 90, 800, 130, (char*)"Chinh sua thong tin ct vat tu", f_medium, 2, 10, 10, 11, 0);
	//
	setfillstyle(1, COLOR_INFOR_SG);
	//
	bar3d(250, 130, 950, 500, 0, 0);
	text_box(430, 165, 800, 195, (char*)mvt.c_str(), f_medium, 1, 6, 5, 15, 0); // chu cao 20
	writeText(260, 170, (char*)"Ma vat tu", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 225, 800, 255, (char*)tvt.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 230, (char*)"So luong", 2, 0, f_medium, COLOR_INFOR_SG);

	text_box(430, 285, 800, 315, (char*)dvt.c_str(), f_medium, 1, 6, 5, 15, 0);
	writeText(260, 290, (char*)"Don gia", 2, 0, f_medium, COLOR_INFOR_SG);

	bar3d(430, 345, 530, 375, 0, 0);
	writeText(260, 350, (char*)"%VAT", 2, 0, f_medium, COLOR_INFOR_SG);
	text_box(430, 345, 800, 375, (char*)vat.c_str(), f_medium, 1, 6, 5, 15, 0);

	text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, 11, 0);
	text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, 11, 0);

}

void handle_nhd_table(int& x, int& y, HoaDon& hd, int i_CRUD, string& c_mavattu, string& c_soluongvt, string& c_dongiavt, string& c_vatvt, bool& nhd_isEdit, DS_VatTu*& ds_vt)
{
	int checkSubmit[4];
	if (nhd_isEdit) {
		for (int i = 0; i < 4; i++)
		{
			checkSubmit[i] = 1;
		}
		text_box(430, 165, 800, 195, (char*)c_mavattu.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mnv
	}
	bool checkCancle = true;
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
		nhdInfor:
			if (ktVT(430, 225, 800, 255, x, y)) { // so luong
				c_soluongvt = input(x, y, 430, 225, 800, 255, 5, 6, 5, 35, 50, c_soluongvt, 6, "number", "camelCase", COLOR_INFOR_SG, 430, 285);

				if (nhd_isEdit) {
					if (checksoluong(ds_vt, (char*)c_mavattu.c_str(), c_soluongvt) == false) {
						warning_msg((char*)"Khong du so luong.", 435, 225 + 35, COLOR_INFOR_SG, I_ERROR_COLOR);
						checkSubmit[1] = -2;
					}
					else if (empty(c_soluongvt) == 1) {
						checkSubmit[1] = -1;
					}
					else {
						checkSubmit[1] = 1;
					}
				}
				goto nhdInfor;

			}
			if (ktVT(430, 285, 800, 315, x, y)) { // dongia
				c_dongiavt = input(x, y, 430, 285, 800, 315, 5, 6, 5, 35, 50, c_dongiavt, 6, "number", "camelCase", COLOR_INFOR_SG, 430, 345);
				if (nhd_isEdit) {
					if (empty(c_dongiavt) == 1) {
						checkSubmit[2] = -1;
					}
					else {
						checkSubmit[2] = 1;
					}
				}
				goto nhdInfor;

			}
			if (ktVT(430, 345, 800, 375, x, y)) { // vat
				c_vatvt = input(x, y, 430, 345, 800, 375, 5, 6, 5, 35, 50, c_vatvt, 4, "decimal", "camelCase", COLOR_INFOR_SG, NULL, NULL);
				if (empty(c_vatvt) == 1) {
					checkSubmit[3] = -1;
				}
				else {
					checkSubmit[3] = 1;
				}
				goto nhdInfor;
			}
			//HUY
			if (ktVT(750, 420, 820, 450, x, y)) {
				text_box(750, 420, 820, 450, (char*)"Huy", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
				if (checkSubmitEditAdd(checkSubmit, 4) < 4) {
					checkCancle = announce_board(x, y, 50, 0, "Ban co muon huy.", "");
				}
				if (checkCancle) {
					nhd_isEdit = false;

					delay(200);
					goto nhd_end;
				}
				else {
					bill_infor(c_mavattu, c_soluongvt, c_dongiavt, c_vatvt);
					if (nhd_isEdit) {

					text_box(430, 165, 800, 195, (char*)c_mavattu.c_str(), f_medium, 1, 6, 5, PROHIBIT, 0); // mnv
					}
					x = NULL, y = NULL;
					goto nhdInfor;
				}

			}
			//LUU
			if (ktVT(840, 420, 910, 450, x, y)) {

				if (checkSubmitEditAdd(checkSubmit, 4) == 0) {
					CT_HoaDon ct_temp;
					if (nhd_isEdit) {
						ct_temp = {};
						strcpy(ct_temp.MAVT, c_mavattu.c_str());
						ct_temp.Soluong = stoi(c_soluongvt);
						ct_temp.Dongia = stoi(c_dongiavt);
						ct_temp.VAT = stof(c_vatvt);
						ct_temp.TrangThai = 1;
						xoaNodeByvitri(hd.first_cthd, i_CRUD);
						themNodeByvitri(hd.first_cthd, i_CRUD, ct_temp);

					}
					nhd_isEdit = false;
					text_box(840, 420, 910, 450, (char*)"Luu", f_medium, 2, 5, 15, XANH_LA_CAY, 0);
					announce_board(x, y, 40, 20, "Ban da luu thanh cong.");
					delay(500);
					goto nhd_end;
				}
				else {
					int left_error = 630;
					if (checkSubmit[0] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 165 + 34, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[1] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 225 + 34, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[2] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 285 + 34, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

					if (checkSubmit[3] == -1) {
						warning_msg("Khong duoc de trong", 430 + 5, 350 + 34, COLOR_INFOR_SG, I_ERROR_COLOR);
					}

				}
			}
		}
	}
nhd_end:;
}

void b_handle_table(int& x, int& y, HoaDon& hd, int& n, check_CURD& delete_table_b, check_CURD& edit_table_b, view_page& vp_b_table, bool& nhd_isEdit, DS_VatTu*& ds_vt)
{
	dscthd p = hd.first_cthd;
	CT_HoaDon temp;
	bool break_all = false;
	int i_CRUD = 0;
	bool check_B_nhd = true;
	string keyCRUD = "";

	// edit
	cout << edit_table_b.n << endl;
	for (int i = 0; i < edit_table_b.n; i++)
	{
		if (ktVT(edit_table_b.data[i].l, edit_table_b.data[i].t, edit_table_b.data[i].r, edit_table_b.data[i].b, x, y)) {
			i_CRUD = (vp_b_table.current - 1) * 7 + i;

			temp = getNodeByvitri(hd.first_cthd, i_CRUD);
			string str_MAVT(temp.MAVT);
			string str_Soluong = to_string(temp.Soluong);
			string str_Dongia = to_string(temp.Dongia);
			stringstream ss;
			ss << fixed << setprecision(2) << temp.VAT;
			string str_VAT = ss.str();

			bill_infor(str_MAVT, str_Soluong, str_Dongia, str_VAT);
			nhd_isEdit = true;
			goto bill_out;
		}
	}
	//delete
	for (int i = 0; i < delete_table_b.n; i++)
	{
		if (ktVT(delete_table_b.data[i].l, delete_table_b.data[i].t, delete_table_b.data[i].r, delete_table_b.data[i].b, x, y)) {
			i_CRUD = (vp_b_table.current - 1) * 7 + i;

			//CT_HoaDon ct = getNodeByvitri(hd.first_cthd, i_CRUD);
			/*delete_bill_table();
			delay(100000);*/
			check_B_nhd = announce_board(x, y, 40, 0, "Ban co muon xoa khong.", "");
			if (check_B_nhd) {
				xoaNodeByvitri(hd.first_cthd, i_CRUD);
				n--;
			}
			goto bill_end;
		}
	}
	// transition page
	if (ktVT(650, 565, 685, 600, x, y)) {
		if (vp_b_table.current == vp_b_table.page) {

		}
		else {
			next_page(650, 565, 685, 600, vp_b_table);
			delete_bill_table();
			bill_nhd_table( hd, vp_b_table, edit_table_b, delete_table_b, 7, n, ds_vt);

		}
	}
	if (ktVT(495, 565, 530, 600, x, y)) {
		if (vp_b_table.current == 1) {

		}
		else {
			prev_page(495, 565, 530, 600, vp_b_table);
			cout << vp_b_table.current;
			delete_bill_table();
			bill_nhd_table(hd, vp_b_table, edit_table_b, delete_table_b, 7, n, ds_vt);

		}
	}
	if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) ||ktVT(1140, 10, 1190, 50, x, y)) {
		b_page = false;
		goto bill_end;
	}


bill_out:
	if (nhd_isEdit) {
		string c_mavattu(temp.MAVT);
		string c_soluongvt = to_string(temp.Soluong);
		string c_dongiavt = to_string(temp.Dongia);
		stringstream ss;
		ss << fixed << setprecision(2) << temp.VAT;
		string c_vatvt = ss.str();
		handle_nhd_table(x, y, hd, i_CRUD, c_mavattu, c_soluongvt, c_dongiavt, c_vatvt, nhd_isEdit, ds_vt);
		nhd_isEdit = false;
	}
bill_end:;

}

// chiu
void create_mavtmanv_header(string title, string search) {
	int colorsearch = 0;
	if (search == "Nhap ten hoac id can tim kiem") {
		colorsearch = COLOR(153, 150, 150);
	}
	text_box(50, 72, 400, 108, (char*)search.c_str(), f_medium, 1, 10, 10, WHITE, colorsearch);
	text_box_no_border(600, 72, 1100, 108, (char*)title.c_str(), f_medium, 3, 10, 10, bk_screen, RED );
	//setcolor(0);
	//setfillstyle(1, bk_screen);
	//text_box(950, 70, 1150, 110, (char*)subTitle.c_str(), f_medium, 2, 10, 20, 11);
	//setbkcolor(bk_screen);
	//setcolor(12);
	//settextstyle(f_medium, 0, 5);(
	//outtextxy(50, 70, (char*)title.c_str());
}

void nhd_manv_table
(
	NhanVien** nhan_vien,
	int length,// day la danh sach cac phan tu chon kd_lieu cho phu hop
	view_page& view_page,
	check_CURD& chon,// k can co the xoa
	int num_rows,
	string searchValue = "Nhap ten hoac id can tim kiem"
) {
	setlinestyle(0, 0, 0);
	delete_after_header();

	create_mavtmanv_header((string)"Danh sach nhan vien", searchValue);
	// tnh so page co trong trang
	setcolor(0);
	int n = length;
	int page = n / num_rows;
	int du = n % num_rows;
	view_page.page = du ? page + 1 : page;
	if (n == 0) {
		view_page.page = 1;
	}
	if (view_page.current > view_page.page) {
		view_page.current--;
	}
	int max_rows = n > (num_rows * view_page.current) ? (num_rows * view_page.current) : n;
	// reder page
	int i = num_rows * (view_page.current - 1);
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
	outtextxy(650, text_top, (char*)sf_table_header[2]);
	outtextxy(900, text_top, (char*)sf_table_header[3]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int e = 0;//edit
	for (; i < max_rows; i++)
	{
		if (i % num_rows == 0) {
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
			bar_bottom -= (max_rows - num_rows * (view_page.current - 1)) - 2;
		}
		// Neu k su dung thi xoa tu day xuong
		//vi tri edit
		chon.data[e].key = (string)nhan_vien[i]->maNV;
		chon.data[e].l = 900;
		chon.data[e].t = text_top;
		chon.data[e].r = 978;
		chon.data[e].b = text_top + 23;
		e++;


		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, nhan_vien[i]->maNV, 1, 0, 3, 15);
		string fullName = nhan_vien[i]->ho;

		fullName += " ";
		fullName += (string)nhan_vien[i]->ten;

		char ten[32];
		strcpy_s(ten, fullName.c_str());
		writeText(230, text_top, ten, 1, 0, 3, 15);
		writeText(650, text_top, nhan_vien[i]->phai, 1, 0, 3, 15);

		//------------- k can co the xoa
		text_box(900, text_top, 978, text_top + 23, (char*)mavt_cn[0], f_small, 1, 1, 17);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	chon.n = e;


	// < >
	page_transition(view_page);
}

bool manv_handle_table(int& x, int& y, DS_NhanVien& ds_nv, check_CURD chon, view_page& vp_manv_table, bool& manv_isChon, const char(&manvphu)[11], string& e_search)
{
	bool break_all = false;
	int i_CRUD = 0;
	bool check_D_staff = true;
	bool checkX = false;
	int svt_NULL = 0;
	int search_empty = 0;
	templeDynamicArray<NhanVien> fillter_nv(ds_nv.length);
	search_staffs(ds_nv, fillter_nv, e_search);
	nhd_manv_table(fillter_nv.a, fillter_nv.size_current, vp_manv_table, chon, 10);
	if (e_search.length() > 0) {
		create_sf_header((string)" Them vat tu", e_search);
	}
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			//search
			if (ktVT(50, 72, 400, 108, x, y)) {// search
				while (1) {
					e_search = input_one(x, y, 50, 72, 400, 108, 10, 10, e_search, 30);
					if (!ktVT(50, 72, 400, 108, x, y)) {
						if (e_search == "") {
							create_sf_header((string)" Them nhan vien", (string)"Nhap ten hoac id can tim kiem");
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
						nhd_manv_table(fillter_nv.a, fillter_nv.size_current, vp_manv_table, chon, 10, e_search);
					}
					delay(1);
				}

			}
			//delete
			for (int i = 0; i < chon.n; i++)
			{
				
				if (ktVT(chon.data[i].l, chon.data[i].t, chon.data[i].r, chon.data[i].b, x, y)) {
					i_CRUD = (vp_manv_table.current - 1) * ROW_STAFF + i;
					strcpy((char*)manvphu, fillter_nv.a[i_CRUD]->maNV);
					goto bill_end;
				}
			}
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_manv_table.current == vp_manv_table.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_manv_table);
				delete_after_header();
				nhd_manv_table(fillter_nv.a, fillter_nv.size_current, vp_manv_table, chon, 10);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_manv_table.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_manv_table);
				delete_after_header();
				nhd_manv_table(fillter_nv.a, fillter_nv.size_current, vp_manv_table, chon, 10);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y)) {
				b_page = false;
				goto bill_end;
			}
		}
		delay(1);
	}

bill_end:;
	return true;
}

void nhd_mavt_table
(
	DS_VatTu* ds_vt,
	DS_s_VT* ds_s_vt,
	view_page& view_page,
	check_CURD& chon,
	int num_cols,
	string searchValue = "Nhap ten hoac id can tim kiem"
) {
	setlinestyle(0, 0, 0);
	delete_after_header();
	create_mavtmanv_header((string)"Danh sach vat tu", searchValue);
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
	outtextxy(95, text_top, (char*)bill_mavt_header[0]);
	outtextxy(230, text_top, (char*)bill_mavt_header[1]);
	outtextxy(450, text_top, (char*)bill_mavt_header[2]);
	outtextxy(650, text_top, (char*)bill_mavt_header[3]);
	outtextxy(900, text_top, (char*)bill_mavt_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
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
		if (i == max_rows - 1) {
			bar_bottom -= (max_rows - num_cols * (view_page.current - 1)) - 2;
		}
		// Neu k su dung thi xoa tu day xuong
		//vi tri edit
		chon.data[e].key = tempVT.maVT;
		chon.data[e].l = 900;
		chon.data[e].t = text_top - 2;
		chon.data[e].r = 978;
		chon.data[e].b = text_top + 23;
		e++;
		// row
		setcolor(0);
		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(55, text_top, stt, 1, 0, 3, 15);
		writeText(95, text_top, tempVT.maVT, 1, 0, 3, 15);
		writeText(230, text_top, tempVT.tenVT, 1, 0, 3, 15);
		writeText(450, text_top, tempVT.DVT, 1, 0, 3, 15);

		writeText(650, text_top, (char*)to_string(tempVT.SLT).c_str(), 1, 0, 3, 15);

		//------------- k can cos the xoa
		text_box(900, text_top - 2, 978, text_top + 23, (char*)mavt_cn[0], f_small, 1, 1, 17);
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa
	chon.n = e;

	// < >
	page_transition(view_page);
}

bool mavt_handle_table(int& x, int& y, DS_VatTu*& ds_vt, DS_s_VT*& ds_s_vt, check_CURD& chon, view_page& vp_mavt_table, bool& is_chon, const char(&mavtphu)[11], bool& xuat, bool& nhap, HoaDon& hd, string& e_search)
{
	bool check_D_staff = true;
	string keyCRUD = "";
	bool checkX = false;
	int svt_NULL = 0;
	int search_empty = 0;
	string placeholder = e_search;
	DS_s_VT* result = NULL;
	nhd_mavt_table(ds_vt, ds_s_vt, vp_mavt_table, chon, 10);
	if (e_search.length() > 0) {
		create_sf_header((string)" Them vat tu", placeholder);
	}
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
		batdau:
			if (ktVT(50, 72, 400, 108, x, y)) {// search
				while (1) {
					e_search = input_one(x, y, 50, 72, 400, 108, 10, 10, e_search, 25);
					if (!ktVT(50, 72, 400, 108, x, y)) {
						if (e_search == "") {
							placeholder = "Nhap ten hoac id can tim kiem";
							create_sf_header((string)" Them vat tu", placeholder);
						}
						break;
					}
					placeholder = e_search;
					result = NULL;
					search_goods(ds_vt, result, e_search);
					deleteTree(ds_s_vt);
					ds_s_vt = NULL;
					coppyVTtoSVT(result, ds_s_vt);
					if (e_search == "") {
						search_empty++;
					}
					else {
						search_empty = 0;
					}
					if (result == NULL) {
						svt_NULL++;
					}
					else {
						svt_NULL = 0;
					}
					if (svt_NULL == 1 || search_empty == 1 || (search_empty == 0 && svt_NULL == 0)) {
						nhd_mavt_table(ds_vt, result, vp_mavt_table, chon, 10, placeholder);
					}
					deleteTree(result);
					delay(1);
				}

			}
			//delete

			for (int i = 0; i < chon.n; i++)
			{
				if (ktVT(chon.data[i].l, chon.data[i].t, chon.data[i].r, chon.data[i].b, x, y)) {
					keyCRUD = chon.data[i].key;
					VatTu x_vt = getNodebyId_maVT(ds_vt, keyCRUD)->vat_tu;
					strcpy((char*)mavtphu, x_vt.maVT);
					string d = mavtphu;
					if (checkSLT(ds_vt, d) == false && xuat == true)
					{
						announce_board(x, y, 40, 20, "Het Hang!");
						delay(500);
						strcpy((char*)mavtphu, "");
						bool a = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, is_chon, mavtphu, xuat, nhap, hd, placeholder);
					}
					if (checktrungmavthoadonhientai(hd, d) == false)
					{
						announce_board(x, y, 40, 20, "Da co vat tu!");
						delay(500);
						strcpy((char*)mavtphu, "");
						bool a = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, is_chon, mavtphu, xuat, nhap, hd, placeholder);
					}
					if (checkSLTfull(ds_vt, d) == true && nhap == true)
					{

						announce_board(x, y, 40, 20, "Da toi da! Khong the nhap them");
						delay(500);
						strcpy((char*)mavtphu, "");
						bool a = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, is_chon, mavtphu, xuat, nhap, hd, placeholder);
					}
					goto bill_end;

				}
			}

			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_mavt_table.current == vp_mavt_table.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_mavt_table);
				delete_after_header();
				nhd_mavt_table( ds_vt, ds_s_vt, vp_mavt_table, chon, 10, placeholder);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_mavt_table.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_mavt_table);
				delete_after_header();
				nhd_mavt_table( ds_vt, ds_s_vt, vp_mavt_table, chon, 10, placeholder);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y)) {
				b_page = false;
				goto bill_end;
			}
		}
		delay(1);
	}
	return true;

bill_end:;

}

int saukhithemvt(HoaDon& hd, int& n, char(&c_sohoadon)[21], char(&c_manhanvien)[11], bool& nhap, bool& xuat, int& x, int& y, DS_NhanVien& ds_nv, DS_VatTu*& ds_vt, DS_s_VT*& ds_s_vt, string& e_search_mavt)
{
lannua:
	char TONGCONG_char[50] = "";
	string a = "0";
	string d;

	check_CURD delete_table_b;
	check_CURD edit_table_b;
	view_page vp_b_table;
	bool nhd_isEdit = false;

	char c_mavattu2[11] = "";
	char c_soluongvt[11] = "";
	char c_dongiavt[11] = "";
	char c_vatvt[6] = "10";

	char mavtphu2[11] = "";
	check_CURD chon;
	view_page vp_mavt_table;
	bool mavt_isChon = false;

	//bool nhap = false, xuat = false;
	//bool sohd = false, manv = false;
	bool mavt = false, soluong = false, dongia = false, vat = true;
	bool themvt = false;

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string curr_date = to_string(ltm->tm_mday);
	string curr_month = to_string(1 + ltm->tm_mon);
	string curr_year = to_string(1900 + ltm->tm_year);

	goto bang;
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
		batdau2:
			if (ktVT(110, 170, 430, 195, x, y))
			{
				resetbaoloi();
			MAVT2:
				if (mavt == true)
				{
					bool mavt_out = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, mavt_isChon, mavtphu2, xuat, nhap, hd, e_search_mavt);
					d = mavtphu2;
					strcpy(mavtphu2, "");
					delete_after_header();
					createHeader(header_title);
					highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
					b_create_menu_title();
					highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
					b_delete_after_create();
					setlinestyle(0, 0, 1);
					//d = input_bill(x, y, 235, 171, 430, 195, 5, 3, 985, 125, 1175, 215, c_mavattu, 10, "textNumberNoSpace", "upcase");
					strcpy(c_mavattu2, "");
				}
				if (mavt == false)
				{
					bool mavt_out = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, mavt_isChon, mavtphu2, xuat, nhap,hd, e_search_mavt);
					if (b_page == true)
					{
						d = mavtphu2;
						strcpy(mavtphu2, "");
						delete_after_header();
						createHeader(header_title);
						highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
						b_create_menu_title();
						highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						setlinestyle(0, 0, 1);
					}

					//d = input_bill(x, y, 235, 171, 430, 195, 5, 3, 985, 125, 1175, 215, "", 10, "textNumberNoSpace", "upcase");
				}
		
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					return 2;
					
				}
				if (checktrungmavt(ds_vt, d) == true)
				{
					mavt = true;
					strcat(c_mavattu2, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto SL2;
				}
				if (ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) || // them hd
					ktVT(9, 229, 1181, 900, x, y))
				{
					goto batdau2;
				}
			}
			if (ktVT(110, 195, 350, 220, x, y))
			{
				//Soluong
				resetbaoloi();
			SL2:
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT2;
				}
				if (soluong == true)
				{
					d = input_bill(x, y, 220, 196, 350, 220, 5, 3, 985, 125, 1175, 215, c_soluongvt, 5, "number", "calmCase");
					strcpy(c_soluongvt, "");
				}
				if (soluong == false)
				{
					d = input_bill(x, y, 220, 196, 350, 220, 5, 3, 985, 125, 1175, 215, "", 5, "number", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					return 2;
				}
				if (empty(d) == true)
				{
					soluong = false;
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto DG2;
				}
				if (checksoluong(ds_vt, c_mavattu2, d) == false && xuat == true)
				{
					soluong = false;
					text_box(985, 125, 1175, 215, (char*)"Ko du so luong!", f_medium, 2, 30, 8, RED, 0, 0);
					text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
					khung_b_nhd();
					goto SL2;
				}
				if (checksoluongnhap(ds_vt, c_mavattu2, d) == false && nhap == true)
				{
					soluong = false;
					text_box(985, 125, 1175, 215, (char*)"SLnhap qua lon!", f_medium, 2, 30, 8, RED, 0, 0);
					text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
					khung_b_nhd();
					goto SL2;
				}
				if (nhap == true)
				{
					soluong = true;
					strcat(c_soluongvt, d.c_str());
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto DG2;
				}
				if (checksoluong(ds_vt, c_mavattu2, d) == true && xuat == true)
				{
					soluong = true;
					strcat(c_soluongvt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto DG2;
				}
				if (ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) || // them hd
					ktVT(9, 229, 1181, 900, x, y))
				{
					goto batdau2;
				}
			}
			if (ktVT(350, 195, 590, 220, x, y))
			{
				//Dongia
				resetbaoloi();
			DG2:
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT2;
				}
				if (dongia == true)
				{
					d = input_bill(x, y, 450, 196, 590, 220, 5, 3, 985, 125, 1175, 215, c_dongiavt, 6, "number", "calmCase");
					strcpy(c_dongiavt, "");
				}
				if (dongia == false)
				{
					d = input_bill(x, y, 450, 196, 590, 220, 5, 3, 985, 125, 1175, 215, "", 6, "number", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					return 2;
				}
				if (empty(d) == true)
				{
					dongia = false;
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto VAT2;
				}
				if (empty(d) == false)
				{
					dongia = true;
					strcpy(c_dongiavt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto VAT2;
				}
				if (ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) || // them hd
					ktVT(9, 229, 1181, 900, x, y))
				{
					goto batdau2;
				}
			}
			if (ktVT(430, 170, 590, 195, x, y))
			{
				//VAT
				resetbaoloi();
			VAT2:
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT2;
				}
				if (vat == true)
				{
					d = input_bill(x, y, 495, 171, 590, 195, 5, 3, 985, 125, 1175, 215, c_vatvt, 4, "decimal", "calmCase");
					strcpy(c_vatvt, "10");
				}
				if (vat == false)
				{
					d = input_bill(x, y, 495, 171, 590, 195, 5, 3, 985, 125, 1175, 215, "10", 4, "decimal", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					return 2;
				}
				if (empty(d) == true)
				{
					vat = false;
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
				}
				if (empty(d) == false)
				{
					vat = true;
					strcpy(c_vatvt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) || // them hd
						ktVT(9, 229, 1181, 900, x, y))
					{
						goto batdau2;
					}
					goto THEMVT2;
				}
				if (ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) || // them hd
					ktVT(9, 229, 1181, 900, x, y))
				{
					goto batdau2;
				}
				goto THEMVT2;
			}
			//check truoc khi them vt
			if (ktVT(620, 145, 770, 170, x, y))
			{
			THEMVT2:
				if (mavt == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap MaVT!", f_medium, 2, 30, 8, RED, 0, 0);
					goto MAVT2;
				}
				if (soluong == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap Soluong!", f_medium, 2, 30, 8, RED, 0, 0);
					goto SL2;
				}
				if (dongia == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap Dongia!", f_medium, 2, 30, 8, RED, 0, 0);
					goto DG2;
				}
				if (vat == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap %VAT!", f_medium, 2, 30, 8, RED, 0, 0);
					goto VAT2;
				}
				if (mavt == true && soluong == true && dongia == true && (nhap == true || xuat == true))
				{
					text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 14, 0);
					text_box(985, 125, 1175, 215, (char*)"Da them VT", f_medium, 2, 30, 8, LIGHTGREEN, 0, 0);
					delay(800);
					resetbaoloi();
					text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
					themvttamthoi(hd, n, c_mavattu2, c_soluongvt, c_dongiavt, c_vatvt, nhap, xuat);
					khung_b_nhd();
					goto lannua;
				}
			}
			if (ktVT(800, 145, 950, 170, x, y))
			{
				if (hd.first_cthd != NULL) themvt = true;
				if (themvt == false)
				{
					text_box(985, 125, 1175, 215, (char*)"chua co VT!", f_medium, 2, 30, 8, RED, 0, 0);
					goto batdau2;
				}
				if (themvt == true)
				{
					text_box_no_border(800, 145, 950, 170, (char*)"Luu hoa don", f_medium, 2, 1, 5, 14, 0);
					text_box(985, 125, 1175, 215, (char*)"Da them HD", f_medium, 2, 30, 8, LIGHTGREEN, 0, 0);
					strcpy(hd.SoHD, c_sohoadon);
					hd.date.ngay = stoi(curr_date);
					hd.date.thang = stoi(curr_month);
					hd.date.nam = stoi(curr_year);
					if (nhap == true)
					{
						strcpy(hd.Loai, "N");
						chuyentrangthainhap(hd, ds_vt);
					}
					if (xuat == true)
					{
						strcpy(hd.Loai, "X");
						chuyentrangthaixuat(hd, ds_vt);
					}

					Insert_last_HD(ds_nv.nhan_vien[search_ID_Staff(ds_nv, c_manhanvien)]->ds_hoadon, hd);
					write_file_staff(ds_nv);
					delay(800);
					resetbaoloi();
					text_box_no_border(800, 145, 950, 170, (char*)"Luu hoa don", f_medium, 2, 1, 5, 11, 0);
					khunglan1();
					delete_bill_table();
					themvt = false;
					break;
				}

			}
			if (ktVT(20, 130, 100, 170, x, y) || //nhap
				ktVT(20, 170, 100, 210, x, y) || //xuat
				ktVT(110, 120, 590, 145, x, y) || //sohd
				ktVT(590, 120, 980, 145, x, y)) // manv
			{
				continue;
			}
			if (ktVT(20, 10, 220, 50, x, y) || //vat tu
				ktVT(320, 10, 520, 50, x, y) || // nhan vien
				ktVT(620, 10, 820, 50, x, y) || // thanh toan
				ktVT(920, 10, 1120, 50, x, y) || // thong ke
				ktVT(15, 70, 310, 110, x, y) || // lap hoa don
				ktVT(350, 70, 645, 110, x, y) || // tra hang
				ktVT(685, 70, 980, 110, x, y)||
				ktVT(1140, 10, 1190, 50, x, y)) // thoat
			{
				return 2;
			}
			
		bang:
			b_handle_table(x, y, hd, n, delete_table_b, edit_table_b, vp_b_table, nhd_isEdit, ds_vt);
			if (hd.first_cthd != NULL)
			{
				delete_after_header();
				b_create_menu_title();
				highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
				khunglan2(c_sohoadon, c_manhanvien, nhap, xuat);
				bill_nhd_table(hd, vp_b_table, edit_table_b, delete_table_b, 7, n, ds_vt);
				long double TONGCONG = tongPhanTuDSLKD(hd);
				text_box_no_border(590, 170, 980, 195, (char*)"TONG CONG", f_medium, 2, 5, 130, 15, 0);
				text_box_no_border(590, 195, 980, 220, (char*)formatNumber(long long(TONGCONG)).c_str(), f_medium, 2, 1, 30, 15, 0);
				text_box_no_border(220, 196, 350, 220, c_soluongvt, f_medium, 1, 3, 5, 9);
				text_box_no_border(450, 196, 590, 220, c_dongiavt, f_medium, 1, 3, 5, 9);
				text_box_no_border(495, 171, 590, 195, c_vatvt, f_medium, 1, 3, 5, 9);
				khunglan2(c_sohoadon, c_manhanvien, nhap, xuat);
				text_box_no_border(235, 171, 430, 195, (char*)d.c_str(), f_medium, 1, 3, 5, 9);
				khung_b_nhd();
			}
			else
			{
				delete_after_header();
				b_create_menu_title();
				highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
				khunglan2(c_sohoadon, c_manhanvien, nhap, xuat);
				text_box_no_border(590, 170, 980, 195, (char*)"TONG CONG", f_medium, 2, 5, 130, 15, 0);
				text_box_no_border(590, 195, 980, 220, TONGCONG_char, f_medium, 2, 1, 30, 15, 0);
				khung_b_nhd();
				goto MAVT2;
			}
			

		}
	}
}



void nhd_bill(int& x, int& y, DS_NhanVien& ds_nv, DS_VatTu*& ds_vt, DS_s_VT *& ds_s_vt)
{
nhd:
	HoaDon hd;
	Initialize_CTHD(hd.first_cthd);

	check_CURD chonnv;
	view_page vp_manv_table;
	bool manv_isChon = false;
	check_CURD chon;
	view_page vp_mavt_table;
	bool mavt_isChon = false;

	int n = 0;
	string a = "0";
	string d;
	char c_sohoadon[21] = "";
	char c_manhanvien[11] = "";
	char c_mavattu[11] = "";
	char c_soluongvt[11] = "";
	char c_dongiavt[11] = "";
	char c_vatvt[6] = "10";

	char mavtphu[11] = "";
	char manvphu[11] = "";

	string e_search_manv = "";
	string e_search_mavt = "";

	bool nhap = false, xuat = false;
	bool sohd = false, manv = false, mavt = false, soluong = false, dongia = false, vat = true;
	bool themvt = false;

	time_t now = time(0);
	tm* ltm = localtime(&now);
	string curr_date = to_string(ltm->tm_mday);
	string curr_month = to_string(1 + ltm->tm_mon);
	string curr_year = to_string(1900 + ltm->tm_year);

	b_create_menu_title();
	highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
	b_delete_after_create();
	setlinestyle(0, 0, 1);
	khunglan1();
	khung_b_nhd();
		
	

	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
		batdau:
			// NHAP XUAT
			if (ktVT(20, 130, 100, 170, x, y))
			{
				resetbaoloi();
				text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
				text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
				khung_b_nhd();
				nhap = true; xuat = false; mavt = false; strcpy(c_mavattu, "");
				continue;

			}
			if (ktVT(20, 170, 100, 210, x, y))
			{
				resetbaoloi();
				text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
				text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
				khung_b_nhd();
				nhap = false; xuat = true; mavt = false; strcpy(c_mavattu, "");
				continue;
			}
			if (ktVT(110, 120, 590, 145, x, y))
			{
				//SoHD
				resetbaoloi();
			SOHD:
				if (sohd == true)
				{
					d = input_bill(x, y, 250, 121, 590, 145, 5, 3, 985, 125, 1175, 215, c_sohoadon, 20, "textNumberNoSpace", "upcase");
					strcpy(c_sohoadon, "");
				}
				if (sohd == false) {

					d = input_bill(x, y, 250, 121, 590, 145, 5, 3, 985, 125, 1175, 215, "", 20, "textNumberNoSpace", "upcase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				if (empty(d) == true)
				{
					sohd = false;
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					if (manv == false) goto MANV;
					if (mavt == false) goto MAVT;
					if (soluong == false) goto SL;
					if (dongia == false) goto DG;
					if (vat == false) goto VAT;
				}
				if (checktrungshd(ds_nv, d) == true)
				{
					sohd = false;
					text_box(985, 125, 1175, 215, (char*)"Loi!Trung SoHD", f_medium, 2, 30, 8, RED, 0, 0);
					text_box_no_border(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 9, 0);
					khung_b_nhd();
					goto SOHD;
				}
				if (checktrungshd(ds_nv, d) == false)
				{
					sohd = true;
					strcat(c_sohoadon, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					if(manv == false) goto MANV;
					if (mavt == false) goto MAVT;
					if (soluong == false) goto SL;
					if (dongia == false) goto DG;
					if (vat == false) goto VAT;
					
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}
			if (ktVT(590, 120, 980, 145, x, y))
			{
				//maNV
				resetbaoloi();
			MANV:
				if (manv == true)
				{
					bool manv_out = manv_handle_table(x, y, ds_nv, chon, vp_manv_table, manv_isChon,manvphu, e_search_manv);
					if (b_page == true)
					{
						d = manvphu;
						strcpy(manvphu, "");
						delete_after_header();
						createHeader(header_title);
						highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
						b_create_menu_title();
						highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						setlinestyle(0, 0, 1);
						khunglan1();
						//nx
						if (nhap == true)
						{
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						}
						if (xuat == true)
						{
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						}
						text_box_no_border(250, 121, 590, 145, c_sohoadon, f_medium, 1, 3, 5, 9);
						text_box_no_border(235, 171, 430, 195, c_mavattu, f_medium, 1, 3, 5, 9);
						text_box_no_border(220, 196, 350, 220, c_soluongvt, f_medium, 1, 3, 5, 9);
						text_box_no_border(450, 196, 590, 220, c_dongiavt, f_medium, 1, 3, 5, 9);
						text_box_no_border(495, 171, 590, 195, c_vatvt, f_medium, 1, 3, 5, 9);
						khung_b_nhd();
						text_box_no_border(750, 121, 980, 145, (char*)d.c_str(), f_medium, 1, 3, 5, 9);


						//d = input_bill(x, y, 750, 121, 980, 145, 5, 3, 985, 125, 1175, 215, c_manhanvien, 10, "textNumberNoSpace", "upcase");
						strcpy(c_manhanvien, "");
					}
				}
				if (manv == false)
				{
					bool manv_out = manv_handle_table(x, y, ds_nv, chon, vp_manv_table, manv_isChon, manvphu, e_search_manv);
					if (b_page == true)
					{
						d = manvphu;
						strcpy(manvphu, "");
						delete_after_header();
						createHeader(header_title);
						highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
						b_create_menu_title();
						highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						setlinestyle(0, 0, 1);
						khunglan1();
						//nx
						if (nhap == true)
						{
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						}
						if (xuat == true)
						{
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						}
						text_box_no_border(250, 121, 590, 145, c_sohoadon, f_medium, 1, 3, 5, 9);
						text_box_no_border(235, 171, 430, 195, c_mavattu, f_medium, 1, 3, 5, 9);
						text_box_no_border(220, 196, 350, 220, c_soluongvt, f_medium, 1, 3, 5, 9);
						text_box_no_border(450, 196, 590, 220, c_dongiavt, f_medium, 1, 3, 5, 9);
						text_box_no_border(495, 171, 590, 195, c_vatvt, f_medium, 1, 3, 5, 9);
						khung_b_nhd();
						text_box_no_border(750, 121, 980, 145, (char*)d.c_str(), f_medium, 1, 3, 5, 9);

						//d = input_bill(x, y, 750, 121, 980, 145, 5, 3, 985, 125, 1175, 215, "", 10, "textNumberNoSpace", "upcase");
					}
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}

				if (checktrungmanv(ds_nv, d) == true)
				{
					manv = true;
					strcat(c_manhanvien, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					//goto MAVT;
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}
			if (ktVT(110, 170, 430, 195, x, y))
			{
				//MAVT
				resetbaoloi();
			MAVT:
				if (nhap == false && xuat == false)
				{
					text_box(985, 125, 1175, 215, (char*)"xin chon N/X!", f_medium, 2, 30, 8, RED, 0, 0);
					continue;
					if (ktVT(20, 130, 100, 170, x, y))
					{
						resetbaoloi();
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = true; xuat = false;mavt = false;
						
						continue;
					}
					if (ktVT(20, 170, 100, 210, x, y))
					{
						resetbaoloi;
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = false; xuat = true;mavt = false;
						continue;
					}
				}
				if (mavt == true)
				{

					bool mavt_out = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, mavt_isChon, mavtphu, xuat, nhap,hd, e_search_mavt);
					if (b_page == true)
					{
						d = mavtphu;
						strcpy(mavtphu, "");
						delete_after_header();
						createHeader(header_title);
						highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
						b_create_menu_title();
						highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						setlinestyle(0, 0, 1);
						khunglan1();
						//nx
						if (nhap == true)
						{
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						}
						if (xuat == true)
						{
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						}
						text_box_no_border(250, 121, 590, 145, c_sohoadon, f_medium, 1, 3, 5, 9);
						text_box_no_border(750, 121, 980, 145, c_manhanvien, f_medium, 1, 3, 5, 9);
						text_box_no_border(220, 196, 350, 220, c_soluongvt, f_medium, 1, 3, 5, 9);
						text_box_no_border(450, 196, 590, 220, c_dongiavt, f_medium, 1, 3, 5, 9);
						text_box_no_border(495, 171, 590, 195, c_vatvt, f_medium, 1, 3, 5, 9);
						khung_b_nhd();
						text_box_no_border(235, 171, 430, 195, (char*)d.c_str(), f_medium, 1, 3, 5, 9);

						//d = input_bill(x, y, 235, 171, 430, 195, 5, 3, 985, 125, 1175, 215, c_mavattu, 10, "textNumberNoSpace", "upcase");
						strcpy(c_mavattu, "");
					}
				}
				if (mavt == false)
				{
					// doan nay ne 
					bool mavt_out = mavt_handle_table(x, y, ds_vt, ds_s_vt, chon, vp_mavt_table, mavt_isChon,mavtphu,xuat, nhap,hd, e_search_mavt);
					if (b_page == true)
					{
						d = mavtphu;
						strcpy(mavtphu, "");
						delete_after_header();
						createHeader(header_title);
						highlight_box(620, 10, 820, 50, header_title[2], f_medium, 3, 10, 35);
						b_create_menu_title();
						highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						setlinestyle(0, 0, 1);
						khunglan1();
						if (nhap == true)
						{
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						}
						if (xuat == true)
						{
							text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
							text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						}
						text_box_no_border(250, 121, 590, 145, c_sohoadon, f_medium, 1, 3, 5, 9);
						text_box_no_border(750, 121, 980, 145, c_manhanvien, f_medium, 1, 3, 5, 9);
						text_box_no_border(220, 196, 350, 220, c_soluongvt, f_medium, 1, 3, 5, 9);
						text_box_no_border(450, 196, 590, 220, c_dongiavt, f_medium, 1, 3, 5, 9);
						text_box_no_border(495, 171, 590, 195, c_vatvt, f_medium, 1, 3, 5, 9);
						khung_b_nhd();
						text_box_no_border(235, 171, 430, 195, (char*)d.c_str(), f_medium, 1, 3, 5, 9);
					}
			
					
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				if (checktrungmavt(ds_vt, d) == true)
				{
					mavt = true;
					strcat(c_mavattu, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto SL;
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}
			if (ktVT(110, 195, 350, 220, x, y))
			{
				//Soluong
				resetbaoloi();
			SL:
				if (nhap == false && xuat == false)
				{
					text_box(985, 125, 1175, 215, (char*)"xin chon N/X!", f_medium, 2, 30, 8, RED, 0, 0);
					continue;
					if (ktVT(20, 130, 100, 170, x, y))
					{
						resetbaoloi();
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = true; xuat = false; mavt = false; strcpy(c_mavattu, "");

						continue;
					}
					if (ktVT(20, 170, 100, 210, x, y))
					{
						resetbaoloi;
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = false; xuat = true; mavt = false; strcpy(c_mavattu, "");
						continue;
					}
				}
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT;
				}
				if (soluong == true)
				{
					d = input_bill(x, y, 220, 196, 350, 220, 5, 3, 985, 125, 1175, 215, c_soluongvt, 5, "number", "calmCase");
					strcpy(c_soluongvt, "");
				}
				if (soluong == false)
				{
					d = input_bill(x, y, 220, 196, 350, 220, 5, 3, 985, 125, 1175, 215, "", 5, "number", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				if (empty(d) == true)
				{
					soluong = false;
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto DG;
				}
				
				if (nhap == true)
				{
					soluong = true;
					strcat(c_soluongvt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto DG;
				}
				if (checksoluong(ds_vt, c_mavattu, d) == false && xuat == true)
				{
					soluong = false;
					text_box(985, 125, 1175, 215, (char*)"Ko du so luong!", f_medium, 2, 30, 8, RED, 0, 0);
					text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
					khung_b_nhd();
					goto SL;
				}
				if (checksoluongnhap(ds_vt, c_mavattu, d) == false && nhap == true)
				{
					soluong = false;
					text_box(985, 125, 1175, 215, (char*)"SLnhap qua lon!", f_medium, 2, 30, 8, RED, 0, 0);
					text_box_no_border(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
					khung_b_nhd();
					goto SL;
				}
				if (checksoluong(ds_vt, c_mavattu, d) == true && xuat == true)
				{
					soluong = true;
					strcat(c_soluongvt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto DG;
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}
			if (ktVT(350, 195, 590, 220, x, y))
			{
				//Dongia
				resetbaoloi();
			DG:
				if (nhap == false && xuat == false)
				{
					text_box(985, 125, 1175, 215, (char*)"xin chon N/X!", f_medium, 2, 30, 8, RED, 0, 0);
					continue;
					if (ktVT(20, 130, 100, 170, x, y))
					{
						resetbaoloi();
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = true; xuat = false; mavt = false; strcpy(c_mavattu, "");

						continue;
					}
					if (ktVT(20, 170, 100, 210, x, y))
					{
						resetbaoloi;
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = false; xuat = true; mavt = false; strcpy(c_mavattu, "");
						continue;
					}
				}
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT;
				}
				if (dongia == true)
				{
					d = input_bill(x, y, 450, 196, 590, 220, 5, 3, 985, 125, 1175, 215, c_dongiavt, 6, "number", "calmCase");
					strcpy(c_dongiavt, "");
				}
				if (dongia == false)
				{
					d = input_bill(x, y, 450, 196, 590, 220, 5, 3, 985, 125, 1175, 215, "", 6, "number", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				if (empty(d) == true)
				{
					dongia = false;
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto VAT;
				}
				if (empty(d) == false)
				{
					dongia = true;
					strcpy(c_dongiavt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto VAT;
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}
			if (ktVT(430, 170, 590, 195, x, y))
			{
				//VAT
				resetbaoloi();
			VAT:
				if (nhap == false && xuat == false)
				{
					text_box(985, 125, 1175, 215, (char*)"xin chon N/X!", f_medium, 2, 30, 8, RED, 0, 0);
					continue;
					if (ktVT(20, 130, 100, 170, x, y))
					{
						resetbaoloi();
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = true; xuat = false; mavt = false; strcpy(c_mavattu, "");

						continue;
					}
					if (ktVT(20, 170, 100, 210, x, y))
					{
						resetbaoloi;
						text_box_no_border(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
						text_box_no_border(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
						khung_b_nhd();
						nhap = false; xuat = true; mavt = false; strcpy(c_mavattu, "");
						continue;
					}
				}
				if (mavt == false)
				{
					announce_board(x, y, 40, 20, "Chon Ma Vat Tu!");
					delay(1000);
					goto MAVT;
				}
				if (vat == true)
				{
					d = input_bill(x, y, 495, 171, 590, 195, 5, 3, 985, 125, 1175, 215, c_vatvt, 4, "decimal", "calmCase");
					strcpy(c_vatvt, "10");
				}
				if (vat == false)
				{
					d = input_bill(x, y, 495, 171, 590, 195, 5, 3, 985, 125, 1175, 215, "10", 4, "decimal", "calmCase");
				}
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				if (empty(d) == true)
				{
					vat = false;
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto THEMVT;
				}
				if (empty(d) == false)
				{
					vat = true;
					strcpy(c_vatvt, d.c_str());
					// if click chuyen o input
					if (ktVT(110, 120, 590, 145, x, y) || //sohd
						ktVT(590, 120, 980, 145, x, y) || //manv
						ktVT(110, 170, 430, 195, x, y) || //mavt
						ktVT(110, 195, 350, 220, x, y) || //soluong
						ktVT(350, 195, 590, 220, x, y) || //dongia
						ktVT(430, 170, 590, 195, x, y) || //vat
						ktVT(620, 145, 770, 170, x, y) || // them vt
						ktVT(800, 145, 950, 170, x, y) ||// them hd
						ktVT(20, 130, 100, 170, x, y) || // nhap
						ktVT(20, 170, 100, 210, x, y))  // xuat
					{
						goto batdau;
					}
					goto THEMVT;
				}
				if (ktVT(110, 120, 590, 145, x, y) || //sohd
					ktVT(590, 120, 980, 145, x, y) || //manv
					ktVT(110, 170, 430, 195, x, y) || //mavt
					ktVT(110, 195, 350, 220, x, y) || //soluong
					ktVT(350, 195, 590, 220, x, y) || //dongia
					ktVT(430, 170, 590, 195, x, y) || //vat
					ktVT(620, 145, 770, 170, x, y) || // them vt
					ktVT(800, 145, 950, 170, x, y) ||// them hd
					ktVT(20, 130, 100, 170, x, y) || // nhap
					ktVT(20, 170, 100, 210, x, y))  // xuat
				{
					goto batdau;
				}
			}

			//check truoc khi them vt
			if (ktVT(620, 145, 770, 170, x, y))
			{
			THEMVT:
				if (sohd == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap SoHD!", f_medium, 2, 30, 8, RED, 0, 0);
					goto SOHD;
				}
				if (manv == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap MaNV!", f_medium, 2, 30, 8, RED, 0, 0);
					goto MANV;
				}
				if (mavt == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap MaVT!", f_medium, 2, 30, 8, RED, 0, 0);
					goto MAVT;
				}
				if (soluong == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap Soluong!", f_medium, 2, 30, 8, RED, 0, 0);
					goto SL;
				}
				if (dongia == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap Dongia!", f_medium, 2, 30, 8, RED, 0, 0);
					goto DG;
				}
				if (vat == false) {
					text_box(985, 125, 1175, 215, (char*)"nhap %VAT!", f_medium, 2, 30, 8, RED, 0, 0);
					goto VAT;
				}
				if (sohd == true && manv == true && mavt == true && soluong == true && dongia == true && (nhap == true || xuat == true))
				{
					text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 14, 0);
					text_box(985, 125, 1175, 215, (char*)"Da them VT", f_medium, 2, 30, 8, LIGHTGREEN, 0, 0);
					delay(800);
					resetbaoloi();
					text_box_no_border(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
					khung_b_nhd();
					themvttamthoi(hd, n, c_mavattu, c_soluongvt, c_dongiavt, c_vatvt, nhap, xuat);
					khung_b_nhd();
					//vat tu lan 2 tu day xuong
					int thoat2 = saukhithemvt(hd, n, c_sohoadon, c_manhanvien, nhap, xuat, x, y, ds_nv, ds_vt, ds_s_vt, e_search_mavt);
					if(thoat2 == 2)
					{
						break;
					}
					goto nhd;
				}
			}
			if (ktVT(800, 145, 950, 170, x, y))
			{
				text_box(985, 125, 1175, 215, (char*)"chua co VT!", f_medium, 2, 30, 8, RED, 0, 0);
				continue;
			}


			if (ktVT(20, 10, 220, 50, x, y) || //vat tu
				ktVT(320, 10, 520, 50, x, y) || // nhan vien
				ktVT(620, 10, 820, 50, x, y) || // thanh toan
				ktVT(920, 10, 1120, 50, x, y) || // thong ke
				ktVT(15, 70, 310, 110, x, y) || // lap hoa don
				ktVT(350, 70, 645, 110, x, y) || // tra hang
				ktVT(685, 70, 980, 110, x, y) || // in hoa don
				ktVT(1140, 10, 1190, 50, x, y)) // thoat
			{
				break;
			}
		}
		delay(1);
	}
end:;
}

bool lonhon3ngaykhong(int day1, int month1, int year1, int day2, int month2, int year2)
{
	struct tm date1 = { 0, 0, 0, day1, month1 - 1, year1 - 1900 };
	struct tm date2 = { 0, 0, 0, day2, month2 - 1, year2 - 1900 };

	// Chuyển struct tm thành time_t
	time_t t1 = mktime(&date1);
	time_t t2 = mktime(&date2);

	// Tính số giây chênh lệch giữa hai ngày tháng
	double diff = difftime(t2, t1);

	// Nếu chênh lệch lớn hơn 3 ngày, trả về true
	if (diff > 3 * 24 * 60 * 60 || diff < -3 * 24 * 60 * 60)
		return true;

	return false;
}


HoaDon checkshdtrahang(DS_NhanVien ds_nv, string d)
{
	for (int i = 0; i < ds_nv.length; i++)
	{
		DS_HoaDon* curr_hd = ds_nv.nhan_vien[i]->ds_hoadon; // trỏ đến danh sách hóa đơn của nhân viên hiện tại
		while (curr_hd != NULL) // duyệt từng hóa đơn trong danh sách
		{
			if (strcmp(curr_hd->hoadon.SoHD, d.c_str()) == 0) // nếu trùng số hóa đơn
			{
				return curr_hd->hoadon; // trả về hóa đơn tương ứng
			}
			curr_hd = curr_hd->next; // chuyển đến hóa đơn tiếp theo trong danh sách
		}
	}
}

bool checknhapxuattrahang(HoaDon p)
{
	if (p.Loai[0] == 'N') return false;
	if (p.Loai[0] == 'X') return true;
}

bool checkconcainaochuatrakhong(HoaDon p)
{
	dscthd current = p.first_cthd;
	while (current != NULL)
	{
		if (current->ct_hoadon.TrangThai == 1) return true;
		current = current->next;
	}
	return false;
}

NhanVien* checknhanvientrahang(DS_NhanVien& ds_nv, string d)
{
	for (int i = 0; i < ds_nv.length; i++)
	{
		DS_HoaDon* curr_hd = ds_nv.nhan_vien[i]->ds_hoadon; // trỏ đến danh sách hóa đơn của nhân viên hiện tại
		while (curr_hd != NULL) // duyệt từng hóa đơn trong danh sách
		{
			if (strcmp(curr_hd->hoadon.SoHD, d.c_str()) == 0) // nếu trùng số hóa đơn
			{
				return ds_nv.nhan_vien[i]; // trả về nhân viên tương ứng với hóa đơn
			}
			curr_hd = curr_hd->next; // chuyển đến hóa đơn tiếp theo trong danh sách
		}
	}
	return NULL; // nếu không tìm thấy hóa đơn, trả về NULL
}

void duyetlaihdsaukhitrahang(HoaDon tra, HoaDon phu, DS_VatTu*& ds_vt, HoaDon& hd)
{
	dscthd current_a = hd.first_cthd;
	while (current_a != NULL) { // duyệt qua từng phần tử trong danh sách a
		if (phu.first_cthd == NULL)
		{
			current_a->ct_hoadon.TrangThai = false; // nếu tìm thấy thì gán TrangThai của a là false

			cout << "666" << current_a->ct_hoadon.MAVT;
			TimKiemNode(ds_vt, current_a->ct_hoadon.MAVT)->vat_tu.sldaban--;
			TimKiemNode(ds_vt, current_a->ct_hoadon.MAVT)->vat_tu.SLT += current_a->ct_hoadon.Soluong;
			write_file_goods(ds_vt);
			current_a = current_a->next;
		}
		if (phu.first_cthd != NULL)
		{
			dscthd current_b = tra.first_cthd;
			while (current_b != NULL) { // tìm kiếm trường MAVT trong danh sách b
				if (strcmp(current_a->ct_hoadon.MAVT, current_b->ct_hoadon.MAVT) == 0) {
					current_a->ct_hoadon.TrangThai = false; // nếu tìm thấy thì gán TrangThai của a là false
					TimKiemNode(ds_vt, current_a->ct_hoadon.MAVT)->vat_tu.sldaban--;
					TimKiemNode(ds_vt, current_a->ct_hoadon.MAVT)->vat_tu.SLT += current_a->ct_hoadon.Soluong;
					write_file_goods(ds_vt);
					break; // thoát khỏi vòng lặp tìm kiếm
				}
				current_b = current_b->next;
			}
			current_a = current_a->next;
		}

	}
	while (current_a != NULL)
	{
		cout << current_a->ct_hoadon.MAVT << "\n";
		cout << "vat:" << current_a->ct_hoadon.VAT;
		current_a = current_a->next;
	}
}

void khung_b_trahang()
{
	b_taokhungden(10, 120, 110, 220);
	b_taokhungden(110, 120, 980, 220);
	b_taokhungden(980, 120, 1180, 220);
	b_taokhungden(10, 120, 110, 220);
	b_taokhungden(110, 120, 590, 145);//sohd
	b_taokhungden(110, 145, 270, 170);
	b_taokhungden(270, 145, 430, 170);
	b_taokhungden(430, 145, 590, 170);
	b_taokhungden(590, 120, 980, 145);
	b_taokhungden(590, 170, 980, 195);
	b_taokhungden(590, 195, 980, 220);
	b_taokhungden(110, 170, 590, 195);
	b_taokhungden(110, 195, 590, 220);
	b_taokhungden(980, 120, 1180, 170);
	b_taokhungden(980, 170, 1180, 220);
}

void khungtrahang(HoaDon& hd, HoaDon& p, NhanVien*& nv, HoaDon& u)
{
	char ngay[10];
	char thang[10];
	char nam[10];
	snprintf(ngay, sizeof(ngay), "%d", p.date.ngay);
	snprintf(thang, sizeof(thang), "%d", p.date.thang);
	snprintf(nam, sizeof(nam), "%d", p.date.nam);
	char ten[30] = "";
	strcat(ten, nv->ho);
	strcat(ten, " ");
	strcat(ten, nv->ten);
	text_box_no_border(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(250, 121, 590, 145, p.SoHD, f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(110, 145, 270, 170, (char*)"ngay:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(180, 146, 265, 168, ngay, f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(270, 145, 430, 170, (char*)"thang:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(350, 146, 425, 168, thang, f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(430, 145, 590, 170, (char*)"nam:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(480, 146, 585, 168, nam, f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(590, 120, 980, 145, (char*)"Ma nhan vien:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(750, 121, 980, 145, (char*)nv->maNV, f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(590, 145, 980, 170, (char*)"Ten:", f_medium, 2, 1, 5, 15, 0);
	text_box_no_border(650, 145, 980, 170, ten, f_medium, 2, 1, 5, 15, 0);
	if (p.Loai[0] == 'N')
	{
		text_box_no_border(10, 120, 110, 220, (char*)"N", f_medium, 8, 10, 25, 15, 0);
	}
	if (p.Loai[0] == 'X')
	{
		text_box_no_border(10, 120, 110, 220, (char*)"X", f_medium, 8, 10, 25, 15, 0);
	}
	long double TONGCONGtra = tongPhanTuDSLKD(u);
	long double TONGCONG = tongPhanTuDSLKD(hd);
	text_box_no_border(110, 170, 590, 195, (char*)"TRA LAI CHO KHACH", f_medium, 2, 5, 120, 15, 0);
	text_box_no_border(110, 195, 590, 220, (char*)formatNumber(long long(TONGCONGtra)).c_str(), f_medium, 2, 1, 30, 15, 0);
	text_box_no_border(590, 170, 980, 195, (char*)"TONG CONG CON LAI", f_medium, 2, 5, 90, 15, 0);
	text_box_no_border(590, 195, 980, 220, (char*)formatNumber(long long(TONGCONG)).c_str(), f_medium, 2, 1, 30, 15, 0);
	text_box_no_border(980, 120, 1180, 170, (char*)"XAC NHAN", f_medium, 4, 10, 20, XANH_DUONG_NHAT, 0);
	text_box_no_border(980, 170, 1180, 220, (char*)"HUY", f_medium, 4, 10, 60, XANH_DUONG_NHAT, 0);
	khung_b_trahang();

}

bool bill_announce_board(int x, int y, int kcl = 0, int kct = 0, string value = "", string type = "noClose", int bg = COLOR(232, 246, 250)) { // 200 //400 

	setfillstyle(1, bg);
	setcolor(I_ERROR_COLOR);
	bar3d(420, 260, 780, 460, 0, 0);
	string temp_value;
	temp_value = "";
	int minus = 0;
	if (value.length() >= 27 && value[27] != ' ') {
		minus = 27;
		while (value[minus] != ' ') {
			minus--;
		}
		minus = 27 - minus;
	}
	int text_length = value.length() <= 27 ? value.length() : (27 - minus);
	for (int i = 0; i < text_length; i++)
	{
		temp_value += value[i];
	}
	writeText(450 + kcl, 330 + kct, (char*)temp_value.c_str(), 1, 0, f_medium, bg);
	if (value.length() > 26) {
		temp_value = "";
		for (int i = 27; i < value.length(); i++)
		{
			temp_value += value[i];
		}
		writeText(450 + kcl, 350 + kct, (char*)trim(temp_value).c_str(), 1, 0, f_medium, bg);
	}
	if (type != "noClose") {
		text_box(500, 395, 570, 420, (char*)"Co", f_medium, 1, 5, 20, bg, 0);
		text_box(610, 395, 680, 420, (char*)"Khong", f_medium, 1, 5, 6, bg, 0);
		text_box(750, 260, 780, 290, (char*)"X", f_medium, 1, 7, 9, COLOR(255, 97, 100), 0, I_ERROR_COLOR);
		while (1) {
			if (ismouseclick(WM_LBUTTONDOWN)) {
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (ktVT(500, 395, 570, 420, x, y)) {
					x = NULL;
					y = NULL;

					text_box(500, 395, 570, 420, (char*)"Co", f_medium, 1, 5, 20, XANH_LA_CAY, 0);
					delay(200);
					return 1;
				}
				if (ktVT(610, 395, 680, 420, x, y)) {
					text_box(610, 395, 680, 420, (char*)"Khong", f_medium, 1, 5, 6, XANH_LA_CAY, 0);
					delay(200);
					x = NULL;
					y = NULL;
					return 0;
				}
				if (ktVT(750, 260, 780, 290, x, y)) {
					x = NULL;
					y = NULL;
					text_box(750, 260, 780, 290, (char*)"X", f_medium, 1, 7, 9, COLOR(250, 0, 4), 0, I_ERROR_COLOR);
					delay(200);
					return 0;
				}
			}
		}
	}

	return 1;
}

void bill_trahang_table(
	HoaDon& hd,
	view_page& view_page,
	check_CURD& edit_table_b,
	int num_rows,
	DS_VatTu*& ds_vt
) {
	dscthd p;
	p = hd.first_cthd;
	setlinestyle(0, 0, 0);
	delete_bill_table();
	setcolor(0);
	int n = getNumOfCTHD(p);
	int page = n / num_rows;
	int du = n % num_rows;
	view_page.page = du ? page + 1 : page;
	if (view_page.current > view_page.page)
	{
		view_page.current--;
	}
	if (n == 0) {
		view_page.page = 1;
	}
	int max_page = n > (num_rows * view_page.current) ? (num_rows * view_page.current) : n;
	// reder page
	int i = num_rows * (view_page.current - 1);
	//header
	int bar_top = 230, bar_bottom = 260;
	int text_top = 235;
	setfillstyle(1, COLOR_HEADER_TABLE);
	setbkcolor(COLOR_HEADER_TABLE);
	settextstyle(f_small, 0, 1);
	bar3d(10, bar_top, 1180, bar_bottom, 0, 0);
	outtextxy(16, text_top, (char*)"STT");
	outtextxy(75, text_top, (char*)bill_table_header[0]);
	outtextxy(200, text_top, (char*)bill_table_header[1]);
	outtextxy(350, text_top, (char*)bill_table_header[2]);
	outtextxy(450, text_top, (char*)bill_table_header[3]);
	outtextxy(560, text_top, (char*)bill_table_header[4]);
	outtextxy(680, text_top, (char*)bill_table_header[5]);
	outtextxy(780, text_top, (char*)bill_table_header[6]);
	outtextxy(1030, text_top, (char*)bill_table_header[7]);
	setfillstyle(1, 15);
	setbkcolor(15);

	int e = 0;//trahang
	for (; i < max_page; i++)
	{

		p = getNodeByIndexdscthd(hd.first_cthd, i);
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
		//vi tri trahang
		//edit.data[e].key =string( );
		edit_table_b.data[e].l = 1030;
		edit_table_b.data[e].t = text_top;
		edit_table_b.data[e].r = 1108;
		edit_table_b.data[e].b = text_top + 22;
		e++;
		// --------------------------------- xuong day
		// row
		setcolor(0);
		bar3d(10, bar_top, 1180, bar_bottom, 0, 0);
		// title header
		int SL = p->ct_hoadon.Soluong;
		char SL_char[10];
		sprintf(SL_char, "%d", SL);

		int DG = p->ct_hoadon.Dongia;
		char DG_char[10];
		sprintf(DG_char, "%d", DG);

		float VAT = p->ct_hoadon.VAT;
		char VAT_char[8];
		snprintf(VAT_char, sizeof(VAT_char), "%.2f", VAT);

		long double TT = 0.00;
		TT = thanhtien1vt(SL, DG, VAT);
		char TT_char[20];
		snprintf(TT_char, sizeof(TT_char), "%.2Lf", TT);

		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(16, text_top, stt, 1, 0, 3, 15);
		writeText(75, text_top, p->ct_hoadon.MAVT, 1, 0, 3, 15);
		char* TENVT = timTenVT(ds_vt, p->ct_hoadon.MAVT);
		writeText(200, text_top, TENVT, 1, 0, 3, 15);
		char* DVT = timDvtVT(ds_vt, p->ct_hoadon.MAVT);
		writeText(350, text_top, DVT, 1, 0, 3, 15);
		writeText(450, text_top, SL_char, 1, 0, 3, 15);
		writeText(560, text_top, DG_char, 1, 0, 3, 15);
		writeText(680, text_top, VAT_char, 1, 0, 3, 15);
		writeText(780, text_top, TT_char, 1, 0, 3, 15);

		text_box(1030, text_top, 1108, text_top + 23, (char*)tra_hang_cn[0], f_small, 1, 1, 2);
		setfillstyle(1, 15);
		setbkcolor(15);

		p = p->next;



	}
	//------------- k can cos the xoa
	edit_table_b.n = e;
	// < >
	page_transition(view_page);
}

void trahang_handle_table(int& x, int& y, HoaDon& hd, check_CURD& edit_table_b, view_page& vp_b_table, HoaDon& tra, DS_VatTu*& ds_vt)
{
	long double TONGCONGtra;
	long double TONGCONG;
	bool break_all = false;
	int i_CRUD = 0;
	bool check_B_nhd = true;
	string keyCRUD = "";
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// edit

			for (int i = 0; i < edit_table_b.n; i++)
			{
				if (ktVT(edit_table_b.data[i].l, edit_table_b.data[i].t, edit_table_b.data[i].r, edit_table_b.data[i].b, x, y)) {
					i_CRUD = (vp_b_table.current - 1) * 7 + i;
					check_B_nhd = bill_announce_board(x, y, 40, 0, "Ban co muon tra khong.", "");
					if (check_B_nhd) {
						Insert_last_CTHD(tra.first_cthd, getNodeByvitri(hd.first_cthd, i_CRUD));
						xoaNodeByvitri(hd.first_cthd, i_CRUD);
						TONGCONGtra = tongPhanTuDSLKD(tra);
						TONGCONG = tongPhanTuDSLKD(hd);
						text_box_no_border(110, 170, 590, 195, (char*)"TRA LAI CHO KHACH", f_medium, 2, 5, 120, 15, 0);
						text_box_no_border(110, 195, 590, 220, (char*)formatNumber(long long(TONGCONGtra)).c_str(), f_medium, 2, 1, 30, 15, 0);

						text_box_no_border(590, 170, 980, 195, (char*)"TONG CONG CON LAI", f_medium, 2, 5, 90, 15, 0);
						text_box_no_border(590, 195, 980, 220, (char*)formatNumber(long long(TONGCONG)).c_str(), f_medium, 2, 1, 30, 15, 0);
						cout << "?????!!!!!";
						goto bill_end;
					}
					goto bill_end;
				}

			}
			
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_b_table.current == vp_b_table.page) {

				}
				else {
					next_page(650, 565, 685, 600, vp_b_table);
					delete_bill_table();
					bill_trahang_table( hd, vp_b_table, edit_table_b, 7, ds_vt);

				}
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_b_table.current == 1) {

				}
				else {
					prev_page(495, 565, 530, 600, vp_b_table);
					cout << vp_b_table.current;
					delete_bill_table();
					bill_trahang_table(hd, vp_b_table, edit_table_b, 7, ds_vt);

				}
			}
			if (ktVT(980, 120, 1180, 170, x, y) ||
				ktVT(980, 170, 1180, 220, x, y) ||
				ktVT(20, 10, 220, 50, x, y) || //vat tu
				ktVT(320, 10, 520, 50, x, y) || // nhan vien
				ktVT(620, 10, 820, 50, x, y) || // thanh toan
				ktVT(920, 10, 1120, 50, x, y) || // thong ke
				ktVT(15, 70, 310, 110, x, y) || // lap hoa don
				ktVT(350, 70, 645, 110, x, y) || // tra hang
				ktVT(685, 70, 980, 110, x, y) || // in hoa don
				ktVT(1140, 10, 1190, 50, x, y)) // thoat
			{
				g_page = false;
				goto bill_end;
			}
		}
		delay(1);
	}


bill_end:;

}


void trahang_bill(int& x, int& y, DS_NhanVien& ds_nv, DS_VatTu*& ds_vt)
{
batdau:
	DS_NhanVien ds_nvphu;
	HoaDon hd;
	HoaDon p, u;
	NhanVien* h;
	Initialize_CTHD(u.first_cthd);
	Initialize_CTHD(hd.first_cthd);
	read_file_staff(ds_nvphu);
	check_CURD edit_table_b;
	view_page vp_b_table;
	bool nhd_isEdit = false;
	bool check_B_trahang = true;

	char sohd[21] = "";
	bool sohoadon = false;

	time_t now = time(0);
	tm* ltm = localtime(&now);
	int mday = ltm->tm_mday;
	int mmonth = 1 + ltm->tm_mon;
	int myear = 1900 + ltm->tm_year;


	setlinestyle(0, 0, 1);
	b_create_menu_title();
	highlight_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, 14, 0);
	b_delete_after_create();
	text_box(250, 200, 950, 500, (char*)"", f_medium, 3, 0, 0, COLOR_INFOR_SS, 0);
	text_box(350, 150, 850, 200, (char*)"Vui long nhap so hoa don muon tra hang:", f_medium, 2, 15, 20, COLOR(51, 51, 51), 15);
	text_box_no_border(330, 325, 530, 355, (char*)"SO HOA DON:", f_medium, 3, 1, 1, COLOR_INFOR_SS, 0);
	text_box(525, 450, 675, 500, (char*)"Kiem tra", f_medium, 2, 15, 20, COLOR(255, 153, 51), 0);
	text_box(520, 325, 870, 355, (char*)"", f_medium, 2, 1, 1, 15, 0);

	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (ktVT(520, 325, 870, 355, x, y))
			{
			nhapsohd:
				string d = input(x, y, 520, 325, 870, 355, 15, 5, 0, 0, 50, sohd, 20, "textNumberNoSpace", "upcase", COLOR_INFOR_SS, COLOR_INFOR_SS, RED);
				if (ktVT(20, 10, 220, 50, x, y) || //vat tu
					ktVT(320, 10, 520, 50, x, y) || // nhan vien
					ktVT(620, 10, 820, 50, x, y) || // thanh toan
					ktVT(920, 10, 1120, 50, x, y) || // thong ke
					ktVT(15, 70, 310, 110, x, y) || // lap hoa don
					ktVT(350, 70, 645, 110, x, y) || // tra hang
					ktVT(685, 70, 980, 110, x, y) || // in hoa don
					ktVT(1140, 10, 1190, 50, x, y)) // thoat
				{
					break;
				}
				strcpy(sohd, d.c_str());
				goto trahang;
			}

			if (ktVT(525, 450, 675, 500, x, y))
			{
			trahang:
				if (checktrungshd(ds_nvphu, sohd) == false)
				{
					sohoadon = false;
					strcpy(sohd, "");
					text_box_no_border(520, 355, 580, 380, (char*)"KHONG TON TAI HOA DON", f_medium, 2, 1, 1, COLOR_INFOR_SS, RED);
					goto nhapsohd;
				}
				if (checktrungshd(ds_nvphu, sohd) == true)
				{
					p = checkshdtrahang(ds_nvphu, sohd);
					HoaDon tt1;
					tt1.first_cthd = getNodesByTrangThai(p.first_cthd, 1);
					h = checknhanvientrahang(ds_nvphu, sohd);
					if (checknhapxuattrahang(p) == false)
					{
						sohoadon = false;
						strcpy(sohd, "");
						text_box_no_border(520, 355, 580, 380, (char*)"KHONG PHAI HOA DON XUAT", f_medium, 2, 1, 1, COLOR_INFOR_SS, RED);
						goto nhapsohd;
					}
					if (lonhon3ngaykhong(p.date.ngay, p.date.thang, p.date.nam, mday, mmonth, myear) == true)
					{
						sohoadon = false;
						strcpy(sohd, "");
						text_box_no_border(520, 355, 580, 380, (char*)"QUA 3 NGAY. KHONG DUOC TRA HANG!", f_medium, 2, 1, 1, COLOR_INFOR_SS, RED);
						goto nhapsohd;
					}
					if (checkconcainaochuatrakhong(p) == false)
					{
						sohoadon = false;
						strcpy(sohd, "");
						text_box_no_border(520, 355, 580, 380, (char*)"HOA DON DA TRA HET VT", f_medium, 2, 1, 1, COLOR_INFOR_SS, RED);
						goto nhapsohd;
					}
					if (lonhon3ngaykhong(p.date.ngay, p.date.thang, p.date.nam, mday, mmonth, myear) == false)
					{
					th:

						if (tt1.first_cthd == NULL)
						{
							khung_b_trahang();
							delete_bill_table();
							check_B_trahang = bill_announce_board(x, y, 40, 0, "Luu Thay Doi?.", "");
							if (check_B_trahang)
							{
								hd = checkshdtrahang(ds_nv, sohd);
								duyetlaihdsaukhitrahang(u, tt1, ds_vt, hd);
								write_file_staff(ds_nv);
								goto batdau;
							}
							else goto batdau;
						}
						if (tt1.first_cthd != NULL)
						{
							if (ktVT(980, 120, 1180, 170, x, y))
							{

								check_B_trahang = bill_announce_board(x, y, 40, 0, "Luu Thay Doi?.", "");
								if (check_B_trahang) {
									hd = checkshdtrahang(ds_nv, sohd);
									duyetlaihdsaukhitrahang(u, tt1, ds_vt, hd);
									write_file_staff(ds_nv);
									goto batdau;
								}
							}
							if (ktVT(980, 170, 1180, 220, x, y))
							{
								check_B_trahang = bill_announce_board(x, y, 40, 0, "huy qua trinh tra hang!.", "");
								if (check_B_trahang) {
									goto batdau;
								}
							}
						}

						if (ktVT(20, 10, 220, 50, x, y) || //vat tu
							ktVT(320, 10, 520, 50, x, y) || // nhan vien
							ktVT(620, 10, 820, 50, x, y) || // thanh toan
							ktVT(920, 10, 1120, 50, x, y) || // thong ke
							ktVT(15, 70, 310, 110, x, y) || // lap hoa don
							ktVT(350, 70, 645, 110, x, y) || // tra hang
							ktVT(685, 70, 980, 110, x, y) || // in hoa don
							ktVT(1140, 10, 1190, 50, x, y)) // thoat
						{
							break;
						}

						b_create_menu_title();
						highlight_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, 14, 0);
						b_delete_after_create();
						khungtrahang(tt1, p, h, u);
						bill_trahang_table(tt1, vp_b_table, edit_table_b, 7, ds_vt);
						trahang_handle_table(x, y, tt1, edit_table_b, vp_b_table, u, ds_vt);

						goto th;
					}
				}
			}

			if (ktVT(20, 10, 220, 50, x, y) || //vat tu
				ktVT(320, 10, 520, 50, x, y) || // nhan vien
				ktVT(620, 10, 820, 50, x, y) || // thanh toan
				ktVT(920, 10, 1120, 50, x, y) || // thong ke
				ktVT(15, 70, 310, 110, x, y) || // lap hoa don
				ktVT(350, 70, 645, 110, x, y) || // tra hang
				ktVT(685, 70, 980, 110, x, y) || // in hoa don
				ktVT(1140, 10, 1190, 50, x, y)) // thoat
			{
				break;
			}
		}
		delay(1);
	}
}

void bill_page(int& x, int& y, DS_NhanVien& ds_nv, DS_VatTu*& ds_vt, DS_s_VT*& ds_s_vt, view_page& vp_m_print, string& soHD)
{
	bool error_soHD = false;
	bool in_hoa_don_page = false;
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
		batdau:
			if (ktVT(15, 70, 310, 110, x, y))
			{
				nhd_bill(x, y, ds_nv, ds_vt,ds_s_vt);
				goto batdau;
			}
			if (ktVT(350, 70, 645, 110, x, y))
			{
				trahang_bill(x, y, ds_nv, ds_vt);
				goto batdau;

			}
			if (ktVT(685, 70, 980, 110, x, y))
			{
				b_create_menu_title();
				highlight_box(685, 70, 980, 110, (char*)"In hoa don", f_medium, 3, 10, 40, 14, 0);
				b_delete_after_create();
				do_hoa_in_hoadon(error_soHD, vp_m_print);
				in_hoa_don_page = true;
				soHD = "";
			}
			xu_li_tra_cuu_hoa_don(x, y, error_soHD, soHD, in_hoa_don_page, ds_nv, ds_vt, vp_m_print);

			if (ktVT(20, 10, 220, 50, x, y) ||
				ktVT(320, 10, 520, 50, x, y) ||
				ktVT(620, 10, 820, 50, x, y) ||
				ktVT(920, 10, 1120, 50, x, y) ||
				ktVT(1140, 10, 1190, 50, x, y))
			{
				break;
			}

		}
		delay(1);

	}
}