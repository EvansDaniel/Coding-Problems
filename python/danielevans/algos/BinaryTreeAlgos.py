class TreeNode:
    def __init__(self, value, parent=None, left=None, right=None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def set_parent(self, parent):
        self.parent = parent


class TreeNodeLeft:
    def __init__(self, key, parent=None, left=None, sibling=None):
        self.key = key
        self.parent = parent
        self.left = left
        self.sibling = sibling

    def set_sibling(self, sibling):
        self.sibling = sibling


# O(n) recursive procedure that, given an n-node binary tree
# prints the key of each node in the tree
def print_tree(root):
    # using node as a temp causes O(n)
    # storage from the recursions
    if root is not None:
        # print root.key -> for pre order traversal
        print root.key
        # call print tree on the left and right child
        print "<--"
        print_tree(root.left)
        # print root.key -> for in order traversal
        print "-->"
        print_tree(root.right)
        # print root.key -> for post order traversal


# prints tree using an auxiliary stack structure
def print_tree_non_recursive(node):
    stack = [node]
    while len(stack) > 0:
        node = stack[-1]
        # 'pop' last element off the end of the stack
        del stack[-1]
        # stopping condition for when a null object is added
        # to the stack below. Otherwise, appending below causes looping to continue
        if node is not None:
            print(node.key)
            # prints pre order, swap left and right
            stack.append(node.right)
            # add left last, so that it is the first one popped
            stack.append(node.left)


# Write an O(n)-time procedure that prints all the keys of an arbitrary
# rooted tree with n nodes, where the tree is stored using the left-child, right-sibling
# representation. -> wrote both print only left child tree functions for this
def print_only_left_child_tree_r(root):
    if root is not None:
        print root.key
        print_only_left_child_tree_r(root.left)
        print_only_left_child_tree_r(root.sibling)


def print_only_left_helper(node):
    print(node.key)
    s = node.sibling
    while s is not None:
        print(s.key)
        if node.left is not None:
            print_only_left_helper(s.left)
        s = s.sibling


def print_only_left_child_tree_i(node):
    if node is not None:
        while node.parent is not None:
            node = node.parent
        while node is not None:
            print_only_left_helper(node)
            node = node.left


# a non-recursive constant storage O(n) algorithm for printing a binary tree
# NOTE: I define 'normal traversal' as prev being the parent of whatever node points to
def print_t(node):
    # prev points to the node that node was previously at
    prev = None
    while node is not None:
        # normal traversal of the tree is happening
        if node.parent == prev:
            print(node.value)
            prev = node
            # if left child null, if this occurs the next iteration will cause the
            # elif portion of the code to run
            if node.left is None:
                node = node.parent
            else:
                # continues normal traversal
                node = node.left
        # if node.left was at some point null, because at this point we have gone
        # back to the parent; that is the only way for prev to be left child of node
        elif node.left == prev:
            prev = node
            # we came back to the parent to see if it had a right child, if not
            # go to the parent
            if node.right is None:
                node = node.parent
            else:
                # begin normal traversal of the node.right subtree
                node = node.right
        else:
            # getting here indicates that prev is == node.right, meaning that
            # the only thing left to do is go back to the parent of node
            # and see if there is a right child subtree to print
            prev = node
            node = node.parent
