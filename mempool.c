#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block{
    size_t size;
    bool isActive;
    struct Block* next;  
}Block;

//initialize
#define MEMORY_POOL_SIZE 1024
#define BLOCK_SIZE (sizeof(Block))

static char MemoryPool[MEMORY_POOL_SIZE];  // define a memory pool, 1024 bytes
static Block* freelist = NULL;

void* mymalloc(size_t size){
    Block* current = freelist;
    // iterate the memory pool
    while(current != NULL){
        if(current->size >= size + BLOCK_SIZE){
            // try to split
            if(current->size > size + BLOCK_SIZE){
                Block* newBlock = (Block*)((char*)current+size+BLOCK_SIZE);
                newBlock->size = current->size-BLOCK_SIZE-size;
                newBlock->isActive = false;
                newBlock->next = current->next;
                current->next = newBlock;
            }
            return (void*)((char*)current+BLOCK_SIZE);  //return memory and metadata block
        }
        current = current->next;
    }
    return NULL;
}

void mtfree(void* ptr){
    if(ptr == NULL) return;

    Block* freeblock = (char*)ptr - BLOCK_SIZE;
    freeblock->isActive = true;

    // try to merge the blocks
    Block* current = freelist;
    while(current != NULL){
        if(current->isActive && current->next && current->next->isActive){
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

int main(){

    return 0;
}