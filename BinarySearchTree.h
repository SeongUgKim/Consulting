//
//  BinarySearchTree.h
//  Assignment4
//
//  Created by Seong Kim on 2021/03/27.
//  Copyright © 2021 Seong Kim. All rights reserved.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include <memory>
#include <vector>

namespace assignment4
{
    template<typename T>
    class TreeNode;

    template<typename T>
    class BinarySearchTree final
    {
    public:
        BinarySearchTree();
        ~BinarySearchTree() = default;
        BinarySearchTree(const BinarySearchTree<T>& other) = default;
        BinarySearchTree& operator=(const BinarySearchTree<T>& rhs) = default;
        void Insert(std::unique_ptr<T> data);
        bool Search(const T& data);
        bool Delete(const T& data);
        const std::weak_ptr<TreeNode<T>> GetRootNode() const;

        static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);
    private:
        void depthFirstSearchInOrder(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& vec);
        std::shared_ptr<TreeNode<T>> minValueNode(const std::shared_ptr<TreeNode<T>> startNode);
        std::shared_ptr<TreeNode<T>> mRoot;
    };

    template<typename T>
    BinarySearchTree<T>::BinarySearchTree()
        : mRoot(nullptr)
    {
    }

    template<typename T>
    void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
    {
        if (mRoot == nullptr)
        {
            mRoot = std::make_shared<TreeNode<T>>(std::move(data));
            return;
        }
        auto temp = mRoot;
        while (temp != nullptr)
        {
            if (*data <= *temp->Data && temp->Left == nullptr)
            {
                auto newNode = std::make_shared<TreeNode<T>>(temp, std::move(data));
                temp->Left = newNode;
                return;
            }
            else if (*data <= *(temp->Data))
            {
                temp = temp->Left;
            }
            else if (*data > *temp->Data && temp->Right == nullptr)
            {
                auto newNode = std::make_shared<TreeNode<T>>(temp, std::move(data));
                temp->Right = newNode;
                return;
            }
            else
            {
                temp = temp->Right;
            }
        }
    }
    
    template<typename T>
    const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
    {
        return mRoot;
    }

    template<typename T>
    bool BinarySearchTree<T>::Search(const T& data)
    {
        if (mRoot == nullptr)
        {
            return false;
        }
        auto temp = mRoot;
        while (temp != nullptr)
        {
            if (data == *temp->Data)
            {
                return true;
            }
            if (data < *temp->Data)
            {
                temp = temp->Left;
            }
            else
            {
                temp = temp->Right
            }
        }
        return false;
    }
    
    template<typename T>
    bool BinarySearchTree<T>::Delete(const T& data)
    {
        auto temp = mRoot;
        if (mRoot == nullptr)
        {
            return false;
        }
        while (temp != nullptr)
        {
            if (data < *temp->Data)
            {
                temp = temp->Left;
            }
            else if (data > *temp->Data)
            {
                temp = temp->Right;
            }
            else
            {
                if (temp->Left == nullptr && temp->Right == nullptr)
                {
                    auto tempParent = temp->Parent.lock();
                    if (*temp->Data > *tempParent->Data)
                    {
                        tempParent->Right = nullptr;
                    }
                    else
                    {
                        tempParent->Left = nullptr;
                    }
                }
                else if (temp->Left == nullptr)
                {
                    auto res = temp->Right;
                    auto tempParent = temp->Parent.lock();
                    if (*temp->Data > *tempParent->Data)
                    {
                        tempParent->Right = res;
                        res->Parent = tempParent;
                    }
                    else
                    {
                        tempParent->Left = res;
                        res->Parent = tempParent;
                    }
                }
                else if (temp->Right == nullptr)
                {
                    auto res = temp->Left;
                    auto tempParent = temp->Parent.lock();
                    if (*temp->Data > *tempParent->Data)
                    {
                        tempParent->Right = res;
                        res->Parent = tempParent;
                    }
                    else
                    {
                        tempParent->Left = res;
                        res->Parent = tempParent;
                    }
                }
                else
                {
                    auto res = minValueNode(temp->Right);
                    T& tempData = *res->Data;
                    Delete(tempData);
                    *temp->Data = tempData;
                }
            }
        }
    }

    template<typename T>
    std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
    {
        std::vector<T> v;
        if (r == nullptr)
        {
            return v;
        }
        depthFirstSearchInOrder(startNode->Left, v);
        v.push_back(*startNode->Data);
        depthFirstSearchInOrder(startNode->Right, v);
        return v;
    }
    std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::minValueNode(const std::shared_ptr<TreeNode<T>> startNode)
    {
        auto current = startNode;
        while (current->Left != nullptr)
        {
            current = current->Left;
        }
        return current;
    }
    void BinarySearchTree::depthFirstSearchInOrder(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& vec)
    {
        depthFirstSearchInOrder(startNode->Left, vec);
        vec.push_back(*startNode->Data);
        depthFirstSearchInOrder(startNode->Right, vec);
    }
}

#endif /* BinarySearchTree_h */
