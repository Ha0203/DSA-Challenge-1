#include "Functions.h"

bool RESULT::PostOrder()
 {
    if(!Tree) 
    {
        return false;
    }
    stack<node*> first;

    first.push(Tree);
    node* left = nullptr;
    node* right = nullptr;

    while(!first.empty())
    {
        left = first.top()->left;
        right = first.top()->right;
        Postfix = first.top()->data + Postfix;
        first.pop();
        if(left)
            first.push(left);
        if(right)
            first.push(right);
        if(!first.empty())
            Postfix = " " + Postfix;
    }

    return true;
 }

float RESULT::Calculate(node* root)
 {
    if(!root) 
    {
        return false;
    }
    
    if(root->IsLeaf())
    {
        return stof(root->data);
    }
    
    float op1 = Calculate(root->left);
    float op2 = Calculate(root->right);

    if(root->data == "/" && op2 == 0)
    {
        ErrorFlag = true;
        return INT16_MAX;
    }

    return Process(root->data, op1, op2);
 }

 bool node::IsLeaf()
 {
    return left == nullptr && right == nullptr;
 }

 float Process(string operand, float op1, float op2)
 {
    if(operand == "+")
        return op1 + op2;
    else if(operand == "-")
        return op1 - op2;
    else if(operand == "*")
        return op1 * op2;
    else if(operand == "^")
        return pow(op1, op2);
    else
        return op1/op2;
 }