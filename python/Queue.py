# TODO: add more queue and deque operations as well as certain application functions
# implemented using an array (list in python) 
class Queue:
    def __init__(self, size):
        self.q = [-1 for _ in xrange(size)]
        self.head = 0
        self.tail = 0

    def enqueue(self, x):
        if (self.tail + 1) % len(self.q) == self.head:
            raise Exception('overflow')
        self.q[self.tail] = x
        self.tail += 1
        if self.tail == len(self.q):
            self.tail = 0

    def dequeue(self):
        if self.head == self.tail:
            raise Exception('underflow')
        x = self.q[self.head]
        self.head += 1
        if self.head == len(self.q):
            self.head = 0
        return x


class Dequeue:
    def __init__(self, size):
        self.q = [-1 for _ in xrange(size)]
        self.front = 0
        self.back = 0

    def push_front(self, x):
        if (self.back + 1) % len(self.q) == self.front:
            raise Exception('overflow')
        self.front -= 1
        if self.front == -1:
            self.front = len(self.q) - 1
        self.q[self.front] = x

    def push_back(self, x):
        if (self.back + 1) % len(self.q) == self.front:
            raise Exception('overflow')
        self.q[self.back] = x
        self.back += 1
        if self.back == len(self.q):
            self.back = 0

    def pop_front(self):
        if self.front == self.back:
            raise Exception('underflow')
        x = self.q[self.front]
        self.front += 1
        if self.front == len(self.q):
            self.front = 0
        return x

    def pop_back(self):
        if self.front == self.back:
            raise Exception('underflow')
        self.back -= 1
        if self.back == -1:
            self.back = len(self.q) - 1
        return self.q[self.back]
