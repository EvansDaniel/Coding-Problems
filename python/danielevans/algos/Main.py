from python.danielevans.algos.BinaryTreeAlgos import TreeNodeLeft, print_only_left_child_tree_i


def print_tree_demo():
    s2 = TreeNodeLeft("s2", None)
    s1 = TreeNodeLeft("s1", None, None, s2)
    leftChild = TreeNodeLeft("leftChild", None, None, s1)
    ls2 = TreeNodeLeft("ls2", None, s2)
    ls1 = TreeNodeLeft("ls1", None, s2, ls2)
    left = TreeNodeLeft("left", None, leftChild, ls1)
    root = TreeNodeLeft("root", None, left)

    s2.set_parent(left)
    s1.set_parent(left)
    leftChild.set_parent(left)
    ls2.set_parent(root)
    left.set_parent(root)
    ls1.set_parent(root)
    print_only_left_child_tree_i(root)


print_tree_demo()
