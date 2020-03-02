#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawaxes;
double posx=100;
double posy=100;
double posz=0;
double lx=-1/sqrt(2);
double ly=-1/sqrt(2);
double lz=0;
double rx=-1/sqrt(2);
double ry=1/sqrt(2);
double rz=0;
double ux=0;
double uy=0;
double uz=1;
double angle=0;
double theta=0;
double car1=0;
double car2=0;
double car3=0;
double car4=0;
double forwardmove=0;
int indicator=0;
struct point
{
    double x,y,z;
};
void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);
            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);
            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }
        glEnd();
    }
}
void drawCube(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a, a);
        glVertex3f( a,-a,a);
        glVertex3f(-a,-a,a);
        glVertex3f(-a, a,a);
        glVertex3f( a, a, -a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f( a, a, a);
        glVertex3f(a, a,-a);
        glVertex3f(a,-a,-a);
        glVertex3f(a,-a, a);
        glVertex3f( -a, a, a);
        glVertex3f(-a, a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
        glVertex3f( a,a, a);
        glVertex3f( a,a,-a);
        glVertex3f(-a,a,-a);
        glVertex3f(-a,a, a);
        glVertex3f( a,-a, a);
        glVertex3f( a,-a,-a);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
    }
    glEnd();
}
void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    for(i=0; i<=segments; i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    for(i=0; i<segments; i++)
    {
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,height/2);
            glVertex3f(points[i+1].x,points[i+1].y,height/2);
            glVertex3f(points[i].x,points[i].y,-height/2);
            glVertex3f(points[i+1].x,points[i+1].y,-height/2);
        }
        glEnd();
    }
}
void drawSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
    int i,j;
    double h,r;
    for(i=0; i<=stacks; i++)
    {
        h=radius*sin(((double)i/(double)stacks)*(pi/2));
        r=radius*cos(((double)i/(double)stacks)*(pi/2));
        for(j=0; j<=slices; j++)
        {
            points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
            points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
            points[i][j].z=h;
        }
    }
    for(i=0; i<stacks; i++)
    {
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        for(j=0; j<slices; j++)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
            }
            glEnd();
        }
    }
}
drawJeep(double js)
{
    //main box
    glPushMatrix();
    {
        glTranslatef(0,35,0);
        glScalef(1.5,1,1);
        drawCube(js);
    }
    glPopMatrix();
    //front box
    glPushMatrix();
    {
        glTranslatef(40,25,0);
        glScalef(1,.5,1);
        drawCube(js);
    }
    glPopMatrix();
}
void drawWheel()
{
    // 1st tire
    glPushMatrix();
    {
        glTranslatef(-10,0,18);
        glColor3f(0,0,1); //RGB
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //2nd tire
    glPushMatrix();
    {
        glTranslatef(-10,0,-18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //3rd tire
    glPushMatrix();
    {
        glTranslatef(40,0,18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
    //4th tire
    glPushMatrix();
    {
        glTranslatef(40,0,-18);
        glColor3f(0,0,1);
        glRotatef(theta,0,0,1);
        drawCylinder(15,4,15);
    }
    glPopMatrix();
}
void drawHuman()
{
    glPushMatrix();
    {
        glTranslatef(-80,0,130);
        glScalef(.4,.4,.4);
        glPushMatrix(); //1st feet
        {
            glTranslatef(-20,-30,0);
            glScalef(.5,.2,.7);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); //2nd feet
        {
            glTranslatef(20,-30,0);
            glScalef(.5,.2,.7);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // 1st leg
        {
            glTranslatef(20,0,-10);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,60,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd leg
        {
            glTranslatef(-20,0,-10);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,60,20);
        }
        glPopMatrix();
        glPushMatrix(); // body
        {
            glTranslatef(0,60,-5);
            glScalef(1.5,1.6,.7);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); //1st hand 1st part
        {
            glTranslatef(40,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); //1st hand 2nd part
        {
            glTranslatef(55,95,-10);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd hand 1st part
        {
            glTranslatef(-50,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // 2nd hand 2nd part
        {
            glTranslatef(-70,80,-10);
            glRotatef(90,0,0,1);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(8,40,20);
        }
        glPopMatrix();
        glPushMatrix(); // head
        {
            glTranslatef(0,110,-10);
            drawSphere(20,20,20);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawRoad()
{
    glPushMatrix(); // Draw the main ground
    {
        glTranslatef(0,-100,0);
        glScalef(20,.001,15);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road of over-bridge on the ground
    {
        glTranslatef(0,-99,0);
        glScalef(20,.001,7);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the road on the ground
    {
        glTranslatef(-100,-99,0);
        glScalef(5,.001,15);
        glColor3f(1,0,0);
        drawCube(20);
    }
    glPopMatrix();

}
void drawFootpath()
{
    glPushMatrix(); // Draw front left footpath 1
    {
        glTranslatef(-220,-99,220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left footpath 2
    {
        glTranslatef(-320,-99,160);
        glScalef(4,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 1
    {
        glTranslatef(20,-99,220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right footpath 2
    {
        glTranslatef(220,-99,170);
        glScalef(9,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 1
    {
        glTranslatef(-220,-99,-220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left footpath 2
    {
        glTranslatef(-320,-99,-160);
        glScalef(4,.001,1);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 1
    {
        glTranslatef(20,-99,-220);
        glScalef(1,.001,4);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right footpath 2
    {
        glTranslatef(220,-99,-170);
        glScalef(9,.001,1.5);
        glColor3f(0,0,1);
        drawCube(20);
    }
    glPopMatrix();
}
void drawPolicebox()
{
    glPushMatrix(); // Draw the base of the police box
    {
        glTranslatef(-100,-85,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front left pole
    {
        glTranslatef(-140,-10,45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw front right pole
    {
        glTranslatef(-55,-10,45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back left pole
    {
        glTranslatef(-140,-10,-45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw back right pole
    {
        glTranslatef(-55,-10,-45);
        glRotatef(90,1,0,0);
        glColor3f(1,0,1);
        drawCylinder(5,140,10);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the roof of the police box
    {
        glTranslatef(-100,50,0);
        glScalef(1,.3,1);
        glColor3f(1,.5,0);
        drawCube(50);
    }
    glPopMatrix();
}
void drawOverbridge()
{
    glPushMatrix();
    {
        glTranslatef(75,0,0);
        glPushMatrix(); // draw the main box of over-bridge
        {
            glTranslatef(130,50,0);
            glScalef(2,.2,7);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 1
        {
            glTranslatef(95,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side of main box of over-bridge 2
        {
            glTranslatef(95,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 1
        {
            glTranslatef(165,90,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side of main box of over-bridge 2
        {
            glTranslatef(165,70,0);
            glScalef(.1,.1,7.2);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side front edge of main box of over-bridge
        {
            glTranslatef(100,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side middle edge of main box of over-bridge
        {
            glTranslatef(100,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back edge of main box of over-bridge
        {
            glTranslatef(100,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side front edge of main box of over-bridge
        {
            glTranslatef(160,70,138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side middle edge of main box of over-bridge
        {
            glTranslatef(160,70,0);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back edge of main box of over-bridge
        {
            glTranslatef(160,70,-138);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front pillar
        {
            glTranslatef(130,-30,170);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back pillar
        {
            glTranslatef(130,-30,-170);
            glRotatef(90,1,0,0);
            glColor3f(1,0,1);
            drawCylinder(20,150,10);
        }
        glPopMatrix();
        glPushMatrix(); // draw the front box of over-bridge
        {
            glTranslatef(130,50,160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the back box of over-bridge
        {
            glTranslatef(130,50,-160);
            glScalef(2,.2,1);
            glColor3f(1,1,0);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of front box
        {
            glTranslatef(130,0,270);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); // draw the side of back box
        {
            glTranslatef(130,0,-80);
            glScalef(.28,1,1);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glTranslatef(95,90,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glScalef(.1,.1,7);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,0);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
            glPushMatrix();
            {
                glTranslatef(95,70,-138);
                glRotatef(90,0,0,1);
                glScalef(1,.1,.1);
                glColor3f(1,1,1);
                drawCube(20);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front left
    {
        glTranslatef(105,-25,160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of front right
    {
        glTranslatef(305,-25,160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back left
    {
        glTranslatef(105,-25,-160);
        glRotatef(50,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // Draw the slide of back right
    {
        glTranslatef(305,-25,-160);
        glRotatef(310,0,0,1);
        glScalef(5,.2,1);
        glColor3f(1,1,0);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 1
    {
        glTranslatef(40,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front lower edge 2
    {
        glTranslatef(40,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 1
    {
        glTranslatef(103,15,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 2
    {
        glTranslatef(105,-5,175);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 3
    {
        glTranslatef(103,15,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the left side front slider hand 4
    {
        glTranslatef(105,-5,145);
        glRotatef(50,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the left side back lower edge 1
        {
            glTranslatef(40,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back lower edge 2
        {
            glTranslatef(40,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 1
        {
            glTranslatef(103,15,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 2
        {
            glTranslatef(105,-5,175);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 3
        {
            glTranslatef(103,15,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the left side back slider hand 4
        {
            glTranslatef(105,-5,145);
            glRotatef(50,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 1
    {
        glTranslatef(370,-80,175);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front lower edge 2
    {
        glTranslatef(370,-80,145);
        glRotatef(90,0,0,1);
        glScalef(1,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 1
    {
        glTranslatef(305,15,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 2
    {
        glTranslatef(305,15,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 3
    {
        glTranslatef(300,3,175);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix(); // draw the right side front slider hand 4
    {
        glTranslatef(303,0,145);
        glRotatef(310,0,0,1);
        glScalef(5,.1,.1);
        glColor3f(1,1,1);
        drawCube(20);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0,0,-320);
        glPushMatrix(); // draw the right side back lower edge 1
        {
            glTranslatef(370,-80,175);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back lower edge 2
        {
            glTranslatef(370,-80,145);
            glRotatef(90,0,0,1);
            glScalef(1,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 1
        {
            glTranslatef(305,15,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 2
        {
            glTranslatef(305,15,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 3
        {
            glTranslatef(303,3,175);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
        glPushMatrix(); // draw the right side back slider hand 4
        {
            glTranslatef(300,0,145);
            glRotatef(310,0,0,1);
            glScalef(5,.1,.1);
            glColor3f(1,1,1);
            drawCube(20);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawCars()
{
    glPushMatrix();
    {
        glScalef(.8,.8,.8);
        glPushMatrix(); //car 1
        {
            glTranslatef(car1,0,0);
            glTranslatef(-450,-100,-100);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); //car 2
        {
            glTranslatef(car2,0,0);
            glTranslatef(450,-100,170);
            glRotatef(180,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); //car 3
        {
            glTranslatef(0,0,car3);
            glTranslatef(-30,-100,-200);
            glRotatef(270,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
        glPushMatrix(); //car 4
        {
            glTranslatef(0,0,car4);
            glTranslatef(-220,-100,350);
            glRotatef(90,0,1,0);
            glPushMatrix();
            {
                glColor3f(0,1,1);
                drawJeep(20);
                drawWheel();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}
void drawPoliceman()
{
    glPushMatrix();
    {
        drawHuman();
    }
    glPopMatrix();
}
void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case 'q':
        posx=posx+lx;
        posy=posy+ly;
        posz=posz+lz;
        break;
    case 'w':
        posx=posx-lx;
        posy=posy-ly;
        posz=posz-lz;
        break;
    case 'a':
        posx=posx+rx;
        posy=posy+ry;
        posz=posz+rz;
        break;
    case 's':
        posx=posx-rx;
        posy=posy-ry;
        posz=posz-rz;
        break;
    case 'z':
        posx=posx+ux;
        posy=posy+uy;
        posz=posz+uz;
        break;
    case 'x':
        posx=posx-ux;
        posy=posy-uy;
        posz=posz-uz;
        break;

    default:
        break;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(00,200,700,	0,0,0,	0,1,0);
    //gluLookAt(posx,posy,posz,	posx+lx,posy+lz,posz+lz,	0,1,0);
    glMatrixMode(GL_MODELVIEW);
    drawAxes();
    drawRoad();
    drawFootpath();
    drawPolicebox();
    drawOverbridge();
    drawCars();
    drawPoliceman();
    glutSwapBuffers();
}
void animate()
{
    theta=theta-0.3;
    forwardmove=((2*pi*15)/360)*0.3;
    car1=car1+forwardmove;
    if(car1>850)
    {
        car1=0;
    }
    car2=car2-forwardmove;
    if(car2<-850)
    {
        car2=0;
    }
    car3=car3+forwardmove;
    if(car3>520)
    {
        car3=0;
    }
    car4=car4-forwardmove;
    if(car4<-520)
    {
        car4=0;
    }
    glutPostRedisplay();
}
void init()
{
    drawaxes=0;
    cameraHeight=150.0;
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1300, 900);
    glutInitWindowPosition(0,100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("My OpenGL Program");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}
