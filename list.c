#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void add(struct List* list, struct Item* newItem) {
	if (!list->head) {
		newItem->next = NULL;
		newItem->prev = NULL;
		list->head = newItem;
		list->tail = newItem;
	}
	else {
		newItem->prev = list->tail;
		newItem->next = NULL;
		list->tail->next = newItem;
		list->tail = newItem;
	}
}

int count(struct List* list) {
	int i;
	struct Item* tmp = list->head;
	for (i = 0; tmp; i++)
		tmp = tmp->next;
	return i;
}

void printList(struct List* list) {
	int i;
	struct Item* printedItem;
	if (list->head) {
		i = 0;
		printf("\n\tPREV\t\t CURR\t\t NEXT\n");
		for (printedItem = list->head; printedItem; printedItem = printedItem->next) {
			printf("%i: %p %p %p\n", i, printedItem->prev, printedItem, printedItem->next);
			i++;
		}
	}
	else printf("List is empty\n");
}

struct Item* getItem(struct List* list, int indexItem) {
	struct Item* searchingItem;
	int indexNow = 0;
	for (searchingItem = list->head; searchingItem; searchingItem = searchingItem->next) {
		if (indexNow == indexItem)
			break;
		indexNow++;
	}
	return searchingItem;
}

int indexOf(struct List* list, struct Item* item) {
	int indexNow = 0;
	struct Item* curr;
	for (curr = list->head; curr != item; curr = curr->next)
		indexNow++;
	return indexNow;
}

struct Item* removeItem(struct List* list, int i) {
	struct Item* itemForRemove = getItem(list, i);
	if (!itemForRemove)
		return NULL;
	else if (itemForRemove == list->head) {
		if (itemForRemove->next == NULL) {
			list->head = NULL;
			list->tail = NULL;
			return itemForRemove;
		}
		list->head = itemForRemove->next;
		itemForRemove->next->prev = NULL;
		itemForRemove->next = NULL;
	}
	else if (itemForRemove == list->tail) {
		list->tail = itemForRemove->prev;
		itemForRemove->prev->next = NULL;
		itemForRemove->prev = NULL;
	}
	else {
		itemForRemove->next->prev = itemForRemove->prev;
		itemForRemove->prev->next = itemForRemove->next;
		itemForRemove->prev = NULL;
		itemForRemove->next = NULL;
	}
	return itemForRemove;
}

void deleteItem(struct List* list, int i) {
	struct Item* item = removeItem(list, i);
	if (item)
		free(item);
}

void clear(struct List* list) {
	struct Item* curr;
	for (curr = list->head; list->head; curr = list->head) {
		deleteItem(list, 0);
	}
}

void insert(struct List* list, struct Item* itemForInsert, int index) {
	struct Item* itemForShift = getItem(list, index);
	if (!itemForShift) {
		add(list, itemForInsert);
	}
	else if (!index) {
		list->head->prev = itemForInsert;
		itemForInsert->next = list->head;
		itemForInsert->prev = NULL;
		list->head = itemForInsert;
	}
	else {
		itemForInsert->next = itemForShift;
		itemForInsert->prev = itemForShift->prev;
		itemForShift->prev->next = itemForInsert;
		itemForShift->prev = itemForInsert;
	}
}

