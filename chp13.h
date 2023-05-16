#ifndef CHP13_H
#define CHP13_H

#include <cstddef>
#include <utility>

#include <iostream>

namespace keeler {

  namespace detail {

    enum class Color {
      RED,
      BLACK
    };

    template <typename Value>
    struct node {
      node* p = nullptr;
      node* l = nullptr;
      node* r = nullptr;

      Value value;

      Color color = Color::RED;
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

    friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs) {
      return lhs.m_node == rhs.m_node;
    }

    friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs) {
      return !(lhs == rhs);
    }

   protected:
    
    detail::node<Value>*& get_node() {  return m_node; }

   private:

    detail::node<Value>* m_node;
  };
  
  template <typename Value>
  class PreorderTreeIterator : public TreeIterator<Value> {
   public:

    using size_type = std::size_t;

    PreorderTreeIterator(detail::node<Value>* node) : TreeIterator<Value> {node} { }

    PreorderTreeIterator<Value> operator++() {
      auto& node = this->get_node();

      if (node->l) { 
        node = node->l;

      } else {
        while (node && node->p && node->p->l == node) {
          node = node->p;
          --m_depth;
        }

        node = node->r;
      }

      ++m_depth;

      return *this;
    }

    size_type depth() const { return m_depth; }

    detail::Color color() { return this->get_node()->color; }

   private:

    size_type m_depth = 0;

  };

  template <typename Value>
  class InorderTreeIterator : public TreeIterator<Value> {
   public:

    InorderTreeIterator(detail::node<Value>* node) : TreeIterator<Value> {node} { }

    InorderTreeIterator<Value> operator++() {
      auto& node = this->get_node();

      if (node->r) { 
        node = node->r;

        for (auto curr = node; curr; curr = curr->l) {
          node = curr;
        }

      } else {
        while (node && node->p && node->p->r == node) {
          node = node->p;
        }

        node = node->p;
      }

      return *this;
    }

  };


  template<typename Key, typename T>
  class RbTree {

   public:

    using size_type = std::size_t;
    using value_type = std::pair<const Key, T>;
    using iterator = InorderTreeIterator<value_type>;
    using preorder_iterator = PreorderTreeIterator<value_type>;

    using node = detail::node<value_type>;
    using node_ptr = node*;

    iterator begin() noexcept {
      node_ptr left_node = nullptr;

      for (auto curr = root; curr; curr = curr->l) {
        left_node = curr;
      }

      return iterator(left_node);
    }

    iterator end() noexcept {
      return iterator(nullptr);
    }

    preorder_iterator preorder_begin() noexcept {
      return preorder_iterator(root);
    }

    preorder_iterator preorder_end() noexcept {
      return preorder_iterator(nullptr);
    }
    
    bool empty() const noexcept {
      return root == nullptr;
    }

    size_type size() const noexcept {
      return m_sz;
    }

    void insert(const value_type& value) {
      const auto new_node = new node {nullptr, nullptr, nullptr, value, detail::Color::RED };

      auto parent = find_parent_of(value);

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

      insert_fixup(new_node);

      ++m_sz;
    }

   private:

    node_ptr find_parent_of(const value_type& value) const noexcept {
      auto curr = root;
      node_ptr parent = nullptr;

      while (curr) {
        parent = curr;
        if (value.first <= curr->value.first) {
          curr = curr->l;
        } else {
          curr = curr->r;
        }
      }

      return parent;
    }

    void insert_fixup(node_ptr x) {
      while (x) {
        if (x->p && x->p->p && x->p->p->r && x->p->p->r->color == detail::Color::RED) {
          std::cout << "HERE\n";
          x->p->color = detail::Color::BLACK;
          x->p->p->r->color = detail::Color::BLACK;
          x->p->p->color = detail::Color::RED;
          x = x->p->p;
        }
      }
    }

    node_ptr root = nullptr;
    size_type m_sz = 0;
  };
}

#endif // CHP13_H
