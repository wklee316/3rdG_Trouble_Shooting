#pragma once

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