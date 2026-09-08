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
     //hàm siftdown
    void siftDown(int i) {
        int maxIndex = i; //cho i là lớn nhất
        int l = left(i);
        int r = right(i);

        //nếu con trái > cha hiện tại
        if (l < heap.size() && heap[l] > heap[maxIndex]) {
            maxIndex = l;
        }
        //nếu con phải > cha hiện tại (hoặc lớn hơn cả con trái)
        if (r < heap.size() && heap[r] > heap[maxIndex]) {
            maxIndex = r;
        }

        //nếu cha chưa phải lớn nhất
        if (maxIndex != i) {
            swap(heap[i], heap[maxIndex]); //đổi chỗ với con giỏi nhất
            siftDown(maxIndex); //tiếp tục thực hiện hàm cho đến khi vào đúng vị trí
        }
    }
    //ham siftup
    void siftUp(int i) {         //phải lên đc tới gốc và cha > con
        while (i > 0 && heap[i] > heap[parent(i)]) { // khi chưa tới gốc và con vẫn > cha
            swap(heap[i], heap[parent(i)]); //đổi chỗ
            i = parent(i); //cập nhật lại vị trí của con
        }
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

    //hàm thêm phần tử
    void insert(int value) {
        heap.push_back(value); //chèn cuối
        siftUp(heap.size() - 1); //sd sift up để cho lên
    }

    // Hàm Lấy ra Sếp Tổng (phần tử lớn nhất)
    int extractMax() {
        if (heap.empty()) return -1; // Cây rỗng

        int maxVal = heap[0]; // Lưu lại Sếp Tổng để lát trả về

        heap[0] = heap.back(); // Lấy thằng lính cuối mảng lên làm Sếp
        heap.pop_back();       // Xóa thằng lính cuối mảng

        if (!heap.empty()) {
            siftDown(0); // Bắt đầu giáng chức thằng Sếp dỏm từ gốc
        }

        return maxVal; // Trả về Sếp Tổng xịn ban đầu
    }
};
int main() {
    MaxHeap pq; // Khởi tạo một Hàng đợi ưu tiên (Priority Queue)

    cout << "--- MO PHONG HANG DOI UU TIEN (MAX-HEAP) ---\n\n";

    // 1. chọn mua các sản phẩm có giá trị khác nhau
    cout << "1.  --- MUA HANG ---\n";
    pq.insert(50); cout << "+ Da chon san pham tri gia 50K\n";
    pq.insert(100); cout << "+ Da chon san pham tri gia 100K\n";
    pq.insert(200); cout << "+ Da chon san pham tri gia 200K\n";
    pq.insert(500); cout << "+ Da chon san pham tri gia 500K\n";
    pq.insert(20); cout << "+ Da chon san pham tri gia 20K\n";

    //in sản phẩm đã chọn
    cout << "\n-> Danh sach so tien cua cac san pham hien tai:\n";
    pq.printAsTree();

    // 2. bắt đầu thanh toán (từ đắt - > rẻ)
    cout << "\n2. --- THANH TOAN ---\n";

    int target1 = pq.extractMax();
    cout << "- Lay ra so tien de tra cho san pham dat nhat " << target1 << "\n";

    int target2 = pq.extractMax();
    cout << "- Lay ra so tien de tra cho san pham dat thu hai " << target2 << "\n";

    //in lại số tiền còn lại
    cout << "\n-> So tien con lai:\n";
    pq.printAsTree();

    return 0;
}
