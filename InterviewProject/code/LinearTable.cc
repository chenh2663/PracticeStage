#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//ͷ�巨�½�����
LinkList CreatList1(LinkList &L)
{
	LNode *s;int x;
	L=(LinkList)malloc(sizeof(LNode));//��ͷ�ڵ������
	L->next=NULL;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		s->next=L->next;
		L->next=s;
		scanf("%d",&x);
	}
	return L;
}
//β�巨�½�����
LinkList CreatList2(LinkList &L)
{
	int x;
	L=(LinkList)malloc(sizeof(LNode));//��ͷ�ڵ������
	LNode *s,*r=L;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		r->next=s;
		r=s;//rָ���µı�β���
		scanf("%d",&x);
	}
	r->next=NULL;
	return L;
}
//����Ų��ҽ��ֵ
LNode *GetElem(LinkList L,int i)
{
	int j=1;
	LNode *p=L->next;
	if(i==0)
		return L;
	if(i<1)
		return NULL;
	while(p&&j<i)
	{
		p=p->next;
		j++;
	}
	return p;
}
//��ֵ����
LNode *LocateElem(LinkList L,ElemType e)
{
	LNode *p=L->next;
	while(p!=NULL&&p->data!=e)
		p=p->next;
	return p;
}
//�½������i��λ��
bool ListFrontInsert(LinkList L,int i,ElemType e)
{
	LinkList p=GetElem(L,i-1);
	if(NULL==p)
	{
		return false;
	}
	LinkList s=(LNode*)malloc(sizeof(LNode));//Ϊ�²���Ľ������ռ�
	s->data=e;
	s->next=p->next;
	p->next=s;
	return true;
}
//ɾ����i�����
bool ListDelete(LinkList L,int i)
{
	LinkList p=GetElem(L,i-1);
	if(NULL==p)
	{
		return false;
	}
	LinkList q;
	q=p->next;
	p->next=q->next;
	free(q);
	return true;
}
//��ӡ������ÿ������ֵ
void PrintList(LinkList L)
{
	L=L->next;
	while(L!=NULL)
	{
		printf("%3d",L->data);
		L=L->next;
	}
	printf("\n");
}
int main()
{
	LinkList L;
	LinkList search;
	//CreatList1(L);//�������ݿ���Ϊ3 4 5 6 7 9999
	CreatList2(L);//�������ݿ���Ϊ3 4 5 6 7 9999
	PrintList(L);
	search=GetElem(L,2);
	if(search!=NULL)
	{
		printf("����Ų��ҳɹ�\n");
		printf("%d\n",search->data);
	}
	search=LocateElem(L,6);
	if(search!=NULL)
	{
		printf("��ֵ���ҳɹ�\n");
		printf("%d\n",search->data);
	}
	ListFrontInsert(L,2,99);
	PrintList(L);
	ListDelete(L,4);
	PrintList(L);
	system("pause");
}