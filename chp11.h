#include <cstddef>
#include <functional>

namespace keeler {

  namespace detail {

    template<typename Value>
    struct HashNode {
      HashNode* m_next = nullptr;
      Value val;
      std::size_t hash_code;
    };

  }

  template <typename Value>
  class UnorderedMapIterator {

   public:
    UnorderedMapIterator(detail::HashNode<Value>* node) {
      m_node = node;
    }

    UnorderedMapIterator operator++() {
      m_node = m_node->m_next;
      return UnorderedMapIterator<Value>(m_node);
    }

    Value& operator*() {
      return m_node->val;
    }

    inline bool operator==(const UnorderedMapIterator<Value>& rhs) {
      return m_node == rhs.m_node;
    }

    inline bool operator!=(const UnorderedMapIterator<Value>& rhs) {
      return !(*this == rhs);
    }

   private:

    detail::HashNode<Value>* m_node;

  };

  template<typename Key, typename T, typename Hash = std::hash<Key> >
  class UnorderedMap {
   public:

    using value_type = std::pair<const Key, T>;
    using iterator = UnorderedMapIterator<value_type>;

    using hash_node = detail::HashNode<value_type>;
    
    bool empty() const {
      return size() == 0;
    }

    std::size_t size() const {
      return m_el_ct;
    }

    bool insert(const value_type& val) {
      if (empty()) {
        m_bkts = new hash_node*[10] { nullptr };
        m_bkt_ct = 10;
      }

      const auto hash = hasher(val.first);
      auto& bkt_ptr = m_bkts[hash % m_bkt_ct];

      auto new_begin = new hash_node { nullptr, val, hash  };

      if (bkt_ptr == nullptr) {
        new_begin->m_next = m_before_begin.m_next;

        if (m_before_begin.m_next) {
          auto& prev_begin_bkt_ptr = m_bkts[m_before_begin.m_next->hash_code % m_bkt_ct];
          prev_begin_bkt_ptr = new_begin;
        }

        m_before_begin.m_next = new_begin;
        bkt_ptr = &m_before_begin;

      } else {
        auto node = bkt_ptr->m_next;
        while (node && (node->hash_code == hash)) {
          if (node->val == val) {
            return true;
          }

          node = node->m_next;
        }

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

    hash_node m_before_begin;
    hash_node** m_bkts = nullptr;
    std::size_t m_bkt_ct = 1;
    std::size_t m_el_ct = 0;
    Hash hasher;
  };
}
