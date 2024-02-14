const int SIZE = 1048576;
const int nullVal = -2147483648;
int probes;
long int key1, key2;
unsigned long int key;
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
  key1 = val % SIZE;
  if(key1 < 0) key1 = key1 * (-1);
  key2 = (key1 * 2) + 1;

  for(long int i = 0; i < SIZE; i++){
    key = (key1 + (i * key2)) % SIZE;
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
  key1 = val % SIZE;
  if(key1 < 0) key1 = key1 * (-1);
  key2 = (key1 * 2) + 1;

  for(long int i = 0; i < SIZE; i++){
    key = (key1 + (i * key2)) % SIZE;
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
  key1 = val % SIZE;
  if(key1 < 0) key1 = key1 * (-1);
  key2 = (key1 * 2) + 1;

  for(long int i = 0; i < SIZE; i++){
    key = (key1 + (i * key2)) % SIZE;
    if(hash_table[key] == val){
      hash_table[key] = nullVal;
      break;
    }
  }
}
