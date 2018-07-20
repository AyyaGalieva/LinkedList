#include <iostream>

typedef int value_type;

namespace MyList {
    class LinkedList {
        struct Node {
            value_type data;
            Node* next;
            Node* prev;
        };
        int count;
        Node *endptr;
    public:
        LinkedList();
        LinkedList(const LinkedList & other);
        LinkedList(LinkedList && other);

        ~LinkedList();

        class iterator {
            Node *ptr;
            iterator(Node *x) : ptr(x) {}
        public:
            iterator & operator=(const iterator & other);
            bool operator!=(const iterator & other) const;
            bool operator==(const iterator & other) const;
            value_type & operator*() const;
            value_type * operator->() const;
            iterator & operator++();
            iterator operator++(int);
            iterator & operator--();
            iterator operator--(int);

            friend class LinkedList;
        };

        class const_iterator {
            Node *ptr;
            const_iterator(Node *x) : ptr(x) {}
        public:
            const_iterator & operator=(const const_iterator & other);
            bool operator!=(const const_iterator & other) const;
            bool operator==(const const_iterator & other) const;
            const value_type & operator*() const;
            const value_type * operator->() const;
            const_iterator & operator++();
            const_iterator operator++(int);
            const_iterator & operator--();
            const_iterator operator--(int);

            friend class LinkedList;
        };

        LinkedList & operator=(const LinkedList & other);
        LinkedList & operator=(LinkedList && other);

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        int size() const;
        bool empty() const;

        value_type & front();
        const value_type & front() const;
        value_type & back();
        const value_type & back() const;

        iterator erase(iterator position);
        iterator erase(iterator begin, iterator end);
        int remove(const value_type & value);
        void clear();

        void pop_back();
        void pop_front();
        void push_back(const value_type & value);
        void push_front(const value_type & value);
        iterator insert(iterator before, const value_type & value);

        LinkedList & operator+=(const LinkedList & other);
        friend bool operator!=(const LinkedList & left, const LinkedList & right);
        friend bool operator==(const LinkedList & left, const LinkedList & right);
    };

    LinkedList operator+(const LinkedList & left, const LinkedList & right);
}