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
void deleteNode(DS_VatTu*& root, string x)
{
	if (root != NULL)
	{
		DS_VatTu* p = root;
		DS_VatTu* prev = p;
		bool isRoot = true;
		if (p->left == NULL && p->right == NULL) {
			root = NULL;
		}
		else {
			while (p != NULL && string(p->vat_tu.tenVT) != x)
			{
				isRoot = false;
				prev = p;
				if (x > string(p->vat_tu.tenVT))
				{
					p = p->right;
				}
				else
				{
					p = p->left;
				}
			}
			if (p != NULL)
			{

				if ((p->left != NULL && p->right != NULL) || isRoot)
				{
					DS_VatTu* temp = p;
					prev = p;
					if (temp->right == NULL) {
						temp = temp->left;
						prev = temp;
					}
					if (temp->right != NULL) {
						temp = temp->right;
						while (temp->left != NULL)
						{
							prev = temp;
							temp = temp->left;
						}
					}
					else {
						prev = p;
					}
					p->vat_tu = temp->vat_tu;// gan gia tri
					p = temp;// doi dia chi
				}
				DS_VatTu* t = p;
				if (t->left == NULL)
				{
					t = t->right;
				}
				else
				{
					t = t->left;
				}
				if ((string)(prev->vat_tu.tenVT) > (string)(p->vat_tu.tenVT))
				{

					prev->left = t;
				}
				else if ((string)(prev->vat_tu.tenVT) == (string)(p->vat_tu.tenVT)) {
					if (prev->left != NULL) {
						prev->left = t;
					}
					else {
						prev->right = t;
					}
				}
				else
				{

					prev->right = t;
				}
				delete p, t, prev;
			}
		}
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
void lnr(DS_VatTu* root)
{
	if (root != NULL)
	{
		lnr(root->left);
		cout << root->vat_tu.maVT << " ";
		lnr(root->right);
	}
}