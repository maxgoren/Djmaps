/*
Copyright (c) 2020 Max Goren 
maxgoren@icloud.com
http://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
struct Point {
  int x;
  int y;
};

struct Tile {
 Point pos;
 color_t color;
 int value;
 std::string sym;
 bool blocks;
};

class World {
public:
int mapW;
int mapH;
Tile layout[82][43];
void setValue(Point*);
void makeMap();
void dig_shape(Point pos, int w, int h);
void allSeeingEye(Point*);
World(int w, int h);
};

World::World(int w, int h)
{
 int x, y;
 this->mapW = w;
 this->mapH = h;
 for (x = 0; x < mapW; x++)
 {
  for (y = 0; y < mapH; y++)
  {
     this->layout[x][y].blocks = true;
     this->layout[x][y].sym = "#";
     this->layout[x][y].value = 0;
     this->layout[x][y].color = color_from_name("white");
  }
 }
}

//This is the function that creats the "Dijstrika Map"
//Around objects of value, in this demo that being
//the players character.
void World::setValue(Point* pPos)
{
 int x,y;
 int distance;
 int dx,dy;
 int limiter = 6; //changing this value changes how far out the Map goes around object.
 
 color_t djcol[8] = { color_from_name("green"),
 		                  color_from_name("red"),
 		                  color_from_name("flame"),
 		                  color_from_name("yellow"),
 		                  color_from_name("orange"),
 		                  color_from_name("magenta"),
 		                  color_from_name("cyan"),
 		                  color_from_name("blue")};
 
 
 for (x = 1; x < mapW - 1; x++)
 {
  for (y = 1; y < mapH - 1; y++)
  {
    dx = x - pPos->x;
    dy = y - pPos->y;
    float dist = sqrtf(dx*dx+dy*dy);
    distance = (int)round(dist);
    if (distance < limiter)
    {
      this->layout[x][y].value = distance;
      this->layout[x][y].sym = std::to_string(distance);
      this->layout[x][y].color=djcol[distance];
    } else {
      this->layout[x][y].sym = " ";
      this->layout[x][y].value = 10;
      this->layout[x][y].color=color_from_name("white");
    }
  }
 }
}

void World::dig_shape(Point pos, int w, int h)
{
 int x, y;
 for (x = pos.x; x < pos.x+w; x++)
 for (y = pos.y; y < pos.y+h; y++)
 {
 {
  this->layout[x][y].blocks = false;
  }
 }
}
//set up some quick room and tunnels
//for our demonstration
void World::makeMap()
{
  Point rm1;
  Point rm2;
  Point rm3;
  Point rm4;
  Point rm5;
  Point rm6;
  Point rm7;
  rm1.x = 5; rm1.y = 5;
  rm2.x = 12; rm2.y = 11;
  rm3.x = 19; rm3.y = 14;
  rm4.x = 44; rm4.y = 16;
  rm5.x = 46; rm5.y = 20;
  rm6.x = 59; rm6.y = 7;
  rm7.x = 42; rm7.y = 3;
  dig_shape(rm1, 13, 8);
  dig_shape(rm2, 8, 6);
  dig_shape(rm3, 27,2);
  dig_shape(rm4, 2, 6);
  dig_shape(rm5, 15,2);
  dig_shape(rm6, 2, 15);
  dig_shape(rm7, 30, 8);
  
}

