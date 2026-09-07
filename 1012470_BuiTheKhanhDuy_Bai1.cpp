#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;
struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
TreeNode* insert(TreeNode* root, int key) // hàm insert
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
int height (TreeNode* root) // hàm chiều cao
{
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}
int main()
{
    int sizes[] = {1000, 5000, 10000, 20000};
    for (int n : sizes) //=>vòng for chạy 4 lần ứng với 4 số
    {
        TreeNode* root = nullptr;
        auto start = high_resolution_clock::now(); // bắt đầu chạy thời gian
        for (int i = 0; i < n; i++) 
            root = insert(root, i);// chèn số
        auto end = high_resolution_clock::now();//kết thúc
        duration<double, milli> time_span = end - start;//cuối trừ đầu => thời gian chạy

        cout << "n = " << n << "\n";
        cout << "Chieu cao thuc te: " << height(root) << "\n";
        cout << "Chieu cao ly thuyet log2(n): " << log2(n) << "\n";
        cout << "Thoi gian chen: " << time_span.count() << " ms\n";
        cout << "-----------------------\n";
    }
    return 0;
}
