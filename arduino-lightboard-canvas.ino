#include <OctoWS2811.h>
#include <stdbool.h>
#include <stdint.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int midiChannel = 16;
const int width = 30;
const int height = 16;

// just a single strip
const int ledsPerStrip = width * height;

int canvas[width * height];
int l1[width * height];

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

// Swap two bytes
#define SWAP(x,y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)

#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010

int colors[] = {RED, GREEN, BLUE, YELLOW, PINK, ORANGE, WHITE};
int bgColor = 0;
int shapeColor = 6;
int pos[] {width / 2, height /2 };
int offX, offY, size;

int mClock = 0;

void setup() {
  MIDI.begin(midiChannel);
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleNoteOn(handleNoteOn);
  leds.begin();
  offX = 0;
  offY = 0;
  size = 5;
}

void setBackgroundColor(int color) {
  for (int i = 0; i < ledsPerStrip; i++) {
      canvas[i] = color;
    }
}

void handleNoteOn(byte channel, byte note, byte velocity) {
    bgColor++;
    if (bgColor > 6) {
      bgColor = 0;
    }
}

void handleClock() {
    mClock++;
    if(mClock % 2 == 0) {
          setBackgroundColor(colors[bgColor]);
    checkers(size, offX, offY, WHITE);
    for(int i = 0; i < width * height; i++) {
      leds.setPixel(i, canvas[i]);
    }
    leds.show();
    }
    if (mClock % 12 == 0) {
       offX++;
       offY++;
    } 
}

void loop() {
  MIDI.read();
}


int xy(int x, int y) {
  return (y % 2 == 1) ? (y * width + x) : (y * width + (width - (x + 1)));
}

void drawOnLayer(int index, int color) {
    canvas[index] = color;
  }

void setPix(int x, int y, int color) {
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;
    drawOnLayer(xy(x, y), color);
  }

// even rows should be 0 < x < 4, 8 < 12, etc. even multiples of 4

void checkers(int size, int offX, int offY, int color) {
  bool evenRow, evenCol;
  for(int y = 0; y < height; y++) {
      evenRow = ((y + offY) % (2 * size) < size);
      for (int x = 0; x < width; x++) {
          evenCol= ((x + offX) % (2 * size) < size);
          if (evenRow == evenCol) setPix(x, y, color);
        }
    }
}

void drawRect(int x, int y, int w, int h, int color) {
  // x is the corner vertex
  // horizontal lines
  horiz(x, x+w-1, y, color);
  horiz(x, x+w-1, y+h-1, color);
  //vertical lines
  drawLine(x, y, x, y + h-1, color);
  drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
  }

void fillRect(int x, int y, int w, int h, int color) {
  for(int i = y; i < y + h; i++) {
      horiz(x, x + w - 1, i, color);
    }
}

void octaPoints(int xc, int yc, int x, int y, int color) { 
    drawOnLayer(xy(xc+x, yc+y), color); 
    drawOnLayer(xy(xc-x, yc+y), color); 
    drawOnLayer(xy(xc+x, yc-y), color); 
    drawOnLayer(xy(xc-x, yc-y), color); 
    drawOnLayer(xy(xc+y, yc+x), color); 
    drawOnLayer(xy(xc-y, yc+x), color); 
    drawOnLayer(xy(xc+y, yc-x), color); 
    drawOnLayer(xy(xc-y, yc-x), color); 
  } 

void octaLines(int xc, int yc, int x, int y, int color) {
  horiz(xc+x, xc-x, yc+y, color);
  horiz(xc+x, xc-x, yc-y, color);
  horiz(xc+y, xc-y, yc+x, color);
  horiz(xc+y, xc-y, yc-x, color);
  }

void drawCircle(int xc, int yc, int r, int color) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    octaPoints(xc, yc, x, y, color); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        octaPoints(xc, yc, x, y, color);  
    } 
} 

void fillCircle(int xc, int yc, int r, int color) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    octaLines(xc, yc, x, y, color); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        octaLines(xc, yc, x, y, color);  
    } 
} 

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x3, y3, color);
  drawLine(x3, y3, x1, y1, color);
  }

  // Horizontal line
void horiz(int x1, int x2, int y, int c) {
  if(x1>=x2) SWAP(x1,x2);
  for(;x1<=x2;x1++) drawOnLayer(xy(x1,y), c);
}

void drawLine(int x1,int y1,int x2,int y2,int c){
 if (y1 == y2) {
    horiz(x1, x2, y1, c);
    return;
  }
 int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 dx=x2-x1;
 dy=y2-y1;
 dx1=fabs(dx);
 dy1=fabs(dy);
 px=2*dy1-dx1;
 py=2*dx1-dy1;
 if(dy1<=dx1){
  if(dx>=0)
  {
   x=x1;
   y=y1;
   xe=x2;
  }
  else
  {
   x=x2;
   y=y2;
   xe=x1;
  }
  drawOnLayer(xy(x,y),c);
  for(i=0;x<xe;i++)
  {
   x=x+1;
   if(px<0)
   {
    px=px+2*dy1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     y=y+1;
    }
    else
    {
     y=y-1;
    }
    px=px+2*(dy1-dx1);
   }
   drawOnLayer(xy(x,y),c);
  }
 }
 else
 {
  if(dy>=0)
  {
   x=x1;
   y=y1;
   ye=y2;
  }
  else
  {
   x=x2;
   y=y2;
   ye=y1;
  }
  drawOnLayer(xy(x,y),c);
  for(i=0;y<ye;i++)
  {
   y=y+1;
   if(py<=0)
   {
    py=py+2*dx1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     x=x+1;
    }
    else
    {
     x=x-1;
    }
    py=py+2*(dx1-dy1);
   }
   drawOnLayer(xy(x,y),c);
  }
 }
}


// Fill a triangle - slope method
// Original Author: Adafruit Industries
void fillTriangleslope(int x0, int y0,int x1, int y1, int x2, int y2, int color) {
  int a, b, y, last;
    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }
    if (y1 > y2) { SWAP(y2, y1); SWAP(x2, x1); }
    if (y0 > y1) { SWAP(y0, y1); SWAP(x0, x1); }
  
    if(y0 == y2) { // All on same line case
      a = b = x0;
      if(x1 < a)      a = x1;
      else if(x1 > b) b = x1;
      if(x2 < a)      a = x2;
      else if(x2 > b) b = x2;
        horiz(a, b, y0, color);
        return;
    }

    int
        dx01 = x1 - x0,
        dy01 = y1 - y0,
        dx02 = x2 - x0,
        dy02 = y2 - y0,
        dx12 = x2 - x1,
        dy12 = y2 - y1;
    int16_t sa = 0, sb = 0;

    // For upper part of triangle, find scanline crossings for segment
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y
    // is included here (and second loop will be skipped, avoiding a /
    // error there), otherwise scanline y1 is skipped here and handle
    // in the second loop...which also avoids a /0 error here if y0=y
    // (flat-topped triangle)
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        // longhand a = x0 + (x1 - x0) * (y - y0) / (y1 - y0)
        //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
        horiz(a, b, y, color);
    }

    // For lower part of triangle, find scanline crossings for segment
    // 0-2 and 1-2.  This loop is skipped if y1=y2
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        // longhand a = x1 + (x2 - x1) * (y - y1) / (y2 - y1)
        //          b = x0 + (x2 - x0) * (y - y0) / (y2 - y0)
        horiz(a, b, y, color);
    }
}

// Fill a triangle - Bresenham method
// Original from http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
void fillTriangle(int x1,int y1,int x2,int y2,int x3,int y3, int c) {
  int t1x,t2x,y,minx,maxx,t1xp,t2xp;
  bool changed1 = false;
  bool changed2 = false;
  int signx1,signx2,dx1,dy1,dx2,dy2;
  int e1,e2;
    // Sort vertices
  if (y1>y2) { SWAP(y1,y2); SWAP(x1,x2); }
  if (y1>y3) { SWAP(y1,y3); SWAP(x1,x3); }
  if (y2>y3) { SWAP(y2,y3); SWAP(x2,x3); }

  t1x=t2x=x1; y=y1;   // Starting points

  dx1 = (int)(x2 - x1); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
  dy1 = (int)(y2 - y1);
 
  dx2 = (int)(x3 - x1); if(dx2<0) { dx2=-dx2; signx2=-1; } else signx2=1;
  dy2 = (int)(y3 - y1);
  
  if (dy1 > dx1) {   // swap values
        SWAP(dx1,dy1);
    changed1 = true;
  }
  if (dy2 > dx2) {   // swap values
        SWAP(dy2,dx2);
    changed2 = true;
  }
  
  e2 = (int)(dx2>>1);
    // Flat top, just process the second half
    if(y1==y2) goto next;
    e1 = (int)(dx1>>1);
  
  for (int i = 0; i < dx1;) {
    t1xp=0; t2xp=0;
    if(t1x<t2x) { minx=t1x; maxx=t2x; }
    else    { minx=t2x; maxx=t1x; }
        // process first line until y value is about to change
    while(i<dx1) {
      i++;      
      e1 += dy1;
          while (e1 >= dx1) {
        e1 -= dx1;
               if (changed1) t1xp=signx1;//t1x += signx1;
        else          goto next1;
      }
      if (changed1) break;
      else t1x += signx1;
    }
  // Move line
  next1:
        // process second line until y value is about to change
    while (1) {
      e2 += dy2;    
      while (e2 >= dx2) {
        e2 -= dx2;
        if (changed2) t2xp=signx2;//t2x += signx2;
        else          goto next2;
      }
      if (changed2)     break;
      else              t2x += signx2;
    }
  next2:
    if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
    if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
      horiz(minx, maxx, y, c);    // Draw line from min to max points found on the y
    // Now increase y
    if(!changed1) t1x += signx1;
    t1x+=t1xp;
    if(!changed2) t2x += signx2;
    t2x+=t2xp;
      y += 1;
    if(y==y2) break;
    
   }
  next:
  // Second half
  dx1 = (int)(x3 - x2); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
  dy1 = (int)(y3 - y2);
  t1x=x2;
 
  if (dy1 > dx1) {   // swap values
        SWAP(dy1,dx1);
    changed1 = true;
  } else changed1=false;
  
  e1 = (int)(dx1>>1);
  
  for (int i = 0; i<=dx1; i++) {
    t1xp=0; t2xp=0;
    if(t1x<t2x) { minx=t1x; maxx=t2x; }
    else    { minx=t2x; maxx=t1x; }
      // process first line until y value is about to change
    while(i<dx1) {
        e1 += dy1;
          while (e1 >= dx1) {
        e1 -= dx1;
                if (changed1) { t1xp=signx1; break; }//t1x += signx1;
        else          goto next3;
      }
      if (changed1) break;
      else          t1x += signx1;
      if(i<dx1) i++;
    }
  next3:
        // process second line until y value is about to change
    while (t2x!=x3) {
      e2 += dy2;
          while (e2 >= dx2) {
        e2 -= dx2;
        if(changed2) t2xp=signx2;
        else          goto next4;
      }
      if (changed2)     break;
      else              t2x += signx2;
    }        
  next4:

    if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
    if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
      horiz(minx, maxx, y, c);    // Draw line from min to max points found on the y
    // Now increase y
    if(!changed1) t1x += signx1;
    t1x+=t1xp;
    if(!changed2) t2x += signx2;
    t2x+=t2xp;
      y += 1;
    if(y>y3) return;
  }
}
