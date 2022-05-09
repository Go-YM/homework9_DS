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
//<stdio.h>�� <stdlib.h>�� ������ ���� �ҽ��� Ȯ���ϵ��� ����

//node ����ü ����
typedef struct node {
	int key;	//data�� ������ key���� ����	
	struct node *left;	//left-child�� ����ų node ������ ���� left����
	struct node *right; //right-child�� ����ų node ������ ���� right����
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

//BST���α׷��� �����Լ�
int main()
{
	char command;	//command�� ������ ���� ����
	int key;	//key�� ������ ���� ����
	int count = 0;	//Initialize���� �����ϰ� �ϴ� count ���� ����
	Node* head = NULL;	//Node������ ���� head ����
	Node* ptr = NULL;	//Node ������ �ۼ� ptr ����

	printf("-------[����] [2019038003]-------\n");
	do{	//q or Q�� �Էµɶ����� �ݺ��ϴ� do-while��
		//�޴� ���
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
		scanf(" %c", &command);	//����ڷκ��� command�� �Է¹���

		switch(command) {	//command�� ���� ���� �����ϴ� switch��
		case 'z': case 'Z':	//command�� z or Z�϶�
			initializeBST(&head);
			count++;
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			freeBST(head);
			break;
		case 'n': case 'N': //command�� n or N�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': //command�� d or D�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': //command�� f or F�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': //command�� s or S�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I': //command�� i or I�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': //command�� p or P�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			preorderTraversal(head->left);
			break;
		case 't': case 'T': //command�� t or T�϶�
			if(count == 0)	//count�� 0�϶�
			{
				printf("Please Initialize BST firstly.\n");	//���� �޼��� ���
				break;
			}
			postorderTraversal(head->left);
			break;
		default:	//command�� ���������� �Է��϶�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;	//1 ��ȯ
}

//BST�� �ʱ�ȭ ���ִ� �Լ�
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)	//h��尡 ���������
		freeBST(*h);	//h�� free

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));	//h�� �����޸� �Ҵ�
	(*h)->left = NULL;	//h�� left-child�� NULL�� ����
	(*h)->right = *h;	//h�� right_childe�� �ڽ����� ����
	(*h)->key = -9999;	//h�� key���� -9999�� ����
	return 1;	//1 ��ȯ
}


//BST�� ������ȸ�ϴ� �Լ�
void inorderTraversal(Node* ptr)
{
	if(ptr) { //ptr�� NULL�� �ƴҶ�
		inorderTraversal(ptr->left);	//ptr�� left-child�� ������ȸ (L)
		printf(" [%d] ", ptr->key);		//ptr�� key�� ��� (V)
		inorderTraversal(ptr->right);	//ptr�� right-childe�� ������ȸ (R)
	}
}

//BST�� ������ȸ �ϴ� �Լ�
void preorderTraversal(Node* ptr)
{
	if(ptr) { //ptr�� NULL�� �ƴҶ�
		printf(" [%d] ", ptr->key); 	//ptr�� key�� ��� (V)
		preorderTraversal(ptr->left);	//ptr�� left-child�� ������ȸ (L)
		preorderTraversal(ptr->right);	//ptr�� right-childe�� ������ȸ (R)
	}
}

//BST�� ������ȸ �ϴ� �Լ�
void postorderTraversal(Node* ptr)
{	
	if(ptr) { //ptr�� NULL�� �ƴҶ�
		postorderTraversal(ptr->left);	//ptr�� left-child�� ������ȸ (L)
		postorderTraversal(ptr->right);	//ptr�� right-childe�� ������ȸ (R)
		printf(" [%d] ", ptr->key);		//ptr�� key�� ��� (V)
	}
}

//BST�� ��带 �߰��ϴ� �Լ�
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//Node ������ ���� newNode�� ������ �����޸� �Ҵ�
	newNode->key = key;	//����ڷκ��� �Է¹��� key�� newNode�� key�� ����
	newNode->left = NULL;	
	newNode->right = NULL;
	//newNode�� left-child�� right-childe�� NULL�� �ʱ�ȭ

	if (head->left == NULL) {	//headnode�� left-child�� ������
		head->left = newNode;	//headnode�� left-child�� newNode ����
		return 1;	//1 ��ȯ
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//Node������ ���� ptr�� head�� left-child ����

	Node* parentNode = NULL;
	//Node ������ ���� parentNode ���� �� �ʱ�ȭ
	while(ptr != NULL) 	//ptr�� ���� NULL�϶����� �ݺ��ϴ� while��
	{
		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;	//ptr�� key���� ����ڷκ��� �Է¹��� key�� ������ 1 ��ȯ

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;
		//parentNode�� ptr ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)	//ptr�� key�� ����ڷκ��� �Է¹��� key���� ������
			ptr = ptr->right;	//ptr�� ptr�� right-child�� �Ƶ�
		else	//ptr�� key�� ����ڷκ��� �Է¹��� key���� Ŭ��
			ptr = ptr->left;	//ptr�� ptr�� left-child�� �Ƶ�
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)	//parentNode�� key�� ����ڷκ��� �Է¹��� key���� Ŭ��
		parentNode->left = newNode;	//parentNode�� left-child�� newNode ����
	else	//parentNode�� key�� ����ڷκ��� �Է¹��� key���� ������
		parentNode->right = newNode; //parentNode�� right-child�� newNode ����
	return 1;	//1 ��ȯ
}

//Node�� �����ϴ� �Լ�
int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {	//BST�� �������
		printf("\n Nothing to delete!!\n");	//�����޼��� ���
		return -1;	//-1 ��ȯ
	}

	if (head->left == NULL) {	//head�� left-child�� �������
		printf("\n Nothing to delete!!\n");	//�����޽��� ���
		return -1;	//-1 ��ȯ
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//Node ������ ���� ptr ���� �� head�� left-child ����


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;
	//Node ������ ���� parentNode ���� �� head ����

	while(ptr != NULL) {	//ptr�� NULL�϶����� �ݺ��ϴ� while��

		if(ptr->key == key) {	//ptr�� key���� ����ڷκ��� �Է¹��� key���� ������
			if(ptr->left == NULL && ptr->right == NULL) {	//ptr�� left-child�� right-child�� ���������

				/* root node case */
				if(parentNode == head)	//parentNode�� head�϶�
					head->left = NULL;	//head�� left-child�� NULL�� �ʱ�ȭ

				/* left node case or right case*/
				if(parentNode->left == ptr)	//parentNode�� left-child�� ptr�϶�
					parentNode->left = NULL;	//parentNode�� left-child�� NULL�� �ʱ�ȭ
				else 	//parentNode�� right-child�� ptr�϶�
					parentNode->right = NULL;	//parentNode�� right-childe�� NULL�� �ʱ�ȭ

				free(ptr);	//ptr�� free
			}
			else {	//ptr�� left-child �� �ְų� right-child �� ������
				printf("the node [%d] is not a leaf \n", ptr->key);	//���� �޽��� ���
			}
			return 1;	// 1 ��ȯ
		}

		/* keep the parent node */
		parentNode = ptr;
		//parentNode�� ptr�� ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)	//ptr�� key�� ����ڷκ��� �Է¹��� key���� ������
			ptr = ptr->right;	//ptr�� ptr�� right-child�� ����
		else	//ptr�� key�� ����ڷκ��� �Է¹��� key���� Ŭ��
			ptr = ptr->left;	//ptr�� ptr�� left-child�� ����
	}

	//BST�� �ش� key���� ��尡 �������� ������
	printf("Cannot find the node for key [%d]\n ", key);	//���� �޽��� ���

	return 1;	// 1 ��ȯ
}

//Resursive search �Լ�
Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)	//ptr�� NULL�϶�
		return NULL;	//NULL ��ȯ

	if(ptr->key < key)	//ptr�� key���� ����ڷκ��� �Է¹��� key�� ���� ������
		ptr = searchRecursive(ptr->right, key);	//ptr�� ptr�� right-childe�� Recursive search�� ��� ����
	else if(ptr->key > key)	//ptr�� key���� ����ڷκ��� �Է¹��� key�� ���� ������
		ptr = searchRecursive(ptr->left, key);	//ptr�� ptr�� left-childe�� Recursive search�� ��� ����

	/* if ptr->key == key */
	return ptr;	//ptr ��ȯ

}

//Iterative search �Լ�
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;
	//Node ������ ���� ptr�� head�� left-child ����

	while(ptr != NULL)	//ptr�� NULL�϶����� �ݺ��ϴ� while�� ����
	{
		if(ptr->key == key)	//ptr�� key���� ����ڷκ��� �Է¹��� key���� ������
			return ptr;	//ptr ��ȯ

		if(ptr->key < key) //ptr�� key���� ����ڷκ��� �Է¹��� key�� ���� ������
			ptr = ptr->right;	//ptr�� ptr�� right-child�� �̵�
		else	//ptr�� key���� ����ڷκ��� �Է¹��� key�� ���� Ŭ��
			ptr = ptr->left;	//ptr�� ptr�� left-child�� �̵�
	}

	return NULL;	//NULL ��ȯ
}

//��带 free���ִ� �Լ�
void freeNode(Node* ptr)
{
	if(ptr) {	//ptr�� NULL�� �ƴҶ�
		freeNode(ptr->left);	//ptr�� left-child�� free
		freeNode(ptr->right);	//ptr�� right-child�� free
		free(ptr);	//ptr�� free
	}
}

//BST�� free���ִ� �Լ�
int freeBST(Node* head)
{

	if(head->left == head)	//head�� left-child�� head�϶�
	{
		free(head);	//head�� free
		return 1;	//1 ��ȯ
	}

	Node* p = head->left;
	//Node ������ ���� p��  head�� left-child�� ����

	freeNode(p);	//p�� freeNode

	free(head);	//head�� free
	return 1;	// 1 ��ȯ
}




