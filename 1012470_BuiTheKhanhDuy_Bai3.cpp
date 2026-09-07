#include <iostream>
#include <vector>
#include<chrono>
#include<cmath>
#include <algorithm>

using namespace std;

struct AVLNode
{
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};
int getHeight(AVLNode* node)
{
    if (node == nullptr) return -1;
    return node->height;
}
void updateHeight(AVLNode* node)
{
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}
int getBalanceFactor(AVLNode* node)
{
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}
#include <climits>

//hàm đi tuần tra từng nút
bool isValidAVLHelper(AVLNode* node, long long minVal, long long maxVal, bool& balanced)
{
    if (node == nullptr) return true;

    //kiểm tra luật BST (trái<gốc<phải)
    if (node->data <= minVal || node->data >= maxVal) return false;

    //kiểm tra luật cân bằng AVL
    int bfval = getBalanceFactor(node);
    if (bfval < -1 || bfval > 1)
    {
        balanced = false; //vi phạm
    }

    //tiếp tục xuống nhánh trái và nhánh phải
    bool leftOk = isValidAVLHelper(node->left, minVal, node->data, balanced);
    bool rightOk = isValidAVLHelper(node->right, node->data, maxVal, balanced);

    return leftOk && rightOk;
}
bool isValidAVL(AVLNode* root)
{
    bool balanced = true;
    bool isBST = isValidAVLHelper(root, LLONG_MIN, LLONG_MAX, balanced);

    //phải đạt cả 2 thì mới được công nhận là AVL
    return isBST && balanced;
}
AVLNode* rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;     // x là con trái của y
    AVLNode* T2 = x->right;   // T2 là con phải của x

    //Thực hiện xoay:
    x->right = y;             // Kéo y xuống làm con phải của x
    y->left = T2;             // Gắn T2 vào làm con trái của y để không bị mất dữ liệu

    //update chiều cao
    updateHeight(y);          // y giờ là con, phải cập nhật trước
    updateHeight(x);          // x lên làm gốc mới, cập nhật sau cùng

    return x;                 // trả về gốc mới của cây
}
AVLNode* rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;    // y là con phải của x
    AVLNode* T2 = y->left;    // T2 là con trái của y

    // Thực hiện xoay:
    y->left = x;              // Kéo x xuống làm con trái của y
    x->right = T2;            // Gắn T2 vào làm con phải của x

    //update chiều cao
    updateHeight(x);          // x giờ là con, cập nhật trước
    updateHeight(y);          // y lên làm gốc mới, cập nhật sau cùng

    return y;                 // Trả về gốc mới của cây
}
AVLNode* insertAVL(AVLNode* node, int key)
{
    // Bước 1: Chèn như BST bình thường
    if (node == nullptr) return new AVLNode(key);
    if (key < node->data)
        node->left = insertAVL(node->left, key);
    else if (key > node->data)
        node->right = insertAVL(node->right, key);
    else
        return node;
// Bước 2: Cập nhật chiều cao
    updateHeight(node);
// Buoc 3: TODO - tinh balance factor va xu ly 4 truong hop LL/RR/LR/RL
    int balance = getBalanceFactor(node);
    // TH LL
    if (balance > 1 && key < node->left->data)
        return rotateRight(node);

    // TH RR
    if (balance < -1 && key > node->right->data)
        return rotateLeft(node);

    // TH LR (Bị gập góc)
    if (balance > 1 && key > node->left->data)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // TH RL (Bị gập góc)
    if (balance < -1 && key < node->right->data)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

int main()
{
    cout << "KIEM THU 4 PHEP XOAY AVL\n\n";

    // 1. TH Left-Left
    AVLNode* rootLL = nullptr;
    int keysLL[] = {30, 20, 10}; //Lệch trái
    for (int k : keysLL)
    {
        rootLL = insertAVL(rootLL, k);
    }
    cout << "1. Truong hop LL (30, 20, 10):\n";
    cout << "- Cay hop le khong? " << (isValidAVL(rootLL) ? "Co" : "Khong") << "\n";
    cout << "- Goc hien tai: " << rootLL->data << "\n";


    // 2. Trường hợp Right-Right
    AVLNode* rootRR = nullptr;
    int keysRR[] = {10, 20, 30}; //Lệch phải
    for (int k : keysRR)
    {
        rootRR = insertAVL(rootRR, k);
    }
    cout << "2. Truong hop RR (10, 20, 30):\n";
    cout << "- Cay hop le khong? " << (isValidAVL(rootRR) ? "Co" : "Khong") << "\n";
    cout << "- Goc hien tai: " << rootRR->data << "\n";


    // 3. Trường hợp Left-Right
    AVLNode* rootLR = nullptr;
    int keysLR[] = {30, 10, 20}; //Lệch trái rồi phải
    for (int k : keysLR)
    {
        rootLR = insertAVL(rootLR, k);
    }
    cout << "3. Truong hop LR (30, 10, 20):\n";
    cout << "- Cay hop le khong? " << (isValidAVL(rootLR) ? "Co" : "Khong") << "\n";
    cout << "- Goc hien tai: " << rootLR->data << "\n";


    // 4. Trường hợp Right-Left
    AVLNode* rootRL = nullptr;
    int keysRL[] = {10, 30, 20}; // Lệch phải rồi trái
    for (int k : keysRL)
    {
        rootRL = insertAVL(rootRL, k);
    }
    cout << "4. Truong hop RL (10, 30, 20):\n";
    cout << "- Cay hop le khong? " << (isValidAVL(rootRL) ? "Co" : "Khong") << "\n";
    cout << "- Goc hien tai: " << rootRL->data << "\n";

    return 0;
}
