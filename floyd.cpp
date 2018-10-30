#include"Floyd.h"


//构造函数
Graph_DG::Graph_DG(int vexnum, int edge) {
    //初始化顶点数和边数
    this->vexnum = vexnum;
    this->edge = edge;
    //为邻接矩阵开辟空间和赋初值
    arc = new double*[this->vexnum];
    dis = new double*[this->vexnum];
    path = new int*[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new double[this->vexnum];
        dis[i] = new double[this->vexnum];
        path[i] = new int[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //邻接矩阵初始化为无穷大
            arc[i][k] = INT_MAX;
        }
    }
}

//析构函数
Graph_DG::~Graph_DG() {
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
        delete this->dis[i];
        delete this->path[i];
    }
    delete dis;
    delete arc;
    delete path;
}

void Graph_DG::printMatrix() {
    cout << "图的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
                       //开始打印
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "∞" << " ";
            else
                cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::Floyd() {
    int row = 0;
    int col = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = 0; col < this->vexnum; col++) {
            //把矩阵D初始化为邻接矩阵的值
            this->dis[row][col] = this->arc[row][col];
            //矩阵P的初值则为各个边的终点顶点的下标
            this->path[row][col] = col;
        }
    }
    //三重循环，用于计算每个点对的最短路径
    int temp = 0;
    double select = 0;
    for (temp = 0; temp < this->vexnum; temp++) {
        for (row = 0; row < this->vexnum; row++) {
            for (col = 0; col < this->vexnum; col++) {
                //为了防止溢出，所以需要引入一个select值
                select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
                if (this->dis[row][col] > select) {
                    //更新我们的D矩阵
                    this->dis[row][col] = select;
                    //更新我们的P矩阵
                    this->path[row][col] = this->path[row][temp];
                }
            }
        }
    }


}

void Graph_DG::generateRoute(int start,int end) {
    int row = start-1;
    int col = end-1;
    int temp = 0;
    routeId.push_back(row+1);
    temp = this->path[row][col];
    //循环输出途径的每条路径。
    while (temp != col)
    {
        routeId.push_back(temp + 1);
        temp = this->path[temp][col];
    }
    routeId.push_back(col + 1);
}

void Graph_DG::printRoute() {
    cout << "各个顶点对的最短路径：" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = 0; row < this->vexnum; row++)
    {
        for (col = row + 1; col < this->vexnum; col++)
        {
            cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col+1) << " weight: "
                << this->dis[row][col] << " path: " << " v" << to_string(row + 1);
            temp = path[row][col];
            //循环输出途径的每条路径。
            while (temp != col)
            {
                cout << "-->" << "v" << to_string(temp + 1);
                temp = path[temp][col];
            }
            cout << "-->" << "v" << to_string(col + 1) << endl;
         }
    cout << endl;
    }
}
