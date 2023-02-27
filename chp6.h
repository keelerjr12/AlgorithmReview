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

int left(int i) { return (i << 1) + 1;
}

int right(int i) {
    return (i + 1) << 1;
}

void Heap::Heapify(int i) {
    auto l = left(i);
    auto r = right(i);
    auto largest = i;

    if (l < mHeapSize && mData[largest] < mData[l]) {
        largest = l;
    }

    if (r < mHeapSize && mData[largest] < mData[r]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(mData[largest], mData[i]);
        Heapify(largest);
    }
}

void Heap::Build() {
    for (auto i = (mHeapSize / 2) - 1; i >= 0; --i) {
        Heapify(i);
    }
}

void Heap::Sort() {
    Build();

    while (mHeapSize > 0) {
        std::swap(mData[0], mData[mHeapSize - 1]);

        --mHeapSize;

        Heapify(0);
    }
}
#endif // CHP6_H