// Boost.Polygon library polygon_set_data_test.cpp file

//          Copyright Andrii Sydorchuk 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <boost/core/lightweight_test.hpp>
#include <boost/polygon/polygon.hpp>
#include <vector>
#include <iostream>

using namespace boost::polygon;
using namespace boost::polygon::operators;

void polygon_set_data_test3()
{
	bool vertical = true;
    typedef point_data<int> point_type;
    typedef polygon_90_with_holes_data<int> polygon_type;
    typedef polygon_90_set_data<int> polygon_set_type;

	std::vector< rectangle_data<int> > rects;

    std::vector<point_type> data;
    data.push_back(point_type(0,0));
    data.push_back(point_type(6,0));
    data.push_back(point_type(6,4));
    data.push_back(point_type(4,4));
    data.push_back(point_type(4,6));
    data.push_back(point_type(0,6));

    
	std::vector<point_type> data1;
    data1.push_back(point_type(5,2));
    data1.push_back(point_type(5,1));
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
	allpset = pset - pset2;
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
			{	std::cout<<(*it).x()<<" ";
				std::cout<<(*it).y()<<std::endl;
			}
		}
	}
	//show polygon data
	for(int i = 0; i < polyresults.size(); ++i)
	{
		std::cout<<"i="<<i<<std::endl;
		for(it=polyresults[i].begin();it!=polyresults[i].end();it++)
		{
			std::cout<<(*it).x()<<" ";
			std::cout<<(*it).y()<<std::endl;
		}
	}

}

int main()
{
    polygon_set_data_test3();
    return boost::report_errors();
}
