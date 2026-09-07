#include <iostream>
#include <vector>
#include<chrono>
#include<cmath>
#include <algorithm>

using namespace std;

struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};
int getHeight(AVLNode* node) {
    if (node == nullptr) return -1;
    return node->height;
}
void updateHeight(AVLNode* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}
int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}
#include <climits>

//hàm đi tuần tra từng nút
bool isValidAVLHelper(AVLNode* node, long long minVal, long long maxVal, bool& balanced) {
    if (node == nullptr) return true;

    //kiểm tra luật BST (trái<gốc<phải)
    if (node->data <= minVal || node->data >= maxVal) return false;

    //kiểm tra luật cân bằng AVL
    int bfval = getBalanceFactor(node);
    if (bfval < -1 || bfval > 1) {
        balanced = false; //vi phạm
    }

    //tiếp tục xuống nhánh trái và nhánh phải
    bool leftOk = isValidAVLHelper(node->left, minVal, node->data, balanced);
    bool rightOk = isValidAVLHelper(node->right, node->data, maxVal, balanced);

    return leftOk && rightOk;
}
bool isValidAVL(AVLNode* root) {
    bool balanced = true;
    bool isBST = isValidAVLHelper(root, LLONG_MIN, LLONG_MAX, balanced);

    //phải đạt cả 2 thì mới được công nhận là AVL
    return isBST && balanced;
}
int main() {
    // case1: tạo cây AVL hợp lệ
    //        20
    //       /  \
    //     10    30
    AVLNode* root1 = new AVLNode(20);
    root1->left = new AVLNode(10);
    root1->right = new AVLNode(30);

    //cập nhật chiều cao từ dưới lên
    updateHeight(root1->left);
    updateHeight(root1->right);
    updateHeight(root1);

    cout << "Cay 1 co phai AVL hop le khong? "
         << (isValidAVL(root1) ? "Co" : "Khong") << "\n";


    // --- TEST 2: Tạo cây vi phạm -cây suy biến
    //        30
    //       /
    //     20
    //    /
    //  10
    AVLNode* root2 = new AVLNode(30);
    root2->left = new AVLNode(20);
    root2->left->left = new AVLNode(10);

    //cập nhật chiều cao từ dưới lên
    updateHeight(root2->left->left);
    updateHeight(root2->left);
    updateHeight(root2);

    cout << "Cay 2 co phai AVL hop le khong? "
         << (isValidAVL(root2) ? "Co" : "Khong") << "\n";

    return 0;
}
