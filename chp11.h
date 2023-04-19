#include <cstddef>
#include <functional>

namespace keeler {

  namespace detail {

    template<typename T>
    struct HashNode {
      HashNode* m_next;
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

  class UnorderedMapIterator {

  };

  template<typename Key, typename T, typename Hash = std::hash<Key> >
  class UnorderedMap {
   public:

    using iterator = UnorderedMapIterator;
    
    bool empty() const {
      return size() == 0;
    }

    std::size_t size() const {
      return m_el_ct;
    }

    bool insert(const T& val) {
      if (empty()) {
        m_bkts = new detail::Bucket<T>[10];
        m_bkt_ct = 10;
      }

      const auto hash = hasher(val);
      const auto bkt = m_bkts[hash % m_bkt_ct];

      if (bkt.contains(val)) {
        return true;
      }

      m_bkts[hash % m_bkt_ct].insert(val);
      ++m_el_ct;

      return false;
    }

    iterator begin() {
      return UnorderedMapIterator();
    }

   private:

    detail::Bucket<T>* m_bkts = nullptr;
    std::size_t m_bkt_ct = 1;
    std::size_t m_el_ct = 0;
    Hash hasher;
  };
}
