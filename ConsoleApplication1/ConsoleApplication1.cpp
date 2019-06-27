// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>

using std::cin;
using std::cout;
using std::endl;

#define MAXVEX 10
#define TRUE 1
#define FALSE 0
#define INF 65535
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

typedef char VertexType;
typedef struct
{
	VertexType vexs[MAXVEX]; //顶点数组集合
	int arc[MAXVEX][MAXVEX]; //边的“权值”
	int numVertexes, //顶点的数量
		numEdges;	//边的数量
}MGraph;

//1.构建邻接矩阵的二维数组（手动的给定一些值）
void CreateMGraphExample(MGraph *G)
{
	/*VertexType vexs[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
	int arc[][9] = {
		{0, 10, INF, INF, INF, 11, INF, INF, INF},
		{10, 0, 18, INF, INF, INF, 16, INF, 12},
		{INF, 18, 0, 22, INF, INF, INF, INF, 8},
		{INF, INF, 22, 0, 20, INF, INF, 16, 21},
		{INF, INF, INF, 20, 0, 26, INF, 7, INF},
		{11, INF, INF, INF, 26, 0, 17, INF, INF},
		{INF, 16, INF, INF, INF, 17, 0, 19, INF},
		{INF, INF, INF, 16, 7, INF, 19, 0, INF},
		{INF, 12, 8, 21, INF, INF, INF, INF, 0}
	};*/
	int vexCount = 0;
	printf("请输入顶点个数(顶点计数从0开始)：");
	cin >> vexCount;
	G->numVertexes = vexCount;//顶点数
	//1.创建顶点集合
	for (int i = 0; i < vexCount; i++)
	{
		G->vexs[i] = i;
	}
	//2.先构造一个二维数组，值都为INF
	for (int i = 0; i < vexCount; i++)
	{
		for (int j = 0; j < vexCount; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = INF;
		}
	}
	//3.输入点与点之间的权值
	int pointA = 0;
	int pointB = 0;
	int quan = 0;
	printf("\n开始输入连接顶点和权值（A<0 结束输入）：\n");
	do
	{
		printf("\n顶点A=");
		cin >> pointA;
		if (pointA < 0) 
		{
			printf(" 输入结束\n--------------------------\n");
			 break;
		}
		else if (pointA >= vexCount)
		{
			printf("索引出界，输入无效。\n--------------------------\n");
			continue;
		}
		printf("顶点B=");
		cin >> pointB;
		if (pointB < 0 || pointB >= vexCount)
		{
			printf("索引出界，无效。\n--------------------------\n");
			continue;
		}
		if (pointA == pointB)
		{
			printf("A=B无效。\n--------------------------\n");
			continue;
		}
		printf("权值=");
		cin >> quan;
		if (quan < 0) 
		{
			printf("权值负数无效。\n--------------------------\n");
			continue;
		}			
		G->arc[pointA][pointB] = quan;
		G->arc[pointB][pointA] = quan;
		printf("\n--------------------------\n");
	} while (pointA >= 0);

	//二维数组，按对角线将值“对称”
	for (int i = 0; i < vexCount; i++)
	{
		for (int j = 0; j < vexCount; j++)
		{			
			printf("   %d   ", G->arc[i][j]);
		}
		printf("\n");
	}
	//4.边数
	G->numEdges = 0;
	for (int i = 0; i < G->numVertexes; i++)
	{
		for (int j = 0; j < G->numVertexes; j++)
		{
			if (i != j && G->arc[i][j] != INF)
			{
				G->numEdges++;
			}
		}
	}
	printf("顶点个数=%d，边的个数=%d\n ", G->numVertexes, G->numEdges / 2);
}
//2. Prim 算法生成最小生成树 
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;  // min 为当前权值最小值
	int lowcost[MAXVEX];  /* 保存顶点间边的权值 */
	int adjvex[MAXVEX];   /* 保存相关顶点的下标，即下标与其值所连边为当前最小权值边 */
	lowcost[0] = 0;  /* 选取第一个顶点为起始点， 即 v0 加入树， lowcost的值为0，在这里就是此下标的顶点已经加入生成树 */
	adjvex[0] = 0;   /* 初始化第一个顶点下标为0 */
	for (i = 1; i < G.numVertexes; i++)  /* 循环除下标为 0 外的全部顶点 */
	{
		lowcost[i] = G.arc[0][i];  /* 将与 v0 顶点有边的权值存入数组 */
		adjvex[i] = 0;  /* 将其他所有顶点的值初始化为 v0 的下标 */
	}
	for (i = 1; i < G.numVertexes; i++)
	{
		min = INF;   /* 初始化最小权值为 无穷大 */
		j = 1, k = 0;
		while (j < G.numVertexes)  /* 循环全部顶点，寻找当前最小生成树顶点集合中最小权值的边 */
		{
			if (lowcost[j] != 0 && lowcost[j] < min)  /* 如果权值不为 0(即不在树中), 且权值小于 min */
			{
				min = lowcost[j];  /* 则让当前权值成为最小值 */
				k = j;             /* 将当前最小值的下标存入k */
			}
			j++;
		}
		lowcost[k] = 0;  /* 将当前顶点的权值设置为0, 表示此顶点已加入树的顶点集合 */
		printf("(%d, %d)", adjvex[k], k);  /* 打印当前顶点边中权值最小的边 */
		for (j = 1; j < G.numVertexes; j++)  /* 循环所有顶点 */
		{
			/* 如果下标为 k 的顶点边集中权值小于已存在的权值, 比如 (v0, v6)权值为INF, 而(v1, v6)权值为 16， 更新*/
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{
				lowcost[j] = G.arc[k][j];  /* 将较小的权值存入 lowcost 相应位置 */
				adjvex[j] = k;   /* 将下标为 k 的顶点存入 adjvex */
			}
		}
	}
}
//3.main函数（程序的入口，从此处执行）
int main()
{
	//1.构建邻接矩阵的二维数组
	MGraph G;
	CreateMGraphExample(&G);
	printf("-------------------------------\n");
	//2.最小生成树
	printf("最小生成树：\n");
	MiniSpanTree_Prim(G);

	//3.无实际意义，为了演示“保持输出窗口”
	int result = 0;
	cin >> result;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
