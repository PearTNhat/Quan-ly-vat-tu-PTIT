#pragma once
#include"Header.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0


// chi tiet hoa don
struct CT_HoaDon
{
	char MAVT[11];
	int Soluong;
	int Dongia;
	float VAT;
	bool TrangThai;
};

struct DS_CT_HoaDon
{
	CT_HoaDon ct_hoadon;
	DS_CT_HoaDon* next;
};
typedef DS_CT_HoaDon* dscthd;
dscthd dautien = NULL;

void Initialize(dscthd& dautien)
{
	dautien = NULL;
}

dscthd dNewnode(void)
{
	dscthd d = new DS_CT_HoaDon;
	return d;
}
dscthd d = dNewnode();

dscthd nodepointer(dscthd dautien, int i)
{
	dscthd d;
	int vitri = 1;
	d = dautien;
	while (d != NULL && vitri < i)
	{
		d = d->next;
		vitri++;
	}
	return(d);
}

void Insert_First(dscthd& First, CT_HoaDon x)
{
	dscthd d;
	d = new DS_CT_HoaDon;
	d->ct_hoadon = x;
	d->next = dautien;
	dautien = d;
}

void Insert_after(dscthd d, CT_HoaDon x)
{
	dscthd e;
	if (d == NULL)
		cout << "Khong the them phan tu vao danh sach";
	else
	{
		e = new DS_CT_HoaDon;
		e->ct_hoadon = x;
		e->next = d->next;
		d->next = e;
	}
}

//hoa don

struct Date
{
	int ngay;
	int thang;
	int nam;

	bool operator==(Date& other)
	{
		return this->ngay == other.ngay && this->thang == other.thang && this->nam == other.nam ? true : false;
	}

	bool operator!=(Date& other)
	{
		return this->ngay != other.ngay && this->thang != other.thang && this->nam != other.nam ? true : false;
	}
};


struct HoaDon
{
	char SoHD[21];
	Date date;
	char Loai[2];

	bool operator==(HoaDon& other)
	{
		if (strcmp(this->SoHD, other.SoHD) == 0 &&
			strcmp(this->Loai, other.Loai) == 0 &&
			this->date == other.date)
			return true;

		return false;

	}

	bool operator!=(HoaDon& other)
	{
		if (strcmp(this->SoHD, other.SoHD) != 0 &&
			strcmp(this->Loai, other.Loai) != 0 &&
			this->date != other.date)
			return true;

		return false;

	}
};

struct DS_HoaDon
{
	HoaDon hoadon;
	DS_HoaDon* next;
};
typedef DS_HoaDon* PTRHD;
PTRHD First = NULL;

/* Tac vu nodepointer: xac dinh con tro cua nut i trong danh sach lien ket
   (i = 2, ...) */
PTRHD nodepointer(PTRHD First, int i)
{
	PTRHD p;
	int vitri = 1;
	p = First;
	while (p != NULL && vitri < i)
	{
		p = p->next;
		vitri++;
	}
	return(p);
}



// Tac vu position: xac dinh vi tri cua nut p trong danh sach lien ket
int position(PTRHD First, PTRHD p)
{
	int vitri = 1;
	PTRHD q = First;
	while (q != NULL && q != p)
	{
		q = q->next; 	vitri++;
	}
	if (q == NULL)     return (-1);
	return(vitri);
}

//Initialize khoi dong danh sach lien ket
void Initialize(PTRHD& First)
{
	First = NULL;
}


PTRHD Newnode(HoaDon x = {})
{
	PTRHD p = new DS_HoaDon;
	p->hoadon = x;
	p->next = NULL;
	return p;
}
PTRHD p= Newnode();
void Insert_First(PTRHD& First, HoaDon x)
{
	PTRHD p=Newnode(x);
	p->next = First;
	First = p;
}

void Insert_after(PTRHD &p, HoaDon x)
{
	PTRHD q=p;
	if (p == NULL) {
		Insert_First(p,x);
	}
	else
	{
		while (q->next != NULL) {
			q = q->next;
		}
		PTRHD temp=Newnode(x);
		q->next = temp;
	}
}

PTRHD Search_info(PTRHD First, HoaDon x)
{
	PTRHD p;
	for (p = First; p != NULL; p = p->next)
	{
		if (p->hoadon.SoHD == x.SoHD && p->hoadon.date == x.date && p->hoadon.Loai == x.Loai) return p;
		return NULL;
	}
}

int Empty(PTRHD First)
{
	return(First == NULL);
}

int Delete_First(PTRHD& First)
{
	PTRHD p;
	if (Empty(First))
		return 0;
	p = First;
	First = p->next;
	delete p;
	return 1;
}

int Delete_after(PTRHD p)
{
	PTRHD q;
	if ((p == NULL) || (p->next == NULL))
		return 0;
	q = p->next;
	p->next = q->next;
	delete q;
	return 1;
}

int Delete_Info(PTRHD& First, HoaDon x)
{
	PTRHD p = First;
	if (First = NULL)
		return 0;
	if (First->hoadon == x)
	{
		Delete_First(First);return 1;
	}

	for (p = First;p->next != NULL && p->next->hoadon != x;p = p->next);
	if (p->next != NULL)
	{
		Delete_after(p); return 1;
	}
	return 0;
}

int Delete_ALl_Info(PTRHD& First, HoaDon x)
{
	int count = 0;
	if (First == NULL) return 0;
	for (PTRHD p = First; p->next != NULL;)
	{
		if (p->next->hoadon == x)
		{
			Delete_after(p); count++;
		}
		else
			p = p->next;
	}
	if (First->hoadon == x)
	{
		Delete_First(First); count++;
	}
	//return count;
}


void Clearlist(PTRHD& First)
{
	PTRHD p;
	while (First != NULL) Delete_First(First);
}
void display_dsHD(PTRHD First) {
	if (First!=NULL) {
		PTRHD p= First;
		while (p!=NULL) {
			cout << p->hoadon.SoHD << ",";
			cout << p->hoadon.Loai;
			p = p->next;
			cout << endl;
		}
		
	}
	else {
		cout << "Node is NULL";
	}
}
int getNums_dsHD(PTRHD First) {
	int count = 0;
	while (First !=NULL) {
		count++;
		First = First->next;
	}
	return count;
}

int Empty(dscthd dautien)
{
	return(dautien == NULL);
}


int Delete_First(dscthd& dautien)
{
	dscthd p;
	if (Empty(dautien))
		return 0;
	p = dautien;
	dautien = p->next;
	delete p;
	return 1;
}

void Clearlist(dscthd& First)
{
	while (First != NULL) Delete_First(First);
}

void traverse(PTRHD First, dscthd dautien)
{
	PTRHD p;
	dscthd d;
	int stt = 1;
	p = First;
	d = dautien;
	if (p == NULL)
		cout << "Khong co hoa don trong danh sach ";
	while (p != NULL && d != NULL)
	{
		cout << "\n\n";
		cout << "Hoa don so " << stt++ << "\n";
		cout << "So hoa don: " << p->hoadon.SoHD << "\n";
		cout << "Date: " << p->hoadon.date.ngay << "/" << p->hoadon.date.thang << "/" << p->hoadon.date.nam << "\n";
		cout << "Loai: " << p->hoadon.Loai << "\n";
		cout << "Ma vat tu: " << d->ct_hoadon.MAVT << "\n";
		cout << "So luong: " << d->ct_hoadon.Soluong << "\n";
		cout << "Don gia: " << d->ct_hoadon.Dongia << "\n";
		cout << "%VAT: " << d->ct_hoadon.VAT << "\n";
		cout << "Trang thai ( 1-mua, 0-tra): " << d->ct_hoadon.TrangThai << "\n";

		p = p->next;
		d = d->next;
	}
}


char menu()
{
	char chucnang;
	do
	{
		system("cls");
		cout << "NHAP XUAT VAT TU \n";
		cout << "  1: Tao hoa don\n";
		cout << "  2: Them hoa don\n";
		cout << "  3: Xem danh sach hoa don\n";
		cout << "  0: Ket thuc chuong trinh\n";
		cout << "Chuc nang ban chon: ";
		cin >> chucnang;
	} while (chucnang < '0' || chucnang> '3');
	return chucnang;
}

void Creart_List(PTRHD& First, dscthd& dautien)
{
	PTRHD Last = nullptr, p = nullptr;
	HoaDon hoadon;

	dscthd cuoicung = nullptr, d = nullptr;
	CT_HoaDon ct_hoadon;

	Clearlist(First);
	cout << "So hoa don: "; cin >> hoadon.SoHD;

	while (hoadon.SoHD[0] != '0')
	{
		cout << "Ngay: "; cin >> hoadon.date.ngay;
		cout << "Thang: "; cin >> hoadon.date.thang;
		cout << "Nam: "; cin >> hoadon.date.nam;
		cout << "Loai: "; cin >> hoadon.Loai;


		if (hoadon.Loai[0] == 'N')
		{
			cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
			cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
			cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
			cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
			cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;
		}
		if (hoadon.Loai[0] == 'X')
		{
			cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
			cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
			cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
			cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
			cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;
		}

		p = new DS_HoaDon;
		p->hoadon = hoadon;
		if (First == NULL) First = p;
		else Last->next = p;
		Last = p;
		p->next = NULL;

		d = new DS_CT_HoaDon;
		d->ct_hoadon = ct_hoadon;
		if (dautien == NULL) dautien = d;
		else cuoicung->next = d;
		cuoicung = d;
		p->next = NULL;

		cout << "\nSo hoa don moi: "; cin >> hoadon.SoHD;

	}


}


void demoPhu()
{
	PTRHD First, Last = nullptr;
	HoaDon hoadon;
	dscthd dautien, cuoicung = nullptr;
	CT_HoaDon ct_hoadon;
	int vitri;
	char chucnang, c, maso[5], c_vitri[5];
	// khoi dong danh sach lien ket
	Initialize(First);
	Initialize(dautien);
	do
	{
		chucnang = menu();
		switch (chucnang)
		{
		case '1':
		{
			system("cls");
			Creart_List(First, dautien);
			break;
		}
		case '2':
		{
			system("cls");
			cout << "Nhap vi tri muon them hoa don: "; cin >> vitri;
			p = nodepointer(First, vitri - 1);
			d = nodepointer(dautien, vitri - 1);
			if (vitri <= 0 || p == NULL || d == NULL)
			{
				cout << "Vi tri khong hop le";
				system("pause");
			}
			else
			{


				cout << "So hoa don: "; cin >> hoadon.SoHD;
				cout << "Ngay: "; cin >> hoadon.date.ngay;
				cout << "Thang: "; cin >> hoadon.date.thang;
				cout << "Nam: "; cin >> hoadon.date.nam;
				cout << "Loai: "; cin >> hoadon.Loai;


				if (hoadon.Loai[0] == 'N')
				{
					cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
					cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
					cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
					cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
					cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;
				}
				if (hoadon.Loai[0] == 'X')
				{
					cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
					cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
					cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
					cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
					cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;
				}
				if (vitri == 1)
				{
					Insert_First(First, hoadon);
					Insert_First(dautien, ct_hoadon);
				}
				else
				{
					Insert_after(p, hoadon);
					Insert_after(d, ct_hoadon);
				}

			}
			break;
		}
		case '3':
		{
			system("cls");
			cout << "DANH SACH HOA DON\n";
			traverse(First, dautien);
			system("pause");
			break;
		}
		}
	} while (chucnang != '0');
	Clearlist(dautien);
	Clearlist(First);
	//return 0;
}