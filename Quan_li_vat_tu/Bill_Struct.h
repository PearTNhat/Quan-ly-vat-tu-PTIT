#pragma once
#include"Header.h"
struct Date {
	int ngay;
	int thang;
	int nam;

	bool operator==(Date &other) {
		return this->ngay == other.ngay && this->thang == other.thang && this->nam == other.nam ? true : false;
	}
};
struct CT_HoaDon
{
	char MAVT[11];
	int Soluong;
	int Dongia;
	float VAT;
	int TrangThai;
};
//123

struct HoaDon
{
	char SoHD[21];
	Date date;
	char Loai[2];

	bool operator==(HoaDon &other) {
		if (strcmp(this->SoHD, other.SoHD) == 0 &&
			strcmp(this->Loai, other.Loai) == 0 &&
			this->date == other.date)
			return true; //test đi
		return false;
	}
};

// haizz

struct DS_HoaDon
{
	HoaDon hoadon;
	DS_HoaDon* next;
};
typedef DS_HoaDon* PTRHD;
PTRHD First = NULL;

//void Initialize(PTRHD  &First) 
//{
//	First = NULL;
//}

PTRHD Newnode(void) 
{
	PTRHD p = new DS_HoaDon;
	return p;
}
PTRHD p = Newnode();

void Insert_First(PTRHD &First, HoaDon x)
{
	PTRHD p;
	p = new DS_HoaDon;
	p->hoadon = x;
	p->next = First;
	First = p;
}

void Insert_after(PTRHD p, HoaDon x)
{
	PTRHD q;
	if (p == NULL)
		printf("khong them phan tu vao danh sach duoc");
	else
	{
		q = new DS_HoaDon;
		q->hoadon = x;
		q->next = p->next;
		p->next = q;
	}
}


PTRHD Search_info(PTRHD First, HoaDon x)
{
	PTRHD p;
	for (p = First; p != NULL; p = p->next)
		if (p->hoadon.SoHD == x.SoHD && p->hoadon.date == x.date  && p->hoadon.Loai == x.Loai  ) return p;
	return NULL;
}


struct DS_CTHoaDon
{
	CT_HoaDon ct_hoadon;
	DS_CTHoaDon* next;
};