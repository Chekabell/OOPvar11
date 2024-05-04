#include <stdio.h>
#include <stdlib.h>
#include "subj.h"

const char* Menu[11] = { "(none)", "add","count","print list","delete","insert","clear","sort by area","sort by perimeter","search for shapes that can fit into a rectangle", "exit"};
const char* Type[5] = { "(unknown)", "Circle","Square","Rhomb","Regular Polygon" };

int doMenu(const char* s[], int max) {
    int i = 0;
    printf("\n");
    for (i = 1; i <= max; i++) {
        printf("%i - %s\n", i, s[i]);
    }
    printf("\n>");
    fflush(stdin);
    scanf_s("%i", &i);
    return i<1 || i>max ? 0 : i;
}

int main(void) {
    struct List list;
    list.head = NULL;
    list.tail = NULL;
    struct Base* item = NULL;
    int key = 0, index = 0, type = 0;
    double high = 0 , width = 0;
    while (1) {
        type = 0;
        key = doMenu(Menu, 10);
        if (key) {
            switch (key) {
            case 1:
                while (1) {
                    if (type = doMenu(Type, 4)) {
                        item = create(type);
                        add(&list, (struct Item*)item);
                        inputObject(item);
                        break;
                    }
                    printf("Unknown type object\n");
                }
                break;
            case 2:
                printf("%i\n", count(&list));
                break;
            case 3:
                printListObj(&list);
                break;
            case 4:
                printf("Enter index: ");
                while (1) {
                    if (scanf_s("%i", &index)) {
                        deleteItem(&list, index - 1);
                        break;
                    }
                }
                break;
            case 5:
                printf("Enter index: ");
                while (1) {
                    if (scanf_s("%i", &index)) {
                        while (1) {
                            if (type = doMenu(Type, 4)) {
                                item = create(type);
                                insert(&list, (struct Item*)item, index - 1);
                                inputObject(item);
                                break;
                            }
                            printf("Unknown type object\n");
                        }
                        break;
                    }
                }
                break;
            case 6:
                clear(&list);
                break;
            case 7:
                sortByArea(&list);
                printListObj(&list);
                break;
            case 8:
                sortByPerimeter(&list);
                printListObj(&list);
                break;
            case 9:
                while (1) {
                    printf("Enter high and width square: ");
                    if(scanf_s("%lg %lg", &high, &width));
                        break;
                }
                searchByShapesInRectangle(&list, high, width);
                break;
            case 10:
                return 0;
            default:
                printf("Wrong opinion\n");
                break;
            }
        }
    }
    return 0;
}