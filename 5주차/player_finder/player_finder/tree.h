#pragma once

struct TreeNode {
    Tile* tile;

    vector<TreeNode*> children; // 자식 노드들을 가리키는 포인터 벡터

    // 생성자 함수
    TreeNode(Tile* data) {
        this->tile = data;
    }
};

// 전위 순회 함수
void preOrderTraversal(TreeNode* node) {
    if (node != nullptr) {
        cout << node->tile << " ";
        for (auto child : node->children) {
            preOrderTraversal(child);
        }
    }
}
