// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "node.h"
using namespace std;

void showGraph(Node **graph,int w,int h);
void outputGraph(Node **graph,int w,int h, int ncc, string outfile);
int BFScoloring(Node **graph, int x, int y, char tcolor,char ncolor,int w, int h, int* count);
int BFS(Node **graph, int x, int y, char tcolor,int w, int h);
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
		
		int count = 0;
		char tcolor = graph[y*w+x]->getcolor();
		BFScoloring(graph, x, y, tcolor, ncolor, w, h, &count);
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
					BFS(graph, j, i, graph[i*w+j]->getcolor(), w, h);
					//cout<<j<<"_"<<i<<endl;
				}
			}
		
		}
		//cout<<ncc<<endl;
		outputGraph(graph, w, h, ncc, outfile);
		for(int i=0;i<w*h;i++)
		{delete graph[i];}
		delete[] graph;
    	myfile.close();
  	}else 
		cout << "Unable to open file"; 

  return 0;
}

int BFS(Node **graph, int x, int y, char tcolor,int w, int h)
{	
	int ind = y*w+x;
	//cout<<"("<<x<<","<<y<<") "<<ind<<"<"<<w*h<<endl;
	
	if(x<0||y<0||x>=w||y>=h){
			return 2;//out of bound
	}
	if(graph==NULL)
	{
		cout<<"1.NULL!"<<endl;
		exit(0);
	}
	if(graph[ind]==NULL)
	{
		cout<<"NULL!"<<endl;
		exit(0);
	}
	if(graph[ind]->getflag()==true)
			return 1;//already found
	if(graph[ind]->getcolor()==tcolor){
		graph[ind]->setflag(true);
	//up
		BFS(graph, x, y-1, tcolor, w, h);
	//down
		BFS(graph, x, y+1, tcolor, w, h);
	//left
		BFS(graph, x-1, y, tcolor, w, h);
	//right
		BFS(graph, x+1, y, tcolor, w, h);
	}
	else
	{	
		return 0;//not the color we are looking for
	}

}
int BFScoloring(Node **graph, int x, int y, char tcolor,char ncolor,int w, int h, int* c)
{
	int ind = y*w+x;
	//cout<<"("<<x<<","<<y<<") "<<*c<<endl;
	if(x<0||y<0||x>=w||y>=h)
			return 2;//out of bound
	if(graph[ind]->getflag()==true)
			return 1;//already found
	if(graph[ind]->getcolor()==tcolor){
		graph[ind]->setcolor(ncolor);
		graph[ind]->setflag(true);
		(*c)++;
	//up
		BFScoloring(graph, x, y-1, tcolor, ncolor, w, h, c);
	//down
		BFScoloring(graph, x, y+1, tcolor, ncolor, w, h, c);
	//left
		BFScoloring(graph, x-1, y, tcolor, ncolor, w, h, c);
	//right
		BFScoloring(graph, x+1, y, tcolor, ncolor, w, h, c);
	}
	else
	{	
		return 0;//not the color we are looking for
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
