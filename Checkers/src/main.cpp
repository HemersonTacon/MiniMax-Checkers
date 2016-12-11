
#include <iostream>
#include <stdio.h>
#include <GL/glut.h>
#include "misc.h"
#define WIDTH 560
#define HEIGHT 560

Node* game;

void init(void)
{
    // selecionar cor de fundo (preto)
   glClearColor (0.6, 0.6, 0.6, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade

   game = init_tree();
}

void idle()
{
}

void display(void)
{
  	glClear (GL_COLOR_BUFFER_BIT);
  	game->display();

	glutSwapBuffers();
}

void motion(int x, int y)
{

}

void passiveMotion(int x, int y)
{
    /** Movimento passivo do mouse pra controlar o rebatedor **/

}

void mouse(int button, int state, int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y)
{

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(280, 60);
    glutCreateWindow("Checkers");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseFunc(mouse);
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    printf("Pressione ESC, Q ou q para fechar.\n");

    glutMainLoop();
    return 0;
}




