#include <iostream>
#include <vector>

using namespace std;

struct Ticket
{
    int id;
    int priority;
};

class TicketHeap
{
private:
    vector<Ticket> heap; //mảng chứa các gói Ticket

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

    //so sánh dựa trên .priority
    void siftUp(int i)
    {
        while (i > 0 && heap[i].priority > heap[parent(i)].priority)
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // so sánh dựa trên .priority
    void siftDown(int i)
    {
        int maxIndex = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l].priority > heap[maxIndex].priority)
        {
            maxIndex = l;
        }
        if (r < heap.size() && heap[r].priority > heap[maxIndex].priority)
        {
            maxIndex = r;
        }

        if (maxIndex != i)
        {
            swap(heap[i], heap[maxIndex]);
            siftDown(maxIndex);
        }
    }

public:
    //nhận vào một Ticket
    void insert(Ticket t)
    {
        heap.push_back(t);
        siftUp(heap.size() - 1);
    }

    //trả về một Ticket
    Ticket extractMax()
    {
        if (heap.empty())
        {
            return {-1, -1}; //trống =>trả về -1
        }

        Ticket maxTicket = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
        {
            siftDown(0);
        }

        return maxTicket;
    }

    bool isEmpty()
    {
        return heap.empty();
    }
};

//chương trình mo phỏng
int main()
{
    TicketHeap helpdesk;

    cout << "--- HE THONG TIEP NHAN TICKET HELPDESK ---\n\n";

    //tiếp nhận 6 ticket với mức độ ưu tiên ngẫu nhiên
    cout << "1. Tiep nhan cac yeu cau tu nguoi dung:\n";
    helpdesk.insert({101, 2});
    cout << "+ Nhan Ticket #101 (uu tien: 2) - Quen mat khau\n";
    helpdesk.insert({102, 5});
    cout << "+ Nhan Ticket #102 (uu tien: 5) - SERVER SAP!\n";
    helpdesk.insert({103, 1});
    cout << "+ Nhan Ticket #103 (uu tien: 1) - Doi username\n";
    helpdesk.insert({104, 4});
    cout << "+ Nhan Ticket #104 (uu tien: 4) - Khong the thanh toan\n";
    helpdesk.insert({105, 3});
    cout << "+ Nhan Ticket #105 (uu tien: 3) - Loi dang nhap\n";
    helpdesk.insert({106, 5});
    cout << "+ Nhan Ticket #106 (uu tien: 5) - Loi mat DATA\n";

    cout << "\n2. Xu ly ticket (uu tien cao nhat truoc):\n";

    //vòng lặp rút ticket ra xử lý cho đến khi hết
    int order = 1;
    while (!helpdesk.isEmpty())
    {
        Ticket current = helpdesk.extractMax();
        cout << "- Luot " << order++ << ": Xu ly ticket #" << current.id
             << " (muc uu tien: " << current.priority << ")\n";
    }

    return 0;
}
