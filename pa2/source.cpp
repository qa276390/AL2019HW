// C++ code
#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

class Edge{
public:
	int length;
	int flow;
	int capacity;
	Edge(){length=1e9;flow=0;capacity=0;}
	Edge(int l, int f, int c){length=l;flow=f;capacity=c;}

};
class Node{
public:
	int x;
	int y;
	int s;
	Node(){x=0;y=0;s=0;}
	Node(int xx, int yy, int ss){x=xx;y=yy;s=ss;}
};
class Graph_FlowNetWorks{
private:
    int num_vertex;
    std::vector<std::vector<Edge *> > AdjMatrix;
public:
    Graph_FlowNetWorks():num_vertex(0){};
    Graph_FlowNetWorks(int n);
    void AddEdge(int from, int to, int capacity, int length);

    void FordFulkerson(int source, int termination);
    bool BFSfindExistingPath(std::vector<std::vector<Edge*> > graphResidual, 
                             int *predecessor, int source, int termination);
    bool findNegativeCicle(std::vector<std::vector<Edge*> > graphResidual, 
                             int *predecessor);
	bool getNegativeCicle(int *predecessor, int x);
    int MinCapacity(std::vector<std::vector<Edge*> > graphResidual, 
                    int *predecessor, int termination);
	void ShowAdjMat(std::vector<std::vector<Edge*> > );

};
void Graph_FlowNetWorks::ShowAdjMat(std::vector<std::vector<Edge*> > graph){
	cout<<"# of nodes="<<num_vertex<<endl;
	
    for (int i = -1; i < num_vertex; i++){
		cout<<setw(3)<<i<<" ";
		for(int j = 0; j < num_vertex; j++)
		{
			if(i==-1)
				cout<<setw(3)<<j<<" ";
			else
				cout<<graph[i][j]->flow<<"/"<<graph[i][j]->capacity<<" ";
		
		}
		cout<<endl;
   	} 
	for (int i = -1; i < num_vertex; i++){
		cout<<setw(3)<<i<<" ";
		for(int j = 0; j < num_vertex; j++)
		{	
			if(i==-1)
				cout<<setw(3)<<j<<" ";
			else if(graph[i][j]->length==1e9)
				cout<<" -  ";
			else
				cout<<setw(3)<<graph[i][j]->length<<" ";
		}cout<<endl;
	}

}
Graph_FlowNetWorks::Graph_FlowNetWorks(int n):num_vertex(n){
    // constructor
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++){
        AdjMatrix[i].resize(num_vertex);
		for(int j = 0; j < num_vertex; j++)
			AdjMatrix[i][j] = new Edge();
	}
}

bool Graph_FlowNetWorks::getNegativeCicle(int *predecessor, int x){

	bool visit[num_vertex+1];
	memset(visit, false, sizeof(visit));
	for(; !visit[x]; x=predecessor[x])
		visit[x] = true;
	cout<<"Negative Cicle:"<<endl;
	cout<<x;
	for(int a = predecessor[x]; a!=x; a=predecessor[a])
		cout<<"<-"<<a;
	cout<<endl;
	
	cout<<x;
	int a = predecessor[x]; 
	for(int i = 0;  i < 10; i++)
	{	cout<<"<-"<<a;
		a = predecessor[a];
	}cout<<endl;
}

bool Graph_FlowNetWorks::findNegativeCicle(std::vector<std::vector<Edge*> > graph, int *predecessor){
    
    std::vector<std::vector<Edge *> > extgraph;
	extgraph.resize(num_vertex+1);
    for (int i = 0; i < num_vertex+1; i++){
        extgraph[i].resize(num_vertex+1);
		for(int j = 0; j < num_vertex+1; j++)
			if(i==num_vertex)
			{
				extgraph[i][j] = new Edge(0, 0, 1);	
			}else if(j==num_vertex){
				extgraph[i][j] = new Edge(0, 0, 0);
			}
			else{
				extgraph[i][j] = graph[i][j];}
	}
	cout<<"***Redisual After Extension***"<<endl;
	ShowAdjMat(extgraph);
    int distance[num_vertex+1];
	int n[num_vertex+1];
	bool inqueue[num_vertex+1];

    for (int i = 0; i < num_vertex+1; i++){
        distance[i] = 1e9;     
        predecessor[i] = -1;
		n[i] = 0;
		inqueue[i] = false;
    }
	int source = num_vertex;
	distance[source] = 0;
	predecessor[source] = source;
	n[source] = 0;

    std::queue<int> queue;
    // BFS 從 s 開始, 也可以規定s一律訂成vertex(0)
    queue.push(source);
    cout<<"start"<<endl;
	while(!queue.empty()){
        int exploring = queue.front();
		//cout<<exploring<<endl;
		queue.pop();
		inqueue[exploring] = false;
		if(inqueue[predecessor[exploring]]){continue;}

        for (int j = 0; j < num_vertex+1; ++j) {
            if (extgraph[exploring][j]->length!=1e9 && extgraph[exploring][j]->capacity>0 && distance[exploring]+extgraph[exploring][j]->length < distance[j]) {
            	distance[j] = distance[exploring] + extgraph[exploring][j]->length;
				predecessor[j] = exploring;
				n[j] = n[exploring] + 1;

				if(n[j]>=num_vertex+1)
				{
					cout<<n[j]<<endl;
					getNegativeCicle(predecessor, j);
					return true;
				}
				if(!inqueue[j])
				{
					queue.push(j);
					inqueue[j] = true;
				}
			}
        }
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
            if (graph[exploring][j]->capacity!=0 && visited[j]==0) {
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
        if (graph[predecessor[idx]][idx]->capacity!=0 && graph[predecessor[idx]][idx]->capacity < min) {
            min = graph[predecessor[idx]][idx]->capacity;
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
			graphResidual[i][j] = new Edge(e->length, 0, e->capacity);
		}
	}
    int maxflow = 0;                                           
    int predecessor[num_vertex];
    int predecessor2[num_vertex];
	//ShowAdjMat(AdjMatrix);

    // BFS finds augmenting path,
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        int mincapacity = MinCapacity(graphResidual, predecessor, termination);
        maxflow = maxflow + mincapacity;
        for (int Y = termination; Y != source; Y = predecessor[Y]){
            // 更新 residual graph
            int X = predecessor[Y];
            graphResidual[X][Y]->capacity -= mincapacity;
            graphResidual[Y][X]->capacity += mincapacity;
			AdjMatrix[X][Y]->flow += mincapacity;
        }
    }
	cout<<"***Redisual After Ford-Fulkerson***"<<endl;
	ShowAdjMat(graphResidual);
    std::cout << "Possible Maximum Flow:"  << maxflow << std::endl;
	ShowAdjMat(AdjMatrix);

	while(findNegativeCicle(graphResidual, predecessor2)){
		//cout<<"negative cicle found!"<<endl;

		break;
	
	}
}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity, int length){

    AdjMatrix[from][to]->capacity = capacity;
    AdjMatrix[from][to]->length = length;
}

int main(int argc, char* argv[]){

	if(argc!=3)
	{	cout<<"please add 2 parameters!"<<endl;
		return 0;		
	}
	string infile = argv[1];
	string outfile = argv[2];


	ifstream myfile(infile.c_str());
	int x, y, s;
	int n_nodes = 0;
	int n_source = 0;
	int n_sink = 0;
	vector<Node*> sourcevec;
	vector<Node*> sinkvec;
	string line;	
  	stringstream ss;
	if (myfile.is_open())
  	{
		
    	while ( getline (myfile,line) )
    	{
			ss.str("");
			ss.clear();
			ss<<line;
			if(n_nodes==0)
				ss>>n_nodes;
			else{
				ss>>x>>y>>s;
				if(s>0)
				{//source
					sourcevec.push_back(new Node(x, y, s));
					n_source++;
				}else{
				//sink
					sinkvec.push_back(new Node(x, y, s));
					n_sink++;
				}
			}
    	}
		int n_edges = n_source + n_sink + n_source*n_sink;
		Graph_FlowNetWorks graph(n_nodes+2);
		Node *Si;
		Node *Tj;
		for(int i = 0; i < n_source; i++)
		{
			Si = sourcevec[i];
			//from S to Si(i+1)
			graph.AddEdge(0, i+1, Si->s, 0);
			graph.AddEdge(i+1, 0, 0, 0);
			//from Si to Tj
			for(int j = 0; j < n_sink; j++)
			{
				Tj = sinkvec[j];
				if(i==0)
				{
					graph.AddEdge(j+1+(n_source), n_source+n_sink+1, -(Tj->s), 0);
					graph.AddEdge(n_source+n_sink+1,j+1+(n_source), 0, 0);
				}
				graph.AddEdge(i+1, j+1+(n_source), Si->s, sqrt(pow((Si->x - Tj->x),2)+pow((Si->y - Tj->y),2)));
				graph.AddEdge(j+1+(n_source), i+1, 0, -sqrt(pow((Si->x - Tj->x),2)+pow((Si->y - Tj->y),2)));
			}
		}
		graph.FordFulkerson(0, n_nodes+1);    // 指定source為vertex(0), termination為vertex(5)
	}
    return 0;
}
