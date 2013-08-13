#include <stdio.h>
#include <string.h>

#define N 52
#define MAX 3
char cards[N][MAX];
int num[N];

void test_input() {
  int i;
  for (i=0; i<N; i++)
    printf ("%s ", cards[i]);
  printf ("\n");
}

int match (char cards[N][MAX], int i, int j) {
  if (i<0 || j<0 || i>=N || j >=N)
    return 0;
  if (cards[i][0] == cards[j][0] ||
      cards[i][1] == cards[j][1])
    return 1;
  else
    return 0;
}

int find_match (char cards[N][MAX], int num[N], int i) {
  int j = i-1;
  int k;
  while (j >= 0 && num[j]==0)
    j --;

  k = j-1;
  while (k >=0 && num[k] == 0)
    k --;
  k = k-1;
  while (k >=0 && num[k] == 0)
    k --;

  if (match(cards, i, k))
      return k;

  if (match(cards, i, j))
      return j;

  return -1;
}

void solve (char cards[N][MAX], int num[N], int n) {
  int i, j, k;

  for (i=1; i<n; i++) {
    if (num[i] == 0) continue;
    j = find_match (cards, num, i);
    k = -1;
    while (j != -1) {
      k = j;
      j = find_match (cards, num, j);
    }
    if (k != -1) {
      num[k] += num[i]; num[i] = 0;
      printf ("%s %s\n", cards[k], cards[i]);
      strcpy (cards[k], cards[i]);
      i = k;
    }
  }
}

void output (int num[N], int n) {
  int i, count = 0;

  for (i=0; i<n; i++)
    if (num[i] != 0)
      count ++;

  printf ("%d pile remaining:", count);
  for (i=0; i<n; i++)
    if (num[i] != 0)
      printf (" %d", num[i]);
  printf ("\n"); 
}


int main() {
  int i;
  char card[MAX];

  while (scanf ("%s", card) != EOF) {
    if (!strcmp (card, "#")) break;
    else strcpy (cards[0], card);

    for (i=1; i<N; i++) {
      scanf ("%s", card);
      strcpy (cards[i], card);
    }

    /* test_input(); */
    for (i=0; i<N; i++)
      num[i] = 1;

    solve (cards, num, N);

    output (num, N); 
  }

  return 0;
}