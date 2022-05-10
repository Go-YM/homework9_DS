/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;	
	struct node *left;	
	struct node *right; 
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;	//command를 저장할 변수 선언
	int key;	//key를 저장할 변수 선언
	Node* head = NULL;	//Node포인터 변수 head 선언
	Node* ptr = NULL;	//Node 포인터 蒡 ptr 선언

	printf("-------[고영민] [2019038003]-------\n");
	do{	//q or Q가 입력될때까지 반복하는 do-while문
		//메뉴 출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);	//사용자로부터 command를 입력받음

		switch(command) {	//command의 값에 따라 실행하는 switch문
		case 'z': case 'Z':	//command가 z or Z일때
			initializeBST(&head);
			count++;
			break;
		case 'q': case 'Q': //command가 q or Q일때
			freeBST(head);
			break;
		case 'n': case 'N': //command가 n or N일때
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': //command가 d or D일때
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': //command가 f or F일때
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': //command가 s or S일때
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': //command가 i or I일때
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': //command가 p or P일때
			preorderTraversal(head->left);
			break;
		case 't': case 'T': //command가 t or T일때
			postorderTraversal(head->left);
			break;
		default:	//command가 비정상적인 입력일때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;	//1 반환
}

//BST를 초기화 해주는 함수
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)	//h노드가 비어있을때
		freeBST(*h);	//h를 free

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));	//h를 동적메모리 할당
	(*h)->left = NULL;	//h의 left-child를 NULL로 저장
	(*h)->right = *h;	//h의 right_childe를 자신으로 저장
	(*h)->key = -9999;	//h의 key값을 -9999로 저장
	return 1;	//1 반환
}


//BST를 중위순회하는 함수
void inorderTraversal(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아닐때
		inorderTraversal(ptr->left);	//ptr의 left-child를 중위순회 (L)
		printf(" [%d] ", ptr->key);		//ptr의 key값 출력 (V)
		inorderTraversal(ptr->right);	//ptr의 right-childe를 중위순회 (R)
	}
}

//BST를 전위순회 하는 함수
void preorderTraversal(Node* ptr)
{
	if(ptr) { //ptr이 NULL이 아닐때
		printf(" [%d] ", ptr->key); 	//ptr의 key값 출력 (V)
		preorderTraversal(ptr->left);	//ptr의 left-child를 중위순회 (L)
		preorderTraversal(ptr->right);	//ptr의 right-childe를 중위순회 (R)
	}
}

//BST를 후위순회 하는 함수
void postorderTraversal(Node* ptr)
{	
	if(ptr) { //ptr이 NULL이 아닐때
		postorderTraversal(ptr->left);	//ptr의 left-child를 중위순회 (L)
		postorderTraversal(ptr->right);	//ptr의 right-childe를 중위순회 (R)
		printf(" [%d] ", ptr->key);		//ptr의 key값 출력 (V)
	}
}

//BST에 노드를 추가하는 함수
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//Node 포인터 변수 newNode를 선언후 동적메모리 할당
	newNode->key = key;	//사용자로부터 입력받은 key를 newNode의 key에 저장
	newNode->left = NULL;	
	newNode->right = NULL;
	//newNode의 left-child와 right-childe를 NULL로 초기화

	if (head->left == NULL) {	//headnode의 left-child가 없을때
		head->left = newNode;	//headnode의 left-child에 newNode 저장
		return 1;	//1 반환
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//Node포인터 변수 ptr에 head의 left-child 저장

	Node* parentNode = NULL;
	//Node 포인터 변수 parentNode 선언 후 초기화
	while(ptr != NULL) 	//ptr의 값이 NULL일때까지 반복하는 while문
	{
		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;	//ptr의 key값이 사용자로부터 입력받은 key와 같을때 1 반환

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;
		//parentNode에 ptr 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)	//ptr의 key가 사용자로부터 입력받은 key보다 작을때
			ptr = ptr->right;	//ptr을 ptr의 right-child로 아동
		else	//ptr의 key가 사용자로부터 입력받은 key보다 클때
			ptr = ptr->left;	//ptr을 ptr의 left-child로 아동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)	//parentNode의 key가 사용자로부터 입력받은 key보다 클때
		parentNode->left = newNode;	//parentNode의 left-child에 newNode 저장
	else	//parentNode의 key가 사용자로부터 입력받은 key보다 작을때
		parentNode->right = newNode; //parentNode의 right-child에 newNode 저장
	return 1;	//1 반환
}

//Node를 삭제하는 함수
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {	//BST가 비었을때
		printf("\n Nothing to delete!!\n");	//오류메세지 출력
		return -1;	//-1 반환
	}

	if (head->left == NULL) {	//head의 left-child가 비었을때
		printf("\n Nothing to delete!!\n");	//오류메시지 출력
		return -1;	//-1 반환
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//Node 포인터 변수 ptr 선언 후 head의 left-child 저장


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;
	//Node 포인터 변수 parentNode 선언 후 head 저장

	while(ptr != NULL) {	//ptr이 NULL일때까지 반복하는 while문

		if(ptr->key == key) {	//ptr의 key값이 사용자로부터 입력받은 key값과 같을때
			if(ptr->left == NULL && ptr->right == NULL) {	//ptr의 left-child와 right-child가 비어있을때

				/* root node case */
				if(parentNode == head)	//parentNode가 head일때
					head->left = NULL;	//head이 left-child를 NULL로 초기화

				/* left node case or right case*/
				if(parentNode->left == ptr)	//parentNode의 left-child가 ptr일때
					parentNode->left = NULL;	//parentNode의 left-child를 NULL로 초기화
				else 	//parentNode의 right-child가 ptr일때
					parentNode->right = NULL;	//parentNode의 right-childe를 NULL로 초기화

				free(ptr);	//ptr을 free
			}
			else {	//ptr의 left-child 가 있거나 right-child 가 있을때
				printf("the node [%d] is not a leaf \n", ptr->key);	//오류 메시지 출력
			}
			return 1;	// 1 반환
		}

		/* keep the parent node */
		parentNode = ptr;
		//parentNode에 ptr을 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)	//ptr의 key가 사용자로부터 입력받은 key보다 작을때
			ptr = ptr->right;	//ptr에 ptr의 right-child를 저장
		else	//ptr의 key가 사용자로부터 입력받은 key보다 클때
			ptr = ptr->left;	//ptr에 ptr의 left-child를 저장
	}

	//BST에 해당 key값의 노드가 존재하지 않을때
	printf("Cannot find the node for key [%d]\n ", key);	//오류 메시지 출력

	return 1;	// 1 반환
}

//Resursive search 함수
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)	//ptr이 NULL일때
		return NULL;	//NULL 반환

	if(ptr->key < key)	//ptr의 key값이 사용자로부터 입력받은 key값 보다 작을때
		ptr = searchRecursive(ptr->right, key);	//ptr에 ptr의 right-childe를 Recursive search한 노드 저장
	else if(ptr->key > key)	//ptr의 key값이 사용자로부터 입력받은 key값 보다 작을때
		ptr = searchRecursive(ptr->left, key);	//ptr에 ptr의 left-childe를 Recursive search한 노드 저장

	/* if ptr->key == key */
	return ptr;	//ptr 반환

}

//Iterative search 함수
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;
	//Node 포인터 변수 ptr에 head에 left-child 저장

	while(ptr != NULL)	//ptr이 NULL일때까지 반복하는 while문 선언
	{
		if(ptr->key == key)	//ptr의 key값이 사용자로부터 입력받은 key값과 같을때
			return ptr;	//ptr 반환

		if(ptr->key < key) //ptr의 key값이 사용자로부터 입력받은 key값 보다 작을때
			ptr = ptr->right;	//ptr을 ptr의 right-child로 이동
		else	//ptr의 key값이 사용자로부터 입력받은 key값 보다 클때
			ptr = ptr->left;	//ptr을 ptr의 left-child로 이동
	}

	return NULL;	//NULL 반환
}

//노드를 free해주는 함수
void freeNode(Node* ptr)
{
	if(ptr) {	//ptr이 NULL이 아닐때
		freeNode(ptr->left);	//ptr의 left-child를 free
		freeNode(ptr->right);	//ptr의 right-child를 free
		free(ptr);	//ptr을 free
	}
}

//BST를 free해주는 함수
int freeBST(Node* head)
{

	if(head->left == head)	//head의 left-child가 head일때
	{
		free(head);	//head를 free
		return 1;	//1 반환
	}

	Node* p = head->left;
	//Node 포인터 변수 p에  head의 left-child를 저장

	freeNode(p);	//p를 freeNode

	free(head);	//head를 free
	return 1;	// 1 반환
}
