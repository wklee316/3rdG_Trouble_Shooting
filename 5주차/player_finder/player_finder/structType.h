#pragma once

struct Tile {
	//���� Ÿ�� data�� ������ �ش� Ÿ�� ���� ������ �ִ��� �����Ѵ�. 0 : ����, 1 : �÷��̾�, 2 : ��, 3 : ��ֹ�, 7 : �ִ� ���
	int data;
	int x, y;

	Tile(int a, int b, int c) {
		this->data = a;
		this->x = b;
		this->y = c;
	}
};

struct TreeNode {
    Tile* tile;

    TreeNode* parents;
    vector<TreeNode*> children; // �ڽ� ������ ����Ű�� ������ ����

    // ������ �Լ�
    TreeNode(Tile* data, TreeNode* pa) {
        this->tile = data;
        this->parents = pa;
    }
};