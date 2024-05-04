#pragma once
#include "list.h"

enum ItemType { None, Circle, Square, Rhomb, RegularPolygon };

struct Base {
    struct Item* next;
    struct Item* prev;
    enum ItemType type;
    double area;
    double perimeter;
};

struct Circle {
    struct Item* next;
    struct Item* prev;
    enum ItemType type;
    double area;
    double perimeter;
    double radius;
};

struct Square{
    struct Item* next;
    struct Item* prev;
    enum ItemType type;
    double area;
    double perimeter;
    double lenSide;
};

struct Rhomb{
    struct Item* next;
    struct Item* prev;
    enum ItemType type;
    double area;
    double perimeter;
    double lenDiagLong;
    double lenDiagShort;
};

struct RegularPolygon {
    struct Item* next;
    struct Item* prev;
    enum ItemType type;
    double area;
    double perimeter;
    double lenSide;
    int quantityTop;
};

struct Base* create(enum ItemType);

void inputObject(struct Base*);
void inputCircle(struct Circle*);
void inputSquare(struct Square*);
void inputRhomb(struct Rhomb*);
void inputRegularPolygon(struct RegularPolygon*);

void printObject(struct Base*);
void printCircle(struct Circle*);
void printSquare(struct Square*);
void printRhomb(struct Rhomb*);
void printRegularPolygon(struct RegularPolygon*);

void printListObj(struct List*);
void sortByPerimeter(struct List*);
void sortByArea(struct List*);
void swap(struct List*, int);
void searchByShapesInRectangle(struct List*, const double, const double);