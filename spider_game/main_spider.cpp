#include <iostream>

#include <windows.h>
#include <glut.h>
#include "math.h"
#include"RGBA.h"
#include "spider.h"
#include "wav.h"

int width = 400;
int height = 400;



void myinit(void);
void draw_bullet( float x, float y );



void pressKeyControls(int key, int x, int y);
void releaseKeyControls(int key, int x, int y);

//Global variables for sprite SPIDER

Spider s(Point2 (0.0,0.0));


//Global variables for sprite BULLET
float bullet_posx=.0f;	// center
float bullet_posy=-183.0f;	// bottom
float bullet_horizontal_velocity=.0f; // does not move
float bullet_speed=1000.0f;
bool is_firing=false;	// true when firing


void display(){

     glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    	
		//glPushMatrix();
		  s.render();//drawSpider();
		//glPopMatrix();

		draw_bullet(bullet_posx, bullet_posy);
		
	glutSwapBuffers();
}

void draw_bullet( float x, float y )
{
    glPushMatrix();
    

    glColor3f( .5, .4, .0);	// the head
    glBegin( GL_TRIANGLES);
        glVertex2f( x, y);
        glVertex2f( x-3, y-5);
        glVertex2f( x+3, y-5);

    glEnd();

    glBegin( GL_POLYGON);	// the shell
        glVertex2f( x+3, y-5);                                        
		glVertex2f( x-3, y-5);
        glVertex2f( x-3, y-15);
        glVertex2f( x+3, y-15);
    glEnd();
    glPopMatrix();
}

float gettime()
{
    static __int64 i64Frequency=0;
    static __int64 i64BeginCount=0;
    if (i64Frequency==0){	// do this only for the first time
        QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
       QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount); //retrieve the number of
												//ticks since system start (64bit int).

    }
    __int64 i64CurrentCount;
    QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
    return  (float)(i64CurrentCount-i64BeginCount)/i64Frequency;
}
void move(int value)
{
	
	static float prevtime=0.0f;		// previous frame’s time
    float currtime = gettime();		// current frame’s time
    float elapsedtime = currtime - prevtime;	// elapsed time

    				// Spider speed is constant

    
	/**************Do all this stuff here if spider is alive****************/
	    //  Calculate dx dy for spider either by changing theta randomly or
	    //  by changing rate of theta randomly
	    //  Update Posx,Posy for spider
        //  Perform boundary check so spiders couldn't escape from world window
	    //  reverse the direction of spider when it hits world boundary
		
	/********************************************************/
	
	/**************Do all this stuff here if bullet is firing****************/
	
	      //update bullets y bc it only fires vertically
	      // check if bullet move out of windo  fire ends
    /********************************************************/

    // Finally perform collision detection i.e postion of bullet and spider collapse or 
	// the the difference b/w the bullet position and spider positon < 2 pixels

				
	
	
	
    prevtime=currtime;
	glutPostRedisplay();
}
void pressKeyControls(int key, int x, int y){

	//move left
	if(key == GLUT_KEY_LEFT){
		bullet_horizontal_velocity = -800.0f;
	}
	//move right
	if(key == GLUT_KEY_RIGHT){
		bullet_horizontal_velocity = 800.0f;
	}
	if(key == GLUT_KEY_UP){
		is_firing = true;
	}
	glutPostRedisplay();
}


//stop moving when release key
void releaseKeyControls(int key, int x, int y){

	if(key == GLUT_KEY_LEFT){
		bullet_horizontal_velocity = .0f;
	}
	
	if(key == GLUT_KEY_RIGHT){
		bullet_horizontal_velocity = .0f;
	}
	glutPostRedisplay();
}

void myinit()
{
	
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL,1.0); 
  	glClearColor( 1.0, 1.0, 1.0, 1.0);  //Set the clear color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(-12, width, -12,height); // The para are: (left, right, bottom, top)
   PlayBackgroundSound("backmusic.wav");

}
void reshape(int w, int h)		// called whenever the
{					// window is resized
    width=w;
    height=h;
	bullet_posy = -(height/2) + 13; //update bullet y position upon reshape

    glViewport(0,0,w,h);			// use the entire window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);	// maintain unit-pixel proj.
    glMatrixMode(GL_MODELVIEW);
}

int  main(int argc, char** argv)
{
  	glutInit( &argc, argv);          // Initialize GLUT function callings

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Set window size (width, height) in number of pixels  	
	glutInitWindowSize( 400, 400);   

	// Specify window position, from the left and top of the screen,
  	glutInitWindowPosition( 200, 100);        // in numbers of pixels 

	// Specify a window creation event 
  	glutCreateWindow( "2D game"); 

	//Specify the drawing function, called when the window 
 	glutDisplayFunc( display);         // is created or re-drew

	//glutTimerFunc(0,move,1);
	glutTimerFunc(200,move,1);

	glutSpecialFunc(pressKeyControls);
	glutSpecialUpFunc(releaseKeyControls); 

	glutReshapeFunc( reshape );

 	myinit();		      //Invoke this function for initializaton	

	glutMainLoop();           // Enter the event processing loop

  	return 0;                     // ANSI C requires main() to return an int
}