#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "Pattern.cpp"

#define HEIGHT 42
#define WIDTH 150
#define SLEEP_TIME 50000
#define DEAD_CELL ' '
#define ALIVE_CELL '*'

using namespace std;

void init(string (&grid)[HEIGHT])
{
    for(int i=0;i<HEIGHT;i++)
    {
        grid[i].assign(WIDTH,DEAD_CELL);
    }   
}

void feedPattern(string (&grid)[HEIGHT])
{
    vector<Point> myPattern;
    loadPattern(myPattern,HEIGHT,WIDTH,1);
    for(int i = 0;i<myPattern.size();i++)
    {
        int row = myPattern[i].y;
        int col = myPattern[i].x;
        grid[row][col] = ALIVE_CELL;        
    }
}

void display(string grid[HEIGHT])
{
    cout << "\033[H\033[2J";
    for(int i=0;i<HEIGHT;i++)
        cout<<grid[i]<<endl;
}

int getAliveNbrs(string grid[HEIGHT],int row,int col)
{
    int top,bottom,left,right;
    top = row==0?HEIGHT-1:row-1;
    bottom = row==HEIGHT-1?0:row+1;
    left = col==0?WIDTH-1:col-1;
    right = col==WIDTH-1?0:col+1;
    
    int count = 0;
    //Moore neighbourhood
    if(grid[top][left] == ALIVE_CELL)
        count++;
    if(grid[top][col] == ALIVE_CELL)
        count++;
    if(grid[top][right] == ALIVE_CELL)
        count++;
    if(grid[bottom][left] == ALIVE_CELL)
        count++;
    if(grid[bottom][col] == ALIVE_CELL)
        count++;
    if(grid[bottom][right] == ALIVE_CELL)
        count++;
    if(grid[row][left] == ALIVE_CELL)
        count++;
    if(grid[row][right] == ALIVE_CELL)
        count++;
    
    return count;
}

void playTurn(string (&grid)[HEIGHT])
{
    vector<pair<int,int> > newDead,newAlive;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            int alive = getAliveNbrs(grid,i,j);
            
            if(grid[i][j] == ALIVE_CELL && (alive<2 || alive>3))
                newDead.push_back(make_pair(i,j));
            
            if(grid[i][j] == DEAD_CELL && alive==3)
                newAlive.push_back(make_pair(i,j));
        }
    }
    
    for(vector<pair<int,int> >::iterator it = newDead.begin();it!=newDead.end();it++)
    {
        grid[it->first][it->second] = DEAD_CELL;
    }
    
    for(vector<pair<int,int> >::iterator it = newAlive.begin();it!=newAlive.end();it++)
    {
        grid[it->first][it->second] = ALIVE_CELL;
    }
}

int main()
{
    string grid[HEIGHT];
    init(grid);
    feedPattern(grid);
    for(int i=0;i<1000000;i++)
    {
        display(grid);
        playTurn(grid);
        usleep(SLEEP_TIME);
    }
}