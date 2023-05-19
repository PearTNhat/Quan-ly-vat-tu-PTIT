#pragma once
#include "Header.h"
#include "Constant.h"
#include "Common.h"
bool only_number(char x) {
	if (x == 9)return true;
	if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == 8 || x == 13) {
		return true;
	}
	return false;
}
bool only_letter(char x) {
	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x == 8 || x == 13 || x == 9|| x == ' ') {
		return true;
	}
	return false;
}
bool decimal_number(char x) {
	if (x == 9)return true;

	if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == 8 || x == 13 || x == '.') {
		return true;
	}
	return false;
}
bool kt_KTu(char x) {
	if (x == 9)return true;

	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == '/' || x == '\\' || x == 8 || x == 13 || x == ' ' || x == '.') {
		return true;
	}
	return false;
} // text and number
bool text_no_space(char x) {
	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x == 8 || x == 13 || x == 9) {
		return true;
	}
	return false;
};
bool text_number_nospace(char x) {
	if (x == 9)return true;

	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x >= '0' && x <= '9') {
		return true;
	}
	else if ( x == 8 || x == 13 ) {
		return true;
	}
	return false;
}
bool text_number(char x) {
	if (x == 9)return true;

	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == 8 || x == 13||x==' ') {
		return true;
	}
	return false;
}
string input(
	int& x, int& y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	int e_kcl, int e_kct, int e_length = 50, // can chinh bao loi
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
	text_box(l, t, r, b, (char*)"", f_medium, 1, 0, 0, i_highlight, i_color); // vẽ khung input
	writeText(l + kcl, t + kct, result, 1, i_color, f_medium, i_highlight); // chữ trong input
	while (!key_enter) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				//---xoa canh bao
				setfillstyle(1, i_bg);
				bar(l + e_kcl, t + e_kct, r + e_length, b + 25);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				//
				if (input.length() == 1) {
					warning_msg("Khong duoc de trong", l + e_kcl, t + e_kct, i_bg, i_error_color);
					// reset lai mau
					setbkcolor(i_highlight);
					setcolor(i_color);
				}
				input.erase(input.end() - 1);
				strcpy_s(result, trim(input).c_str());
				cout << "result:" << result << endl;
				// enter  xong vẫn để lại chữ
				setfillstyle(1, 15);
				bar3d(l, t, r, b, 0, 0);
				writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 15);
				break;

			}
		}

		input.erase(input.length() - 1);
		settextstyle(f_medium, 0, 1);
		setfillstyle(1, i_highlight);
		bar3d(l, t, r, b, 0, 0);
		outtextxy(l + kcl, t + kct, (char*)input.c_str());
		delay(1);
		input += "|";
		setfillstyle(1, i_highlight);
		bar3d(l, t, r, b, 0, 0);
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
				check_key= text_number_nospace(key);
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
				else if (key != 13 && key!=9) {
					if (input.length() == (max_value + 1)) {
						string s = "Ban da nhap dung ";
						s += to_string(max_value);
						s += " ki tu roi.";
						warning_msg(s, l + e_kcl, t + e_kct, i_bg, i_error_color);
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
					input += key;
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
					if (function == "firstCase") {
						input[0]=toupper(input[0]);
					}

					input += "|";
				}
				
				strcpy_s(result, input.c_str());
				//---xoa canh bao
				setfillstyle(1, i_bg);
				bar(l + e_kcl, t + e_kct, r + e_length, b + 25);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13 || key == 9) {
					//enter để break
					if (input.length() == 1) {
						warning_msg("Khong duoc de trong", l + e_kcl, t + e_kct, i_bg, i_error_color);
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
	return input;
}

