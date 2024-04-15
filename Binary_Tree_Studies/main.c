#include "BST_H.h"
#include "Queue.h"

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

int main(void) {

  Queue q;
  int val1 = 1, val2 = 2, val3 = 3, val4 = 4;
  init_queue(&q, impressq, compareq);
  enqueue(&q, &val1);
  enqueue(&q, &val2);
  enqueue(&q, &val3);
  
  impressQueue(&q);
  printf("%d\n", q.counter);
  printf("%s\n", search_queue(&q, &val4) ? "Found" : "Not Found");
  
  impressQueue(&q);
  remove_queue(&q, &val3);
  impressQueue(&q);
  enqueue(&q, &val3);
  enqueue(&q, &val4);
  impressQueue(&q);
  int *tempval = (int *)dequeue(&q);
  impressQueue(&q);
  printf("%d\n", *tempval);
  impressQueue(&q);
  //free_queue(&q);
  //impressQueue(&q);
  

  
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
  
  
  puts("Finished!");
}