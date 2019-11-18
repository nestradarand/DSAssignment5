#ifndef EXTENDED_TREE
#define EXTENDED_TREE
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include <cstddef>

template <typename T>
class ExtendedTree: public BST<T>
{
    public:
        ExtendedTree();
        // ~ExtendedTree();
        void printToStrings();
        void insert(T value);
        T search(T entry);

    private:
        void printFullNodes(TreeNode<T> *root);

};
#endif
template <typename T>
ExtendedTree<T>::ExtendedTree(): BST<T>()
{

}
//works
template <typename T>
void ExtendedTree<T>::printToStrings()
{
    if (this ->root != NULL)
        printFullNodes(this -> root);
    else
        std::cout << "Nothing in the tree to print out" << std::endl;
}
//works
template <typename T>
void ExtendedTree<T>::printFullNodes(TreeNode<T> *root)
{
    if (root != NULL)
    {
        printFullNodes(root->left);
        std::cout << root->key->toString() << "\n---" << std::endl;
        printFullNodes(root->right);
    }
    else
        return;
}
//works
template <typename T>
void ExtendedTree<T>::insert(T value)
{
    TreeNode<T> *newNode = new TreeNode<T>(value);
    if (this ->root == NULL)
        this -> root = newNode;
    //otherwise tree is not empty/need to find insertion location
    TreeNode<T> *current = this->root;
    TreeNode<T> *parent = NULL;
    //will run until the current node value is NULL, that way we can place the new node at that location
    //works by updating the parent to the current node then the if values move us down the tree
    while (true)
    {
        parent = current;
        if (value->operator<(*current->key))
        {
            current = current->left;
            if (current == NULL)
            {
                parent->left = newNode;
                break;
            }
        }
        else if (value->operator>(*current->key))
        {
            current = current->right;
            if (current == NULL)
            {
                parent->right = newNode;
                break;
            }
        }
        else
            break;
    }
}
template <typename T>
T ExtendedTree<T>::search(T value)
{
    if (this->root == NULL)
        return NULL;
    //tree is not empty; let's look
    TreeNode<T> *current = this->root;
    while (current->key->operator!=(*value))
    {
        if (value->operator<(*current->key))
            current = current->left;
        else
            current = current->right;
        if (current == NULL) //didnt find the value
            return NULL;
    }
    return current->key; //happens if the value was found which would have broken the loop above
}