class LinkListNode:
    def __init__(self, key):
        self.key = key
        self.next = None
        self.prev = None


class LinkList:
    def __init__(self):
        self.nil = LinkListNode(None)
        self.nil.next = self.nil
        self.nil.prev = self.nil

    def insert(self, x):
        x = LinkListNode(x)
        x.next = self.nil.next
        x.prev = self.nil
        x.next.prev = x
        x.prev.next = x

    def search(self, k):
        self.nil.key = k
        x = self.nil.next
        while x.key != k:
            x = x.next
        if x == self.nil:
            return None
        return x

    def union(self, list2):
        # make the first node of self point to last node of list2
        self.nil.next.prev = list2.nil.prev
        # make last node of list2 point to the first node of self
        list2.nil.prev.next = self.nil.next
        # make self.nil.next point to first node in list2
        self.nil.next = list2.nil.next
        # make the previous pointer of the first node of list2 point to self.nil
        list2.nil.next.prev = self.nil
        # list2 has now been appended to the front of self


# turns a linked list into a list (or dynamic array)
def to_list(head):
    values = []
    head = head.next
    while head is not None:
        # add to the array
        values.append(head.value)
        # traverse to next node in the list
        head = head.next
    return values


# reverse a singly linked list in theta(n) time using constant storage
def reverse(head):
    # pointer to previous node
    prev = None
    # pointer to the current node
    node = head
    while node is not None:
        next_node = node.next
        # reverse the next pointers
        node.next = prev
        # reset the previous to be the current node
        prev = node
        # make next node be the current node
        node = next_node
    # need to reset the head reference to be what was the end of the list; it is now
    # the beginning of the list
    head = prev
