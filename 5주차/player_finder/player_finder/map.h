#pragma once


struct Tile {
	//���� Ÿ�� data�� ������ �ش� Ÿ�� ���� ������ �ִ��� �����Ѵ�. 0 : ����, 1 : �÷��̾�, 2 : ��, 3 : ��ֹ�
	int data;
	int x, y;

	Tile(int a, int b, int c) {
		this->data = a;
		this->x = b;
		this->y = c;
	}
};