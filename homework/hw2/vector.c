/* HW2 */

#include "vector.h"
#include <stdlib.h>
#include <string.h>

/* Initialize */
int vector_init(Vector* vector, size_t capacity, size_t element_size){
    if (vector == NULL || element_size == 0)  /*check NULL*/
        return VECTOR_ERROR;
    vector->size = 0;
    vector->capacity = MAX(capacity, VECTOR_MINIMUM_CAPACITY);
    vector->element_size = element_size;
    /* Memory alloc */
    vector->data = malloc(vector->capacity * vector->element_size);
    if (vector->data == VECTOR_UNINITIALIZED)
        return VECTOR_ERROR;
    return VECTOR_SUCCESS;  /* return success */
}

int vector_copy(Vector* destination, Vector* source){
    /* check if dest is uninit */
    if (destination == NULL || source == NULL || source->data == VECTOR_UNINITIALIZED)  
        return VECTOR_ERROR;    /*check NULL*/
    destination->data = malloc(source->capacity * source->element_size);
    /* check if init successfully */
    if (destination->data == VECTOR_UNINITIALIZED)  
        return VECTOR_ERROR;
    /*dest_init*/
    destination->capacity = source->capacity;
    destination->element_size = source->element_size;
    destination->size = source->size;
    /*copy elements*/
    memcpy(destination->data, source->data, source->size * source->element_size);
    return VECTOR_SUCCESS;
}

/* Free the memory alloced */
int vector_destroy(Vector* vector){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED)   /* check */
        return VECTOR_ERROR;
    free(vector->data);
    return VECTOR_SUCCESS;
}


/* Memory management */
int vector_resize(Vector* vector, size_t new_size){
    void* tmp;
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED)
        return VECTOR_ERROR;
    while (new_size >= vector->capacity){   /* check memory */
        tmp = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        if (tmp == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(tmp, vector->data, vector->capacity * vector->element_size);
        free(vector->data); /* free the original memory*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
        vector->data = malloc(vector->capacity * vector->element_size);
        if (vector->data == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(vector->data, tmp, vector->capacity * vector->element_size);
        free(tmp);
    }
    /* change size */
    vector->size = new_size;
    return VECTOR_SUCCESS;
}

/* Insertion */
int vector_push_back(Vector* vector, void* element){
    void* tmp;
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || element == NULL)   /* check */
        return VECTOR_ERROR;
    memcpy((char *)vector->data + vector->size * vector->element_size, element, vector->element_size);
    ++vector->size;
    /* realloc if vector is full */
    if (vector->size >= vector->capacity){
        tmp = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        if (tmp == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(tmp, vector->data, vector->capacity * vector->element_size);
        free(vector->data); /* free the original memory*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
        vector->data = malloc(vector->capacity * vector->element_size);
        if (vector->data == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(vector->data, tmp, vector->capacity * vector->element_size);
        free(tmp);
    }
    return VECTOR_SUCCESS;    /* return success */
}

int vector_push_front(Vector* vector, void* element){
    void* tmp;
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || element == NULL )   /* check */
        return VECTOR_ERROR;
    memmove((char *)vector->data + vector->element_size, vector->data, vector->size * vector->element_size);
    memcpy(vector->data, element, vector->element_size);
    ++vector->size; /* size_inc */
    if (vector->size >= vector->capacity){
        tmp = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        if (tmp == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(tmp, vector->data, vector->capacity * vector->element_size);
        free(vector->data); /* free the original memory*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
        vector->data = malloc(vector->capacity * vector->element_size);
        if (vector->data == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(vector->data, tmp, vector->capacity * vector->element_size);
        free(tmp);
    }
    return VECTOR_SUCCESS;    /* return success */
}

/* insert at VECTOR[index] */
int vector_insert(Vector* vector, size_t index, void* element){
    void* tmp;
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || element == NULL || index >= vector->capacity)
        return VECTOR_ERROR;
    /* copy elements */
    memmove((char *)vector->data + (index + 1) * vector->element_size, (char *)vector->data + index * vector->element_size, (vector->size - index) * vector->element_size);
    memcpy((char *)vector->data + index * vector->element_size, element, vector->element_size);
    ++vector->size;
    if (vector->size >= vector->capacity){  /* realloc when full */
        tmp = malloc(VECTOR_GROWTH_FACTOR * vector->capacity * vector->element_size);
        if (tmp == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(tmp, vector->data, vector->capacity * vector->element_size);
        free(vector->data); /* free the original memory*/
        vector->capacity *= VECTOR_GROWTH_FACTOR;
        vector->data = malloc(vector->capacity * vector->element_size);
        if (vector->data == NULL)    return VECTOR_ERROR; /*check if malloc successfully */
        memcpy(vector->data, tmp, vector->capacity * vector->element_size);
        free(tmp);
    }
    /* return success */
    return VECTOR_SUCCESS;
}

/* assign to VECTOR[index] */
int vector_assign(Vector* vector, size_t index, void* element){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || element == NULL || index >= vector->size)
        return VECTOR_ERROR;
    /* assign */
    memcpy((char *)vector->data + index * vector->element_size, element, vector->element_size);
    return VECTOR_SUCCESS;
}

/* Deletion */
int vector_pop_back(Vector* vector){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || vector->size == 0)
        return VECTOR_ERROR;
    --vector->size; /* size_dec */
    return VECTOR_SUCCESS;
}

/* pop the first element */
int vector_pop_front(Vector* vector){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || vector->size == 0)
        return VECTOR_ERROR;
    /* copy other elements */
    memmove(vector->data, (char *)vector->data +vector->element_size, (vector->size - 1) * vector->element_size);
    --vector->size;
    return VECTOR_SUCCESS;  /* success */
}

/* delete VECTOR[index] */
int vector_erase(Vector* vector, size_t index){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED || vector->size == 0 || index >= vector->size)
        return VECTOR_ERROR;
    /* copy elements from right */
    memmove((char *)vector->data + index * vector->element_size, (char *)vector->data + (index + 1) * vector->element_size, (vector->size - index - 1) * vector->element_size);
    --vector->size;
    return  VECTOR_SUCCESS; /* success */
}

/* clear all the elements */
int vector_clear(Vector* vector){
    if (vector == NULL || vector->data == VECTOR_UNINITIALIZED)
        return VECTOR_ERROR;
    vector->size = 0;   /* set size to zero */
    return VECTOR_SUCCESS;
}

/* Lookup */
void* vector_get(Vector* vector, size_t index){ /* VECTOR[index] */
    if (vector == NULL || vector->data == NULL || index >= vector->size) return NULL;
    return (char *)vector->data + index * vector->element_size;
}

void* vector_front(Vector* vector){ /* VECTOR[0] */
    return vector->data;
}

void* vector_back(Vector* vector){  /* VECTOR[-1] */
    return (char *)vector->data + (vector->size - 1) * vector->element_size;
}

/* Information */
size_t vector_size(const Vector* vector){   /* return size */
    if (vector == NULL) return 0;
    return vector->size;
}

bool vector_is_empty(const Vector* vector){ /* TRUE when empty */
    if (vector == NULL) return false;
    return (vector->size == 0);
}

/* Iterators */
Iterator vector_begin(Vector* vector){
    Iterator it;
    /* check null */
    if (vector == NULL){
        it.pointer = NULL;
        it.element_size = 0;
        return it; /* return the iter */
    }
    /*assign*/
    it.pointer = vector->data;
    it.element_size = vector->element_size;
    return it; /* return the iter */
}

Iterator vector_end(Vector* vector){
    Iterator it;
    /* check null */
    if (vector == NULL){
        it.pointer = NULL;
        it.element_size = 0;
        return it; /* return the iter */
    }
    /*assign*/
    it.pointer = (char *)vector->data + vector->size * vector->element_size;
    it.element_size = vector->element_size;
    return it; /* return the iter */
}

Iterator vector_iterator(Vector* vector, size_t index){
    Iterator it;
    /* check null */
    if (vector == NULL || index >= vector->size){
        it.pointer = NULL;
        it.element_size = 0;
        return it; /* return the iter */
    }
    /* assign */
    it.pointer = (char *)vector->data + index * vector->element_size;
    it.element_size = vector->element_size;
    return it; /* return the iter */
}

/* get element */
void* iterator_get(Iterator* iterator){
    if (iterator == NULL)   return NULL;
    return iterator->pointer;
}

/* iter++ */
void iterator_increment(Iterator* iterator){
    if (iterator == NULL || iterator->pointer == NULL)  return;
    iterator->pointer = (char *)iterator->pointer + iterator->element_size;
}

/* iter-- */
void iterator_decrement(Iterator* iterator){
    if (iterator == NULL || iterator->pointer == NULL)  return;
    iterator->pointer = (char *)iterator->pointer - iterator->element_size;
}

/* iter_1 == iter_2 */
bool iterator_equals(Iterator* first, Iterator* second){
    if (first == NULL || second == NULL || first->pointer == NULL || second->pointer  == NULL)    return false;   
    return (first->pointer == second->pointer && first->element_size == second->element_size);
}

/* sort ascendingly */
void vector_sort(Vector *vector, vector_less_func *less){
    size_t i, j;
    void *tmp;
    if (vector == NULL || less == NULL) return; /* valid */
    tmp = malloc(vector->element_size);   /* use tmp to store element */
    for (i = 0; i < vector->size - 1; i++){
        for (j = 0; j < vector->size - 1 - i; j++){
            /* bubble sort */
            if (less((char *)vector->data + (j + 1) * vector->element_size, (char *)vector->data + j * vector->element_size)){
                memcpy(tmp, (char *)vector->data + j * vector->element_size, vector->element_size);
                memcpy((char *)vector->data + j * vector->element_size, (char *)vector->data + (j + 1) * vector->element_size, vector->element_size);
                memcpy((char *)vector->data + (j + 1) * vector->element_size, tmp, vector->element_size);
                /* exchange VECTOR[j], VECTOR[j+1] */
            }
        }
    }
    free(tmp);  /*free*/
}