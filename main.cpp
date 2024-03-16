#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <glew.h>
#include <freeglut.h>
#include <assimp.h>



static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int animate = 0;
static float leg_angle = 0.0;
static float ball_angle = 0.0;
static int animate_time = 20;
static int forward = 0;

//for the ball
static int isAnimate = 0;
static int animationPeriod = 100; // Time interval between frames.
static float t = 0.0; // Time parameter.
static float h = 4.5; // Horizontal component of initial velocity.
static float v = 2.50; // Vertical component of initial velocity.
static float g = 0.2;  // Gravitational accelaration.


static float groundY = -8.0;



// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -20.0);
    // Modeling transformations.

    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    //for the ball
    if (isAnimate)
    {

        if (h * t <= groundY) {
            isAnimate = 0;
            h = 5.0;  // Set horizontal position to 0 to keep it on the ground.
            v = -7.5;  // set vertical velocity to 0.
            t = 5.0;  // Reset time.


        }
        else {
            t += 1.0;
            h += forward ? 0.1 : -0.1; // Adjust horizontal velocity for return.
        }

    }



    // Apply equations of motion to transform sphere.
    glTranslatef(h * t, v * t - (g / 2.0) * t * t, 0.0);

    // Sphere.
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(-25.70, 12.0, 0.0);
    glutSolidSphere(2.0, 10, 10);
    glTranslatef(25.70, -12.0, 0.0);

    glTranslatef(-h * t, -(v * t - (g / 2.0) * t * t), 0.0);



    // glTranslatef(-h * t, -(v * t - (g / 2.0) * t * t), 0.0);
      //////////////////////////////////////////////////////////
    glColor3f(0.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glTranslatef(4.0, 0.0, 0.0);
    glutWireSphere(2.0, 10, 8);
    glTranslatef(-4.0, 0.0, 0.0);

    //////////////////////////////////////////////////////////
    //for the human



    glColor3f(1.0, 0.8, 0.6);  // Skin color (light skin tone)

    // Right Arm (will not appear)
    glPushMatrix();
    glTranslatef(-14.0, 0.0, 0.0); // Position the right arm
    glRotatef(-45.0, 0.0, 1.0, 0.0); // Rotate the right arm
    glScalef(0.5, 5.0, 1.0); // Scale the right arm
    glutSolidCube(2.0); // Draw the right arm
    glPopMatrix();


    glColor3f(0.0, 0.0, 0.0);

    //torso
    glTranslatef(-15.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 3.0, 1.5);
    glutSolidCube(4.0);
    glPopMatrix();

    //head

    glColor3f(1.0, 0.8, 0.6);  // Skin color (light skin tone)
    glPushMatrix();
    glTranslatef(0.0, 9.0, 0.0);
    glScalef(1.0, 1.5, 1.0);
    glutSolidSphere(2, 50, 50);
    glPopMatrix();

    //the left arm

    glPushMatrix();
    glTranslatef(-2.5, 0.0, 0.0); // Position the left arm relative to the torso
    glTranslatef(0.0, 5.0, 0.0); // Translate to the upper edge of the left arm
    glRotatef(-120, 0.0, 0.0, 1.0); // Rotate the left arm around its upper edge
    glRotatef(-leg_angle, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -5.0, 0.0); // Translate back to the center of the left arm
    glScalef(0.5, 5.0, 1.0); // Scale the left arm
    glutSolidCube(2.0); // Draw the left arm
    glPopMatrix();








    //left leg
    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);
    // glRotatef(leg_angle, 0.0, 0.0, 1.0); // Rotate in the XY plane
    glTranslatef(0.0, 7.5, 0.0);

    glTranslatef(0.0, -10.5, -1.0);
    glScalef(1.0, 6.0, 1.0);
    glutSolidCube(1.5);
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef(0.0, -7.5, 0.0);
    //glRotatef(angle, 0.0, 0.0, 1.0); // Rotate in the XY plane

    glTranslatef(0.0, 7.5, 0.0);

    glTranslatef(0.0, -10.5, 1.0);
    glScalef(1.0, 6.0, 1.0);
    glutSolidCube(1.5);
    glPopMatrix();


    //the ball
    /*
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(ball_angle, 0.0, 0.0, 1.0); // Rotate in the XY plane
    glTranslatef(4.0, -13.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidSphere(2, 50, 50);
    glPopMatrix();
    */
    glutSwapBuffers();




}


// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8.0, 8.0, -8.0, 8.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void animation(int value)
{
    if (animate)
    {

        if (leg_angle < 250.0)
            leg_angle += 5.0;

        glutPostRedisplay();
        glutTimerFunc(animate_time, animation, 1);


    }

}

void ball_animate(int value)
{
    if (isAnimate)
    {
        if (h >= 8.0 || h <= -8.0)
            isAnimate = 0;

        glutPostRedisplay();
        glutTimerFunc(animationPeriod, ball_animate, 1);
    }
}





// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case ' ':
        if (animate)
        {
            animate = 0;
        }
        else
        {
            animate = 1;
            animation(1);
        }
        if (isAnimate)
        {
            isAnimate = 0;
        }
        else
        {
            isAnimate = 1;
            ball_animate(1);
        }
        break;


    case 'x':
        Xangle += 5.0;
        if (Xangle > 360.0) Xangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        Xangle -= 5.0;
        if (Xangle < 0.0) Xangle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        Yangle += 5.0;
        if (Yangle > 360.0) Yangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        Yangle -= 5.0;
        if (Yangle < 0.0) Yangle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        Zangle += 5.0;
        if (Zangle > 360.0) Zangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        Zangle -= 5.0;
        if (Zangle < 0.0) Zangle += 360.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    //glutInitContextVersion(4, 3);
    //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("box.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}

