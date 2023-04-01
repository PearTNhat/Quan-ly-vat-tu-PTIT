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

	bool operator==(CT_HoaDon& other)
	{
		if (strcmp(this->MAVT, other.MAVT) == 0 &&
			this->Soluong == other.Soluong &&
			this->Dongia == other.Dongia &&
			this->VAT == other.VAT &&
			this->TrangThai == other.TrangThai)
			return true;

		return  false;
	}

	bool operator!=(CT_HoaDon& other)
	{
		if (strcmp(this->MAVT, other.MAVT) != 0 ||
			this->Soluong != other.Soluong ||
			this->Dongia != other.Dongia ||
			this->VAT != other.VAT ||
			this->TrangThai != other.TrangThai)
			return true;

		return  false;
	}
};

struct DS_CT_HoaDon
{
	CT_HoaDon ct_hoadon;
	DS_CT_HoaDon* next;
};
typedef DS_CT_HoaDon* dscthd;

//Initialize khoi dong danh sach lien ket ct hoadon
void Initialize(dscthd& dautien)
{
	dautien = NULL;
}

/* Tac vu nodepointer: xac dinh con tro cua nut i trong danh sach lien ket ct hoadon
   (i = 2, ...) */
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

// Tac vu position: xac dinh vi tri cua nut p trong danh sach lien ket ct hoadon
int position(dscthd dautien, dscthd d)
{
	int vitri = 1;
	dscthd q = dautien;
	while (q != NULL && q != d)
	{
		q = q->next; 	vitri++;
	}
	if (q == NULL)     return (-1);
	return(vitri);
}


// Newnode ct hoadon
dscthd dNewnode(CT_HoaDon x = {})
{
	dscthd d = new DS_CT_HoaDon;
	d->ct_hoadon = x;
	d->next = NULL;
	return d;
}
dscthd d = dNewnode();



// them vao dau ct hoadon
void Insert_First(dscthd& dautien, CT_HoaDon x)
{
	dscthd d = dNewnode(x);
	d->next = dautien;
	dautien = d;
}

//them vao sau cung ct hoadon
void Insert_last_d(dscthd& d, CT_HoaDon x)
{
	dscthd q = d;
	if (d == NULL) {
		Insert_First(d, x);
	}
	else
	{
		while (q->next != NULL) {
			q = q->next;
		}
		dscthd temp = dNewnode(x);
		q->next = temp;
	}
}

//them vao sau d của ct hoadon
void Insert_after_d(dscthd d, CT_HoaDon  x)
{
	dscthd q;
	if (d == NULL)
		Insert_First(d, x);
	else
	{
		q = new DS_CT_HoaDon;
		q->ct_hoadon = x;
		q->next = d->next;
		d->next = q;
	}

}


// kiem tra rong ct hoadon
int Empty(dscthd dautien)
{
	return(dautien == NULL);
}

// xoa dau ct hoadon
int Delete_First(dscthd& dautien)
{
	dscthd d;
	if (Empty(dautien))
		return 0;
	d = dautien;
	dautien = d->next;
	delete d;
	return 1;
}

// xoa sau d ct hoa don
int Delete_after_d(dscthd d)
{
	dscthd q;
	if ((d == NULL) || (d->next == NULL))
		return 0;
	q = d->next;
	d->next = q->next;
	delete q;
	return 1;
}

// xoa theo thong tin ct hoadon
int Delete_Info(dscthd& dautien, CT_HoaDon x)
{
	dscthd d = dautien;
	if (dautien = NULL)
		return 0;
	if (dautien->ct_hoadon == x)
	{
		Delete_First(dautien);return 1;
	}

	for (d = dautien;d->next != NULL && d->next->ct_hoadon != x;d = d->next);
	if (d->next != NULL)
	{
		Delete_after_d(d); return 1;
	}
	return 0;
}

// xoa tat ca theo thong tin ct hoadon
int Delete_ALl_Info(dscthd& dautien, CT_HoaDon x)
{
	int count = 0;
	if (dautien == NULL) return 0;
	for (dscthd d = dautien; d->next != NULL;)
	{
		if (d->next->ct_hoadon == x)
		{
			Delete_after_d(d); count++;
		}
		else
			d = d->next;
	}
	if (dautien->ct_hoadon == x)
	{
		Delete_First(dautien); count++;
	}
	return count;
}

// xoa danh sach lien ket ct hoadon
void Clearlist(dscthd& dautien)
{
	//dscthd p;
	while (dautien != NULL) Delete_First(dautien);
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
	dscthd first_cthd = NULL;
	//CT_HoaDon ct_hoadon;
	// nap chong toan tu 
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
		if (strcmp(this->SoHD, other.SoHD) != 0 ||
			strcmp(this->Loai, other.Loai) != 0 ||
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

//Initialize khoi dong danh sach lien ket hoadon
void Initialize(PTRHD& First)
{
	First = NULL;
}

/* Tac vu nodepointer: xac dinh con tro cua nut i trong danh sach lien ket hoadon
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

// Tac vu position: xac dinh vi tri cua nut p trong danh sach lien ket hoadon
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


// Newnode hoadon
PTRHD Newnode(HoaDon x = {})
{
	PTRHD p = new DS_HoaDon;
	p->hoadon = x;
	p->next = NULL;
	return p;
}
PTRHD p = Newnode();



// them vao dau hoadon
void Insert_First(PTRHD& First, HoaDon x)
{
	PTRHD p = Newnode(x);
	p->next = First;
	First = p;
}

//them vao sau hoadon
void Insert_last(PTRHD& p, HoaDon x)
{
	PTRHD q = p;
	if (p == NULL) {
		Insert_First(p, x);
	}
	else
	{
		while (q->next != NULL) {
			q = q->next;
		}
		PTRHD temp = Newnode(x);
		q->next = temp;
	}
}

//them vao sau p cua hoadon
void Insert_after_p(PTRHD p, HoaDon x)
{
	PTRHD q;
	if (p == NULL)
		Insert_First(p, x);
	else
	{
		q = new DS_HoaDon;
		q->hoadon = x;
		q->next = p->next;
		p->next = q;
	}

}

//tim thong tin hoadon 
PTRHD Search_info(PTRHD First, HoaDon x)
{
	PTRHD p;
	for (p = First; p != NULL; p = p->next)
	{
		if (p->hoadon.SoHD == x.SoHD) return p;

	}
	return NULL;
}

// kiem tra rong hoadon
int Empty(PTRHD First)
{
	return(First == NULL);
}

// xoa dau hoadon
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

// xoa sau (hoa don)
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

// xoa theo thong tin ( hoadon)
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

// xoa tat ca theo thong tin ( hoadon)
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
	return count;
}

// xoa danh sach lien ket hoadon
void Clearlist(PTRHD& First)
{
	//PTRHD p;
	while (First != NULL) Delete_First(First);
}
void display_dsHD(PTRHD First) {
	if (First != NULL) {
		PTRHD p = First;
		while (p != NULL) {
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


int getNumOfBill(PTRHD First) {
	int count = 0;
	PTRHD temp = First;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	temp = NULL;
	delete temp;
	return count;
}

// ham chung cua ct hoadon va hoadon
void traverse(PTRHD First, dscthd first_cthd)
{
	PTRHD p;
	dscthd d;

	int stt = 1;
	p = First;
	d = first_cthd;

	if (p == NULL)
		cout << "Khong co hoa don trong danh sach ";
	while (p != NULL)
	{
		cout << "\n\n";
		cout << "STT: " << stt++ << "\n";
		cout << "So hoa don: " << p->hoadon.SoHD << "\n";
		cout << "Date: " << p->hoadon.date.ngay << "/" << p->hoadon.date.thang << "/" << p->hoadon.date.nam << "\n";
		cout << "Loai: " << p->hoadon.Loai << "\n";
		while (d != NULL)
		{
			cout << "Ma vat tu: " << d->ct_hoadon.MAVT << "\n";
			cout << "So luong: " << d->ct_hoadon.Soluong << "\n";
			cout << "Don gia: " << d->ct_hoadon.Dongia << "\n";
			cout << "%VAT: " << d->ct_hoadon.VAT << "\n";
			cout << "Trang thai ( 1-mua, 0-tra): " << d->ct_hoadon.TrangThai << "\n";
			cout << "\n";
			d = d->next;
		} 

		p = p->next;
		

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
		cout << "  4: Hieu chinh danh sach hoa don va chi tiet hoa don:\n";
		cout << "  0: Ket thuc chuong trinh\n";
		cout << "Chuc nang ban chon: ";
		cin >> chucnang;
	} while (chucnang < '0' || chucnang> '4');
	return chucnang;
}

void Creart_List(PTRHD& First, dscthd& first_cthd)
{
	HoaDon hoadon;
	PTRHD Last = nullptr, p = nullptr;

	dscthd cuoicung = nullptr, d = nullptr;
	CT_HoaDon ct_hoadon;

	Clearlist(First);
	cout << "So hoa don (nhap 0 de thoat): "; cin >> hoadon.SoHD;

	while (hoadon.SoHD[0] != '0')
	{
		cout << "Ngay: "; cin >> hoadon.date.ngay;
		cout << "Thang: "; cin >> hoadon.date.thang;
		cout << "Nam: "; cin >> hoadon.date.nam;
		cout << "Loai: "; cin >> hoadon.Loai;

		if (hoadon.Loai[0] == 'N')
		{
			cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
			while (ct_hoadon.MAVT[0] != '0')
			{
				cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
				cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
				cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
				cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;

				p = new DS_HoaDon;
				p->hoadon = hoadon;
				if (First == NULL) First = p;
				else Last->next = p;
				Last = p;
				p->next = NULL;

				d = new DS_CT_HoaDon;
				d->ct_hoadon = ct_hoadon;
				if (first_cthd == NULL) first_cthd = d;
				else cuoicung->next = d;
				cuoicung = d;
				p->next = NULL;

				cout << "\nNhap ma vat tu moi:"; cin >> ct_hoadon.MAVT;
			}
		}

		if (hoadon.Loai[0] == 'X')
		{
			cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
			while (ct_hoadon.MAVT[0] != '0')
			{
				cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
				cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
				cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
				cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;

				p = new DS_HoaDon;
				p->hoadon = hoadon;
				if (First == NULL) First = p;
				else Last->next = p;
				Last = p;
				p->next = NULL;

				d = new DS_CT_HoaDon;
				d->ct_hoadon = ct_hoadon;
				if (first_cthd == NULL) first_cthd = d;
				else cuoicung->next = d;
				cuoicung = d;
				p->next = NULL;

				cout << "\nNhap ma vat tu moi(nhap 0 de thoat):"; cin >> ct_hoadon.MAVT;
			}
		}

			


			cout << "\nSo hoa don moi (nhap 0 de thoat): "; cin >> hoadon.SoHD;
	}


}


void demoPhu()
{
	PTRHD First, Last = nullptr;
	HoaDon hoadon;
	dscthd dautien, cuoicung = nullptr;
	CT_HoaDon ct_hoadon;

	int vitri , ct;
	char chucnang;
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
			cout << "Nhap vi tri muon them hoa don(nhap 0 de thoat): "; cin >> vitri;
			p = nodepointer(First, vitri - 1);
			d = nodepointer(dautien, vitri - 1);

			while (vitri != 0)
			{
				if (vitri < 0 || p == NULL)
				{
					cout << "Vi tri khong hop le";
					system("pause");
					cout << "Nhap vi tri muon them hoa don(nhap 0 de thoat): "; cin >> vitri;
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
						while (ct_hoadon.MAVT[0] != '0')
						{
							cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
							cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
							cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
							cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;

							if (vitri == 1)
							{
								Insert_First(First, hoadon);
								Insert_First(dautien, ct_hoadon);
							}
							else
							{
								Insert_after_p(p, hoadon);
								Insert_after_d(d, ct_hoadon);
							}

							cout << "\nNhap ma vat tu moi:"; cin >> ct_hoadon.MAVT;
						}
					}
					if (hoadon.Loai[0] == 'X')
					{
						cout << "Nhap ma vat tu: "; cin >> ct_hoadon.MAVT;
						while (ct_hoadon.MAVT[0] != '0')
						{
							cout << "Nhap so luong: "; cin >> ct_hoadon.Soluong;
							cout << "Nhap don gia: "; cin >> ct_hoadon.Dongia;
							cout << "Nhap %VAT: "; cin >> ct_hoadon.VAT;
							cout << "Nhap trang thai ( 1: khach mua, 0: khach da tra hang) : "; cin >> ct_hoadon.TrangThai;

							if (vitri == 1)
							{
								Insert_First(First, hoadon);
								Insert_First(dautien, ct_hoadon);
							}
							else
							{
								Insert_after_p(p, hoadon);
								Insert_after_d(d, ct_hoadon);
							}

							cout << "\nNhap ma vat tu moi:"; cin >> ct_hoadon.MAVT;
						}
					}
					

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
		case '4':
		{
			cout << "Nhap vi tri hoa don muon hieu chinh"; cin >> vitri;
			p = nodepointer(First, vitri - 1);
			if (vitri < 0 || p == NULL)
			{
				cout << "Vi tri khong hop le";
				system("pause");
			}
			else
			{
				cout << "So hoa don moi: "; cin >> hoadon.SoHD;
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
					Insert_after_p(p, hoadon);
					Insert_after_d(d, ct_hoadon);
				}
			}
			break;
		}
		}
	} while (chucnang != '0');
	Clearlist(dautien);
	Clearlist(First);
	//return 0;
}
