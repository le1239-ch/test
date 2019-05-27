#include<iostream>
#include"Graph.h"
using namespace std;

//m_Graphͼ�ṹ�Ѿ����������ж��壬�˴�������
extern Graph m_Graph;

//��ʼ��ͼ�ṹ
int Init()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;	//�ڽӾ�������
		}
		m_Graph.m_nVexNum = 0;				//������Ŀ����
	}
	return OK;
}

//��������ӵ�������
int InsertVex(Vex sVex)
{ 
	//��������
	if (m_Graph.m_nVexNum == 20)
		return ERROR;      
	//
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return OK;
}

//���߱��浽�ڽӾ�����
int InsertEdge(Edge sEdge)
{ 
	//�±�Խ��
	if (sEdge.vex1<0 || sEdge.vex1 >= 20 || sEdge.vex2<0 || sEdge.vex2 >= 20)
		return ERROR;  
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return OK;
}

//��ѯָ��������Ϣ
Vex GetVex(int nVex)
{
	return m_Graph.m_aVexs[nVex];
}

//��ѯ��ָ�����������ı�
int FindEdge(int nVex, Edge aEdge[])
{
	int flag = 0;  //�뾰��n���ڵıߵ�����
	//��������ͼ���ڽӾ���
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

//��ȡ��ǰ������
int GetVexmun(){
	return m_Graph.m_nVexNum;
}

//ʵ��ͼ�����������������
void DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList)
{
	bVisited[nVex] = true;				//��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;		//���ʶ���nVex����ֵ������Ȼ������ֵ�Լ�

	//�ж����еĶ����Ƿ��Ѿ������ʹ�									
	int v_num = 0;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		//�����ǰi�ڵ㱻���ʹ�����V-Num�Լ�
		if (bVisited[i])
			v_num++;
	}
	
	//���еĶ��㶼�Ѿ������ʹ�,����������,����˴ε�·�������뱣�棬��Ȼ�ں����ĵݹ��л�����ظ�ʹ�õ�vex�������е�·�������vexû��ֵ
	if (v_num == m_Graph.m_nVexNum)
	{		
		//����һ������������ǰ��pList�е����ݱ�������
		pList->next = new Path;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;		//pListָ����������ƶ���Ѱ����һ��·��
		pList->next = NULL;			//next��ֵΪ��
	}
	//��û��ȫ�����ʣ������Ѱ����һ�����ڽڵ�Ĳ���
	else
	{
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//���i��nVex�ĵ��ڽӵ�  ����δ������
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i]>0)	
			{
				DFS(i, bVisited, nIndex, pList);			//�ݹ����DFS
				bVisited[i] = false;						//��Ϊδ���ʣ�����
				nIndex--;									//����ֵ��һ
			}
		}
	}
}

//������ȱ���
void DFSTraverse(int nVex, PathList & pList)
{
	int nIndex = 0;					//�������
	bool bVisited[20] = { false };  //���еľ�����ʼ��Ϊδ����
	DFS(nVex, bVisited, nIndex, pList);

}

//Ѱ�����·��
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[20][20];       //�������·���������б�ʾ�յ㣬�б�ʾ����㵽�յ�����·����ÿһ��
	int nShortDistance[20];       //������̾��룬�������㵽��һ�������̾���
	bool aVisited[20];            //�ж�ĳ�����Ƿ��Ѿ����뵽���·����
	int v;                        //�������ѭ���У���ʾÿһ���ҵ��Ŀ��Լ��뼯�ϵĶ��㣬���Ѿ��ҵ��˴���㵽�ö�������·��

	//��ʼ������
	for (v = 0; v<m_Graph.m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			//��ʼ���ö��㵽�����������̾��룬Ĭ��Ϊ�������ľ���
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			//�������v��nVexStart������������̾�������Ϊ���ֵ
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;   //��ʼ��ΪnVexStart
		//��ʼ�����·��
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}

	//��ʼ������nVexStart������뵽������
	aVisited[nVexStart] = true;
	int min;					//�ݴ�·������Сֵ
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//�ж��Ƿ��ж�����Լ��뼯��
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w]<min)
			{
				v = w;						//w�������nVexStart�������
				min = nShortDistance[w];	//w��nVexStart����̾���Ϊmin
				bAdd = true;
			}
		}
		//����û�ж�����Լ��뵽���ϣ�������ѭ��
		if (!bAdd) break;
		aVisited[v] = true;			//��w������뵽����
		nShortPath[v][i] = v;		//ÿ���ҵ����·���󣬾��൱�ڴ�Դ����������յ㣬����nShortPath[v][i]=v
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			//��w��Ϊ���ɶ������nVexStartͨ��w��ÿ������ľ���
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w]<nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w]>0))
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w]; 			
			   	for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//���ͨ��w�ﵽ����i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
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
	bool bVisited[20] = { false };				//��ʼ��ȫ�����Ϊδ����
	int start = nVexStart,end= nVexStart;		//�����ֵ��ֵ���м����start������ã��յ�ͬ���
	int  index = 0;								//�������/·�߳���
	bVisited[start] = true;						//�������Ϊ�ѷ���

	//ѭ����ֱ���м������յ����������յ�nVexEnd�غϣ���Ѱ�����
	while (end != nVexEnd) {
		int MaxWeight = 0x7fffffff;					//����һ����ʼ���·��
		//Ѱ�����ڽӵ� start->end �����·��
		for (int j = 0; j < m_Graph.m_nVexNum; j++) {
			//���j->iֱ������������ȨֵС�ڵ�ǰ��֪�����Ȩֵ�����ҵ�ǰ�ص�jδ�����ʣ���ô��������͸���һ��
			if (m_Graph.m_aAdjMatrix[start][j] > 0 && m_Graph.m_aAdjMatrix[start][j] < MaxWeight && !bVisited[j]) {
				MaxWeight = m_Graph.m_aAdjMatrix[start][j];
				end = j;
				bVisited[j] = true;
				if (end == nVexEnd)		//�����ʱ�ĵ��Ѿ����յ㣬��ô�ò���Ҫ��������
					break;
			}
		}
		
		//�����м�����start��ֵ��aPath����
		aPath[index].vex1 = start;
		aPath[index].vex2 = end;
		aPath[index++].weight = MaxWeight;
		//��һ��ѭ�������Ϊ��ε��յ�
		start = end;
	}
	return index;		//������ȣ����ҵ���·��������*/
}

void FindMinTree(Edge aPath[])
{
	bool aVisited[20] = { false };		//�ж�ĳ�����Ƿ�����С�������У�true��ʾ�Ѿ���ӵ�����С��������
	aVisited[0] = true;					//��0�Ŷ��㿪ʼ�����뵽������
	int min;
	int nVex1, nVex2;
	
	for (int k = 0; k<m_Graph.m_nVexNum - 1; k++)
	{
		min = 0x7FFFFFFF;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//�Ӽ�����ȡһ������
			if (aVisited[i])
			{
				for (int j = 0; j<m_Graph.m_nVexNum; j++)
				{
					//�Ӳ��ڼ����еĶ��� ��ȡ��һ������
					if (!aVisited[j])
					{
						if ((m_Graph.m_aAdjMatrix[i][j]<min) && (m_Graph.m_aAdjMatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							//�ҳ���̱�
							min = m_Graph.m_aAdjMatrix[i][j];
						}
					}
				}
			}
		}

		//������̱ߵ���������
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];
		//������������뼯��
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}

}
