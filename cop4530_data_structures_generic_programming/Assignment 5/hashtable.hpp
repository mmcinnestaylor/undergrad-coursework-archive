template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size):currentSize(0){
  if(size == 0){
    ht.resize(default_capacity);
    std::cout << "** input too small\nset to default capacity: " << default_capacity;
  }
  else
    ht.resize(prime_below(size));
}

template<typename K, typename V>
HashTable<K, V>::~HashTable(){}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const{
  if(!ht[myhash(k)].empty()){
    auto itr = ht[myhash(k)].begin();
    while(itr != ht[myhash(k)].end())
      if((*(itr++)).first == k) return true;
  }
  return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const{
  if(!ht[myhash(kv.first)].empty()){
    auto itr = ht[myhash(kv.first)].begin();
    while(itr != ht[myhash(kv.first)].end())
      if(*(itr++) == kv) return true;
  }
  return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv){
  if(contains(kv.first)){
    if(match(kv)) return false;
    else{
      auto itr = ht[myhash(kv.first)].begin();
      while(itr != ht[myhash(kv.first)].end()){
        if((*itr).first == kv.first){
          (*itr).second = kv.second;
          break;
        }
        else itr++;
      }
    }
  }
  else{
    ht[myhash(kv.first)].push_back(kv);
    currentSize++;
  }
  if(currentSize > ht.size())
    rehash();
  return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv){
  if(contains(kv.first)){
    if(match(kv)) return false;
    else{
      auto itr = ht[myhash(kv.first)].begin();
      while(itr != ht[myhash(kv.first)].end()){
        if((*itr).first == kv.first){
          (*itr).second = std::move(kv.second);
          break;
        }
        else itr++;
      }
    }
  }
  else{
    ht[myhash(kv.first)].push_back(std::move(kv));
    currentSize++;
  }
  if(currentSize > ht.size())
    rehash();
  return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k){
  if(contains(k)){
    auto itr = ht[myhash(k)].begin();
    while(itr != ht[myhash(k)].end()){
      if((*(itr)).first == k){
        ht[myhash(k)].erase(itr);
        currentSize--;
        return true;
      }
    }
  }
  return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear(){
  makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename){
  bool successFlag = true;
  std::ifstream fs;
  fs.open(filename);
  if(fs.bad()) return false;
  K key;
  V value;
  std::pair<K, V> kv;
  while(fs >> key){
    if(fs.peek() == ' '){
      fs >> value;
      kv = std::make_pair(key, value);
      if(!insert(kv)){
        std::cout << "Error: Loading file entry is incorrect\n";
        successFlag = false;
      }
    }
    else{
      std::cout << "Error: Loading file entry is incorrect\n";
      successFlag = false;
    }
  }
  fs.close();
  return successFlag;
}

template<typename K, typename V>
void HashTable<K, V>::dump() const{
  for(int i = 0; i < ht.size(); i++){
    std::cout << "v[" << i << "]: ";
    if(!ht[i].empty()){
      auto itr = ht[i].begin();
      while(itr != ht[i].end()){
        if(itr == ht[i].begin())
          std::cout << (*itr).first << ' ' << (*itr).second;
        else
          std::cout << ":" << (*itr).first << ' ' << (*itr).second;
        itr++;
      }
    }
    std::cout << '\n';
  }
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const{
  std::ofstream fs(filename);
  for(int i = 0; i < ht.size(); i++){
    if(!ht[i].empty()){
      auto itr = ht[i].begin();
      while(itr != ht[i].end()){
        fs << (*itr).first << ' ' << (*itr).second << '\n';
        itr++;
      }
    }
  }
  fs.close();
  return true;
}

template<typename K, typename V>
size_t HashTable<K, V>::getSize() const{
  return currentSize;
}

//private functions
template<typename K, typename V>
void HashTable<K, V>::makeEmpty(){
  for(int i = 0; i < ht.size(); i++){
    ht[i].clear();
  }
  currentSize = 0;
}

template<typename K, typename V>
void HashTable<K, V>::rehash(){
  HashTable tempTable(prime_below(2 * ht.size()));
  for(int i = 0; i < ht.size(); i++){
    if(!ht[i].empty()){
      auto itr = ht[i].begin();
      while(itr != ht[i].end())
        tempTable.insert(*(itr++));
    }
  }
  std::swap(ht, tempTable.ht);
  std::swap(currentSize, tempTable.currentSize);
}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k) const{
  std::hash<K> theHash;
  return theHash(k) % ht.size();
}
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n){
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes){
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
