#include<iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>
#include<assert.h>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

//m_Graph图结构已经在主函数中定义，此处调用他
extern Graph m_Graph;

//读取文件，创建景区景点图
int CreateGraph() {
	cout << "=====创建景点景区图=====" << endl;

	Init();			//初始化图

	//读取Vex.txt文件，将其中的数据通过 景点Vex 加载到 图m_Graph 中
	ifstream VexFile("Vex.txt");      

	//如果打开文件失败，显示错误信息并返回
	if (!VexFile) {
		cout << "Vex.txt文件打开失败，请检查！" << endl;
		return ERROR;
	}

	//定义以下一个Char数组参数，用来暂时保存从Vex.txt读取的一行数据
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;

	//逐行读取Vex.txt文件中的数据
	VexFile.getline(num, 2);		//将第一行的数据读出，丢掉
	cout << "景区数目："<<atoi(num) << endl ;
	cout << "————————顶点————————" << endl;
	cout << "编号\t景区名称\t景区描述" << endl;
	while (VexFile.getline(num,2)){
		sVex.num = atoi(num);

		VexFile.getline(name, 20);
		strcpy(sVex.name, name);

		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		//将目前景点Vex 信息输出
		cout << sVex.num<<"\t"<<sVex.name<<"\t\t"<<sVex.desc<< endl;

		//将景点插入图中并根据反馈值进行错误提示
		if (!InsertVex(sVex)) {
			cout << "新增景点失败！" << endl;
			continue;
		}
	}
	//关闭文件
	VexFile.close();

	/*
	ifstream EdgeFile("Edge.txt");
	if (!EdgeFile) {
		cout << "Edge.txt文件打开失败，请检查！" << endl;
		return ERROR;
	}
	Edge SEdge;
	cout << "————————边———————" << endl;
	cout << "起点\t终点\t权值" << endl;
	while (EdgeFile)
	{
		EdgeFile >> SEdge.vex1 >> SEdge.vex2 >> SEdge.weight;

		cout << SEdge.vex1 << "\t" << SEdge.vex2 << "\t" << SEdge.weight << endl;

		if (!InsertEdge(SEdge))
		{
			cout << "新增路径信息失败！" << endl;
			continue;
		}
	}
	EdgeFile.close();*/

	/*=============================================*/
	FILE *EdgeFile = fopen("Edge.txt", "r");
	if (!EdgeFile) {
		cout << "Edge.txt文件打开失败，请检查！" << endl;
		return ERROR;
	}
	cout << "-----边-----" << endl;
	Edge sEdge;
	while (fscanf(EdgeFile, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		cout << "<" << sEdge.vex1 << "," << sEdge.vex2 << ">  " << sEdge.weight << endl;
		//新增边
		if (!InsertEdge(sEdge))
		{
			cout << "新增路径信息失败！" << endl;
			continue;
		}
	}
	fclose(EdgeFile);

	cout << endl;
	return OK;
}

//查询指定景点信息，显示到相邻景点的距离
int GetSPotInfo() {
	cout << "=====查询景点信息=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return ERROR;
	}
	//将景点信息列出来
	cout << "当前景区个数：" << m_Graph.m_nVexNum << endl ;
	cout << "编号\t景点名称" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "\t" << sVex.name << endl;
	}

	//提示用户根据编码查询
	cout << "\n请输入想要查询的景点编号：";
	int querynum;
	cin >> querynum;
	if (querynum<0 || querynum >= m_Graph.m_nVexNum)
		cout << "输入错误！" << endl;
	else
	{
		Vex sVex = GetVex(querynum);
		cout << "景点名称\t景点描述" << endl;
		cout << sVex.name << "\t\t" << sVex.desc << endl ;

		//将周边景区同样输出
		cout << "-----周边景区-----" << endl;
		Edge aEdge[20];
		int EdgeNum = FindEdge(querynum, aEdge);   //周边景点的数目
		cout << "周边景区数目：" << EdgeNum << endl;
		for (int i = 0; i<EdgeNum; i++)
		{
			Vex v1 = GetVex(aEdge[i].vex1);
			Vex v2 = GetVex(aEdge[i].vex2);
			cout << v1.name << "->" << v2.name << "  " << aEdge[i].weight << "m" << endl;
		}
	}
	cout << endl;
	return OK;
}

//得到景点导航图路线，并显示
void TravelPath()
{
	//先输出当前景点以及编号
	cout << "=====旅游景点导航=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//提示用户选择景点起点
	cout << "请输入想要起始点编号：";
	int startplace;		//起点编号
	cin >> startplace;
	//判断用户输入是否符合规范
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "输入错误！" << endl;
		return;
	}

	//查询从startplace开始的路径信息
	PathList pList = new Path;
	PathList pHead = pList;
	//得到路径信息
	DFSTraverse(startplace, pList);    

	//输出路径信息
	cout << "供参考路线：" << endl;
	int i = 1;
	pList = pHead;			//头指针一直在，将其赋值给pList，用来遍历链表
	while (pList->next!=NULL)
	{
		//输出一条路径信息
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "路线" << i++ << "：" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//指针继续下移，遍历下一个结点
	}
	cout << endl;
	//指针做处理
	delete pList;
	pList = NULL;
	pHead = NULL;
}

void FindShortPath(void)
{
	//输出目录等相关信息
	cout << "==========搜索最短路径==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//提示用户输入信息
	int start_place, end_place;
	cout << "请输入起点的编号：";
	cin >> start_place;
	cout << "请输入终点的编号：";
	cin >> end_place;
	//判断用户输入的信息是否符合规范
	if (start_place<0 || start_place >= m_Graph.m_nVexNum || end_place<0 || end_place >= m_Graph.m_nVexNum)
	{
		cout << "输入错误！" << endl;
		return;
	}

	Edge aPath[20];						//边信息数组，依次保存最短的路径
	for (int i = 0; i < 20; i++) {		//初始化边信息数组（可要可不要）
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}
	//查找最短路径，并给最短路径的条数index赋值
	int index=FindShortPath(start_place, end_place, aPath);
	int length = 0;						//最短路径总长度
	Vex sVex = GetVex(aPath[0].vex1);	//顶点信息（景点信息）

	//将最短路径输出，显示
	cout << "最短路径为："<<sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "最短距离为：" << length << endl << endl;;

}

void DesigePath(void)
{
	cout << "==========铺设电路规划==========" << endl;
	Edge aPath[20];
	FindMinTree(aPath);
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}

	int nAllLength = 0;
	cout << "在以下两个景点之间铺设电路：" << endl;
	//Vex nVex1, nVex2;
	for (int i = 0; i<m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);
		//输出铺设的路线
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "铺设电路的总长度是：" << nAllLength << "m" << endl;
}
