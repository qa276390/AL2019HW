#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <climits>
using namespace std;

// source, end, capacity, length
class Node{
public:
	int x;
	int y;
	int s;
	Node(){x=0;y=0;s=0;}
	Node(int xx, int yy, int ss){x=xx;y=yy;s=ss;}
};
struct Edge {int a, b, r, w;};

int en = 0;
int N = 0;

 
void AddEdge(int a, int b, int c, int w, vector<int>* adj, Edge* edge)
{
    edge[en] = (Edge){a, b, c, +w};
    adj[a].push_back(en++);
    edge[en] = (Edge){b, a, 0, -w};
    adj[b].push_back(en++);
}
 

int MinCostMaxstFlow(int s, int t, vector<int>* adj, Edge* edge)
{
	vector<int> p(N);
	vector<int> d(N);
	vector<int> index(N);
	vector<bool> inqueue(N);
    int flow = 0, cost = 0; 
 
    while (true)
    {
        for (int i=0; i<N; ++i) d[i] = 1e9;
        d[s] = 0;
        queue<int> Q;
        Q.push(s);
 		while(!Q.empty())
        {
            int a = Q.front(); Q.pop();
            inqueue[a] = false;
            for (int i=0; i<adj[a].size(); ++i)
            {
                Edge& e = edge[adj[a][i]];
                int b = e.b;
                if (e.r > 0 && d[a] + e.w < d[b])
                {
                    d[b] = d[a] + e.w;
                    p[b] = a;
                    index[b] = adj[a][i];
 
                    {
                        Q.push(b);
                        inqueue[b] = true;
                    }
                }
            }
        }
        if (d[t] == 1e9) break;
 
        int df = 1e9;
        for (int a = t; a != s; a = p[a])
        {
            int i = index[a];
            df = min(df, edge[i].r);
        }
        for (int a = t; a != s; a = p[a])
        {
            int i = index[a];
            edge[i].r -= df;
            edge[i^1].r += df;
        }
        flow += df;
        cost += df * d[t];
    }
 
	return cost;
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
			{	ss>>n_nodes;
				N = n_nodes + 2;
			}	
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
		vector<int> adj[N];
		int n_edges = n_source + n_sink + n_source*n_sink;
		Edge edge[n_edges*2];
		Node *Si;
		Node *Tj;
		int capa;
		for(int i = 0; i < n_source; i++)
		{
			Si = sourcevec[i];
			//from S to Si(i+1)
			AddEdge(0, i+1, Si->s, 0, adj, edge);
			//AddEdge(i+1, 0, 0, 0);
			//from Si to Tj
			for(int j = 0; j < n_sink; j++)
			{
				Tj = sinkvec[j];
				if(i==0)
				{
					AddEdge(j+1+(n_source), n_source+n_sink+1, -(Tj->s), 0, adj, edge);
					//AddEdge(n_source+n_sink+1,j+1+(n_source), 0, 0);
				}
				capa = (Si->s < (-Tj->s))? Si->s : -(Tj->s);
				//capa = INT_MAX;
				AddEdge(i+1, j+1+(n_source), capa, (abs((Si->x - Tj->x))+abs((Si->y - Tj->y))), adj, edge);
				//AddEdge(j+1+(n_source), i+1, 0, -(abs((Si->x - Tj->x))+abs((Si->y - Tj->y))));
			}
		}
		//cout<<"setting done"<<endl;
		int mincost = MinCostMaxstFlow(0, n_nodes+1, adj, edge);
		ofstream fout(outfile.c_str());
		fout<<mincost<<endl;
		for(int i = 0; i<N; i++)
		{
			vector<int> tmp = adj[i];
			while(!tmp.empty())
			{
				Edge x = edge[tmp.back()];
				tmp.pop_back();
				if(0<x.b && x.b<n_source+1 && x.a>n_source && x.a<N-1 && x.r!=0)
				{
					int from = x.b;
					int to = x.a;
		//			cout<<"from "<<x.b<<" to "<<x.a<<":";	
		//			cout<<setw(3)<<x.r<<" ";
		//			cout<<endl;

					fout<< Nodes[from]->x << " " << Nodes[from]->y <<" "<< Nodes[to]->x <<" "<< Nodes[to]->y << " " << x.r<<endl;

				}
			}
			//cout<<endl;
		}
	}
    return 0;
}
