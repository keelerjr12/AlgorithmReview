#ifndef CHP10_H
#define CHP10_H

namespace Keeler {

    template <class T>
    class List {
     public:
        using value = T;
        using reference = value&;

        reference front() {
            return head->value;
        }

        reference back() {
            return tail->value;
        }

        bool empty() const {
            return head == nullptr;
        }

        void push_back(const T& value) {
            const auto to_add = new Node {nullptr, tail, value};

            if (empty()) {
                head = to_add;
            }

            tail = to_add;
        }

        void pop_back() {
            const auto new_tail = tail->prev;
            delete tail;

            tail = new_tail;
            if (tail == nullptr) {
                head = nullptr;
            }
        }

        void clear() {
            for (auto curr = head; curr != nullptr; /* empty */) {
                const auto next_node = curr->next;
                delete curr;

                curr = next_node;
            }

            head = nullptr;
            tail = nullptr;
        }

     private:
        struct Node {
            Node* next = nullptr;
            Node* prev = nullptr;
            T value;
        };

        Node* head = nullptr;
        Node* tail = nullptr;
    };

}

#endif // CHP10_H