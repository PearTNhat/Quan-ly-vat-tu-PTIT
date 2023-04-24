#pragma once
#include "Header.h"
#include "Constant.h"
#include "Bill_Struct.h"
#define MAX_DATA_CRUD 10
bool g_page = false, sf_page = false, b_page = false, ss_page = false, out_table = false,X_page = false;
struct view_page {
	int current = 1;
	int page = 1;
};
struct dataCRUD {
	string key="";
	int l;
	int t;
	int r;
	int b;
};
struct check_CURD {
	dataCRUD data[MAX_DATA_CRUD];
	int n=0; 
};
struct arrString {
	string s[100];
	int length = 0;
};
//
string trim(string& s);
void warning_msg(string text, int l, int t, int bg, int color, int font = f_medium);
void split(string s, arrString& arrS);
bool checkLowcase(char s);
//
bool ktVT(int l, int t, int r, int b, int x, int y) {
	/*cout << l << " " << x << " " << r << "|" << t << " " << y << " " << b << " ";*/
	if (x <= r && x >= l && y >= t && y <= b) return true;
	return false;
}
void text_box(int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8, int bg = XANH_DUONG_NHAT, int tColor = COLOR(0, 0, 0), bool printHD = false, int cBoder = 0) {
	setcolor(cBoder);
	setfillstyle(1, bg);
	settextstyle(font, 0, f_size);
	if (printHD) bar(l, t, r, b);
	else bar3d(l, t, r, b, 0, 0);
	setcolor(tColor);
	setbkcolor(bg);
	outtextxy(l + d_l, t + d_t, s);
}

void text_box_no_border(int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8, int bg = 11, int tColor = 0) {
	setcolor(tColor);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar(l, t, r, b);
	setbkcolor(bg);
	outtextxy(l + d_l, t + d_t, s);
}

void createHeader(char x[][maxTHeader]) {
	setfillstyle(1, HEADER_BACKGROUND);
	setcolor(HEADER_TEXT_COLOR);
	bar3d(-1, 0, 1200, 60, 0, 0);

	text_box(20, 10, 230, 50, x[0], f_medium, 3, 10, 56);
	text_box(300, 10, 500, 50, x[1], f_medium, 3, 10, 43);
	text_box(600, 10, 800, 50, x[2], f_medium, 3, 10, 35);
	text_box(900, 10, 1100, 50, x[3], f_medium, 3, 10, 45);
	text_box(1130, 10, 1180, 50, (char*)"X", f_medium, 4, 5, 14,LIGHTRED);
}
void highlight_box(int l, int t, int r, int b, char s[], int font, int f_size, int kct, int kcl, int bg = HIGHLIGHT_BACKGROUND, int color = 0) {
	setcolor(0);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar3d(l, t, r, b, 0, 0);
	setbkcolor(bg);
	setcolor(color);
	outtextxy(l + kcl, t + kct, s);
}
void writeText(int x, int y, char text[], int size = 1, int tColor = 0, int font = f_small, int bg = bk_screen) {
	setcolor(tColor);
	setbkcolor(bg);
	settextstyle(font, 0, size);
	outtextxy(x, y, text);
}
void delete_after_header() {
	setfillstyle(1, bk_screen);
	bar(0, 60, 1200, 900);
}
void page_transition(view_page& view_page, bool printHD = false) {
	int l_arrow_l = 495, t_arrow_l = 565, r_arrow_l = 530, b_arrow_l = 600;
	int l_arrow_r = 650, t_arrow_r = 565, r_arrow_r = 685, b_arrow_r = 600;
	string s = to_string(view_page.current) + " / " + to_string(view_page.page);
	char num_p[10];
	strcpy_s(num_p, s.c_str());
	if (printHD)
		setbkcolor(15);
	else setbkcolor(bk_screen);
	settextstyle(f_small, 0, 2);
	if (printHD) setcolor(0);
	else setcolor(15);
	outtextxy(575, 570, num_p);
	char arrow_left[] = "<";
	char arrow_right[] = ">";
	if (view_page.page == 1) {

	}
	else if (view_page.current == 1) {
		//>
		if (printHD) text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10, COLOR(221, 221, 221), 0, 1);
		else text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10);

	}
	else if (view_page.current == view_page.page) {
		//<
		if (printHD) text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10, COLOR(221, 221, 221), 0, 1);
		else text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10);
	}
	else {
		//<  >
		if (printHD) {
			text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10, COLOR(221, 221, 221), 0, 1);
			text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10, COLOR(221, 221, 221), 0, 1);
		}
		else {
			text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10);
			text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10);
		}
		

	}
}
void next_page(int l, int t, int r, int b, view_page& check_page, bool printHD = false, int _delay = 200, int d_t = 5, int d_l = 10, int bg = HEADER_BACKGROUND, int color = 10) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current >= total_page) {
		cout << "Het";
	}
	else {
		check_page.current++;
		if (printHD) highlight_box(l, t, r, b, (char*)">", f_medium, 3, d_t, d_l, COLOR(51, 51, 51), COLOR(221, 221 , 221));
		else highlight_box(l, t, r, b, (char*)">", f_medium, 3, d_t, d_l, bg, color);
		delay(_delay);
	}
}
void prev_page(int l, int t, int r, int b, view_page& check_page, bool printHD = false, int _delay = 200, int d_t = 5, int d_l = 10, int bg = HEADER_BACKGROUND, int color = 10) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current <= 1) {
		cout << "Het";
	}
	else {
		check_page.current--;
		if (printHD) highlight_box(l, t, r, b, (char*)"<", f_medium, 3, d_t, d_l, COLOR(51, 51, 51), COLOR(221, 221, 221));
		else highlight_box(l, t, r, b, (char*)"<", f_medium, 3, d_t, d_l, bg, color);
		delay(_delay);
	}
}
void warning_msg(string text,int l,int t,int bg,int color,int font) {
	char m[255];
	strcpy_s(m, text.c_str());
	writeText(l, t, m, 1, color, f_medium, bg);
}
bool announce_board( int x,int y,int kcl = 0, int kct = 0, string value = "",string type = "noClose", int bg = COLOR(232, 246, 250)) { // 200 //400 

	setfillstyle(1, bg);
	setcolor(I_ERROR_COLOR);
	bar3d(420, 210, 780, 410, 0, 0);
	string temp_value;
	temp_value = "";
	int minus =0;
	if (value.length()>=27 && value[27] != ' '  ) {
		minus = 27;
		while (value[minus]!=' ') {
			minus--;
		}
		minus = 27 - minus;
	}
	int text_length = value.length() <= 27 ? value.length() : (27-minus);
	for (int i = 0; i < text_length; i++)
	{
		temp_value += value[i];
	}
	writeText(450 + kcl, 280 + kct, (char*)temp_value.c_str(), 1, 0, f_medium, bg);
	if(value.length() > 26) {
		temp_value = "";
		for (int i = 27; i < value.length(); i++)
		{
			temp_value += value[i];
		}
		writeText(450 + kcl, 300 + kct, (char*)trim(temp_value).c_str(), 1, 0, f_medium, bg);
	}
	if (type!= "noClose") {
		text_box(500, 345, 570, 370, (char*)"Co", f_medium, 1, 5, 20, bg, 0);
		text_box(610, 345, 680, 370, (char*)"Khong", f_medium, 1, 5, 6, bg, 0);
		text_box(750, 210, 780, 240, (char*)"X", f_medium, 1, 7, 9, COLOR(255, 97, 100),0, I_ERROR_COLOR);
		while (1) {
			if (ismouseclick(WM_LBUTTONDOWN)) {
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (ktVT(500, 345, 570, 370, x,y)) {
					x = NULL;
					y = NULL;

					text_box(500, 345, 570, 370, (char*)"Co", f_medium, 1, 5, 20, XANH_LA_CAY, 0);
					delay(200);
					return 1;
				}
				if (ktVT(610, 345, 680, 370, x, y)) {
					text_box(610, 345, 680, 370, (char*)"Khong", f_medium, 1, 5, 6, XANH_LA_CAY, 0);
					delay(200);
					x = NULL;
					y = NULL;
					return 0;
				}
				if ( ktVT(750, 210, 780, 240, x, y)) {
					x = NULL;
					y = NULL;
					text_box(750, 210, 780, 240, (char*)"X", f_medium, 1, 7, 9, COLOR(250, 0, 4), 0,I_ERROR_COLOR);
					delay(200);
					return 0;
				}
			}
		}
	}

	return 1;
}
string trim(string& s) {
	for (int i = 0; i < s.length(); i++)
	{
		if (s[0] == ' ') {
			s.erase(0, 1);
		}
		if (s.length() > 0 && s[s.length() - 1] == ' ') {
			s.pop_back();
		}
	}
	return s;
}

void split(string s, arrString& arrS) {
	string temp = "";
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ') {
			arrS.s[arrS.length++] = temp;
			temp = "";
			continue;
		}
		temp += s[i];
	}
	arrS.s[arrS.length++] = temp;
}
bool checkLowcase(char s) {
	if (s >= 'a' && s <= 's') return true;
	return false;
}

std::string formatNumber(int num) {
	std::ostringstream ss;
	ss << num;
	std::string numStr = ss.str();

	int numDigits = numStr.size();
	int numCommas = (numDigits - 1) / 3;

	for (int i = 1; i <= numCommas; i++) {
		int commaPos = numDigits - i * 3;
		numStr.insert(commaPos, ",");
	}

	return numStr;
}

struct DS_info {
	HoaDon hoadon;
	char hoTenNV[40];
	char maNV[11];
	DS_info* next;
};

DS_info* taoNodeInfo(char hoten[40], char maNV[11], HoaDon hd) {
	DS_info* phanTuMoi = new DS_info();
	phanTuMoi->hoadon = hd;
	strcpy_s(phanTuMoi->hoTenNV, hoten);
	strcpy_s(phanTuMoi->maNV, maNV);
	return phanTuMoi;
}

void insertLast_DS_info(DS_info*& first, char hoten[40], char maNV[11], HoaDon hd) {
	DS_info* temp = taoNodeInfo(hoten, maNV, hd);
	if (first == NULL) first = temp;
	else {
		DS_info* nodeIt = first;
		while (nodeIt->next != NULL) nodeIt = nodeIt->next;
		nodeIt->next = temp;
	}
}

DS_info* getIndexDS_InfoTable(DS_info* first, int index) {
	int i = 0;
	DS_info* nodeIt = first;
	while (nodeIt != NULL) {
		if (i++ == index) return nodeIt;
		nodeIt = nodeIt->next;
	}
	return NULL;
}

int getNumOfInfo(DS_info* First) {
	int count = 0;
	DS_info* temp = First;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	temp = NULL;
	delete temp;
	return count;
}

void removeRedundantSpaces(string& sentence) {
	string result = "";

	bool lastWasSpace = true; // Start with a space to handle leading spaces
	for (char c : sentence) {
		if (c == ' ') {
			if (!lastWasSpace) {
				result += c;
			}
			lastWasSpace = true;
		}
		else {
			result += c;
			lastWasSpace = false;
		}
	}

	sentence = result;
}

string convertToText(int number) {
	string units[] = { "", "mot", "hai", "ba", "bon", "nam", "sau", "bay", "tam", "chin" };
	string tens[] = { "", "muoi", "hai muoi", "ba muoi", "bon muoi", "nam muoi", "sau muoi", "bay muoi", "tam muoi", "chin muoi" };
	string suffixes[] = { "", "nghin", "trieu" };
	string result = "";

	// Handle zero case
	if (number == 0) {
		return "Khong dong";
	}

	// Split the number into groups of three digits and process them separately
	int groupCount = 0;
	while (number > 0) {
		int group = number % 1000;
		number /= 1000;
		string groupText = "";

		// Convert the hundreds place to text
		int hundreds = group / 100;
		if (hundreds > 0) {
			groupText += units[hundreds] + " tram";
		}

		// Convert the tens and units places to text
		int tensAndUnits = group % 100;
		if (tensAndUnits > 0) {
			if (tensAndUnits < 10) {
				if (groupCount == 2) groupText += " " + units[tensAndUnits];
				else groupText += " linh " + units[tensAndUnits];
			}
			else if (tensAndUnits < 20) {
				groupText += " muoi";
				if (tensAndUnits == 11) {
					groupText += " mot";
				}
				else if (tensAndUnits == 15) {
					groupText += " lam";
				}
				else {
					groupText += " " + units[tensAndUnits % 10];
				}
			}
			else {
				groupText += " " + tens[tensAndUnits / 10];
				if (tensAndUnits % 10 > 0) {
					groupText += " " + units[tensAndUnits % 10];
				}
			}
		}

		// Add the suffix to the group text if it's not empty
		if (!groupText.empty()) {
			groupText += " " + suffixes[groupCount];
		}

		// Combine the group text with the overall result
		result = groupText + " " + result;
		groupCount++;
	}

	result += " dong";
	removeRedundantSpaces(result);
	// Capitalize the first letter of the result
	result[0] = toupper(result[0]);

	return result;
}
//void staff_table(
//	char sf_table_header[][20],
//	DS_NhanVien ds, // day la danh sach cac phan tu chon kd_lieu cho phu hop
//	char curd_o[][20], // "them sua xoa" // k can co the xoa
//	view_page& view_page,
//	check_CURD edit[],//// k can co the xoa
//	check_CURD _delete[],// k can co the xoa
//	int num_rows,
//	string value = ""
//) {
//	delete_after_header();
//	create_sf_header(value);
//	// tnh so page co trong trang
//	setcolor(0);
//	int n = ds.length;
//	int page = n / num_rows;
//	int du = n % num_rows;
//	view_page.page = du ? page + 1 : page;
//	int max_page = n > (num_rows * view_page.current) ? (num_rows * view_page.current) : n;
//	// reder page
//	int i = num_rows * (view_page.current - 1);
//	//header
//	int bar_top = 120, bar_bottom = 150;
//	int text_top = 125;
//	setfillstyle(1, 6);
//	setbkcolor(6);
//	settextstyle(f_small, 0, 1);
//	bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
//	outtextxy(55, text_top, (char*)"STT");
//	outtextxy(95, text_top, sf_table_header[0]);
//	outtextxy(230, text_top, sf_table_header[1]);
//	outtextxy(650, text_top, sf_table_header[2]);
//	outtextxy(900, text_top, sf_table_header[3]);
//	setfillstyle(1, 15);
//	setbkcolor(15);
//	int d = 0;//delete
//	int e = 0;//edit
//	for (; i < max_page; i++)
//	{
//		if (i % num_rows == 0) {
//			bar_top += 30;
//			bar_bottom += 40;
//			text_top += 35;
//		}
//		else {
//			bar_top += 40;
//			bar_bottom += 40;
//			text_top += 40;
//		}
//		// Neu k su dung thi xoa tu day xuong
//		//vi tri edit
//		edit[e].l = 900;
//		edit[e].t = text_top;
//		edit[e].r = 978;
//		edit[e].b = text_top + 22;
//		e++;
//		// vi tri delete
//		_delete[d].l = 990;
//		_delete[d].t = text_top;
//		_delete[d].r = 1038;
//		_delete[d].b = text_top + 22;
//		d++;
//		// --------------------------------- xuong day
//
//		// row
//		setcolor(0);
//		bar3d(50, bar_top, 1150, bar_bottom, 0, 0);
//		// title header
//		char stt[10];
//		strcpy_s(stt, to_string(i + 1).c_str());
//		writeText(55, text_top, stt, 1, 0, 3, 15);
//		writeText(95, text_top, ds.nhan_vien[i]->maNV, 1, 0, 3, 15);
//		cout << ds.nhan_vien[i]->ho << endl;
//		string fullName = ds.nhan_vien[i]->ho;
//
//		fullName += " ";
//		fullName += ds.nhan_vien[i]->ten;
//
//		char ten[30];
//		strcpy_s(ten, fullName.c_str());
//		cout << ten << endl;
//		writeText(230, text_top, ten, 1, 0, 3, 15);
//		writeText(650, text_top, ds.nhan_vien[i]->phai, 1, 0, 3, 15);
//
//		//------------- k can co the xoa
//		text_box(900, text_top, 978, text_top + 22, curd_o[0], f_small, 1, 1);
//		text_box(995, text_top, 1038, text_top + 22, curd_o[1], f_small, 1, 1);
//		setfillstyle(1, 15);
//		setbkcolor(15);
//	}
//	//------------- k can cos the xoa
//	_delete[0].n = d;
//	edit[0].n = e;
//
//	// < >
//	page_transition(view_page);
//
//}