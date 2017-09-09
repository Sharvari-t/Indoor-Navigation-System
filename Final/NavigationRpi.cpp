// Program is run on raspberry pi 
// It implements A* algorithm to find the optimal path to arrive at the destination
// It drives the bot to follow the generated path.

#include<bits/stdc++.h>
using namespace std;
#define ROW 29
#define COL 18
#include<wiringPi.h>
using namespace std;
int Q1=0,Q2=2,Q3=4,Q4=5;
int dir,ddir,sdir=0,i;
int straight=1000;
int diagonal=1300;
int t45=200;
int t135=405;
int t90=400;
int t180=540;
int a[][2];
int q=0;
void forward(int tim);
void rotateleft(int delay1);
void rotateright(int delay2);
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> >pPair;
struct cell
{
   int parent_i, parent_j;
    double f, g, h;
};
bool Valid(int row, int col)
{
      return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL);
}
bool UnBlocked(int grid[][COL], int row, int col)
{
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}
bool Destination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
double calculate(int row, int col, Pair dest)
{
    return ((double)sqrt ((row-dest.first)*(row-dest.first)
                          + (col-dest.second)*(col-dest.second)));
}
void Path(cell cellDetails[][COL], Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push (make_pair (row, col));
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ",p.first,p.second);

            a[q][0]=p.first;
            a[q][1]=p.second;
        q++;
    }

    return;
}
void Star(int grid[][COL], Pair src, Pair dest)
{
if (Valid (src.first, src.second) == false)
    {
        return;
    }
    if (Valid (dest.first, dest.second) == false)
    {
        return;
    }
    if (UnBlocked(grid, src.first, src.second) == false ||
            UnBlocked(grid, dest.first, dest.second) == false)
    {
        return;
    }
    if (Destination(src.first, src.second, dest) == true)
    {
        return;
    }
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof (closedList));
    cell cellDetails[ROW][COL];

    int i, j;

    for (i=0; i<ROW; i++)
    {
        for (j=0; j<COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    set<pPair> openList;
    openList.insert(make_pair (0.0, make_pair (i, j)));
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        double gNew, hNew, fNew;
        if (Valid(i-1, j) == true)
        {
            if (Destination(i-1, j, dest) == true)
            {
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                Path (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i-1][j] == false &&
                     UnBlocked(grid, i-1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate(i-1, j, dest);
                fNew = gNew + hNew;
                if (cellDetails[i-1][j].f == FLT_MAX ||
                        cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair(i-1, j)));
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }
        if (Valid(i+1, j) == true)
        {
            if (Destination(i+1, j, dest) == true)
            {
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                Path(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i+1][j] == false &&
                     UnBlocked(grid, i+1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate(i+1, j, dest);
                fNew = gNew + hNew;
                if (cellDetails[i+1][j].f == FLT_MAX ||
                        cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i+1, j)));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }
        if (Valid (i, j+1) == true)
        {
          if (Destination(i, j+1, dest) == true)
            {
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                Path(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i][j+1] == false &&
                     UnBlocked (grid, i, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate (i, j+1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j+1].f == FLT_MAX ||
                        cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                        make_pair (i, j+1)));
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }
        if (Valid(i, j-1) == true)
        {
            if (Destination(i, j-1, dest) == true)
            {
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                Path(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i][j-1] == false &&
                     UnBlocked(grid, i, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate(i, j-1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j-1].f == FLT_MAX ||
                        cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew,
                                          make_pair (i, j-1)));
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
if (Valid(i-1, j+1) == true)
        {
            if (Destination(i-1, j+1, dest) == true)
            {
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                Path (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i-1][j+1] == false &&
                     UnBlocked(grid, i-1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate(i-1, j+1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i-1][j+1].f == FLT_MAX ||
                        cellDetails[i-1][j+1].f > fNew)
                {
                    openList.insert( make_pair (fNew,
                                    make_pair(i-1, j+1)));
                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }
        if (Valid (i-1, j-1) == true)
        {
            if (Destination (i-1, j-1, dest) == true)
            {
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                Path (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i-1][j-1] == false &&
                     UnBlocked(grid, i-1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate(i-1, j-1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i-1][j-1].f == FLT_MAX ||
                        cellDetails[i-1][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }
        if (Valid(i+1, j+1) == true)
        {
            if (Destination(i+1, j+1, dest) == true)
            {
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                Path (cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i+1][j+1] == false &&
                     UnBlocked(grid, i+1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate(i+1, j+1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i+1][j+1].f == FLT_MAX ||
                        cellDetails[i+1][j+1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                        make_pair (i+1, j+1)));
                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }
        if (Valid (i+1, j-1) == true)
        {
            if (Destination(i+1, j-1, dest) == true)
            {
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                Path(cellDetails, dest);
                foundDest = true;
                return;
            }
            else if (closedList[i+1][j-1] == false &&
                     isUnBlocked(grid, i+1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate(i+1, j-1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i+1][j-1].f == FLT_MAX ||
                        cellDetails[i+1][j-1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                                        make_pair(i+1, j-1)));
                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }

    return;
}
int main()
{
   int grid[ROW][COL] =   {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

    };  // grids of different floorplan is received by the server side grid generator application
 
    Pair src = make_pair(26, 2);
    Pair dest = make_pair(3, 6);
Star(grid, src, dest);
wiringPiSetup();
  pinMode(Q1,OUTPUT);
  pinMode(Q2,OUTPUT);
  pinMode(Q3,OUTPUT);
  pinMode(Q4,OUTPUT);
  cout<<"the pins have been set"<<endl;
  for(i=0; i<q; i++)
  {
    if (!((a[i][0]== a[i+1][0]) || (a[i][1] == a[i+1][1])))//checking for directions with respect to north
         {
          if(a[i][0]<a[i+1][0])
            {
           if ( a[i][1] > a[i+1][1] )
               ddir=7;
            else if(a[i][1] < a[i+1][1] )
                  ddir=1;
             }
              else
              {
              if ( a[i][1] > a[i+1][1] )
               ddir=5;
            else if(a[i][1] < a[i+1][1] )
                  ddir=3;
             }
          }
     else
     {
        if ( a[i][0] == a[i+1][0] )
           {
             if ( a[i][1] > a[i+1][1])
                   ddir=6;
             else if ( a[i][1] < a[i+1][1])
                   ddir=2;
           }
        else if ( a[i][0] > a[i+1][0] )
            ddir=0;
        else if ( a[i][0] < a[i+1][0] )
            ddir=4;
      }
     dir=sdir-ddir;
     if(dir==0)
     forward(straight);
     else if(dir==4||dir==-4){
     rotateleft(t180);//180 degree
     forward(straight);
     }
     else if(dir==-2||dir==6){
    rotateright(t90);
    forward(straight);
     }
    else if(dir==2||dir==-6){
     rotateleft(t90);//90 degree
     forward(straight);
    }
     else if(dir==-1||dir==7){
      rotateright(t45);
      forward(diagonal);
     }
      else if(dir==1||dir==-7){
      rotateleft(t45);//45 degree
      forward(diagonal);
      }
      else if(dir==-3||dir==5){
      rotateright(t135);//135 degree
      forward(diagonal);
      }
      else if(dir==-5||dir==3){
      rotateleft(t135);
      forward(diagonal);
      }
      sdir=ddir;
      }// for end
  //loop end

    return(0);
}
void forward(int tim)//north
{
 cout<<"forward"<<endl;
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
  delay(tim);
}
void rotateleft(int delay1)
{
  cout<<"left"<<endl;
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
  delay(delay1);
 }
void rotateright(int delay2)
{
 cout<<"right"<<endl;
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
   delay(delay2);
}
