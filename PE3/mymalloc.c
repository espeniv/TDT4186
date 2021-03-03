#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int has_initialized = 0;

// our memory area we can allocate from, here 64 kB
#define MEM_SIZE (64 * 1024)
uint8_t heap[MEM_SIZE];

// start and end of our own heap memory area
void *managed_memory_start;

// this block is stored at the start of each free and used block
struct mem_control_block
{
  int size;
  int free;
  struct mem_control_block *next;
};

// pointer to start of our free list
struct mem_control_block *free_list_start;

void mymalloc_init()
{

  // our memory starts at the start of the heap array
  managed_memory_start = &heap;

  // allocate and initialize our memory control block
  // for the first (and at the moment only) free block
  struct mem_control_block *m = (struct mem_control_block *)managed_memory_start;
  m->size = MEM_SIZE - sizeof(struct mem_control_block);

  //Mark block as free
  m->free = 1;

  // no next free block
  m->next = NULL;

  // initialize the start of the free list
  free_list_start = m;

  // We're initialized and ready to go
  has_initialized = 1;
}

int roundUp(int numToRound)
{
  int remainder = numToRound % 8;
  if (remainder == 0)
  {
    return numToRound;
  }
  return numToRound + 8 - remainder;
}

void split(struct mem_control_block *fitting_slot, size_t size)
{
  int roundedSize = roundUp(size);
  struct mem_control_block *new = (void *)((void *)fitting_slot + roundedSize + sizeof(struct mem_control_block));
  new->size = (fitting_slot->size) - roundedSize - sizeof(struct mem_control_block);
  new->free = 1;
  new->next = fitting_slot->next;
  fitting_slot->size = roundedSize;
  fitting_slot->free = 0;
  fitting_slot->next = new;
  printf("%ld was allocated with split in block with space: %d\n", size, fitting_slot->size);
  printf("Largest block of membytes remaining: %d\n", new->size);
}

void *mymalloc(long numbytes)
{
  if (has_initialized == 0)
  {
    mymalloc_init();
  }
  /* add your code here! */
  printf("Trying to allocate: %ld\n", numbytes);
  struct mem_control_block *curr, *prev;
  void *result;
  curr = free_list_start;

  while ((((curr->size) < numbytes) || ((curr->free) == 0)) && (curr->next != NULL))
  {
    prev = curr;
    curr = curr->next;
    printf("Checked one block\n");
  }
  if ((curr->size) == numbytes)
  {
    printf("Size of current block: %d\n", curr->size);
    curr->free = 0;
    result = (void *)(++curr);
    printf("%ld allocated with exact fit \n", numbytes);
    return result;
  }
  else if ((curr->size) > (numbytes + (sizeof(struct mem_control_block))))
  {
    printf("Size of current block: %d\n", curr->size);
    split(curr, numbytes);
    result = (void *)(++curr);
    return result;
  }
  else
  {
    result = NULL;
    printf("Not enough memory to allocate\n");
    return (void *)0;
  }
}

void myfree(void *firstbyte)
{
  /* add your code here! */
  if (((void *)heap <= firstbyte))
  {
    struct mem_control_block *curr = firstbyte;
    --curr;

    struct mem_control_block *current, *prev;
    current = free_list_start;
    while ((current->next) != NULL)
    {
      current->size += (current->next->size) + sizeof(struct mem_control_block);
      current->next = current->next->next;
      prev = current;
      current = current->next;
    }
  }
  else
    printf("myfree need a valid pointer\n");
}

int main(int argc, char **argv)
{

  /* add your test cases here! */
  mymalloc(42);
  mymalloc(10);
  mymalloc(12345);
  /*
  mymalloc(20);
  mymalloc(30);
  mymalloc(65426);
  mymalloc(10);
  mymalloc(12345);
  mymalloc(65328);
  */
}