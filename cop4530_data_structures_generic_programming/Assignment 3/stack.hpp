template <typename T>
Stack<T>::Stack(){}

template <typename T>
Stack<T>::~Stack(){}

template <typename T>
Stack<T>::Stack(const Stack& s){
  this->data = s.data;
}

template <typename T>
Stack<T>::Stack(Stack&& s){
  this->data = std::move(s.data);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& s){
  if(this != &s)
    this->data = s.data;
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& s){
  std::swap(*this, s);
  return *this;
}

template <typename T>
bool Stack<T>::empty() const{
  return this->data.empty();
}

template <typename T>
void Stack<T>::clear(){
  this->data.clear();
}

template <typename T>
void Stack<T>::push(const T& x){
  this->data.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x){
  this->data.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop(){
  this->data.pop_back();
}

template <typename T>
T& Stack<T>::top(){
  return this->data.back();
}

template <typename T>
const T& Stack<T>::top() const{
  return this->data.back();
}

template <typename T>
int Stack<T>::size() const{
  return this->data.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const{
  auto itr = this->data.begin();
  while(itr != this->data.end())
    os << *(itr++) << ofc;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a){
  a.print(os);
  return os;
}

template<typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b){
  if(a.size() != b.size())
    return false;
  else{
    auto x = a;
    auto y = b;
    while(!x.empty()){
      if(x.top() != y.top())
        return false;
      x.pop();
      y.pop();
    }
  }
  return true;
}

template<typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b){
  return !(a == b);
}

template<typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b){
  if(a.size() > b.size())
    return false;
  else{
    auto x = a;
    auto y = b;
    while(!x.empty()){
      if(x.top() > y.top())
        return false;
      x.pop();
      y.pop();
    }
  }
  return true;
}
