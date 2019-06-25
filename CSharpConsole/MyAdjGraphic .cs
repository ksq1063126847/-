using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsole
{
    public class MyAdjGraphic
    {
        static readonly int maxWeight = -1; //如果两个结点之间没有边，权值为-1；
        ArrayList vertices = new ArrayList();//存放结点的集合
        int[][] edges; //邻接矩阵的二维数组
        int numOfEdges; //边的数量

        public MyAdjGraphic(int n)
        {
            edges = new int[n][];
            for (int i = 0; i < n; i++)
            {
                edges[i] = new int[n];
                for (int j = 0; j < n; j++)
                {
                    if (i == j) //对角线上的元素为0
                    {
                        edges[i][j] = 0;
                    }
                    else
                    {
                        edges[i][j] = maxWeight;
                    }
                }
            }
            numOfEdges = 0;
        }

        //返回边的数量
        public int getNumOfEdges()
        {
            return this.numOfEdges;
        }

        //返回结点的数量
        public int getNumOfVertice()
        {
            return this.vertices.Count;
        }

        //返回结点的值
        public Object getValueOfVertice(int index)
        {
            return this.vertices[index];
        }

        //获得某条边的权值
        public int getWeightOfEdges(int v1, int v2)
        {
            if ((v1 < 0 || v1 >= vertices.Count) || (v2 < 0 || v2 >= vertices.Count))
            {
                throw new Exception("v1或者v2参数越界错误！");
            }
            return this.edges[v1][v2];
        }

        //插入结点
        public void insertVertice(Object obj)
        {
            this.vertices.Add(obj);
        }

        //插入带权值的边
        public void insertEdges(int v1, int v2, int weight)
        {
            if ((v1 < 0 || v1 >= vertices.Count) || (v2 < 0 || v2 >= vertices.Count))
            {
                throw new Exception("v1或者v2参数越界错误！");
            }
            this.edges[v1][v2] = weight;
            this.edges[v2][v1] = weight;
            this.numOfEdges++;
        }

        //删除某条边
        public void deleteEdges(int v1, int v2)
        {
            if ((v1 < 0 || v1 >= vertices.Count) || (v2 < 0 || v2 >= vertices.Count))
            {
                throw new Exception("v1或者v2参数越界错误！");
            }
            if (v1 == v2 || this.edges[v1][v2] == maxWeight)//自己到自己的边或者边不存在则不用删除。    
            {
                throw new Exception("边不存在！");
            }
            this.edges[v1][v2] = maxWeight;
            this.numOfEdges--;
        }

        //打印邻接矩阵
        public void print()
        {
            for (int i = 0; i < this.edges.Count(); i++)
            {
                for (int j = 0; j < this.edges[i].Count(); j++)
                {
                    System.Console.Write(edges[i][j] + " ");
                }
                System.Console.WriteLine();
            }
        }
    }

    //插入的边的类
    public class Weight
    {

        int row;  //起点
        int col;  //终点
        int weight; //权值

        public Weight(int row, int col, int weight)
        {
            this.row = row;
            this.col = col;
            this.weight = weight;
        }

        public static void createAdjGraphic(MyAdjGraphic g, Object[] vertices, int n, Weight[] weight, int e)
        {
            //初始化结点
            for (int i = 0; i < n; i++)
            {
                g.insertVertice(vertices[i]);
            }
            //初始化所有的边
            for (int i = 0; i < e; i++)
            {
                g.insertEdges(weight[i].row, weight[i].col, weight[i].weight);
            }
        }
    }
  
}
