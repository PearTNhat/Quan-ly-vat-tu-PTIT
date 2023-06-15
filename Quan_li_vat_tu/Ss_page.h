#pragma once

#include "Common.h";
#include "Statistic.h";

#define MAXTITLE 25
#define I_BG_SS COLOR(186, 245, 223) // màu nền khi enter nhập xong
#define I_HIGHLIGHT_SS COLOR(255, 255, 255) // highlight khi click vào
#define I_COLOR_SS 0 // màu chữ
#define I_ERROR_COLOR_SS COLOR(255,0,0) // màu của chữ khi báo lỗi

string day_b = "";
string month_b = "";
string year_b = "";
string day_e = "";
string month_e = "";
string year_e = "";
string year_dt = "";

// DANH SÁCH FUNCTION
void create_ss_header();
bool ktra_loi_input(string input, int max_value, string input_field, int input_result, int e_kcl, int e_kct, int i_error_color, int i_bg, int i_highlight, int i_color);
void get_current_date(string& day_e, string& month_e, string& year_e);
void ss_handleTable(int& x, int& y, DS_info* ds_info, view_page& vp_m_ss);
void get_current_date(string& day_e, string& month_e, string& year_e);
bool xu_li_nam_nhuan(int day, int month, int year, string& error_leap_year);
void xu_li_button_tim_kiem(int& x, int& y, bool is_all_valid, string dayb, string monthb, string yearb, string daye, string monthe, string yeare, DS_NhanVien ds_nv, view_page& vp_m_ss);
int compareDate(Date date1, Date date2);
std::string search_tenNV_by_HD(DS_NhanVien ds_nv, DS_HoaDon* hd);


DS_info* merge(DS_info* l1, DS_info* l2) {
	if (!l1) return l2;
	if (!l2) return l1;

	if (compareDate(l1->hoadon.date, l2->hoadon.date) < 0) {  
		l1->next = merge(l1->next, l2);
		return l1;
	}
	else if (compareDate(l1->hoadon.date, l2->hoadon.date) > 0) {
		l2->next = merge(l1, l2->next);
		return l2;
	}
	else { // dates are the same
		if (strcmp(l1->hoadon.SoHD, l2->hoadon.SoHD) <= 0) {
			l1->next = merge(l1->next, l2);
			return l1;
		}
		else {
			l2->next = merge(l1, l2->next);
			return l2;
		}
	}
}


DS_info* split(DS_info* head) {
	DS_info* slow = head;
	DS_info* fast = head->next;  // 1 2 3 4

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	DS_info* mid = slow->next;
	slow->next = nullptr;
	return mid;
}


DS_info* mergeSort(DS_info* head) {
	if (!head || !head->next) return head;

	DS_info* mid = split(head);
	DS_info* l1 = mergeSort(head);
	DS_info* l2 = mergeSort(mid);

	return merge(l1, l2);
}

void create_ss_header() {
	setfillstyle(1, HEADER_BACKGROUND);
	setcolor(0);
	//bar3d(10, 65, 1180, 115, 0, 0);
	text_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, ss_page_header_box_color);
	text_box(320, 70, 640, 110, (char*)"Thong ke doanh thu", f_medium, 3, 10, 40, ss_page_header_box_color);
}


void ss_table(
	DS_info* ds,
	view_page& view_page,
	int num_per_pg
) {
	delete_after_header();
	create_ss_header();
	// tinh so page co trong trang
	int n = getNumOfInfo(ds);
	int page = n / num_per_pg;
	int du = n % num_per_pg;
	view_page.page = du ? page + 1 : page;
	if (n == 0) view_page.page = 1;
	int max_rows = n > (num_per_pg * view_page.current) ? (num_per_pg * view_page.current) : n;
	// reder page
	int i = num_per_pg * (view_page.current - 1);
	// create table title
	string from_date = "Tu " + day_b + "/" + month_b + "/" + year_b + " den " + day_e + "/" + month_e + "/" + year_e;
	char m[50];
	strcpy_s(m, from_date.c_str());
	writeText(465, 140, (char*)"THONG KE HOA DON", 4, 15, 8, bk_screen);
	writeText(480, 170, m, 2, 15, 8, bk_screen);
	writeText(1000, 148, (char*)"Co", 2, 15, 8, bk_screen);
	string numOfHD_str = to_string(n);
	strcpy_s(m, numOfHD_str.c_str());
	settextjustify(CENTER_TEXT, TOP_TEXT);
	writeText(1040, 145, (char*)m, 2, 15, 3, bk_screen);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	writeText(1060, 148, (char*)"hoa don", 2, 15, 8, bk_screen);
	// header num_rows
	int bar_top = 220, bar_bottom = 252;
	int text_top = 225;
	setcolor(0);
	setfillstyle(1, COLOR(51, 51, 51)); // original color -> 6
	setbkcolor(COLOR(51, 51, 51));
	//bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	bar(50, bar_top, 1150, bar_bottom);
	setcolor(15);
	settextstyle(f_small, 0, 2);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(110, text_top, (char*)ss_table_header[0]);
	outtextxy(230, text_top, (char*)ss_table_header[1]);
	outtextxy(480, text_top, (char*)ss_table_header[2]);
	outtextxy(660, text_top, (char*)ss_table_header[3]);
	outtextxy(900, text_top, (char*)ss_table_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
	int e = 0;//edit
	for (; i < max_rows; i++)
	{
		int bkcolor = 15;
		setfillstyle(1, 15);
		if (i % 2 == 1) {
			//setfillstyle(1, COLOR(221, 221, 221));
			//bkcolor = COLOR(221, 221, 221);
			setfillstyle(1, COLOR(238, 238, 238));
			bkcolor = COLOR(238, 238, 238);
		}
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
		//setcolor(0);
		//bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
		bar(50, bar_top, 1150, bar_bottom);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(70, text_top, stt, 1, 0, 3, bkcolor);
		DS_info* tempNodeInfo = getIndexDS_InfoTable(ds, i);
		writeText(114, text_top, tempNodeInfo->hoadon.SoHD, 1, 0, 3, bkcolor);
		string full_date = "";
		full_date += to_string(tempNodeInfo->hoadon.date.ngay);
		full_date += " / ";
		full_date += to_string(tempNodeInfo->hoadon.date.thang);
		full_date += " / ";
		full_date += to_string(tempNodeInfo->hoadon.date.nam);

		char date[30];
		strcpy_s(date, full_date.c_str());
		writeText(230, text_top, date, 1, 0, 3, bkcolor);
		if (strcmp(tempNodeInfo->hoadon.Loai, "N") == 0) {
			writeText(490, text_top, (char*)"Nhap", 1, 0, 3, bkcolor);
		} else writeText(490, text_top, (char*)"Xuat", 1, 0, 3, bkcolor);
		writeText(650, text_top, tempNodeInfo->hoTenNV, 1, 0, 3, bkcolor);
		// Lấy trị giá hóa đơn
		long double triGia = 0;
		DS_CT_HoaDon* nodeCT = tempNodeInfo->hoadon.first_cthd;
		while (nodeCT != NULL) {
			if (nodeCT->ct_hoadon.TrangThai == 1) {
				triGia += ((long double)nodeCT->ct_hoadon.Dongia * (long double)nodeCT->ct_hoadon.Soluong) + ((long double)nodeCT->ct_hoadon.Dongia * (long double)nodeCT->ct_hoadon.Soluong * (long double)nodeCT->ct_hoadon.VAT / 100);
			}
			nodeCT = nodeCT->next;
		}
		string triGia_str = formatNumber((long long)triGia);
		writeText(920, text_top, (char*)triGia_str.c_str(), 1, 0, 3, bkcolor);
	}

	// < >
	page_transition(view_page);
}

void ss_table_test(
	DS_HoaDon* ds,
	DS_NhanVien ds_nv,
	view_page& view_page,
	int num_per_pg
) {
	delete_after_header();
	create_ss_header();
	// tinh so page co trong trang
	int n = getNumOfBill(ds);
	int page = n / num_per_pg;
	int du = n % num_per_pg;
	view_page.page = du ? page + 1 : page;
	if (n == 0) view_page.page = 1;
	int max_rows = n > (num_per_pg * view_page.current) ? (num_per_pg * view_page.current) : n;
	// reder page
	int i = num_per_pg * (view_page.current - 1);
	// create table title
	string from_date = "Tu " + day_b + "/" + month_b + "/" + year_b + " den " + day_e + "/" + month_e + "/" + year_e;
	char m[50];
	strcpy_s(m, from_date.c_str());
	writeText(465, 140, (char*)"THONG KE HOA DON", 4, 15, 8, bk_screen);
	writeText(480, 170, m, 2, 15, 8, bk_screen);
	// header num_rows
	int bar_top = 220, bar_bottom = 252;
	int text_top = 225;
	setcolor(0);
	setfillstyle(1, COLOR(51, 51, 51)); // original color -> 6
	setbkcolor(COLOR(51, 51, 51));
	//bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
	bar(50, bar_top, 1150, bar_bottom);
	setcolor(15);
	settextstyle(f_small, 0, 2);
	outtextxy(55, text_top, (char*)"STT");
	outtextxy(110, text_top, (char*)ss_table_header[0]);
	outtextxy(230, text_top, (char*)ss_table_header[1]);
	outtextxy(480, text_top, (char*)ss_table_header[2]);
	outtextxy(660, text_top, (char*)ss_table_header[3]);
	outtextxy(900, text_top, (char*)ss_table_header[4]);
	setfillstyle(1, 15);
	setbkcolor(15);
	for (; i < max_rows; i++)
	{
		int bkcolor = 15;
		setfillstyle(1, 15);
		if (i % 2 == 1) {\
			setfillstyle(1, COLOR(238, 238, 238));
			bkcolor = COLOR(238, 238, 238);
		}
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
		bar(50, bar_top, 1150, bar_bottom);
		// title header
		char stt[10];
		strcpy_s(stt, to_string(i + 1).c_str());
		writeText(70, text_top, stt, 1, 0, 3, bkcolor);
		DS_HoaDon* tempNodeInfo = getIndexBill(ds, i);
		writeText(114, text_top, tempNodeInfo->hoadon.SoHD, 1, 0, 3, bkcolor);
		string full_date = "";
		full_date += to_string(tempNodeInfo->hoadon.date.ngay);
		full_date += " / ";
		full_date += to_string(tempNodeInfo->hoadon.date.thang);
		full_date += " / ";
		full_date += to_string(tempNodeInfo->hoadon.date.nam);

		char date[30];
		strcpy_s(date, full_date.c_str());
		writeText(230, text_top, date, 1, 0, 3, bkcolor);
		if (strcmp(tempNodeInfo->hoadon.Loai, "N") == 0) {
			writeText(490, text_top, (char*)"Nhap", 1, 0, 3, bkcolor);
		}
		else writeText(490, text_top, (char*)"Xuat", 1, 0, 3, bkcolor);
		string hoTenNV = search_tenNV_by_HD(ds_nv, tempNodeInfo);
		std::cout << "Ho ten nhan vien: " << hoTenNV << std::endl;
		writeText(650, text_top, (char*)hoTenNV.c_str(), 1, 0, 3, bkcolor);
		// Lấy trị giá hóa đơn
		long double triGia = 0;
		DS_CT_HoaDon* nodeCT = tempNodeInfo->hoadon.first_cthd;
		while (nodeCT != NULL) {
			if (nodeCT->ct_hoadon.TrangThai == 1) {
				triGia += ((long double)nodeCT->ct_hoadon.Dongia * (long double)nodeCT->ct_hoadon.Soluong) + ((long double)nodeCT->ct_hoadon.Dongia * (long double)nodeCT->ct_hoadon.Soluong * (long double)nodeCT->ct_hoadon.VAT / 100);
			}
			nodeCT = nodeCT->next;
		}
		string triGia_str = formatNumber((long long)triGia);
		writeText(920, text_top, (char*)triGia_str.c_str(), 1, 0, 3, bkcolor);
	}

	// < >
	page_transition(view_page);
}

void ss_handleTable(int& x, int& y, DS_info* ds, view_page& vp_m_ss) {
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_m_ss.current == vp_m_ss.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_m_ss);
			
				delete_after_header();
				ss_table(ds, vp_m_ss, ROWS_PER_PG_SS);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_m_ss.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_m_ss);
				delete_after_header();
				ss_table(ds, vp_m_ss, ROWS_PER_PG_SS);
			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y)) {
				ss_page = false;
				goto ss_end;
			}
			if (ktVT(15, 70, 310, 110, x, y) || ktVT(320, 70, 640, 110, x, y)) {
				// reset view_page
				vp_m_ss.current = 1;
				vp_m_ss.page = 1;
				out_table = true;
				goto ss_end;
			}
		}
		delay(1);
	}
ss_end:;
}

void ss_handleTable_test(int& x, int& y, DS_HoaDon* ds, DS_NhanVien ds_nv, view_page& vp_m_ss) {
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// transition page
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (vp_m_ss.current == vp_m_ss.page) {
					continue;
				}
				next_page(650, 565, 685, 600, vp_m_ss);

				delete_after_header();
				ss_table_test(ds, ds_nv, vp_m_ss, ROWS_PER_PG_SS);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (vp_m_ss.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, vp_m_ss);
				delete_after_header();
				ss_table_test(ds, ds_nv, vp_m_ss, ROWS_PER_PG_SS);

			}
			if (ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y)) {
				ss_page = false;
				goto ss_end;
			}
			if (ktVT(15, 70, 310, 110, x, y) || ktVT(320, 70, 640, 110, x, y)) {
				// reset view_page
				vp_m_ss.current = 1;
				vp_m_ss.page = 1;
				out_table = true;
				goto ss_end;
			}
		}
		delay(1);
	}
ss_end:;
}

void table_doanhThu(
	DS_VatTu* root,
	DS_HoaDon* ds
) {
	delete_after_header();
	create_ss_header();
	// create doanhThu array
	int doanhThu_arr[3][12] = {};
	// create soldItem array
	SoldItem_arr soldItemArr;
	// reder page
	int i = 0, j = 0;
	// create table title
	string title = "THONG KE DOANH THU NAM ";
	title += year_dt;
	const char* m = title.c_str();
	writeText(580, 115, (char*)m, 4, 15, 8, bk_screen);
	// header num_rows
	int bar_top = 147-20, bar_bottom = 179-20;
	int text_top = 152-20;

	setcolor(0);
	setfillstyle(1, COLOR(51, 51, 51)); // original color -> 6
	setbkcolor(COLOR(51, 51, 51));
	bar(15, bar_top, 500, bar_bottom); // x = 250, y = 950;
	setcolor(15);
	settextstyle(f_small, 0, 2);
	outtextxy(100, text_top, (char*) table_doanhThu_header[0]);
	outtextxy(315, text_top, (char*) table_doanhThu_header[1]);
	setfillstyle(1, 15);
	setbkcolor(15);

	for (; i < 12; i++)
	{
		int bkcolor = 15;
		setfillstyle(1, 15);
		if (i % 2 == 1) {
			setfillstyle(1, COLOR(238, 238, 238));
			bkcolor = COLOR(238, 238, 238);
		}
		if (i == 0) {
			bar_top += 30;
			bar_bottom += 38;
			text_top += 35;
		}
		else {
			bar_top += 35;
			bar_bottom += 35;
			text_top += 35;
		}
		setcolor(0);
		bar(15, bar_top, 500, bar_bottom);
		// title header
		DS_HoaDon* nodeHD = ds;
		long long doanh_thu = 0;

		bool check;
		while (nodeHD != NULL) {
			if (nodeHD->hoadon.date.thang == i + 1 && !strcmp(nodeHD->hoadon.Loai, "X")) {
				doanhThu_arr[2][i]++;
				DS_CT_HoaDon* nodeCT = nodeHD->hoadon.first_cthd;
				while (nodeCT != NULL) {
					if (nodeCT->ct_hoadon.TrangThai == 1) {
						doanh_thu += (nodeCT->ct_hoadon.Dongia * nodeCT->ct_hoadon.Soluong) + (nodeCT->ct_hoadon.Dongia * nodeCT->ct_hoadon.Soluong * nodeCT->ct_hoadon.VAT / 100);
						// check item đã có trong soldItem_arr
						check = false;
						for (j = 0; j < soldItemArr.length; j++) {
							if (strcmp(soldItemArr.soldItem[j]->MAVT, nodeCT->ct_hoadon.MAVT) == 0) {
								soldItemArr.soldItem[j]->sold++;
								check = true;
								break;
							}
						}

						if (check == false) {
							SoldItem* newItem = new SoldItem();
							strcpy(newItem->MAVT, nodeCT->ct_hoadon.MAVT);
							newItem->sold = 1;
							soldItemArr.soldItem[soldItemArr.length] = newItem;
							soldItemArr.length++;
						}
					}
					nodeCT = nodeCT->next;
				}
			}
			else if (nodeHD->hoadon.date.thang == i + 1 && !strcmp(nodeHD->hoadon.Loai, "N")) doanhThu_arr[1][i]++;
			nodeHD = nodeHD->next;
		}
		// push to doanhThu arr
		doanhThu_arr[0][i] = doanh_thu;

		string thang = to_string(i + 1);
		const char* m = thang.c_str();
		int indent = 0;
		if (strlen(m) == 2) indent += 5;
		writeText(118 - indent, text_top, (char*)m, 1, 0, 3, bkcolor);
		string doanh_thu_str = formatNumber(doanh_thu);
		m = doanh_thu_str.c_str();
		indent = 0;
		indent += 3*(strlen(m) - 0);
		writeText(372 - indent, text_top, (char*)m, 1, 0, 3, bkcolor);
	}
	
	int bestSeller_qty = 0;
	char maVT_bestSeller[11];

	setbkcolor(bk_screen);
	setcolor(15);

	// ======= Lập chart doanh thu =======
	int chartWidth = 400;
	int chartHeight = 200;
	int barWidth = chartWidth / 12;

	int maxDoanhThu = 0;
	for (int i = 0; i < 12; i++) {
		if (doanhThu_arr[0][i] > maxDoanhThu) {
			maxDoanhThu = doanhThu_arr[0][i];
		}
	}

	float scale = (float)chartHeight / maxDoanhThu;

	int startX = 530;
	int startY = 580;

	// Trục x
	line(startX, startY, startX + chartWidth + 250, startY);

	// Trục y
	line(startX, startY, startX, startY - chartHeight - 40);

	// Mũi tên
	line(startX - 5, startY - chartHeight - 30, startX, startY - chartHeight - 43);
	line(startX + 5, startY - chartHeight - 30, startX, startY - chartHeight - 43);

	outtextxy(startX - 20, startY - chartHeight - 70, (char*)"Doanh thu (vnd)");

	// Label
	const char months[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	int labelY = startY + 8;
	for (int i = 0; i < 12; i++) {
		int labelX;
		if (i == 0) {
			labelX = startX + 25;
			outtextxy(labelX, labelY, (char*)months[i]);
			continue;
		}
		labelX = startX + (i * (barWidth + 20)) + 25;
		outtextxy(labelX, labelY, (char*)months[i]);
	}

	// Vẽ ô chart
	for (int i = 0; i < 12; i++) {
		int barHeight = (int)(doanhThu_arr[0][i] * scale);
		int endX = startX + barWidth;
		int endY = startY - barHeight;
			
		setfillstyle(LTSLASH_FILL, COLOR(145, 181, 186));
		bar3d(startX + 20, endY, endX + 20, startY, 10, 1);

		int indent = 0;
		string doanh_thu_str = formatNumber(doanhThu_arr[0][i]);
		m = doanh_thu_str.c_str();
		if (strlen(m) == 1) indent += 30;
		outtextxy(startX + 10 + indent, endY - 25, (char*)m);
		startX = endX + 10 + 10;
	}

	// ========= Tổng doanh thu =========
	int tongDT = 0;
	setfillstyle(1, 15);
	setcolor(COLOR(204, 204, 204));
	bar3d(530, 157, 800, 280, 0, 0);
	line(530, 157 + 75, 800, 157 + 75);
	setbkcolor(15);
	setcolor(COLOR(51, 51, 51)); // #333
	outtextxy(600, 165, (char*)"Tong doanh thu");
	for (int i = 0; i < 12; i++) tongDT += doanhThu_arr[0][i];
	string tongDT_str = formatNumber(tongDT);
	tongDT_str += " vnd";
	m = tongDT_str.c_str();
	settextstyle(8, 0, 3); // 4, 6, 8, 9
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(660, 200, (char*)m);	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	// Vặt tư bán chạy nhất
	for (j = 0; j < soldItemArr.length; j++)
		if (soldItemArr.soldItem[j]->sold > bestSeller_qty) {
			bestSeller_qty = soldItemArr.soldItem[j]->sold;
			strcpy(maVT_bestSeller, soldItemArr.soldItem[j]->MAVT);
		}

	DS_VatTu* nodeVT = getNodebyId_maVT(root, maVT_bestSeller);
	string tit = "Vat tu ban chay nhat: ";
	tit += nodeVT->vat_tu.tenVT;
	const char* mes = tit.c_str();

	settextstyle(3, 0, 1);
	outtextxy(550, 245, (char*)mes);

	// ========= Tổng đơn hàng =========
	setfillstyle(1, 15);
	setcolor(COLOR(204, 204, 204));
	bar3d(820, 157, 1090, 280, 0, 0);
	line(820, 157 + 75, 1090, 157 + 75);
	setbkcolor(15);
	setcolor(COLOR(51, 51, 51)); // #333
	settextstyle(3, 0, 1);
	outtextxy(890, 165, (char*)"Tong so don hang");
	int tongDH = 0;
	for (int i = 0; i < 12; i++) tongDH += doanhThu_arr[1][i] + doanhThu_arr[2][i];
	string tongDH_str = to_string(tongDH);
	m = tongDH_str.c_str();
	settextstyle(6, 0, 3);
	outtextxy(935, 200, (char*)m);
	setcolor(COLOR(204, 204, 204));
	line(955, 157 + 75, 955, 280);

	// Tổng hóa đơn nhập
	setcolor(COLOR(26, 218, 124));
	int tongHDN = 0;
	for (int i = 0; i < 12; i++) tongHDN += doanhThu_arr[1][i];
	string tongHDN_str = to_string(tongHDN);
	m = tongHDN_str.c_str();
	outtextxy(880, 157 + 75 + 15, (char*)m);

	// Tổng hóa đơn xuất
	setcolor(COLOR(172, 81, 190));
	int tongHDX = 0;
	for (int i = 0; i < 12; i++) tongHDX += doanhThu_arr[2][i];
	string tongHDX_str = to_string(tongHDX);
	m = tongHDX_str.c_str();
	outtextxy(1010, 157 + 75 + 15, (char*)m);

	// Chú thích
	settextstyle(f_small, 1, 1);
	setcolor(COLOR(26, 218, 124));
	circle(960, 310, 5);
	setfillstyle(1, COLOR(26, 218, 124));
	floodfill(960, 310, COLOR(26, 218, 124));
	setbkcolor(bk_screen);
	outtextxy(970, 300, (char*)"Don hang nhap");

	setcolor(COLOR(197, 125, 212));
	circle(960, 350, 5);
	setfillstyle(1, COLOR(197, 125, 212));
	floodfill(960, 350, COLOR(197, 125, 212));
	setbkcolor(bk_screen);
	outtextxy(970, 340, (char*)"Don hang xuat");
}

// kiểm tra năm nhuận
bool isLeapYear(int year) {
	if (year % 4 != 0) {
		return false;
	}
	else if (year % 100 != 0) {
		return true;
	}
	else if (year % 400 != 0) {
		return false;
	}
	else {
		return true;
	}
}

// Xu li input
bool ktra_loi_input(
	string input,
	int max_value,
	string input_field,
	int input_result,
	int e_kcl, int e_kct,
	int i_error_color, int i_bg, int i_highlight, int i_color
) {
	string error = "";
	
	if (input_field == "day") {
		if (input_result < 1 || input_result > 31) error = "Ngay khong hop le!";
	}
	else if (input_field == "month") {
		if (input_result < 1 || input_result > 12) error = "Thang khong hop le";
	}
	else if (input_field == "year" || input_field == "year_search_doanh_thu") {
		if (input_result < 2003) error = "Vui long nhap nam > 2003";
		else if (input_result > 2023) error = "Nam o tuong lai!";
	}

	// Thong bao loi
	char m[255];
	strcpy_s(m, error.c_str());
	cout << "Loi input! : " << error << endl;
	int error_padding = 0;
	if (input_field == "year_search_doanh_thu") error_padding += 20;
 	writeText(e_kcl + error_padding, e_kct, m, 2, i_error_color, 8, i_bg);
	// reset lai mau
	setbkcolor(i_highlight);
	setcolor(i_color);
	if (error != "") return 1;
	else return 0;
}

string ss_page_input(
	bool& is_all_valid,
	bool& is_error,
	int& x, int& y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	int e_kcl, int e_kct, int e_length = 50, // can chinh bao loi
	string value = "", int max_value = 255, int type = NULL, string input_field = "year",
	bool isOut = false,
	int i_bg = I_BG,
	int i_highlight = I_HIGHLIGHT,
	int i_color = I_COLOR,
	int i_error_color = I_ERROR_COLOR
) {
	if (!is_all_valid && !is_error) {
		x = y = NULL;
		return "";
	}
	while (kbhit()) {
		getch();
	}
	bool key_enter = false;
	string input = value;
	input += "_";
	char result[255] = { "" };
	if (input.length() != 0) {
		strcpy_s(result, input.c_str());
	}
	text_box(l, t, r, b, (char*)"", f_medium, 1, 0, 0, i_highlight, i_color); // vẽ khung input
	if (is_error) i_color = COLOR(255, 0, 0);
	writeText(l + kcl, t + kct, result, 1, i_color, f_medium, i_highlight); // chữ trong input
	while (!key_enter) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				out_click:
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				input.erase(input.end() - 1);
				strcpy_s(result, input.c_str());
				std::cout << "result:" << result << endl;
				// enter  xong vẫn để lại chữ
				setfillstyle(1, 15);
				bar3d(l, t, r, b, 0, 0);
				if (input.length() == 0) {
					is_all_valid = true;
					is_error = false;
				}
				else {
					int input_result = stoi(input);
					is_error = ktra_loi_input(input, max_value, input_field, input_result, e_kcl, e_kct, i_error_color, i_bg, i_highlight, i_color);
					int color = COLOR(0, 0, 0);
					if (is_error) {
						is_all_valid = false;
						color = COLOR(255, 0, 0);
					}
					else is_all_valid = true;
					writeText(l + kcl, t + kct, result, 1, color, f_medium, 15);
				}
				break;
			}
		}
		if (kbhit()) {
			char key = (char)getch(); // nhận key từ bàn phím
			bool check_key;
			cout << "key " << endl;
			if (type == 1) {
				check_key = only_number(key);
			}
			else if (type == 2) {
				check_key = decimal_number(key);
			}
			else if (type == 3) {
				check_key = only_letter(key);
			}
			else {
				check_key = kt_KTu(key);
			}
			if (check_key) {
				if (key == 8) {// <- backspace xoa
					if (input.length() == 1) {

					}
					else {
						setcolor(0); // reset color sau khi input không còn lỗi
						input.erase(input.end() - 2);
					}
				}
				else if (key != 13) {
					if (input.length() == (max_value + 1)) {
						continue;
					}
					// them chữ vào input
					input.erase(input.end() - 1);
					input += key;
					input += "_";
				}
				if (input.length() > 2) {
					// kiem tra 2 dau cách, .  thi xoa
					int n = input.length();
					if ((input[n - 2] == input[n - 3]) && (input[n - 2] == ' ' || input[n - 2] == '.')) {
						input.erase(input.end() - 2);
					}
				}
				strcpy_s(result, input.c_str());
				//---xoa canh bao
				setfillstyle(1, i_bg);
				bar(e_kcl-50, e_kct, e_kcl+320, e_kct+20);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13) {
					//enter để break					
					key_enter = true;
					x = NULL; y = NULL;
					input.erase(input.end() - 1);
					strcpy_s(result, input.c_str());
					int input_result;
					if (input != "") input_result = std::stoi(input);
					else input_result = NULL;
					cout << "result:" << input_result << endl;
					// enter xong vẫn để lại chữ
					setfillstyle(1, 15);
					bar3d(l, t, r, b, 0, 0);
					// tiến hành ktra lỗi -------------
					if (input != "") { // Tiến hành kiểm tra lỗi chỉ khi input != ""
						is_error = ktra_loi_input(input, max_value, input_field, (int)input_result, e_kcl, e_kct, i_error_color, i_bg, i_highlight, i_color);
						int color = COLOR(0, 0, 0);
						if (is_error) {
							is_all_valid = false;
							color = COLOR(255, 0, 0); // set color red khi input lỗi
						}
						else is_all_valid = true;
						writeText(l + kcl, t + kct, result, 1, color, f_medium, 15);
					}
				}
			}
			else {
				cout << "ki tu k hop le" << endl;
			}
		}
		if (isOut) goto out_click;
		delay(1);
	}
	cout << "out";
	return input;
}

void do_hoa_search_hd(view_page& vp_m_ss) {
	vp_m_ss = {};
	setfillstyle(1, COLOR_INFOR_SS);
	setcolor(0);
	bar3d(280, 180, 920, 530, 0, 0);

	setlinestyle(0, 0, 1);
	// Thanh tieu de
	const char* title = "Tim kiem hoa don";
	text_box(440, 140, 750, 181, (char*)title, 10, 3, 10, 40, COLOR(51, 51, 51), 15); // font 8
	// Thanh tim kiem
	text_box(310, 480, 890, 520, (char*)"Tim kiem", f_medium, 3, 10, 230, COLOR(252, 186, 3), 0);
	// Begin
	text_box(290, 190, 520, 230, (char*)"Tu ngay (begin)", f_medium, 3, 10, 10, COLOR(200, 200, 190), 0);
	setcolor(0);
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SS);
	outtextxy(320, 260, (char*)"Ngay");
	bar3d(400, 250, 500, 285, 0, 0);
	outtextxy(530, 260, (char*)"Thang");
	bar3d(610, 250, 710, 285, 0, 0);
	outtextxy(740, 260, (char*)"Nam");
	bar3d(800, 250, 900, 285, 0, 0);
	// End
	text_box(290, 300, 520, 340, (char*)"Den ngay (end)", f_medium, 3, 10, 10, COLOR(200, 200, 190), 0);
	setcolor(0);
	text_box(540, 300, 650, 340, (char*)"TODAY", f_medium, 3, 10, 20, COLOR(252, 186, 3), 0);
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SS);
	outtextxy(320, 370, (char*)"Ngay");
	bar3d(400, 360, 500, 395, 0, 0);
	outtextxy(530, 370, (char*)"Thang");
	bar3d(610, 360, 710, 395, 0, 0);
	outtextxy(740, 370, (char*)"Nam");
	bar3d(800, 360, 900, 395, 0, 0);
}

void get_current_date(string &day_e, string &month_e, string &year_e) {
	bool is_all_valid = true;
	bool is_error = false;
	int x_daye = 450, y_daye = 251;
	int x_monthe = 611, y_monthe = 361;
	int x_yeare = 801, y_yeare = 361;
	// GET CURRENT TIME ================
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string curr_date = to_string(ltm->tm_mday);
	string curr_month = to_string(1 + ltm->tm_mon);
	string curr_year = to_string(1900 + ltm->tm_year);
	// =================================
	// Xoa báo lỗi
	setfillstyle(1, COLOR_INFOR_SS);
	bar(510 - 50, 445, 510 + 290, 445 + 20); 
	day_e = ss_page_input(is_all_valid, is_error, x_daye, y_daye, 400, 360, 500, 395, 40, 10, 510, 445, 50, curr_date, 2, 1, "day_e", true, COLOR_INFOR_SS);
	month_e = ss_page_input(is_all_valid, is_error, x_monthe, y_monthe, 610, 360, 710, 395, 40, 10, 510, 445, 50, curr_month, 2, 1, "month_e", true, COLOR_INFOR_SS);
	year_e = ss_page_input(is_all_valid, is_error, x_yeare, y_yeare, 800, 360, 900, 395, 30, 10, 510, 445, 50, curr_year, 2, 1, "year_e", true, COLOR_INFOR_SS);
}

bool xu_li_nam_nhuan(int day, int month, int year, string &error_leap_year) {

	if (month == 2) {
		if (isLeapYear(year) && day > 29) {
			//error_leap_year = "Nam " + to_string(year) + " khong co ngay " + to_string(day);
			cout << "year: " << year << endl;
			error_leap_year = "Ngay " + to_string(day) + " khong ton tai";
			return true;
		}
		else if (!isLeapYear(year) && day > 28) {
			//error_leap_year = "Nam " + to_string(year) + " khong co ngay " + to_string(day);
			cout << "year: " << year << endl;
			error_leap_year = "Ngay " + to_string(day) + " khong ton tai";
			return true;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) {
			cout << "truong hop 3" << endl;
			error_leap_year = "Ngay " + to_string(day) + " khong ton tai";
			return true;
		}
	}
	return false;
}

int compareDate(Date date1, Date date2) {
	if (date1.nam < date2.nam) return -1;
	if (date1.nam > date2.nam) return 1;
	if (date1.thang < date2.thang) return -1;
	if (date1.thang > date2.thang) return 1;
	if (date1.ngay < date2.ngay) return -1;
	if (date1.ngay > date2.ngay) return 1;
	return 0;
}

void getDataTKDT(DS_HoaDon*& ds, DS_NhanVien ds_nv, int year) {
	int i;
	for (i = 0; i < ds_nv.length; i++) {
		DS_HoaDon* nodeHoaDon = ds_nv.nhan_vien[i]->ds_hoadon;
		while (nodeHoaDon != NULL) {
			if (nodeHoaDon->hoadon.date.nam > year) break;
			else if (nodeHoaDon->hoadon.date.nam == year) Insert_last_HD(ds, nodeHoaDon->hoadon);
			nodeHoaDon = nodeHoaDon->next;
		}
	}
}

void getDataTKHD(DS_info*& ds_info, DS_NhanVien ds_nv, Date date_begin, Date date_end) {
	int i;
	char ho_ten[40];
	for (i = 0; i < ds_nv.length; i++) {
		NhanVien* nv = ds_nv.nhan_vien[i];
		DS_HoaDon* nodeHoaDon = nv->ds_hoadon;
		while (nodeHoaDon != NULL) {
			if (compareDate(date_begin, nodeHoaDon->hoadon.date) <= 0 && compareDate(date_end, nodeHoaDon->hoadon.date) >= 0) {
				strcpy(ho_ten, nv->ho);
				strcat(ho_ten, " ");
				strcat(ho_ten, nv->ten);
				insertLast_DS_info(ds_info, ho_ten, nv->maNV, nodeHoaDon->hoadon);
			}
			else if (compareDate(nodeHoaDon->hoadon.date, date_end) > 0)
				break;
			nodeHoaDon = nodeHoaDon->next;
		}
	}
}

void getDataTKHD_test(DS_HoaDon*& ds_info, DS_NhanVien ds_nv, Date date_begin, Date date_end) {
	int i;
	char ho_ten[40];
	for (i = 0; i < ds_nv.length; i++) {
		NhanVien* nv = ds_nv.nhan_vien[i];
		DS_HoaDon* nodeHoaDon = nv->ds_hoadon;
		while (nodeHoaDon != NULL) {
			if (compareDate(date_begin, nodeHoaDon->hoadon.date) <= 0 && compareDate(date_end, nodeHoaDon->hoadon.date) >= 0) {
				Insert_last_HD(ds_info, nodeHoaDon->hoadon);
			}
			else if (compareDate(nodeHoaDon->hoadon.date, date_end) > 0)
				break;
			nodeHoaDon = nodeHoaDon->next; 
		}
	}
}

std::string search_tenNV_by_HD(DS_NhanVien ds_nv, DS_HoaDon* hd) {
	int i;
	for (i = 0; i < ds_nv.length; i++) {
		NhanVien* nv = ds_nv.nhan_vien[i];
		DS_HoaDon* nodeHD = nv->ds_hoadon;
		if (nodeHD == NULL || compareDate(nodeHD->hoadon.date, hd->hoadon.date) > 0) {
			continue;
		} 
		while (nodeHD != NULL) {
			if (!strcmp(nodeHD->hoadon.SoHD, hd->hoadon.SoHD)) {
				std::string fullname = nv->ho;
				fullname += " ";
				fullname += nv->ten;
				return fullname;
			}
			nodeHD = nodeHD->next;
		}
	}
}

void xu_li_button_tim_kiem(
	int& x, int& y,
	bool is_all_valid,
	string dayb, string monthb, string yearb, string daye, string monthe, string yeare,
	DS_NhanVien ds_nv, view_page& vp_m_ss
) {
	// check empty
	if (dayb == "" || daye == "" || monthe == "" || monthb == "" || yearb == "" || yeare == "") {
		if (dayb == "") text_box(400, 250, 500, 285, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		if (monthb == "") text_box(610, 250, 710, 285, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		if (yearb == "") text_box(800, 250, 900, 285, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		if (daye == "") text_box(400, 360, 500, 395, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		if (monthe == "") text_box(610, 360, 710, 395, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		if (yeare == "") text_box(800, 360, 900, 395, (char*)"Trong!", f_medium, 2, 8, 20, 15, COLOR(255, 0, 0));
		return;
	}

	// date string to int
	int day_b = stoi(dayb);
	int month_b = stoi(monthb);
	int year_b = stoi(yearb);
	int day_e = stoi(daye);
	int month_e = stoi(monthe);
	int year_e = stoi(yeare);
		
	// Kiểm tra định dạng ngày/tháng/năm
	cout << "day_b = " << day_b << ", month_b = " << month_b << ", year_b =  " << year_b << ", day_e = " << day_e << ", month_e = " << month_e << ", year_e = " << year_e << endl;
	if (!is_all_valid) return; // Ngay/thang/nam không đúng định dạng -> return
	bool error_end = false;	// kiểm tra begin > current
	// get current day
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curr_date = ltm->tm_mday;
	int curr_month = 1 + ltm->tm_mon;
	int curr_year = 1900 + ltm->tm_year;
	if (curr_year < year_e) {
		error_end = true;
		cout << "year_e = " << year_e << " curr_year = " << curr_year << endl;
	}
	else if (curr_year == year_e) {
		if (month_e > curr_month) {
			error_end = true;
			cout << "month_e = " << month_e << " month_b = " << month_b << endl;
		}
		else if (month_e == curr_month) {
			if (curr_date < day_e) {
				error_end = true;
				cout << "day_e = " << day_e << " curr_date = " << curr_date << endl;
			}
		}
	}

	bool error_begin_end = false;	// kiểm tra begin > end
	if (year_e < year_b) {
		error_begin_end = true;
		cout << "year_e = " << year_e << " < year_b = " << year_b << endl;
	}
	else if (year_e == year_b) {
		if (month_e < month_b) {
			error_begin_end = true;
			cout << "month_e = " << month_e << " < month_b = " << month_b << endl;
		}
		else if (month_e == month_b) {
			if (day_e < day_b) {
				error_begin_end = true;
				cout << "day_e = " << day_e << " < day_b = " << day_b << endl;
			}
		}
	}

	// Kiểm tra năm nhuân
	bool is_error_leap_year_begin;
	bool is_error_leap_year_end;
	string error_leap_year = "";
	is_error_leap_year_begin = xu_li_nam_nhuan(day_b, month_b, year_b, error_leap_year);
	is_error_leap_year_end = xu_li_nam_nhuan(day_e, month_e, year_e, error_leap_year);

	if (is_error_leap_year_begin) { // Lỗi leap year ở begin -> Báo lỗi đỏ
		char result[255] = { "" };
		strcpy_s(result, to_string(day_b).c_str());
		writeText(400 + 40, 250 + 10, result, 1, COLOR(255, 0, 0), f_medium, 15);
	}
	else { // Trả chữ về màu đen khi không còn lỗi
		char result[255] = { "" };
		strcpy_s(result, to_string(day_b).c_str());
		writeText(400 + 40, 250 + 10, result, 1, 0, f_medium, 15);
	}
	if (is_error_leap_year_end) {	// Lỗi leap year ở end -> Báo lỗi đỏ
		char result[255] = { "" };
		strcpy_s(result, to_string(day_e).c_str());
		writeText(400 + 40, 360 + 10, result, 1, COLOR(255, 0, 0), f_medium, 15);
	}
	else { // Trả chữ về màu đen khi không còn lỗi
		char result[255] = { "" };
		strcpy_s(result, to_string(day_e).c_str());
		writeText(400 + 40, 360 + 10, result, 1, 0, f_medium, 15);
	}

	// print message
	if (error_leap_year != "") { 
		char m[255];
		strcpy_s(m, error_leap_year.c_str());
		writeText(490, 445, m, 2, COLOR(255, 0, 0), 8, COLOR_INFOR_SS);
		return;
	}
	else if (error_end) {
		string error = "Ngay/thang/nam o tuong lai";
		char m[255];
		strcpy_s(m, error.c_str());
		writeText(470, 445, m, 2, COLOR(255, 0, 0), 8, COLOR_INFOR_SS);
	}
	else if (error_begin_end) {
		string error = "Ngay/thang/nam BEGIN > END";
		char m[255];
		strcpy_s(m, error.c_str());
		writeText(470, 445, m, 2, COLOR(255, 0, 0), 8, COLOR_INFOR_SS);
		return;
	}
	else if (error_leap_year == "" && !error_end && !error_begin_end) { // Ngày tháng năm đúng định dạng -> Tiến hành tạo table
		DS_info* ds_info = NULL;
		DS_HoaDon* ds = NULL;

		Date date_begin;
		date_begin.ngay = day_b;
		date_begin.thang = month_b;
		date_begin.nam = year_b;
		Date date_end;
		date_end.ngay = day_e;
		date_end.thang = month_e;
		date_end.nam = year_e;

		getDataTKHD(ds_info, ds_nv, date_begin, date_end);
		ds_info = mergeSort(ds_info);
		ss_table(ds_info, vp_m_ss, ROWS_PER_PG_SS);
		ss_handleTable(x, y, ds_info, vp_m_ss);
		//getDataTKHD_test(ds, ds_nv, date_begin, date_end);
		//ss_table_test(ds, ds_nv, vp_m_ss, ROWS_PER_PG_SS);
		//ss_handleTable_test(x, y, ds, ds_nv, vp_m_ss);
	}
}

void do_hoa_search_doanh_thu() {
	setfillstyle(1, COLOR_INFOR_SS);
	setcolor(0);
	bar3d(280, 180, 920, 490, 0, 0);

	// Thanh tieu de
	setlinestyle(0, 0, 1);
	const char* title = "Tra cuu doanh thu";
	text_box(440, 140, 750, 181, (char*)title, 10, 3, 10, 40, COLOR(51, 51, 51), 15); // font 8
	// Thanh tim kiemi
	text_box(450, 410, 750, 450, (char*)"Tra cuu", f_medium, 3, 10, 100, COLOR(255, 153, 51), 0);
	// User input 
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SS);
	outtextxy(350, 290, (char*)"Nhap nam can tra cuu:");
	bar3d(670, 285, 835, 320, 0, 0);
}

void xu_li_tra_cuu_doanh_thu(int &x, int &y, bool &is_all_valid, bool &error_year, string &year, bool page, DS_NhanVien ds_nv, DS_VatTu* root) {
	if (ktVT(670, 285, 835, 320, x, y) && page) {
		cout << "Tien hanh nhap input --nam";
		year = ss_page_input(is_all_valid, error_year, x, y, 670, 285, 835, 320, 66, 10, 470, 370, 50, year, 4, 1, "year_search_doanh_thu", false, COLOR_INFOR_SS);
	}
	if (!is_all_valid) return;
	if (ktVT(450, 410, 750, 450, x, y) && page) {
		cout << "Click button tim kiem" << endl;
		// check empty 
		if (year == "") text_box(670, 285, 835, 320, (char*)"Trong!", f_medium, 2, 8, 50, 15, COLOR(255, 0, 0));
		else {
			DS_HoaDon* dshd_dt = NULL;
			getDataTKDT(dshd_dt, ds_nv, stoi(year));
			table_doanhThu(root, dshd_dt);
		}
	}
}

void  xu_li_thong_ke_hd(
	int& x, int& y,
	bool& is_all_valid, bool& error_dayb, bool& error_monthb, bool& error_yearb, bool& error_daye, bool& error_monthe, bool& error_yeare,
	string& day_b, string& month_b, string& year_b,
	string& day_e, string& month_e, string& year_e,
	bool page,
	DS_NhanVien ds_nv, view_page& vp_m_ss
) {
	// Begin ===========================================
	// input day
 	start_input:
	if (ktVT(400, 250, 500, 285, x, y) && page) {
		cout << "Tien hanh nhap input -ngay\n" << endl;
		cout << "is_all_valid: " << is_all_valid << endl;
		cout << "is_error: " << error_dayb << endl;
		day_b = ss_page_input(is_all_valid, error_dayb, x, y, 400, 250, 500, 285, 40, 10, 510, 445, 50, day_b, 2, 1, "day", false, COLOR_INFOR_SS);
		goto start_input;
	}
	// input month
	if (ktVT(610, 250, 710, 285, x, y) && page) {
		cout << "Tien hanh nhap input -thang\n";
		cout << "is_all_valid: " << is_all_valid << endl;
		cout << "is_error: " << error_monthb << endl;
		month_b = ss_page_input(is_all_valid, error_monthb, x, y, 610, 250, 710, 285, 40, 10, 510, 445, 50, month_b, 2, 1, "month", false, COLOR_INFOR_SS);
		goto start_input;
	}
	// input year 
	if (ktVT(800, 250, 900, 285, x, y) && page) {
		cout << "Tien hanh nhap input -nam\n";
		std::cout << "is_all_valid: " << is_all_valid << endl;
		cout << "is_error: " << error_yearb << endl;
		year_b = ss_page_input(is_all_valid, error_yearb, x, y, 800, 250, 900, 285, 30, 10, 510, 445, 50, year_b, 4, 1, "year", false, COLOR_INFOR_SS);
		goto start_input;
	}

	// Click on TODAY button ====================
	if (ktVT(540, 300, 650, 340, x, y) && page) {
		text_box(540, 300, 650, 340, (char*)"TODAY", f_medium, 3, 10, 20, COLOR(255, 153, 51), 0);
		get_current_date(day_e, month_e, year_e);
	}

	// End ======================================
	if (ktVT(400, 360, 500, 395, x, y) && page) {
		cout << "Tien hanh nhap input -ngay\n";
		day_e = ss_page_input(is_all_valid, error_daye, x, y, 400, 360, 500, 395, 40, 10, 510, 445, 50, day_e, 2, 1, "day", false, COLOR_INFOR_SS);
		goto start_input;
	}
	if (ktVT(610, 360, 710, 395, x, y) && page) {
		cout << "Tien hanh nhap input -thang\n";
		month_e = ss_page_input(is_all_valid, error_monthe, x, y, 610, 360, 710, 395, 40, 10, 510, 445, 50, month_e, 2, 1, "month", false, COLOR_INFOR_SS);
		goto start_input;
	}

	if (ktVT(800, 360, 900, 395, x, y) && page) {
		cout << "Tien hanh nhap input -nam\n";
		year_e = ss_page_input(is_all_valid, error_yeare, x, y, 800, 360, 900, 395, 30, 10, 510, 445, 50, year_e, 4, 1, "year", false, COLOR_INFOR_SS);
		goto start_input;
	}

	// Click on Tìm kiếm button =================
	if (ktVT(310, 480, 890, 520, x, y) && page) {
		cout << "Click on button tim kiem" << endl;
		xu_li_button_tim_kiem(x, y, is_all_valid, day_b, month_b, year_b, day_e, month_e, year_e, ds_nv, vp_m_ss);
	}
}

void test_data(DS_NhanVien ds_nv) {
	for (int i = 0; i < ds_nv.length; i++) {
		std::cout << "=================== NHAN VIEN " << i + 1 << " ===================" << std::endl;
		std::cout << "MaNV: " << ds_nv.nhan_vien[i]->maNV << " - Ten: " << ds_nv.nhan_vien[i]->ho << " " << ds_nv.nhan_vien[i]->ten << std::endl;
		std::cout << "Gioi tinh: " << ds_nv.nhan_vien[i]->phai << std::endl;
		if (ds_nv.nhan_vien[i]->ds_hoadon == NULL) std::cout << "DSHD: null" << std::endl;
		else {
			int stt_hd = 1;
			DS_HoaDon* nodeIt = ds_nv.nhan_vien[i]->ds_hoadon;
			while (nodeIt != NULL) {
				std::cout << "------- Hoa don " << stt_hd++ << " -------"<< std::endl;
				std::cout << "SoHD: " << nodeIt->hoadon.SoHD << std::endl;
				std::cout << "Ngay lap: " << nodeIt->hoadon.date.ngay << "/" << nodeIt->hoadon.date.thang << "/" << nodeIt->hoadon.date.nam << std::endl;
				if (strcmp(nodeIt->hoadon.Loai, "N") == 0) std::cout << "Loai: nhap" << std::endl;
				else std::cout << "Loai: xuat" << std::endl;
				std::cout << "Chi tiet HD: " << std::endl;
				DS_CT_HoaDon* nodeItCTHD = nodeIt->hoadon.first_cthd;
				while (nodeItCTHD != NULL) {
					std::cout << " - Vat tu: " << nodeItCTHD->ct_hoadon.MAVT << ", so luong: " << nodeItCTHD->ct_hoadon.Soluong << ", don gia: " << nodeItCTHD->ct_hoadon.Dongia << ", VAT: " << nodeItCTHD->ct_hoadon.VAT << ", loai: " << nodeItCTHD->ct_hoadon.TrangThai << std::endl;
					nodeItCTHD = nodeItCTHD->next;
				}
				nodeIt = nodeIt->next;
			}
		}
	}
}

