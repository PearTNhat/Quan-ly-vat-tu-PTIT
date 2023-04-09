#pragma once
#define maxTHeader  20
// Color constant
#define HIGHLIGHT_BACKGROUND COLOR(255, 211, 0)//COLOR(157, 238, 157)//COLOR(173, 255, 173)//COLOR(255, 211, 0)
#define HEADER_BACKGROUND COLOR(31, 53, 76)//COLOR(51, 73, 96)
#define HEADER_TEXT_COLOR 0
//
#define ROW_STAFF 10
#define ROWS_PER_PG_SS 7
//color infor staff good
#define COLOR_INFOR_SG COLOR(186, 245, 223)
#define COLOR_INFOR_SS COLOR(221, 221, 221)

// input
#define I_BG COLOR(51, 73, 96) // màu nền khi enter nhập xong
#define I_HIGHLIGHT COLOR(226, 205, 247) // highlight khi click vào
#define I_COLOR 0 // màu chữ
#define I_ERROR_COLOR COLOR(255,0,0) // màu của chữ khi báo lỗi
// color
#define ss_page_header_box_color COLOR(157, 238, 157)
#define XANH_DUONG_NHAT COLOR(157, 238, 157)//COLOR(144, 238, 144)//COLOR(11, 172, 173)
#define XANH_LA_CAY COLOR(0, 255, 0)
#define PROHIBIT COLOR(200, 200, 190)

char header_title[4][maxTHeader] = { "VAT TU","NHAN VIEN","THANH TOAN","THONG KE" };
char CURD_o_text[3][20] = { "Chinh sua","Xoa","Chi tiet"};

//goods
char g_table_header[][20] = { "MaVT","TenVT","Don vi","So luong ton","Chuc nang"};

//staff
char sf_table_header[4][20] = { "MaNV","Ho Ten","Phai","Chuc nang"};

const int bk_screen = COLOR(76, 98, 119);//COLOR(51, 73, 96);
const int textColor = 0;


const int f_medium = 10; //ma BOLD_FONT settextstyle() trong box chuc nang kc l? 1
const int f_small = 3;// kc l? 1

//Statistic
char ss_table_header[5][20] = { "So HD", "Ngay lap", "Loai HD", "Ho ten NV lap", "Tri gia HD (VND)" };
char table_doanhThu_header[2][20] = { "Thang", "Doanh thu (VND)" };
char table_in_HD_header[][20] = { "Ma VT", "So luong", "Don gia", "%VAT", "Trang Thai", "Thanh tien (VND)" };