#pragma once
#include "Header.h"
#include "Goods_Struct.h"
#include "Stack.h"
void initNode(DS_VatTu*& root)
{
	root = NULL;
}
DS_VatTu* createNode(VatTu x)
{
	DS_VatTu* p = new DS_VatTu;
	strcpy_s(p->vat_tu.maVT, x.maVT);
	strcpy_s(p->vat_tu.tenVT, x.tenVT);
	strcpy_s(p->vat_tu.DVT, x.DVT);
	p->vat_tu.SLT = x.SLT;
	p->vat_tu.trangThai = x.trangThai;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void insertNode(DS_VatTu*& root, VatTu x)
{
	if (root == NULL)
	{
		root = createNode(x);
	}
	else
	{
		DS_VatTu* p = root;
		DS_VatTu* prev = p;
		while (p != NULL && string(p->vat_tu.tenVT) != string(x.tenVT))
		{
			prev = p;
			if (string(x.tenVT) > string(p->vat_tu.tenVT))
			{
				p = p->right;
			}
			else
			{
				p = p->left;
			}
		}
		if (p == NULL)
		{
			DS_VatTu* temp = createNode(x);
			if ((string)(x.tenVT) > (string)(prev->vat_tu.tenVT))
			{
				prev->right = temp;
			}
			else
			{
				prev->left = temp;
			}
		}
	}
}
int searchNode(DS_VatTu* root, string x)
{
	DS_VatTu* p = root;
	while (p != NULL && string(p->vat_tu.tenVT) != string(x))
	{
		if (string(x) > string(p->vat_tu.tenVT))
		{
			p = p->right;
		}
		else
		{
			p = p->left;
		}
	}
	if (p == NULL)
	{
		return -1;
	}
	return 1;
}
void deleteNode(DS_VatTu*& root, string key)
{
	DS_VatTu* curr = root;
	DS_VatTu* prev = NULL;
	while (curr != NULL && (string)curr->vat_tu.tenVT != key)
	{
		prev = curr;
		if (key < curr->vat_tu.tenVT)
			curr = curr->left;
		else
			curr = curr->right;
	}

	if (curr != NULL)
	{
		if (curr->left == NULL || curr->right == NULL)
		{

			DS_VatTu* newCurr;
			if (curr->left == NULL)
				newCurr = curr->right;
			else
				newCurr = curr->left;

			if (prev == NULL) {
				root = newCurr;
			}
			else {
				if (curr == prev->left)
					prev->left = newCurr;
				else
					prev->right = newCurr;

			}
		}
		else
		{
			DS_VatTu* p = NULL;
			DS_VatTu* temp;
			temp = curr->right;
			while (temp->left != NULL)
			{
				p = temp;
				temp = temp->left;
			}
			if (p != NULL)
				p->left = temp->right;
			else
				curr->right = temp->right;
			strcpy_s(curr->vat_tu.tenVT, temp->vat_tu.tenVT);

		}
	}
	else {
		cout << "---Key " << key << " not found in the--";
	}

}

int getSizeGoods(DS_VatTu* root) {
	if (root == NULL) {
		return 0;
	}
	return getSizeGoods(root->left) + getSizeGoods(root->right) + 1;
}
DS_VatTu* getIndexGoods(DS_VatTu*& root, int index) {
	DS_VatTu* temp = root;
	DS_VatTu* res;
	Stack s(getSizeGoods(root));
	int k = 0;
	while (1) {
		while (temp != NULL) {
			push(s, temp);
			temp = temp->left;
		}
		if (!isEmpty(s)) {
			res = pop(s);
			index--;
			if (index == 0) {
				return res;
			}
			if (res->right != NULL) {
				temp = res->right;
			}
		}
		else {
			break;
		}
	}
	return NULL;
}
bool findMVT(DS_VatTu* root, string mvt) {
	DS_VatTu* temp = root;
	DS_VatTu* res;
	Stack s(getSizeGoods(root));
	int k = 0;
	while (1) {
		while (temp != NULL) {
			push(s, temp);
			temp = temp->left;
		}
		if (!isEmpty(s)) {
			res = pop(s);
			if ((string)res->vat_tu.maVT == mvt) {
				return true;
			}
			if (res->right != NULL) {
				temp = res->right;
			}
		}
		else {
			break;
		}
	}
	return false;
}

DS_VatTu* searchVT(DS_VatTu* root, string mvt) {
	DS_VatTu* temp = root;
	DS_VatTu* res;
	Stack s(getSizeGoods(root));
	int k = 0;
	while (1) {
		while (temp != NULL) {
			push(s, temp);
			temp = temp->left;
		}
		if (!isEmpty(s)) {
			res = pop(s);
			if ((string)res->vat_tu.maVT == mvt) {
				return res;
			}
			if (res->right != NULL) {
				temp = res->right;
			}
		}
		else {
			break;
		}
	}
	return NULL;
}
void lnr(DS_VatTu* root)
{
	if (root != NULL)
	{
		lnr(root->left);
		cout << root->vat_tu.maVT << " ";
		lnr(root->right);
	}
}