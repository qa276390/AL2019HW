// C++ code
#include <iostream>
#include <vector>
#include <queue>

class Edge{
public:
	int length;
	int flow;
	int capacity;
	Edge(){length=0;flow=0;capacity=0;}
	Edge(int l, int f, int c){length=l;flow=f;capacity=c;}

};
class Graph_FlowNetWorks{
private:
    int num_vertex;
    std::vector<std::vector<Edge *> > AdjMatrix;
public:
    Graph_FlowNetWorks():num_vertex(0){};
    Graph_FlowNetWorks(int n);
    void AddEdge(int from, int to, int capacity);

    void FordFulkerson(int source, int termination);
    bool BFSfindExistingPath(std::vector<std::vector<Edge*> > graphResidual, 
                             int *predecessor, int source, int termination);
    int MinCapacity(std::vector<std::vector<Edge*> > graphResidual, 
                    int *predecessor, int termination);

};
Graph_FlowNetWorks::Graph_FlowNetWorks(int n):num_vertex(n){
    // constructor
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++){
        AdjMatrix[i].resize(num_vertex);
		for(int j = 0; j < num_vertex; j++)
			AdjMatrix[i][j] = new Edge();
	}
}

bool Graph_FlowNetWorks::BFSfindExistingPath(std::vector<std::vector<Edge*> > graph, int *predecessor, int s, int t){
    int visited[num_vertex];

    for (int i = 0; i < num_vertex; i++){
        visited[i] = 0;     // 0 表示還沒有被找到
        predecessor[i] = -1;
    }

    std::queue<int> queue;
    // BFS 從 s 開始, 也可以規定s一律訂成vertex(0)
    queue.push(s);
    visited[s] = 1;
	while(!queue.empty()){
        int exploring = queue.front();
        for (int j = 0; j < num_vertex; j++) {
            if (graph[exploring][j]->flow!=0 && visited[j]==0) {
                queue.push(j);
                visited[j] = 1;
                predecessor[j] = exploring;
            }
        }
        queue.pop();
    }
    return (visited[t] == 1);   // 若t有被visited, 表示有path從s到t
                                // 也可以用 if (predecessor[t] != -1) 判斷
}

int Graph_FlowNetWorks::MinCapacity(std::vector<std::vector<Edge*> > graph, 
                                    int *predecessor, int t){
    int min = 100;      // 確保min會更新, 假設graph上的capacity都小於100

    // 用predecessor[idx] 和 idx 表示一條edge
    // 找到在從s到t的path上, capacity最小的值, 存入min
    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]){
        if (graph[predecessor[idx]][idx]->flow!=0 && graph[predecessor[idx]][idx]->flow < min) {
            min = graph[predecessor[idx]][idx]->flow;
        }
    }
    return min;
}

void Graph_FlowNetWorks::FordFulkerson(int source, int termination){

    // residual networks的初始狀態等於AdjMatrix, 見圖五(a)
    Edge* e;
	std::vector<std::vector<Edge*> > graphResidual(AdjMatrix);
    for (int i = 0; i < num_vertex; i++){
		for(int j = 0; j < num_vertex; j++){
			e = AdjMatrix[i][j];
			graphResidual[i][j] = new Edge(e->length, e->capacity, e->capacity);
		}
	}
    int maxflow = 0;                                           
    int predecessor[num_vertex];

    // BFS finds augmenting path,
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        int mincapacity = MinCapacity(graphResidual, predecessor, termination);
        maxflow = maxflow + mincapacity;
        for (int Y = termination; Y != source; Y = predecessor[Y]){
            // 更新 residual graph
            int X = predecessor[Y];
            graphResidual[X][Y]->flow -= mincapacity;
            graphResidual[Y][X]->flow += mincapacity;
			AdjMatrix[X][Y]->flow += mincapacity;
        }
    }
    std::cout << "Possible Maximum Flow:"  << maxflow << std::endl;
}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity){

    AdjMatrix[from][to]->capacity = capacity;
}

int main(){
    Graph_FlowNetWorks g11(6);

    g11.AddEdge(0, 1, 9);g11.AddEdge(0, 3, 9);
    g11.AddEdge(1, 2, 3);g11.AddEdge(1, 3, 8);
    g11.AddEdge(2, 4, 2);g11.AddEdge(2, 5, 9);
    g11.AddEdge(3, 2, 7);g11.AddEdge(3, 4, 7);
    g11.AddEdge(4, 2, 4);g11.AddEdge(4, 5, 8);

    g11.FordFulkerson(0, 5);    // 指定source為vertex(0), termination為vertex(5)
    return 0;
}
