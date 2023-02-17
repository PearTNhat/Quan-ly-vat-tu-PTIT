#pragma once
#include "Header.h"
#include "Common.h"
#include "Constant.h"
void create_sf_header() {
	setfillstyle(1, bk_screen);
	setcolor(0);
	bar3d(10, 65, 1180, 115, 0, 0);

	text_box(15, 70, 310, 110, (char*)"Them nhan vien", f_medium, 3, 10, 40, 11);
}