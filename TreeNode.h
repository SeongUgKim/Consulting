//
//  TreeNode.h
//  Assignment4
//
//  Created by Seong Kim on 2021/03/27.
//  Copyright © 2021 Seong Kim. All rights reserved.
//

#ifndef TreeNode_h
#define TreeNode_h
#include <memory>

namespace assignment4
{
    template<typename T>
    class TreeNode final
    {
    public:
        TreeNode(std::unique_ptr<T> data);
        TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data);

        std::unique_ptr<T> Data;
        std::shared_ptr<TreeNode<T>> Left;
        std::shared_ptr<TreeNode<T>> Right;
        std::weak_ptr<TreeNode<T>> Parent;
    };

    template<typename T>
    TreeNode<T>::TreeNode(std::unique_ptr<T> data)
        : Data(std::move(data))
        , Left(nullptr)
        , Right(nullptr)
    {
    }

    template<typename T>
    TreeNode<T>::TreeNode(std::shared_ptr<TreeNode<T>> parent, std::unique_ptr<T> data)
        : Data(std::move(data))
        , Parent(parent)
        , Left(nullptr)
        , Right(nullptr)
    {
    }
}

#endif /* TreeNode_h */
