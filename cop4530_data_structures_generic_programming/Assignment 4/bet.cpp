#include "bet.h"

BET::BET():root(nullptr){}

BET::BET(const std::string& postfix):root(nullptr){
  buildFromPostfix(postfix);
}

BET::BET(const BET& tree){
  root = nullptr;
  root = clone(tree.root);
}

BET::~BET(){
  makeEmpty(root);
}

bool BET::buildFromPostfix(const std::string& postfix){
  std::string token;
  std::stack<BET::BinaryNode*> tokStk;
  std::stringstream ss(postfix);

  while(ss >> token){
    if(!BET::isOperator(token))
      tokStk.push(new BinaryNode(token));
    else{
      if(tokStk.empty() || tokStk.size() == 1){
        std::cout << "Error, operator does not have corresponding operands.\n";
        return false;
      }
      else{
        BET::BinaryNode* rC = tokStk.top();
        tokStk.pop();
        BET::BinaryNode* lC = tokStk.top();
        tokStk.pop();
        tokStk.push(new BinaryNode(token,lC, rC));
      }
    }
  }
  if(tokStk.size() > 1){
    std::cout << "Operand(s) missing corresponding operators.\n";
    return false;
  }
  root = tokStk.top();
  tokStk.pop();
  return true;
}

const BET& BET::operator= (const BET& tree){
  if(this != &tree){
    makeEmpty(root);
    root = clone(tree.root);
    return *this;
  }
  else
    return *this;
}

void BET::printInfixExpression() const{
  printInfixExpression(root);
  std::cout << '\n';
}

void BET::printPostfixExpression() const{
  printPostfixExpression(root);
  std::cout << '\n';
}

size_t BET::size() const{
  return size(root);
  std::cout << '\n';
}

size_t BET::leaf_nodes() const{
  return leaf_nodes(root);
  std::cout << '\n';
}

bool BET::empty() const{
  if(root == nullptr)
    return true;
  else
    return false;
}

//private functions
void BET::printInfixExpression(BET::BinaryNode *n) const{
  if(n != nullptr){
    if(isOperator(n->data)){
      if(isOperator(n->leftChild->data)){
        if(precedence(n->leftChild->data) >= precedence(n->data))
            printInfixExpression(n->leftChild);
        else{
            std::cout << "( ";
            printInfixExpression(n->leftChild);
            std::cout << ") ";
        }
      }
      else
        std::cout << n->leftChild->data << " ";
      std::cout << n->data << " ";
      if(isOperator(n->rightChild->data)){
        if(precedence(n->rightChild->data) <= precedence(n->data)){
          std::cout << "( ";
          printInfixExpression(n->rightChild);
          std::cout << ") ";
        }
        else
          printInfixExpression(n->rightChild);
      }
      else
        std::cout << n->rightChild->data << " ";
    }
    else
      std::cout << n->data << " ";
  }
}

void BET::makeEmpty(BET::BinaryNode* &t){
  if(t != nullptr){
    if(t->leftChild != nullptr){
      makeEmpty(t->leftChild);
    }
    if(t->rightChild != nullptr){
      makeEmpty(t->rightChild);
    }
    delete t;
    t = nullptr;
  }
}

BET::BinaryNode * BET::clone(BET::BinaryNode *t) const{
  if(t != nullptr)
    return new BET::BinaryNode{t->data, BET::clone(t->leftChild), BET::clone(t->rightChild)};
  else
    return nullptr;
}

void BET::printPostfixExpression(BET::BinaryNode *n) const{
  if(n != nullptr){
    printPostfixExpression(n->leftChild);
    printPostfixExpression(n->rightChild);
    std::cout << n->data << " ";
  }
}

size_t BET::size(BET::BinaryNode *t) const{
  if(t != nullptr){
    return size(t->leftChild) + size(t->rightChild) + 1;
  }
  else
    return 0;
}

size_t BET::leaf_nodes(BET::BinaryNode *t) const{
  if(t != nullptr){
    if((t->leftChild == nullptr) && (t->rightChild == nullptr))
        return 1;
    else{
      return leaf_nodes(t->leftChild) + leaf_nodes(t->rightChild);
    }
  }
  else
    return 0;
}

//extra helper functions
bool BET::isOperator(const std::string& tok) const{
  if(tok == "*" || tok == "/" || tok == "+" || tok == "-")
    return true;
  else
    return false;
}

bool BET::precedence(const std::string& tok) const{
  if(tok == "*" || tok == "/")
    return true;
  else
    return false;
}
