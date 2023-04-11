#pragma once
#include "structType.h"

class Map {

private:
	Tile* tile[10][10];
	bool isVisit[10][10] = { false, };
	vector<TreeNode*> shortestroute;
	int px, py, ex, ey;

public:
	Map() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				tile[i][j] = new Tile(0, j, i);
				isVisit[i][j] = false;
			}
		}

		tile[2][1]->data = 1;
		tile[2][4]->data = 3;
		tile[3][4]->data = 3;
		tile[4][4]->data = 3;
		tile[5][4]->data = 3;
		tile[6][4]->data = 3;
		tile[6][3]->data = 3;
		tile[6][2]->data = 3;
		tile[6][1]->data = 3;
		tile[6][0]->data = 3;
		tile[8][8]->data = 2;

		px = 1;
		py = 2;
		ex = 8;
		ey = 8;
	}


	


	void printMap() {
		system("cls");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "   0  1  2  3  4  5  6  7  8  9" << endl;
		for (int i = 0; i < 10; i++) {
			cout << i;
			for (int j = 0; j < 10; j++) {
				switch (tile[i][j]->data)
				{
				case 0: SetConsoleTextAttribute(hConsole, 0 | 7); cout << " □"; break;
				case 1: SetConsoleTextAttribute(hConsole, 0 | 2); cout << " ●"; break;
				case 2: SetConsoleTextAttribute(hConsole, 0 | 4); cout << " ●"; break;
				case 3: SetConsoleTextAttribute(hConsole, 0 | 15); cout << " ■"; break;
				case 7: SetConsoleTextAttribute(hConsole, 0 | 2); cout << " ■"; break;
				}
			}
			cout << endl; cout << endl;
		}

	}

	void printTrace() {
		int ln = 0;
		shortestroute.clear();
		shortestroute = route(ex, ey);
		ln = shortestroute.size() - 1;
		if (shortestroute.size() > 1) {
			shortestroute.pop_back();
			for (int i = 0; i < ln - 1; i++) {
				shortestroute.back()->tile->data = 7;
				shortestroute.pop_back();
				printMap();
				cout << "최단 길이 : " << ln;
				Sleep(100);
			}
		}
		else
			cout << "경로를 찾을 수 없습니다.";

		clear();
		cout << endl << "엔터키를 입력하면 메인 화면으로 넘어갑니다.";
		cin.ignore();
		getchar();
	}

	void changePlayerPos() {
		tile[py][px]->data = 0;
		cout << "위치시킬 플레이어의 좌표를 입력해주세요.[ex. (5,1)은 \"5 1\"로 입력합니다.] : ";
		cin >> px >> py;
		tile[py][px]->data = 1;
	}

	void changeEnemyPos() {
		tile[ey][ex]->data = 0;
		cout << "적의 좌표를 입력해주세요.[ex. (5,1)은 \"5 1\"로 입력합니다.] : ";
		cin >> ex >> ey;
		tile[ey][ex]->data = 2;
	}

	void addOrRemoveBlock() {
		int cx, cy;
		cout << "좌표를 입력해주세요. 해당 좌표에 장애물이 존재하면 삭제, 존재하지 않는다면 추가합니다.[ex. (5,1)은 \"5 1\"로 입력합니다.] : ";
		cin >> cx >> cy;
		if (tile[cy][cx]->data == 0)
			tile[cy][cx]->data = 3;
		else if (tile[cy][cx]->data == 3)
			tile[cy][cx]->data = 0;
		else
			cout << "해당 좌표는 이미 플레이어 또는 몬스터가 존재합니다.";
	}

	

	


	
private:

	bool isMovable(int x, int y, int n, int m) {
		return x >= 0 && x < n&& y >= 0 && y < m;
	}

	void clear() {

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (tile[i][j]->data == 7)
					tile[i][j]->data = 0;
				isVisit[i][j] = false;
			}
		}
	}

	vector<TreeNode*> makeRouteQueue(TreeNode* node) {
		vector<TreeNode*> q;

		q.push_back(node);
		while (q.back()->parents != NULL) {
			q.push_back(q.back()->parents);
		}
		return q;
	}


	TreeNode* makeTree(TreeNode* root) {


		queue<TreeNode*> q;
		q.push(root);
		isVisit[root->tile->y][root->tile->x] = true;



		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();

			int x = node->tile->x;
			int y = node->tile->y;

			int dx[4] = { -1, 0, 1, 0 }; // 좌, 하, 우, 상
			int dy[4] = { 0, 1, 0, -1 };

			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (isMovable(nx, ny, 10, 10) && (isVisit[ny][nx] == false) && (tile[ny][nx]->data != 3)) {
					TreeNode* child = new TreeNode(tile[ny][nx], node);
					node->children.push_back(child);
					isVisit[ny][nx] = true; // 방문한 좌표는 true으로 변경하여 중복 방문을 방지함
					q.push(child);

					if (tile[ny][nx]->data == 1) {
						return child;
					}
				}
			}

		}
		return root;
	}

	vector<TreeNode*> route(int x, int y) {
		TreeNode* root = new TreeNode(tile[y][x], NULL);

		vector<TreeNode*> route = makeRouteQueue(makeTree(root));


		return route;

	}
};

