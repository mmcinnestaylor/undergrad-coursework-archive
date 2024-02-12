#ifndef BET_H
#define BET_H
#include <string>
#include <stack>
#include <sstream>
#include <iostream>

class BET{
  public:
    BET(); //default zero-parameter constructor. Builds an empty tree.
    BET(const std::string& postfix); //one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces.
    BET(const BET& tree); //copy constructor -- makes appropriate deep copy of the tree
    ~BET(); //destructor -- cleans up all dynamic space in the tree
    bool buildFromPostfix(const std::string& postfix); //parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
    const BET& operator= (const BET& tree); //assignment operator -- makes appropriate deep copy
    void printInfixExpression() const; //Print out the infix expression. Should do this by making use of the private (recursive) version
    void printPostfixExpression() const; //Print the postfix form of the expression. Use the private recursive function to help
    size_t size() const; //Return the number of nodes in the tree (using the private recursive function)
    size_t leaf_nodes() const; //Return the number of leaf nodes in the tree. (Use the private recursive function to help)
    bool empty() const; //return true if the tree is empty. Return false otherwise.


  private:
    struct BinaryNode{
      std::string data;
      BinaryNode* leftChild;
      BinaryNode* rightChild;
      BinaryNode(const std::string& theData, BinaryNode* lC = nullptr, BinaryNode* rC = nullptr)
        :data(theData), leftChild(lC), rightChild(rC){}
    };
    BinaryNode* root;
    //Private helper functions (all the required private member functions must be implemented recursively):
    void printInfixExpression(BinaryNode *n) const; //print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
    void makeEmpty(BinaryNode* &t); //delete all nodes in the subtree pointed to by t.
    BinaryNode * clone(BinaryNode *t) const; //clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=.
    void printPostfixExpression(BinaryNode *n) const; //print to the standard output the corresponding postfix expression.
    size_t size(BinaryNode *t) const; //return the number of nodes in the subtree pointed to by t.
    size_t leaf_nodes(BinaryNode *t) const; //return the number of leaf nodes in the subtree pointed to by t.

    bool isOperator(const std::string& tok) const;
    bool precedence(const std::string& tok) const;
};

#endif
