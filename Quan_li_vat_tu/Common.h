#pragma once
#include "Header.h"
#include "Constant.h"

bool g_page = false, sf_page = false, b_page = false, ss_page = false;
struct view_page {
	int current = 1;
	int page = 1;
};
struct check_CURD {
	int l;
	int t;
	int r;
	int b;
	int n; // luu so luong can check // o vi tri so index = 0 //  
};

bool ktVT(int l, int t, int r, int b, int x, int y) {
	/*cout << l << " " << x << " " << r << "|" << t << " " << y << " " << b << " ";*/
	if (x <= r && x >= l && y >= t && y <= b) return true;
	return false;
}
void text_box (int l, int t, int r, int b, char s[], int font, int f_size, int d_t = 0, int d_l = 8,int bg=XANH_DUONG_NHAT, int tColor = 15) {
	setcolor(tColor);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar3d(l, t, r, b, 0, 0);
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
	bar3d(-1, 0, 1200, 60,0,0);
	
	text_box(50, 10, 250, 50, x[0], f_medium, 3, 10, 56);
	text_box(350, 10,550 , 50, x[1], f_medium, 3, 10, 43);
	text_box(650, 10, 850, 50, x[2], f_medium, 3, 10, 35);
	text_box(950, 10, 1150, 50, x[3], f_medium, 3, 10, 45);
}
void highlight_box(int l, int t, int r, int b, char s[], int font, int f_size,int kct, int kcl,int bg= HIGHLIGHT_BACKGROUND, int color=0) {
	setcolor(color);
	settextstyle(font, 0, f_size);
	setfillstyle(1, bg);
	bar3d(l, t, r, b, 0, 0);
	setbkcolor(bg);
	outtextxy(l + kcl, t + kct, s);
}
void writeText(int x, int y, char text[], int size=1,int tColor=0,int font = f_small,int bg=bk_screen) {
	setcolor(tColor);
	setbkcolor(bg);
	settextstyle(font, 0, size);
	outtextxy(x, y, text);
}
void delete_after_header() {
	setfillstyle(1, bk_screen);
	bar(0, 60, 1200, 900);
}
void page_transition(view_page& view_page) {
	int l_arrow_l = 495, t_arrow_l = 565, r_arrow_l = 530, b_arrow_l = 600;
	int l_arrow_r = 650, t_arrow_r = 565, r_arrow_r = 685, b_arrow_r = 600;
	
	string s = to_string(view_page.current) + " / " + to_string(view_page.page);
	char num_p[10];
	strcpy_s(num_p, s.c_str());
	setbkcolor(bk_screen);
	settextstyle(f_small, 0, 2);
	outtextxy(575, 570, num_p);
	char arrow_left[] = "<";
	char arrow_right[] = ">";
	if (view_page.current == 1) {
		//>
		text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5,10);

	}
	else if (view_page.current == view_page.page) {
		//<
		text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5,10);
	}
	else  {
		//<  >
		text_box(l_arrow_l, t_arrow_l, r_arrow_l, b_arrow_l, arrow_left, f_medium, 3, 5, 10);
		text_box(l_arrow_r, t_arrow_r, r_arrow_r, b_arrow_r, arrow_right, f_medium, 3, 5, 10);

	}
}
void next_page(int l, int t, int r, int b, view_page& check_page,int _delay=200 ,int d_t=5,int d_l=10 ,int bg = HEADER_BACKGROUND, int color = 10) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current >= total_page) {
		cout<<"K the next page";
	}
	else {
		check_page.current++;
		highlight_box(l, t, r, b, (char*)">", f_medium, 3, d_t, d_l,bg,color );
		delay(_delay);
	}
}
void prev_page(int l, int t, int r, int b, view_page& check_page, int _delay = 200,int d_t = 5, int d_l = 10,int bg = HEADER_BACKGROUND, int color = 10) {
	int current = check_page.current;
	int total_page = check_page.page;
	if (current <=1) {
		cout << "K the prev page";
	}
	else {
		check_page.current--;
		highlight_box(l, t, r, b, (char*)"<", f_medium, 3,d_t,d_l,bg,color);
		delay( _delay);
	}
}bool only_number(char x) {

	if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == 8 || x == 13) {
		return true;
	}
	return false;
}
bool only_letter(char x) {
	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x == 8 || x == 13 || x==' ') {
		return true;
	}
	return false;
}
bool decimal_number(char x) {

	if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == 8 || x == 13 || x == '.') {
		return true;
	}
	return false;
}
bool kt_KTu(char x) {
	if (x >= 'a' && x <= 'z') {
		return true;
	}
	if (x >= 'A' && x <= 'Z') {
		return true;
	}
	else if (x >= '0' && x <= '9') {
		return true;
	}
	else if (x == '/' || x == '\\' || x == 8 || x == 13 || x == ' ' || x == '.') {
		return true;
	}
	return false;
}
string input(
	int &x,int &y,
	int l, int t, int r, int b,
	int kcl, int kct,// can chinh vi tri input
	int e_kcl, int e_kct, int e_length = 50, // can chinh bao loi
	string value = "", int max_value = 255, int type = NULL,
	int i_bg = I_BG,
	int i_highlight = I_HIGHLIGHT,
	int i_color = I_COLOR,
	int i_error_color= I_ERROR_COLOR

	) {
	while (kbhit()) {
		getch();
	}
	bool key_enter = false;
	string input = value;
	input += "_";
	char result[255] = {""};
	if (input.length() != 0) {
		strcpy_s(result, input.c_str());
	}
	text_box(l, t, r, b, (char*)"", f_medium, 1, 0, 0, i_highlight, i_color); // vẽ khung input
	writeText(l + kcl, t + kct, result,1, i_color, f_medium, i_highlight); // chữ trong input
	while (!key_enter) {
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!ktVT(l, t, r, b, x, y)) {
				//---xoa canh bao
				setfillstyle(1, i_bg);
				bar(l + e_kcl, t + e_kct, r + e_length, b + 20);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				input.erase(input.end() - 1);
				strcpy_s(result, input.c_str());
				cout << "result:" << result << endl;
				// enter  xong vẫn để lại chữ
				setfillstyle(1, 15);
				bar3d(l, t, r, b, 0, 0);
				writeText(l + kcl, t + kct, result, 1, i_color, f_medium, 15);
				break;

			}
		}
		if (kbhit()) {
			char key = (char)getch(); // nhận key từ bàn phím
			bool check_key;
			cout << "key "<<endl;
			if (type == 1) {
				check_key = only_number(key);
			}
			else if (type == 2) {
				check_key = decimal_number(key);
			}
			else if (type == 3) {
				check_key = only_letter(key);
			}
			else {
				check_key = kt_KTu(key);
			}
			if (check_key) {
				if (key == 8) {// <- backspace xoa
					if (input.length() == 1) {
						
					}
					else {
						input.erase(input.end() - 2);
					}
				}
				else if (key != 13) {
					if (input.length() == (max_value + 1)) {
						string s = "Toi da la ";
						s += to_string(max_value);
						s += " ki tu.";
						char m[255];
						strcpy_s(m, s.c_str());
						writeText(l + e_kcl, t + e_kct, m, 1, i_error_color, f_medium, i_bg);
						// reset lai mau
						setbkcolor(i_highlight);
						setcolor(i_color);
						continue;
					}
					// them chữ vào input
					input.erase(input.end() - 1);
					input += key;
					input += "_";
				}
				if (input.length() > 2) {
					// kiem tra 2 dau cách, .  thi xoa
					int n = input.length();
					if ((input[n - 2] == input[n - 3]) && (input[n - 2] == ' ' || input[n - 2] == '.')) {
						input.erase(input.end() - 2);
					}
				}
				strcpy_s(result, input.c_str());
				//---xoa canh bao
				setfillstyle(1, i_bg);
				bar(l + e_kcl, t+e_kct ,r + e_length, b + 20);
				//-- xoa đề render lại từ đầu
				setfillstyle(1, i_highlight);
				bar3d(l, t, r, b, 0, 0);
				//-- ghi chữ lại
				outtextxy(l + kcl, t + kct, result);
				cout << "input: " << input << endl;
				if (key == 13 ) {
					//enter để break					
					key_enter = true;
					x = NULL; y = NULL;
					input.erase(input.end() - 1);
					strcpy_s(result, input.c_str());
					cout << "result:" << result << endl;

					// enter xong vẫn để lại chữ
					// enter  xong vẫn để lại chữ
					setfillstyle(1, 15);
					bar3d(l, t, r, b, 0, 0);
					writeText(l + kcl, t + kct, result,1, i_color,f_medium,15);
				}
			}
			else {
				cout << "ki tu k hop le" << endl;
			}
			
		}
		
		
		delay(1);
	}
		cout << "out";
	return input;
}
bool announce_board(int kcl=0, int kct=0,int bg= COLOR(232, 246, 250)) { // 200 //400 

	setfillstyle(1, bg);
	bar3d(420, 210, 780, 410, 0, 0);
	writeText(450+kcl, 280+kct, (char*)"Ban co muon xoa khong?", 1, 0,f_medium, bg);
	text_box(500, 345, 570, 370, (char*)"Co", f_medium, 1, 5, 20, bg, 0);
	text_box(610, 345, 680, 370, (char*)"Khong", f_medium, 1, 5, 6, bg, 0);
	text_box(750, 210, 780, 240,(char*)"X",f_medium,1,7,9,COLOR(255, 21, 0), 0);

	return 0;
}