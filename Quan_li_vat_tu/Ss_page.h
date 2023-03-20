#pragma once

#include "Common.h";

#define MAXTITLE 25
#define I_BG_SS COLOR(186, 245, 223) // màu nền  khi enter nhập xong
#define I_HIGHLIGHT_SS COLOR(255, 255, 255) // highlight khi click vào
#define I_COLOR_SS 0 // màu chữ
#define I_ERROR_COLOR_SS COLOR(255,0,0) // màu của chữ khi báo lỗi

char title[5][MAXTITLE] = { "Top", "Ma VT", "Ten Vat Tu", "Don Vi Tinh", "Doanh Thu" };

// Xu li input
string ss_page_input(
	int& x, int& y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	string e_str,
	int e_kcl, int e_kct, int e_length = 50, // can chinh bao loi
	string value = "", int max_value = 255, int type = NULL,
	int i_bg = I_BG,
	int i_highlight = I_HIGHLIGHT,
	int i_color = I_COLOR,
	int i_error_color = I_ERROR_COLOR
) {
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
	writeText(l + kcl, t + kct, result, 1, i_color, f_medium, i_highlight); // chữ trong input
	while (!key_enter) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				//---xoa canh bao
				//setfillstyle(1, i_bg);
				//bar(e_kcl, e_kct, e_kcl+220, e_kct + 20);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				input.erase(input.end() - 1);
				strcpy_s(result, input.c_str());
				cout << "result:" << result << endl;
				// enter  xong vẫn để lại chữ
				setfillstyle(1, 15);
				bar3d(l, t, r, b, 0, 0);
				writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 15);
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
						input.erase(input.end() - 2);
					}
				}
				else if (key != 13) {
					if (input.length() == (max_value + 1)) {
						string s = e_str;
						char m[255];
						strcpy_s(m, s.c_str());
						cout << "Vi tri chu bao loi: " << e_kcl << endl;
						writeText(e_kcl, e_kct, m, 1, i_error_color, f_medium, i_bg);
						// reset lai mau
						setbkcolor(i_highlight);
						setcolor(i_color);
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
				bar(e_kcl, e_kct, e_kcl+275, e_kct+20);
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
					cout << "result:" << result << endl;
					// enter xong vẫn để lại chữ
					setfillstyle(1, 15);
					bar3d(l, t, r, b, 0, 0);
					writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 15);
				}
			}
			else {
				cout << "ki tu k hop le" << endl;
			}
		}
		delay(1);
	}
	cout << "out";
	return input;
}

void create_ss_header() {
	setfillstyle(1, HEADER_BACKGROUND);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);
	text_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(320, 70, 640, 110, (char*)"Thong ke doanh thu", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
}

void do_hoa_search_hd() {
	setfillstyle(1, COLOR_INFOR_SG);
	setcolor(0);
	bar3d(280, 180, 920, 530, 0, 0);

	// Thanh tieu de
	const char* title = "Tim Kiem Hoa Don";
	text_box(440, 140, 750, 181, (char*)title, f_medium, 3, 10, 40, 11, 0);
	// Thanh tim kiem
	text_box(310, 480, 890, 520, (char*)"Tim kiem", f_medium, 3, 10, 230, COLOR(255, 153, 51), 0);
	// Begin
	text_box(290, 190, 520, 230, (char*)"Tu ngay (begin)", f_medium, 3, 10, 10, 11, 0);
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SG);
	outtextxy(320, 260, (char*)"Ngay");
	bar3d(400, 250, 500, 285, 0, 0);
	outtextxy(530, 260, (char*)"Thang");
	bar3d(610, 250, 710, 285, 0, 0);
	outtextxy(740, 260, (char*)"Nam");
	bar3d(800, 250, 900, 285, 0, 0);
	// End
	text_box(290, 300, 520, 340, (char*)"Den ngay (end)", f_medium, 3, 10, 10, 11, 0);
	text_box(540, 300, 650, 340, (char*)"TODAY", f_medium, 3, 10, 20, COLOR(255, 153, 51), 0);
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SG);
	outtextxy(320, 370, (char*)"Ngay");
	bar3d(400, 360, 500, 395, 0, 0);
	outtextxy(530, 370, (char*)"Thang");
	bar3d(610, 360, 710, 395, 0, 0);
	outtextxy(740, 370, (char*)"Nam");
	bar3d(800, 360, 900, 395, 0, 0);
}

void do_hoa_search_doanh_thu() {
	setfillstyle(1, COLOR_INFOR_SG);
	setcolor(0);
	bar3d(280, 180, 920, 490, 0, 0);

	// Thanh tieu de
	const char* title = "Tra cuu doanh thu";
	text_box(440, 140, 750, 181, (char*)title, f_medium, 3, 10, 40, 11, 0);
	// Thanh tim kiemi
	text_box(450, 410, 750, 450, (char*)"Tra cuu", f_medium, 3, 10, 100, COLOR(255, 153, 51), 0);
	// User input 
	setfillstyle(1, 15);
	setbkcolor(COLOR_INFOR_SG);
	outtextxy(350, 290, (char*)"Nhap nam can tra cuu:");
	bar3d(670, 285, 835, 320, 0, 0);
}


void xu_li_tra_cuu_doanh_thu(int &x, int &y, string &year, bool page) {
	if (ktVT(670, 285, 835, 320, x, y) && page) {
		cout << "Tien hanh nhap input --nam";
		year = ss_page_input(x, y, 670, 285, 835, 320, 66, 10, "Nam tim kiem khong hop le", 470, 370, 50, year, 4, 1, COLOR_INFOR_SG);
	}
}

void  xu_li_thong_ke_hd(int &x, int &y, string &day_b, string &month_b, string &year_b, string &day_e, string &month_e, string &year_e, bool page) {
	// Begin----------------------------------
	// input day
	if (ktVT(400, 250, 500, 285, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		day_b = ss_page_input(x, y, 400, 250, 500, 285, 40, 10, "Ngay khong hop le", 510, 445, 50, day_b, 2, 1, COLOR_INFOR_SG);
	}
	// input month
	if (ktVT(610, 250, 710, 285, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		month_b = ss_page_input(x, y, 610, 250, 710, 285, 40, 10, "Thang khong hop le", 510, 445, 50, month_b, 2, 1, COLOR_INFOR_SG);
	}
	// input year 
	if (ktVT(800, 250, 900, 285, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		year_b = ss_page_input(x, y, 800, 250, 900, 285, 30, 10, "Nam khong hop le", 510, 445, 50, year_b, 4, 1, COLOR_INFOR_SG);
	}

	// End--------------------------------------
	if (ktVT(400, 360, 500, 395, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		day_e = ss_page_input(x, y, 400, 360, 500, 395, 40, 10, "Ngay khong hop le", 510, 445, 50, day_e, 2, 1, COLOR_INFOR_SG);
	}
	if (ktVT(610, 360, 710, 395, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		month_e = ss_page_input(x, y, 610, 360, 710, 395, 40, 10, "Thang khong hop le", 510, 445, 50, month_e, 2, 1, COLOR_INFOR_SG);
	}

	if (ktVT(800, 360, 900, 395, x, y) && page) {
		cout << "Tien hanh nhap input -ngay";
		year_e = ss_page_input(x, y, 800, 360, 900, 395, 30, 10, "Nam khong hop le", 510, 445, 50, year_e, 4, 1, COLOR_INFOR_SG);
	}
}

