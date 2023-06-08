#ifndef MAP_ARRAY_HPP
#define MAP_ARRAY_HPP

#include <algorithm>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

template <typename Key, typename Value>
class MapArray {

public:

    using value_type = std::pair<Key, Value>;
    
    class ArrayIterator {

    public:
        
        // Iterator traits:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = MapArray::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr) : ptr(ptr) {}

        ArrayIterator& operator++() {
            
            ++ptr;
            return *this;
        }

        ArrayIterator& operator--() {

            --ptr;
            return *this;
        }

        ArrayIterator operator++(int) {
            
            ArrayIterator previous = *this;
            ++ptr;
            return previous;
        }

        ArrayIterator operator--(int) {

            ArrayIterator previous = *this;
            --ptr;
            return previous;
        }

        ArrayIterator& operator+=(difference_type d) {

            ptr += d;
            return *this;
        }

        ArrayIterator& operator-=(difference_type d) {

            ptr -= d;
            return *this;
        }

        friend ArrayIterator operator+(ArrayIterator it, difference_type d) {

            return it += d;
        }

        friend ArrayIterator operator+(difference_type d, ArrayIterator it) {

            return it + d;
        }

        friend ArrayIterator operator-(ArrayIterator it, difference_type d) {

            return it -= d;
        }

        friend difference_type operator-(ArrayIterator lhs, ArrayIterator rhs) {

            return lhs.ptr - rhs.ptr;
        }

        auto operator<=>(const ArrayIterator& other) const = default;

        std::pair<Key, Value>& operator*() const {
            
            return *ptr;
        }

        std::pair<Key, Value>* operator->() const {

            return &(*ptr);
        }

        std::pair<Key, Value>& operator[](difference_type d) const {

            return *(*this + d);
        }

    private:

        std::pair<Key, Value>* ptr;
    };

    using iterator = ArrayIterator;

    // Normally there would also be a const_iterator

    ArrayIterator begin() {

        return ArrayIterator(data.data());
    }

    ArrayIterator end() {

        return ArrayIterator(data.data() + data.size());
    }

    Value& operator[](const Key& key) {

        auto it = std::lower_bound(data.begin(), data.end(), key, [](const value_type& val, const Key& key) {return val.first < key;});
        if (it != data.end() && it->first == key) {
            return it->second;
        } else {
            it = data.insert(it, value_type(key, Value{}));
            return it->second;
        }
    }

private:

    std::vector<std::pair<Key, Value>> data;
    static_assert(std::random_access_iterator<iterator>);
};

#endif

