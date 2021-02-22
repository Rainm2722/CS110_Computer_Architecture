#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INFINITE_NUMBER 1919810;
int scanf_value __attribute__((unused));
/* a global mutex lock */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* define a struct to pack data */
//typedef struct{
    /* threads */
    int max;
    pthread_t* threads;
    /* size, source, destination */
    int size;
    int src;
    int dst;
    /* the current vertex in two directions of Dijkstra */
    int vertex;
    /* the adjacenct matrix */
    int **adj_mat;
    /* distance, find, previous */
    int *dis;
    int *find;
    int *prev;
//}Pack;
/* create a package */
//Pack package;
int min;
/* find the minimum of the path to the next vertex */
void* find_min(int x){
    //int x = (int) x_;
    
    int load = size / max;
    int cond = (x + 1) * load;
    if (x == max-1) cond = size;
    //printf("thread: %d\n", x);
    /* find the shortest distance between current vertex with adjacent vertices */
    for (int i = (x) * load; i < cond; i++){
        if (find[i] == 0 && dis[i] > 0 && dis[i] < min){
            min = dis[i];
            vertex = i;
        }
    }
    return NULL;
}

/* update the shortest-path of the graph */
void* update_graph(int x){
    //int x = (int)x_;
    int load = size / max;
    //pthread_mutex_lock(&mutex);
    int cond = (x + 1) * load;
    if (x == max-1) cond = size;
    for (int i = (x) * load; i < cond; i++){
        if(find[i] == 0){
            /* if dis[vertex] + adj_mat[vertex][i] < dis[i], then update prev and dis */
            if ( ((dis[i] > 0 && dis[vertex] + adj_mat[vertex][i] < dis[i]) || (dis[i] == -1)) && adj_mat[vertex][i] != 0 ){
                prev[i] = vertex;
                dis[i] = dis[vertex] + adj_mat[vertex][i];
            }
        }
    }
    //pthread_mutex_unlock(&mutex);
    return NULL;
}

/* Dijkstra from source to destination */
void dijkstra(){
    /* initialize the distance of the graph */
    for (int i = 0; i < size; i++){
        if(i == src) dis[i] = 0;
        dis[i] = (adj_mat[src][i] == 0)? -1: adj_mat[src][i];
    
        /* initialize the state of the vertices */
        find[i] = (i == src)? 1 : 0;

        /* initialize the previous vertex of the shortest-path */
        prev[i] = (adj_mat[src][i] == 0)? -1: src;
    }
    /* vertex_src for update vertex, d for update distance */
    vertex = src;

    /* Dijkstra */
    while(find[dst] != 1){/* check if the dst has been found */
        /* find the minimum of the path to the next vertex */
        //int count = 0;

        /* set the next vertex's status to 'Found' */
        

        min = INFINITE_NUMBER;
        for (int j = 0; j < max; ++j){
            pthread_create(threads + j, NULL, find_min, j);
        }
        /* join threads */
        for (int j = 0; j < max; ++j){
            pthread_join(threads[j], NULL);
        }
        find[vertex] = 1;
        /* update the shortest-path */
        for (int j = 0; j < max; ++j){
            pthread_create(threads + j, NULL, update_graph, j);
        }
        /* join threads */
        for (int j = 0; j < max; ++j){
            pthread_join(threads[j], NULL);
        }
    }
}

/* Calculate the shortest distance given the input. */
void
dist (int max_threads)
{
    /* get the input n, s and t */
    int n, s, t;
    scanf_value = scanf("%d %d %d", &n, &s, &t);
    
    /* build a two-dimension dynamic array for adj_mat_src */
    int **A;
    A = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++){
        A[i] = (int*)malloc(sizeof(int) * n);
    }
    /* build the adjacency matrix A[n][n] */
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf_value = scanf("%d", &A[i][j]);
        }
    }
    
    /* initialize data */
    threads = (pthread_t*)malloc(sizeof(*threads) * max_threads);
    max = max_threads;
    adj_mat = A;
    size = n;
    src = s;
    dst = t;
    find = (int*)malloc(sizeof(int) * size);
    dis = (int*)malloc(sizeof(int) * size);
    prev = (int*)malloc(sizeof(int) * size);

    /* run Dijkstra */
    dijkstra();

    /* output result */
    /* output distance */
    printf("%d\n", dis[dst]);
    /* create a temporary array to store vertices */
    int *next;
    next = (int*)malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++){
        next[i] = -1;
    }

    vertex = dst;
    /* reverse the array prev */
    while (vertex != src){
        next[prev[vertex]] = vertex;
        vertex = prev[vertex];
    }

    /* print vertices from src to dist */
    printf("%d\n", src);
    while (vertex != dst){
        printf("%d\n", next[vertex]);
        vertex = next[vertex];
    }
    
    /* free memory and exit */
    free(threads);
    free(find);
    free(dis);
    free(prev);
    for (int i = 0; i < n; i++){
        free(A[i]);
    }
    free(A);
    free(next);
    pthread_mutex_destroy(&mutex);
}
