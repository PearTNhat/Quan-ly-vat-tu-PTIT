#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
#define CLL COLOR(240, 163, 223)

void Loading()
{
	text_box_no_border(0, 0, 1200, 900, (char*)"QUAN LY VAT TU", 4, 7, 100, 200, CLL, 0);
	text_box_no_border(200, 200, 300, 300, (char*)"LE TUAN NHAT", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 240, 300, 340, (char*)"DO NGUYEN PHUONG", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(200, 280, 300, 380, (char*)"HO VAN PHU", 4, 2, 0, 0, CLL, 0);
	text_box_no_border(600, 350, 900, 390, (char*)"GV: LUU NGUYEN KY THU", 4, 2, 0, 8, CLL, 0);
	text_box_no_border(250, 400, 300, 420, (char*)"Loading...", 4, 1, 0, 8, CLL, 0);
	rectangle(200, 420, 985, 450);
}