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

    bool insert(const T& val) {
      if (empty()) {
        m_data = new T[10];
      }

      const auto hash = hasher(val);
      const auto stored = m_data[hash];

      if (stored == val) {
        return true;
      }

      m_data[hash] = val;
      ++m_size;
      return false;
    }

   private:

    std::size_t m_size = 0;
    T* m_data = nullptr;
    Hash hasher;
  };
}
