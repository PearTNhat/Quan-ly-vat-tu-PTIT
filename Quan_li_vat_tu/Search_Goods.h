#pragma once
#include "Header.h"
#include"Common.h"
#include "Goods_FuncTree.h"
#include "Goods_Struct.h"
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