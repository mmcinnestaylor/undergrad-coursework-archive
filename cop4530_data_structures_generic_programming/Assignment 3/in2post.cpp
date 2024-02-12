#include "stack.h"
#include <sstream>
#include <string>
#include <cctype>
#include <typeinfo>

using namespace cop4530;
using namespace std;

bool isOperand(const string& s);
bool isOperator(const string& s);
int precedence(const string& s);
bool isNumExp(const string& str);
bool isFloat(const string& str);
bool convPost(stringstream& in, string& out);
template<typename T>
bool evalPost(stringstream& stream, T& returnVal);

int main(){
  stringstream strStream;
  string input, postfixExp;
  float returnVal_f = 0;
  int returnVal_i = 0;

  while(!cin.eof()){
    cout << "Enter infix expression (\"exit\" to quit): " << endl;
    strStream.str(std::string());
    strStream.clear();
    input.clear();
    postfixExp.clear();

    getline(cin, input);

    if((input == "exit") || input.empty())
      return 0;

    strStream.str(input);

    if(convPost(strStream, postfixExp)){
        cout << "Postfix expression: " << postfixExp << endl;
        if(isNumExp(postfixExp)){
          if(isFloat(postfixExp) && evalPost<float>(strStream, returnVal_f)){
            cout << "Postfix evaluation: " << postfixExp << "= "
                 << returnVal_f << endl;
          }
          else if(evalPost<int>(strStream, returnVal_i)){
            cout << "Postfix evaluation: " << postfixExp << "= "
                 << returnVal_i << endl;
          }
        }
        else{
          cout << "Postfix evaluation: " << postfixExp
               << " = " << postfixExp << endl;
        }
    }
  }
    return 0;
}

bool isOperand(const string& s){
  if(s == "(" || s == ")" || s == "*" || s == "/" ||
     s == "+" || s == "-")
    return false;
  else
    return true;
}

bool isOperator(const string& s){
  if(s == "*" || s == "/" || s == "+" || s == "-")
    return true;
  else
    return false;
}

int precedence(const string& s){
  if(s == "(")
    return 4;
  else if(s == ")")
    return 3;
  else if(s == "*" || s == "/")
    return 2;
  else if(s == "+" || s == "-")
    return 1;
  else
    return 0;
}

bool isNumExp(const string& str){
  auto itr = str.begin();
  while(itr != str.end()){
    if(isalpha(*(itr++)))
      return false;
  }
  return true;
}

bool isFloat(const string& str){
  auto itr = str.begin();
  while(itr != str.end()){
    if(*(itr++) == '.')
      return true;
  }
  return false;
}

bool convPost(stringstream& in, string& out){
  string token, prevtoken;
  cop4530::Stack<string> tokStk;

  while(in >> token){
    if(isOperand(token))
      out = out + token + " ";
    else if(token == "("){
      tokStk.push(token);
    }
    else if(token == ")"){
      if(isOperator(prevtoken) || prevtoken.empty()){
        cout << "Error: Missing operand in the expression or parenthesis mismatch." << endl;
        return false;
      }
      else{
        while(!tokStk.empty() && (tokStk.top() != "(")){
          out = out + tokStk.top() + " ";
          tokStk.pop();
        }
        if(tokStk.top() == "(")
          tokStk.pop();
        else if(tokStk.empty()){
          cout << "Error: Parenthesis mismatch." << endl;
          return false;
        }
      }
    }
    else if(isOperator(token)){
      if(isOperator(prevtoken)){
        cout << "Error: Operator/operand mismatch, missing operand." << endl;
        return false;
      }
      while(!tokStk.empty() && (tokStk.top() != "(") &&
            (precedence(token) <= precedence(tokStk.top()))){
          out = out + tokStk.top() + " ";
          tokStk.pop();
      }
      tokStk.push(token);
    }
    prevtoken = token;
  }
  if(isOperator(prevtoken) || prevtoken == "("){
    cout << "Error: Missing operand or parenthesis mismatch." << endl;
    return false;
  }
  while(!tokStk.empty()){
    if(tokStk.top() == "("){
      cout << "Error: Missing operators in the expression" << endl;
      return false;
    }
    out = out + tokStk.top() + " ";
    tokStk.pop();
  }
  in.clear();
  in.str(out);
  return true;
}

template<typename T>
bool evalPost(stringstream& stream, T& returnVal){
  T temp1, temp2;
  string s;
  string numType = typeid(temp1).name();
  cop4530::Stack<T> opStk;
  if(numType == "f"){
    while(stream >> s){
      if(isOperand(s)){
      opStk.push(stof(s));
    }
      else if(isOperator(s)){
        if(opStk.size() < 2){
        cout << "Error: Postfix operator/operand mismatch. " << endl;
        return false;
      }
        switch(precedence(s)){
          case 2:{
            if(s == "*"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 * temp2);
            }
            else if(s == "/"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 / temp2);
            }
            break;
          }
          case 1:{
            if(s == "+"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 + temp2);
            }
            else if(s == "-"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 - temp2);
            }
            break;
          }
        }
      }
    }
  }
  else if(numType == "i"){
    while(stream >> s){
      if(isOperand(s)){
        opStk.push(stoi(s));
      }
      else if(isOperator(s)){
        if(opStk.size() < 2){
          cout << "Error: Postfix operator/operand mismatch. " << endl;
          return false;
        }
        switch(precedence(s)){
          case 2:{
            if(s == "*"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 * temp2);
            }
            else if(s == "/"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 / temp2);
            }
            break;
          }
          case 1:{
            if(s == "+"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 + temp2);
            }
            else if(s == "-"){
              temp2 = opStk.top();
              opStk.pop();
              temp1 = opStk.top();
              opStk.pop();
              opStk.push(temp1 - temp2);
            }
            break;
          }
        }
      }
    }
  }
  if((opStk.size()) > 1){
    cout << "Error: Postfix operator/operand mismatch." << endl;
    return false;
  }
  else if(opStk.size() == 0){
    returnVal = 0;
    return true;
  }
  else{
    returnVal = opStk.top();
    return true;
  }
}
