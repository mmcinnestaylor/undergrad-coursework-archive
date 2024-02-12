#ifndef STACK_H
#define STACK_H
#include <vector>
#include <iostream>

namespace cop4530{

template <typename T>
  class Stack{

    public:
        Stack();
        ~Stack();
        Stack(const Stack& s);
        Stack(Stack&& s);
        Stack& operator=(const Stack& s);
        Stack& operator=(Stack&& s);
        bool empty() const;
        void clear();
        void push(const T& x);
        void push(T&& x);
        void pop();
        T& top();
        const T& top() const;
        int size() const;
        void print(std::ostream& os, char ofc = ' ') const;
    private:
      std::vector<T> data;
  };

  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

  template<typename T>
  bool operator==(const Stack<T>& a, const Stack<T>& b);

  template<typename T>
  bool operator!=(const Stack<T>& a, const Stack<T>& b);

  template<typename T>
  bool operator<=(const Stack<T>& a, const Stack<T>& b);


#include "stack.hpp"
}

#endif
