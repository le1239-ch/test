#include<iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>
#include<assert.h>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

//m_Graphͼ�ṹ�Ѿ����������ж��壬�˴�������
extern Graph m_Graph;

//��ȡ�ļ���������������ͼ
int CreateGraph() {
	cout << "=====�������㾰��ͼ=====" << endl;

	Init();			//��ʼ��ͼ

	//��ȡVex.txt�ļ��������е�����ͨ�� ����Vex ���ص� ͼm_Graph ��
	ifstream VexFile("Vex.txt");      

	//������ļ�ʧ�ܣ���ʾ������Ϣ������
	if (!VexFile) {
		cout << "Vex.txt�ļ���ʧ�ܣ����飡" << endl;
		return ERROR;
	}

	//��������һ��Char���������������ʱ�����Vex.txt��ȡ��һ������
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;

	//���ж�ȡVex.txt�ļ��е�����
	VexFile.getline(num, 2);		//����һ�е����ݶ���������
	cout << "������Ŀ��"<<atoi(num) << endl ;
	cout << "�������������������㡪��������������" << endl;
	cout << "���\t��������\t��������" << endl;
	while (VexFile.getline(num,2)){
		sVex.num = atoi(num);

		VexFile.getline(name, 20);
		strcpy(sVex.name, name);

		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		//��Ŀǰ����Vex ��Ϣ���
		cout << sVex.num<<"\t"<<sVex.name<<"\t\t"<<sVex.desc<< endl;

		//���������ͼ�в����ݷ���ֵ���д�����ʾ
		if (!InsertVex(sVex)) {
			cout << "��������ʧ�ܣ�" << endl;
			continue;
		}
	}
	//�ر��ļ�
	VexFile.close();

	/*
	ifstream EdgeFile("Edge.txt");
	if (!EdgeFile) {
		cout << "Edge.txt�ļ���ʧ�ܣ����飡" << endl;
		return ERROR;
	}
	Edge SEdge;
	cout << "�����������������ߡ�������������" << endl;
	cout << "���\t�յ�\tȨֵ" << endl;
	while (EdgeFile)
	{
		EdgeFile >> SEdge.vex1 >> SEdge.vex2 >> SEdge.weight;

		cout << SEdge.vex1 << "\t" << SEdge.vex2 << "\t" << SEdge.weight << endl;

		if (!InsertEdge(SEdge))
		{
			cout << "����·����Ϣʧ�ܣ�" << endl;
			continue;
		}
	}
	EdgeFile.close();*/

	/*=============================================*/
	FILE *EdgeFile = fopen("Edge.txt", "r");
	if (!EdgeFile) {
		cout << "Edge.txt�ļ���ʧ�ܣ����飡" << endl;
		return ERROR;
	}
	cout << "-----��-----" << endl;
	Edge sEdge;
	while (fscanf(EdgeFile, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		cout << "<" << sEdge.vex1 << "," << sEdge.vex2 << ">  " << sEdge.weight << endl;
		//������
		if (!InsertEdge(sEdge))
		{
			cout << "����·����Ϣʧ�ܣ�" << endl;
			continue;
		}
	}
	fclose(EdgeFile);

	cout << endl;
	return OK;
}

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
int GetSPotInfo() {
	cout << "=====��ѯ������Ϣ=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return ERROR;
	}
	//��������Ϣ�г���
	cout << "��ǰ����������" << m_Graph.m_nVexNum << endl ;
	cout << "���\t��������" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "\t" << sVex.name << endl;
	}

	//��ʾ�û����ݱ����ѯ
	cout << "\n��������Ҫ��ѯ�ľ����ţ�";
	int querynum;
	cin >> querynum;
	if (querynum<0 || querynum >= m_Graph.m_nVexNum)
		cout << "�������" << endl;
	else
	{
		Vex sVex = GetVex(querynum);
		cout << "��������\t��������" << endl;
		cout << sVex.name << "\t\t" << sVex.desc << endl ;

		//���ܱ߾���ͬ�����
		cout << "-----�ܱ߾���-----" << endl;
		Edge aEdge[20];
		int EdgeNum = FindEdge(querynum, aEdge);   //�ܱ߾������Ŀ
		cout << "�ܱ߾�����Ŀ��" << EdgeNum << endl;
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

//�õ����㵼��ͼ·�ߣ�����ʾ
void TravelPath()
{
	//�������ǰ�����Լ����
	cout << "=====���ξ��㵼��=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//��ʾ�û�ѡ�񾰵����
	cout << "��������Ҫ��ʼ���ţ�";
	int startplace;		//�����
	cin >> startplace;
	//�ж��û������Ƿ���Ϲ淶
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "�������" << endl;
		return;
	}

	//��ѯ��startplace��ʼ��·����Ϣ
	PathList pList = new Path;
	PathList pHead = pList;
	//�õ�·����Ϣ
	DFSTraverse(startplace, pList);    

	//���·����Ϣ
	cout << "���ο�·�ߣ�" << endl;
	int i = 1;
	pList = pHead;			//ͷָ��һֱ�ڣ����丳ֵ��pList��������������
	while (pList->next!=NULL)
	{
		//���һ��·����Ϣ
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "·��" << i++ << "��" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//ָ��������ƣ�������һ�����
	}
	cout << endl;
	//ָ��������
	delete pList;
	pList = NULL;
	pHead = NULL;
}

void FindShortPath(void)
{
	//���Ŀ¼�������Ϣ
	cout << "==========�������·��==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//��ʾ�û�������Ϣ
	int start_place, end_place;
	cout << "���������ı�ţ�";
	cin >> start_place;
	cout << "�������յ�ı�ţ�";
	cin >> end_place;
	//�ж��û��������Ϣ�Ƿ���Ϲ淶
	if (start_place<0 || start_place >= m_Graph.m_nVexNum || end_place<0 || end_place >= m_Graph.m_nVexNum)
	{
		cout << "�������" << endl;
		return;
	}

	Edge aPath[20];						//����Ϣ���飬���α�����̵�·��
	for (int i = 0; i < 20; i++) {		//��ʼ������Ϣ���飨��Ҫ�ɲ�Ҫ��
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}
	//�������·�����������·��������index��ֵ
	int index=FindShortPath(start_place, end_place, aPath);
	int length = 0;						//���·���ܳ���
	Vex sVex = GetVex(aPath[0].vex1);	//������Ϣ��������Ϣ��

	//�����·���������ʾ
	cout << "���·��Ϊ��"<<sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "��̾���Ϊ��" << length << endl << endl;;

}

void DesigePath(void)
{
	cout << "==========�����·�滮==========" << endl;
	Edge aPath[20];
	FindMinTree(aPath);
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}

	int nAllLength = 0;
	cout << "��������������֮�������·��" << endl;
	//Vex nVex1, nVex2;
	for (int i = 0; i<m_Graph.m_nVexNum - 1; i++)
	{
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);
		//��������·��
		cout << nVex1.name << "-" << nVex2.name << "    " << aPath[i].weight << "m" << endl;
		nAllLength += aPath[i].weight;
	}
	cout << "�����·���ܳ����ǣ�" << nAllLength << "m" << endl;
}
