#pragma once
#define maxTHeader  20
// Color constant
#define HIGHLIGHT_BACKGROUND COLOR(248, 223, 9)
#define HEADER_BACKGROUND COLOR(51, 73, 96)
#define HEADER_TEXT_COLOR 15
#define COLS_SF 10
// input
#define I_BG COLOR(51, 73, 96) // màu nền  khi enter nhập xong
#define I_HIGHLIGHT COLOR(226, 205, 247) // highlight khi click vào
#define I_COLOR 0 // màu chữ
#define I_ERROR_COLOR COLOR(255,0,0) // màu của chữ khi báo lỗi
// color
#define XANH_NHAT COLOR(11, 172, 173)
char header_title[4][maxTHeader] = { "VAT TU","NHAN VIEN","THANH TOAN","THONG KE" };
char CURD_o_text[3][20] = { "Chinh sua","Xoa","Chi tiet"};

//staff
char sf_table_header[4][20] = { "MaNV","Ho Ten","Phai","Chuc nang"};

const int bk_screen = COLOR(51, 73, 96);
const int textColor = 0;


const int f_medium = 10; //ma BOLD_FONT settextstyle() trong box chuc nang kc l? 1
const int f_small = 3;// kc l? 1