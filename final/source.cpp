#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>

#include <boost/core/lightweight_test.hpp>
#include <boost/polygon/polygon.hpp>
using namespace boost::polygon;
using namespace boost::polygon::operators;

std::map<int, int> mapping;

// oper1 records every operation, oper2 records every point of every polygon per operation
std::vector< rectangle_data<int> > polygon_set_data_test3(std::vector<std::string> oper1, std::vector<int>** oper2, std::vector<int> num_of_polygon_per_oper){
    int num_of_oper = oper1.size();
	bool vertical = true;
    typedef point_data<int> point_type;
    typedef polygon_90_with_holes_data<int> polygon_type;
    typedef polygon_90_set_data<int> polygon_set_type;
    std::vector< rectangle_data<int> > rects_v;
    std::vector< rectangle_data<int> > rects_h;

    int m_idx;

    polygon_set_type allpset;
    // 第一個operation比較不一樣，其第一個polygon為起始allpset
    for (int i = 0; i < 1; i++){
        m_idx = mapping.find(i)->second;
        // std::cout << "i = " << i << std::endl;
        int num_of_polygon = num_of_polygon_per_oper[m_idx];
        // std::cout << "num_of_polygon of operation " << i << ": " << num_of_polygon << std::endl;
        std::vector<point_type> data;
        // std::cout << "test: " << oper2[i][0].size() << std::endl;
        // std::cout  << "POLYGON ";
        for (int k = 0; k < oper2[m_idx][0].size()/2; k++){
            data.push_back(point_type(oper2[m_idx][0][2*k], oper2[m_idx][0][2*k + 1]));
            // std::cout << oper2[i][0][2*k] << " " << oper2[i][0][2*k + 1] << " ";
        }
        // std::cout << std::endl;

        polygon_type polygon;
        polygon.set(data.begin(), data.end());
        polygon_set_type pset;
        pset += polygon;
        allpset = pset; // 一開始令allpset = 第一個polygon的pset
        for (int j = 1; j < num_of_polygon; j++){  //應該除了第一個operation以外其他都從0開始 這邊要把2改成真正的polygon的個數
            std::vector<point_type> data1;
            // std::cout  << "POLYGON ";
            for (int k = 0; k < oper2[m_idx][j].size()/2; k++){
                data1.push_back(point_type(oper2[m_idx][j][2*k], oper2[m_idx][j][2*k + 1]));
                // std::cout << oper2[i][j][2*k] << " " << oper2[i][j][2*k + 1] << " ";
            }
            // std::cout << std::endl;

            polygon_type polygon1;
            polygon1.set(data1.begin(), data1.end());
            polygon_set_type pset1;
            pset1 += polygon1;

            if (oper1[i].find("M") != std::string::npos){
                // std::cout << "M" << j << std::endl;
                allpset += pset1;
            }
            else if (oper1[i].find("C") != std::string::npos){
                // std::cout << "C" << j << std::endl;
                allpset -= pset1;
            } 
            else {
                std::cout << "This Operation is not correct." << std::endl;
            }   
        }
        std::cout << "The area of operation " << i+1 << " is " << area(allpset) << std::endl;
    }

    for (int i = 1; i < num_of_oper-1; i++){
        m_idx = mapping.find(i)->second;
        // std::cout << "i = " << i << std::endl;
        int num_of_polygon = num_of_polygon_per_oper[m_idx];            
        // std::cout << "The number of polygon of operation " << i+1 << " is " << num_of_polygon << std::endl;
        for (int j = 0; j < num_of_polygon; j++){  //應該除了第一個operation以外其他都從0開始 這邊要把1改成真正的polygon的個數
            std::vector<point_type> data1;
            // std::cout << "POLYGON ";
            for (int k = 0; k < oper2[m_idx][j].size()/2; k++){
                data1.push_back(point_type(oper2[m_idx][j][2*k], oper2[m_idx][j][2*k + 1]));
                // std::cout << oper2[i][j][2*k] << " " << oper2[i][j][2*k + 1] << " ";
            }
            // std::cout << std::endl;

            polygon_type polygon1;
            polygon1.set(data1.begin(), data1.end());
            polygon_set_type pset1;
            pset1 += polygon1;

            if (oper1[i].find("M") != std::string::npos){
                // std::cout << "M" << j << std::endl;
                allpset += pset1;
            }
            else if (oper1[i].find("C") != std::string::npos){
                // std::cout << "C" << j << std::endl;
                allpset -= pset1;
            } 
            else {
                std::cout << "This Operation is not correct." << std::endl;
            }   
        }
        std::cout << "The area of operation " << i+1 << " is " << area(allpset) << std::endl;
    }
    std::cout << "the area of final polygon is " << area(allpset) << std::endl;

    if (oper1[oper1.size()-1] == "SV"){
        get_rectangles(rects_v, allpset, VERTICAL);
        // std::cout << "rects_v has " << rects_v.size() << " polygon." << std::endl;
        // long unsigned total_v = 0;
        // for (int i = 0; i < rects_v.size(); i++){
        //     // std::cout << "The area of vect_v[" << i << "] is " << area(rects_v[i]) << "." << std::endl;
        //     total_v += area(rects_v[i]);
        // }
        // std::cout << "total rects_v area is " << total_v << std::endl;
        return rects_v;
    }
    else if (oper1[oper1.size()-1] == "SH"){
        get_rectangles(rects_h, allpset, HORIZONTAL);
        // std::cout << "rects_h has " << rects_h.size() << " polygon." << std::endl;
        // long unsigned total_h = 0;
        // for (int i = 0; i < rects_h.size(); i++){
        //     // std::cout << "The area of vect_h[" << i << "] is " << area(rects_h[i]) << "." << std::endl;
        //     total_h += area(rects_h[i]);
        // }
        // std::cout << "total rects_h area is " << total_h << std::endl;
        return rects_h;
    }

    else {
        std::cerr << "Invalid input operation." << std::endl;
        exit(1);
    }
	// /*************** showing result ********************/
	// std::vector< polygon_type > polyresults;
	// polygon_type::iterator_type it;
	
	// allpset.get_polygons(polyresults);

	// for(int i = 0; i < polyresults.size(); ++i)
	// {
	// 	std::cout<<"i="<<i<<std::endl;
	// 	for(it=polyresults[i].begin();it!=polyresults[i].end();it++)
	// 	{	
	// 		std::cout<<(*it).x()<<" ";
	// 		std::cout<<(*it).y()<<std::endl;
	// 	}
	// }
}


int main(int argc, char* argv[]){
    if (argc != 3){
        std::cerr << "Invalid input parameter. Valid input format is ./em [input file name] [output file name]" << std::endl;
        exit(1);
    }
    std::ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.fail()){
        std::cerr << "Error opening File, File doesn't exist." << std::endl;
        exit(1);
    }
    int Num_of_operations = 0;
    std::vector<std::string> oper1;
    while (true){
        std::string temp;
        inFile >> temp;
        if (temp == ";"){
            // std::cout << "first line read finished."<< std::endl;
            break;
        }
        else if (temp == "OPERATION"){
            continue;
        }
        else {
            oper1.push_back(temp);
        }
    }
    // for (int i = 0; i < oper1.size(); i++){
    //     std::cout << oper1[i] << " ";
    // }
    // std::cout << std::endl;
    std::vector<int> num_of_polygon_per_oper;


    int V_idx = 0;
    for (int i = 0; i < oper1.size()-1; i++){
        int j = 0;
        while (true){
            std::string temp;
            inFile >> temp;
            if (temp == "POLYGON"){
                j++;
                // while (true){
                //     std::string coordinate;
                //     inFile >> coordinate;
                //     if (coordinate == ";"){
                //         break;
                //     }
                //     else {
                //         oper2[i][j].push_back(std::atoi(coordinate.c_str()));
                //     }
                // }
                // j++;
            }
            else if (temp == "END"){
                inFile >> temp;
                // std::cout << "one operation finished." << std::endl;
                break;
            }
            else if (temp == "DATA"){
                inFile >> temp;
                inFile >> temp;
                for (int k = 0; k < oper1.size(); k++){
                    if (strcmp(temp.c_str(), oper1[k].c_str()) == 0){
                        mapping.insert(std::pair<int, int>(k, V_idx));
                        V_idx++;
                    }

                }
                continue;
            }
        }
        num_of_polygon_per_oper.push_back(j);
    }
    // for (int i = 0; i < oper1.size()-1; i++){
    //     std::cout << num_of_polygon_per_oper[i] << " ";
    // }
    // std::cout << std::endl;
    inFile.close();


    std::ifstream inFile2;
    inFile2.open(argv[1]);
    std::vector<int>** oper2 = new std::vector<int>*[oper1.size()];
    for (int i = 0; i < oper1.size()-1; i++){
        oper2[i] = new std::vector<int>[num_of_polygon_per_oper[i]];
    }
    // std::cout << "set up matrix." << std::endl;
    for (int i = 0; i < oper1.size()-1; i++){
        int j = 0;
        while (true){
            std::string temp;
            inFile2 >> temp;
            if (temp == "POLYGON"){
                while (true){
                    std::string coordinate;
                    inFile2 >> coordinate;
                    if (coordinate != ";"){
                        oper2[i][j].push_back(std::atoi(coordinate.c_str()));
                        // std::cout << oper2[i][j].back() << " ";
                    }
                    else {
                        // std::cout << std::endl;
                        // std::cout << "one line finished." << std::endl;
                        break;
                    }
                }
                j++;
                if (j == num_of_polygon_per_oper[i]){
                    break;
                }
            }
            else {
                continue;
            }
        }
    }
    // for (int i = 0; i < oper1.size()-1; i++){
    //     int j = 0;
    //     while (j < num_of_polygon_per_oper[i]){
    //         // oper2[i][j].pop_back();
    //         // oper2[i][j].pop_back();
    //         std::cout  << "POLYGON ";
    //         for (int k = 0; k < oper2[i][j].size(); k++){
    //             std::cout << oper2[i][j][k] << " ";
    //         }
    //         std::cout << std::endl;
    //         j++;
    //     }
    // }
    inFile2.close();

    // for (int i = 0; i < oper1.size()-1; i++){
    //     std::cout << "number of polygon at " << i << " operation is " << num_of_polygon_per_oper[i] << std::endl;
    // }

    std::ofstream outFile;
    outFile.open(argv[2]);
    std::string a = "RECT";

    // std::cout << "in" << std::endl;
    std::vector< rectangle_data<int> > result;
    result = polygon_set_data_test3(oper1, oper2, num_of_polygon_per_oper);
    // std::cout << "out" << std::endl;
    for (int i = 0; i < result.size(); i++){
        outFile << a << " ";
        outFile << result[i].get(WEST) << " " << result[i].get(SOUTH) << " " << result[i].get(EAST) << " " << result[i].get(NORTH) << " ;" << std::endl; 
    }

    outFile.close();
    return 0;
}