// Cooding Interview question
// Includes
#include <vector>
#include<stdlib.h>
#include<iostream>

using namespace std;

enum Color
{
    Red,
    Blue,
    Orange
};

struct Block
{
    Color color;
    int x;
    int y;
};

class Snake
{
    vector<Block> snake;
    int len;
    Color color;
    public:

    Snake() : snake(0)
    {
        len = snake.size();
    }

    void addblock(int x , int y , Color c)
    {
        if(len == 0)
        {
            Block temp;
            temp.x  = x;
            temp.y  = y;
            temp.color = c;
            color = c;
            snake.push_back(temp);   
            len++; 
        }
        else
        {
            if(color == c)
            {
                Block temp;
                temp.x  = x;
                temp.y  = y;
                temp.color = c;
                snake.push_back(temp);
                len++;
            }     
        }    
    }

    void addblock(Block temp)
    {
        if(len==0)
        {
            snake.push_back(temp);
            color = temp.color;
            len++;
        }
        else
        {
            if(color == temp.color)
            {
                snake.push_back(temp);
                len++;
            }
        }
    }

    bool check(Block newblock)
    {
        if(color == newblock.color)
        {
            for(int i = 0 ; i < len; i++)
            {
                if((abs(snake[i].y - newblock.y) == 1) && (snake[i].x == newblock.x))
                {
                    return true;
                }
                if((abs(snake[i].x - newblock.x) == 1) && (snake[i].y == newblock.y))
                {
                    return true;
                }
            }
        }
        return false;
    }

    int getsize()
    {
        return len;
    }
};

class Grid
{
    Block *grid;
    vector<Snake> snakes;
    int columns;
    int rows;

    public:

    Grid(int rows , int columns , Color newgrid[]): snakes(0)
    {
        Grid::columns = columns ; 
        Grid::rows = rows ; 
        grid = new Block[columns*rows];

        for(int i = 0 ; i < rows ; i++)
        {
            for(int j = 0 ; j < columns ; j++)
            {
                Block temp;
                temp.color = newgrid[i*columns + j];
                temp.x = i;
                temp.y = j;
                grid[i * columns + j] = temp ;
            }
        }
    }

    Snake Analyse()
    {
        Snake temp;
        bool flag = false;
        temp.addblock(at(0,0));
        snakes.push_back(temp);

        for(int i=0 ;i<rows; i++)
        {
            for(int j=0 ;j < columns ; j++)
            {
                if(i==0 && j==0)
                {
                    continue;
                }
                int numSnakes = snakes.size();
                for(int k = 0 ;k < numSnakes ; k++ )
                {
                    if(snakes[k].check( at(i , j) ))
                    {
                        snakes[k].addblock( at(i,j) );
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                {
                    Snake temp;
                    temp.addblock(at(i , j));
                    snakes.push_back(temp);
                }
                flag = false;
            }
        }
        int numSnakes = snakes.size();
        int large = snakes[0].getsize();
        int index = 0;
        for(int i = 0 ; i < numSnakes ; i++)
        {
            if(large < snakes[i].getsize())
            {
                large = snakes[i].getsize();
                index = i;
            }
        }
        return snakes[index];
    }

    Block at(int i , int j)
    {
        return grid[i*columns + j];
    }
};

void main()
{
    Color flatgrid[9] = { Red , Blue , Orange , Red , Blue , Orange , Red , Blue , Orange};

    Grid grid1( 3 , 3 , flatgrid);
    Snake largestSnake = grid1.Analyse();

    cout << largestSnake.getsize() ;
}
