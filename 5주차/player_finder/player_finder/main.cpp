#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

#include "map.h"
#include "tree.h"


Tile* map[10][10];
Tile* Vmap[10][10];



bool isMovable(int x, int y, int n, int m) {
	return x >= 0 && x < n&& y >= 0 && y < m;
}


void printMap() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	CONSOLE_FONT_INFOEX oldCfi = cfi;
	cfi.dwFontSize.X = 20; // 가로 크기를 12로 변경
	cfi.dwFontSize.Y = 20; // 세로 크기를 24로 변경
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (map[i][j]->data)
			{
			case 0: SetConsoleTextAttribute(hConsole, 0 | 7); cout << "□"; break;
			case 1: SetConsoleTextAttribute(hConsole, 0 | 2); cout << "●"; break;
			case 2: SetConsoleTextAttribute(hConsole, 0 | 4); cout << "●"; break;
			case 3: SetConsoleTextAttribute(hConsole, 0 | 15); cout << "■"; break;
			case 7: SetConsoleTextAttribute(hConsole, 0 | 6); cout << "■"; break;
			}
		}
		cout << endl;
	}

}

void init() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = new Tile(0,j,i);
		}
	}


	map[2][1]->data = 1;
	map[8][8]->data = 2;
	map[4][4]->data = 3;
	map[5][4]->data = 3;
	map[6][4]->data = 3;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Vmap[i][j] = map[i][j];
		}
	}
}

void dfs(TreeNode* node) {
	cout << node->tile->data << endl;
	for (int i = 0; i < node->children.size(); i++) {
		dfs(node->children[i]);
	}
}


TreeNode* makeTree(TreeNode* node) {

	int dx[4] = { -1, 0, 1, 0 }; // 좌, 하, 우, 상
	int dy[4] = { 0, 1, 0, -1 };

	int x = node->tile->x;
	int y = node->tile->y;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isMovable(nx, ny, 10, 10) && Vmap[ny][nx]->data == 0) {
			TreeNode* child = new TreeNode(map[ny][nx]);
			node->children.push_back(child);
			Vmap[ny][nx]->data = 7; // 방문한 좌표는 7으로 변경하여 중복 방문을 방지함
			makeTree(child);
		}
	}

	return node;
}

void route(int x, int y) {
	TreeNode* root = new TreeNode(map[y][x]);


	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Vmap[i][j] = map[i][j];
		}
	}
	makeTree(root);

	dfs(root);
}



int main() {


	init();
	printMap();

	route(7, 7);
	system("cls");
	printMap();

	
	return 0;
}

