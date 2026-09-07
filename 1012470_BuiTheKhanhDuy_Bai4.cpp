#include <iostream>
#include <vector>
#include<chrono>
#include<cmath>
#include <algorithm>
#include <cstdlib>
#include <climits>
using namespace std;
using namespace std::chrono;
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int key)
{
    if (root == nullptr)
    {
        return new TreeNode(key);
    }
    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }
    return root;
}
int height(TreeNode* root)
{
    if (root == nullptr) return -1;
    return 1 + std::max(height(root->left), height(root->right));
}
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
//tìm kiếm cho cây BST thường
bool searchBST(TreeNode* root, int key)
{
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchBST(root->left, key);
    return searchBST(root->right, key);
}

//tìm kiếm cho cây AVL
bool searchAVL(AVLNode* root, int key)
{
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data) return searchAVL(root->left, key);
    return searchAVL(root->right, key);
}
int main()
{
    int sizes[] = {1000, 5000, 10000, 20000};

    cout << "n\t| Cau truc\t| Chieu cao\t| TG chen (ms)\t| TG tim 1000 lan (ms)\n";
    cout << "----------------------------------------------------------------------\n";

    for (int n : sizes)
    {
        //chuẩn bị
        TreeNode* bstRoot = nullptr;
        AVLNode* avlRoot = nullptr;

        //1. Check cây BST thường
        auto startBstInsert = high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            bstRoot = insert(bstRoot, i);// Hàm insert của Bài 1
        }
        auto endBstInsert = high_resolution_clock::now();
        duration<double, std::milli> timeBstInsert = endBstInsert - startBstInsert;

        //bấm giờ cho 1000 lần tìm kiếm ngẫu nhiên trên BST
        auto startBstSearch = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            searchBST(bstRoot, rand() % n);
        }
        auto endBstSearch = high_resolution_clock::now();
        duration<double, std::milli> timeBstSearch = endBstSearch - startBstSearch;

        //2. Check cây AVL
        auto startAvlInsert = high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            avlRoot = insertAVL(avlRoot, i); // Hàm insert của Bài 3
        }
        auto endAvlInsert = high_resolution_clock::now();
        duration<double, std::milli> timeAvlInsert = endAvlInsert - startAvlInsert;

        //bấm giờ cho 1000 lần tìm kiếm ngẫu nhiên trên BST
        auto startAvlSearch = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            searchAVL(avlRoot, rand() % n);
        }
        auto endAvlSearch = high_resolution_clock::now();
        duration<double, std::milli> timeAvlSearch = endAvlSearch - startAvlSearch;

        //In KQ
        cout << n << "\t| BST thuong\t| " << height(bstRoot) << "\t\t| "
             << timeBstInsert.count() << "\t\t| " << timeBstSearch.count() << "\n";
        cout << n << "\t| AVL Tree\t| " << getHeight(avlRoot) << "\t\t| "
             << timeAvlInsert.count() << "\t\t| " << timeAvlSearch.count() << "\n";
        cout << "----------------------------------------------------------------------\n";
    }

    return 0;
}
