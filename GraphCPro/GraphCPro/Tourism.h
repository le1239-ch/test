#pragma once
#ifndef TOURISM_H
#define TOURISM_H

#define OK 1
#define ERROR 0

//读取文件，创建景区景点图
int CreateGraph();

//查询指定景点信息，显示到相邻景点的距离
int GetSPotInfo();

//得到景点导航图路线，并显示
void TravelPath();

//通过调用函数查询两个景点之间的最短路径和距离
void FindShortPath(void);

//查询铺设电路规划图
void DesigePath(void);


#endif