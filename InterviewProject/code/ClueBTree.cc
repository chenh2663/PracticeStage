#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElemType;
typedef struct ThreadNode{
        ElemType data;
        struct ThreadNode *lchild,*rchild;
        int ltag,rtag;
}ThreadNode,*ThreadTree;
//手工建线索树，总计5个结点
void BulidThreadTree(ThreadTree &T)
{
        ThreadTree arr[5];
        int i;
        for(i=0;i<5;i++)
        {
                arr[i]=(ThreadTree)malloc(sizeof(ThreadNode));
                memset(arr[i],0,sizeof(ThreadNode));
                arr[i]->data='A'+i;
        }
        arr[0]->lchild=arr[1];
        arr[0]->rchild=arr[2];
        arr[1]->rchild=arr[3];
        arr[2]->lchild=arr[4];
        T=arr[0];
}
void InThread(ThreadTree &p,ThreadTree &pre)
{
        if(p!=NULL){
                InThread(p->lchild,pre);
                if(p->lchild==NULL){
                        p->lchild=pre;
                        p->ltag=1;
                }
                if(pre!=NULL&&pre->rchild==NULL){
                        pre->rchild=p;
                        pre->rtag=1;
                }
                pre=p;
                InThread(p->rchild,pre);
        }
}
void CreateInThread(ThreadTree T)
{
        ThreadTree pre=NULL;
        if(T!=NULL){
                InThread(T,pre);
                pre->rchild=NULL;
                pre->rtag=1;
        }
}
//中序序列下的第一个结点
ThreadNode *Firstnode(ThreadNode *p)
{
        while(p->ltag==0)
                p=p->lchild;
        return p;
}
//p在中序序列下的后继结点

int main()
{
        ThreadTree T;
        ThreadTree p;
        BulidThreadTree(T);
        CreateInThread(T);
        p=Firstnode(T);
        printf("最左下结点值为 %d\n",p);
        system("pause");
}
