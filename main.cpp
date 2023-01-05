#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, Calpha= 360.0, C_hr_alpha=360.0 ,angle = 3 , Y = 0;
GLboolean bRotate = false, fRotate= true, cRotate= true, xz_rotate=false,l_on=true;
GLboolean amb=true, spec=true, dif=true;
GLfloat x = -16;
GLfloat y = 20;
GLfloat z = -40;
// new commit 1
// Velocity of the ball
float vx = 0.1f;
float vy = 0.1f;
float vz = 0.1f;
// new commit 2
// Acceleration of the ball
float ax = 0.0f;
float ay = -0.001f;
float az = 0.0f;
// new commit 3
// Radius of the ball
float radius = 0.1f;

bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;
double spt_cutoff=40;
GLfloat eyeX = 5;
GLfloat eyeY = 15;
GLfloat eyeZ = -30;
GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;
//////////v_cube X, Y and Z////////////
static GLfloat v_Cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {0.0, 2.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 2.0, 0.0},
    {0.0, 2.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 2.0, 2.0}
};

//////////getting the indices to draw v_cube////////////
static GLubyte quadIndices[6][4] =
{
    {1, 4, 7, 6},
    {7, 4, 2, 5},
    {3, 5, 2, 0},
    {3, 6, 7, 5},
    {0, 2, 4, 1},
    {1, 6, 3, 0}
};
/////// normal vector for faces of the cube//////////
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

////////////cube function to give a cube with ambient,diffuse, specular and shininess with arguments of 3 colors////////////
void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3)
{



    GLfloat cube_no[] = {0.2, 0, 0, 1.0};
    GLfloat cube_amb[] = {colr1*0.3,colr2*0.3,colr3*0.3,1};
    GLfloat cube_dif[] = {colr1,colr2,colr3,1};
    GLfloat cube_spec[] = {1,1,1,1};
    GLfloat cube_sh[] = {10};


    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]);
        }
    }
    glEnd();


}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, width / ar);
}
 /////////drawing the floor with scaling and translation with the help of function cube/////////
 void drawRedBookWithWhitePages() {
    // Set the color to red
    glColor3f(1.0, 0.0, 0.0);

    // Draw the front cover of the book
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Set the color to white
    glColor3f(1.0, 1.0, 1.0);

    // Draw the back cover of the book
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Set the color to red
    glColor3f(1.0, 0.0, 0.0);

    // Draw the sides of the book
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
}

void drawSphere(float radius)
{
    const int slices = 32;
    const int stacks = 16;

    glutSolidSphere(radius, slices, stacks);
}
void drawSnowman()
{
    // Draw the bottom sphere
    glPushMatrix();
    glTranslatef(-20,6,30);

    glColor3f(0.9, 0.9, 1.0);
    drawSphere(1.0);

    // Translate to the position of the middle sphere
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);

    // Draw the middle sphere
    glColor3f(1.0, 1.0, 1.0);
    drawSphere(0.75);
    // Translate to the position of the top sphere
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);

    // Draw the top sphere
    glColor3f(0.9, 0.9, 0.9);
    drawSphere(0.5);

    // Draw the nose
    glColor3f(1.0, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.2);
    glRotatef(360.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.2, 0.5, 10, 1);
    glPopMatrix();

    // Draw the eyes
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.2, 0.15, 0.5);
    drawSphere(0.1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2, 0.15, 0.5);
    drawSphere(0.1);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
void anothersnowman()
{
    glPushMatrix();
    glTranslatef(9,-4.3,-12);
    drawSnowman();
    glPopMatrix();
}

void floor()
{
    glPushMatrix();
    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(0.663, 0.663, 0.663);
    glPopMatrix();
}
void drawBall() {
  glPushMatrix();
  glTranslatef(x, y,z);
  glutSolidSphere(5, 20, 20);
  glPopMatrix();
}
void updateBall() {
  // Update the position of the ball
  x += vx;
  y += vy;
  z += vz;

  // Update the velocity of the ball
  vx += ax;
  vy += ay;
  vz += az;

  // Check for collision with the floor
  if (y < radius) {
    y = radius;
    vy = -vy;
  }
}
/////////////drawing a table using translation and scaling with the help of cube function /////////
void table()
{
/////////////base/////////
    glPushMatrix();
    glScalef(5,1, 3);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();
/////////////leg 1//////////
    glPushMatrix();
    glTranslatef(4.4,-8.5,-2);
    glScalef(0.6,8, 0.8);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();
/////////////leg 2/////////
    glPushMatrix();
    glTranslatef(-4.3,-8.5,-2);
    glScalef(0.6,8,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();

/////////leg 3///////////
    glPushMatrix();
    glTranslatef(-4.3,-8.5,2);
    glScalef(0.6,8,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();

/////////leg 4///////////
    glPushMatrix();
    glTranslatef(4.4,-8.5,2);
    glScalef(0.6,8,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();
}
///////////function to draw a chair//////////
void chair()
{
/////////upper_base///////////
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.1,5.5,-2.5);
    glScalef(3,4.5,0.5);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();
/////////base///////////
    glPushMatrix();
    glScalef(3,1,3);
    glTranslatef(-1,-1,-1);
    cube(0.722, 0.525, 0.043);
    glPopMatrix();
/////////leg 1///////////
    glPushMatrix();
    glTranslatef(2.33,-4.5,-2.1);
    glScalef(0.6,4,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();
/////////leg 2///////////
    glPushMatrix();
    glTranslatef(-2.33,-4.5,2.1);
    glScalef(0.6,4,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();
/////////leg 3///////////
    glPushMatrix();
    glTranslatef(2.33,-4.5,2.1);
    glScalef(0.6,4,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();
///////leg4///////////
    glPushMatrix();
    glTranslatef(-2.33,-4.5,-2.1);
    glScalef(0.6,4,0.8);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();
    glPopMatrix();
}

void full_set()
{
    glPushMatrix();
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-3,-8);
    chair();
    glPopMatrix();
}

void nine_full_set_chair_table()
{
    glPushMatrix();
    full_set();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,-20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,-20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0);
    full_set();
    glPopMatrix();

}
void closet()
{
    glPushMatrix();

    glPushMatrix();  //main_box
    glScalef(8,15,5);
    glTranslatef(-1,-1,-1);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix(); // closet_line
    glTranslatef(0.4,0,4.1);
    glScalef(0.2,15,0.91);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); // closet_handle_right
    glTranslatef(1.5,5,4.5);
    glScalef(0.32,1,0.91);
    glTranslatef(-1,-1,-1);
    cube(0.957, 0.643, 0.376);
    glPopMatrix();

    glPushMatrix(); // closet_handle_left
    glTranslatef(-0.6,5,4.5);
    glScalef(0.32,1,0.91);
    glTranslatef(-1,-1,-1);
    cube(0.957, 0.643, 0.376);
    glPopMatrix();

    glPopMatrix();
}
///////function to draw the wall//////////
void wall(GLfloat col1,GLfloat col2,GLfloat col3)
{
    glPushMatrix();
    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(col1, col2, col3);
    glPopMatrix();


}

void fan_leg()
{
    glPushMatrix();
    glScalef(5,0.01113,2);
    glTranslatef(-1,-1,-1);
    cube(0.392, 0.584, 0.929);
    glPopMatrix();
}

void fan_face()
{
    glPushMatrix();
    glScalef(1.5,0.2,1.5);
    glTranslatef(-1,-1,-1);
    cube(1.000, 1.000, 1.000);
    glPopMatrix();
}

void fan_stand()
{
    glPushMatrix();
    glTranslatef(0,3.5,0);
    glScalef(0.3,6,0.3);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();
}
////////////////////////function to draw fan//////////////////////
void draw_fan()
{
    glPushMatrix();
    fan_face();
    glPopMatrix();

///////////////////part1///////////////////////////////////////////
    glPushMatrix();
    glTranslatef(-6,0,0);
    fan_leg();
    glPopMatrix();
///////////////////part2///////////////////////////////////////////
    glPushMatrix();
    glTranslatef(6,0,0);
    fan_leg();
    glPopMatrix();
///////////////////part3///////////////////////////////////////////
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(6,0,0);
    fan_leg();
    glPopMatrix();
///////////////////part4///////////////////////////////////////////
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-6,0,0);
    fan_leg();
    glPopMatrix();

}

///////function to draw a fan//////////
void fan()
{
    glPushMatrix();
    glTranslatef(0,Y,-4);
    glRotatef(alpha,0,1,0);
    draw_fan();
    glPopMatrix();
    glPushMatrix();
    glColor3b(1.0,1.0,1.0);
    glTranslatef(0,2.5,-4);
    fan_stand();
    glPopMatrix();

}
void updatefan()
{
    if(Y>=-28)
        Y--;
}
///////the clock part//////////
void clock()
{
    glPushMatrix();

    glPushMatrix(); //clock_leg1

    glScalef(1.5,1,1);
    glTranslatef(-.5,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clock_leg2
    glRotatef( C_hr_alpha,0, 1, 0.0 );
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clock_leg3
    glRotatef( Calpha,0, 1, 0.0 );
    glRotatef(90,0,1,0);
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();



    glScalef(4,0.2,3.5);
    glTranslatef(-1,-1,-1);
    cube(0.000, 0.000, 0.804);

    glPopMatrix();

}
void door(float angle) {
  // Draw door
  glPushMatrix();
  glTranslatef(49, 6, 20);
  glRotatef(angle, 0, 1, 0);
  glTranslatef(-4.5, 0, -1);
  glScalef(8, 15, 0.5);
  glTranslatef(-1, -1, -1);
  cube(0.647, 0.165, 0.165);
  glPopMatrix();

  // Restore modelview matrix
  glPopMatrix();
}
void blackdoor() {

  // Draw door
  glPushMatrix();
  glTranslatef(49, 6, 20);
  glRotatef(90, 0, 1, 0);
  glTranslatef(-4.5, 0, 0);
  glScalef(8, 15, 0.5);
  glTranslatef(-1, -1, -1);
  cube(0.0, 0.0, 0.0);
  glPopMatrix();
}
void updateDoor()
{
    angle+=1;
}
void room()
{
    glPushMatrix();//front wall
    glTranslatef(0,0,45);
    glRotatef(270,1,0,0);

    glPushMatrix();//light front side
    glTranslatef(3,2,36);
    glRotatef(90,1,0,0);
    glScalef(12,.8,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glPushMatrix();  //blackboard
    glTranslatef(0,1,18);
    glScalef(30,0.5,8);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();//clock
    glPushMatrix();
    glTranslatef(3,1,31);
    clock();
    glPopMatrix();
    glPopMatrix();
    wall(1.000, 1.000, 0.878);
    glPopMatrix();   // front wall end
    glPushMatrix();
    glTranslatef(0.0,0,-50);
    glRotatef(90,1,0,0);
    wall(0.863, 0.863, 0.8630); //back  wall
    glPopMatrix();

    glPushMatrix();//left side  wall start

    glPushMatrix();//light right side
    glTranslatef(42,30,-5);
    glRotatef(90,0,1,0);
    glScalef(12,1,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glPushMatrix();
    door(angle);
    updateDoor();
    blackdoor();
    glPopMatrix();

    glTranslatef(50.0,0,-1);
    glRotatef(90,0,0,1);
    wall(1.000, 0.894, 0.882);
    glPopMatrix();//left side  wall


    glPushMatrix(); //right side wall start

    glPushMatrix();//light right side

    glTranslatef(-42,30,-5);
    glRotatef(90,0,1,0);
    glScalef(12,1,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glTranslatef(-50.0,0,-1);
    glRotatef(90,0,0,1);
    wall(1.000, 0.894, 0.882);
    glPopMatrix();//right side  wall


    glPushMatrix();

    glPushMatrix(); //top wall fan
    glScalef(0.8,1,1);
    glTranslatef(-5,30,0);
    fan();
    glPopMatrix();
    glTranslatef(0,40,-5);
    glRotatef(90,0,1,0);
    wall(0.663, 0.663, 0.663); //top  wall
    glPopMatrix();

    glPushMatrix();//floor
    glTranslatef(0,-10,0);
    glPushMatrix();// teacher floor
    glTranslatef(-40,2,25);
    glScaled(40,1,10);
    cube(0.647, 0.165, 0.165);
    glPopMatrix();
    floor();
    glPopMatrix();

}
///////function to draw the whole class////////
void classRoom()
{
    glPushMatrix();
    room();
    glPopMatrix();

    glPushMatrix();   //teachers desk
    glScalef(1.5,1,1);
    glRotatef(180,0,1,0);
    glTranslatef(15,4,-30);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,-5);
    glScalef(1.2,1,1.2);
    nine_full_set_chair_table();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.2,1.4,1);
    glTranslatef(-35,0,10);
    glRotatef(90,0,1,0);
    closet();
    glPopMatrix();

}
////////////the light part//////////
void light()
{

    //light

    GLfloat l_amb[] = {0.5, 0.2, 0.2, 1.0};
    GLfloat l_dif[] = {0.961, 0.871, 0.702};
    GLfloat l_spec[] = {10,0.2,0.2,1};
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_pos1[] = {20,20,20,1.0}; //front side light
    GLfloat l_pos2[] = {44,30,-5,1.0}; //right side
    GLfloat l_pos3[] = {10,60,-30,1.0}; //left side

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);

    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);



    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
        }

    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
    }

    glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0); //eyeX,eyeY,eyeZ //5,10,-20
    glRotatef(theta,axis_x,axis_y,0);

    // Draw the snowman
    drawSnowman();
    anothersnowman();
    light();
    classRoom();
    drawRedBookWithWhitePages();
    drawBall();
    updateBall();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'r'://camera rotation
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
    case 'f': //fan
        fRotate = !fRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case '+': //zoom in
        eyeZ++;
        lookZ++;
    case 'y': //zoom in
        updatefan();
        break;
    case '-': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case '*': //go up
        eyeY++;
        lookY++;
        break;
    case '/': //go down
        eyeY--;
        lookY--;
        break;

    case 'x'://move left
        eyeX++;
        lookX++;
        break;
    case 'z': //move right
        eyeX--;
        lookX--;
        break;

    case '1': //light
        l_on1=!l_on1;
        break;
    case '2':
        l_on2=!l_on2;
        break;
    case '3':
        l_on3=!l_on3;
        break;

    case 'a':  //poperties of light
        amb= !amb;
        break;
    case 's':
        spec =!spec;
        break;
    case 'd':
        dif=!dif;
        break;

    case 27:	// Escape key
        exit(1);
    }
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }
    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (cRotate == true)  //for clock
    {
        Calpha -= 0.075;
        C_hr_alpha -=0.009;
        if(Calpha < 1.0)
            Calpha = 360.0;
        if(C_hr_alpha < 1.0)
            C_hr_alpha = 360.0;
    }
    glutPostRedisplay();
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,600);
    glutCreateWindow("haunted classRoom");
    glutReshapeFunc(resize);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    printf("Use '1' to on/off light  from the front side.\n");
    printf("Use '2' to on/off light  from the right side.\n");
    printf("Use '3' to on/off spot light from the left side.\n");
    printf("Use 'a' to on/off the light ambient property for all lights.\n");
    printf("Use 'd' to on/off the light diffuse property for all lights.\n");
    printf("Use 's' to on/off the light Specular property for all lights.\n");
    printf("Use 'r' to rotate the scene. \n");
    printf("Use 'f' to on/off the fan.\n");
    printf("Use '+' to zoom in and '-' to zoom out.\n");
    printf("Use '*' to look up, '/' to look down, 'z' to look right, and 'x' to look left.\n");
    sndPlaySound("unlock.wav",SND_ASYNC);
    glutMainLoop();
    return 0;
}
