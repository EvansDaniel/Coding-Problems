import sys


class LinkListNode:
    def __init__(self, key):
        self.key = key
        self.next = None


class MergeableHeapSorted:
    def __init__(self):
        self.head = None

    # insert element into heap
    def insert(self, value):
        new_node = LinkListNode(value)
        if self.head is None:
            self.head = new_node
        else:
            if value < self.head.key:
                new_node.next = self.head
                self.head = new_node
            else:
                x = self.head
                # iterate through list til end or til the next node's key
                #  is bigger than value
                while x.next is not None and x.next.key < new_node.key:
                    x = x.next
                # add new node to the right place
                new_node.next = x.next
                x.next = new_node

    def minimum(self):
        if self.head is None:
            return None
        return self.head.key

    def extract_min(self):
        if self.head is None:
            return None
        node = self.head
        self.head = self.head.next
        return node.key

    def get_head(self):
        return self.head

    def union(self, other):
        other_head = other.head
        if self.head is None:
            if other_head is None:
                return None
            else:
                return other_head
        if other_head is None:
            return self.head
        # - - - - - - - - - - - - - - -
        node = self.head
        while node.next is not None and other_head is not None:
            if node.next.key >= other_head.key:
                o_head = other_head.next
                other_head.next = node.next
                node.next = other_head
                other_head = o_head
            node = node.next
        # append the rest of the other_head list if any is left
        if other_head is not None:
            node.next = other_head

    def print_list(self):
        node = self.head
        while node is not None:
            print node.key
            node = node.next


class MergeableHeapUnsorted:
    def __init__(self):
        self.head = None
        self.min = sys.maxint

    # insert element into heap
    def insert(self, value):
        if value < self.min:
            self.min = value

        new_node = LinkListNode(value)
        if self.head is None:
            self.head = new_node
        else:
            new_node.next = self.head.next
            self.head.next = new_node

    def minimum(self):
        return self.min

    def extract_min(self):
        node = self.head
        min_node_pointer = node
        while node.next is not None:
            if self.min == node.next.key:
                min_node_pointer = node
            node = node.next
        if min_node_pointer is self.head:
            self.head = self.head.next
        else:
            min_node_pointer.next = min_node_pointer.next.next
        return self.min

    def union(self, other):
        node = self.head
        while node.next is not None:
            node = node.next
        node.next = other.head

    def print_list(self):
        node = self.head
        while node is not None:
            print node.key
            node = node.next
