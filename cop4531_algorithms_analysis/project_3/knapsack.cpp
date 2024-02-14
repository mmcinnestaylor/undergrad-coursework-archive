/* n is the number of items */
void knapsack(unsigned int *weights, unsigned int *values, size_t n, unsigned
             long weight_limit){

    size_t i;
    unsigned long w;
    unsigned long c[n+1][weight_limit+1];
    bool* includedArr = new bool[n];
    for(i = 0; i < n; i++)
      includedArr[i] = false;

    for(i = 0; i <= n; i++){
      for(w = 0; w <= weight_limit; w++){
        if(i == 0 || w == 0)
          c[i][w] = 0;
        else if(weights[i-1] <= w){
          if(values[i-1] + c[i-1][w-weights[i-1]] > c[i-1][w])
            c[i][w] = values[i-1] + c[i-1][w-weights[i-1]];
          else
            c[i][w] = c[i-1][w];
        }
        else
          c[i][w] = c[i-1][w];
      }
    }

    unsigned long result = c[n][weight_limit];

    for(i = n, w = weight_limit; i > 0 && result > 0; i--){
      if(result == c[i-1][w])
        continue;
      else{
        includedArr[i-1] = true;
        result -= values[i-1];
        w -= weights[i-1];
      }
    }

    for(i = 0; i < n; i++)
      if(!includedArr[i])
        weights[i] = 0;

    delete [] includedArr;
}
