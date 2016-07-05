#include <algorithm>

template<typename Object>
class List {
private:
    /**
     *      Node struct that contains data of some type, pointer to previous node
     *      and pointer to the next node in the list
     */
    struct Node {
        Object data;
        Node *prev;
        Node *next;

        // constructor for the Node struct, Object {} initializes d with default constructor of Object
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
                : data{d}, prev{p}, next{n} { }


        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
                : data{std::move(d)}, prev{p}, next{n} { }
    };

    // number of nodes in list
    int theSize;
    // reference to the head sentinel node
    Node *head;
    // reference to the last node in list
    Node *tail;

public:
    class const_iterator {
    public:
        const_iterator() : current{nullptr} { }

        // returns the data at current
        const Object &operator*() const { return retrieve(); }

        // advances the iterator forward
        // TODO: go backward too
        const_iterator &operator++() {
            current = current->next;
            return *this;
        }

        // postfix ++ - advances iterator forward
        const_iterator operator++(int) {
            // save the old copy of the iterator
            const_iterator old = *this;
            ++(*this);
            // return the old copy after advancing the iterator forward
            return old;
        }

        // returns true if the this iterator's current node matches rhs's current node
        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        // does the opposite of ==
        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        // Node at the iterator's current position
        Node *current;

        // return lvalue reference to current's data
        Object &retrieve() const { return current->data; }

        // constructor to initialize const_iterator with pointer to Node
        const_iterator(Node *p) : current{p} { }

        // needs to be a friend to access its members such as current or
        friend class List<Object>;
    };

    // everything an const_iterator is but non-const
    class iterator : public const_iterator {
    public:
        iterator() { }

        Object &operator*() { return const_iterator::retrieve(); }

        const Object &operator*() const { return const_iterator::operator*(); }

        iterator &operator++() {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator{p} { }

        friend class List<Object>;
    };

public:
    // initializes the previous node, next node, head and tail nodes, and puts theSize == 0
    List() { init(); }

    // removes and deallocates all the nodes in the list, including the sentinel nodes, head and tail
    ~List() {
        clear();
        delete head;
        delete tail;
    }

    // copy constructor that uses the push back method to avoid low-level pointer manipulation
    List(const List &rhs) {
        init();
        for (auto &x : rhs)
            push_back(x);
    }

    // passes list by reference, copies it, and swaps *this with the copy
    List &operator=(const List &rhs) {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // move constructor, initializes the node with the rvalue reference
    // allowed to perform the move since rhs is about to be destroyed
    List(List &&rhs)
            : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    // move assignment operator, we 'steal' rhs's member variables before it gets destroyed
    // and return the new version of *this
    List &operator=(List &&rhs) {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);

        return *this;
    }

    // returns the iterator whose current node is set to the first node
    // in the list in the list; note that head is a sentinel node providing
    // a reference to the first node in the list
    iterator begin() {
        return {head->next};
    }

    // returns a const_iterator whose current member is set to the first node in the list
    const_iterator begin() const {
        return {head->next};
    }

    // returns an iterator whose current member is set to the tail sentinel node, which
    // is 'out-of-bounds' i.e. it is the link to the last node in the list
    iterator end() {
        return {tail};
    }

    // same as other end but a const_iterator
    const_iterator end() const {
        return {tail};
    }

    // returns length of the list
    int size() const {
        return theSize;
    }

    // true if the list is empty
    bool empty() const {
        return size() == 0;
    }

    // destroys all the nodes in the list
    void clear() {
        while (!empty())
            pop_front();
    }

    // returns an lvalue reference to the data in the first node in the list -
    // calls retrieve on the first node in the list
    Object &front() {
        return *begin();
    }

    // returns a const lvalue refernce but otherwise same as the other front
    const Object &front() const {
        return *begin();
    }

    // returns lvalue reference to the data contained in the last node in the list
    Object &back() {
        return *--end();
    }

    // same as other back but returns a const lvalue reference
    const Object &back() const {
        return *--end();
    }

    // @param x data to place into the new node
    // inserts the node at the front of the list
    void push_front(const Object &x) {
        insert(begin(), x);
    }

    // moves the data from the rvalue reference
    // into the new node, inserts it at the front
    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }

    // same as push_front(const Object&), but inserted at the back
    void push_back(const Object &x) {
        insert(end(), x);
    }

    // same as push_front(Object&&), but inserted at the back
    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    // removes the first node in the list
    void pop_front() {
        erase(begin());
    }

    // removes the last node in the list
    // O(1) operation because we maintain a reference to the previous node as well
    // as reference to the last node in the list
    void pop_back() {
        erase(--end());
    }

    // inserts node containing x before itr
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    // Insert x before itr.
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        theSize++;
        return p->prev = p->prev->next
                = new Node{std::move(x), p->prev, p};
    }


    // Erase item at itr.
    iterator erase(iterator itr) {
        Node *p = itr.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;

        return retVal;
    }

    // erases nodes from 'from' to 'to'
    // returns an iterator with current member pointing to 'to'
    iterator erase(iterator from, iterator to) {
        for (iterator itr = from; itr != to;)
            itr = erase(itr);

        return to;
    }

    // allocate memory for nodes, pointers to the first node in list,
    // set size to 0
    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};
