#include "CanvasPath.h"
#include "CanvasState.h"
#include "CanvasTransform.h"

#ifndef Canvas_H
#define Canvas_H

class Canvas {
  public:
    Canvas();
    Canvas(unsigned int width, unsigned int height,  unsigned int maxNumPaths, unsigned int maxPathLength, unsigned int maxNumStates);
    ~Canvas();

    void save(); // Pushes the current CanvasState to the stack.
    void restore(); // Pops the last CanvasState from the stack and applies the settings to the current settings.

    void beginPath(); // Resets the current default path
    void closePath(); // Marks the current subpath as closed, and starts a new subpath with a point the same as the start and end of the newly closed subpath.
    void stroke(); // Paints the current default path onto the bitmap.
    void fill(); // Closes all subpaths in the current default path and paints it onto the bitmap. line from non-connected points

    void moveTo(int x, int y); // Creates a new subpath with the given point.
    //void lineTo(int x, int y); // Adds the given point to the current subpath, connected to the previous one by a straight line.
    //void arcTo(int x1, int y1, int x2, int y2, unsigned int radius); // Adds an arc with the given control points and radius to the current subpath, connected to the previous point by a straight line.
    //void quadraticCurveTo(int cpx, int cpy, int x, int y); // Adds the given point to the current subpath, connected to the previous one by a quadratic Bézier curve with the given control point.
    //void bezierCurveTo(int cpx, int cpy, int x, int y); // Adds the given point to the current subpath, connected to the previous one by a cubic Bézier curve with the given control point.

    void setStrokeColor(unsigned int color); // Sets the current stroke color. Stroke is the border of the shape
    unsigned int getStrokeColor(); // Returns the current stroke color.
    
    void setFillColor(unsigned int fillColor); // Sets the current fil color.
    unsigned int getFillColor(); // returns the current fill color.

    void setBackgroundColor(unsigned int color); // Sets the color of the canvas.

    //void strokeRect(int x, int y, unsigned int height, unsigned int width); // Clears all pixels on the bitmap in the given rectangle to transparent black.
    //void fillRect(int x, int y, unsigned int height, unsigned int width); // Paints the given rectangle onto the bitmap, using the current fill style.
    //void clearRect(int x, int y, unsigned int height, unsigned int width); // Paints the box that outlines the given rectangle onto the bitmap, using the current stroke style.

    // Adds points to the subpath such that the arc described by the circumference of the ellipse described by the arguments, starting at the given start angle and ending at the 
    // given end angle, going in the given direction (defaulting to clockwise), is added to the path, connected to the previous point by a straight line.
    // void ellipse(int x, int y, unsigned int radiusX, unsigned int radiusY, float startAngle, float endAngle);                         
    //void ellipse(int x, int y, unsigned int radiusX, unsigned int radiusY, float startAngle, float endAngle, bool counterclockwise);  

    unsigned int getPixel(unsigned int x, unsigned int y); // Returns the color of the pixel at the given point.

    //void scale(float x, float y); // Changes the current transformation matrix to apply a scaling transformation with the given characteristics.
    //void rotate(float angle); // Changes the current transformation matrix to apply a rotation transformation with the given characteristics. The angle is in radians.
    //void translate(int x, int y); // Changes the current transformation matrix to apply a translation transformation with the given characteristics.
    //void transform(float a, float b, float c, float d, float e, float f); // Changes the current transformation matrix to apply the matrix given by the arguments as described below.
    //void getTransform(CanvasTransform& transform); // Copies the contents of the current transformation matrix into the provided CanvasTransform.
    //void setTransform(float a, float b, float c, float d, float e, float f); // Changes the current transformation matrix to the matrix given by the arguments as described below.
    //void setTransform(CanvasTransform transform); // Changes the current transformation matrix to the matrix represented by the passed CanvasTransform.
    //void resetTransform(); // Changes the current transformation matrix to the identity matrix.
    
  private:
    void drawPix(int x, int y, unsigned int color);
    void horiz(int x1, int x2, unsigned int y, unsigned int color); // Quickly draws a horizontal line
    
    unsigned int width; 
    unsigned int height;
    
    unsigned int strokeColor;
    unsigned int fillColor;

    unsigned int maxNumPaths; // Maximum number of total paths allowed.
    unsigned int maxPathLength; // Maximum total number of xy-coordinates in all subpaths of any given path.
    unsigned int maxNumStates; // Maximum number of canvas states to be saved to the stack.
    
    unsigned int numStates; // Current number of states on the stack.
    unsigned int numPaths; // Number of paths currently in the paths list.
    
    CanvasPath currentDefaultPath;
    CanvasPath* paths;
    
    //CanvasTransform currentTransform; 
    
    CanvasState* states;
   
    unsigned int** canvas; // The bitmap: a 2d array of color values.
};
#endif
