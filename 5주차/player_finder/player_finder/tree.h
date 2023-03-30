#pragma once

struct TreeNode {
    Tile* tile;

    vector<TreeNode*> children; // �ڽ� ������ ����Ű�� ������ ����

    // ������ �Լ�
    TreeNode(Tile* data) {
        this->tile = data;
    }
};

// ���� ��ȸ �Լ�
void preOrderTraversal(TreeNode* node) {
    if (node != nullptr) {
        cout << node->tile << " ";
        for (auto child : node->children) {
            preOrderTraversal(child);
        }
    }
}
