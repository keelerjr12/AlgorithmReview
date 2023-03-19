#ifndef CHP10_H
#define CHP10_H

namespace Keeler {

    template <class T>
    class List {
     public:
        using reference = T&;

        reference front() {
            return head->value;
        }

        reference back() {
            return tail->value;
        }

        bool empty() const {
            return head == &sentinel;
        }

        void push_back(const T& value) {
            Node* to_add = new Node();
            to_add->next = &sentinel;
            to_add->value = value;

            if (empty()) {
                head = to_add;
            }

            tail = to_add;
        }

        void pop_back() {
        }

     private:
        struct Node {
            Node* next = nullptr;
            T value;
        };

        Node sentinel;
        Node* head = &sentinel;
        Node* tail = &sentinel;
    };

}

#endif // CHP10_H