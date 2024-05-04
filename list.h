#pragma once

struct Item {
	struct Item* next;
	struct Item* prev;
};

struct List {
	struct Item* head;
	struct Item* tail;
};

void add(struct List*, struct Item*);
struct Item* getItem(struct List*, const int);
void insert(struct List*, struct Item*, const int);
int indexOf(struct List*, struct Item*);
struct Item* removeItem(struct List*, const int);
void deleteItem(struct List*, const int);
void clear(struct List*);
int count(struct List*);
void printList(struct List*);