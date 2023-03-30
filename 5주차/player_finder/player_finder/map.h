#pragma once


struct Tile {
	//맵의 타일 data의 정보로 해당 타일 위에 무엇이 있는지 저장한다. 0 : 공백, 1 : 플레이어, 2 : 적, 3 : 장애물
	int data;
	int x, y;

	Tile(int a, int b, int c) {
		this->data = a;
		this->x = b;
		this->y = c;
	}
};