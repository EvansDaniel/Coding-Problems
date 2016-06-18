//
// Created by daniel on 6/17/16.
//

#ifndef CPPTEST_SSL_H
#define CPPTEST_SSL_H

#include <algorithm>

template<typename T>
class SSL {

private:

    struct Node {
        T data;
        Node *next;

        Node(const T &d = T {}, Node *p = nullptr) : data{d}, next{p} { };

        Node(T &&d, Node *p = nullptr) : data{std::move(d)}, next{p} { };

    };

    Node *head;
    Node *sentinelNode;
    int len;

public:
    class const_iterator {
    public:
        const_iterator() : current{nullptr} { };

        const_iterator &operator++() {
            current = current->next;
            return *this;
        }

        const T &operator*() const {
            return retrieve();
        }

        const_iterator &operator++(int) {
            const_iterator old = *this;
            current = current->next;
            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const {
            return current != rhs.current;
        }


    protected:
        Node *current;

        const_iterator(Node *newNode) : current{newNode} { };

        T &retrieve() const {
            return current->data;
        }

        friend class SSL<T>;
    };

    class iterator : public const_iterator {
        iterator() { }

        T &operator*() {
            return const_iterator::retrieve();
        }

        const T &operator*() const {
            return const_iterator::operator*();
        }

        iterator &operator++() {
            this->current = this->current->next;
            return *this;
        }

        iterator &operator++(int) {
            iterator old = *this;
            this->current = this->current->next;
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator{p} { };


        friend class SSL<T>;

    };

public:
    SSL() {
        init();
    };

    // initializes and allocate memory for the two
    // sentinel nodes, head and tail; sets list length = 0
    void init() {
        len = 0;
        head = new Node;
        sentinelNode = new Node;
        // list is empty to start
        head->next = sentinelNode;
    }

    void push_front(const T &d) {
        //head->next = new Node(d,head->next);
        insert(begin(), d);
    }

    void push_front(T &&d) {
        insert(begin(), std::move(d));
    }

    // after init(
    iterator push_back(const T &d) {
        /*iterator itr;
        // go to the node just before the sentinel node
        for(itr = begin(); itr.current->next != sentinelNode; ++itr)
            ;
        // make it's current's next point to the new node,
        // make the new Node's next point to the sentinel node
        itr.current->next = new Node(d, sentinelNode);
        ++len;
        return itr;*/
        insert(sentinelNode, d);
    }

    iterator push_back(const T &&d) {
        return insert(sentinelNode, d);
    }

    void pop_front() {
        erase(begin());
    }

    // copy constructor
    SSL(const SSL &rhs) {
        init();
        // push_back returns an iterator containing a pointer to the new node
        // so it handles the iterating through rhs
        for (auto &x : rhs)
            push_back(x);
    }

    ~SSL() {
        clear();
    }


    SSL &operator=(SSL rhs) {
        std::swap(this->head, rhs.head);
        std::swap(this->sentinelNode, rhs.sentinelNode);
        std::swap(this->len, rhs.len);
        return *this;
    }

    // move constructor
    // double check this constructor
    SSL(SSL &&rhs) : len{std::move(rhs.len)}, head{std::move(rhs.head)}, sentinelNode{std::move(rhs.sentinelNode)} {
        rhs.len = 0;
        rhs.sentinelNode = nullptr;
        rhs.head = nullptr;
    }

    // move assignment operator
    SSL &operator=(SSL &&x) {
        std::swap(this->len, x.len);
        std::swap(this->head, x.head);
        std::swap(this->sentinelNode, x.sentinelNode);
        return *this;
    }

    iterator begin() {
        return head->next;
    }

    const_iterator begin() const {
        return head->next;
    }

    int size() const {
        return len;
    }

    bool empty() {
        return len == 0;
    }

    void clear() {
        for (iterator itr = begin(); len != 0;) {
            iterator i{itr};
            ++itr;
            erase(i);
        }
    }

    /**
     * @return iterator to the inserted node, or nullptr if the
     * the node specified by itr was not found in the list
     *
     * if itr.current is found in the list, insert inserts a new
     * node before itr.current
     */
    iterator insert(iterator itr, const T &d) {
        if (this->empty()) {
            head->next = new Node(d, sentinelNode);
            ++len;
            return head->next;
        }
        Node *p = head;
        while (p->next != itr.current) {
            p = p->next;
        }
        // we found the node they specified
        if (p->next == itr.current) {
            p->next = new Node(d, itr.current);
            ++len;
            return p->next;
        }
        // this means the node specified by itr doesn't exist in the list
        return nullptr;
    }

    bool erase(iterator itrToDel) {
        iterator itr = begin();
        if (itr.current == itrToDel.current) {
            head->next = itr.current->next;
            delete itrToDel.current;
            itrToDel = nullptr;
            --len;
            return true;
        }
        for (; itr.current != sentinelNode; ++itr) {
            if (itr.current->next == itrToDel.current) {
                // [CURR]-next->[DELETED]-next->[nextNext]
                // state after next line: [CURR]-next->[nextNext]
                itr.current->next = itr.current->next->next;
                itr.current = nullptr;
                delete itr.current;
                --len;
                return true;
            }
        }
        return false;
    }

/*    iterator erase ( iterator from, iterator to) {
        for(iterator itr = from; itr != to; )
            itr = erase(itr);
    }*/


    iterator end() {
        return sentinelNode;
    }

    const const_iterator end() const {
        return sentinelNode;
    }


    void print() {
        std::cout << "head->";
        for (iterator itr = begin(); itr.current != sentinelNode; ++itr)
            std::cout << *itr << "->";
        std::cout << "sNode\n\n";
    }


};

#endif //CPPTEST_SSL_H
