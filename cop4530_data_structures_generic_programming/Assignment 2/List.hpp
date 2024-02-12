/*LIST CLASS
DEFINITTIONS*/

template <typename T>
void List<T>::init(){
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
  theSize = 0;
}
template <typename T>
List<T>::List(){
  init();
}

template <typename T>
List<T>::List(const List &rhs){
  init();
  List<T>::const_iterator itr = begin();
  while(itr != nullptr){
      push_back(*itr);
      itr++;
      theSize++;
  }
}

template <typename T>
List<T>::List(List && rhs){
  init();
  std::swap(*this.head, rhs.head);
  std::swap(*this.tail, rhs.tail);
  std::swap(*this.theSize, rhs.theSize)
}

template <typename T>
List<T>::explicit List(int num, const T& val){
  init();
  for(auto i = 0; i < num; i++)
    push_back(val);
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end){
  init();
  auto itr = start;
  while(itr != end()){
    push_back(*itr);
    itr++;
  }
}

template <typename T>
List<T>::List(std::initializer_list<T> iList){}

template <typename T>
List<T>::~List(){
  clear();
}

template <typename T>
const List& List<T>::operator=(const List & rhs){
  if(this != &rhs){
    auto copy(rhs);
    std::swap(*this, copy);
    return *this;
  }
  else
    return *this;
}

template <typename T>
List& List<T>::operator=(List && rhs){
  std::swap(*this, rhs);
  return *this;
}

template <typename T>
List& List<T>::operator=(std::initializer_list<T> iList){}

template <typename T>
int List<T>::size() const{
  return theSize;
}

template <typename T>
bool List<T>::empty() const{
  if(theSize > 0) return false;
  else return true;
}

template <typename T>
void List<T>::clear(){
  while(!empty())
    pop_front();
  init();
}

template <typename T>
void List<T>::reverse(){
  auto templist;
  auto itr = --end();
  for(auto i = 0; i < size(); i++){
    templist.push_back((*itr)--);
  }
  std::swap(*this, templist);
}

template <typename T>
T& List<T>::front(){
  return(head->next->data;)
}

template <typename T>
const T& List<T>::front() const{
  return(head->next->data);
}

template <typename T>
T& List<T>::back(){
  return(tail->prev->data);
}

template <typename T>
const T& List<T>::back() const{
  return(tail->prev->data);
}

template <typename T>
void List<T>::push_front(const T & val){
  auto* tempptr = new Node(val, head, head->next)
  head->next = head->next->prev = tempptr;
  theSize++;
}

template <typename T>
void List<T>::push_front(T && val){
  push_front(val);
}

template <typename T>
void List<T>::push_back(const T & val){
  auto* tempptr = new Node(val, tail->prev, tail);
  tail->prev = tail->prev->next = tempptr;
  theSize++;
}

template <typename T>
void List<T>::push_back(T && val){
  push_back(val);
}

template <typename T>
void List<T>::pop_front(){
  auto* tempptr = head->next;
  head->next = tempptr->next;
  head->next->prev = head;
  delete tempptr;
  theSize--;
}

template <typename T>
void List<T>::pop_back(){
  auto* tempptr = tail->prev;
  tail->prev = tempptr->prev;
  tail->prev->next = tail;
  delete tempptr;
  theSize--;
}

template <typename T>
void List<T>::remove(const T &val){
  auto itr = begin();
  while(itr != end()){
    if(*itr == val){
      tempptr = itr.current;
      itr++;
      tempptr->prev->next = itr.current;
      itr.current->prev = tempptr->prev;
      delete tempptr;
      theSize--;
    }
    else itr++;
  }
}

template <typename T>
void List<T>::remove_if(PREDICATE pred){}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
  auto itr = begin();
  while(itr != end()){
    os << *itr << ofc;
  }
}

template <typename T>
iterator List<T>::begin(){
  return(List<T>::iterator<T>::iterator itr(head->next));
}

template <typename T>
const_iterator List<T>::begin() const{
  return(List<T>::const_iterator<T>::const_iterator itr(head->next));
}

template <typename T>
iterator List<T>::end(){
  return(List<T>::iterator<T>::iterator itr(tail));
}

template <typename T>
const_iterator List<T>::end(){
  return(List<T>::const_iterator<T>::const_iterator itr(tail));
}

template <typename T>
iterator List<T>::insert(iterator itr, const T& val){
  auto* tempptr = new Node(val, itr.current->prev, itr.current);
  itr.current->prev = itr.current->prev->next = tempptr;
  theSize++;
  return itr;
}

template <typename T>
iterator List<T>::insert(iterator itr, const T&& val){
  itr = insert(itr, val);
  return itr;
}

template <typename T>
iterator List<T>::erase(iterator itr){
  auto* tempptr = itr.current;
  itr++;
  tempptr->prev->next = itr.current;
  itr.current->prev = tempptr->prev;
  delete tempptr;
  theSize--;
  return itr;
}

template <typename T>
iterator List<T>::erase(iterator start, iterator end){
  while(start != end){
    start = erase(start);
  }
  return end;
}

/*CONST ITERATOR CLASS
DEFINITTIONS*/
template <typename T>
List<T>::const_iterator<T>::const_iterator():current(nullptr){}

template <typename T>
List<T>::const_iterator<T>::const_iterator(Node *p):current(p){}

template <typename T>
T& List<T>::const_iterator<T>::retrieve() const{
  return(this->current->data);
}

template <typename T>
const T& List<T>::const_iterator<T>::operator*() const{
  return(retrieve());
}

template <typename T>
const_iterator& List<T>::const_iterator<T>::operator++(){
  if(*this != end()){
    this->current = this->current->next;
    return *this;
  }
  else return *this;
}

template <typename T>
const_iterator List<T>::const_iterator<T>::operator++(int){
  auto itr = *this;
  if(*this != end()){
    this->current = this->current->next;
    return itr;
  }
  else return itr;
}

template <typename T>
const_iterator& List<T>::const_iterator<T>::operator--(){
  if(this->current != head){
    this->current = this->current->prev;
    return *this;
  }
  else return *this;
}

template <typename T>
const_iterator List<T>::const_iterator<T>::operator--(int){
  auto itr = *this;
  if(this->current != head){
    this->current = this->current->prev;
    return itr;
  }
  else return itr;
}

template <typename T>
bool List<T>::const_iterator<T>::operator==(const const_iterator & rhs) const{
  if(this->current == rhs.current)
    return true;
  else
    return false;
}

template <typename T>
bool List<T>::const_iterator<T>::operator!=(const const_iterator & rhs) const{
  return !(*this == rhs);

  
