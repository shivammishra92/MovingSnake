#include <simplecpp>
const int gridsep = 20, xinit = 30, yinit = 20, length = 10, npts = 40;

struct Snake{
  Circle body[length];
  int headindex;   // which body element is the head of the snake
  int dx,dy;       // current direction of motion.
  Snake(){         // head at (xinit,yinit) in the coarse grid.
    headindex = 0;
    for(int i=0; i<length; i++)
      body[i].reset((xinit+0.5+i)*gridsep, (yinit+0.5)*gridsep, gridsep*0.5);
    dx = -gridsep; dy = 0;
  }
  void move(char command){
                                  // find direction of motion.
    if(command == 'w')      { dx = -gridsep; dy = 0;}
    else if (command == 'n'){ dx = 0; dy = -gridsep;}
    else if (command == 'e'){ dx = gridsep; dy = 0;}
    else if (command == 's'){ dx = 0; dy = gridsep;}
                           // else old direction, do not change dx, dy.
    int tailindex = (headindex +length - 1) % length;  // current tail
    body[tailindex] = body[headindex];  // current tail now on top of head
    body[tailindex].move(dx, dy);
    headindex = tailindex;              // current tail element becomes head
  }
};

int main(){
  initCanvas("Snake", gridsep*npts, gridsep*npts);
  Snake s;
  while(true){
    XEvent event;
    if(checkEvent(event) && keyPressEvent(event)){
	char c = charFromEvent(event);
	s.move(c);
    }
    else s.move('\0'); // NULL = continue to move in previous direction.
    wait(0.1);
  }
}
