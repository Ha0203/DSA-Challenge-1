#include "Functions.h"

bool RESULT::PostOrder()
 {
    if(!Tree) 
    {
        return false;
    }
    stack<node*> first;
    stack<node*> second;

    first.push(Tree);
    node* left = nullptr;
    node* right = nullptr;

    while(!first.empty())
    {
        left = first.top()->left;
        right = first.top()->right;
        second.push(first.top());
        first.pop();
        if(left)
            first.push(left);
        if(right)
            first.push(right);
    }

    while(!second.empty())
    {
        Postfix += second.top()->data;
        second.pop();
        if(!second.empty())
            Postfix += " ";
    }

    return true;
 }

int RESULT::Calculate(node* root)
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