#ifndef PRIMITIVEDRAWER_H
#define PRIMITIVEDRAWER_H

class PrimitiveDrawer {
public:
	PrimitiveDrawer();
	void DrawPoint(Point point);
	void DrawLine(Point start, Point end);

	void DrawQuad(Point v1, Point v2, Point v3, Point v4, float r, float g, float b);
	void DrawQuad(Point v1, Point v2, Point v3, Point v4,int image);

	void Draw8poly(Point v1, Point v2, Point v3, Point v4,Point v5,Point v6,Point v7,Point v8, int image);
	void Draw8poly(Point v1, Point v2, Point v3, Point v4,Point v5,Point v6,Point v7,Point v8,float r,float g,float b);
	
//	void drawMySpher(GLUquadric *quadric,float x, float y, float z ,float radius, float slice,float stack,float xRotate, float yRotate, float zRotate,int image);
	
//	void drawMyCylinder(GLUquadric *quadric, float x, float y, float z, float baseRadius, float topRadius, float height, float xRotate, float yRotate, float zRotate,int image);
//	void drawMyCylinder(GLUquadric *quadric, float x, float y, float z, float baseRadius, float topRadius, float height, float xRotate, float yRotate, float zRotate);
};

#endif
