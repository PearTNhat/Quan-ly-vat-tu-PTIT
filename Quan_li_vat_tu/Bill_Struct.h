#pragma once
#include"Header.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <ctype.h>
#undef max
#include <limits> // thêm thư viện này để sử dụng numeric_limits
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

		return false;
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
typedef DS_CT_HoaDon* PTRCT;


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
	DS_CT_HoaDon* dscthd;
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
	DS_CT_HoaDon* dscthd;
};
typedef DS_HoaDon* PTRHD;

void NhapDSHoaDon(DS_HoaDon*& ds_hd)
{
	// Khởi tạo danh sách liên kết đơn DS_HoaDon
	ds_hd = new DS_HoaDon;
	PTRHD p = ds_hd;
	p->next = nullptr;

	// Nhập thông tin hóa đơn
	cout << "Nhap so hoa don: ";
	cin.ignore();
	cin.getline(p->hoadon.SoHD, 21);

	while (strcmp(p->hoadon.SoHD,"0") != 0)
	{

		cout << "Nhap ngay: "; cin >> p->hoadon.date.ngay;
		cout << "Nhap thang: "; cin >> p->hoadon.date.thang;
		cout << "Nhap nam: "; cin >> p->hoadon.date.nam;
		cout << "Nhap loai: "; 
		cin.ignore();
		cin.getline(p->hoadon.Loai, 2);

		// Khởi tạo danh sách liên kết đơn DS_CT_HoaDon
		p->dscthd = new DS_CT_HoaDon;
		PTRCT q = p->dscthd;
		q->next = nullptr;

		//nhap thong tin ct_hoadon
		cout << "Nhap ma vat tu: ";
		//cin.ignore();
		cin.getline(q->ct_hoadon.MAVT, 11);

		while (strcmp(q->ct_hoadon.MAVT,"0")!= 0)
		{
			cout << "Nhap so luong: ";
			cin >> q->ct_hoadon.Soluong;
			cout << "Nhap don gia: ";
			cin >> q->ct_hoadon.Dongia;
			cout << "Nhap VAT: ";
			cin >> q->ct_hoadon.VAT;
			cout << "Nhap trang thai: ";
			cin >> q->ct_hoadon.TrangThai;
			
			

			// Tạo một node mới của danh sách liên kết đơn DS_CT_HoaDon
			q->next = new DS_CT_HoaDon;
			q = q->next;
			q->next = nullptr;

			//nhap thong tin ct_hoadon tiep theo
			cout << "Nhap ma vat tu (nhap 0 de dung lai): ";
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.ignore();
			cin.getline(q->ct_hoadon.MAVT, 11);

		}

		// Tạo một node mới của danh sách liên kết đơn DS_HoaDon
		p->next = new DS_HoaDon;
		p = p->next;
		p->next = nullptr;

		// Nhập thông tin hóa đơn tiếp theo
		cout << "Nhap so hoa don (nhap 0 de dung lai): ";
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.getline(p->hoadon.SoHD, 21);
	}
}

void XuatDSHoaDon(PTRHD ds) {
	if (ds == NULL) {
		cout << "Danh sach rong!" << endl;
		return;
	}
	PTRHD p = ds;
	while (p != NULL) {
		if (p->next == NULL) break;
		cout << "So hoa don: " << p->hoadon.SoHD << endl;
		cout << "Ngay lap: " << p->hoadon.date.ngay << "/"
			                 << p->hoadon.date.thang << "/"
			                 << p->hoadon.date.nam << endl;
		cout << "Loai hoa don: " << p->hoadon.Loai << endl;
		cout << "Danh sach chi tiet hoa don: " << endl;
		if (p->dscthd == NULL) {
			cout << "\tDanh sach chi tiet hoa don rong!" << endl;
		}
		else {
			PTRCT q = p->dscthd;
			while (q != NULL) {
				if (q->next == NULL) break;
				cout << "\tMa vat tu: " << q->ct_hoadon.MAVT << endl;
				cout << "\tSo luong: " << q->ct_hoadon.Soluong << endl;
				cout << "\tDon gia: " << q->ct_hoadon.Dongia << endl;
				cout << "\tVAT: " << q->ct_hoadon.VAT << endl;
				cout << "\tTrang thai: " << (q->ct_hoadon.TrangThai ? "Khach mua" : "Khach tra") << endl << endl;
				q = q->next;
			}
		}
		p = p->next;
	}
}

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
	p->dscthd = nullptr;
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

//them vao sau cung hoadon
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

void demoPhu()
{
	char chucnang;
	PTRHD First;
	Initialize(First);
	do 
	{
		chucnang = menu();
		switch (chucnang)
		{
		case'1':
		{
			system("cls");
			NhapDSHoaDon(First);
			break;
		}
		case'3':
		{
			system("cls");
			XuatDSHoaDon(First);
			system("pause");
			break;
		}
		}
	} while (chucnang != '0');

	Clearlist(First);
	//return 0;
}
