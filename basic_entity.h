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

class ent {
public:
  Point pos;
  char ch[2];
  int id;
  bool canWalk(World*, int, int);
  void move(World*, int x, int y);
  void render();
  ent(int x, int y, int id, char ch);
};

ent::ent(int x, int y, int id, char ch)
{
 this->pos.x = x;
 this->pos.y = y;
 this->ch[0] = ch;
 this->ch[1] = '\0';
 this->id = id;
}

void ent::move(World* map, int dx, int dy)
{
 if (canWalk(map, this->pos.x+dx, this->pos.y+dy))
 {
  map->layout[pos.x][pos.y].blocks = false;
  this->pos.x += dx;
  this->pos.y += dy;
  map->layout[pos.x][pos.y].blocks = true;
 }
  map->setValue(&pos); //we recreate the value map everytime we move.
}

void ent::render()
{
 terminal_layer(2);
 terminal_color("green");
 terminal_print(pos.x, pos.y, ch);
}

bool ent::canWalk(World* map, int x, int y)
{
  if (map->layout[x][y].blocks == true) {
   return false;
  } else {
   return true;
  }
}


class ai {
public:
 void moveNPC(World* map, ent* g, Point* playerPos);
 ai();
};

ai::ai()
{

}
//This function examines all of the tiles immediatley
//surounding the NPC. if the tile being examined
//has a lower value than the current lowest, that
//tile becomes the new lowest value.
void ai::moveNPC(World* map, ent* g, Point* playerPos)
{
 int least, x , y;
 Point lowest;
 int centx = g->pos.x;
 int centy = g->pos.y;
 for (x = centx - 1; x < centx + 2; x++)
 {
  for (y = centy - 1; y < centy + 2; y++)
  {
    if (map->layout[x][y].value <= least && map->layout[x][y].blocks == false)
    {
     least = map->layout[x][y].value;
     lowest.x = x;
     lowest.y = y;
    }
  }
 }
 if (map->layout[lowest.x][lowest.y].blocks == false)
 {
  map->layout[g->pos.x][g->pos.y].blocks = false;
  g->pos.x = lowest.x;
  g->pos.y = lowest.y; 
  map->layout[g->pos.x][g->pos.y].blocks = true;
 }
}
