
#include<GL/freeglut.h>

#include <stdio.h>

#include<mmsystem.h>

bool bFullScreen = false;

GLfloat rotate_angle = 0.0f;

GLfloat xpos = 0.0f;
GLfloat ypos = 0.0f;
GLfloat zpos = 0.0f;

double pos[7050][3];

GLuint index = -1;

GLfloat x = 1.0f;
GLfloat y = 1.0f;
GLfloat z = 5.0f;
GLfloat dx = 0.0f;
GLfloat dy = 0.0f;
GLfloat dz = 0.0f;

GLfloat dt = 0.005;

GLdouble s = 10;
GLdouble b = 2.6666;
GLdouble r = 28;
GLdouble w = 0.02;

double dim=2;

void small(void);
void big(void);
void lorenz(void);
void Timer(int);



int main(int argc, char ** argv)
{
    void display(void);
    void resize(int, int);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);
    void initialize(void);
    void uninitialize(void);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Lorenz System");

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    //glutIdleFunc(_Timer);
    glutCloseFunc(uninitialize);

    //Timer(10);

    glutMainLoop();

}

void display()
{

    int i = 0;

    GLfloat red = 0.5, green = 0.0000f, blue = 0.0000f;
    short br = 1, bg = 2, bb = 2;
    bool brg = true;

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    
    glTranslatef(-2.0f, -1.5f, 0.0f);
    //glRotated(0,1,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glDepthRange(1.0f, 0.0f);

    //glRotated(0,0,1,0);
	glScalef(7.0f, 7.0f, 7.0f);

    glRotatef(rotate_angle,1.0f, 0.5f, 0.0f);
    glRotatef(-90,1.0f, 0.0f, 0.0f);
    glRotatef(45.0,0.0f, 0.0f, 1.0f);

    glEnable(GL_POINT_SIZE);
    glEnable( GL_BLEND );      
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glEnable( GL_POINT_SMOOTH );
    glPointSize(6.0f);
    glBegin(GL_LINE_STRIP);
    //glBegin(GL_POINTS);
    //glColor3f(1.0f, 0.0f, 0.0f);

        for(i = 0; i <= index; i++)
        {
            //if(pos[i][0] > 0)    
                glColor3d(red, green, 0.0f);// blue);
        //glColor3f(1.0f - pos[i][2], 1.0f - pos[i][1], 1.0f - pos[i][2]);
            //else
                //glColor3f(pos[i][1], pos[i][2],pos[i][1]);
        
            glVertex3f(pos[i][2], pos[i][1], pos[i][0]);
            //glVertex3dv(pos[i]);
            //glVertex3f(xpos, ypos, zpos);

            
            red += (br ? (br == 1 ? 0.001f : 0.00f) : -0.001f) ;// ( ? ( ? 1 : 2 ) : 0 )
            
            green += (bg ? (bg == 1 ? 0.001f : 0.00f) : -0.001f) ;// ( ? ( ? 1 : 2 ) : 0 )
            
            //blue += (bb ? (bb == 1 ? 0.001f : 0.00f) : -0.001f) ;// ( ? ( ? 1 : 2 ) : 0 )
            
            /*if(green >= 1.0 && red >= 1.0)
            {
                //printf("1\n");
                br = 0;
                bg = 2;
            }
            else if(green >= 1.0f && red <= 0.0f && blue <= 0.0f)
            {
                //printf("2\n");
                //red = 0.0;
                bb = 1;
                br = 2;
            }
            if(blue >= 1.0f && green >= 1.0)
            {
                //printf("3\n");
                bb = 2;
                bg = 0;
            }
            else if(blue >= 1.0f && green <= 0.0f && red <= 0.0f)
            {
               // printf("4\n");
                bg = 2;
                br = 1;
            }
            else if(blue >= 1.0f && red >= 1.0)
            {
                //printf("5\n");
                bb = 0;
                br = 2;
            }
            else if(red >= 1.0 && blue <= 0.0f && green <= 0.0f)
            {
                //printf("6\n");
                br = 2;
                bg = 1;
            } */

            if(green >= 1.0 && red >= 1.0)
            {
                //printf("1\n");
                if(brg)
                {
                    br = 0;
                    bg = 2;
                    brg = false;
                }
                else
                {
                    br = 2;
                    bg = 0;
                    brg = true;
                }
                
            }
            //else 
            
            if(green >= 1.0f && red <= 0.0f)// && blue <= 0.0f)
            {
                //printf("2\n");
                //red = 0.0;
                bg = 2;
                br = 1;
            }
            if(blue >= 1.0f && green >= 1.0)
            {
                //printf("3\n");
                bb = 2;
                bg = 0;
            }
            else if(red >= 1.0 && green <= 0.0f)
            {
                //printf("6\n");
                br = 2;
                bg = 1;
            } 


        }
        //glColor3f(0.0f, 1.0f, 0.0f);
        //glVertex3f(-x, -y, 0.0f);

        //glColor3f(0.0f, 0.0f, 1.0f);
        //glVertex3f(x, -y, 0.0f);
        
    glEnd();

    
        glEnable(GL_POINT_SIZE);
        glPointSize(10.0f);
    glBegin(GL_POINTS);
    //glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(pos[--i][2], pos[i][1], pos[i][0]);
        glDisable(GL_POINT_SIZE);
    glEnd();

    glDisable(GL_DEPTH_TEST);


  //  Label axes
    //glTranslatef(2.0f, 0.0f, 0.0f);
    //glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
  
  //drawBitmapText("Hello World", 0.1, 0, 0);

    //printf(" -> INDEX = %d ", index);

  //  Display parameters

  //glWindowPos2i(5,5);

    glutSwapBuffers();
}

void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    lorenz();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            glutLeaveMainLoop();
            break;
        
        case 'F':
        case 'f':
        {
            if(bFullScreen)
            {
                glutLeaveFullScreen();
                bFullScreen = false;
            }
            else
            {
                glutFullScreen();
                bFullScreen = true;
            }
        }
        break;

        case 's':
        case 'S':
        {
            Timer(10);
            PlaySound(TEXT(".\\ImitationGamesSoundTrack.wav"), NULL, SND_ASYNC);
            printf("Play Sound");
            //small();
            //x -= 0.1f;
            //y -= 0.1f;
            //glutPostRedisplay();
            
        }
        break;

        case 'b':
        case 'B':
        {
            
            big();
            //x -= 0.1f;
            //y -= 0.1f;
            glutPostRedisplay();
            
        }
        break;

        case 'l':
        case 'L':
        {
            
            lorenz();
            //x -= 0.1f;
            //y -= 0.1f;
            glutPostRedisplay();
            
        }
        break;

        default:
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            break;

        default:
            break;
    }
}

void resize(int width, int height)
{
    //if(height == 0)
    //    height = 1;
  double w2h = (height>0) ? (double)width/height : 1;



    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

  glOrtho(-dim*w2h,+dim*w2h, -dim, +dim, -(5*dim),+(5*dim));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void small(void)
{
    /*angleTri = angleTri+1.0f;
    if(angleTri >= 360.0f)
        angleTri -= 360.0f;
*/
    x -= 0.1f;
    y -= 0.1f;

    //glutPostRedisplay(); 
}

void big()
{
    x += 0.1f;
    y += 0.1f;
}

void uninitialize()
{

}

void lorenz()
{

    dx = s*(y-x);

    dy = x*(r-z)-y;

    dz = x*y - b*z;

    x += dt * dx;

    y += dt * dy;

    z += dt * dz;

    index++;
    pos[index][0] = xpos = x * w;
    pos[index][1] = ypos = y * w;
    pos[index][2] = zpos = z * w;
  
}

void spin(void)
{
    rotate_angle = rotate_angle+0.3f;
    if(rotate_angle >= 360.0f)
        rotate_angle -= 360.0f;

}

void Timer(int value)
{
    if(index >= 7050)
        glutLeaveMainLoop();

    lorenz();
    spin();

    glutPostRedisplay();

    glutTimerFunc(20, Timer, value);
}


