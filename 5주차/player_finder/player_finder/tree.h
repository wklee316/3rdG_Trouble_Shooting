#pragma once

struct TreeNode {
    Tile* tile;

    TreeNode* parents;
    vector<TreeNode*> children; // 자식 노드들을 가리키는 포인터 벡터

    // 생성자 함수
    TreeNode(Tile* data, TreeNode* pa) {
        this->tile = data;
        this->parents = pa;
    }
};