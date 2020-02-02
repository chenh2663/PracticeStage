#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct LinkNode{
	ElemType data;
	struct LinkNode *next;
}LinkNode;
typedef struct{
	LinkNode *front,*rear;//����ͷ ����β
}LinkQueue;//�Ƚ��ȳ�

void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));//ͷ��βָ��ͬһ�����
	Q.front->next=NULL;
}

bool IsEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return true;
	else
		return false;
}

void EnQueue(LinkQueue &Q,ElemType x)
{
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data=x;s->next=NULL;
	Q.rear->next=s;
	Q.rear=s;
}
//����  ͷ��ɾ����
bool DeQueue(LinkQueue &Q,ElemType &x)
{
	if(Q.front==Q.rear) return false;//����Ϊ��
	LinkNode *p=Q.front->next;//ͷ���ʲô��û�棬����ͷ������һ���ڵ��������
	x=p->data;
	Q.front->next=p->next;//����
	if(Q.rear==p)//ɾ���������һ��Ԫ��
		Q.rear=Q.front;//������Ϊ��
	free(p);
	return true;
}
//���������ߣ���롷�γ�
//�����������ݽṹ 3.2.3 ���е���ʽ�洢
//ͷ��ɾ������β�����뷨
int main()
{
	LinkQueue Q;
	bool ret;
	ElemType element;//�洢����Ԫ��
	InitQueue(Q);
	EnQueue(Q,3);
	EnQueue(Q,4);
	EnQueue(Q,5);
	EnQueue(Q,6);
	EnQueue(Q,7);
	ret=DeQueue(Q,element);
	if(ret)
	{
		printf("���ӳɹ�,Ԫ��ֵΪ %d\n",element);
	}else{
		printf("����ʧ��\n");
	}
	system("pause");
}
//��ϰʵս�⣺ʵ��˫�˶��У�������ޣ��������޵�˫�˶��У���ô�죿
//cskaoyan.com