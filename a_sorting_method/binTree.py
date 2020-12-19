class binTreeNode():
    def __init__(self, val):
        self.val = val
        self.count = 1
        self.left = None
        self.right = None

class binTree():
    def __init__(self):
        self.root = None
        self.node_count = 0

    def find(self, target_val : int) -> bool:
        '''
            查找二叉树中是否存在该值
        '''
        root = self.root

        while root != None and root.val != target_val:
            if root.val > target_val:
                root = root.left
            else:
                root = root.right
        
        return root != None


    def insert(self, val : int):
        root = self.root
        leaf_father = None

        while root:
            leaf_father = root
            if root.val == val:
                root.count += 1
                return
            elif root.val > val:
                root = root.left
            else:
                root = root.right
            
        
        new_node = binTreeNode(val)
        self.node_count += 1

        if leaf_father:
            if leaf_father.val > val:
                leaf_father.left = new_node
            else:
                leaf_father.right = new_node
        else:
            self.root = new_node


    def MidOrder(self, mode = 'Node') -> list:
        '''
            生成二叉树的中序遍历列表 \n
            :[param mode]: 
            \t'Node' 代表输出节点类列表 \n
            \t'val' 代表输出值列表 \n
        '''
        if mode not in ('val', 'Node'):
            return []

        self.MinOrder_temp_list = []

        def MidOrder_helper(root : binTreeNode):
            if root:
                MidOrder_helper(root.left)
                if mode == 'val':
                    self.MinOrder_temp_list.append(root.val)
                elif mode == 'Node':
                    self.MinOrder_temp_list.append(root)

                MidOrder_helper(root.right)
        
        MidOrder_helper(self.root)
        return self.MinOrder_temp_list


def from_list(int_list : list):
    tree = binTree()
    for i in int_list:
        tree.insert(i)

    return tree


if __name__ == '__main__':
    import numpy as np 
    random_list = list(np.random.randint(0, 30, 30))
    print(random_list)
    temp_tree = from_list(random_list)
    node_list = temp_tree.MidOrder()

    ordered = []
    for node in node_list:
        ordered += [node.val] * node.count
    
    print(ordered)