#ifndef TREENODE_H
#define TREENODE_H
#include <cstddef>

///this is where the key is the value///need to adjust for future assignments
template <typename T>
class TreeNode 
{
public:
    TreeNode();
    TreeNode(T newKey);
    ~TreeNode();

    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
#endif

template <typename T>
TreeNode<T>::TreeNode()
{
    key = nullptr;
    left = nullptr;
    right = nullptr;
}
template <typename T>
TreeNode<T>::TreeNode(T newKey)
{
    key = newKey;
    left = nullptr;
    right = nullptr;
}
template <typename T>
TreeNode<T>::~TreeNode()
{
    //need to check to see if this is right
    //it is because then this will help recursively delete everything in the tree upon destruction
    // delete key;
    if(left != nullptr)
        delete left;
    if(right != nullptr)
        delete right;
}