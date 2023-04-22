#include <cstddef>
#include <functional>

namespace keeler {

  namespace detail {

    template<typename T>
    struct HashNode {
      HashNode* m_next = nullptr;
      T val;
    };

  }

  template <typename T>
  class UnorderedMapIterator {

   public:
    UnorderedMapIterator(detail::HashNode<T>* node) {
      m_node = node;
    }

    UnorderedMapIterator operator++() {
      m_node = m_node->m_next;
      return UnorderedMapIterator<T>(m_node);
    }

    T& operator*() {
      return m_node->val;
    }

    inline bool operator==(const UnorderedMapIterator<T>& rhs) {
      return m_node == rhs.m_node;
    }

    inline bool operator!=(const UnorderedMapIterator<T>& rhs) {
      return !(*this == rhs);
    }

   private:

    detail::HashNode<T>* m_node;

  };

  template<typename Key, typename T, typename Hash = std::hash<Key> >
  class UnorderedMap {
   public:

    using iterator = UnorderedMapIterator<T>;
    
    bool empty() const {
      return size() == 0;
    }

    std::size_t size() const {
      return m_el_ct;
    }

    bool insert(const T& val) {
      if (empty()) {
        m_bkts = new detail::HashNode<T>*[10] { nullptr };
        m_bkt_ct = 10;
      }

      const auto hash = hasher(val);
      auto& bkt_ptr = m_bkts[hash % m_bkt_ct];

      if (bkt_ptr == nullptr) {
        auto new_begin = new detail::HashNode<T>();
        new_begin->val = val;
        new_begin->m_next = m_before_begin.m_next;

        if (m_before_begin.m_next) {
          auto& prev_begin_bkt_ptr = m_bkts[hasher(m_before_begin.m_next->val) % m_bkt_ct];
          prev_begin_bkt_ptr = new_begin;
        }

        m_before_begin.m_next = new_begin;
        bkt_ptr = &m_before_begin;

      } else {
        auto node = bkt_ptr->m_next;
        while (node && (hasher(node->val) == hash)) {
          if (node->val == val) {
            return true;
          }
          node = node->m_next;
        }

        auto new_begin = new detail::HashNode<T>();
        new_begin->val = val;
        new_begin->m_next = bkt_ptr->m_next;
        bkt_ptr->m_next = new_begin;
      }
      
      ++m_el_ct;

      return false;
    }

    iterator begin() {
      return iterator(m_before_begin.m_next);
    }

    iterator end() {
      return iterator(nullptr);
    }

   private:

    detail::HashNode<T> m_before_begin;
    detail::HashNode<T>** m_bkts = nullptr;
    std::size_t m_bkt_ct = 1;
    std::size_t m_el_ct = 0;
    Hash hasher;
  };
}
