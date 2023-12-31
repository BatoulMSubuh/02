#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>

#include "Point.h"
#include "Stair.h"

Stair::Stair() {}

//To make stairs Draw a quadrilateral with the given four vertices. 
void Stair::DrawQuad(Point v1, Point v2, Point v3, Point v4,float r,float g,float b) {
  

    glBegin(GL_QUADS);
   // glColor3f(r,g,b);
  glTexCoord2f(0.0f, 0.0f);glVertex3f(v1.x, v1.y, v1.z);
  glTexCoord2f(1.0f, 0.0f);glVertex3f(v2.x, v2.y, v2.z);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(v3.x, v3.y, v3.z);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(v4.x, v4.y, v4.z);
    glEnd();


  
}
void Stair::DrawQuad(Point v1, Point v2, Point v3, Point v4,int image) {
  
	glBindTexture(GL_TEXTURE_2D, image);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x1F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x1F);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(v3.x, v3.y, v3.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v4.x, v4.y, v4.z);
    
	glEnd();
	glDisable(GL_TEXTURE_2D);
  
}

// Draw Stair Using One Point &Length & Width & Hight
void Stair::DrawQuad(Point v1,float length,float width,float hight,int image1,int image2) {
  /*
	v1.x = v1.x - width / 2;
	v1.y = v1.y - hight / 2;
	v1.z = v1.z - length / 2;
	*/

	glBindTexture(GL_TEXTURE_2D, image1);
	glEnable(GL_TEXTURE_2D);


	//Front 
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, 2* v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight,v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width,v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y,2*  v1.z);
	glEnd();


	//Back 
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, 2*v1.z-length);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width,v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, 2*v1.z-length);
    glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image2);
	glEnable(GL_TEXTURE_2D);

	//Up 
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y+hight, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z);
    glEnd();

	//Down
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, 2*v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y, 2*v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y, 2*v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, 2*v1.z);
    glEnd();

	//Right
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, 2*v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x, v1.y, 2*v1.z-length);
    glEnd();

	//Left 
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x-width, v1.y, 2*v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x-width, v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, 2*v1.z-length);
    glEnd();



	glDisable(GL_TEXTURE_2D);
  
}