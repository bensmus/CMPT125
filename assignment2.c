#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

#define WHITE 0
#define RED 1

void print_square_array(int N, int ar[N][N])
{
	for (size_t y = 0; y < N; y++)
	{
		for (size_t x = 0; x < N; x++)
		{
			printf("%d ", ar[y][x]);
		}
		printf("\n");
	}
}

long foo(int n)
{
	if (n == 0)
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	if (n == 2)
	{
		return 2;
	}

	if (n % 2 == 0)
	{
		return n;
	}

	return (-2 - 3 * (n / 2 - 1));
}

int linear_search_rec(person *A, int n, int id)
{
	// A: pointer to array. n: length of array. id: searching for id
	// output: index of person with id, or -1
	static int index = 0;

	if (A[0].id == id)
	{
		return index;
	}
	if (n == 1)
	{
		return -1;
	}

	// Getting ready for recursive call.
	index++;
	size_t n_new = n - 1;
	person A_new[n_new];

	// Filling up A_new.
	for (size_t i = 1, i_new = 0; i < n; i++, i_new++)
	{
		A_new[i_new] = A[i];
	}

	return linear_search_rec(A_new, n_new, id);
}

int binary_search_rec(person *A, int n, int id)
{
	// index stores index of (first element of this array)
	// in (original array).
	static int index = 0;

	// middleval stores value we are comparing with id.
	int middleval_index = n / 2;
	int middleval = A[middleval_index].id;

	if (middleval == id)
	{
		return index + middleval_index;
	}
	if (middleval != id && n == 1)
	{
		return -1;
	}

	// Allocating room for array and updating index.
	size_t n_new = n / 2;
	if (id > middleval)
	{
		index += middleval_index + 1;
		if (n % 2 == 0)
		{
			n_new = n / 2 - 1;
		}
	}
	person A_new[n_new];

	if (middleval > id)
	{
		// Take left of middleval.
		for (size_t i = 0; i < middleval_index; i++)
		{
			A_new[i] = A[i];
		}
	}
	else
	{
		// Take right of middleval.
		for (size_t i = index, i_new = 0; i < n; i++, i_new++)
		{
			A_new[i_new] = A[index];
		}
	}

	return binary_search_rec(A_new, n_new, id);
}

void flood_fill(int N, int ar[N][N], point start)
{
	// start will be treated as the current point
	ar[start.y][start.x] = RED;

	// check right
	if (start.x + 1 < N)
	{
		if (ar[start.y][start.x + 1] == WHITE)
		{
			point right = {start.x + 1, start.y};
			flood_fill(N, ar, right);
		}
	}

	// check left
	if (start.x - 1 > -1)
	{
		if (ar[start.y][start.x - 1] == WHITE)
		{
			point left = {start.x - 1, start.y};
			flood_fill(N, ar, left);
		}
	}

	// check up
	if (start.y - 1 > -1)
	{
		if (ar[start.y - 1][start.x] == WHITE)
		{
			point up = {start.x, start.y - 1};
			flood_fill(N, ar, up);
		}
	}

	// check down
	if (start.y + 1 < N)
	{
		if (ar[start.y + 1][start.x] == WHITE)
		{
			point down = {start.x, start.y + 1};
			flood_fill(N, ar, down);
		}
	}
}

person *find_person(const char *file_name, int ID)
{
	FILE *fp;
	fp = fopen(file_name, "r");

	if (fp == NULL)
	{
		return NULL;
	}

	char person_name[100];
	int person_ID;

	while (fscanf(fp, "%d %s", &person_ID, person_name) != EOF)
	{
		if (person_ID == ID)
		{
			fclose(fp);
			person *person_pointer = malloc(sizeof(person));
			person_pointer->id = person_ID;
			person_pointer->name = person_name;
			return person_pointer;
		}
	}

	fclose(fp);
	return NULL;
}

/*
If person with ID is in file                                        [1]
If the person is not in the file [add p to file]                    [0]
If the file does not exist [create new file] [add p to file]        [0]
If error opening file                                               [-1]
*/

int add_person(const char *file_name, person p)
{
	FILE *fp;
	fp = fopen(file_name, "a");

	if (fp == NULL)
	{
		// there was error creating a new file or accessing old file
		fclose(fp);
		return -1;
	}

	person *person_pointer = find_person(file_name, p.id);
	if (person_pointer != NULL)
	{
		fclose(fp);
		return 1;
	}

	// add person!
	fprintf(fp, "%d %s\n", p.id, p.name);
	fclose(fp);
	return 0;
}