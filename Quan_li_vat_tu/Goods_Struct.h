#pragma once
#include "Header.h"
struct ListGoods {
	char maVT[11];
	char tenVT[26];
	char DVT[7];
	int SLT;
};
// tree
struct Node_Goods {
	ListGoods goods;
	Node_Goods* left;
	Node_Goods* right;
};
