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

    UnorderedMapIterator& operator++() {
      m_node = m_node->m_next;
      return *this;
    }

    Value& operator*() {
      return m_node->val;
    }

    Value* operator->() {
      return &m_node->val;
    }

    friend inline bool operator==(const UnorderedMapIterator<Value>& lhs, 
        const UnorderedMapIterator<Value>& rhs) {

      return lhs.m_node == rhs.m_node;
    }

    friend inline bool operator!=(const UnorderedMapIterator<Value>& lhs, 
        const UnorderedMapIterator<Value>& rhs) {

      return !(lhs == rhs);
    }

   private:

    detail::HashNode<Value>* m_node;

  };

  template <typename Value>
  class UnorderedMapLocalIterator {

   public:

    using size_type = std::size_t;

    explicit UnorderedMapLocalIterator(detail::HashNode<Value>* node, size_type bkt, size_type bkt_ct)
      : m_node(node), m_bkt(bkt), m_bkt_ct(bkt_ct) { }

    UnorderedMapLocalIterator& operator++() {
      m_node = m_node->m_next;

      if (m_node) {
        const auto next_node_bkt = m_node->hash_code % m_bkt_ct;
        if (next_node_bkt != m_bkt) {
          m_node = nullptr;
        }
      }

      return *this;
    }

    Value& operator*() {
      return m_node->val;
    }

    Value* operator->() {
      return &m_node->val;
    }

    friend inline bool operator==(const UnorderedMapLocalIterator<Value>& lhs, 
        const UnorderedMapLocalIterator<Value>& rhs) {

      return lhs.m_node == rhs.m_node;
    }

    friend inline bool operator!=(const UnorderedMapLocalIterator<Value>& lhs, 
        const UnorderedMapLocalIterator<Value>& rhs) {

      return !(lhs == rhs);
    }

   private:

    detail::HashNode<Value>* m_node;
    size_type m_bkt;
    size_type m_bkt_ct;
  };

  template<typename Key, typename T, typename Hash = std::hash<Key> >
  class UnorderedMap {
   public:

    using value_type = std::pair<const Key, T>;
    using iterator = UnorderedMapIterator<value_type>;
    using const_iterator = const UnorderedMapIterator<value_type>;
    using local_iterator = UnorderedMapLocalIterator<value_type>;
    using size_type = std::size_t;

    using hash_node = detail::HashNode<value_type>;

    ~UnorderedMap() {
      clear();
    }
    
    bool empty() const {
      return size() == 0;
    }

    size_type size() const {
      return m_el_ct;
    }

    iterator begin() {
      return iterator(m_before_begin.m_next);
    }

    iterator end() {
      return iterator(nullptr);
    }

    const_iterator cend() const {
      return const_iterator(nullptr);
    }

    local_iterator begin(size_type n) {
      auto bkt = m_bkts[n];
      return local_iterator(bkt->m_next, n, m_bkt_ct);
    }

    local_iterator end(size_type n) {
      return local_iterator(nullptr, n, m_bkt_ct);
    }

    void clear() noexcept {
      for (auto node = begin_node(); node; /* empty */) {
        const auto next_node = node->m_next;
        delete node;

        node = next_node;
      }

      delete [] m_bkts;
      m_bkts = nullptr;
    }

    // TODO: This needs major refactoring!
    bool insert(const value_type& val) {
      if (empty()) {
        m_bkts = new hash_node*[10] { nullptr };
        m_bkt_ct = 10;
      }

      const auto bkt = bkt_idx(val.first);
      auto& bkt_ptr = m_bkts[bkt];

      const auto hash = hasher(val.first);
      auto new_begin = new hash_node { nullptr, val, hash  };

      if (!bkt_ptr) {
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

    iterator find(const Key& key) {
      const auto node = find_node(key);
      return iterator(node);
    }

    const_iterator find(const Key& key) const {
      const auto node = find_node(key);
      return const_iterator(node);
    }

    bool contains(const Key& key) const {
      return find(key) != cend();
    }

   private:

    hash_node* begin_node() const {
      return m_before_begin.m_next;
    }

    size_type bkt_idx(const Key& key) const {
      const auto hash = hasher(key); 
      return hash % m_bkt_ct;
    }

    hash_node* find_node(const Key& key) const {
      const auto bkt = bkt_idx(key);
      auto begin = m_bkts[bkt];

      if (!begin) {
        return nullptr;
      }

      // TODO: This needs major refactoring!
      const auto hash = hasher(key);
      for (auto node = begin->m_next; node && (node->hash_code % m_bkt_ct == hash % m_bkt_ct); node = node->m_next) {

        if (node->val.first == key) {
          return node;
        }
      }
      
      return nullptr;
    }

    hash_node m_before_begin;
    hash_node** m_bkts = nullptr;
    std::size_t m_bkt_ct = 1;
    std::size_t m_el_ct = 0;
    Hash hasher;
  };
}
