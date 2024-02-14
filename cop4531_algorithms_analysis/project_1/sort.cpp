void sortArray(struct Students arr[], int numStudents)
{
   bool swapped = true;
   int i = j = 0;
   struct Students temp;

   while (swapped)
   {
      swapped = false;
      j++;
      for(i = 0; i < numStudents - j; i++)
      {
         if(!aPreceedsB(arr[i].lastname, arr[i+1].lastname))
         {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            swapped = true;
         }
      }
   }
}

bool aPreceedsB(string a, string b){
  bool result;
  for(int i=0; i<a.length(); ++i)
    a.[i] = toupper(a[i]);

  for(int i=0; i<b.length(); ++i)
    b.[i] = toupper(b[i]);

  if(a.compare(b) <= 0)
    result = true;
  else
    result = false;

  return result;
}
