#ifndef CHP13_H
#define CHP13_H

#include <utility>

namespace keeler {

  namespace detail {

    struct node {
      node* p = nullptr;
      node* l = nullptr;
      node* r = nullptr;

      bool black = true; // TODO: change this to single bit
    };

  }

  template<typename Key, typename T>
  class RbTree {

   public:

    using size_type = std::size_t;
    using value_type = std::pair<const Key, T>;
    
    bool empty() const noexcept {
      return root == &nil;
    }

    size_type size() const noexcept {
      return m_sz;
    }

    void insert(const value_type& value) {

    }

   private:

    detail::node nil;
    detail::node* root = &nil;

    size_type m_sz = 0;
  };
}

#endif // CHP13_H
