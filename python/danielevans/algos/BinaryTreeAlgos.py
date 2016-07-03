class TreeNode:
    def __init__(self, key, left=None, right=None):
        self.key = key
        self.left = left
        self.right = right


class TreeNodeLeft:
    def __init__(self, key, parent=None, left=None, sibling=None):
        self.key = key
        self.parent = parent
        self.left = left
        self.sibling = sibling

    def set_parent(self, parent):
        self.parent = parent

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
# representation. -> wrote both print only left child tree funcitons for this
def print_only_left_child_tree_r(root):
    if root is not None:
        print root.key
        print_only_left_child_tree_r(root.left)
        print_only_left_child_tree_r(root.sibling)


def print_only_left_child_tree_i(node):
    if node is not None:
        while node.parent is not None:
            node = node.parent
        while node is not None:
            print(node.key)
            s = node.sibling
            while s is not None:
                print(s.key)
                s = s.sibling

            node = node.left
