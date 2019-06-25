using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsole
{
    class Program
    {
        static void Main(string[] args)
        { 
            Object[] vertices = new Object[] { 'A', 'B', 'C', 'D', 'E' };//5个结点
            MyAdjGraphic graph = new MyAdjGraphic(vertices.Length);
            Weight[] weights = new Weight[] { new Weight(0, 1, 2), new Weight(0, 4, 3), new Weight(2, 1, 4), new Weight(1, 3, 5), new Weight(3, 2, 6) };//5条边           
            try
            {
                Weight.createAdjGraphic(graph, vertices, vertices.Length, weights, weights.Length);
                System.Console.WriteLine("--------该临街矩阵如下---------");
                graph.print();
                System.Console.WriteLine("结点的个数：" + graph.getNumOfVertice());
                System.Console.WriteLine("边的个数：" + graph.getNumOfEdges());
                graph.deleteEdges(0, 4);
                System.Console.WriteLine("--------删除之后---------");
                graph.print();
                System.Console.WriteLine("结点的个数：" + graph.getNumOfVertice());
                System.Console.WriteLine("边的个数：" + graph.getNumOfEdges());
                System.Console.ReadLine();
            }
            catch (Exception ex)
            {

            }
        }
    }
}
