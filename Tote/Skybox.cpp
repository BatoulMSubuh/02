
#include <windows.h>    // Header File For Windows
#include <gl.h>      // Header File For The OpenGL32 Library
#include <glu.h>      // Header File For The GLu32 Library
#include <glaux.h>    // Header File For The Glaux Library
#include <cmath>

#include "Point.h"
#include "Skybox.h"

Skybox::Skybox() {}

//To make Sky Box l with the given four vertices. 

void Skybox::DrawSky(Point v1, Point v2, Point v3, Point v4,int image) {
  
	


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v3.x, v3.y, v3.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v4.x, v4.y, v4.z);
   
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

	

void Skybox::DrawSky(Point v1,float length,float width,float hight,int Skyfront,int Skyback,int Skyup,int Skydown,int Skyleft,int Skyright) {

	

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skyfront);
	//glEnable(GL_TEXTURE_2D);
	//Front 
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width,v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, v1.z);
	glDisable(GL_TEXTURE_2D);
	glEnd();
   

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skyback);
	//Back 
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, v1.z-length);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width,v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, v1.z-length);
    glDisable(GL_TEXTURE_2D);
    glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skyup);

	//Up 
	glBegin(GL_QUADS);
	//glNormal3d(0,0,0);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y+hight, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skydown);
	

	//Down
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y, v1.z-length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, v1.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skyright);

	//Right
	glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x, v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x, v1.y, v1.z-length);
	glDisable(GL_TEXTURE_2D);
    glEnd();
    

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skyleft);
	glEnable(GL_TEXTURE_2D);

	//Left 
	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(v1.x-width, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(v1.x-width, v1.y+hight, v1.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(v1.x-width, v1.y+hight, v1.z-length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(v1.x-width, v1.y, v1.z-length);
	glDisable(GL_TEXTURE_2D);
    glEnd();



	
}