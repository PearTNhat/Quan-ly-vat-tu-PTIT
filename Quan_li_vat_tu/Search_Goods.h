#pragma once
#include "Goods_Func.h"
#include "Header.h"
#include"Common.h"
#include "Goods_FuncTree.h"
#include "Goods_Struct.h"
void goods_table_reducing(
	DS_VatTu* ds_vt,
	DS_s_VT* ds_s_vt,
	view_page& view_page,
	int num_cols,
	string search
);
void search_goods_I(int& x, int& y, DS_VatTu* ds_vt);

void search_goods(DS_VatTu *root,DS_s_VT*&root_k_tenVT, string value) {
	value = lowercase(value);
	deleteAllSpace(value);
	DS_VatTu* temp = root;
	DS_VatTu* res;
	s_VT s_vt ;
	Stack <DS_VatTu> s(getSizeGoods(root));
	int k = 0;
	while (1) {
		while (temp != NULL) {
			push(s, temp);
			temp = temp->left;
		}
		if (!isEmpty(s)) {
			res = pop(s);
			strcpy_s(s_vt.maVT, res->vat_tu.maVT);
			strcpy_s(s_vt.tenVT, res->vat_tu.tenVT);
			if (search_string(res->vat_tu.tenVT, value) >= 0) {
				insertNode_k_tenVT(root_k_tenVT, s_vt);
			}
			else if (search_string(res->vat_tu.maVT, value) >= 0) {
				insertNode_k_tenVT(root_k_tenVT, s_vt);
			}
			if (res->right != NULL) {
				temp = res->right;
			}
		}
		else {
			break;
		}
	}
}
void search_goods_I(int &x, int &y,DS_VatTu *ds_vt) {
	int svt_NULL = 0;
	int search_empty = 0;
	string value;
	view_page searhcing_view;
	DS_s_VT* result = NULL;
	string placeholder = "Nhap ten hoac id can tim kiem";
	search_goods(ds_vt, result, value);
	goods_table_reducing(ds_vt, result, searhcing_view, 10, value);
	create_sf_header((string)"    Tro ve", (string)"Nhap ten hoac id can tim kiem");
	while (1) { // chong rerender k can thiet
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (ktVT(50, 72, 400, 108, x, y)) {
				while (1) {
					value = input_one(x, y, 50, 72, 410, 108, 10, 10, value, 25);
					placeholder = value;

					if (!ktVT(50, 72, 400, 108, x, y)) {
						if (value == "") {
							placeholder = "Nhap ten hoac id can tim kiem";
							create_sf_header((string)"    Tro ve", placeholder);
						}
						break;
					}
					deleteTree(result);
					result = NULL;
					search_goods(ds_vt,result,value);
					if (value == "") {
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
															// là lúc đang bấm chữ
						goods_table_reducing(ds_vt, result, searhcing_view, 10, value);
					}
					delay(1);
				}
			}
			if (ktVT(650, 565, 685, 600, x, y)) {
				if (searhcing_view.current == searhcing_view.page) {
					continue;
				}
				next_page(650, 565, 685, 600, searhcing_view);
				goods_table_reducing(ds_vt, result, searhcing_view, 10, placeholder);
			}
			if (ktVT(495, 565, 530, 600, x, y)) {
				if (searhcing_view.current == 1) {
					continue;
				}
				prev_page(495, 565, 530, 600, searhcing_view);
				goods_table_reducing(ds_vt, result, searhcing_view, 10, placeholder);
			}
			if (ktVT(950, 70, 1150, 110,x,y) || ktVT(20, 10, 220, 50, x, y) || ktVT(320, 10, 520, 50, x, y) || ktVT(620, 10, 820, 50, x, y) || ktVT(920, 10, 1120, 50, x, y) || ktVT(1140, 10, 1190, 50, x, y)) {
				break;
			}
			delay(1);
		}
	}
	deleteTree(result);
}
void goods_table_reducing(
	DS_VatTu* ds_vt,
	DS_s_VT* ds_s_vt,
	view_page& view_page,
	int num_cols,
	string search
)
{
	setlinestyle(0, 0, 0);
	delete_after_header();
	create_sf_header((string)"    Tro ve", search);
	// tnh so page co trong trang
	setcolor(0);
	int n = getSize_s_VT(ds_s_vt);
	int page = n / num_cols;
	int du = n % num_cols;
	view_page.page = du? page + 1 : page;
	cout << view_page.current << " " << view_page.page;

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
	outtextxy(95, text_top, (char*)g_table_header[0]);
	outtextxy(230, text_top, (char*)g_table_header[1]);
	outtextxy(450, text_top, (char*)g_table_header[2]);
	outtextxy(650, text_top, (char*)g_table_header[3]);
	setfillstyle(1, 15);
	setbkcolor(15);
	int d = 0;//delete
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
		setfillstyle(1, 15);
		setbkcolor(15);
	}
	//------------- k can cos the xoa

	// < >
	page_transition(view_page);

}