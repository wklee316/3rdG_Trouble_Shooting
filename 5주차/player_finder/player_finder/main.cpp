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
		cout << "커맨드를 입력해주세요.\n[1 : 최단 경로 출력, 2 : 플레이어 위치 변경, 3 : 몬스터 위치 변경, 4 : 장애물 추가 및 삭제, 0 : 프로그램 종료 ] : ";
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
			cout << "프로그램을 종료합니다.";
			return 0;
			break;
		default:
			cout << "잘못된 입력입니다.";
			break;
		}
		Sleep(500);
		m1.printMap();
	}

	
	return 0;
}

