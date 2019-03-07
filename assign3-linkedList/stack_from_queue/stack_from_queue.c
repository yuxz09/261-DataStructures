/***********************************************************
* Author: Yuxi Zhang
* Email: zhangyu8@oregonstate.edu
* Date Created: Feb 11th, 2019
* Filename: stack_from_queue.c
*
* Overview:
*   This program is an implementation of a stack using two 
*	instances of a queue. The stack functions worked on from
*	Worksheet 17 were re-implemented using the queue functions
*	worked on from Worksheet 18. The main used for testing is
*	included in this file, so that the program is able to be
*	compiled/built and run (see 'Usage').
*	The queue ADT allows for the following behavior:
*		- adding a new link to the back (enqueue)
*		- getting the value of the front
*		- removing the front link (dequeue)
*		- checking if the queue is empty
*	The stack implementation using the queue ADT " ":
*		- adding a new link to the front (push - expensive)
*		- removing the front link (pop)
*		- getting the value of the front link (top)
*		- checking if the stack is empty
*	The critical piece to utilizing two queues to implement a
*	stack involve using the second queue to properly dequeue
*	the first queue's links when performing a push operation 
*	and swapping the first and second queues so the first 
*	always represents the actual 'stack'. This makes this op
*	expensive, but then top and pop are easy/efficient ops
*	given that the queue ADT has O(1) access to the front.
*
*	Note that this implementation uses single links, i.e. each
*	link only has a next pointer. Each queue has a head and tail
*	pointer that point to first/last link respectively. Each stack
*	has two queue pointers.
*
* Usage:
* 	1) gcc -g -Wall -std=c99 -o stack_from_queue stack_from_queue.c
*	2) ./stack_from_queue 
************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef TYPE
#define TYPE int
#endif

// Single link
struct Link {
	TYPE value;
	struct Link* next;
};

// Single linked list with head and tail pointers
struct Queue {
	struct Link* head;
	struct Link* tail;
};

// Stack with two Queue instances
struct Stack {
	struct Queue* q1;
	struct Queue* q2;
};

/**
  	Internal func allocates the queue's sentinel. Sets sentinels' next to null,
  	and queue's head and tail to the sentinel.
	param: 	queue 	struct LinkedList ptr
	pre: 	queue is not null
	post: 	queue sentinel not null
			sentinel next points to null
			head points to sentinel (always)
			tail points to sentinel (always point to last link unless empty)
 */
void listQueueInit(struct Queue* queue) 
{
	/* FIXME: You will write this function */
	assert(queue != 0);
	//allocate queue's sentinel
	struct Link* sentinel = malloc(sizeof(struct Link));
	//queue sentinel not null
	assert(sentinel != 0);
    //set sentinel's next to null
    sentinel -> next = NULL;///////////////////
    //head points to sentinel
	queue -> head = sentinel;
	//tail always points to the last link, unless empty will points to sentinel
	queue -> tail = sentinel;
}

/**
	Allocates and initializes a queue.
	pre: 	none
	post: 	memory allocated for new struct Queue ptr
			queue init (call to _initQueue func)
	return: queue
 */
struct Queue* listQueueCreate() 
{	
     /* FIXME: You will write this function */
	struct Queue* queue = malloc(sizeof(struct Queue));
	assert(queue != 0);
	listQueueInit(queue);
	return queue;
}

/**
	Adds a new link with the given value to the back of the queue.
	param: 	queue 	struct Queue ptr
	param: 	value 	TYPE
	pre: 	queue is not null
	post: 	link is created with given value 
			link is added before current last link (pointed to by queue tail)
 */
void listQueueAddBack (struct Queue* queue, TYPE value) 
{
	/* FIXME: You will write this function */
	assert(queue != 0);
	//allocate memory space
//	printf("queue head %p\n", queue -> head);
//    printf("queue tail %p\n", queue -> tail);
	struct Link* newlink = malloc(sizeof(struct Link));
	newlink -> value = value;
	queue -> tail -> next = newlink;
	queue -> tail = newlink;
	newlink -> next = NULL;/////////////
//	printf("after adding new value %d\n", queue -> tail -> value);
}

/**
	Returns the value of the link at the front of the queue.
	param: 	queue 	struct Queue ptr
	pre:	queue is not null
	pre:	queue is not empty (i.e., queue's head next pointer is not null)
	post:	none
	ret:	first link's value 
 */
TYPE listQueueFront(struct Queue* queue) 
{
   /* FIXME: You will write this function */
	//since head always points to sentinel, not the firstlink
	return queue -> head -> next -> value;
}

/**
	Removes the link at the front of the queue and returns the value
	of the removed link.
	param: 	queue 	struct Queue ptr
	pre:	queue is not null
	pre:	queue is not empty (i.e., queue's head next pointer is not null)
	post:	first link is removed and freed (call to removeLink)
 */
TYPE listQueueRemoveFront(struct Queue* queue) 
{
	/* FIXME: You will write this function */
	assert(queue != 0);
	assert(listQueueIsEmpty(queue) == 0);//not empty
	//use temp as firstlink
	struct Link* temp = queue -> head -> next;
	//only one element, head points to sentinel, tail points to the one element
	TYPE tempvalue = temp -> value;
	if (queue -> head -> next == queue -> tail)///////////////////
    {
	    queue -> tail = queue -> head;
	    queue -> head -> next = NULL;
    }
    else
    {
        queue -> head -> next = queue -> head -> next -> next;
    }
	free(temp);
	return tempvalue;
}

/**
	Returns 1 if the queue is empty and 0 otherwise.
	param:	queue	struct Queue ptr
	pre:	queue is not null
	post:	none
	ret:	1 if queue head next pointer is null (empty); 
			otherwise 0 (not null; not empty)
 */
int listQueueIsEmpty(struct Queue* queue) 
{
	/* FIXME: You will write this function */
	if (queue -> head -> next == NULL)//head == tail, wrong
	{
		return 1;
	}
	return 0;
}

/**
	Deallocates every link in the queue including the sentinel,
	and frees the queue itself.
	param:	queue 	struct Queue ptr
	pre: 	queue is not null
	post: 	memory allocated to each link is freed
			" " sentinel " "
			" " queue " "
 */
void listQueueDestroy(struct Queue* queue) 
{
    assert(queue != NULL);
	while(!listQueueIsEmpty(queue)) {
		listQueueRemoveFront(queue);
	}
	free(queue->head);///////////////
	free(queue);
	queue = NULL;
}

/**
	Allocates and initializes a stack that is comprised of two 
	instances of Queue data structures.
	pre: 	none
	post: 	memory allocated for new struct Stack ptr
			stack q1 Queue instance init (call to queueCreate func)
			stack q2 Queue instance init (call to queueCreate func)
	return: stack
 */
struct Stack* listStackFromQueuesCreate() 
{
	/* FIXME: You will write this function */
	//allocate new struct stack ptr
	struct Stack* stack = malloc(sizeof(struct Stack));
	//init q1
	struct Queue* queue1 = listQueueCreate();
	//init q2
	struct Queue* queue2 = listQueueCreate();
	stack -> q1 = queue1;
	stack -> q2 = queue2;
	return stack;
};

/**
	Deallocates every link in both queues contained in the stack,
	(inc.the sentinel), the queues themselves and the stack itself.
	param:	stack 	struct Stack ptr
	pre: 	stack is not null
	pre:	queues are not null
	post: 	memory allocated to each link is freed along with the 
			two queues and stack themselves
	
	Note that I checked that q1 and q2 are not null in this function
	also when I could have just left the assertion to fail in queueDestroy
	if either were pointing to null, but I thought it best to be explicit,
	albeit slightly repetitive.
 */
void listStackDestroy(struct Stack* stack)
{
	assert(stack != NULL);
	assert(stack->q1 != NULL && stack->q2 != NULL);
	listQueueDestroy(stack->q1);
	listQueueDestroy(stack->q2);
	free(stack);
	stack = NULL;
}

/**
	Returns 1 if the stack is empty and 0 otherwise.
	param:	stack	struct Stack ptr
	pre:	stack is not null
	post:	none
	ret:	1 if q1 is empty; else, 0
*/
int listStackIsEmpty(struct Stack* stack)
{	
	/* FIXME: You will write this function */
	assert(stack != 0);
	if (listQueueIsEmpty(stack -> q1) == 1)//if q1 is empty
	{
		return 1;
	}
	return 0;
}

/**
	This internal function swaps what q1 and q2 pointers, such that
	q1 points to q2 and q2 points to q1.
	param: 	stack 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	stack is not null
	post: 	q1 points to the actual 'stack' with links
 */
void listSwapStackQueues(struct Stack* stack)
{
	/* FIXME: You will write this function */
	assert(stack != 0);
	struct Queue* tempqueue;
//	struct Queue* tempqueue = malloc(sizeof(struct Queue));
	//1st question, if it is swapped successfully,
	tempqueue = stack -> q1;
	stack -> q1 = stack -> q2;
	stack -> q2 = tempqueue;
	//q1 points to the actual 'stack'
	assert(stack -> q1 != 0);
	//q1 points to the actual 'stack' with links
	assert(listQueueIsEmpty(stack -> q1) == 0);//whether swap successful
	//free tempqueue
//	listQueueDestroy(tempqueue); 
//	printf("q1: %p\n", stack->q1);
//    printf("q2: %p\n", stack->q2);

}

/**
	Adds a new link with the given value to the back of the Queue q2.

	Then while Queue q1 isn't empty, the first link of the queue is 
	dequeued/removed and added to the back of Queue q2, so that in
	the end, Queue q2 has the new order to represent the stack properly
	with the new value at the front of the queue.
	param: 	stack 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	stack is not null
	post: 	new link is created w/ given value and added to end of q2
			the first link of q1 is removed and added to end of q2 until
			it's empty
			q1 and q2 are swapped
 */

void listStackPush(struct Stack* stack, TYPE value) 
{
	/* FIXME: You will write this function */
	//newlink with given value to the back of the queue
	listQueueAddBack(stack -> q2 , value);
//	printf("after adding, q2\n");
//	printQueue(stack -> q2);

	TYPE tempvalue;
	while(listQueueIsEmpty(stack -> q1) == 0)//not empty
	{		
		tempvalue = listQueueRemoveFront(stack -> q1);
		listQueueAddBack(stack -> q2, tempvalue);
	}
	listSwapStackQueues(stack);
 //   printf("after swapping, q1\n");
 //   printQueue(stack -> q1);
}


/**
	Removes the link at the top of the stack and returns its value.
	param: 	stack 	struct Stack ptr
	pre:	stack is not null
	pre:	stack is not empty
	post:	first link is removed and freed (call to removeLink)
	ret:	value of the removed link
 */
TYPE listStackPop(struct Stack* stack) 
{
	/* FIXME: You will write this function */
	assert(stack != 0);
	assert(listStackIsEmpty(stack) == 0);
	struct Link* temp = stack -> q1 -> head -> next;
	//only one element in stack
	if(temp == stack -> q1 -> tail)
    {
	    stack -> q1 -> tail = stack -> q1 -> head;
        stack -> q1 -> head -> next = NULL;
    }
    else
    {
        stack -> q1 -> head -> next = temp -> next;
    }
	TYPE tempvalue = temp -> value;
	free(temp);
	return tempvalue;
}

/**
	Returns the value of the link at the top of the stack.
	param: 	stack 	struct Stack ptr
	pre:	stack is not null
	pre:	stack is not empty
	post:	none
	ret:	first link's value 
 */
TYPE listStackTop(struct Stack* stack) 
{
	/* FIXME: You will write this function */
	assert(stack != 0);
	assert(listStackIsEmpty(stack) == 0);
	return stack -> q1 -> head -> next -> value;
}

/**
	Used for testing the stack from queue implementation.
 */

void assertTrue(int pred, char* msg) 
{
	printf("%s: ", msg);
	if(pred)
		printf("\tPASSED\n");
	else
		printf("\tFAILED\n");
}

int main() 
{
	struct Stack* s = listStackFromQueuesCreate();
	assert(s);
	printf("\n-------------------------------------------------\n"); 
	printf("---- Testing stack from queue implementation ----\n");
	printf("-------------------------------------------------\n"); 
	printf("stack init...\n");
	assertTrue(listStackIsEmpty(s) == 1, "stackIsEmpty == 1");
	
	printf("\npushing 4, 5, -300...\n");
	listStackPush(s, 4);
	listStackPush(s, 5);
	listStackPush(s, -300);
	
	assertTrue(listStackIsEmpty(s) == 0, "stackIsEmpty == 0");
	assertTrue(listStackPop(s) == -300, "\npopping; val == -300");
	assertTrue(listStackPop(s) == 5, "popping; val == 5");
	assertTrue(listStackTop(s) == 4, "top val == 4\t");
	assertTrue(listStackPop(s) == 4, "popping; val == 4");
	assertTrue(listStackIsEmpty(s) == 1, "stackIsEmpty == 1");
	// listStackPop(s); 	// should fail assert
	// listStackTop(s); 	// should fail assert

	printf("\npushing 0-9...\n");
	for(int i = 0; i < 10; i++) {
		listStackPush(s, i);
	}
	assertTrue(listStackTop(s) == 9, "top val == 9\t");

	listStackDestroy(s);

	return 0;
}

