#ifndef CHP6_H
#define CHP6_H

#include <vector>

class Heap {
 public:

    Heap(const std::vector<int>& data) : mData(data), mHeapSize(data.size()) { }

    const std::vector<int>& Data() const { return mData; }
    void Sort();

 private:

    void Build();
    void Heapify(int i);

    std::vector<int> mData;
    int mHeapSize;
};

#endif // CHP6_H