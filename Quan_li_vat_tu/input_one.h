#pragma once
#include"Header.h"
#include"Common.h"
#include "input_staff_good.h"
string input_one(int& x, int& y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	string value = "", int max_value = 255,
	int i_bg = I_BG,
	int setX = NULL, int setY = NULL,
	int i_highlight = I_HIGHLIGHT,
	int i_color = I_COLOR,
	int i_error_color = I_ERROR_COLOR) {
	while (kbhit()) {
		getch();
	}
	
	string input = value;
	input += "|";
	while (1) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				input.erase(input.length() - 1);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, 15);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				if (input.length() >0&&( input[input.length()-1]==' ')) {
					input.erase(input.length() - 1, 1);
				}
				writeText(l + kcl, t + kct, (char*)input.c_str(), 1, i_color, f_medium, 15);
				return input;
			}
		}
		input.erase(input.length() - 1);
		settextstyle(f_medium, 0, 1);
		setfillstyle(1, i_highlight);
		setbkcolor(i_highlight);
		setcolor(0);
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
			check_key= text_number(key);
			if (check_key) {
				check_key = true;
			}
			else {
				check_key = false;

			}
			if (check_key) {
				input.erase(input.end() - 1);
				if (key == 8) {// <- backspace xoa
					if (input.length() >0) {
						if (input.length() > 1 && input[input.length() - 2]==' ') {
							input.erase(input.length() - 1, 1);
						}
						input.erase(input.length() - 1,1);
					}
				}
				else if (key ==13 || key == 9) {
					if (input.length() > 0 && (input[input.length() - 1] == ' ')) {
						input.erase(input.length() - 1, 1);
					}
					setfillstyle(1, 15);
					bar3d(l, t, r, b, 0, 0);
					writeText(l + kcl, t + kct, (char*)input.c_str(), 1, i_color, f_medium, 15);
					x = 0; y = 0;
					return input;
				}
				else {
					input += key;
				}				
				//-- ghi chữ lại
				if (input[0]==' ' ) {
					input.erase(0, 1);
				}
				if ((input.length() > 1 && input[input.length() - 1] == ' ' && input[input.length() - 2] == ' ')) {
					input.erase(input.length() - 1, 1);
				}
				writeText(l + kcl, t + kct, (char*)input.c_str(), 1, i_color, f_medium, i_highlight);
				return input;
			}
			else {
				cout << "ki tu k hop le" << endl;
			}
		}
		
	
		
	}
}