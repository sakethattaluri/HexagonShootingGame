#include<iostream>
#include<math.h>
#include<string.h>
#include<windows.h>
#include <stdlib.h>
#include <time.h>
#include<GL/glut.h>
using namespace std;

class rocket{                                                                //class for the counterMissiles of the rocket
	public: 
		int posX,posY;
		float xcr,ycr,xr=0.0,yr=0.0;
		void set(float xm,float ym){
			posX = xm*2500;
			posY = ym*2500;
			xcr = -4*xm;
			ycr=-4*ym;
		}
		void drawCMissile(){                                                //draws the counterMissile
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glClear(GL_DEPTH_BUFFER_BIT);
    			glTranslatef(xr,yr,0.0);
    			glColor3f(0.0,0.0,1.0);
    			drawCircleRocket(2.0);
    		glPopMatrix();
    		glFinish();
		}
		void drawCircleRocket(float radius){
    		float x1,y1,x2,y2;
			float angle;
			glBegin(GL_TRIANGLE_FAN);
 
   			for (int i=0; i<360; i++){
      			float degInRad = i*3.14159/180;
      			glVertex2f(posX+cos(degInRad)*radius,posY+sin(degInRad)*radius);
  			 }
 
   			glEnd();
		}
};
void drawBlast(float a,float b){
    		float x1,y1,x2,y2;
			float angle;
			glBegin(GL_TRIANGLE_FAN);
            glColor3f(1,0,0);
   			for (int i=0; i<360; i++){
      			float degInRad = i*3.14159/180;
      			glVertex2f(a+cos(degInRad)*5,b+sin(degInRad)*5);
  			 }
 
   			glEnd();
		}
float a = 50.0,b=10.0,c = 7.5,d=10.0,theta = 0,x[6],y[6],abk1,abk2;
float rt3 = 1.73205,pi = 3.1415, xR=0.0, yR=0.0,zR=0.0,xR1=0.0, yR1=0.0,zR1=0.0;
float DEG2RAD = 3.14159/180;
int status = 0,k=0,u,var=0,cR=0,abk,score=0,rscore=0,lifes=3,rlifes=1,mc=0,mVar=0,rot = 0,blast=0;
rocket *cRocket[100];                                                            //object for counterMissile

float abs(float temp){                                                           //returns the absolute value
	if(temp>0) return temp;
	else return -temp;
}

void drawCircle(float radius,float x, float y){                                 //draws the missile
    float x1,y1,x2,y2;
	float angle;
	glBegin(GL_TRIANGLE_FAN);
 
   for (int i=0; i<360; i++){
      float degInRad = i*DEG2RAD;
      glVertex2f(x+cos(degInRad)*radius,y+sin(degInRad)*radius);
   }
 
   glEnd();
}

void hexagon(){                                                  				//draws the hexagon frontier
	glColor3f(0.5f, 0.4f, 0.3f);
	glBegin(GL_POLYGON);
    	glVertex2f(-a/2,-rt3/2*a);
    	glVertex2f(a/2,-rt3/2*a);
    	glVertex2f(a,0.0);
    	glVertex2f(a/2,rt3/2*a);
    	glVertex2f(-a/2,rt3/2*a);
    	glVertex2f(-a,0.0);
    glEnd();
}
void triangle(){                                                			 //draws the shape of the rocket
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_TRIANGLES);
    	glVertex2f(0,-rt3/2*a);
    	glVertex2f(b/2,-rt3/2*(a+b));
    	glVertex2f(-b/2,-rt3/2*(a+b));
    	
    	glVertex2f(b/2,-rt3/2*(a+1.5*b));
    	glVertex2f((b+c)/2,-rt3/2*(a+2.5*b));
    	glVertex2f(b/2,-rt3/2*(a+2.5*b));
    	
    	glVertex2f(-b/2,-rt3/2*(a+1.5*b));
    	glVertex2f(-(b+c)/2,-rt3/2*(a+2.5*b));
    	glVertex2f(-b/2,-rt3/2*(a+2.5*b));
    glEnd();
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    	glVertex2f(b/2,-rt3/2*(a+b));
    	glVertex2f(-b/2,-rt3/2*(a+b));
    	glVertex2f(-b/2,-rt3/2*(a+3*b));
    	glVertex2f(b/2,-rt3/2*(a+3*b));
    	
    	glColor3f(1.0f, 0.2f, 0.05f);
    	glVertex2f(-b/2,-rt3/2*(a+3*b));
    	glVertex2f(b/2,-rt3/2*(a+3*b));
    	glVertex2f(b/2+c,-rt3/2*(a+3*b+d));
    	glVertex2f(-b/2-c,-rt3/2*(a+3*b+d));
    glEnd();
}
void Sprint(float x, float y, char *st)
{
        int l, i;
        l = strlen(st); // see how many characters are in text string.
        glRasterPos2f(x, y); // location to start printing text
        for (i = 0; i < l; i++) // loop until i is greater then l
        {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
        }

}
void Sprint1(float x, float y, char *st)
{
        int l, i;
        l = strlen(st); // see how many characters are in text string.
        glRasterPos2f(x, y); // location to start printing text
        for (i = 0; i < l; i++) // loop until i is greater then l
        {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, st[i]); // Print a character on the screen
        }

}
void shape(float th){                                                 //calls functions to draw hexagon and rocket with rotation and translation
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	hexagon();
	glPushMatrix();
    	if(k!=0) {
    		glRotatef(th*180/pi,0.0,0.0,1.0);
    	}
		triangle();
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 0.6f);
    Sprint(-75,75,"Score:");
        char cstr[2],cstr1[2];
	    itoa(score,cstr,10);
	    Sprint(-55,75,cstr);
	    Sprint(0,75,"Lives:");
	    itoa(lifes,cstr1,10);
	    Sprint(20,75,cstr1);
    glFlush();
}


void missile(float r,float g,float b){                                  //draws the Enemy missile
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix();
		glClear(GL_DEPTH_BUFFER_BIT);
    	glTranslatef(xR,yR,zR);
    	glColor3f(r,g,b);
    	drawCircle(2.0,0,0);
    glPopMatrix();
    glFinish();
}

void kboard(unsigned char key, int p, int q){                          //Keyboard functions
	int kb = key;
	switch(kb){ 
		case 100:                                                      //to rotate rocket in clockwise direction
			status = (status+1)%6;
			k=1;
			theta = status*pi/3;
			shape(status*pi/3);
			break;
		case 97:                                                      //to rotate rocket in Anti-clockwise direction
			status = (status-1)%6;
			if(status<0) status = status+6;
			k=1;
			theta = status*pi/3;
			shape(status*pi/3);
			break;
		case 32:                                                      //to shoot the CounterMissiles
			cRocket[cR] = new rocket();
			abk = (int)(theta*3/pi);
			if(theta*3/pi>4.5&&abk==4) abk=5;
			if(abk<0) abk = abk+6;
			abk1 = x[abk];abk2 = y[abk];
			cRocket[cR]->set(abk1,abk2);
			cRocket[cR]->drawCMissile();
			cR++;
			if(cR>3){
			 // delete cRocket[0];
			  cR=0;
			}
			break;
		default:
			break;
	}
}
void intro(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0,0.5,1.0);
	Sprint(-40,35,"Hexagon Shooting Game");
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glRotatef(rot,0.0,0.0,1.0);
	glBegin(GL_POLYGON);
        glVertex2f(-a/8,-rt3/8*a-10);
    	glVertex2f(a/8,-rt3/8*a-10);
    	glVertex2f(a/4,0.0-10);
    	glVertex2f(a/8,rt3/8*a-10);
    	glVertex2f(-a/8,rt3/8*a-10);
    	glVertex2f(-a/4,0.0-10);
    glEnd();
    glPopMatrix();
    glColor3f(1.0,1.0,1.0);
    Sprint1(-5,0,"PLAY");
	glFlush();
}
void welcome(){                                                                     //Start Screen
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 0.0f, 1.0f);
	intro();
}
void idleFunc(){
	if(mVar == 0){
		rot += 6;
		if(rot == 360) rot = 0;
		intro();
	}
	else{
		xR += 5*x[u];yR += 5*y[u];
		if(sqrt(xR*xR+yR*yR)<=rt3*a/2){
			missile(1,1,0.6);	
		}
		else{
	    	if(rlifes>0){
	    		lifes--;
	    		xR=0;yR=0;
				srand (time(NULL));
				u = rand()%6;
	    		rlifes=0;
	   		}
	    if(lifes==0){
			Sprint(-75,75,"Score:");
        	char cstr[2],cstr1[2];
	    	itoa(score,cstr,10);
	    	Sprint(-55,75,cstr);
	    	Sprint(0,75,"Lives:");
	    	itoa(lifes,cstr1,10);
	    	Sprint(20,75,cstr1);
	    	Sprint(55,75,"Game Over!");
	    	if(rscore==0){
	    		cout<<"Score:"<<score;    
	    		rscore++;
	    		Sleep(1000);
	    		exit(0);
	    	}
	    }   
	    return;
		}
		rlifes=1;
			Sprint(-75,75,"Score:");
        	char cstr[2],cstr1[2];
	    	itoa(score,cstr,10);
	    	Sprint(-55,75,cstr);
	    	Sprint(0,75,"Lives:");
	    	itoa(lifes,cstr1,10);
	    	Sprint(20,75,cstr1);
		for(int k=0;k<cR;k++){
			cRocket[k]->xr += cRocket[k]->xcr;
			cRocket[k]->yr += cRocket[k]->ycr;
			float sx = abs(cRocket[k]->posX+cRocket[k]->xr);
			float sy = abs(cRocket[k]->posY+cRocket[k]->yr);
			if(abs(cRocket[k]->posX+cRocket[k]->xr)<=abs(xR)&&abs(cRocket[k]->posY+cRocket[k]->yr)<=abs(yR)&&status==u){
				delete cRocket[k];
				drawBlast(xR,yR);
				xR=0;yR=0;
				srand (time(NULL));
				u = rand()%6;
				score++;                                                
			}
			else if(sqrt(sx*sx+sy*sy)<=1.0){	
				delete cRocket[k];
			}
			cRocket[k]->drawCMissile();
		}
		shape(theta);
	}
}

void display(){
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 0.0f, 1.0f);
    shape(0);
}

void init(){
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
        glutInitWindowSize(600, 600);        
        glutInitWindowPosition(100, 100);      
}
void enter(){
	init();
	glutCreateWindow("Hexagon_Shooting_Game");              
        glutDisplayFunc(display);
		glutKeyboardFunc(kboard);
		Sprint(-75,75,"Score:");
        char cstr[2],cstr1[2];
	    itoa(score,cstr,10);
	    Sprint(-55,75,cstr);
	    Sprint(0,75,"Lifes:");
	    itoa(lifes,cstr1,10);
	    Sprint(20,75,cstr1);
		x[0]=0;y[0]=-(rt3*a)/5000;x[1]=3*a/(4*2500);y[1]=-rt3*a/(4*2500);x[2]=3*a/(4*2500);y[2]=rt3*a/(4*2500);x[3]=0;y[3]=(rt3*a)/5000;x[4]=-3*a/(4*2500);y[4]=rt3*a/(4*2500);x[5]=-3*a/(4*2500);y[5]=-rt3*a/(4*2500);
		glutIdleFunc(idleFunc);   
}
void play(int button, int state, int x, int y){
	if(abs(x)<=360 && abs(x)>=240 && abs(y)<=360 && abs(y)>=240 && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		mVar=1;
	   enter();
	}
}
int main(int argc, char** argv){
        glutInit(&argc, argv);  
        init();
        glutCreateWindow("Hexagon_Shooting_Game");
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glutDisplayFunc(welcome);
        glutIdleFunc(idleFunc);  
        glutMouseFunc(play);                   
        glutMainLoop();                        
        return 0;
}
