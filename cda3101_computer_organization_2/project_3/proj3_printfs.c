#include <stdio.h>
#include <stdlib.h>

typedef struct{
  char readWrite;
  int address;
}line;
typedef struct{
  int* valid;
  int* dirty;
  int* tag;
  int* LRU;
} set;

int my_log2(int input);
int my_pow(int power);
int lruIndex(set* const theSet, const int ASSOC);
set* makeCache(int* const parameters);
void printStats(int* const parameters, const int offsetBits,
               const int indexBits);
void simWT_NWA(set* theCache, line* const lineIn, int* const parameters,
              const int offsetBits, const int indexBits, const int SIZE);
void simWB_WA(set* theCache, line* const lineIn, int* const parameters,
              const int offsetBits, const int indexBits, const int SIZE);
void deallocCache(set* theCache, const int numSets);

int main(){
  //parameters[0]-blockSize, parameters[1]-numSets, parameters[2]- associativ
  int parameters[3];
  set *cacheWB, *cacheWT;
  line lineIn[100];
  int i;

  for(i = 0; i < 3; i++)
    scanf("%d\n", &(parameters[i]));

  //printf("Read in parameters.\n");

  const int offsetBits = my_log2(parameters[0]);
  const int indexBits = my_log2(parameters[1]);

  i = 0;
  while(scanf("%c %d\n", &(lineIn[i].readWrite), &(lineIn[i].address)) == 2){
    i++;
    //printf("Reading in addresses\n");
  }

  const int SIZE = i;

  cacheWT = makeCache(parameters);
  cacheWB = makeCache(parameters);

  printStats(parameters, offsetBits, indexBits);
  simWT_NWA(cacheWT, lineIn, parameters, offsetBits, indexBits, SIZE);
  simWB_WA(cacheWB, lineIn, parameters, offsetBits, indexBits, SIZE);

  //Free dynamically allocated memory.
  /*for(i = 0; i < parameters[1]; i++){
    free(cacheWB[i].valid);
    free(cacheWB[i].dirty);
    free(cacheWB[i].tag);
    free(cacheWB[i].LRU);
  }
  free(cacheWB);
  for(i = 0; i < parameters[1]; i++){
    free(cacheWT[i].valid);
    free(cacheWT[i].dirty);
    free(cacheWT[i].tag);
    free(cacheWT[i].LRU);
  }
  free(cacheWT);*/
  deallocCache(cacheWT, parameters[1]);
  cacheWT = 0;
  deallocCache(cacheWB, parameters[1]);
  cacheWB = 0;

  return 0;
}

int my_log2(int input){
  int counter = 0;
  input = input >> 1;
  while(input != 0){
    input = input >> 1;
    counter++;
  }
  return counter;
}

int my_pow(int power){
  int i, value = 1;
  for(i = 1; i <= power; i++)
    value = value << 1;

  return value;
}

int lruIndex(set* const theSet, const int ASSOC){
  int i, minLRU, index = 0;
  minLRU = theSet->LRU[0];

  for(i = 1; i < ASSOC; i++)
    if(minLRU > theSet->LRU[i]){
      minLRU = theSet->LRU[i];
      index = i;
    }
  return index;
}

set* makeCache(int* const parameters){
    int j;
    set* temp = (set*)calloc(parameters[1],sizeof(set));

    for(j = 0; j < parameters[1]; j++){
      temp[j].valid = (int*)calloc(parameters[2], sizeof(int));
      temp[j].dirty = (int*)calloc(parameters[2], sizeof(int));
      temp[j].tag = (int*)calloc(parameters[2], sizeof(int));
      temp[j].LRU = (int*)calloc(parameters[2], sizeof(int));
    }
    return temp;
}

void printStats(int* const parameters, const int offsetBits,
               const int indexBits){
  printf("Block size: %d\n", parameters[0]);
  printf("Number of sets: %d\n", parameters[1]);
  printf("Associativity: %d\n", parameters[2]);
  printf("Number of offset bits: %d\n", offsetBits);
  printf("Number of index bits: %d\n", indexBits);
  printf("Number of tag bits: %d\n", 32 - offsetBits - indexBits);
}

void simWT_NWA(set* theCache, line* const lineIn, int* const parameters,
              const int offsetBits, const int indexBits, const int SIZE){
  char hitFlag = 0;
  int i = 0, j = 0, hits = 0, index = 0, tag = 0, misses = 0, memRefs = 0,
      getIndex = 0, lruCounter = 1, minLRU = 0;

  //Bitmask to grab index value.
  getIndex = my_pow(indexBits) - 1;

  for(i = 0; i < SIZE; i++){
    //printf("SIMULATION: %d\n", i);
    index = ((lineIn[i].address >> offsetBits) & getIndex) % parameters[1];
    tag = lineIn[i].address >> (indexBits + offsetBits);
    //printf("The index is: %d\n", index);
    //printf("The tag is: %d\n", tag);
    hitFlag = 0;
    //Read reference
    if(lineIn[i].readWrite == 'R'){
      //printf("Read reference\n");
      //Check set for hit.
      for(j = 0; j < parameters[2]; j++)
        if(theCache[index].valid[j] == 1 && theCache[index].tag[j] == tag){
          hitFlag = 1;
          break;
        }
      //Data in cache. Update counter.
      if(hitFlag){
        theCache[index].LRU[j] = lruCounter;
        hits++;
      }
      //Data not in cache, insert into cache.
      else{
        //Check to see if there is room in set. If so, insert into cache.
        for(j = 0; j < parameters[2]; j++)
          if(theCache[index].valid[j] == 0){
            //printf("Writing to cache\n");
            theCache[index].valid[j] = 1;
            //printf("Wrote valid bit\n");
            theCache[index].tag[j] = tag;
            //printf("Wrote tag\n");
            theCache[index].LRU[j] = lruCounter;
            //printf("Wrote LRU\n");
            break;
          }
        //Check if cache insert was unsuccessful, replace using LRU.
        if(j >= parameters[2]){
          //printf("Insert unsuccessful. Replace using LRU.\n");
          minLRU = lruIndex(&(theCache[index]), parameters[2]);
          theCache[index].tag[minLRU] = tag;
          theCache[index].LRU[minLRU] = lruCounter;
        }
        memRefs++;
        misses++;
      }
    }
    //Write reference
    else{
      //printf("Write reference\n");
      //Check set for hit.
      for(j = 0; j < parameters[2]; j++)
        if(theCache[index].valid[j] == 1 && theCache[index].tag[j] == tag){
          hitFlag = 1;
          break;
        }
      //Data in cache. Update counters.
      if(hitFlag){
        theCache[index].LRU[j] = lruCounter;
        hits++;
        memRefs++;
      }
      //Data not in cache. Update counters.
      else{
        misses++;
        memRefs++;
      }
    }
    lruCounter++;
    //printf("Hits: %d\n", hits);
    //printf("Misses: %d\n", misses);
    //printf("Memory References: %d\n\n", memRefs);
  }
  printf("****************************************\n");
  printf("Write-through with No Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %d\n", SIZE);
  printf("Hits: %d\n", hits);
  printf("Misses: %d\n", misses);
  printf("Memory References: %d\n", memRefs);
}

void simWB_WA(set* theCache, line* const lineIn, int* const parameters,
              const int offsetBits, const int indexBits, const int SIZE){
  char hitFlag = 0;
  int i = 0, j = 0, hits = 0, index = 0, tag = 0, misses = 0, memRefs = 0,
      getIndex = 0, lruCounter = 1, minLRU = 0;

  //Bitmask to grab index value.
  getIndex = my_pow(indexBits) - 1;

  for(i = 0; i < SIZE; i++){
    //printf("SIMULATION: %d\n", i);
    index = ((lineIn[i].address >> offsetBits) & getIndex) % parameters[1];
    tag = lineIn[i].address >> (indexBits + offsetBits);
    //printf("The index is: %d\n", index);
    //printf("The tag is: %d\n", tag);
    hitFlag = 0;
    //Read reference
    if(lineIn[i].readWrite == 'R'){
      //printf("Read reference\n");
      //Check set for hit.
      for(j = 0; j < parameters[2]; j++)
        if(theCache[index].valid[j] == 1 && theCache[index].tag[j] == tag){
          hitFlag = 1;
          break;
        }
      //Data in cache. Update counter.
      if(hitFlag){
        //printf("Hit.\n");
        theCache[index].LRU[j] = lruCounter;
        hits++;
      }
      //Data not in cache, insert into cache.
      else{
        //printf("Miss.\n");
        //Check to see if there is room in set. If so, insert into cache.
        for(j = 0; j < parameters[2]; j++)
          if(theCache[index].valid[j] == 0){
            //printf("Free spot found in cache LINE %d of SET %d\n",j, index);
            //printf("Writing to cache\n");
            theCache[index].valid[j] = 1;
            //printf("Wrote valid bit\n");
            theCache[index].dirty[j] = 0;
            //printf("Cleared dirty bit\n");
            theCache[index].tag[j] = tag;
            //printf("Wrote tag\n");
            theCache[index].LRU[j] = lruCounter;
            //printf("Wrote LRU\n");
            break;
          }
        //Check if cache insert was unsuccessful, replace using LRU.
        if(j >= parameters[2]){
          //printf("Insert unsuccessful. Replace using LRU.\n");
          minLRU = lruIndex(&(theCache[index]), parameters[2]);
          //If cache line to replace is dirty, update counter
          if(theCache[index].dirty[minLRU]){
            //printf("Cache dirty. Updating counters.\n");
            memRefs++;
          }
          //printf("Writing to cache.\n");
          theCache[index].dirty[minLRU] = 0;
          theCache[index].tag[minLRU] = tag;
          theCache[index].LRU[minLRU] = lruCounter;
        }
        memRefs++;
        misses++;
      }
    }
    //Write reference
    else{
      //printf("Write reference\n");
      //Check set for hit.
      for(j = 0; j < parameters[2]; j++)
        if(theCache[index].valid[j] == 1 && theCache[index].tag[j] == tag){
          hitFlag = 1;
          break;
        }
      //Data in cache. Update counter.
      if(hitFlag){
        //printf("Hit. Writing dirty bit.\n");
        theCache[index].dirty[j] = 1;
        theCache[index].LRU[j] = lruCounter;
        hits++;
      }
      //Data not in cache. Update counters.
      else{
        //printf("Miss.\n");
        //Check to see if there is room in set. If so, insert into cache.
        for(j = 0; j < parameters[2]; j++)
          if(theCache[index].valid[j] == 0){
            //printf("Free spot found in cache LINE %d of SET %d\n",j, index);
            //printf("Writing to cache\n");
            theCache[index].valid[j] = 1;
            //printf("Wrote valid bit\n");
            theCache[index].dirty[j] = 1;
            //printf("Cleared dirty bit.\n");
            theCache[index].tag[j] = tag;
            //printf("Wrote tag\n");
            theCache[index].LRU[j] = lruCounter;
            //printf("Wrote LRU\n");
            break;
          }
        //Check if cache insert was unsuccessful, replace using LRU.
        if(j >= parameters[2]){
          minLRU = lruIndex(&(theCache[index]), parameters[2]);
          //printf("Insert unsuccessful. Replace using LRU in LINE %d of SET %d\n",
          //      minLRU, index);
          //If cache line to replace is dirty, update counter
          if(theCache[index].dirty[minLRU]){
            //printf("Dirty bit set. Updating counters.\n");
            memRefs++;
          }
          //printf("Writing to cache.\n");
          theCache[index].dirty[minLRU] = 1;
          theCache[index].tag[minLRU] = tag;
          theCache[index].LRU[minLRU] = lruCounter;
        }
        misses++;
        memRefs++;
      }
    }
    lruCounter++;
    //printf("Hits: %d\n", hits);
    //printf("Misses: %d\n", misses);
    //printf("Memory References: %d\n\n", memRefs);
  }
  printf("****************************************\n");
  printf("Write-back with Write Allocate\n");
  printf("****************************************\n");
  printf("Total number of references: %d\n", SIZE);
  printf("Hits: %d\n", hits);
  printf("Misses: %d\n", misses);
  printf("Memory References: %d\n", memRefs);
}

void deallocCache(set* theCache, const int numSets){
  int i;
  for(i = 0; i < numSets; i++){
    free(theCache[i].valid);
    free(theCache[i].dirty);
    free(theCache[i].tag);
    free(theCache[i].LRU);
  }
  free(theCache);
}
