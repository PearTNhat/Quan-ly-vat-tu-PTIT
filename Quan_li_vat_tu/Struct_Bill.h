#pragma once
#include"Header.h"

struct Chitiethoadon
{
	char MAVT[11];
	int Soluong;
	int Dongia;
	int VAT;
	int TrangThai;
};

struct Hoadon
{
	char SoHD[21];
	char Ngaylaphoadon[10];
	char Loai[2];

};

struct Link_list_Hoadon
{
	Hoadon hoadon;
	Link_list_Hoadon* node;
};

struct Link_list_Chitiethd
{
	Chitiethoadon chitiethoadon;
	Link_list_Chitiethd* node;
};