#include <stdlib.h>
#include "hash.h"

struct HashTable{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn){
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));
    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;
    return hash_tbl;
}

void _hash_pair_destroy(HashTableItem *p){
    free(p);
}

//HA MODIFICACOES A SEREM FEITAS (hash table item)
void hash_table_set(HashTable *h, void *key, void *val){
    int index = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[index];
    if(bucket == NULL){
        bucket = forward_list_construct();
        h->buckets[index] = bucket;
    }

    HashTableItem *new_pair = malloc(sizeof(HashTableItem));
    new_pair->key = key;
    new_pair->val = val;

    data_type found_item = forward_list_find(bucket, key, h->cmp_fn);
    if(found_item != NULL){
        HashTableItem *found_pair = found_item;
        found_pair->val = val;
    }else{
        forward_list_push_front(bucket, new_pair);
        h->n_elements++;
    }

}

//HA MODIFICACOES A SEREM FEITAS (hash table item)
void *hash_table_get(HashTable *h, void *key){
    int index = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[index];

    if(bucket == NULL)
        return NULL;

    HashTableItem *found_pair = forward_list_find(bucket, key, h->cmp_fn);

    if(found_pair != NULL)
        return found_pair->val;
    else
        return NULL;
}

//HA MODIFICACOES A SEREM FEITAS (hash table item)
void *hash_table_pop(HashTable *h, void *key){
    int index = h->hash_fn(h, key);
    ForwardList *bucket = h->buckets[index];

    if(bucket == NULL)
        return NULL;

    HashTableItem *found_pair = forward_list_find(bucket, key, h->cmp_fn);

    if(found_pair != NULL) {
        void *value = found_pair->val;
        forward_list_remove(bucket, found_pair);
        _hash_pair_destroy(found_pair);
        h->n_elements--;
        return value;
    }else {
        return NULL;
    }
}

// numero de buckets
int hash_table_size(HashTable *h){
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h){
        return h->n_elements;
}

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h){
    for (int i = 0; i < h->table_size; i++){
        if (h->buckets[i] != NULL){
            Node *n = h->buckets[i]->head;

            while (n != NULL){
                HashTableItem *pair = n->value;
                _hash_pair_destroy(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
    }
}

    free(h->buckets);
    free(h);
}