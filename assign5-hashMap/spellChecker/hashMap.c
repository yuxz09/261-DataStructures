/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Yuxi Zhang
 * Date: Mar 3rd, 2019
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}
/*
sum all char in char* key
 */

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}
/*
r = 1*key[0] + 2*key[1] + 3*key[2] + ... +
 */

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    assert(link != 0);
    link->key = malloc(sizeof(char) * (strlen(key) + 1));/////
    assert(link -> key != 0);
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    link->key = NULL;
    free(link);
    link = NULL;
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    assert(map != 0);
    for (int i = 0; i < map -> capacity; i++)
    {
         struct HashLink* tempLink = map -> table[i];
         struct HashLink* dellink = NULL;
         while(tempLink != 0)
         {
            dellink = tempLink;
            tempLink = tempLink -> next;
            hashLinkDelete(dellink);           
         }      
    }
    free(map->table);///////////////need to free table here
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    int hashIndex = HASH_FUNCTION(key) % map -> capacity;
    int* valptr = NULL;
    //get bucket index
    if(hashIndex < 0)
    {
        hashIndex += map -> capacity;
    }
    struct HashLink* tempLink = map->table[hashIndex];
    while(tempLink != NULL)
    {
        if(strcmp(tempLink -> key, key) == 0)
        {
            valptr = &(tempLink -> value);
            return valptr;
        }
        tempLink = tempLink -> next;
    }
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.!!!!!
 * 
 * @param map
 * @param capacity The new number of buckets.
 */

/*
steps for create a new map:
hashMapNew(int capacity): malloc space for hashmap
hashMapInit(map, capacity): malloc space for table
hashLinkNew(const char* key, int value, HashLink* next): create new links

steps for free a map:
hashMapCleanUp(map):free each key within each link, free each link and free table
free(map)
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    // create a newmap with given capacity
    assert(map != 0);
    HashMap* newmap = hashMapNew(capacity);//already set new capacity to newmap
    assert(newmap != 0);
    struct HashLink* tempLink = NULL;
    int tempvalue = 0;
    char* tempkey = NULL;

    for (int i = 0; i < map -> capacity; i++)
    {
        tempLink = map -> table[i];
        while(tempLink != NULL)
        {
            tempkey = tempLink -> key;
            tempvalue = tempLink -> value;
            //rehashing
            hashMapPut(newmap, tempkey, tempvalue);
            tempLink = tempLink -> next;
        } 
    }
    //store original size
//    int orisize = map -> size;
    //no need to assign capacity    
    hashMapCleanUp(map);
    //map = newmap;///////////why can not directly assign newmap here
    map->table = newmap->table;
//    map->size = orisize;
    map->capacity = capacity;
  //  free(newmap);
}
     

    /*
    hashMapDelete(map);
    map = newmap;
     */


/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    assert(map != 0);
    assert(key != 0);
    int hashIndex = HASH_FUNCTION(key) % (map -> capacity);
    if(hashIndex < 0)
    {
        hashIndex += map -> capacity;
    }
    struct HashLink* tempLink = map -> table[hashIndex];
    while(tempLink != NULL)
    {
        //if find a link with given key already exists, update it
        if(strcmp(tempLink -> key, key) == 0)
        {
            tempLink -> value = value;
            //break;//when break here, tempLink will not equal to NULL
            return;
        }
        //not find, move forward
        tempLink = tempLink -> next;
    }  
    //put newlink with key.value at front of linkedlist, so pass map -> table[hashIndex] as next; 

    struct HashLink* newlink = hashLinkNew(key, value, map -> table[hashIndex]);
    assert(newlink != 0);
    map -> table[hashIndex] = newlink;
    map->size++;
    
    if(hashMapTableLoad(map) >= MAX_TABLE_LOAD)
    {
        resizeTable(map, hashMapCapacity(map)*2);
    }
}


/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != 0);
    assert(key != 0);
    struct HashLink* tempLink = NULL;
    int hashIndex = HASH_FUNCTION(key) % hashMapCapacity(map);////
    if (hashIndex < 0)
    {
        hashIndex += map->capacity;////
    }
    tempLink = map->table[hashIndex];
    struct HashLink* formerlink = NULL;
    ///////////////////////////////////////////
    while(tempLink != NULL)
    {
        if(strcmp(tempLink -> key, key) == 0 && tempLink -> next == NULL)
        {
            map->table[hashIndex] = tempLink -> next;
            hashLinkDelete(tempLink);
            map->size--;
            return;            
        }
        else
        {
            if(strcmp(tempLink ->next -> key, key) == 0)
            {
                formerlink = tempLink -> next;
                tempLink -> next = formerlink -> next;
                hashLinkDelete(formerlink);

                map->size--;
                return;
            }
            else
            {
                tempLink = tempLink->next; 
            }           
        }           
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map!= 0);

    int hashIndex = HASH_FUNCTION(key) % map->capacity;
    if(hashIndex < 0)
    {
        hashIndex += map -> capacity;
    }
    struct HashLink* tempLink = map->table[hashIndex];
    while(tempLink != NULL)
    {
        if(strcmp(tempLink -> key, key) == 0)
        {               
            return 1;
        }
        tempLink = tempLink -> next;
    }   
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert(map!= 0);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    assert(map!= 0);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    assert(map!= 0);
    int num = 0;
    struct HashLink* tempLink = NULL;
    for(int i = 0; i < map->capacity; i++)
    {
        tempLink = map->table[i];
        if(tempLink == NULL)
        {
            num++;
        }
    }
    return num;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    assert(map!= 0);
    assert(map->capacity!= 0);
    return hashMapSize(map)/ (double)hashMapCapacity(map);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
  // FIXME: implement
    struct HashLink* tempLink = NULL;
    for(int i = 0; i < map -> capacity; i++)
    {
        tempLink = map->table[i];
        if(tempLink != NULL)
        {
            printf("Bucket %d -> ", i);
            while (tempLink != NULL)
            {
                printf("(%s, %d) ->", tempLink->key, tempLink->value);
                tempLink = tempLink->next;
            }
            printf("\n");
        }
    }
}








