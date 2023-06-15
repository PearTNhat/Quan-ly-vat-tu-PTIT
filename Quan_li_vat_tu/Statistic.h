#include "Header.h"
#pragma once

struct SoldItem {
	char MAVT[11];
	int sold;
};

struct SoldItem_arr {
	SoldItem* soldItem[500];
	int length = 0;
};