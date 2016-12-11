#include "Node.h"
#include <GL/glut.h>
#include <math.h>
#define BLACK 1
#define WHITE -1
#define SIMPLE 1
#define QUEEN 3
#define WIDTH 560
#define HEIGHT 560
#define SIDE 70
#define CIRCLE_PRECISION 180

Node::Node(int n)
{
   this->Setn_child(n);
   children = new Node*[this->Getn_child()];
}

void Node::draw_circle(float radius, int posx, int posy){

    float theta = 2 * 3.1415926 / float(CIRCLE_PRECISION);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = radius;//we start at angle = 0

	float y = 0;

	glBegin(GL_POLYGON);
        for(int i = 0; i < CIRCLE_PRECISION; i++)
        {
            glVertex2f(x + posx, y + posy);//output vertex
            //calculate the tangential vector
            //remember, the radial vector is (x, y)
            //to get the tangential vector we flip those coordinates and negate one of them
            float tx = -y;
            float ty = x;
            //add the tangential vector
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            //correct using the radial factor
            x *= radial_factor;
            y *= radial_factor;
        }
	glEnd();

}

void Node::display(){

    /**Draw the inner squares of the board*/
    glLineWidth(3);
    glColor3f (0.2, 0.2, 0.2);
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
                if((i + j) % 2 == 1){
                    glBegin(GL_QUADS);
                        glVertex2f(i*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, j*SIDE);
                        glVertex2f((i+1)*SIDE, (j+1)*SIDE);
                        glVertex2f(i*SIDE, (j+1)*SIDE);
                    glEnd();
                }
        }
    }

    /**Draw the outer square of the board*/
    glLineWidth(5);
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
                glVertex2f(0.0, 0.0);
                glVertex2f(WIDTH, 0.0);
                glVertex2f(WIDTH, HEIGHT);
                glVertex2f(0.0, HEIGHT);
    glEnd();

    /**Draw pieces*/
    glLineWidth(1);
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
                if((i + j) % 2 == 1){
                        Piece* p = this->Getboard(i, j);
                        if(p != NULL){
                            if(p->Getcolor() == WHITE){
                                glColor3f (0.8, 0.8, 0.8);
                            }else{
                                glColor3f (0.1, 0.1, 0.1);
                            }

                            draw_circle(25, (i+0.5)*SIDE, (j+0.5)*SIDE);

                            if(p->Gettype() == QUEEN){
                                glColor3f (0.5, 0.0, 0.0);
                                draw_circle(5, (i+0.5)*SIDE, (j+0.5)*SIDE);
                            }
                        }
                }
        }
    }
    glutPostRedisplay();
}



Node::~Node()
{
    //dtor
}
