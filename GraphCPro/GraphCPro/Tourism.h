#pragma once
#ifndef TOURISM_H
#define TOURISM_H

#define OK 1
#define ERROR 0

//��ȡ�ļ���������������ͼ
int CreateGraph();

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
int GetSPotInfo();

//�õ����㵼��ͼ·�ߣ�����ʾ
void TravelPath();

//ͨ�����ú�����ѯ��������֮������·���;���
void FindShortPath(void);

//��ѯ�����·�滮ͼ
void DesigePath(void);


#endif