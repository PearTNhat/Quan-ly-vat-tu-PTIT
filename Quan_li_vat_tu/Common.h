#pragma once
#include "Header.h"
#include "Constant.h"
#include "Bill_Struct.h"
#define MAX_DATA_CRUD 10
bool g_page = false, sf_page = false, b_page = false, ss_page = false, out_table = false, X_page = false;

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
	//cout << l << " " << x << " " << r << "|" << t << " " << y << " " << b << " ";
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

	text_box(20, 10, 220, 50, x[0], f_medium, 3, 10, 56);
	text_box(320, 10, 520, 50, x[1], f_medium, 3, 10, 43);
	text_box(620, 10, 820, 50, x[2], f_medium, 3, 10, 35);
	text_box(920, 10, 1120, 50, x[3], f_medium, 3, 10, 45);
	text_box(1140, 10, 1190, 50, (char*)"X", f_medium, 4, 5, 14,LIGHTRED);
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
string lowercase(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void deleteAllSpace (string &str) {
	for (int i = 0; i < str.length();)
	{	
		if(str[i]==' ') {
			str.erase(i,1);
			continue;
		}
		i++;
	}
}
bool checkLowcase(char s) {
	if (s >= 'a' && s <= 's') return true;
	return false;
}
int search_string(string str, string subStr) {
	trim(str);
	deleteAllSpace(str);
	str = lowercase(str);
	size_t pos = str.find(subStr);
	if (pos != string::npos) {
		return pos;
	}
	return -1;
}
int search_strict(string str, string subStr) {
	cout << str << "  " << subStr;
	if(str==subStr){
		return 1;
	}
	return -1;
}
std::string formatNumber(long long num) {
	std::ostringstream ss;
	ss << num;
	std::string numStr = ss.str();

	long long numDigits = numStr.size();
	long long numCommas = (numDigits - 1) / 3;

	for (long long i = 1; i <= numCommas; i++) {
		long long commaPos = numDigits - i * 3;
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

	bool lastWasSpace = true; 
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

string convertToText(long long number) {
	string units[] = { "", "mot", "hai", "ba", "bon", "nam", "sau", "bay", "tam", "chin" };
	string tens[] = { "", "muoi", "hai muoi", "ba muoi", "bon muoi", "nam muoi", "sau muoi", "bay muoi", "tam muoi", "chin muoi" };
	string suffixes[] = { "", "nghin", "trieu", "ty"};
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
				if (groupCount >= 2) groupText += " " + units[tensAndUnits];
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