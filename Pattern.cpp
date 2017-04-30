#include <vector>
#include <fstream>
#include <string>
#include<sstream>

using namespace std;
struct Point
{
    int y,x;
    Point(int row,int col)
    {
        y = row;
        x = col;
    }
};

void loadPattern(vector<Point> &myPattern, int height,int width,int code)
{    
    ifstream myfile;
	string line;
	myfile.open("Patterns/"+to_string(code)+".pf");
	int row,col;
	while(getline(myfile,line))
	{
		istringstream iss(line);
		if(line[0]=='/' && line[1]=='/' || line[0]==' ')
		    continue;
		while(iss>>row>>col)
		{
			myPattern.push_back(Point(row,col));
		}
	}
}
