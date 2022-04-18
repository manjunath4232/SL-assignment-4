// BT20CSE056 
// JC MANJUNATH

#include <stdio.h>
#include <stdlib.h>

struct Node 			     //block information
{
	int start;
	int end;
	int id;
	struct Node *next;		//point to next block
} *block_list = NULL;		//list point for allocated blocks

typedef struct Node block;

int mem_size;		//size of the memory
int rem_size;		//remaining memory

void printAlloc()
{
	block *next_block = block_list;
	printf ("ID\tStart\tEnd\n");
	printf ("------------------------------\n");

	while (next_block != NULL)
    {
    	printf ("%d\t%d\t%d\t\n", next_block->id, next_block->start,next_block->end-1);
    	next_block = next_block->next;
    }
	return;
}


void allocate_block()
{

	int block_id, block_size;   //block id and size of the block
	block *new_block, *curr_block;		
	int hole_start, hole_end;		//start and end of the hole	
	int flag = 0;	//flag to check if the hole is large enough to fit the block

	printf ("Enter block id: "); 
	scanf ("%d", &block_id);
	printf ("Enter block size: ");
	scanf ("%d", &block_size);

	if (block_size > rem_size)
    {
    	printf ("Cannot fit the block!! Try again with a smaller block size or enough memory\n");
    	return;
    }

	new_block = (block *) malloc (sizeof (block));
	new_block->id = block_id;

	if (block_list == NULL) //empty list
	{
    	new_block->start = 0;			//start of the block
    	new_block->end = block_size;	//end of the block
    	new_block->next = NULL;			//next block is null
    	block_list = new_block;			//new block is the head of the list
    	rem_size -= block_size;			//remaining memory is reduced
    	printAlloc();
    	return;
    }
  		//else traverse list until either appropriate free hole is found or end of list is reached
	curr_block = block_list;

	while (curr_block != NULL)			
    {
		if (block_id == curr_block->id)	//if the block id already exists
		{
			printf ("Block id already exists!! Try again with a different block id\n");
			return;
		}
      	hole_start = curr_block->end;		

      	if (curr_block->next != NULL)	//if the next block is not null
	  	{
	  		hole_end = curr_block->next->start;
	  	}
	  	else								//if the next block is null
	  	{
	  		hole_end = mem_size;
	  	}
		
    	if (block_size <= (hole_end - hole_start))	//if the hole is large enough to fit the block
		{
	  		flag = 1;							//flag is set to 1	
			new_block->start = hole_start;		//start of the block is set to the start of the hole
			new_block->end = hole_start + block_size;	//end of the block is set to the end of the hole
			rem_size -= block_size;			//remaining memory is reduced
			new_block->next = curr_block->next;		//next block is set to the next block
			curr_block->next = new_block;		//current block's next is set to the new block
			printAlloc ();
			return;
		}
    	curr_block = curr_block->next;
    }       

	if (flag == 0)
    {
    	printf ("No hole large enough");
    	return;
    }

	rem_size -= block_size;
	printAlloc ();
	return;
}

void deallocate_block()	
{
	block *curr_block = block_list;	//current block is set to the head of the list
	block *prev_block;	//point to previous block
	int block_id;
	curr_block = block_list;		

	if (curr_block == NULL)		//if the list is empty
    {
    	printf ("No blocks to free\n");
    	return;
    }

	printf ("Enter Block ID: ");
	scanf ("%d", &block_id);

	while ((curr_block != NULL) && (block_id != curr_block->id))	//linear search till id is found
    {
		prev_block = curr_block;
    	curr_block = curr_block->next;
    }
  	if (curr_block == NULL)
    {
      	printf ("\nBlock with given ID not found!!\n");
    }
  	else
    {
      	prev_block->next = curr_block->next;	
      	rem_size += curr_block->end - curr_block->start;
      	free (curr_block);
    }
  	printAlloc ();
  	return;
}

void destruction(block * Node)      //destructor
{

  	if (Node == NULL)
    {
      	return;
    }
  	else
    {
      	destruction(Node->next);
      	free(Node);
    }
  	return;
}

int main ()
{
	printf ("Enter size of physical memory: ");
	scanf ("%d", &mem_size);
	rem_size = mem_size;
  	int choice;
  	do
    {
      	printf ("------------------------------------------\n");
      	printf ("1) Allocate memory for block\n");
      	printf ("2) Deallocate memory for block\n");
      	printf ("3) Quit program\n");
      	printf ("------------------------------------------\n");

      	printf ("\nChoose one option: ");
      	scanf ("%d", &choice);
      	switch (choice)
		{
		case 1:
	  		allocate_block();
		  	break;
		case 2:
	  		deallocate_block();
			break;
		}
	}while (choice != 3);
  	destruction(block_list);
  	printf ("Program Exited!!!\n");
  	return 0;
}
