/* Calculate the shortest distance given the input. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct vertex {
    int isVisited; /* 1 or 0 */
    int dist; /* distance to source vertex */
    int prev; /* previous vertex */
    int next; /* next vertex in the shortest path */
};

int n, s, t;  /* number of vertices, source vertex, target vertex */
int **a = NULL; /* adjacency matrix */
struct vertex *v = NULL;  /* store the attrs of each vertex */
int curr; /* current vertex in Dijkstra algorithm */
int next; /* next vertex in Dijkstra algorithm */
int shortest;  /* shortest path to unvisited vertex */
int load; /* num of nodes for each thread to calculate */
int max;  /* max_threads */

/* update v[].dist of adjacent nodes of the current */
void *thread_func(int i){
  int begin = i * load;
  int end = (i == max-1)? n: begin + load;
  for (int j = begin; j < end; j++){
    /* only check unvisited vertex */
    if (v[j].isVisited == 0){
      /* update next node */
      if ( (a[curr][j] > 0) && (v[j].dist == 0 || v[curr].dist + a[curr][j] < v[j].dist) ){ /* update v[j].dist */
        v[j].dist = v[curr].dist + a[curr][j];
        v[j].prev = curr;
      }
      /* compare v[j].dist with v[curr].dist + edge(curr,j) if j is available */
      if ( (v[j].dist > 0) && (shortest == -1 || v[j].dist < shortest)){
        shortest = v[j].dist;
        next = j;
      }
    }
  }
  return NULL;
}

void dist (int max_threads){
  /* Your code here. */
  int ret __attribute__((unused));
  /* read the input: number of vertices, source vertex, target vertex */
  ret = scanf("%d %d %d", &n, &s, &t);

  /* create a n*n matrix */  
  a = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++){
    a[i] = (int *)malloc(n * sizeof(int));
  }

  /* initialize the adjacency matrix */
  /* A[i][j] represents the weight of the edge from vertex i to j */
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      ret = scanf("%d", &a[i][j]);
    }
  }

  /* create an array to record the attrs of each vertex */
  v = (struct vertex *)malloc(n * sizeof(struct vertex));
  
  for (int i = 0; i < n; i++){  /* initialize */
    v[i].isVisited = 0;
    v[i].dist = 0;
    v[i].prev = -1;
    v[i].next = -1;
  }

  pthread_t *threads = malloc (sizeof (*threads) * max_threads);

  load = n / max_threads; /* num of nodes for each thread to calculate */
  max = max_threads;
  /* Dijkstra algorithm */
  curr = s; /* start from source */
  while (curr != t){
    /* marked curr as visited */
    v[curr].isVisited = 1;

    shortest = -1;  /* shortest path to unvisited vertex */
    next = -1;  /* next vertex to visit */
    
    /* create threads */
    for (int i = 0; i < max_threads; ++i){
      pthread_create(threads + i, NULL, thread_func, i);
    }
    /* join threads */
    for (int i = 0; i < max_threads; ++i){
      pthread_join(threads[i], NULL);
    }
    curr = next;
  }

  /* find the shortest path from the last vertex */
  while (curr != s){
    v[v[curr].prev].next = curr;
    curr = v[curr].prev;
  }

  /* output */
  printf("%d\n%d\n", v[t].dist, s);
  while (curr != t){
    printf("%d\n", v[curr].next);
    curr = v[curr].next;
  }

  /* memory release */
  free(v);
  for (int i = 0; i < n; i++){
    free(a[i]);
  }
  free(a);
  free (threads);
}
