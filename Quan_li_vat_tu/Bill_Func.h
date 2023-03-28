#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "input_staff_good.h"


string b_input(
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
	settextstyle(f_medium, 0, 1);
	setfillstyle(1, 0);
	setcolor(14);
	setbkcolor(0);
	bar3d(l, t, r, b, 0, 0);
	outtextxy(l + kcl, t + kct, result);
	while (!key_enter) {
		while (kbhit()) {
			char key = (char)getch();
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
						/*string s = "Toi da la ";
						s += to_string(max_value);
						s += " ki tu.";
						char m[30];
						strcpy_s(m, s.c_str());
						setcolor(I_ERROR_COLOR);
						setbkcolor(I_BG);
						settextstyle(f_medium, 0, 1);
						outtextxy(l + e_kcl, t + e_kct, m);
						settextstyle(f_medium, 0, 1);
						setbkcolor(I_HIGHLIGHT);
						setcolor(0);
						continue;*/
					}
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
				/*setfillstyle(1, I_BG);
				bar(l + e_kcl, t+e_kct ,r+ e_length, b + 10);*/// xoa canh bao
				setfillstyle(1, 0);

				bar3d(l, t, r, b, 0, 0);
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13) {
					//enter để break
					key_enter = true;
					input.erase(input.end() - 1);
					strcpy_s(result, input.c_str());
					cout << "result:" << result << endl;
					setfillstyle(1, 15);
					setbkcolor(15);
					bar(l, t, r, b);
					outtextxy(l + kcl, t + kct, result);
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
	bar3d(10, 65, 1180, 115, 0, 0);
	text_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	text_box(685, 70, 980, 110, (char*)"In hoa don", f_medium, 3, 10, 40, XANH_DUONG_NHAT);
	
	text_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 11, 0);
	text_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, 11, 0);
	text_box(685, 70, 980, 110, (char*)"In hoa don", f_medium, 3, 10, 40, 11, 0);

	b_taokhungxanhla(10, 65, 1180, 115);
	b_taokhungxanhla(10, 120, 1180, 600);
}

void b_delete_after_create() {
	setfillstyle(1, bk_screen);
	bar(11, 121, 1179, 599);
}

void b_create_NX()
{
	b_taokhungxanhla(10, 120, 110, 220);
	text_box(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 9);
	text_box(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 9);
}

void b_create_info()
{
	text_box(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 9, 0);
	text_box(110, 145, 270, 170, (char*)"ngay:", f_medium, 2, 1, 5, 9, 0);
	text_box(270, 145, 430, 170, (char*)"thang:", f_medium, 2, 1, 5, 9, 0);
	text_box(430, 145, 590, 170, (char*)"nam:", f_medium, 2, 1, 5, 9, 0);
	text_box(590, 120, 980, 145, (char*)"Ma nhan vien:", f_medium, 2, 1, 5, 9, 0);
	text_box(110, 170, 430, 195, (char*)"Ma vat tu:", f_medium, 2, 1, 5, 9, 0);
	text_box(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 9, 0);
	text_box(350, 195, 590, 220, (char*)"Don gia:", f_medium, 2, 1, 5, 9, 0);
	text_box(430, 170, 590, 195, (char*)"%VAT: ", f_medium, 2, 1, 5, 9, 0);
	text_box(620, 165, 770, 190, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
	text_box(800, 165, 950, 190, (char*)"Luu hoa don", f_medium, 2, 1, 5, 11, 0);
	text_box(985, 125, 1175, 215, (char*)"", f_medium, 2, 1, 5, 14, 0);
	
	b_taokhungxanhla(10, 120, 110, 220);
	b_taokhungxanhla(110, 120, 980, 220);
	b_taokhungxanhla(980, 120, 1180, 220);
}

void b_giaodiennhd(int& x, int& y)
{
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);

			if (ktVT(110, 120, 590, 145, x, y))
			{
				//b_create_info();
				//highlight_box(110, 120, 590, 145, (char*)"So hoa don:", f_medium, 2, 1, 5, 0, 14);
				
				string shd=  "So hoa don: ";
				string s = b_input(110, 120, 590, 145, 5, 5, 1, 5, 5 , shd);
				shd = s;
			}
			if (ktVT(110, 145, 270, 170, x, y))
			{
				//b_create_info();
				highlight_box(110, 145, 270, 170, (char*)"ngay:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(270, 145, 430, 170, x, y))
			{
				//b_create_info();
				highlight_box(270, 145, 430, 170, (char*)"thang:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(430, 145, 590, 170, x, y))
			{
				//b_create_info();
				highlight_box(430, 145, 590, 170, (char*)"nam:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(590, 120, 980, 145, x, y))
			{
				//b_create_info();
				highlight_box(590, 120, 980, 145, (char*)"Ma nhan vien:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(110, 170, 430, 195, x, y))
			{
				//b_create_info();
				highlight_box(110, 170, 430, 195, (char*)"Ma vat tu:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(110, 195, 350, 220, x, y))
			{
				//b_create_info();
				highlight_box(110, 195, 350, 220, (char*)"So luong:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(350, 195, 590, 220, x, y))
			{
				//b_create_info();
				highlight_box(350, 195, 590, 220, (char*)"Don gia:", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(430, 170, 590, 195, x, y))
			{
				//b_create_info();
				highlight_box(430, 170, 590, 195, (char*)"%VAT: ", f_medium, 2, 1, 5, 0, 14);
			}
			if (ktVT(620, 165, 770, 190, x, y))
			{
				//b_create_info();
				highlight_box(620, 165, 770, 190, (char*)"Them vat tu", f_medium, 2, 1, 5, 0, 10);
			}
			if (ktVT(800, 165, 950, 190, x, y))
			{
				//b_create_info();
				highlight_box(800, 165, 950, 190, (char*)"Luu hoa don", f_medium, 2, 1, 5, 0, 10);
			}



			if (ktVT(50, 10, 250, 50, x, y)   ||
				ktVT(350, 10, 550, 50, x, y)  ||
				ktVT(650, 10, 850, 50, x, y)  ||
				ktVT(950, 10, 1150, 50, x, y) ||
				ktVT(15, 70, 310, 110, x, y)  ||
				ktVT(350, 70, 645, 110, x, y) ||
				ktVT(685, 70, 980, 110, x, y) ||
				ktVT(20, 130, 100, 170, x, y) ||
				ktVT(20, 170, 100, 210, x, y))
			{
				break;
			}
		}
	}
}






void b_hlNX(int& x, int& y)
{
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
		NX:
			if (ktVT(20, 130, 100, 170, x, y))
			{
				b_create_NX();
				highlight_box(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 0, 14);
				b_create_info();
				b_giaodiennhd(x, y);
			}
			if (ktVT(20, 170, 100, 210, x, y))
			{
				b_create_NX();
				highlight_box(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 0, 14);
				b_create_info();
				b_giaodiennhd(x, y);
				goto NX;
			}

			if (ktVT(50, 10, 250, 50, x, y) ||
				ktVT(350, 10, 550, 50, x, y) ||
				ktVT(650, 10, 850, 50, x, y) ||
				ktVT(950, 10, 1150, 50, x, y) ||
				ktVT(15, 70, 310, 110, x, y) ||
				ktVT(350, 70, 645, 110, x, y) ||
				ktVT(685, 70, 980, 110, x, y))
			{
				break;
			}
		}
		delay(1);
	}
}


//Tra hang

void b_create_gdtrahang() {
	//text_box(350, 150, 850, 200, (char*)"Vui long nhap so hoa don muon tra hang:", f_medium, 2, 15, 20, 9, 0);
	text_box_no_border(350, 150, 850, 200, (char*)"Vui long nhap so hoa don muon tra hang:", f_medium, 2, 15, 20, 9, 0);

	settextstyle(f_medium, 0, 4);
	setbkcolor(I_BG);
	outtextxy(300, 325, (char*)"So hoa don:");

	
	b_taokhungden(250, 200, 950, 500);
	b_taokhungden(550, 325, 900, 355);

	text_box(525, 450, 675, 500, (char*)"Kiem tra", f_medium, 2, 15, 20, 11, 0);
}


void b_ktVT(int& x, int& y) {
	//int x, y ;
	//bool b_nhd = false, b_th = false, b_ihd = false;
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
		batdaub_ktVT:

			if (ktVT(15, 70, 310, 110, x, y))
			{
				b_create_menu_title();
				highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 0, 10);
				b_delete_after_create();
				b_create_NX();
				b_hlNX(x, y);
				goto batdaub_ktVT;

			}
			if (ktVT(350, 70, 645, 110, x, y))
			{
				b_create_menu_title();
				highlight_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, 0, 10);
				b_delete_after_create();
				b_create_gdtrahang();
			}
			if (ktVT(685, 70, 980, 110, x, y))
			{
				b_create_menu_title();
				highlight_box(685, 70, 980, 110, (char*)"In hoa don", f_medium, 3, 10, 40, 0, 10);
				b_delete_after_create();
			}

			if (ktVT(50, 10, 250, 50, x, y) ||
				ktVT(350, 10, 550, 50, x, y) ||
				ktVT(650, 10, 850, 50, x, y) ||
				ktVT(950, 10, 1150, 50, x, y))
			{
				break;
			}

		}
		delay(1);
	}
}

