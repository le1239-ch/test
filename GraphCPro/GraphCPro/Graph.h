#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#define OK 1
#define ERROR 0

//定义景点（图的顶点）
struct Vex
{
	int num;					//景点的编号
	char name[20];				//景点的名称
	char desc[1024];			//景点的描述
};

//定义道路信息（图的边）
struct Edge
{
	int vex1;					//边的第一个顶点
	int vex2;					//边的第二个顶点
	int weight;					//权值，即两个相邻景点的距离
};

//定义图
struct Graph
{
	int m_aAdjMatrix[20][20];   //采用邻接矩阵的形式储存
	Vex m_aVexs[20];            //顶点数组
	int m_nVexNum;              //景点的数目
};

//搜索路径
typedef struct Path
{
	int vexs[20];				//保存的一条完整的路径
	Path *next;					//下一条路径
}*PathList;


//初始化图结构
int Init();

//将定点添加到数组中
int InsertVex(Vex sVex);

//将边保存到邻接矩阵中
int InsertEdge(Edge sEdge);

//查询指定顶点信息
Vex GetVex(int nVex);

//查询与指定顶点相连的边
int FindEdge(int nVex, Edge aEdge[]);

//获取当前顶点数
int GetVexmun();

//==============2==================

//实现图的深度优先搜索遍历
void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);

//深度优先遍历
void DFSTraverse(int nVex, PathList &pList);

//==============3===================

//通过Dijkstra算法求得nVexStart到nVexEnd的最短路径
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);


//=============3=====================

//构建最小生成树
void FindMinTree(Edge aPath[]);

#endif
