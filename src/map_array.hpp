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
    using value_type = ???; //TODO
    class ArrayIterator {
    public:
        // Iterator traits:
        using iterator_category = ???; //TODO
        using value_type = ???; //TODO
        using difference_type = ???; //TODO
        using pointer = ???; //TODO
        using reference = ???; //TODO

        explicit ArrayIterator(std::pair<Key, Value>* ptr = nullptr);
        ArrayIterator& operator++();
        ArrayIterator& operator--();
        ArrayIterator operator++(int);
        ArrayIterator operator--(int);
        ArrayIterator& operator+=(difference_type d);
        ArrayIterator& operator-=(difference_type d);
        friend ArrayIterator operator+(ArrayIterator it, difference_type d);
        friend ArrayIterator operator+(differnece_type d, ArrayIterator it);
        friend ArrayIterator operator-(ArrayIterator it, differnece_type d);
        friend difference_type operator-(ArrayIterartor lhs, ArrayIterator rhs);
        auto operator<=>(const ArrayIterator& other) const = default;
        std::pair<Key, Value>& operator*() const;
        std::pair<Key, Value>* operator->() const;
        std::pair<Key, Value>& operator[](difference_type d) const;
    private:
        std::pair<Key, Value>* ptr;
    };
    using iterator = ArrayIterator;
    // Normally there would also be a const_iterator
    ArrayIterator begin();
    ArrayIterator end();
    Value& operator[](const Key& key);
private:
    std::vector<std::pair<Key, Value>> data;
    static_assert(std::random_access_iterator<iterator>);
};

#endif
