#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>

struct lfile
{

  char name[26];

  int start, siz;

  int blocks[20];

};



void
linked ()
{

  int f[200], bs[20], p, i, j, k, a, st, len, n, alloc = 0;

  char name[26];

  struct lfile files[20];

  int nof;

  for (i = 0; i < 200; i++)
    f[i] = 0;

  printf ("Enter the number of Files...\n");

  scanf ("%d", &nof);

  for (int w = 0; w < nof; w++)

    {

      printf ("Enter the file name...\n");
      scanf ("%s", files[alloc].name);

      printf ("Enter the starting block...\n");

      scanf ("%d", &st);

// if(f[st]==1) // UNCOMMENT IF CHECKING IS REQUIRED
// {
//     printf("Block is already Allocated!\n");
//     continue;
// }
      f[st] = 1;

      printf ("Enter the number of blocks...\n");

      scanf ("%d", &n);

      printf ("Enter Block Numbers...\n");

      int flag = 0;

      for (i = 0; i < n; i++)

	{

	  scanf ("%d", &a);

// if(f[a]==1)
// {
//     printf("The block %d is already allocated!\n",a);
//     int flag=1;
//     break;
// }
	  f[a] = 1;

	  files[alloc].blocks[i] = a;

	}

// if(flag==1)continue;
      files[alloc].start = st;

      files[alloc].siz = n;

      alloc++;

    }

  printf ("\nFile\tStart\tSize\tBlock\n");

  for (int i = 0; i < alloc; i++)

    {

      printf ("%s\t%d\t%d\t", files[i].name, files[i].start, files[i].siz);

      printf ("%d ", files[i].blocks[0]);

      for (int j = 1; j < files[i].siz; j++)

	printf ("--> %d ", files[i].blocks[j]);

      printf ("\n");

    }
}

void
indexed ()
{

  int f[200], index[50], alocfil[50][3], allocated =
    0, i, n, st, len, j, c, k, ind, count = 0;

  for (i = 0; i < 200; i++)

    f[i] = 0;

  int nof;

  printf ("Enter the number of Files...\n");

  scanf ("%d", &nof);

  for (int w = 0; w < nof; w++)

    {

      printf ("Enter the index block: ");

      scanf ("%d", &ind);

      if (f[ind] != 1)

	{

	  printf ("Enter blocks occupied by the file : \n", ind);

	  scanf ("%d", &n);

	}

      else

	{

	  printf ("%d index is already allocated \n", ind);

	  continue;

	}

      count = 0;

      printf ("Enter blocks of file...\n ");

      for (i = 0; i < n; i++)

	{

	  scanf ("%d", &index[i]);

	  if (f[index[i]] == 0)

	    count++;

	}

      if (count == n)

	{

	  for (j = 0; j < n; j++)

	    f[index[j]] = 1;

	  printf ("Allocated!\n");

	  alocfil[allocated][0] = w + 1;

	  alocfil[allocated][1] = ind;

	  alocfil[allocated][2] = n;

	  allocated++;

	}

      else

	{

	  printf ("File in the index is already allocated \n");

	}
    }

  printf ("\nAllocated Blocks\nFile\tIndex\tLength\n");

  for (int i = 0; i < allocated; i++)

    {

      printf ("%d\t%d\t%d\n", alocfil[i][0], alocfil[i][1], alocfil[i][2]);

    }
}

void
seq ()
{

  int files[200], alocfiles[32][3];

  int startBlock, len, j, k, ch, allocated = 0;

  int n;

  for (int i = 0; i < 200; i++)

    files[i] = 0;

  printf ("Enter the number of files...\n");

  scanf ("%d", &n);

  for (int i = 0; i < n; i++)

    {

      int flag = 0;

      printf ("Enter the starting block and the length of the file %d:  ",
	      i + 1);

      scanf ("%d%d", &startBlock, &len);

      for (j = startBlock; j < (startBlock + len); j++)
	{

	  if (files[j] == 0)

	    flag++;

	}

      if (len == flag)
	{

	  for (int k = startBlock; k < (startBlock + len); k++)
	    {

	      if (files[k] == 0)
		{

		  files[k] = 1;

		}

	    }

	  printf ("The file %d is allocated to the disk\n", i + 1);

	  alocfiles[allocated][0] = i + 1;

	  alocfiles[allocated][1] = startBlock;

	  alocfiles[allocated][2] = len;

	  allocated++;

	}

      else

	printf ("The file %d is not allocated to the disk\n", i + 1);

    }

  printf ("\nAllocated Files:\n\nFile No\tStart Block\tLength\n");

  for (int i = 0; i < allocated; i++)

    {

      printf ("%d\t%d\t\t%d\n", alocfiles[i][0], alocfiles[i][1],
	      alocfiles[i][2]);

    }
  int filno;

  printf ("\nEnter File Number: ");

  scanf ("%d", &filno);

  for (int i = 0; i < allocated; i++)

    {

      if (alocfiles[i][0] == filno)

	{
	  printf ("File Number : %d\t Space Occupied : %d\n", alocfiles[i][0],
		  alocfiles[i][2]);

	  filno = -1;

	}

    }

  if (filno != -1)

    printf ("File Number Not Found!\n\n");

  return;

}



int
main ()
{
  printf ("File Allocations");

  int op = 0;

  while (op != 4)

    {

      printf
	("\n\n1. SEQUENTIAL\n2. INDEXED\n3. LINKED\n4. Exit\nEnter your option...\n\n");

      scanf ("%d", &op);

      switch (op)

	{

	case 1:

	  seq ();

	  break;

	case 2:

	  indexed ();

	  break;

	case 3:

	  linked ();

	  break;

	}

    }

}
