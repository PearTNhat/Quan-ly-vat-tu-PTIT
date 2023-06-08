#pragma once
#include "Header.h"
#include "Goods_Struct.h"
#include "Stack.h"
DS_s_VT* createNode_k_tVT(s_VT x)
{
	DS_s_VT* p = new DS_s_VT;
	strcpy_s(p->vat_tu.maVT, x.maVT);
	strcpy_s(p->vat_tu.tenVT, x.tenVT);
	p->left = NULL;
	p->right = NULL;
	return p;
}

void insertNode_k_tenVT(DS_s_VT*& root, s_VT x)
{
	if (root == NULL)
	{
		root = createNode_k_tVT(x);
	}
	else
	{
		DS_s_VT* p = root;
		DS_s_VT* prev = p;
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
			DS_s_VT* temp = createNode_k_tVT(x);
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
void deleteNode_k_tenVT(DS_s_VT*& root, string key)
{
	DS_s_VT* curr = root;
	DS_s_VT* prev = NULL;

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

			DS_s_VT* newCurr;
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
			DS_s_VT* p = NULL;
			DS_s_VT* temp;
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
			strcpy_s(curr->vat_tu.maVT, temp->vat_tu.maVT);
		}
	}
	else {
		cout << "---Key " << key << " not found in the--";
	}

}
template <typename DS_VT>
void coppyVTtoSVT(DS_VT* root, DS_s_VT*& target) {
	s_VT x;
	DS_VT* temp = root;
	if (temp != NULL) {
		strcpy_s(x.maVT, temp->vat_tu.maVT);
		strcpy_s(x.tenVT, temp->vat_tu.tenVT);
		insertNode_k_tenVT(target,x);
		coppyVTtoSVT(temp->left, target);
		coppyVTtoSVT(temp->right, target);
	}
}
int getSize_s_VT(DS_s_VT* root) {
	if (root == NULL) {
		return 0;
	}
	return getSize_s_VT(root->left) + getSize_s_VT(root->right) + 1;
}
DS_s_VT* getNodeByIndex_s_VT(DS_s_VT*& root, int index) {
	DS_s_VT* temp = root;
	DS_s_VT* res;
	Stack <DS_s_VT> s(getSize_s_VT(root));
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
bool searchNode_k_tenVT(DS_s_VT* root, string x)
{
	DS_s_VT* p = root;
	while (p != NULL && string(p->vat_tu.tenVT) != x)
	{
		if (x > string(p->vat_tu.tenVT))
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
		return 0;
	}
	return 1;
}
DS_s_VT * getNodeby_tenVT(DS_s_VT* root, string id) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->vat_tu.tenVT == id) {
			return root;
		}
		else if (root->vat_tu.tenVT > id) {
			return getNodeby_tenVT(root->left, id);
		}
		else {
			return getNodeby_tenVT(root->right, id);
		}
	}

}
void lnrSVT(DS_s_VT* root) {
	if (root!=NULL) {
		lnrSVT(root->left);
		cout << root->vat_tu.maVT << " " << root->vat_tu.tenVT << endl;
		lnrSVT(root->right);
	}
}
//
DS_VatTu* createNode_k_mVT(VatTu x)
{
	DS_VatTu* p = new DS_VatTu;
	strcpy_s(p->vat_tu.maVT, x.maVT);
	strcpy_s(p->vat_tu.tenVT, x.tenVT);
	strcpy_s(p->vat_tu.DVT, x.DVT);
	p->vat_tu.SLT = x.SLT;
	p->vat_tu.sldaban = x.sldaban;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void insertNode_k_maVT(DS_VatTu*& root, VatTu x)
{
	if (root == NULL)
	{
		root = createNode_k_mVT(x);
	}
	else
	{
		DS_VatTu* p = root;
		DS_VatTu* prev = p;
		while (p != NULL && string(p->vat_tu.maVT) != string(x.maVT))
		{
			prev = p;
			if (string(x.maVT) > string(p->vat_tu.maVT))
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
			DS_VatTu* temp = createNode_k_mVT(x);
			if ((string)(x.maVT) > (string)(prev->vat_tu.maVT))
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

bool searchNode_k_maVT(DS_VatTu* root, string x)
{
	DS_VatTu* p = root;
	while (p != NULL && string(p->vat_tu.maVT) != x)
	{
		if (x > string(p->vat_tu.maVT))
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
		return 0;
	}
	return 1;
}
DS_VatTu *getNodebyId_maVT(DS_VatTu *root,string id) {
	if (root==NULL) {
		
		return NULL;
	}
	else {
		if ((string)root->vat_tu.maVT==id) {
			return root;
		}
		else if ((string)root->vat_tu.maVT>id) {
			return getNodebyId_maVT(root->left, id);
		}
		else {
			return getNodebyId_maVT(root->right, id);
		}
	}

}
void deleteNode_k_maVT(DS_VatTu*& root, string key)
{
	DS_VatTu* curr = root;
	DS_VatTu* prev = NULL;

	while (curr != NULL && (string)curr->vat_tu.maVT != key)
	{
		prev = curr;
		if (key < curr->vat_tu.maVT)
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
			strcpy_s(curr->vat_tu.maVT, temp->vat_tu.maVT);
			strcpy_s(curr->vat_tu.tenVT , temp->vat_tu.tenVT);
			curr->vat_tu.SLT = temp->vat_tu.SLT;
			strcpy_s(curr->vat_tu.DVT, temp->vat_tu.DVT);
			curr->vat_tu.sldaban= temp->vat_tu.sldaban;

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
	Stack <DS_VatTu> s(getSizeGoods(root));
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
		cout << root->vat_tu.tenVT << " \n";
		lnr(root->right);
	}
}
template <typename DS_VT>
void deleteTree(DS_VT* node)
{
	if (node == NULL) return;

	deleteTree(node->left);
	deleteTree(node->right);

	delete node;
}
