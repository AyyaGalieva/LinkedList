#include "MyList.h"

namespace MyList
{
    LinkedList::LinkedList() {
        endptr = new Node;
        endptr->next = endptr;
        endptr->prev = endptr;
        count = 0;
    }
    LinkedList::LinkedList(const LinkedList & other) {
        endptr = new Node;
        endptr->next = endptr;
        endptr->prev = endptr;
        count = 0;
        for (const value_type &v : other) {
            insert(end(), v);
        }
    }
    LinkedList::LinkedList(LinkedList && other) {
        count = 0;
        endptr = new Node;
        endptr->next = endptr;
        endptr->prev = endptr;
        std::swap(endptr, other.endptr);
        std::swap(count ,other.count);
    }

    LinkedList::~LinkedList() {
        clear();
        delete endptr;
    }

    LinkedList::iterator & LinkedList::iterator::operator=(const iterator & other) {
        if (this != &other) {
            ptr = other.ptr;
        }
        return *this;
    }
    bool LinkedList::iterator::operator!=(const iterator & other) const {
        return other.ptr != ptr;
    }
    bool LinkedList::iterator::operator==(const iterator & other) const {
        return other.ptr == ptr;

    }
    value_type & LinkedList::iterator::operator*() const {
        return ptr->data;
    }
    value_type * LinkedList::iterator::operator->() const {
        return &ptr->data;
    }

    LinkedList::iterator & LinkedList::iterator::operator++() {
        ptr = ptr->next;
        return *this;
    }
    LinkedList::iterator LinkedList::iterator::operator++(int) {
        iterator tmp(ptr);
        ptr = ptr->next;
        return tmp;
    }
    LinkedList::iterator & LinkedList::iterator::operator--() {
        ptr = ptr->prev;
        return *this;
    }
    LinkedList::iterator LinkedList::iterator::operator--(int) {
        iterator tmp(ptr);
        ptr = ptr->prev;
        return tmp;
    }

    LinkedList::const_iterator & LinkedList::const_iterator::operator=(const const_iterator & other) {
        if (this != &other) {
            ptr = other.ptr;
        }
        return *this;
    }
    bool LinkedList::const_iterator::operator!=(const const_iterator & other) const {
        return other.ptr != ptr;
    }
    bool LinkedList::const_iterator::operator==(const const_iterator & other) const {
        return other.ptr == ptr;
    }
    const value_type & LinkedList::const_iterator::operator*() const {
        return ptr->data;
    }
    const value_type * LinkedList::const_iterator::operator->() const {
        return &ptr->data;
    }

    LinkedList::const_iterator & LinkedList::const_iterator::operator++() {
        ptr = ptr->next;
        return *this;
    }
    LinkedList::const_iterator LinkedList::const_iterator::operator++(int) {
        const_iterator tmp(ptr);
        ptr = ptr->next;
        return tmp;
    }
    LinkedList::const_iterator & LinkedList::const_iterator::operator--() {
        ptr = ptr->prev;
        return *this;
    }
    LinkedList::const_iterator LinkedList::const_iterator::operator--(int) {
        const_iterator tmp(ptr);
        ptr = ptr->prev;
        return tmp;
    }

    LinkedList & LinkedList::operator=(const LinkedList & other) {
        if (this != &other) {
            clear();
            for (iterator i = other.endptr->next; i != other.endptr; i++) {
                insert(endptr, i.ptr->data);
            }
        }
        return *this;
    }
    LinkedList & LinkedList::operator=(LinkedList && other) {
        std::swap(endptr, other.endptr);
        std::swap(count ,other.count);
        return *this;
    }

    LinkedList::iterator LinkedList::begin() {
        return iterator(endptr->next);
    }
    LinkedList::const_iterator LinkedList::begin() const {
        return const_iterator(endptr->next);
    }
    LinkedList::const_iterator LinkedList::cbegin() const {
        return const_iterator(endptr->next);
    }
    LinkedList::iterator LinkedList::end() {
        return iterator(endptr);
    }
    LinkedList::const_iterator LinkedList::end() const {
        return const_iterator(endptr);
    }
    LinkedList::const_iterator LinkedList::cend() const {
        return const_iterator(endptr);
    }

    int LinkedList::size() const {
        return count;
    }
    bool LinkedList::empty() const {
        return (count == 0);
    }

    value_type & LinkedList::front() {
        return begin().ptr->data;
    }
    const value_type & LinkedList::front() const {
        return cbegin().ptr->data;
    }
    value_type & LinkedList::back() {
        return end().ptr->prev->data;
    }
    const value_type & LinkedList::back() const {
        return cend().ptr->prev->data;
    }

    LinkedList::iterator LinkedList::erase(iterator position) {
        if (position == end())
            return end();
        (position.ptr->prev)->next = position.ptr->next;
        (position.ptr->next)->prev = position.ptr->prev;
        iterator tmp = position;
        ++tmp;
        delete position.ptr;
        --count;
        return tmp;
    }
    LinkedList::iterator LinkedList::erase(iterator begin, iterator end) {
        for (iterator i = begin; i != end;)
            i = erase(i);
        return end;
    }

    int LinkedList::remove(const value_type & value) {
        int count = 0;
        for (iterator i = begin(); i != end();) {
            if (*i != value) i++;
            else{
                i = erase(i);
                count++;
            }
        }
        return count;
    }
    void LinkedList::clear() {
        erase(begin(), end());
    }

    void LinkedList::pop_back() {
        erase(end().ptr->prev);
    }
    void LinkedList::pop_front() {
        erase(begin());
    }
    void LinkedList::push_back(const value_type & value) {
        insert(end(), value);
    }
    void LinkedList::push_front(const value_type & value) {
        insert(begin(), value);
    }
    LinkedList::iterator LinkedList::insert(iterator before, const value_type & value) {
        Node *newnode = new Node;
        newnode->data = value;
        newnode->next = before.ptr;
        newnode->prev = before.ptr->prev;
        (newnode->prev)->next = newnode;
        (newnode->next)->prev = newnode;
        ++count;
        return iterator(endptr);
    }

    LinkedList & LinkedList::operator+=(const LinkedList & other) {
        for (auto item : other) {
            insert(end(), item);
        }
        return *this;
    }

    bool operator!=(const LinkedList & left, const LinkedList & right) {
        return !(left == right);
    }

    bool operator==(const LinkedList & left, const LinkedList & right) {
        if (left.size() != right.size())
            return false;
        LinkedList::const_iterator j = right.begin();
        for (LinkedList::const_iterator i = left.begin(); i != left.end(); i++) {
            if (*i != *j)
                return false;
            j++;
        }
        return true;
    }

    LinkedList operator+(const LinkedList & left, const LinkedList & right) {
        LinkedList merge(left);
        return merge += right;
    }
}