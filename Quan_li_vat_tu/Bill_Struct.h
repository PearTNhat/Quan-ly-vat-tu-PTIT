#pragma once
#include"Header.h"
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <ctype.h>
#include <string>

#define MAX_HD 500
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

	/*bool operator==(CT_HoaDon& other)
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
	}*/
};

struct DS_CT_HoaDon
{
	CT_HoaDon ct_hoadon;
	DS_CT_HoaDon* next;
};
typedef DS_CT_HoaDon* dscthd;

// Initialize khoi dong danh sach lien ket chi tiet hoadon
void Initialize_CTHD(dscthd& first_cthd)
{
	first_cthd = NULL;
}

/* Tac vu nodepointer: xac dinh con tro cua nut i trong danh sach lien ket chi tiet hoadon
   (i = 2, ...) */
dscthd nodepointer_CTHD(dscthd& first_cthd, int i)
{
	dscthd d;
	int vitri = 1;
	d = first_cthd;
	while (d != NULL && vitri < i)
	{
		d = d->next;
		vitri++;
	}
	return(d);
}

// Tac vu position: xac dinh vi tri cua nut p trong danh sach lien ket chi tiet hoadon
int position_CTHD(dscthd first_cthd, dscthd d)
{
	int vitri = 1;
	dscthd q = first_cthd;
	while (q != NULL && q != d)
	{
		q = q->next; 	vitri++;
	}
	if (q == NULL)     return (-1);
	return(vitri);
}

// Newnode chi tiet hoadon
dscthd Newnode_CTHD(CT_HoaDon x = {})
{
	dscthd d = new DS_CT_HoaDon;
	d->ct_hoadon = x;
	d->next = NULL;
	/*d->dscthd = nullptr;*/
	return d;
}
dscthd d = Newnode_CTHD();

// them vao dau chi tiet hoadon
void Insert_First_CTHD(dscthd& first_cthd, CT_HoaDon x)
{
	dscthd d = Newnode_CTHD(x);
	d->next = first_cthd;
	first_cthd = d;
}

//them vao sau cung chi tiet hoadon
void Insert_last_CTHD(dscthd& d, CT_HoaDon x)
{
	dscthd q = d;
	if (d == NULL) {
		Insert_First_CTHD(d, x);
	}
	else
	{
		while (q->next != NULL) {
			q = q->next;
		}
		dscthd temp = Newnode_CTHD(x);
		q->next = temp;
	}
}

//them vao sau d cua chi tiet hoadon
void Insert_after_CTHD(dscthd d, CT_HoaDon x)
{
	dscthd q;
	if (d == NULL)
		Insert_First_CTHD(d, x);
	else
	{
		q = new DS_CT_HoaDon;
		q->ct_hoadon = x;
		q->next = d->next;
		d->next = q;
	}

}

// kiem tra rong chi tiet hoadon
int Empty_CTHD(dscthd first_cthd)
{
	return(first_cthd == NULL);
}

// xoa dau chi tiet hoadon
int Delete_First_CTHD(dscthd& first_cthd)
{
	dscthd p;
	if (Empty_CTHD(first_cthd))
		return 0;
	p = first_cthd;
	first_cthd = p->next;
	delete p;
	return 1;
}

// xoa sau chi tiet hoa don
int Delete_after_CTHD(dscthd d)
{
	dscthd q;
	if ((d == NULL) || (d->next == NULL))
		return 0;
	q = d->next;
	d->next = q->next;
	delete q;
	return 1;
}

// xoa danh sach lien ket chi tiet hoadon
void Clearlist_CTHD(dscthd& first_cthd)
{
	//PTRHD p;
	while (first_cthd != NULL) Delete_First_CTHD(first_cthd);
}

CT_HoaDon getNodeByMaVT(dscthd head, char c_mavattu) {
	if (head == nullptr) {
		return CT_HoaDon();
	}

	dscthd current = head;
	while (current != nullptr) {
		if (strcmp(current->ct_hoadon.MAVT, (char*)c_mavattu) == 0) {
			return current->ct_hoadon;
		}
		current = current->next;
	}

	return CT_HoaDon();
}

CT_HoaDon getNodeByvitri(dscthd head, int i) {
	if (head == nullptr) {
		return CT_HoaDon();
	}

	dscthd current = head;
	int count = 0;
	while (current != nullptr && count != i) {
		current = current->next;
		count++;
	}

	if (count == i && current != nullptr) {
		return current->ct_hoadon;
	}

	return CT_HoaDon();
}

void xoaNodeByvitri(dscthd& head, int i) {
	if (head == nullptr) {
		return;
	}

	if (i == 0) {
		dscthd temp = head;
		head = head->next;
		delete temp;
		return;
	}

	dscthd current = head;
	dscthd previous = nullptr;
	int count = 0;

	while (current != nullptr && count != i) {
		previous = current;
		current = current->next;
		count++;
	}

	if (count == i && current != nullptr) {
		previous->next = current->next;
		delete current;
		return;
	}
}

void themNodeByvitri(dscthd& head, int i, CT_HoaDon ct_hoadon) {
	// Tạo một node mới
	dscthd new_node = new DS_CT_HoaDon;
	new_node->ct_hoadon = ct_hoadon;
	new_node->next = nullptr;

	if (head == nullptr && i == 0) {
		// Trường hợp danh sách rỗng, thêm node mới vào đầu danh sách
		head = new_node;
		return;
	}

	if (i == 0) {
		// Thêm node mới vào đầu danh sách
		new_node->next = head;
		head = new_node;
		return;
	}

	dscthd current = head;
	dscthd previous = nullptr;
	int count = 0;

	while (current != nullptr && count != i) {
		previous = current;
		current = current->next;
		count++;
	}

	if (count == i) {
		// Thêm node mới vào vị trí thứ i
		previous->next = new_node;
		new_node->next = current;
		return;
	}

	// Nếu không tìm thấy vị trí cần thêm node mới
	delete new_node; // Giải phóng bộ nhớ đã cấp phát cho node mới
}


dscthd getNodeMaVTdscthd(dscthd head, string c_mavattu) {
	if (head == nullptr) {
		return nullptr;
	}

	dscthd current = head;
	while (current != nullptr) {
		if (current->ct_hoadon.MAVT == c_mavattu) {
			return current;
		}
		current = current->next;
	}

	return nullptr;
}

void xoaNodeMaVTdscthd(dscthd& first, string c_mavattu) {
	// Tìm node cần xóa
	dscthd nodexoa = getNodeMaVTdscthd(first, c_mavattu);

	// Nếu không tìm thấy node cần xóa
	if (nodexoa == nullptr) {
		cout << "Khong tim thay node can xoa" << endl;
		return;
	}

	// Nếu node cần xóa là head
	if (nodexoa == first) {
		first = first->next;
		delete nodexoa;
		return;
	}

	// Tìm node trước node cần xóa
	dscthd prev_node = first;
	while (prev_node->next != nodexoa) {
		prev_node = prev_node->next;
	}

	// Xóa node cần xóa
	prev_node->next = nodexoa->next;
	delete nodexoa;
}

dscthd getNodeByIndexdscthd(dscthd head, int index) {
	if (head == nullptr) {
		return nullptr;
	}
	dscthd current = head;
	int count = 0;
	while (current != nullptr) {
		if (count == index) {
			return current;
		}
		count++;
		current = current->next;
	}
	return nullptr;
}

dscthd getNodesByTrangThai(dscthd head, bool trangThai) {
	dscthd resultHead = nullptr; // Khởi tạo danh sách kết quả rỗng
	dscthd current = head;
	while (current != nullptr) {
		if (current->ct_hoadon.TrangThai == trangThai) {
			dscthd newNode = new DS_CT_HoaDon; // Tạo một nút mới để lưu trữ
			newNode->ct_hoadon = current->ct_hoadon; // Sao chép giá trị từ nút hiện tại
			newNode->next = nullptr;
			Insert_last_CTHD(resultHead, newNode->ct_hoadon); // Thêm nút mới vào danh sách kết quả
		}
		current = current->next;
	}
	return resultHead; // Trả về con trỏ đến đầu danh sách kết quả
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
	dscthd first_cthd;
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
void Initialize_HD(PTRHD& First)
{
	First = NULL;
}

/* Tac vu nodepointer: xac dinh con tro cua nut i trong danh sach lien ket hoadon
   (i = 2, ...) */
PTRHD nodepointer_HD(PTRHD First, int i)
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
int position_HD(PTRHD First, PTRHD p)
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
PTRHD Newnode_HD(HoaDon x = {})
{
	PTRHD p = new DS_HoaDon;
	p->hoadon = x;
	p->next = NULL;
	/*p->dscthd = nullptr;*/
	return p;
}
PTRHD p = Newnode_HD();

PTRHD getLastNodeHD(PTRHD first) {
	PTRHD nodeIt = first;
	while (nodeIt->next != NULL) nodeIt = nodeIt->next;
	return nodeIt;
}

// them vao dau hoadon
void Insert_First_HD(PTRHD& First, HoaDon x)
{
	PTRHD p = Newnode_HD(x);
	p->next = First;
	First = p;
}

//them vao sau cung hoadon
void Insert_last_HD(PTRHD& p, HoaDon x)
{
	PTRHD q = p;
	if (p == NULL) {
		Insert_First_HD(p, x);
	}
	else
	{
		while (q->next != NULL) {
			q = q->next;
		}
		PTRHD temp = Newnode_HD(x);
		q->next = temp;
	}
}

//them vao sau p cua hoadon
void Insert_after_HD(PTRHD p, HoaDon x)
{
	PTRHD q;
	if (p == NULL)
		Insert_First_HD(p, x);
	else
	{
		q = new DS_HoaDon;
		q->hoadon = x;
		q->next = p->next;
		p->next = q;
	}

}

//tim thong tin hoadon 
PTRHD Search_info_HD(PTRHD First, HoaDon x)
{
	PTRHD p;
	for (p = First; p != NULL; p = p->next)
	{
		if (p->hoadon.SoHD == x.SoHD) return p;

	}
	return NULL;
}

// kiem tra rong hoadon
int Empty_HD(PTRHD First)
{
	return(First == NULL);
}

// xoa dau hoadon
int Delete_First_HD(PTRHD& First)
{
	PTRHD p;
	if (Empty_HD(First))
		return 0;
	p = First;
	First = p->next;
	delete p;
	return 1;
}

// xoa sau (hoa don)
int Delete_after_HD(PTRHD p)
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
int Delete_Info_HD(PTRHD& First, HoaDon x)
{
	PTRHD p = First;
	if (First = NULL)
		return 0;
	if (First->hoadon == x)
	{
		Delete_First_HD(First);return 1;
	}

	for (p = First;p->next != NULL && p->next->hoadon != x;p = p->next);
	if (p->next != NULL)
	{
		Delete_after_HD(p); return 1;
	}
	return 0;
}

// xoa tat ca theo thong tin ( hoadon)
int Delete_ALl_Info_HD(PTRHD& First, HoaDon x)
{
	int count = 0;
	if (First == NULL) return 0;
	for (PTRHD p = First; p->next != NULL;)
	{
		if (p->next->hoadon == x)
		{
			Delete_after_HD(p); count++;
		}
		else
			p = p->next;
	}
	if (First->hoadon == x)
	{
		Delete_First_HD(First); count++;
	}
	return count;
}

// xoa danh sach lien ket hoadon
void Clearlist_HD(PTRHD& First)
{
	//PTRHD p;
	while (First != NULL) Delete_First_HD(First);
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


int getNumOfCTHD(dscthd first_cthd) {
	int count = 0;
	dscthd temp = first_cthd;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	temp = NULL;
	delete temp;
	return count;
}

DS_HoaDon* getIndexBill(DS_HoaDon* first, int index) {
	int i = 0;
	DS_HoaDon* nodeIt = first;
	while (nodeIt != NULL) {
		if (i++ == index) return nodeIt;
		nodeIt = nodeIt->next;
	}
	return NULL;
}

DS_CT_HoaDon* getIndexCTHD(DS_CT_HoaDon* first, int index) {
	int i = 0;
	DS_CT_HoaDon* nodeIt = first;
	while (nodeIt != NULL) {
		if (i++ == index) return nodeIt;
		nodeIt = nodeIt->next;
	}
	return NULL;
}


