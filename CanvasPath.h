#ifndef CanvasPath_H
#define CanvasPath_H
#include "CircularStack.h"
#include "SubPath.h"

// The CanvasPath is a stack of subPaths

class CanvasPath {
  public:
    CanvasPath();
    CanvasPath(unsigned int maxNumSubPaths, unsigned int maxPathLength);
    ~CanvasPath();
    void moveTo(unsigned int x, unsigned int y); // Creates a new subpath with the given point.
    void closePath(); // Marks the current subpath as closed, and starts a new subpath with a point the same as the start and end of the newly closed subpath.
    
    void lineTo(unsigned int x, unsigned int y); // Adds the given point to the current subpath, connected to the previous one by a straight line.
//    void arcTo(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius); // Adds an arc with the given control points and radius to the current subpath, connected to the previous point by a straight line.
//    void quadraticCurveTo(unsigned int cpx, unsigned int cpy, unsigned int x, unsigned int y); // Adds the given point to the current subpath, connected to the previous one by a quadratic Bézier curve with the given control point.
//    void bezierCurveTo(unsigned int cpx, unsigned int cpy, unsigned int x, unsigned int y); // Adds the given point to the current subpath, connected to the previous one by a cubic Bézier curve with the given control point.

    unsigned int getNumSubPaths();

  private:
    int _maxNumSubPaths; // maximum number of SubPaths in the Path
    int _maxPathLength; // maximum number of coordinates for a subpath
    bool _needsNewSubpath;
    CircularStack<SubPath> _subPaths;
};

#endif
