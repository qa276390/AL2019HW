
class Node{
private:
	char color;
	bool flag;
	int x;
	int y;
public:
	Node(){color = ' ';flag = false;};
	Node(char c){color = c;flag = false;};

	void setflag(bool f){flag = f;}
	void setcolor(char c){color = c;}
	char getcolor(){return color;}
	bool getflag(){return flag;}
	void setxy(int x, int y){this->x = x; this->y = y;}
	int getx(){return x;}
	int gety(){return y;}


};
/*
class AdjNode{
public:
	int index;
	AdjNode* next;

	AdjNode(){index = 0;next=NULL;}
	AdjNode(int ind){index = ind;next=NULL;}

}*/
