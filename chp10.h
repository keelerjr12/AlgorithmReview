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

    template<typename T>
    class ConstListIterator {
      public:

        using value_type = T;
        using pointer_type = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        explicit ConstListIterator(const detail::Node<T>* node) : m_node(node) { }

        reference operator*() const {
            return m_node->value;
        }

        ConstListIterator& operator++() {
            m_node = m_node->next;
            return *this;
        }

        friend bool operator==(const ConstListIterator& lhs, const ConstListIterator& rhs) { return lhs.m_node == rhs.m_node; }
        friend bool operator!=(const ConstListIterator& lhs, const ConstListIterator& rhs) { return lhs.m_node != rhs.m_node; }

      private:

        const detail::Node<T>* m_node;
    };

    template <typename T>
    class List {

     public:

        using size_type = std::size_t;
        using value = T;
        using reference = value&;
        using iterator = ListIterator<T>;
        using const_iterator = ConstListIterator<T>;

        List() {
            create_header();
         }

        reference front() {
            return header.next->value;
        }

        reference back() {
            return header.prev->value;
        }

        bool empty() const {
            return header.next == &header;
        }

        size_type size() const {
            return std::distance(cbegin(), cend());
        }

        void push_back(const T& value) {
            auto new_node = new detail::Node<T>();
            new_node->value = value;
            new_node->prev = header.prev;
            new_node->next = &header;

            header.prev->next = new_node;
            header.prev = new_node;
        }

        void pop_back() {
            auto tmp = header.prev;

            header.prev->prev->next = &header;
            header.prev = header.prev->prev;

            delete tmp;
        }

        void clear() {

            auto tmp = &header;
            auto next = tmp->next;

            while (next != &header) {
                tmp = next;
                next = tmp->next;

                delete tmp;
            }

            create_header();
        }

        iterator begin() {
            return iterator(header.next);
        }

        const_iterator cbegin() const {
            return const_iterator(header.next);
        }

        iterator end() {
            return iterator(&header);
        }

        const_iterator cend() const {
            return const_iterator(&header);
        }

     private:

        void create_header() {
            header.prev = &header;
            header.next = &header;
        }

        detail::Node<T> header;
    };

    template<typename T>
    class Vector {
     public:
        using value = T;
        using reference = value&;
        using const_reference = const reference;

        Vector() = default;

        ~Vector() {
            delete data;
        }

        bool empty() const {
            return m_size == 0;
        }

        size_t capacity() const {
            return m_capacity;
        }

        reference operator[](int n) {
            return data[n];
        }

        void resize(int n) {
            m_capacity = n;

            if (m_capacity == 0) {
                m_capacity = 1;
            }

            const auto tmp_data = data;
            data = new T[m_capacity];

            if (tmp_data) {
                std::copy_n(tmp_data, m_capacity, data);
            }
        }

        void push_back(const T& value) {
            if (full()) {
                resize(2 * m_capacity);
            }

            data[m_size] = value;
            ++m_size;
        }

     private:
        bool full() const {
            return m_size == m_capacity;
        }

        T* data = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 0;
    };

}

#endif // CHP10_H