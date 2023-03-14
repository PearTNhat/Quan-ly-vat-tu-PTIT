#pragma once
#include "Header.h"
#include "Goods_Struct.h"
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
        DS_VatTu* prev=p;
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
            DS_VatTu* temp = createNode(x);
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
int searchNode(DS_VatTu* root, char x[])
{
    DS_VatTu* p = root;
    while (p != NULL && string(p->vat_tu.maVT) != string(x))
    {
        if (string(x) > string(p->vat_tu.maVT))
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
void deleteNode(DS_VatTu*& root, char x[])
{
    if (root != NULL)
    {
        DS_VatTu* p = root;
        DS_VatTu* prev = p;
        while (p != NULL && string(p->vat_tu.maVT) != string(x))
        {
            prev = p;
            if (string(x) > string(p->vat_tu.maVT))
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
            if (p->left != NULL && p->right != NULL)
            {
                DS_VatTu* temp = p;
                prev = p;
                temp = temp->right;
                while (temp->left != NULL)
                {
                    prev = temp;
                    temp = temp->left;
                }
                p->vat_tu = temp->vat_tu;
                if ((string)(prev->vat_tu.maVT) > (string)(temp->vat_tu.maVT))
                {
                    prev->left = NULL;
                }
                else
                {
                    prev->right = NULL;
                }
                p = temp;
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
            if ((string)(prev->vat_tu.maVT) > (string)(p->vat_tu.maVT))
            {
                prev->left = t;
            }
            else
            {
                prev->right = t;
            }
            delete p, t, prev;
        }
    }
}
int getSizeTree(DS_VatTu* root) {
    if (root == NULL) {
        return 0;
    }
    return getSizeTree(root->left) + getSizeTree(root->right) + 1;
}
void copy_to_arr(DS_VatTu* root, TempArr& arr) {
    if (root != NULL) {
        copy_to_arr(root->left, arr);
        //arr.vat_tu[arr.n] = new VatTu;
        strcpy_s(arr.vat_tu[arr.n].maVT, root->vat_tu.maVT);
        strcpy_s(arr.vat_tu[arr.n].tenVT, root->vat_tu.tenVT);
        strcpy_s(arr.vat_tu[arr.n].DVT, root->vat_tu.DVT);
        arr.vat_tu[arr.n].SLT = root->vat_tu.SLT;
        arr.n++;
        copy_to_arr(root->right, arr);
    }
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