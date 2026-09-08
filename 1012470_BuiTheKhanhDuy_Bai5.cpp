#include <iostream>
#include <vector>

using namespace std;

class MaxHeap
{
private:
    vector<int> heap;

    //hàm định vị trí
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return 2 * i + 1;
    }
    int right(int i)
    {
        return 2 * i + 2;
    }

public:
    void setData(vector<int> arr)
    {
        heap = arr;
    }

    // hàm kiểm tra xem mảng có chuẩn maxheap không
    bool isValidHeap()
    {
        for (int i = 1; i < heap.size(); i++)
        {
            if (heap[i] > heap[parent(i)])   //con chỉ được <= cha
            {
                return false;
            }
        }
        return true; //tất cả đều hợp lệ thì sẽ trả về true - ko vi phạm
    }
    void printAsTree()
    {
        int n = heap.size();
        int levelStart = 0, levelSize = 1;
        while (levelStart < n)
        {
            for (int i = levelStart; i < levelStart + levelSize && i < n; i++)
            {
                cout << heap[i] << " ";
            }
            cout << "\n";
            //xuống tầng dưới - luôn có số lượng chỗ ngồi gấp đôi tầng ngay trên nó
            levelStart += levelSize;
            levelSize *= 2;
        }
    }
};
int main()
{
    cout << "--- KIEM TRA MAX-HEAP ---\n\n";

    //test mảng A hợp lệ
    MaxHeap h1;
    h1.setData({90, 70, 80, 20, 60, 50, 30});
    cout << "Mang A hop le khong? " << (h1.isValidHeap() ? "Co" : "Khong") << "\n";
    cout << "Cau truc cay A:\n";
    h1.printAsTree();
    cout << "\n";

    //test mảng B - mảng có phần tử vi phạm
    MaxHeap h2;
    h2.setData({90, 70, 80, 85, 60, 50, 30});
    cout << "Mang B hop le khong? " << (h2.isValidHeap() ? "Co" : "Khong") << "\n";
    cout << "Cau truc cay B:\n";
    h2.printAsTree();

    return 0;
}
