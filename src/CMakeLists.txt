project(canvas)

add_library(canvas STATIC
	canvas_Namespace.h
	Canvas.h
	CanvasPath.h
	CanvasState.h
	CanvasTransform.h
	CircularStack.h
	SubPath.h
	Canvas.cpp
	CanvasPath.cpp
	CanvasState.cpp
	CircularStack.cpp
	SubPath.cpp
)
