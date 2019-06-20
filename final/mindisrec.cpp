// Boost.Polygon library polygon_set_data_test.cpp file

//          Copyright Andrii Sydorchuk 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <boost/core/lightweight_test.hpp>
#include <boost/polygon/polygon.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace boost::polygon;
using namespace boost::polygon::operators;

typedef point_data<int> point_type;
typedef polygon_90_with_holes_data<int> polygon_type;
typedef polygon_90_set_data<int> polygon_set_type;

class Concave{
public:
	int fromx;
	int fromy;
	int tox;
	int toy;
	Concave(){fromx=0;fromy=0;tox=0;toy=0;}
	Concave(int fx, int fy, int tx, int ty){fromx=fx;fromy=fy;tox=tx;toy=ty;}

}
class Edge{
public:
	int flow;
	int capacity;
	Edge(){flow=0;capacity=0;}
	Edge(int f, int c){flow=f;capacity=c;}

};
class Node{
public:
	point_type* A;
	point_type* B;
	int s;
	Node(){A=NULL;B=NULL;s=0;}
	Node(point_type* a, point_type* b, int ss){A=a;B=b;s=ss;}
};
void checkforDiagonal(std::vector<Concave*>* concavePty, std::vector<point_type*>* concaveVec,std::vector<Node*>* HorDiagVec,std::vector<Node*>* VerDiagVec)
{
	point_type *pt = new point_type(pit.x(), pit.y());
	if((*concaveVec).empty())
	{
		(*concaveVec).push_back(pt);
	}else{
		int minhorlen = 1e9;
		int minverlen = 1e9;
		int minhoridx = -1;
		int minveridx = -1;
		int horlen, verlen;
		for(int i=0; i<(*concaveVec).size()-1;i++)
		{
			if(pit.x()==(*concaveVec)[i]->x())
			{
				horlen = abs(pit.y() - (*concaveVec)[i]->y());
				if(horlen<minhorlen)
				{minhorlen=horlen;minhoridx=i;}
			}
			else if(pit.y()==(*concaveVec)[i]->y())
			{	
				verlen = abs(pit.x() - (*concaveVec)[i]->x());
				if(verlen<minverlen)
				{minverlen=verlen;minveridx=i;}
			}
		}
		if(minhoridx!=-1)
			(*HorDiagVec).push_back(new Node(pt, (*concaveVec)[minhoridx], 1));
		if(minveridx!=-1)
			(*VerDiagVec).push_back(new Node(pt, (*concaveVec)[minveridx], 1));
	
		(*concaveVec).push_back(pt);
	}

}

void polygon_set_data_test3()
{
	bool vertical = true;


	std::vector< rectangle_data<int> > rects;

    std::vector<point_type> data;
    data.push_back(point_type(0,0));
    data.push_back(point_type(6,0));
    data.push_back(point_type(6,4));
    data.push_back(point_type(4,4));
    data.push_back(point_type(4,6));
    data.push_back(point_type(0,6));

    
	std::vector<point_type> data1;
    data1.push_back(point_type(4,2));
    data1.push_back(point_type(4,1));
    data1.push_back(point_type(10,1));
    data1.push_back(point_type(10,2));

	std::vector<point_type> data2;
    data2.push_back(point_type(1,1));
    data2.push_back(point_type(1,2));
    data2.push_back(point_type(2,2));
    data2.push_back(point_type(2,1));

    polygon_type polygon;
	polygon.set(data.begin(), data.end());
    polygon_set_type pset;
    pset += polygon;

    
	polygon_type polygon1;
	polygon1.set(data1.begin(), data1.end());
    polygon_set_type pset1;
    pset1 += polygon1;
    
	polygon_type polygon2;
	polygon2.set(data2.begin(), data2.end());
    polygon_set_type pset2;
    pset2 += polygon2;

    polygon_set_type allpset;
	//allpset = pset + pset1;
	allpset = pset - pset2 - pset1;
	if(vertical){
		get_rectangles(rects, allpset, VERTICAL);
		//const rectangle_data<int>& r = rects[0];
    	BOOST_TEST_EQ(31.0, area(allpset));
   		BOOST_TEST_EQ(31.0, area(rects[0]));
    	BOOST_TEST_EQ(31.0, area(rects[1]));
    	BOOST_TEST_EQ(31.0, area(rects[2]));
	}


	/*************** showing result ********************/
	std::vector< polygon_type > polyresults;
	polygon_type::iterator_holes_type ith;
	polygon_90_data<int>::iterator_type it;
	
	allpset.get(polyresults);
	//show holes data
	for(int i = 0; i < polyresults.size(); ++i)
	{
		std::cout<<"i="<<i<<std::endl;
		for(ith=polyresults[i].begin_holes();ith!=polyresults[i].end_holes();ith++)
		{	
			for(it=ith->begin();it!=ith->end();it++)
			{	
				//std::cout<<(*it).x()<<" ";
				//std::cout<<(*it).y()<<std::endl;
			}
		}
	}
	//show polygon data
	for(int i = 0; i < polyresults.size(); ++i)
	{
		std::cout<<"i="<<i<<std::endl;
		for(it=polyresults[i].begin();it!=polyresults[i].end();it++)
		{
			//std::cout<<(*it).x()<<" ";
			//std::cout<<(*it).y()<<std::endl;
		}
	}

	/**************************************************/

	std::vector<point_type* > concaveVec;
	std::vector<Concave* > concavePty;
	std::vector<Node*> HorDiagVec;
	std::vector<Node*> VerDiagVec;

	std::vector< polygon_type > polys;
	polygon_type::iterator_holes_type itho;
	polygon_90_data<int>::iterator_type pit;
	
	allpset.get(polys);

	int lastx = 1e9;
	int lasty = 1e9;

	int nextx;
	int nexty;

	int x = 1e9;
	int y = 1e9;

	int lastvx;
	int lastvy;

	int vx;
	int vy;

	int outpd;

	point_type current_point;

	bool concave = false;
	for(int i = 0; i < polys.size(); ++i)
	{
			
		std::cout<<"i="<<i<<std::endl;
		//holes
		for(itho=polys[i].begin_holes();itho!=polys[i].end_holes();itho++)
		{	
			for(pit=itho->begin();pit!=itho->end();pit++)
			{	
				std::cout<<(*pit).x()<<" ";
				std::cout<<(*pit).y()<<std::endl;
				concaveVec.push_back(new point_type((*pit).x(), (*pit).y()));
				//concaveXfrom.push_back(
				//checkforDiagonal((*pit), &concaveVec, &HorDiagVec, &VerDiagVec, true);
			}
		}
		//poly data
		pit = polys[i].begin();
		int idx = 0;
		
		std::cout<<polys[i].size()<<std::endl;
		while(idx <= size(polys[i])+1)
		{

			nextx = (*(pit)).x();
			nexty = (*(pit)).y();
			vx = nextx - x;
			vy = nexty - y;
			if(idx>=2){
				if(x>1e8||y>1e8||lastx>1e8||lasty>1e8)
					std::cout<<"MISTAKE!!!!!!!!!"<<std::endl;
				outpd = lastvx*vy-lastvy*vx;
				concave = outpd<0? true : false;
				if(concave){
					std::cout<<"concave!"<<std::endl;
					std::cout<<(current_point).x()<<" ";
					std::cout<<(current_point).y()<<std::endl;
					concaveVec.push_back(new point_type(current_point.x(), current_point.y()));
					concavePty.push_back(new Concave(lastxvx, lastvy, vx, vy);
					//checkforDiagonal((current_point), &concaveVec, &HorDiagVec, &VerDiagVec, false);
				}
			}
			
			lastvx = vx;
			lastvy = vy;
			lastx = x;
			lasty = y;
			x = nextx;
			y = nexty;
			current_point = (*pit);
			idx++;
			pit++;
		}

	}
	
	checkforDiagonal(&concavePty, &concaveVec, &HorDiagVec, &VerDiagVec);

	std::cout<<"Size of concave:"<<concaveVec.size()<<std::endl;
	std::cout<<"Size of Vertiacal DiaVec:"<<VerDiagVec.size()<<std::endl;
	std::cout<<"Size of Horizontal DiaVec:"<<HorDiagVec.size()<<std::endl;
	for(int i=0;i<HorDiagVec.size();i++)
	{	
		std::cout<<HorDiagVec[i]->A->x()<<" ";
		std::cout<<HorDiagVec[i]->A->y()<<" ,";
		std::cout<<HorDiagVec[i]->B->x()<<" ";
		std::cout<<HorDiagVec[i]->B->y()<<" "<<std::endl;
	}
	for(int i=0;i<VerDiagVec.size();i++)
	{	
		std::cout<<VerDiagVec[i]->A->x()<<" ";
		std::cout<<VerDiagVec[i]->A->y()<<" ,";
		std::cout<<VerDiagVec[i]->B->x()<<" ";
		std::cout<<VerDiagVec[i]->B->y()<<" "<<std::endl;
	}

}

int main()
{
    polygon_set_data_test3();
    return boost::report_errors();
}
