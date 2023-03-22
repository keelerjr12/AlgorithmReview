#ifndef CHP10_H
#define CHP10_H

namespace Keeler {

    template <class T>
    class List {

     public:
        class ListIterator;

        using value = T;
        using reference = value&;
        using iterator = ListIterator;

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
            } else {
                tail->next = to_add;
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

        iterator begin() {
            return iterator(head);
        }

     private:
        struct Node {
            Node* next = nullptr;
            Node* prev = nullptr;
            T value;
        };

        Node* head = nullptr;
        Node* tail = nullptr;

    public:
        class ListIterator {
         public:
            explicit ListIterator(Node* node) : m_node(node) { }

            reference operator*() const {
                return m_node->value;
            }

            ListIterator& operator++() {
                m_node = m_node->next;
                return *this;
            }

         private:
            Node* m_node;
        };
    };


}

#endif // CHP10_H