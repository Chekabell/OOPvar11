#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "subj.h"

#define COMPARE_DOUBLE 0.0000001
#define PI_CONST 3.14

const char* ItemTypeName[5] = { "None", "Circle", "Square", "Rhomb", "Regular Polygon" };

struct Base* create(enum ItemType type) {
	struct Base* p = NULL;
	switch (type) {
		case Circle:
			p = (struct Base*)malloc(sizeof(struct Circle));
			break;
		case Square:
			p = (struct Base*)malloc(sizeof(struct Square));
			break;
		case Rhomb:
			p = (struct Base*)malloc(sizeof(struct Rhomb));
			break;
		case RegularPolygon:
			p = (struct Base*)malloc(sizeof(struct RegularPolygon));
			break;
	}
	if (p) p->type = type;
	return p;
}

void inputCircle(struct Circle* p) {
	while (1) {
		fflush(stdin);
		printf("Enter radius: ");
		if (scanf_s("%lg", &p->radius)) break;
	}
	p->area = PI_CONST * (p->radius) * (p->radius);
	p->perimeter = 2 * PI_CONST * (p->radius);
}

void inputSquare(struct Square* p) {
	while (1) {
		fflush(stdin);
		printf("Enter length of side: ");
		if (scanf_s("%lg", &p->lenSide)) break;
	};
	p->area = (p->lenSide) * (p->lenSide);
	p->perimeter = 4 * (p->lenSide);
}

void inputRhomb(struct Rhomb* p) {
	while (1) {
		fflush(stdin);
		printf("Enter lenght short diagonal: ");
		if (scanf_s("%lg", &p->lenDiagShort)) break;
	};
	while (1) {
		fflush(stdin);
		printf("Enter length long diagonal: ");
		if (scanf_s("%lg", &p->lenDiagLong)) break;
	};
	p->area = ((p->lenDiagLong) * (p->lenDiagShort)) / 2;
	p->perimeter = 4 * sqrt(((p->lenDiagLong)/2) * ((p->lenDiagLong) / 2) + (((p->lenDiagShort)/2) * ((p->lenDiagShort)/2)));
}

void inputRegularPolygon(struct RegularPolygon* p) {
	while (1) {
		fflush(stdin);
		printf("Enter quantity of tops: ");
		if (scanf_s("%i", &p->quantityTop)) break;
	}
	while (1) {
		fflush(stdin);
		printf("Enter length of side: ");
		if (scanf_s("%lg", &p->lenSide)) break;
	}
	p->area = (p->lenSide) * (p->lenSide) * (p->quantityTop) / (4 * tan(PI_CONST / (p->quantityTop)));
	p->perimeter = (p->lenSide) * (p->quantityTop);
}

void inputObject(struct Base* p) {
	if (p) {
		switch (p->type) {
		case Circle:
			inputCircle((struct Circle*)p);
			break;
		case Square:
			inputSquare((struct Square*)p);
			break;
		case Rhomb:
			inputRhomb((struct Rhomb*)p);
			break;
		case RegularPolygon:
			inputRegularPolygon((struct RegularPolygon*)p);
			break;
		}
	}
	else printf("Error: null pointer!\n");
}

void printCircle(struct Circle* p) {
	printf("Radius: %lg\n", p->radius);
}

void printSquare(struct Square* p) {
	printf("Length side: %lg\n", p->lenSide);
}

void printRhomb(struct Rhomb* p) {
	printf("Length short diagonal: %lg\nLenght long diagonal: %lg\n", p->lenDiagShort, p->lenDiagLong);
}

void printRegularPolygon(struct RegularPolygon* p) {
	printf("Quantity of top: %i\nLength side: %lg\n", p->quantityTop, p->lenSide);
}

void printObject(struct Base* p) {
	if (p) {
		printf("==------------------==\n\t%s\n==------------------==\n", ItemTypeName[p->type]);
		printf("Area: %lg\nPerimeter: %lg\n", p->area, p->perimeter);
		switch (p->type) {
		case Circle:
			printCircle((struct Circle*)p);
			break;
		case Square:
			printSquare((struct Square*)p);
			break;
		case Rhomb:
			printRhomb((struct Rhomb*)p);
			break;
		case RegularPolygon:
			printRegularPolygon((struct RegularPolygon*)p);
			break;
		}
	}
	else printf("Error: null pointer!\n");
}

void printListObj(struct List* list) {
	struct Item* p;
	if (list) {
		p = list->head;
		if (p)
			while (p) {
				printObject((struct Base*)p);
				p = p->next;
			}
		else printf("List is empty.\n");
	}
	else printf("ERROR: null pointer!\n");
}

void swap(struct List* list, int j) {
	struct Item* a = removeItem(list, j);
	insert(list, a, j + 1);
}

void sortByArea(struct List* list) {
	int i = count(list) - 1, j;
	int indexLastSwap = 0;
	while (i > 0) {
		indexLastSwap = -1;
		for (j = 0; j < i; j++) {
			if (((struct Base*)getItem(list, j))->area > ((struct Base*)getItem(list, j + 1))->area) {
				swap(list, j);
				indexLastSwap = j;
			}
		}
		i = indexLastSwap;
	}
}

void sortByPerimeter(struct List* list) {
	int i = count(list) - 1, j;
	int indexLastSwap = 0;
	while (i > 0) {
		indexLastSwap = -1;
		for (j = 0; j < i; j++) {
			if (((struct Base*)getItem(list, j))->perimeter > ((struct Base*)getItem(list, j + 1))->perimeter) {
				swap(list, j);
				indexLastSwap = j;
			}
		}
		i = indexLastSwap;
	}
}

void searchByShapesInRectangle(struct List* list, const double high, const double width) {
	struct Base* tmp;
	double radiusSquare = 0;
	double radiusPolygon = 0;
	for (tmp = (struct Base*)list->head; tmp; tmp = (struct Base*)tmp->next) {
		switch (tmp->type) {
		case Circle:
			if (((struct Circle*)tmp)->radius <= high && ((struct Circle*)tmp)->radius <= width)
				printObject((struct Circle*)tmp);
			break;
		case Square:
			if (((struct Square*)tmp)->lenSide <= high && ((struct Square*)tmp)->lenSide <= width)
				printObject((struct Square*)tmp);
			break;
		case Rhomb:
			if ((((struct Rhomb*)tmp)->lenDiagLong <= high && ((struct Rhomb*)tmp)->lenDiagShort <= width) ||
				(((struct Rhomb*)tmp)->lenDiagShort <= high && ((struct Rhomb*)tmp)->lenDiagLong <= width))
				printObject((struct Rhomb*)tmp);
			break;
		case RegularPolygon:
			radiusSquare = (sqrt(high * high + width * width))/2;
			radiusPolygon = (((struct RegularPolygon*)tmp)->lenSide) / (2 * sin(PI_CONST / ((struct RegularPolygon*)tmp)->quantityTop));
			if (radiusSquare >= radiusPolygon)
				printObject((struct RegularPolygon*)tmp);
			break;
		}
	}
}