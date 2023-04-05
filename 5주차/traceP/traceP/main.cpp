#include <iostream>
#include <queue>
#include <cstring>
#define MAX 10
#define OBSTACLE -1

using namespace std;

int graph[MAX][MAX];
int dist[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

struct Node {
    int x;
    int y;
    int distance;
};

int bfs(int startX, int startY, int endX, int endY) {
    queue<Node> q;
    q.push({ startX, startY, 0 });

    memset(visited, false, sizeof(visited));
    visited[startX][startY] = true;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int distance = q.front().distance;
        q.pop();

        if (x == endX && y == endY) {
            return distance;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= MAX || ny >= MAX) {
                continue;
            }

            if (!visited[nx][ny] && graph[nx][ny] != OBSTACLE) {
                visited[nx][ny] = true;
                q.push({ nx, ny, distance + 1 });
            }
        }
    }

    return -1;
}

int main() {
    // �� �ʱ�ȭ
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }

    // ��ֹ� �߰�
    graph[2][2] = OBSTACLE;
    graph[3][2] = OBSTACLE;
    graph[4][2] = OBSTACLE;

    // ������, ���� �Է¹ޱ�
    int startX, startY, endX, endY;
    cout << "Enter start coordinate (x,y): ";
    cin >> startY >> startX;
    cout << "Enter end coordinate (x,y): ";
    cin >> endY >> endX;

    // �ִܰŸ� ���
    int shortestDist = bfs(startX, startY, endX, endY);

    // ��� ���
    if (shortestDist == -1) {
        cout << "No path exists.\n";
    }
    else {
        cout << "The shortest distance is " << shortestDist << endl;
    }

    // �� �ð�ȭ
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == startX && j == startY) {
                cout << "�� ";
            }
            else if (i == endX && j == endY) {
                cout << "�� ";
            }
            else if (graph[i][j] == OBSTACLE) {
                cout << "�� ";
            }
            else {
                cout << "�� ";
            }
        }
        cout << endl;
    }

    return 0;
}
