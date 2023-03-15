#pragma once

#include "Common.h";
#define MAXTITLE 25
#define I_BG_SS COLOR(186, 245, 223) // màu nền  khi enter nhập xong
#define I_HIGHLIGHT_SS COLOR(255, 255, 255) // highlight khi click vào
#define I_COLOR_SS 0 // màu chữ
#define I_ERROR_COLOR_SS COLOR(255,0,0) // màu của chữ khi báo lỗi

char title[5][MAXTITLE] = { "Top", "Ma VT", "Ten Vat Tu", "Don Vi Tinh", "Doanh Thu" };


void create_ss_header() {
	setfillstyle(1, HEADER_BACKGROUND);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);
	text_box(15, 70, 310, 110, (char*)"Thong Ke Hoa Don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(320, 70, 565, 110, (char*)"Top 10 Vat Tu", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
}

void create_ss_search(bool isBill) {
	setfillstyle(1, COLOR_INFOR_SG);
	setcolor(0);
	bar3d(280, 180, 920, 530, 0, 0);

	// Thanh tieu de
	const char* title;
	if (isBill) title = "Tim Kiem Hoa Don";
	else title = "Tim Top 10 Vat Tu";
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

void table_top_10_vattu() {
	setfillstyle(1, 15);
	setcolor(0); 
	bar3d(110, 130, 1090, 590, 0, 0);

	// thanh tieu de
	setfillstyle(1, COLOR(4, 169, 109));
	setcolor(15);
	text_box_no_border(200, 140, 1000, 185, (char*)"DANH SACH TOP 10 VAT TU DOANH THU CAO NHAT", 8, 3, 10, 100, COLOR(4, 170, 109), 15);
	
	// Bang top 10 vat tu

}

string ss_page_input(
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	int e_kcl, int e_kct, int e_length = 50, // can chinh bao loi
	string value = "", int max_value = 255, int type = NULL
) {
	bool key_enter = false;
	string input = value;
	input += "_";
	char result[255] = {};
	strcpy_s(result, input.c_str());
	text_box(l, t, r, b, (char*)"", f_medium, 2, 0, 0, I_HIGHLIGHT_SS, I_COLOR_SS); // vẽ khung input
	writeText(l + kcl, t + kct, result, 3, I_COLOR, f_medium, I_HIGHLIGHT_SS); // chữ trong input
	while (!key_enter) {
		while (kbhit()) {
			char key = (char)getch(); // nhận key từ bàn phím
			bool check_key;
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
						string s = "Toi da la ";
						s += to_string(max_value);
						s += " ki tu.";
						char m[255];
						strcpy_s(m, s.c_str());
						writeText(l + e_kcl, t + e_kct, m, 3, I_ERROR_COLOR_SS, f_medium, I_BG_SS);
						// reset lai mau
						setbkcolor(I_HIGHLIGHT_SS);
						setcolor(I_COLOR_SS);
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
				setfillstyle(1, I_BG_SS);
				bar(l + e_kcl, t + e_kct, r + (e_length*2), b + 10);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, I_HIGHLIGHT_SS);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13) {
					//enter để break
					key_enter = true;
					input.erase(input.end() - 1);
					strcpy_s(result, input.c_str());
					cout << "result:" << result << endl;

					// enter xong vẫn để lại chữ
					setfillstyle(1, 15);
					bar3d(l, t, r, b, 0, 0);
					writeText(l + kcl, t + kct, result, 3, I_COLOR_SS, f_medium, 15);
				}
			}
			else {
				cout << "ki tu k hop le" << endl;
			}
		}
		delay(1);
	}
	return input;
}

//bool announce_board(int kcl = 0, int kct = 0, int bg = COLOR(232, 246, 250)) { // 200 //400 
//
//	setfillstyle(1, bg);
//	bar3d(420, 210, 780, 410, 0, 0);
//	writeText(450 + kcl, 280 + kct, (char*)"Ban co muon xoa khong?", 1, 0, f_medium, bg);
//	text_box(500, 345, 570, 370, (char*)"Co", f_medium, 1, 5, 20, bg, 0);
//	text_box(610, 345, 680, 370, (char*)"Khong", f_medium, 1, 5, 6, bg, 0);
//	text_box(750, 210, 780, 240, (char*)"X", f_medium, 1, 7, 9, COLOR(255, 21, 0), 0);
//
//	return 0;
//}
