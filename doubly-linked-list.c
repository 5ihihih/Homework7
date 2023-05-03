#include<stdio.h>
#include<stdlib.h>

/*�����Ϳ� ����� �����͸� ���� ��� ����ü ����*/
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/*ù��° ��带 ����Ű�� ������ ����*/
typedef struct Head {
	struct Node* first;
}headNode;

int initialize(headNode** h);
int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [����ȭ] [2022078036] -----]\n\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*����Ʈ�� �ʱ�ȭ�ϴ� �Լ�*/
int initialize(headNode** h) {

	if(*h != NULL)   
		freeList(*h);

	/*���ο� ����带 �����ϰ� NULL���� �����Ѵ�*/
	*h = (headNode*)malloc(sizeof(headNode)); 
	(*h)->first = NULL;

	return 0;
}

/*����� �޸𸮸� �����ϴ� �Լ�*/
int freeList(headNode* h){
	listNode* p = h->first;
	listNode* prev = NULL;

	/*ù��° ������ ������ ������ ���ʷ� �޸� ������ �ݺ��Ѵ�*/
	while(p != NULL) {      
		prev = p;
		p = p->rlink;
		free(prev);
	}
	/*������� �޸𸮸� �����Ѵ�*/
	free(h);
	return 0;
}

/*����Ʈ�� ����ϴ� �Լ�*/
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	/*����Ʈ�� ��忡 �ϳ��� �����ϸ� key������ ���*/
	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	/*����� ���� ���*/
	printf("  items = %d\n", i);
}

/*�������� ��带 �����ϴ� �Լ�*/
int insertLast(headNode* h, int key) {

    /*������ ��� ����*/
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

    /*�� ����Ʈ�� ��� ������ ��带 ����Ʈ�� ù��° ���� �����*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

    /*n�� ����Ʈ�� ������ ��带 ����Ű���� �ݺ��Ѵ�*/
	while(n->rlink != NULL) {
		n = n->rlink;
	}

    /*n�� ����Ű�� ����� ������ ��ũ�� ������ ����� �ּҸ� �ִ´�*/
	n->rlink = node;

	return 0;
}

/*������ ��带 �����ϴ� �Լ�*/
int deleteLast(headNode* h) {

	/*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/*n�� ����Ű�� ��尡 ������ ����� ��� ������ ����� �޸𸮸� �����Ѵ�*/
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

    /*n�� ������ ��带 ����Ű�� �ʴ� ��� trail�� n�� ���� ����� �ּҸ� �ֱ⸦ �ݺ��Ѵ�*/
	while(n->rlink != NULL){
		trail = n;
		n = n->rlink;
	}

    /*trail�� ����Ű�� ����� ������ ��ũ�� ��� �ּҰ��� NULL�� �����ϰ� ������ ����� �޸𸮸� �����Ѵ�*/
	trail->rlink = NULL;
	free(n);

	return 0;
}

/*����Ʈ�� �պκп� ��带 �����ϴ� �Լ�*/
int insertFirst(headNode* h, int key) {

	/*������ ��带 ����*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/*�� ����Ʈ�� ��� ��带 ���� �� �Լ� ����*/
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	/*ù��° ����� ���� ��ũ�� NULL�� ���´�*/
	node->llink = NULL;
	node->rlink = h->first;

	listNode* n = h->first;
	n->llink = node;
	h->first = node;


	return 0;
}

/*����Ʈ�� ù��° ��带 �����ϴ� �Լ�*/
int deleteFirst(headNode* h) {

	/*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	/*������ ����� �ּ������� n�� ��Ƶΰ�
	first�� �ι�° ��带 ����Ű���� �� ��
	n�� �̿��� ����� �޸𸮸� �����Ѵ�*/
	listNode *n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) {

	/*�� ����Ʈ�� ��� "nothing to invert..."�� ����Ѵ�*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;			//������ �������� �Ǵ� �� ��� �� �� ��带 ����Ų��
		middle = n;				//������ �������� �Ǵ� �� ��� �� �� ��带 ����Ų��
		n = n->rlink;			//n�� ���� ��带 ����Ų��
		/*����� ���� ������ �ٲ۴�*/
		middle->rlink = trail;	//������ �ٲ� ����� rlink�� �� ����� �ּҸ� ���´�
		middle->llink = n;		//������ �ٲ� ����� llink�� ���� ����� �ּҸ� ���´�
	}

	/*���� ����Ʈ���� �������� ��ġ�ߴ� ��带 ù ���� �����Ѵ�*/
	h->first = middle;

	return 0;
}

int insertNode(headNode* h, int key) {

	/*���ο� ��� ����*/
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/*�� ����Ʈ�� ��� ��带 ����Ʈ�� ù�κп� ����*/
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	listNode *n = h->first;

	while(n != NULL){
		/*(�̹� �����ϴ� ����� key)>=(������ ����� key)�� ������ n�� ���� ��带 ����Ű���� �ݺ�*/
		if(n->key < key){
			n = n->rlink;
		}
		/*(�̹� �����ϴ� ����� key)>=(������ ����� key)�� ���*/
		else{
			/*n�� ù��° ��带 ����ų ��� insertFirst�� ȣ���Ͽ� ����*/
			if(n == h->first){
				insertFirst(h, key);
				return 0;
			}
			/*n�� ������ ��带 ����ų ��� insertLast�� ȣ���Ͽ� ����*/
			else if(n->rlink == NULL){
				insertLast(h, key);
				return 0;
			}
			else{
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
		}
	}

	return 0;
}

int deleteNode(headNode* h, int key) {

	/*�� ����Ʈ�� ��� "nothing to delete."�� ����Ѵ�*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;

	while(n != NULL){
		/*������ ��带 ã���� ���*/
		if(n->key == key){
			/*ù��° ����� ��� deleteFirst�� ȣ���� ��� ����*/
			if(n == h->first){
				deleteFirst(h);
			}
			/*������ ����� ��� deleteLast�� ȣ���� ��� ����*/
			else if(n->rlink == NULL){
				deleteLast(h);
			}
			/*������ ����� ������ ��� llink�� ������ ����� ���� ����� �ּҸ� �ְ�
			������ ����� ���� ��� rlink�� ������ ����� ������ ����� �ּҸ� �־�
			������ ���� �޸𸮸� �����Ѵ�*/
			else{
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}
		n = n->rlink; //n�� ���� ��带 ����Ű���� �Ѵ�
	}

	/*������ ��尡 ���� ���*/
	printf("cannot find the node for key = %d\n", key);

	return 0;
}


