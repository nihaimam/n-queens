#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

#define seed 7092 //define seed for srandom

//functions declared
//void swap(int *a, int *b);
//void randPerm(int a[], int n);
//int checkBoard(int b[], int n);
//void displayBoard(int b[], int n);
//double recursionAlgorithm(double r);

void swap(int *a, int *b)
{
  //performs a swap
  int temp = *a;
  *a = *b;
  *b = temp;
}

void randPerm(int a[], int n)
{
  //generate random board using loop
  //shuffle the array
  int i, j; //index
  for (i = n - 1; i > 0; i--)
  {
    j = random() % (i+1); //create random number
    swap(&a[i], &a[j]); //swap random
  }
}

int checkBoard(int b[], int n)
{
  //check if queens are diagonal or in the same row
  int x, y; //first & second index
  for (x = 0; x < n; x++)
  {
    for(y = x + 1; y < n; y++)
    {
      if (abs(x-y) == abs(b[x]-b[y])) //if queens are diagonal
      {
        return 0; //distances are equal, diagonal queens
      }
    }
  }
  return 1; //the board is correct
}

void displayBoard(int b[], int n)
{
  //prints a solution of n-queens
  int i, p;
  for (i = 0; i < n; i++) //row
  {
    for (p = 0; p < n; p++) //column
        {
            if (i==b[p]) //if row == element
            {
                printf("* "); //print a star/queen
            }
            else
            {
                printf("- "); //print dash/no queen
            }
        }
        printf("\n");
    }
}

double recursionAlgorithm(double r)
{
  //factorial function for size! stat
  if (r == 1)
  {
     return 1;
  }
  else
  {
     //recursively call the function
     return r * recursionAlgorithm(r - 1);
  }
}

int main()
{
  //seed the random number generator
  srandom(seed);

  int n; //number of queens

  //arrays to collect statistics
  //for each n calculate
  int min[21]; //minimum
  int max[21]; //maximum
  double mean[21]; //mean
  double size_power[21]; //size**size
  double size_factorial[21]; //size!

  for (n = 4; n < 21; n++) //loop for ever n from 4 to 20
  {
    int arr[n]; //array of size n
    for (int k = 0; k < n; k++) //initialize/fill in array
    {
      arr[k] = k;
    }

    printf("\n\n\n%d QUEENS\n\n",n);

    int ctr = 0; //counter
    int i, o; //index
    for (i = 0; i < 10; i++)
    {
      int count = 1; //start count at one
      randPerm(arr,n); //randomize the board
      
      while(!checkBoard(arr,n)) //if randperm doesnt give right permutation
      {
        randPerm(arr,n); //randomize the board again
        count++; //keep increasing count by one
      }

      if (i == 0) //for the first found solution
      {
        min[n] = count; //track min
        max[n] = count; //track max
        displayBoard(arr,n); //display the board
        printf("\n");
      }

      //display the array for every solution
      printf("[ ");
      for (o = 0; o < n; o++)
      {
        printf("%d ", arr[o]);
      }
      printf("]");

      printf("\n"); 
      min[n] = min(min[n],count); //calcuate min
      max[n] = max(max[n], count); //calculte max
      ctr += count; //add count to ctr
    }

    //collect statistics
    mean[n] = ctr/10.0f; //find average by dividng by the number of times
    double size = pow(n,n); //size ** size
    size_power[n] = size; //store size in stats
    double sizeFactorial = recursionAlgorithm(n); //size factorial by recursion
    size_factorial[n] = sizeFactorial; //store factorial in stat
  }

  printf("\n%2s%10s%13s%13s%15s%12s\n", "size", "min", "max", "mean", "size**size", "size!"); //print header of stats
  int q;
  for (q = 4; q < 21; q++) //for every n print the stats
  {
    //for every n print the stats stored in the arrays
    printf("%2d%13d%13d%13.1e%13.1e%13.1e\n", q, min[q], max[q], mean[q], size_power[q], size_factorial[q]);
  }
}
