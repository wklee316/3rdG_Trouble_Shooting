#include <iostream>
#include <vector>
#include <Windows.h>
#include <queue>
using namespace std;

#include "map.h"






int main() {
	int num = 1;
	Map m1;
	m1.printMap();
	

	while (num != 0) {
		cout << "Ŀ�ǵ带 �Է����ּ���.\n[1 : �ִ� ��� ���, 2 : �÷��̾� ��ġ ����, 3 : ���� ��ġ ����, 4 : ��ֹ� �߰� �� ����, 0 : ���α׷� ���� ] : ";
		cin >> num;

		switch (num)
		{
		case 1:
			m1.printTrace();
			break;
		case 2:
			m1.changePlayerPos();
			break;
		case 3:
			m1.changeEnemyPos();
			break;
		case 4:
			m1.addOrRemoveBlock();
			break;
		case 0:
			cout << "���α׷��� �����մϴ�.";
			return 0;
			break;
		default:
			cout << "�߸��� �Է��Դϴ�.";
			break;
		}
		Sleep(500);
		m1.printMap();
	}

	
	return 0;
}

