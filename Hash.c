#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"

int hash(HashTable hTable, int key)
{
    return key % hTable->size;
}
treeptr createNode(int key)
{
    treeptr t = (treeptr)malloc(sizeof(struct node));
    t->key = key;
    t->left = t->right = t->parent = NULL;

    return t;
}
void destroyLL(treeptr *t)
{
    clearLL(*t);
    free(*t);
    *t = NULL;
}
void addLL(treeptr t, int key)
{
    treeptr temp = createNode(key);
    treeptr p = t, prev = t;

    while (p != NULL)
    {
        prev = p;
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (key <= prev->key)
    {
        prev->left = temp;
        temp->parent = prev->left;
    }
    else
    {
        prev->right = temp;
        temp->parent = prev->right;
    }
}
int containsLL(treeptr t, int key)
{
    if (t == NULL)
        return 0;

    return t->key == key ? 1 : 0 || containsLL(t->left, key) || containsLL(t->right, key);
}
//void removeLL(treeptr t,int key); you can change the function prototype
void clearLL(treeptr t)
{
    if (t != NULL)
    {
        clearLL(t->left);
        clearLL(t->right);

        t->left = t->right = NULL;

        treeptr *temp = &t;
        free(*temp);
        *temp = NULL;
    }
}
void displayLL(treeptr t)
{
    if (t != NULL)
    {
        displayLL(t->left);
        printf("%d ", t->key);
        displayLL(t->right);
    }
}

HashTable newHashTable(int size)
{
    HashTable h = (HashTable)malloc(sizeof(struct hash));
    h->table = (treeptr *)malloc(sizeof(struct node) * size);
    h->size = size;
}
void destroy(HashTable *hTable)
{
    for (int i = 0; i < (*hTable)->size; i++)
        destroyLL((*hTable)->table + i);
    (*hTable)->table = NULL;
    free(*hTable);
    *hTable = NULL;
}
void add(HashTable hTable, int key)
{
    int hashKey = hash(hTable, key);
    if (hTable->table[hashKey] == NULL)
        hTable->table[hashKey] = createNode(key);
    else
        addLL(hTable->table[hashKey], key);
}
//void removeH(HashTable hTable,int key);
int contains(HashTable hTable, int key) { return containsLL(hTable->table[hash(hTable, key)], key); }
void clear(HashTable hTable)
{
    for (int i = 0; i < hTable->size; i++)
    {
        clearLL(hTable->table[i]);
        hTable->table[i] = NULL;
    }
}
void display(HashTable hTable)
{
    for (int i = 0; i < hTable->size; i++)
    {
        printf("[%d] = [ ", i);
        displayLL(hTable->table[i]);
        printf("]\n");
    }
}
