#pragma once
#include"Header.h"
struct Date {
	int ngay;
	int thang;
	int nam;
};
struct CT_HoaDon
{
	char MAVT[11];
	int Soluong;
	int Dongia;
	float VAT;
	int TrangThai;
};

struct HoaDon
{
	char SoHD[21];
	Date date;
	char Loai[2];
};

struct DS_HoaDon
{
	HoaDon hoadon;
	DS_HoaDon* next;
};

struct DS_CTHoaDon
{
	CT_HoaDon ct_hoadon;
	DS_CTHoaDon* next;
};