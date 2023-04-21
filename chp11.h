#include <cstddef>
#include <functional>

namespace keeler {

  namespace detail {

    template<typename T>
    struct HashNode {
      HashNode* m_next = nullptr;
      T val;
    };

    template<typename T>
    class Bucket {
     public:

      bool contains(const T& val) const {
        for (auto curr = m_node; curr != nullptr; ++curr) {
          if (curr->val == val) {
            return true;
          }
        }

        return false;
      }

      void insert(const T& val) {
        auto new_node = new HashNode<T>();
        new_node->val = val;

        if (m_node == nullptr) {
          m_node = new_node;
        } else {
          m_node->m_next = new_node;
        }

        ++m_size;
      }

     private:

      HashNode<T>* m_node = nullptr;
      std::size_t m_size = 0;
    };
  }

  template <typename T>
  class UnorderedMapIterator {

   public:
    UnorderedMapIterator(detail::HashNode<T>* node) {
      std::cout << node << std::endl;
      m_node = node;
    }

    UnorderedMapIterator operator++() {
      m_node = m_node->m_next;
      return UnorderedMapIterator<T>(m_node);
    }

    inline bool operator==(const UnorderedMapIterator<T>& rhs) {
      return m_node == rhs.m_node;
    }

    bool operator!=(const UnorderedMapIterator<T>& rhs) {
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

        const auto hash = hasher(val);
        m_bkts[hash % m_bkt_ct] = &m_before_begin;

        auto new_node = new detail::HashNode<T>();
        new_node->val = val;
        m_before_begin.m_next = new_node;

        ++m_el_ct;

      } else {

        const auto hash = hasher(val);
        const auto bkt = m_bkts[hash % m_bkt_ct];

        if (bkt == nullptr) {
          auto new_begin = new detail::HashNode<T>();
          new_begin->val = val;
          new_begin->m_next = &m_before_begin;
          m_before_begin = *new_begin;
          m_bkts[hash % m_bkt_ct] = &m_before_begin;
        } else {
          auto node = bkt->m_next;
          while (node && (hasher(node->val) == hash)) {
            if (node->val == val) {
              return true;
            }
            node = node->m_next;
          }
          auto new_begin = new detail::HashNode<T>();
          new_begin->val = val;
          new_begin->m_next = bkt;
          m_bkts[hash % m_bkt_ct] = new_begin;
        }
          
        ++m_el_ct;
      }

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
