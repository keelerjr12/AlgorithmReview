#include "chp6.h"

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