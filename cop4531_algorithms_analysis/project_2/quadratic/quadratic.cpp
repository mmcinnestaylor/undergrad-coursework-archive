const long int SIZE = 1048576;
const int nullVal = -2147483648;
const long int c1 = 3;
const long int c2 = 2;
int probes;
long long int key_prime;
unsigned long long int key;
bool failFlag;

/*
 * hash_table will be an integer array of size 1,000,000
 * You need to initialize this table.
 */
void init(int *hash_table){
  for(int i = 0; i < SIZE; i++)
    hash_table[i] = nullVal;
}
/*
 * You need to insert val into hash_table in place.
 */
void insert(int *hash_table, int val){
  failFlag = true;
  probes = 0;
  key_prime = val % SIZE;
  if(key_prime < 0) key_prime = key_prime * (-1);

  for(unsigned long int i = 0; i < SIZE; i++){
    key = (key_prime + (c1 * i) + (c2 * (i * i))) % SIZE;
    probes++;
    if(hash_table[key] == nullVal){
      hash_table[key] = val;
      failFlag = false;
      break;
    }
  }
}
/*
 * Return 1 if val is in hash_table, 0 otherwise.
 */
char search(int *hash_table, int val){
  key_prime = val % SIZE;

  for(unsigned long int i = 0; i < SIZE; i++){
    key = (key_prime + (c1 * i) + (c2 * (i * i))) % SIZE;
    if(hash_table[key] == val){
      return 1;
    }
  }
  return 0;
}
/*
 * Delete the first encountered val from hash_table in place.
 */
void remove(int *hash_table, int val){
  key_prime = val % SIZE;

  for(unsigned long int i = 0; i < SIZE; i++){
    key = (key_prime + (c1 * i) + (c2 * (i * i))) % SIZE;
    if(hash_table[key] == val){
      hash_table[key] = nullVal;
      break;
    }
  }
}
