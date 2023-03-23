#ifndef CHP10_H
#define CHP10_H

namespace keeler {

    namespace detail {
        
        template <typename T>
        struct Node {
            Node* next = nullptr;
            Node* prev = nullptr;
            T value;
        };

    }

    template<typename T>
    class ListIterator {
      public:

        using value_type = T;
        using pointer_type = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        explicit ListIterator(detail::Node<T>* node) : m_node(node) { }

        reference operator*() const {
            return m_node->value;
        }

        ListIterator& operator++() {
            m_node = m_node->next;
            return *this;
        }

        friend bool operator==(const ListIterator& lhs, const ListIterator& rhs) { return lhs.m_node == rhs.m_node; }
        friend bool operator!=(const ListIterator& lhs, const ListIterator& rhs) { return lhs.m_node != rhs.m_node; }

      private:

        detail::Node<T>* m_node;
    };

    template <typename T>
    class List {

     public:

        using value = T;
        using reference = value&;
        using iterator = ListIterator<T>;

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
            const auto to_add = new detail::Node<T> {nullptr, tail, value};

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

        iterator end() {
            return iterator(nullptr);
        }

     private:

        detail::Node<T>* head = nullptr;
        detail::Node<T>* tail = nullptr;

    };


}

#endif // CHP10_H