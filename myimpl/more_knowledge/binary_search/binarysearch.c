#include <stdio.h>
#include <stdlib.h>

int binary_search_iter(int needle, int* array, const int size)
{
     int i;
     int lg2size = size;
     /* first find log2(size) since this is the max number of times to iterate */
     int MAX = 0;
     while( lg2size >>= 1)
	  MAX++;
     MAX++; // keep worst case
     /* actual search */
     int low = 0;
     int high = size;
     int index = (low + high)/2;
     int val;
     for (i = 0; i < MAX; i++)
     {
	  val = array[index];
	  printf("array[%d] = %d\n", index, val);
	  if (val < needle)
	  {
	       low = index + 1;
	       index = (low + high) / 2;
	       continue;
	  }
	  if (val == needle)
	       return index;
	  if (val > needle)
	  {
	       high = index - 1;
	       index = (low + high) / 2;
	       continue;
	  }
     }

     // not found
     return -1;
}

int main()
{
     int arr[10] = {1,3,5,6,7,8,11,12,13,55};
     int foundat = binary_search_iter(55, arr, 10);
     printf("foundat %d\n", foundat);
     return 0;
}
