#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {

    struct ListNode {

        T data;
        std::shared_ptr<ListNode> next;
    };

public:

    using value_type = T;

    class ListIterator {

    public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = SetList::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr) : ptr(ptr){}

        ListIterator& operator++() {

            if (ptr != nullptr) ptr = ptr->next;
            return *this;
        }

        ListIterator operator++(int) {

            ListIterator temp = *this;
            ++(*this);
            return temp;
        }

        T& operator*() const {

            return ptr->data;
        }

        T* operator->() const {

            return &(ptr->data);
        }

        bool operator==(const ListIterator& other) const = default;

    private:

        std::shared_ptr<ListNode> ptr;
    };

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng), std::bind_front(&SetList::insert, this));
    }

    ListIterator begin() {

        return ListIterator(head);
    }

    ListIterator end() {

        return ListIterator(nullptr);
    }

    bool contains(T const& value) {

        std::shared_ptr<ListNode> current = head;
        while (current != nullptr) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    ListIterator insert(T value) {
        if (contains(value)) return ListIterator(nullptr);
        std::shared_ptr<ListNode> new_node = std::make_shared<ListNode>(value);
        new_node->next = head;
        head = new_node;
        return ListIterator(new_node);
    }

private:

    using iterator = ListIterator;

    static_assert(std::forward_iterator<iterator>);

    // Normally there would be a const_iterator too

    std::shared_ptr<ListNode> head = nullptr;
};

#endif
