const int SIZE = 1048576;
const int nullVal = -2147483648;
int probes, tempkey;
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
  probes = 1;
  tempkey = val % SIZE;
  if(tempkey < 0) tempkey = tempkey * -1;
  key = tempkey;

  if(hash_table[key] == nullVal){
    hash_table[key] = val;
    failFlag = false;
  }
  else
    for(int i = 1; i < SIZE; i++){
      probes++;
      if(key + i < SIZE){
        if(hash_table[key + i] == nullVal){
          hash_table[key + i] = val;
          failFlag = false;
          break;
        }
      }
      else{
        if(hash_table[key + i - SIZE] == nullVal){
          hash_table[key + i - SIZE] = val;
          failFlag = false;
          break;
        }
      }
    }
}

/*
 * Return 1 if val is in hash_table, 0 otherwise.
 */
char search(int *hash_table, int val){
  tempkey = val % SIZE;
  if(tempkey < 0) tempkey = tempkey * -1;
  key = tempkey;

  if(hash_table[key] == val) return true;
  else
    for(int i = 1; i < SIZE; i++){
      if(key + i < SIZE){
        if(hash_table[key + i] == val)
          return 1;
      }
      else{
        if(hash_table[key + i - SIZE] == nullVal)
          return 1;
      }
    }
  return 0;
}
/*
 * Delete the first encountered val from hash_table in place.
 */
void remove(int *hash_table, int val){
  tempkey = val % SIZE;
  if(tempkey < 0) tempkey = tempkey * -1;
  key = tempkey;

  if(hash_table[key] == val) hash_table[key] = nullVal;
  else
    for(int i = 1; i < SIZE; i++){
      if(key + i < SIZE){
        if(hash_table[key + i] == val){
          hash_table[key + i] = nullVal;
          break;
        }
      }
      else{
        if(hash_table[key + i - SIZE] == val){
          hash_table[key + i - SIZE] = nullVal;
          break;
        }
      }
    }
}
