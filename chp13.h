#ifndef CHP13_H
#define CHP13_H

#include <utility>

#include <iostream>

namespace keeler {

  namespace detail {

    template <typename Value>
    struct node {
      node* p = nullptr;
      node* l = nullptr;
      node* r = nullptr;

      Value value;

      bool black = false;
    };

  }
  
  template <typename Value>
  class TreeIterator {
   public:

    TreeIterator(detail::node<Value>* node) : m_node(node) { }

    Value& operator*() {
      return m_node->value;
    }

    Value* operator->() {
      return &m_node->value;
    }

    TreeIterator<Value> operator++() {
      if (m_node->r) { 
        m_node = m_node->r;

        for (auto curr = m_node; curr; curr = curr->l) {
          m_node = curr;
        }

      } else {
        while (m_node && m_node->p &&  m_node->p->r == m_node) {
          m_node = m_node->p;
        }

        m_node = m_node->p;
      }

      return *this;
    }

    friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs) {
      return lhs.m_node == rhs.m_node;
    }

    friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs) {
      return !(lhs == rhs);
    }

   private:

    detail::node<Value>* m_node;
  };

  template<typename Key, typename T>
  class RbTree {

   public:

    using size_type = std::size_t;
    using value_type = std::pair<const Key, T>;
    using iterator = TreeIterator<value_type>;

    iterator begin() noexcept {
      detail::node<value_type>* left_node = nullptr;

      for (auto curr = root; curr; curr = curr->l) {
        left_node = curr;
      }

      return iterator(left_node);
    }

    iterator end() noexcept {
      return iterator(nullptr);
    }
    
    bool empty() const noexcept {
      return root == nullptr;
    }

    size_type size() const noexcept {
      return m_sz;
    }

    void insert(const value_type& value) {
      const auto new_node = new detail::node<value_type> {nullptr, nullptr, nullptr, value, false };

      //find insert point
      auto curr = root;
      detail::node<value_type>* parent = nullptr;

      while (curr) {
        parent = curr;
        if (value.first <= curr->value.first) {
          curr = curr->l;
        } else {
          curr = curr->r;
        }
      }

      if (parent) {
        if (value.first <= parent->value.first) {
          parent->l = new_node;
        } else {
          parent->r = new_node;
        }
      }

      new_node->p = parent;
      
      //handle root
      if (empty()) {
        root = new_node;
      }

      ++m_sz;
    }

   private:

    detail::node<value_type>* root = nullptr;

    size_type m_sz = 0;
  };
}

#endif // CHP13_H
