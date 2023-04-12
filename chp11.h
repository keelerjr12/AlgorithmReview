#include <cstddef>
#include <functional>

namespace keeler {

  template<typename Key, typename T, typename Hash = std::hash<Key> >
  class UnorderedMap {
   public:
    
    bool empty() const {
      return size() == 0;
    }

    std::size_t size() const {
      return m_size;
    }

    void insert(const T& val) {
      if (empty()) {
        m_data = new T[10];
      }

      const auto hash = hasher(val);
      m_data[hash] = val;

      ++m_size;
    }

   private:

    std::size_t m_size = 0;
    T* m_data = nullptr;
    Hash hasher;
  };
}
