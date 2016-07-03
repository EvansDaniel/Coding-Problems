from python.danielevans.algos.BinaryTreeAlgos import TreeNode, print_t


def print_tree_demo():
    r1 = TreeNode("r1")
    r2 = TreeNode("r2")
    r3 = TreeNode("r3")
    right = TreeNode("right", None, r3)
    left = TreeNode("left", None, r1, r2)
    root = TreeNode("root", None, left, right)

    right.set_parent(root)
    left.set_parent(root)
    r1.set_parent(left)
    r2.set_parent(left)
    r3.set_parent(right)

    print_t(root)


print_tree_demo()
