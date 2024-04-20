#include "BST_H.h"
#include "BinTree.h"
#include "Queue.h"

void impress(type a);
int compare(type a, type b);
void impressq(void *element);
int compareq(void* data1, void* data2);


int main(void) {

  /* Testing the Queue:

  Queue *q = (Queue *) malloc (sizeof(Queue));
  int val1 = 1, val2 = 2, val3 = 3, val4 = 4;
  init_queue(q, impressq, compareq);
  enqueue(q, &val1);
  enqueue(q, &val2);
  enqueue(q, &val3);

  impressQueue(q);
  printf("%d\n", q->counter);
  printf("%s\n", search_queue(q, &val4) ? "Found" : "Not Found");

  impressQueue(q);
  remove_queue(q, &val3);
  impressQueue(q);
  enqueue(q, &val3);
  enqueue(q, &val4);
  impressQueue(q);
  int *tempval = (int *)dequeue(q);
  impressQueue(q);
  printf("%d\n", *tempval);
  impressQueue(q);
  free_queue(q);
  impressQueue(q);
  */

  BTT *TREE1 = initTree();
  TREE1 = createNodeTree(1, 
          createNodeTree(2, NULL, NULL),
          createNodeTree(3,
            createNodeTree(4, NULL, NULL),
            createNodeTree(5, NULL, NULL)));

  puts("Impressing TREE1:");
  impressByLevel(TREE1);

  BTT *TREE2 = copyTree(TREE1);

  puts("Impressing TREE2:");
  impressByLevel(TREE2);
  // impressTree(TREE1);
  // impressByLevel(TREE1);

  puts("Before Mirroring TREE2:");
  impressByLevel(TREE2);
  mirrorTree(TREE2);
  puts("After Mirroring TREE2:");
  impressByLevel(TREE2);

  BTT *biggestValue = biggestElemTree(TREE1);

  printf("%d\n", biggestValue->data);

  int result = isEqualsTree(TREE1, TREE2);
  printf("%s\n", result ? "TREE1 and TREE2 are Equal!" : "TREE1 and TREE2 are not Equal!");

  puts("Checking if TREE1 has the element 1:");
  printf("%s\n", hasElementTree(TREE1, 4) ? "tree have the element!" : "tree do not have the element!");

  puts("Before Removing:");
  impressTree(TREE1);
  removeElemTree(&TREE1, 1);
  puts("After Removing:");
  impressTree(TREE1);

  freeTree(TREE1); freeTree(TREE2);

  /* Testing the Binary Search Tree:

  BST* testTree = createBST(compare, impress);
  testTree = createNodeBST(testTree, 1);
  testTree = createNodeBST(testTree, 12);
  testTree = createNodeBST(testTree, -3);
  testTree = createNodeBST(testTree, -5);
  testTree = createNodeBST(testTree, -1);
  testTree = createNodeBST(testTree, -2);
  testTree = createNodeBST(testTree, 5);
  testTree = createNodeBST(testTree, 1);
  testTree = createNodeBST(testTree, 3);
  //testTree = createNodeBST(testTree, 6);
  //testTree = removeNodeBST(testTree, 12);
  //testTree->right->data = 4;

  printf("%s\n", isBinaryTree(testTree) ? "TestTree is a Binary Search Tree." : "TestTree is not a Binary Search Tree.");

  impressBST(testTree);
  */

  puts("Finished!");

  return 0;
}


void impress(type a) {
  printf("%d\n", a);
}


int compare(type a, type b) {
  if (a > b) return 1;
  if (a < b) return -1;
  return 0;
}


void impressq(void *element) {
  int* ptr = (int *)element;
  printf("%d", *ptr);
}


int compareq(void* data1, void* data2) {
  int* aux1 = (int *)data1;
  int* aux2 = (int *)data2;
  
  if ((*aux1) > (*aux2)) return 1;
  if ((*aux1) < (*aux2)) return -1;
  return 0;
}