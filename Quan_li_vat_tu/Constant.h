#pragma once
#define maxTHeader  20
#define HIGHLIGHT_BOX 10
#define COLS_SF 10
// input
#define I_BG 15
#define I_HIGHLIGHT COLOR(226, 205, 247)
#define I_COLOR 0
#define I_ERROR_COLOR COLOR(255,0,0)

char header_title[4][maxTHeader] = { "VAT TU","NHAN VIEN","THANH TOAN","THONG KE" };
char CURD_o_text[3][20] = { "Chinh sua","Xoa","Chi tiet"};

//staff
char sf_table_header[4][20] = { "MaNV","Ho Ten","Phai","Chuc nang"};

const int bk_screen = 15;
const int textColor = 0;


const int f_medium = 10; //ma BOLD_FONT settextstyle() trong box chuc nang kc l? 1
const int f_small = 3;// kc l? 1