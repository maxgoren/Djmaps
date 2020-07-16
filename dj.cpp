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
#include <list>
#include <string>
#include <math.h>
#include "BearLibTerminal.h"
#include "basic_world.h"
#include "basic_entity.h"

void drawAll(World* map, std::list<ent*> peeps)
{
 int x, y;
 terminal_layer(0);
 terminal_color("white");
 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
   terminal_color(map->layout[x][y].color);
   terminal_print(x, y, map->layout[x][y].sym.c_str());
   terminal_layer(2);
   if (map->layout[x][y].blocks == true)
   {
    terminal_print(x, y, "#");
   } else {
    terminal_layer(0);
    terminal_print(x,y, map->layout[x][y].sym.c_str());
   }
  }
 }
  for (auto p : peeps) //im so happy this feature was brought to C++.
  {
   p->render();
  }
  terminal_refresh();
}

int main(int argc, char *argv[])
{
 int k;
 bool turn = true;
 terminal_set("window; title='dj', size=85x42;");
 terminal_open();
 std::list<ent*> peeps;
 World* map;
 ai* Ai;
 ent* me;
 ent* g;

 Ai = new ai();
 map = new World(80, 40);
 me = new ent(10,10,666,'@');
 g = new ent(51,7,7,'G');
 peeps.push_back(me);
 peeps.push_back(g);
 map->makeMap();
 map->setValue(&me->pos);
 terminal_refresh();
 drawAll(map, peeps);
 while(true)
 {
  terminal_clear();
  if (terminal_has_input())
  {
   turn = true;
   k=terminal_read();
   switch (k)
   {
    case TK_UP: me->move(map,0,-1); break;
    case TK_DOWN: me->move(map,0,1); break;
    case TK_LEFT: me->move(map,-1,0); break;
    case TK_RIGHT: me->move(map,1,0); break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
   turn = false;
  }
  if (turn == false) {
   Ai->moveNPC(map, g, &me->pos);
  turn = true;
  }
  drawAll(map, peeps);
 }
 terminal_close();
 return 0;
}
