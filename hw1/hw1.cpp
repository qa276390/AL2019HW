// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

void showGraph(char *graph,int w,int h);

int main (int argc, char* argv[]) {
  	string line;
  	int w = 0;
  	int h = 0;
  	char *graph;
  	stringstream ss;


	string infile = argv[1];
	int x = atoi(argv[2]);
	int y = atoi(argv[3]);
	char color = argv[4][0];
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
				graph = new char [w*h];	
			}
			else
			{
				ss.str("");
				ss.clear();
				ss<<line;
				while(ss>>tmp)
				{	//ss>>tmp;
					graph[idx] = tmp;
					idx++;	
				}
			}

    		cout << line << '\n';
		//cout<<"w="<<w<<", h="<<h<<endl;
    	}
		cout<<"w="<<w<<", h="<<h<<endl;
		showGraph(graph, w, h);

    	myfile.close();
  	}else 
		cout << "Unable to open file"; 

  return 0;
}

void showGraph(char *graph,int w,int h)
{
	for(int i=0;i<w*h;i++)
	{
		cout<<char(graph[i])<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}
}
