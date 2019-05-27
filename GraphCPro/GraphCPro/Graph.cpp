#include<iostream>
#include"Graph.h"
using namespace std;

//m_Graph图结构已经在主函数中定义，此处调用其
extern Graph m_Graph;

//初始化图结构
int Init()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;	//邻接矩阵置零
		}
		m_Graph.m_nVexNum = 0;				//景点数目置零
	}
	return OK;
}

//将顶点添加到数组中
int InsertVex(Vex sVex)
{ 
	//顶点已满
	if (m_Graph.m_nVexNum == 20)
		return ERROR;      
	//
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return OK;
}

//将边保存到邻接矩阵中
int InsertEdge(Edge sEdge)
{ 
	//下标越界
	if (sEdge.vex1<0 || sEdge.vex1 >= 20 || sEdge.vex2<0 || sEdge.vex2 >= 20)
		return ERROR;  
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return OK;
}

//查询指定顶点信息
Vex GetVex(int nVex)
{
	return m_Graph.m_aVexs[nVex];
}

//查询与指定顶点相连的边
int FindEdge(int nVex, Edge aEdge[])
{
	int flag = 0;  //与景点n相邻的边的条数
	//便利整个图的邻接矩阵
	for (int j = 0; j < 20; j++) {
		if (m_Graph.m_aAdjMatrix[nVex][j] != 0 && nVex!=j) {
			aEdge[flag].vex1 = nVex;
			aEdge[flag].vex2 = j;
			aEdge[flag].weight = m_Graph.m_aAdjMatrix[nVex][j];
			flag++;
		}
	}
	return flag;
}

//获取当前顶点数
int GetVexmun(){
	return m_Graph.m_nVexNum;
}

//实现图的深度优先搜索遍历
void DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList)
{
	bVisited[nVex] = true;				//改为已访问
	pList->vexs[nIndex++] = nVex;		//访问顶点nVex并赋值给链表，然后索引值自加

	//判断所有的顶点是否都已经被访问过									
	int v_num = 0;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		//如果当前i节点被访问过，则V-Num自加
		if (bVisited[i])
			v_num++;
	}
	
	//所有的顶点都已经被访问过,新增链表结点,保存此次的路径。必须保存，不然在后续的递归中会存在重复使用的vex，导致有的路径结点中vex没有值
	if (v_num == m_Graph.m_nVexNum)
	{		
		//创建一个新链表，将当前的pList中的数据保存起来
		pList->next = new Path;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;		//pList指针继续往下移动，寻找下一条路径
		pList->next = NULL;			//next赋值为空
	}
	//并没有全部访问，则进行寻找下一个相邻节点的操作
	else
	{
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//如果i是nVex的的邻接点  并且未被访问
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i]>0)	
			{
				DFS(i, bVisited, nIndex, pList);			//递归调用DFS
				bVisited[i] = false;						//改为未访问，回退
				nIndex--;									//索引值减一
			}
		}
	}
}

//深度优先遍历
void DFSTraverse(int nVex, PathList & pList)
{
	int nIndex = 0;					//遍历深度
	bool bVisited[20] = { false };  //所有的景点起始均为未访问
	DFS(nVex, bVisited, nIndex, pList);

}

//寻找最短路径
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[20][20];       //保存最短路径，其中行表示终点，列表示从起点到终点的最短路径的每一步
	int nShortDistance[20];       //保存最短距离，保存从起点到任一顶点的最短距离
	bool aVisited[20];            //判断某顶点是否已经加入到最短路径中
	int v;                        //在下面的循环中，表示每一次找到的可以加入集合的顶点，即已经找到了从起点到该顶点的最短路径

	//初始化工作
	for (v = 0; v<m_Graph.m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			//初始化该顶点到其他顶点的最短距离，默认为两顶点间的距离
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			//如果顶点v和nVexStart不相连，则最短距离设置为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;   //起始点为nVexStart
		//初始化最短路径
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}

	//初始化，将nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;
	int min;					//暂存路径的最小值
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//判断是否还有顶点可以加入集合
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w]<min)
			{
				v = w;						//w顶点距离nVexStart顶点最近
				min = nShortDistance[w];	//w到nVexStart的最短距离为min
				bAdd = true;
			}
		}
		//若果没有顶点可以加入到集合，则跳出循环
		if (!bAdd) break;
		aVisited[v] = true;			//将w顶点加入到集合
		nShortPath[v][i] = v;		//每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			//将w作为过渡顶点计算nVexStart通过w到每个顶点的距离
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w]<nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w]>0))
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w]; 			
			   	for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//如果通过w达到顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}

	return nIndex;

	/*
	bool bVisited[20] = { false };				//初始化全部结点为未访问
	int start = nVexStart,end= nVexStart;		//将起点值赋值给中间起点start方便调用；终点同起点
	int  index = 0;								//访问深度/路线长度
	bVisited[start] = true;						//起点设置为已访问

	//循环，直到中间结果的终点与真正的终点nVexEnd重合，即寻找完毕
	while (end != nVexEnd) {
		int MaxWeight = 0x7fffffff;					//定义一个初始最大路径
		//寻找相邻接点 start->end 的最短路径
		for (int j = 0; j < m_Graph.m_nVexNum; j++) {
			//如果j->i直接相连，并且权值小于当前已知的最大权值，并且当前重点j未被访问，那么这两个点就更近一点
			if (m_Graph.m_aAdjMatrix[start][j] > 0 && m_Graph.m_aAdjMatrix[start][j] < MaxWeight && !bVisited[j]) {
				MaxWeight = m_Graph.m_aAdjMatrix[start][j];
				end = j;
				bVisited[j] = true;
				if (end == nVexEnd)		//如果此时的点已经是终点，那么久不需要继续进行
					break;
			}
		}
		
		//将与中间的起点start传值给aPath保存
		aPath[index].vex1 = start;
		aPath[index].vex2 = end;
		aPath[index++].weight = MaxWeight;
		//下一次循环的起点为这次的终点
		start = end;
	}
	return index;		//返回深度（即找到的路径个数）*/
}

void FindMinTree(Edge aPath[])
{
	bool aVisited[20] = { false };		//判断某顶点是否在最小生成树中，true表示已经添加到了最小生成树中
	aVisited[0] = true;					//从0号顶点开始，加入到集合中
	int min;
	int nVex1, nVex2;
	
	for (int k = 0; k<m_Graph.m_nVexNum - 1; k++)
	{
		min = 0x7FFFFFFF;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//从集合中取一个顶点
			if (aVisited[i])
			{
				for (int j = 0; j<m_Graph.m_nVexNum; j++)
				{
					//从不在集合中的顶点 中取出一个顶点
					if (!aVisited[j])
					{
						if ((m_Graph.m_aAdjMatrix[i][j]<min) && (m_Graph.m_aAdjMatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							//找出最短边
							min = m_Graph.m_aAdjMatrix[i][j];
						}
					}
				}
			}
		}

		//保存最短边的两个顶点
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];
		//将两个顶点加入集合
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}

}
