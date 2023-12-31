#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>
#include<glu.h>// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>


#include "Point.h" 
#include "PrimitiveDrawer.h" 
#include "Stair.h" 
#include "texture.h" 
#include "Skybox.h" 




#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>




HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Cntext
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

double movX, movY, movZ;
double lX, lY ;
 double open = 0;
 int StairsTexture,SkyFront,SkyBack,SkyUp,SkyDown,SkyLeft,SkyRight ;
void Camera()
{
	gluLookAt(movX, movY, movZ, lX, lY, -5, 0, 1, 0);
	if (keys['D']||keys['d'])
		movX += 0.001;
	if (keys['A'])
		movX -= 0.001;
	if (keys['W'])
		movY += 0.001;
	if (keys['S'])
		movY -= 0.001;
	if (keys['Z'])
		movZ += 0.001;
	if (keys['X'])
		movZ -= 0.001;
	if (keys[VK_LEFT])
		lX += 0.001;
	if (keys[VK_RIGHT])
		lX -= 0.001;
	if (keys[VK_UP])
		lY += 0.001;
	if (keys[VK_DOWN])
		lY -= 0.001;
	if (keys['1'])
		if(open<0.5)
		open += 0.001;
	if (keys['2'])
		if(open>0)
		open -= 0.001;
}


// For Draw Cylinder With Texture 
void drawMyCylinder(GLUquadric *quadric, float x, float y, float z, float baseRadius, float topRadius, float height, float xRotate, float yRotate, float zRotate,int image) {
//	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(zRotate, 0, 0, 1);
	glRotatef(yRotate, 0, 1, 0);
	glRotatef(xRotate, 1, 0, 0);
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,image);
	gluQuadricTexture(quadric,GL_TRUE);
	//gluCylinder(quadric, baseRadius, topRadius, height, 32.0, height * 5.0);
	gluCylinder(quadric, baseRadius, topRadius, height, 32.0,20.0);
    glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
}


// For Draw Ball 
void drawMySpher(GLUquadric *quadric,float x, float y, float z ,float radius, float slice,float stack,float xRotate, float yRotate, float zRotate,int image) {
	//glPushMatrix();
	//float r,float g,float b 
	//glColor3f(r,g,b);
	glTranslatef(x, y, z);
	glRotatef(zRotate, 0, 0, 1);
	glRotatef(yRotate, 0, 1, 0);
	glRotatef(xRotate, 1, 0, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,image);
	gluQuadricTexture(quadric,GL_TRUE);
	gluSphere(quadric, radius, slice, stack);
	glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
}



int Wall1,Wall2,WallRock,Wall3,Door,Dom,Carpet;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x1F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x1F);
	
	// Load Texture
	//Texture For SkyBox 
	glEnable(GL_TEXTURE_2D);
	SkyFront= LoadTexture("Front.bmp", 255);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	SkyBack = LoadTexture("Back.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	SkyUp   = LoadTexture("Up.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	SkyDown = LoadTexture("Down.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	SkyLeft = LoadTexture("Left.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	SkyRight= LoadTexture("Right.bmp", 255);

	glDisable(GL_TEXTURE_2D);
	//Texture For Stair 
	 glEnable(GL_TEXTURE_2D);
	StairsTexture = LoadTexture("Stair.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//Wall1
	 glEnable(GL_TEXTURE_2D);
	Wall1 = LoadTexture("Wall1.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//Wall2
	 glEnable(GL_TEXTURE_2D);
	Wall2 = LoadTexture("Wall2.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//Rocket Wall
	 glEnable(GL_TEXTURE_2D);
	WallRock = LoadTexture("Wall2.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	// Wall3
	 glEnable(GL_TEXTURE_2D);
	Wall3 = LoadTexture("Wall3.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//Door
	glEnable(GL_TEXTURE_2D);
	Door = LoadTexture("Door.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//Door
	glEnable(GL_TEXTURE_2D);
	Dom = LoadTexture("Dom.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	//carpet
	glEnable(GL_TEXTURE_2D);
	Carpet = LoadTexture("carpet.bmp", 255);
	glDisable(GL_TEXTURE_2D);
	



	return TRUE;										// Initialization Went OK
}

float h=2;
	Point a= Point(0,0,0);
	Point B= Point(0,0,3);
	Point c= Point(2.12,0,5.12);
	Point d= Point(5.12,0,5.12);
	Point e= Point(7.24,0,3);
	Point f= Point(7.24,0,0);
	Point g= Point(5.12,0,-2.12);
	Point H= Point(2.12,0,-2.12);

	Point i= Point(0,h,0);
	Point j= Point(0,h,3);
	Point k= Point(2.12,h,5.12);
	Point l= Point(5.12,h,5.12);
	Point m= Point(7.24,h,3);
	Point n= Point(7.24,h,0);
	Point o= Point(5.12,h,-2.12);
	Point p= Point(2.12,h,-2.12);

	// To Draw Door 
	Point a1= Point(3.12,0,5.12);
	Point B1= Point(4.12,0,5.12);
//	Point j1= Point(3.12,1,5.12);
	Point i1= Point(4.12,1,5.12);

	Point c2= Point(3.12,0,5.12);
	Point d2= Point(4.12,0,5.12);
	Point k2= Point(3.12,h,5.12);
	Point l2= Point(4.12,h,5.12);
	 
	// tTo Draw Stair 
	//Point c3= Point(2.12,-2,5.12);
	Point d3= Point(5.12,-2.25,6);

    //To Draw Sky
	Point sky= Point(15,-7,20);

	PrimitiveDrawer primitiveDrawer=PrimitiveDrawer();



int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{   
	GLUquadric *quadric = gluNewQuadric();

	GLUquadricObj* b = gluNewQuadric();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera();
	glTranslated(0, 2, -30);
	glScaled(1.5,1.5,1.5);

	//Draw Sky 
 Skybox skybox=Skybox();
 skybox.DrawSky(sky,30.0,30.0,30.0,SkyFront,SkyBack,SkyUp,SkyDown,SkyLeft,SkyRight);
	


     glPushMatrix();
 float R = 255.0f / 255.0f;
 float G= 186.0f / 255.0f;
 float P = 64.0f / 255.0f;

//	glTranslated(3.62, 5, 1.5);
 //   glScaled(5,5,5);
	//glColor3f(R, G, P);

	glTranslated(0, 0, 0);
	//gluSphere(b, 1.5, 20, 20);
	drawMySpher(b,0,0,0,1.5, 20, 20,0,0,0,Dom);
	
	glPopMatrix();
	
		glPushMatrix();

	  /*R = 223.0f / 255.0f;
	    G= 196.0f / 255.0f;
	    P = 142.0f / 255.0f;
       glColor3f(R, G, P);*/


   //around dom
	glScaled(5,5,5);
	glRotated(90,1,0,0);
	
	//gluCylinder(b, 0.32,0.32,0.06, 20, 20);
	drawMyCylinder(b,0,0,0.05,0.32,0.32,0.05,0,0,0,Dom);
	glPopMatrix();


	//nick   Dom Wall2
	glPushMatrix();
	
/*	R = 144.0f / 255.0f;
    G= 148.0f / 255.0f;
    P = 186.0f / 255.0f;
glColor3f(R, G, P);*/

	glScaled(5,5,5);
	glRotated(90,1,0,0);
	glTranslated(0,0, -0.0000000000000005);
	glScaled(1,1,0.5);


	//gluCylinder(b, 0.3,0.3,1, 20, 20);
	drawMyCylinder(b,0,0,0.15,0.3,0.3,0.4,0,0,0,Wall3);
	glPopMatrix();


//big
	glPushMatrix();
	glTranslated(0,0.4,0);
/* R = 133.0f / 255.0f;
 G= 132.0f / 255.0f;
 P = 156.0f / 255.0f;
glColor3f(R, G, P);*/

	glTranslated(0, -3, 0);
	glScaled(5,5,5);
	glRotated(270,1,0,0);
	//gluCylinder(b, 0.7,0.2,0.3, 20, 20);
	drawMyCylinder(b,0,0,0.05,0.72,0.2,0.3,0,0,0,Wall3);
	glPopMatrix();

	//helal
	glPushMatrix();
		/* R = 248.0f / 255.0f;
         G= 255.0f / 255.0f;
         P = 64.0f / 255.0f;
         glColor3f(R, G, P);*/
    glTranslated(0, -3, 0);
    glScaled(5,5,5);
	glRotated(270,1,0,0);
	
	//gluCylinder(b, 0.02,0.02,1, 20, 20);
	drawMyCylinder(b,0,0,0,0.02,0.02,1,0,0,0,Dom);

	glPopMatrix();

	
	glTranslated(-3.62,- 5, -1.5);

	glPushMatrix();
  /*  R = 104.0f / 255.0f;
  G= 107.0f / 255.0f;
  P = 134.0f / 255.0f;*/
  
    //Down 8poly 
	primitiveDrawer.Draw8poly(a,B,c,d,e,f,g,H,Carpet);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0.7,0);

	//Top 8poly 
//	primitiveDrawer.Draw8poly(i,j,k,l,m,n,o,p,R, G, P);
	glPopMatrix();
/* R = 181.0f / 255.0f;
 G= 163.0f / 255.0f;
 P = 120.0f / 255.0f;*/

	primitiveDrawer.DrawQuad(a,B,j,i,Wall1);
        //primitiveDrawer.DrawQuad(c,d,l,k,R, G, P);
 primitiveDrawer.DrawQuad(c,c2,k2,k,Wall1);
 primitiveDrawer.DrawQuad(d2,d,l,l2,Wall1);
 primitiveDrawer.DrawQuad(e,f,n,m,Wall1);
 primitiveDrawer.DrawQuad(g,H,p,o,Wall1);
 primitiveDrawer.DrawQuad(a,H,p,i,Wall1);
 primitiveDrawer.DrawQuad(B,c,k,j,Wall1);
 primitiveDrawer.DrawQuad(d,e,m,l,Wall1);
 primitiveDrawer.DrawQuad(f,g,o,n,Wall1);

    /*
	 R = 89.0f / 255.0f;
	 G= 134.0f / 255.0f;
	 P = 123.0f / 255.0f;   */


 
glPushMatrix();
glTranslated(0,1,0);

primitiveDrawer.DrawQuad(a,B,j,i,Wall2);
primitiveDrawer.DrawQuad(c,d,l,k,Wall2);
primitiveDrawer.DrawQuad(e,f,n,m,Wall2);
primitiveDrawer.DrawQuad(g,H,p,o,Wall2);
primitiveDrawer.DrawQuad(a,H,p,i,Wall2);
primitiveDrawer.DrawQuad(B,c,k,j,Wall2);
primitiveDrawer.DrawQuad(d,e,m,l,Wall2);
primitiveDrawer.DrawQuad(f,g,o,n,Wall2);
glPopMatrix();


// Door
glPushMatrix();
 if(open<4.11){
 glTranslated(open,0,0); 
// primitiveDrawer.DrawQuad(a1,j1,i1,B1,1.0, 0.0, 1.0);
 }
 glPopMatrix();


 

  //Draw Stair 
 Stair stair=Stair();
 //stair.DrawQuad(c,d,d3,c3,StairsTexture);
 stair.DrawQuad(d3,2,3,2,StairsTexture,SkyDown);
 glPopMatrix();

	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Example", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

