#include<stdio.h>
#include<stdlib.h>

/*데이터와 양방향 포인터를 갖는 노드 구조체 선언*/
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/*첫번째 노드를 가리키는 포인터 선언*/
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

	printf("[----- [오인화] [2022078036] -----]\n\n");

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

/*리스트를 초기화하는 함수*/
int initialize(headNode** h) {

	if(*h != NULL)   
		freeList(*h);

	/*새로운 헤드노드를 선언하고 NULL값을 대입한다*/
	*h = (headNode*)malloc(sizeof(headNode)); 
	(*h)->first = NULL;

	return 0;
}

/*노드의 메모리를 해제하는 함수*/
int freeList(headNode* h){
	listNode* p = h->first;
	listNode* prev = NULL;

	/*첫번째 노드부터 마지막 노드까지 차례로 메모리 해제를 반복한다*/
	while(p != NULL) {      
		prev = p;
		p = p->rlink;
		free(prev);
	}
	/*헤드노드의 메모리를 해제한다*/
	free(h);
	return 0;
}

/*리스트를 출력하는 함수*/
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	/*리스트의 노드에 하나씩 접근하며 key값들을 출력*/
	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	/*노드의 개수 출력*/
	printf("  items = %d\n", i);
}

/*마지막에 노드를 삽입하는 함수*/
int insertLast(headNode* h, int key) {

    /*삽입할 노드 생성*/
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

    /*빈 리스트일 경우 삽입할 노드를 리스트의 첫번째 노드로 만든다*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

    /*n이 리스트의 마지막 노드를 가리키도록 반복한다*/
	while(n->rlink != NULL) {
		n = n->rlink;
	}

    /*n이 가리키는 노드의 오른쪽 링크에 삽입할 노드의 주소를 넣는다*/
	n->rlink = node;

	return 0;
}

/*마지막 노드를 삭제하는 함수*/
int deleteLast(headNode* h) {

	/*빈 리스트일 경우 "nothing to delete."를 출력한다*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/*n이 가리키는 노드가 마지막 노드일 경우 마지막 노드의 메모리를 해제한다*/
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

    /*n이 마지막 노드를 가리키지 않는 경우 trail과 n에 다음 노드의 주소를 넣기를 반복한다*/
	while(n->rlink != NULL){
		trail = n;
		n = n->rlink;
	}

    /*trail이 가리키는 노드의 오른쪽 링크에 담긴 주소값을 NULL로 변경하고 마지막 노드의 메모리를 해제한다*/
	trail->rlink = NULL;
	free(n);

	return 0;
}

/*리스트의 앞부분에 노드를 삽입하는 함수*/
int insertFirst(headNode* h, int key) {

	/*삽입할 노드를 생성*/
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/*빈 리스트일 경우 노드를 삽입 후 함수 종료*/
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	/*첫번째 노드의 왼쪽 링크는 NULL을 갖는다*/
	node->llink = NULL;
	node->rlink = h->first;

	listNode* n = h->first;
	n->llink = node;
	h->first = node;


	return 0;
}

/*리스트의 첫번째 노드를 삭제하는 함수*/
int deleteFirst(headNode* h) {

	/*빈 리스트일 경우 "nothing to delete."를 출력한다*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	/*삭제할 노드의 주소정보를 n에 담아두고
	first가 두번째 노드를 가리키도록 한 후
	n을 이용해 노드의 메모리를 해제한다*/
	listNode *n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) {

	/*빈 리스트일 경우 "nothing to invert..."를 출력한다*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;			//연결이 역방향이 되는 두 노드 중 앞 노드를 가리킨다
		middle = n;				//연결이 역방향이 되는 두 노드 중 뒷 노드를 가리킨다
		n = n->rlink;			//n이 다음 노드를 가리킨다
		/*노드의 연결 방향을 바꾼다*/
		middle->rlink = trail;	//방향을 바꿀 노드의 rlink가 앞 노드의 주소를 갖는다
		middle->llink = n;		//방향을 바꿀 노드의 llink가 다음 노드의 주소를 갖는다
	}

	/*원래 리스트에서 마지막에 위치했던 노드를 첫 노드로 지정한다*/
	h->first = middle;

	return 0;
}

int insertNode(headNode* h, int key) {

	/*새로운 노드 생성*/
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	/*빈 리스트일 경우 노드를 리스트의 첫부분에 삽입*/
	if(h->first == NULL){
		h->first = node;
		return 0;
	}

	listNode *n = h->first;

	while(n != NULL){
		/*(이미 존재하는 노드의 key)>=(삽입할 노드의 key)일 때까지 n이 다음 노드를 가리키도록 반복*/
		if(n->key < key){
			n = n->rlink;
		}
		/*(이미 존재하는 노드의 key)>=(삽입할 노드의 key)인 경우*/
		else{
			/*n이 첫번째 노드를 가리킬 경우 insertFirst를 호출하여 삽입*/
			if(n == h->first){
				insertFirst(h, key);
				return 0;
			}
			/*n이 마지막 노드를 가리킬 경우 insertLast를 호출하여 삽입*/
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

	/*빈 리스트일 경우 "nothing to delete."를 출력한다*/
    if(h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;

	while(n != NULL){
		/*삭제할 노드를 찾았을 경우*/
		if(n->key == key){
			/*첫번째 노드일 경우 deleteFirst를 호출해 노드 제거*/
			if(n == h->first){
				deleteFirst(h);
			}
			/*마지막 노드일 경우 deleteLast를 호출해 노드 제거*/
			else if(n->rlink == NULL){
				deleteLast(h);
			}
			/*삭제할 노드의 오른쪽 노드 llink에 삭제할 노드의 왼쪽 노드의 주소를 넣고
			삭제할 노드의 왼쪽 노드 rlink에 삭제할 노드의 오른쪽 노드의 주소를 넣어
			연결을 끊고 메모리를 해제한다*/
			else{
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}
		n = n->rlink; //n이 다음 노드를 가리키도록 한다
	}

	/*삭제할 노드가 없을 경우*/
	printf("cannot find the node for key = %d\n", key);

	return 0;
}


