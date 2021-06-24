#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
	int value;
	struct Node* next;
} Node;
typedef struct {
	Node* head;
	Node* tail;
	int size;
}LinkedList;
void list_init(LinkedList* l)
{
	if (l == NULL)return;
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}
void list_insert(LinkedList* l, int value)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	if (l->head == NULL)
	{
		l->head = node;
		l->tail = node;
	}
	else
	{
		l->tail->next = node;
		l->tail = node;
	}
	l->size++;
}
void list_clear(LinkedList* l)
{
	Node* p1 = NULL;
	int i = 0;

		for (p1 = l->head; p1; ) {
			Node* temp = p1;
			p1 = p1->next;
			free(temp);
		}


	list_init(l);
}
void updateTail(LinkedList* l)
{
	Node* p1 = NULL;
	int i = 0;
	for (p1 = l->head; p1->next; p1 = p1->next);
	l->tail = p1;

}

Node* list_remove(LinkedList* l, Node* target)
{
	l->size--;
	Node* p1 = NULL;
	int i = 0;
	//空链表特殊情况
	if (l->head == NULL || l->tail == NULL || target == NULL)
	{
		goto Abnormal;
	}
	if (l->size == 0)
	{
		if (l->head == target)
		{
			free(target);
			list_init(l);
			
		}
		return NULL;
	}
	//队头特殊情况
	if (l->head == target)
	{
		// printf("First Num\n");
		l->head = target->next;
		free(target);
		updateTail(l);
		return (l->head);
	}
	for (p1 = l->head; p1; p1 = p1->next) {
		//Node* temp = p1->next;
		//printf("%p::%p\n",p1,target);
		if (p1->next == target)
		{
			// printf("Found!::%p\n",p1);
			p1->next = target->next;
			free(target);
			updateTail(l);
			return p1->next;
		}

	}
Abnormal:
	l->size++;
	return NULL;
}

void logNodes(LinkedList ll)
{
	// print the link-list
	Node* p1 = NULL;
	int i = 0;
	printf("HEAD:%p Tail:%p size:%d\n", ll.head, ll.tail, ll.size);
	for (p1 = ll.head; p1; p1 = p1->next) {
		printf("link-%p-%p: value[%d] = %d...\n", p1, p1->next, i++, p1->value);
	}
}

int main()
{
	LinkedList lt;
	LinkedList lt2;
	list_init(&lt);

#pragma region 给一点数据
	list_insert(&lt, 10);
//	list_insert(&lt, 20);
	//list_insert(&lt, 30);
	//list_insert(&lt, 40);
	logNodes(lt);
#pragma endregion
	//remove test
	Node* p1 = lt.head;
	
	//p1 = p1->next;
	//p1 = p1->next;
	//p1 = p1->next;
	printf("RemovedNext:%p\n", list_remove(&lt,p1));
	//  list_insert(&lt, 100);
	logNodes(lt);

	return 0;
}
