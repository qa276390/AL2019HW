
class Node{
private:
	char color;
	bool flag;
public:
	Node(){color = ' ';flag = false;};
	Node(char c){color = c;flag = false;};

	void setflag(bool f){flag = f;}
	void setcolor(char c){color = c;}
	char getcolor(){return color;}
	bool getflag(){return flag;}


};
