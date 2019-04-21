// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stack>
#include "fornode.h"
using namespace std;

void showGraph(Node **graph,int w,int h);
void outputGraph(Node **graph,int w,int h, int ncc, string outfile);
int DFS(Node **graph, int x, int y, char ncolor,int w, int h);

int main (int argc, char* argv[]) {
  	string line;
  	int w = 0;
  	int h = 0;
  	Node **graph;
  	stringstream ss;


	string infile = argv[1];
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	char ncolor = argv[4][0];
	string outfile = argv[5];
  

	ifstream myfile(infile.c_str());

	if (myfile.is_open())
  	{
		int idx = 0;
		char tmp;
    	while ( getline (myfile,line) )
    	{
			if(	w==0 || h==0 )
			{
				ss.str("");
				ss.clear();
				ss<<line;
				ss>>w>>h;
				graph = new Node* [w*h];
				for(int i=0;i<w*h;i++)
				{graph[i] = new Node();}
			}
			else
			{
				ss.str("");
				ss.clear();
				ss<<line;
				while(ss>>tmp)
				{	//ss>>tmp;
					graph[idx]->setcolor(tmp);
					idx++;	
				}
			}

    		//cout << line << '\n';
		//cout<<"w="<<w<<", h="<<h<<endl;
    	}
		//cout<<"w="<<w<<", h="<<h<<endl;
		//showGraph(graph, w, h);
		//setting x,y
		for(int yi=0;yi<h;yi++)
		{
			for(int xi=0;xi<w;xi++){
				graph[yi*w+xi]->setxy(xi, yi);
			}
		
		}
		
		int count = 0;
		//char tcolor = graph[y*w+x]->getcolor();
		DFS(graph, x, y, ncolor, w, h);
		int ncc = 0;
		//cout<<endl;
		//showGraph(graph, w, h);
		
			
		for(int i=0;i<w*h;i++)
		{graph[i]->setflag(false);}
		
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++){
				if(graph[i*w+j]->getflag()==false)
				{
					ncc++;
					DFS(graph, j, i, '.', w, h);
					//cout<<j<<"_"<<i<<endl;
				}
			}
		
		}
		cout<<ncc<<endl;
		
		outputGraph(graph, w, h, ncc, outfile);
		for(int i=0;i<w*h;i++)
		{delete graph[i];}
		delete[] graph;
    	myfile.close();
  	}else 
		cout << "Unable to open file"; 

  return 0;
}

int DFS(Node **graph, int x, int y, char ncolor,int w, int h)
{
	stack<Node*> stk;
	Node *u;
	int ind = y*w+x;
	stk.push(graph[ind]);
	int xtmp, ytmp;
	char ctmp;

	while(!stk.empty())
	{
		u = stk.top();
		stk.pop();
		//cout<<u->getflag()<<endl;
		//if(u!=NULL&&u->getflag()==false)
		if(u->getflag()==false)
		{	u->setflag(true);

			//put u's neighbor into stack
			xtmp = u->getx();
			ytmp = u->gety();
			ctmp = u->getcolor();
			//cout<<"x="<<xtmp<<", y="<<ytmp<<endl;
			//cout<<<<endl;
			if(ncolor!='.')
				u->setcolor(ncolor);

			if(ytmp>0 && graph[(ytmp-1)*w+xtmp]->getcolor()==ctmp)
				stk.push(graph[(ytmp-1)*w+xtmp]);
			if(ytmp<h-1 && graph[(ytmp+1)*w+xtmp]->getcolor()==ctmp)
				stk.push(graph[(ytmp+1)*w+xtmp]);
			if(xtmp>0 && graph[(ytmp)*w+(xtmp-1)]->getcolor()==ctmp)//left
				stk.push(graph[(ytmp)*w+(xtmp-1)]);
			if(xtmp<w-1 && graph[(ytmp)*w+(xtmp+1)]->getcolor()==ctmp)//right
				stk.push(graph[(ytmp)*w+(xtmp+1)]);
		}
	}
}

void showGraph(Node **graph,int w,int h)
{
	for(int i=0;i<w*h;i++)
	{
		graph[i]->getflag();
		cout<<char(graph[i]->getcolor())<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}
}

void outputGraph(Node **graph,int w,int h, int ncc, string outfile)
{
	ofstream ofile(outfile.c_str());
	if(ofile.is_open())
	{
		ofile << w << ' ' << h <<"\n";
		for(int i=0;i<w*h;i++)
		{
			ofile<<char(graph[i]->getcolor())<<" ";
			if((i+1)%w==0)
				ofile<<"\n";
		}
		ofile<<ncc;
		ofile.close();
	}else cout<<"Unable to open file"<<endl;
}
