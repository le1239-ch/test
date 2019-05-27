#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#define OK 1
#define ERROR 0

//���徰�㣨ͼ�Ķ��㣩
struct Vex
{
	int num;					//����ı��
	char name[20];				//���������
	char desc[1024];			//���������
};

//�����·��Ϣ��ͼ�ıߣ�
struct Edge
{
	int vex1;					//�ߵĵ�һ������
	int vex2;					//�ߵĵڶ�������
	int weight;					//Ȩֵ�����������ھ���ľ���
};

//����ͼ
struct Graph
{
	int m_aAdjMatrix[20][20];   //�����ڽӾ������ʽ����
	Vex m_aVexs[20];            //��������
	int m_nVexNum;              //�������Ŀ
};

//����·��
typedef struct Path
{
	int vexs[20];				//�����һ��������·��
	Path *next;					//��һ��·��
}*PathList;


//��ʼ��ͼ�ṹ
int Init();

//��������ӵ�������
int InsertVex(Vex sVex);

//���߱��浽�ڽӾ�����
int InsertEdge(Edge sEdge);

//��ѯָ��������Ϣ
Vex GetVex(int nVex);

//��ѯ��ָ�����������ı�
int FindEdge(int nVex, Edge aEdge[]);

//��ȡ��ǰ������
int GetVexmun();

//==============2==================

//ʵ��ͼ�����������������
void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);

//������ȱ���
void DFSTraverse(int nVex, PathList &pList);

//==============3===================

//ͨ��Dijkstra�㷨���nVexStart��nVexEnd�����·��
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);


//=============3=====================

//������С������
void FindMinTree(Edge aPath[]);

#endif
