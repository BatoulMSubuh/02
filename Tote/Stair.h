/*#pragma once
class stairs
{
public:
  stairs(void);
  ~stairs(void);
};*/

#ifndef STAIR_H
#define STAIR_H

class Stair {
public:
  Stair();

  void DrawQuad(Point v1, Point v2, Point v3, Point v4, float r, float g, float b);
  void DrawQuad(Point v1, Point v2, Point v3, Point v4, int image);
  void DrawQuad(Point v1,float length,float width,float hight,int image1,int image2);

  
};

#endif