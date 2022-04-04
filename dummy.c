
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 0
#define FAILED 1

struct SomeThing
{
	int value;
};
typedef struct  Queue
{
	struct SomeThing thing;
	struct Queue *next;
	struct Queue *head;
	//struct Queue *tail;
}Queue;

Queue* InitQueue()
{
	Queue *dummy = (Queue*)malloc(sizeof(Queue));
	dummy->next = NULL;
	dummy->head = dummy->next;
	//dummy->tail = dummy->next;
	return dummy;
}

int EnQueue(Queue * thing,int value)
{
	int ret = SUCCESS;
	Queue * Node = (Queue * ) malloc(sizeof(Queue));
	if(NULL == Node)
	{
		ret = FAILED;
		goto end;
	}
	Node->thing.value = value;
	Node->next = NULL;
	/*
	if(thing->next != NULL)
	{
		thing->tail->next = Node;
		thing->tail = Node;
	}
	else
	{
		thing->next = Node;
		thing->head = Node;
		thing->tail = Node;
	}
	*/
	Queue *cur = thing->next;
	Queue *prev = thing;
	while(cur != NULL)
	{
		cur = cur->next;
		prev = prev->next;
	}
	prev->next = Node;
	thing->head = thing->next;
end:
	return ret;
}
void ListQueue(Queue *thing)
{
	Queue *cur = thing->next; 
	while(cur!= NULL)
	{
		printf("thing.value:%d\n",cur->thing.value);
		cur = cur->next;
	}
}

int DeQueue(Queue *thing, int value)
{
	int ret = FAILED;
	Queue *cur = thing->next;
	Queue *prev = thing;
	Queue *delNode = NULL;
	while( NULL != cur)
	{
		if(cur->thing.value == value)
		{
			ret = SUCCESS;
			delNode = cur;
			cur = cur->next;
			prev->next = cur;
			break;
		}
		cur = cur->next;
		prev = prev->next;
	}
	free(delNode);
	return ret;
}

int main()
{
	int ret = SUCCESS;
	int i = 0;
	Queue *dummy = NULL;
	dummy = InitQueue();
	if(NULL == dummy)
	{
		ret = FAILED;
		goto end;
	}
	for (i=0;i<20;i++)
	{
		ret = EnQueue(dummy,i);
		if(FAILED == ret)
		{
			goto end;
		}
		printf("insert value %d,result:%d\n",i,ret);
	}
	ListQueue(dummy);
	for(i=0;i<30;i++)
	{
		ret = DeQueue(dummy,i);
		printf("delete value %d,reuslt:%d\n",i,ret);
	}
end:
	return ret;
}

