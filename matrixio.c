#include <stdio.h>
#include <stdlib.h>

#include "matrixio.h"
#include "randpi.h"

#define CENT 64

void _print_paren(int*,int*,int,int);

// Fonctions de lecture et affichage, représentation brute
int* read_matrix (int* m, int* n)
{
  int *r, i;
  scanf("%d %d",m,n);
  if (0 == (r=malloc ((*m)*(*n)*sizeof(int))))
      return NULL;

  for (i = 0 ; i < (*m)*(*n) ; i++)
    scanf("%d ", r + i);
  
  return r;
}

int** read_matrices (int** t, int* n_mat)
{
        scanf("%d ", n_mat);
	int _n;
	int **m=malloc((*n_mat)*sizeof(int*));
	int *s=malloc((*n_mat+1)*sizeof(int));
        int i;

        if (m==NULL || s==NULL)
	    return NULL;

	for (i=0 ; i<(*n_mat) ; i++)
	{
	  m[i]=read_matrix(s+i,s+i+1);
	  if (i>0&&_n!=s[i])
	  {
	      printf("Matrix sizes not compatible :");
	      printf("%dx%d, %dx%d\n",s[i-1],_n,s[i],s[i+1]);
	      return NULL;
	  }
	  _n=s[i+1];
	}
	*t=s;
	return m;
}

int* fread_matrix (FILE* f, int* m, int* n)
{
  int *r, i;
  fscanf(f,"%d %d",m,n);
  if (0 == (r=malloc (*m**n*sizeof(int))))
      return NULL;

  for (i = 0; i < *m * *n; i++)
    fscanf(f,"%d ", r + i);
  
  return r;
}

int** fread_matrices (FILE* f, int** t, int* n_mat)
{
        fscanf(f,"%d ", n_mat);
	int _n;
	int **m=malloc((*n_mat)*sizeof(int*));
	int *s=malloc((*n_mat+1)*sizeof(int));
        int i;
        
	for (i=0 ; i<*n_mat ; i++)
	{
	  m[i]=fread_matrix(f,s+i,s+i+1);
	  if (i>0&&_n!=s[i])
	  {
	      printf("Matrix sizes not compatible :");
	      printf("%dx%d, %dx%d\n",s[i-1],_n,s[i],s[i+1]);
	      return NULL;
	  }
	  _n=s[i+1];
	}
	*t=s;
	return m;
}

//On va afficher les coefficients modulo 100
void print_matrix (int* A, int m, int n)
{
  int i;
  printf ("Matrix %d %d :\n", m, n);

  for (i = 0; i < m * n; i++)
    printf((i + 1) % n ? "%3d " : "%3d\n", (A[i]%CENT+CENT)%CENT);
}

// Affiche le parenthésage représenté par tree
// (arbre de coupures) de n coupures
// avec les tailles s des matrices
void print_paren(int* tree, int* s, int n)
{
    if (!n)
    {
	printf("%d\n",0);
	return;
    }

    _print_paren(tree,s,n,0);
    printf("\n");
    return;
}

void print_rand(int n_mat, int min, int max)
{
    int *s, i, j;
    int **m=randmatrices(n_mat,&s,min,max);
    srand(n_mat*max*min);
    printf("%d\n",n_mat);
    for (i=0 ; i<n_mat ; i++)
    {
	printf("%d %d\n",s[i], s[i+1]);
        for (j = 0; j < s[i] * s[i+1]; j++)
            printf((j + 1) % s[i+1] ? "%3d " : "%3d\n", m[i][j]);
    }
    return;
}


/* Fonctions auxiliaires */

// Représentation sous-matrice
void print_extr(int* A, int m, int n, int w)
{
#ifdef PRINT
    int i,j;
    printf("Matrix %d %d :\n", m, n);

    for (i = 0 ; i<m ; i++)
	for (j = 0 ; j<n ; j++)
	    printf((j==n-1)?"%d\n":"%d ",A[j+i*w]);
#endif
}

void _print_paren(int* tree, int* s, int n, int i)
{
    if (tree[0]==1)
        printf("%d[%d,%d].",i,s[0],s[1]);
    else
    {
        printf("(");
        _print_paren(tree+1,s,tree[0]-1,i);
	printf(").");
    }

    if (tree[0]==n)
	printf("%d[%d,%d]",i+n,s[n],s[n+1]);
    else
    {
	printf("(");
	_print_paren(tree+tree[0],s+tree[0],n-tree[0],i+tree[0]);
	printf(")");
    }

    return;
}

int matrix_equal(int* A, int* B, int m, int n)
{
    int i;
    for (i=0 ; i<m*n ; i++)
	if (!(A[i]==B[i]))
	    return 0;
    return 1;
}
