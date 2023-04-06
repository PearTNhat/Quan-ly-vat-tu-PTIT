#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#include "Bill_Struct.h"
#include "input_bill.h"
#include "Staff_func.h"

view_page vp_m_ss;

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
	
	b_taokhungden(10, 120, 1180, 600);
}

void b_delete_after_create() {
	setfillstyle(1, bk_screen);
	bar(11, 121, 1179, 599);
}

void b_create_NX()
{
	b_taokhungden(10, 120, 110, 220);
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
	text_box(620, 145, 770, 170, (char*)"Them vat tu", f_medium, 2, 1, 5, 11, 0);
	text_box(800, 145, 950, 170, (char*)"Luu hoa don", f_medium, 2, 1, 5, 11, 0);
	text_box(590, 170, 980, 195, (char*)"Trang thai", f_medium, 2, 1, 135, 9, 0);
	text_box(590, 195, 740, 220, (char*)"1:khach mua", f_medium, 2, 1, 1, 9, 0);
	text_box(740, 195, 980, 220, (char*)"0:khach da tra hang", f_medium, 2, 1, 1, 9, 0);
	text_box_no_border(985, 125, 1175, 215, (char*)"", f_medium, 2, 1, 5, 14, 0);
	
	b_taokhungden(10, 120, 110, 220);
	b_taokhungden(110, 120, 980, 220);
	b_taokhungden(980, 120, 1180, 220);
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
				//SoHD
				string d = input_bill(x, y, 250, 121, 588, 143, 5, 3, 985, 125, 1175, 215, "", 20, "number", "upcase");
			}
			if (ktVT(110, 145, 270, 170, x, y))
			{
				//ngay
				string d = input_bill(x, y, 175, 146, 268, 168, 5, 3, 985, 125, 1175, 215, "", 2, "number", "calmCase");
			}
			if (ktVT(270, 145, 430, 170, x, y))
			{
				//thang
				string d = input_bill(x, y, 345, 146, 428, 168, 5, 3, 985, 125, 1175, 215, "", 2, "number", "calmCase");
			}
			if (ktVT(430, 145, 590, 170, x, y))
			{
				//nam
				string d = input_bill(x, y, 480, 146, 588, 168, 5, 3, 985, 125, 1175, 215, "", 2, "number", "calmCase");
			}
			if (ktVT(590, 120, 980, 145, x, y))
			{
				//maNV
				string d = input_bill(x, y, 750, 121, 978, 143, 5, 3, 985, 125, 1175, 215, "", 10, "number", "calmCase");
			}
			if (ktVT(110, 170, 430, 195, x, y))
			{
				//MAVT
				string d = input_bill(x, y, 235, 171, 428, 193, 5, 3, 985, 125, 1175, 215, "", 10, "textNumberNoSpace", "calmCase");
			}
			if (ktVT(110, 195, 350, 220, x, y))
			{
				//Soluong
				string d = input_bill(x, y, 220, 196, 348, 218, 5, 3, 985, 125, 1175, 215, "", 5, "number", "calmCase");
			}
			if (ktVT(350, 195, 590, 220, x, y))
			{
				//Dongia
				string d = input_bill(x, y, 450, 196, 588, 218, 5, 3, 985, 125, 1175, 215, "", 7, "number", "calmCase");
			}
			if (ktVT(430, 170, 590, 195, x, y))
			{
				//VAT
				string d = input_bill(x, y, 495, 171, 588, 193, 5, 3, 985, 125, 1175, 215, "", 2, "number", "calmCase");
			}
			if (ktVT(590, 195, 740, 220, x, y))
			{
				//1: khach mua
				text_box(590, 195, 740, 220, (char*)"1:khach mua", f_medium, 2, 1, 1, I_HIGHLIGHT, 0);
			}
			if (ktVT(740, 195, 980, 220, x, y))
			{
				//0 khach da tra hang
				text_box(740, 195, 980, 220, (char*)"0:khach da tra hang", f_medium, 2, 1, 1, I_HIGHLIGHT, 0);
			}
			if (ktVT(620, 165, 770, 190, x, y))
			{
				//b_create_info();
				//highlight_box(620, 165, 770, 190, (char*)"Them vat tu", f_medium, 2, 1, 5, 0, 10);
			}
			if (ktVT(800, 165, 950, 190, x, y))
			{
				//b_create_info();
				//highlight_box(800, 165, 950, 190, (char*)"Luu hoa don", f_medium, 2, 1, 5, 0, 10);
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

void HIGHTLIGHT_ADD_VT(int& x, int& y)
{
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			{
				if (ktVT(620, 165, 770, 190, x, y))
				{
					
					highlight_box(620, 165, 770, 190, (char*)"Them vat tu", f_medium, 2, 1, 5, 14, 0);
				}
				if (ktVT(50, 10, 250, 50, x, y) ||
					ktVT(350, 10, 550, 50, x, y) ||
					ktVT(650, 10, 850, 50, x, y) ||
					ktVT(950, 10, 1150, 50, x, y) ||
					ktVT(15, 70, 310, 110, x, y) ||
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
}

void HIGHTLIGHT_ADD_HD(int& x, int& y)
{
	while (1)
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			{
				if (ktVT(620, 165, 770, 190, x, y))
				{
					highlight_box(800, 165, 950, 190, (char*)"Luu hoa don", f_medium, 2, 1, 5, 0, 10);
				}
				if (ktVT(50, 10, 250, 50, x, y) ||
					ktVT(350, 10, 550, 50, x, y) ||
					ktVT(650, 10, 850, 50, x, y) ||
					ktVT(950, 10, 1150, 50, x, y) ||
					ktVT(15, 70, 310, 110, x, y) ||
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
}



//void create_bill_tabble()
//{
//
//}





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
				highlight_box(20, 130, 100, 170, (char*)"N", f_medium, 3, 10, 30, 14, 0);
				b_create_info();
				b_giaodiennhd(x, y);
			}
			if (ktVT(20, 170, 100, 210, x, y))
			{
				b_create_NX();
				highlight_box(20, 170, 100, 210, (char*)"X", f_medium, 3, 10, 30, 14, 0);
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
				highlight_box(15, 70, 310, 110, (char*)"Lap hoa don", f_medium, 3, 10, 40, 14, 0);
				b_delete_after_create();
				b_create_NX();
				b_hlNX(x, y);
				goto batdaub_ktVT;

			}
			if (ktVT(350, 70, 645, 110, x, y))
			{
				b_create_menu_title();
				highlight_box(350, 70, 645, 110, (char*)"Tra hang", f_medium, 3, 10, 40, 14, 0);
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

