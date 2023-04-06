#pragma once
#include "Header.h"
#include "Constant.h"
#include "Common.h"
#include "input_staff_good.h"

void warning_msg_bill(string text, int e_l, int e_t, int bg, int color, int font)
{
	text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 1, 0, 0, RED, 0);
	char m[255];
	strcpy_s(m, text.c_str());
	writeText(e_l, e_t, m, 1, color, f_medium, bg);
}
string input_bill(
	int& x, int& y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	int e_l, int e_t, int e_r, int e_b, // can chinh bao loi
	string value = "", int max_value = 255, string type = "",
	string function = "", // upcase abc -> ABC
	// camelCase nguyen van a -> Nguyen Van A
	int i_bg = I_BG,
	int setX = NULL, int setY = NULL,
	int i_highlight = I_HIGHLIGHT,
	int i_color = I_COLOR,
	int i_error_color = I_ERROR_COLOR
) {
	while (kbhit()) {
		getch();
	}
	bool key_enter = false;
	string input = value;
	input += "|";
	char result[255] = { "" };
	if (input.length() != 0) {
		strcpy_s(result, input.c_str());
	}
	text_box_no_border(l, t, r, b, (char*)"", f_medium, 1, 0, 0, i_highlight, i_color); // vẽ khung input
	writeText(l + kcl, t + kct, result, 1, i_color, f_medium, i_highlight); // chữ trong input
	while (!key_enter) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				//---xoa canh bao
				text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 1, 0, 0, 14, 0);
			
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar(l, t, r, b);
				//-- ghi chữ lại
				setbkcolor(i_highlight);
				outtextxy(l + kcl, t + kct, result);
				//
				if (input.length() == 1) {
					warning_msg_bill("Khong duoc trong", e_l + 2, e_t + 30, 4, 0, 0);
					// reset lai mau
					setbkcolor(i_highlight);
					setcolor(i_color);
				}
				input.erase(input.end() - 1);
				strcpy_s(result, trim(input).c_str());
				cout << "result:" << result << endl;
				// enter  xong vẫn để lại chữ
				setfillstyle(1, 15);
				bar(l, t, r, b);
				writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 15);
				break;

			}
		}

		input.erase(input.length() - 1);
		settextstyle(f_medium, 0, 1);
		setfillstyle(1, i_highlight);
		bar(l, t, r, b);
		setbkcolor(i_highlight);
		outtextxy(l + kcl, t + kct, (char*)input.c_str());
		delay(1);
		input += "|";
		setfillstyle(1, i_highlight);
		bar(l, t, r, b);
		setbkcolor(i_highlight);
		outtextxy(l + kcl, t + kct, (char*)input.c_str());
		delay(1);

		if (kbhit()) {
			char key = getch(); // nhận key từ bàn phím
			if ((int)key == 0) // chặn F1, F2 , ect....
			{
				key = getch();
				continue;
			}
			bool check_key;
			//cout << "key "<< (int)key <<endl;
			if (type == "number") {
				check_key = only_number(key);
			}
			else if (type == "decimal") {
				check_key = decimal_number(key);
			}
			else if (type == "text") {
				check_key = only_letter(key);
			}
			else if (type == "textNoSpace") {
				check_key = text_no_space(key);
			}
			else if (type == "textNumberNoSpace") {
				check_key = text_number_nospace(key);
			}
			else {
				// all number and text
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
						string s = "Toi da ";
						s += to_string(max_value);
						s += " ki tu.";
						warning_msg_bill(s, e_l + 2, e_t + 30, RED, BLACK, 0);
						// reset lai mau
						setbkcolor(i_highlight);
						setcolor(i_color);
						continue;
					}
					// delete _ ;
					input.erase(input.end() - 1);

					// kiem tra function
					if (function == "upcase") {
						key = toupper(key);
					}
					// noi chu vao
					if (key != 9) { // khac tab
						input += key;
					};
					if (input.length() == 1 && input[0] == ' ') { // dau cach o dau thi xoa
						input.erase(0, 1);
					}
					if (input.length() > 2) { // kiem tra 2 dau cách, .  thi xoa
						int n = input.length();
						if ((input[n - 1] == input[n - 2]) && (input[n - 2] == ' ' || input[n - 2] == '.')) {
							input.erase(input.end() - 1);
						}
					}
					// kiem tra function
					if (input.length() > 0 && function == "camelCase") { // camelCase
						int n = input.length();
						if (n > 1 && input[n - 2] == ' ') {
							input[n - 1] = toupper(input[n - 1]);
						}
						else {
							input[n - 1] = tolower(input[n - 1]);
						}
						input[0] = toupper(input[0]);
					}
					input += "|";
				}


				strcpy_s(result, input.c_str());
				//---xoa canh bao
				setfillstyle(1, i_bg);
				text_box_no_border(e_l, e_t, e_r, e_b, (char*)"", f_medium, 1, 0, 0, YELLOW, 0);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar(l, t, r, b);
				//-- ghi chữ lại
				setbkcolor(i_highlight);
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13 || key == 9) {
					//enter để break	'
					if (input.length() == 1) {
						warning_msg_bill("Khong duoc trong", e_l+2, e_t+30, 4,0,0);
						// reset lai mau
						setbkcolor(i_highlight);
						setcolor(i_color);
					}
					key_enter = true;
					x = setX; y = setY;
					input.erase(input.end() - 1);
					strcpy_s(result, trim(input).c_str());
					cout << "result:" << result << endl;

					// enter  xong vẫn để lại chữ
					setfillstyle(1, 9);
					bar(l, t, r, b);
					writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 9);
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

