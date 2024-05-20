# Generic Linked List
[Linked List](https://www.tutorialspoint.com/data_structures_algorithms/linked_list_algorithms.htm) consists of an abstract and linear data structure whose main objective is to store elements of the same type in a list arranged discontinuously in memory. The most elementary concept used in all linked lists corresponds to the "node", a substructure responsible for containing two attributes: The information that will be placed in each element of the list and a pointer informing the memory address for the next node in the list.

In the specific implementation of this module, another structure will conventionally be created to encompass all the information necessary to perform the specific operations associated with each single linked list instance. Each structure will include:
* A <span style="color:green;">pointer</span> to the first element of the linked list, called "<span style="color:blue;">front</span>";

* A <span style="color:green;">pointer</span> to the last element of the linked list, called "<span style="color:red;">rear</span>";

* A 32-bit unsigned integer counter, which can represent values contained in the interval **0** to **4,294,967,295**, where the limits of this interval are included;
* A <span style="color:green;">pointer</span> to an external function whose purpose is to determine the display method of the list's elements. This parameter is optional, that is, its non-existence does not prevent the basic functioning of the data structure, but it makes it impossible to display its elements;

* A **mandatory**, non-null <span style="color:green;">pointer</span> to an external comparison function. This function receives as parameters two <span style="color:green;">pointers</span> to list elements and is designed to perform two-by-two comparisons between elements. The function must return: A **negative** value (less than zero) if the first parameter is considered inferior to the second; **zero** if both given parameters are equal; a **positive** value (greater than zero) if the first parameter is considered superior to the second;

* A <span style="color:green;">pointer</span> to an external function whose purpose is to implement a specific disposal method for each element in the list. This function receives as its only parameter a <span style="color:green;">pointer</span> to the data type stored in the list and performs the release of dynamically allocated memory for the element. If it is not necessary to deallocate memory, this parameter can be replaced with a <span style="color:red;">null pointer</span> (<span style="color:red;">NULL</span>) during the instantiation of each linked list;

* A <span style="color:green;">pointer</span> to an external function whose purpose is to produce completely independent replicas of each element contained in the list, that is, the function will perform a [deep copy](https://developer.mozilla.org/en-US/docs/Glossary/Deep_copy). The function's only parameter is a <span style="color:green;">pointer</span> to the element to be copied, and it will return a <span style="color:green;">pointer</span> to the new copied element. This function is only necessary if the structure of the elements stored in the list involves dynamic memory allocation, if there is no memory allocated; otherwise, the copy function parameter may be replaced with a <span style="color:red;">null pointer</span> (<span style="color:red;">NULL</span>).

#
### Visualization of the code used to create linked lists::
```c
typedef struct GENERICLINKEDLISTNODE {
    gLinkedListDataPtr data;
    struct GENERICLINKEDLISTNODE* next;
} gLinkedListNode;


typedef struct {
    gLinkedListNode *front, *rear;
    uint32_t counter;
    impressFunctionGenLinkedList printF;
    compareFunctionGenLinkedList compareF;
    destroyFuntionGenLinkedList destroyF;
    deepcopyFunctionGenLinkedList deepcopyF;
} gLinkedList;
```
#

For demonstration and exemplification purposes, there will be comments adjacent to each function signature, briefly describing its behavior and purpose, all contained in the header file (*genLinkedList.h*). Furthermore, there is also a commented program that uses the data structure created in this module, in order to resolve any remaining doubts regarding its use, demonstrating its use in practice.

The pre-existing basic operations contained in this module include:
* *initgLinkedList*: Initializes and returns a pointer to the newly initialized linked list.
* *gLinkedListCopy*: Creates copies and returns a pointer to the copy of a given linked list.
* *gLinkedListAppend*: Appends a new element to the end of the linked list.
* *gLinkedListClear*: Removes all elements contained in the linked list.
* *gLinkedListDestroy*: Completely destroys the linked list, freeing all dynamically allocated memory present in it.
* *gLinkedListImpress*: Displays on the terminal a visual representation of the elements contained in the linked list.
* *gLinkedListRemove*: Removes a specific element from the linked list.
* *gLinkedListReverse*: Reverses the ordering of the elements present in the linked list.
* *gLinkedListIsEmpty*: Informs whether the linked list is empty.
* *gLinkedListIsEquals*: Determine whether two linked lists are equal.
* *gLinkedListSearch*: Informs whether a given element is contained in the linked list.
* *gLinkedListHasSameElements*: Checks whether two linked lists have the same elements.
* *gLinkedListShareSameElements*: Checks whether two linked lists share the same elements.
* *gLinkedListCount*: Counts the number of occurrences of an element in the linked list.
* *gLinkedListSize*: Enumerates and informs the number of elements present in the linked list.
* *gLinkedListGetBiggest*: Returns the largest element present in the linked list.
* *gLinkedListGetSmallest*: Returns the smallest element present in the linked list.
* *gLinkedListPop*: Removes and returns the element located at the specified index within the linked list.

## Algorithmic Complexity in Big O Notation for Linked List Operations:

<div align="center">

| Operation               | Big O   |
|:-----------------------:|:-------:|
| Space                   | O(n)    |
| Copy                    | O(n)    |
| Append                  | O(1)    |
| Clear                   | O(n)    |
| Destroy                 | O(n)    |
| Impress                 | O(n)    |
| Remove                  | O(n)    |
| Reverse                 | O(n)    |
| Is Empty                | O(1)    |
| Equals                  | O(n)    |
| Search                  | O(n)    |
| Has Same Elements       | O(n²)   |
| Share Same Elements     | O(n²)   |
| Count                   | O(n)    |
| Size                    | O(1)    |
| Get Biggest             | O(n)    |
| Get Smallest            | O(n)    |
| Pop                     | O(n)    |

</div>