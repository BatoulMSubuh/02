#ifndef SKYBOX_H
#define SKYBOX_H

class Skybox {
public:
  Skybox();

  //void DrawQuad(Point v1, Point v2, Point v3, Point v4, float r, float g, float b);
  void DrawSky(Point v1, Point v2, Point v3, Point v4, int image);
  void DrawSky ( Point v1,float length,float width,float hight,int Skyfront,int Skyback,int SkyUp,int Skydown,int Skyleft,int Skyright
);

};

#endif