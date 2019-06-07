// C++ code
#include <time.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stack>
#include <cstdlib>
using namespace std;
clock_t start;
clock_t end;

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
    int findNegativeCicle(std::vector<std::vector<Edge*> > graphResidual, 
                             int *predecessor);
	bool getNegativeCicle(int *predecessor, int x);
    int MinCapacity(std::vector<std::vector<Edge*> > graphResidual, 
                    int *predecessor, int termination);
	void ShowAdjMat(std::vector<std::vector<Edge*> > );
	void RefreshFlow(std::vector<std::vector<Edge*> > graph, std::vector<std::vector<Edge*> > graphResidual, stack<int> order, int mincapacity);
	vector<vector<Edge *> > getAdjMatrix(){return AdjMatrix;}
	void outputResult(std::vector<Node*> Nodes, string outfile);
};
void Graph_FlowNetWorks::outputResult(std::vector<Node*> Nodes, string outfile){
	float wireArea = 0.0;
	int totalflow = 0;
	Node* from;
	Node* to;
	int f;
    ofstream fout(outfile.c_str());

	if(!fout)
	{
		cout<<"Fail to open file"<<endl;
		exit(0);
	}
	for (int i = 0; i < num_vertex; i++){
		for(int j = 0; j < num_vertex; j++)
		{	wireArea += (AdjMatrix[i][j]->flow * abs(AdjMatrix[i][j]->length));
			if(i!=0 && i!=num_vertex-1 && j!=0 && j!=num_vertex-1)
				totalflow += AdjMatrix[i][j]->flow;
		}}
	fout<<wireArea<<endl;
	for (int i = 1; i < num_vertex-1; i++){
		for(int j = 1; j < num_vertex-1; j++)
		{
			if((f=AdjMatrix[i][j]->flow)>0)
			{
				from  = Nodes[i];
				to = Nodes[j];
				fout<<from->x<<" "<<from->y<<" "<<to->x<<" "<<to->y<<" "<<f<<endl;	
			}
		}
   	}
	fout.close();
	//cout<<"Total Flow="<<totalflow<<endl;
}
void Graph_FlowNetWorks::ShowAdjMat(std::vector<std::vector<Edge*> > graph){
	//cout<<"# of nodes="<<num_vertex<<endl;
	float wireArea = 0.0;
    for (int i = -1; i < num_vertex; i++){
		cout<<setw(3)<<i<<" ";
		for(int j = 0; j < num_vertex; j++)
		{
			if(i==-1)
				cout<<setw(3)<<j<<" ";
			else
			{	cout<<graph[i][j]->flow<<"/"<<graph[i][j]->capacity<<" ";
				wireArea += (graph[i][j]->flow * abs(graph[i][j]->length));
			}
		
		}
		cout<<endl;
   	}/* 
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
	}*/
	cout<<"Total Wire Area  = "<<wireArea<<endl;
	

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

bool Graph_FlowNetWorks::getNegativeCicle(int *predecessor, int x ){

	
	bool visit[num_vertex+1];
	memset(visit, false, sizeof(visit));
	for(; !visit[x]; x=predecessor[x])
		visit[x] = true;
	//cout<<x;
	for(int a = predecessor[x]; a!=x; a=predecessor[a])
	{	//cout<<"<-"<<a;
	}
	//cout<<endl;	
}

int Graph_FlowNetWorks::findNegativeCicle(std::vector<std::vector<Edge*> > graph, int *predecessor){
    
    std::vector<std::vector<Edge *> > extgraph;
	extgraph.resize(num_vertex+1);
    for (int i = 0; i < num_vertex+1; i++){
        extgraph[i].resize(num_vertex+1);
		for(int j = 0; j < num_vertex+1; j++)
			if(i==num_vertex)
			{

				extgraph[i][j] = new Edge(1e9, 0, 0);
			}else if(j==num_vertex){
				//extgraph[i][j] = new Edge(1e9, 0, 0);
				if(i==0 || i==num_vertex-1)
					extgraph[i][j] = new Edge(1e9, 0, 0);
				else
					extgraph[i][j] = new Edge(0, 0, 1);	
				
			}
			else{
				extgraph[i][j] = graph[i][j];}
	}
	//cout<<"***Redisual After Extension***"<<endl;
	//ShowAdjMat(extgraph);
    int distance[num_vertex+1];
	int n[num_vertex+1];
	bool inqueue[num_vertex+1];

    for (int i = 0; i < num_vertex+1; i++){
        distance[i] = 1e9;     
        predecessor[i] = -1;
		n[i] = 0;
		inqueue[i] = false;
    }
	int source = 1;
	distance[source] = 0;
	predecessor[source] = source;
	n[source] = 0;

    std::queue<int> queue;
    queue.push(source);
    //cout<<"start"<<endl;
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
					//cout<<n[j]<<endl;
					//cout<<j<<endl;
					//getNegativeCicle(predecessor, j);
					return j;
				}
				if(!inqueue[j])
				{
					queue.push(j);
					inqueue[j] = true;
				}
			}
        }
    }
	return -1;
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
    int min = 1e9;      // 確保min會更新, 假設graph上的capacity都小於100

    // 用predecessor[idx] 和 idx 表示一條edge
    // 找到在從s到t的path上, capacity最小的值, 存入min
	int idx = t;
	while(predecessor[idx]!=-1)
	{

        if (graph[predecessor[idx]][idx]->capacity!=0 && graph[predecessor[idx]][idx]->capacity < min) {
            min = graph[predecessor[idx]][idx]->capacity;
        }
	//	cout<<" "<<idx<<"/"<<graph[predecessor[idx]][idx]->capacity<<" ";
		if(predecessor[idx] == t)
			break;
		idx = predecessor[idx];

	}
	//cout<<endl;
	/*
    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]){
        if (graph[predecessor[idx]][idx]->capacity!=0 && graph[predecessor[idx]][idx]->capacity < min) {
            min = graph[predecessor[idx]][idx]->capacity;
        }
    }*/
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
	//cout<<"***Redisual After Ford-Fulkerson***"<<endl;
	//ShowAdjMat(graphResidual);
    //std::cout << "Possible Maximum Flow:"  << maxflow << std::endl;
	//ShowAdjMat(AdjMatrix);
	
	int x;

	while((x = findNegativeCicle(graphResidual, predecessor2))>=0){
		//cout<<"negative cicle found!"<<endl;
		stack<int> pred_stack;
		bool visit[num_vertex+1];
		memset(visit, false, sizeof(visit));
		for(; !visit[x]; x=predecessor2[x])
			visit[x] = true;

        int mincapacity = MinCapacity(graphResidual, predecessor2, x);
		//cout<<"min capacity="<<mincapacity<<endl;
		//cout<<x;
		pred_stack.push(x);
		for(int a = predecessor2[x]; a!=x; a=predecessor2[a])
		{	
			//cout<<"<-"<<a;
			pred_stack.push(a);
		}
		pred_stack.push(x);
		//cout<<endl;

		RefreshFlow(AdjMatrix, graphResidual, pred_stack, mincapacity);
		//if(pred_stack.size()>10)
		//	break;
		//break;
    	//std::cout << "***AdjMatrix***" << std::endl;
		//ShowAdjMat(AdjMatrix);
		if((clock()-start)/CLOCKS_PER_SEC>840)
		{
			cout<<"Time's up"<<endl;
			break;}
	
	}
	/*
	cout<<"***Redisual After ALL***"<<endl;
	ShowAdjMat(graphResidual);
    std::cout << "***AdjMatrix***" << std::endl;
	ShowAdjMat(AdjMatrix);
	*/
	//ComputeWireArea()
}

void Graph_FlowNetWorks::RefreshFlow(std::vector<std::vector<Edge*> > graph, std::vector<std::vector<Edge*> > graphResidual, stack<int> order, int mincapacity)
{
	int from = order.top();
	order.pop();
	int to;
	while(!order.empty())
	{

		to = order.top();
		//cout<<"from:"<<from<<" to:"<<to;
		order.pop();
		if(graph[from][to]->length<0)
		{	
				//cout<<"("<<graph[to][from]->flow<<")";
				graph[to][from]->flow -= mincapacity;
				//cout<<"/("<<graph[to][from]->flow<<")";
				//cout<<" is reverse.";
		}else
		{	//cout<<"("<<graph[from][to]->flow<<")";
			graph[from][to]->flow += mincapacity;
			//cout<<"/("<<graph[from][to]->flow<<")";
		}
		graphResidual[from][to]->capacity -= mincapacity;
		graphResidual[to][from]->capacity += mincapacity;

		from = to;
		//cout<<endl;
	}

}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity, int length){

    AdjMatrix[from][to]->capacity = capacity;
    AdjMatrix[from][to]->length = length;
}

int main(int argc, char* argv[]){
	start = clock();
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
		vector<Node*> Nodes;
		Nodes.push_back(NULL);
		for(int i = 1; i < n_nodes+1; i++)
		{
			if(i<=n_source)
				Nodes.push_back(sourcevec[i-1]);
			else
				Nodes.push_back(sinkvec[i-1-n_source]);
		}
		int n_edges = n_source + n_sink + n_source*n_sink;
		Graph_FlowNetWorks graph(n_nodes+2);
		Node *Si;
		Node *Tj;
		int capa;
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
				capa = (Si->s < (-Tj->s))? Si->s : -(Tj->s);
				graph.AddEdge(i+1, j+1+(n_source), capa, (abs((Si->x - Tj->x))+abs((Si->y - Tj->y))));
				graph.AddEdge(j+1+(n_source), i+1, 0, -(abs((Si->x - Tj->x))+abs((Si->y - Tj->y))));
			}
		}
		graph.FordFulkerson(0, n_nodes+1);  
		
		graph.outputResult(Nodes, outfile);
			

	}
    return 0;
}
