#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

#include <utility>
#include <ctime>
#include "game.h"

const GLint win_size = 500;
const GLdouble win_size_double = 500.0;
const GLfloat win_size_float = 500.0;

GLfloat cell_size = win_size_float / board_size;

game Game;

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	GLdouble black_cell[] = { 0.556, 0.276, 0.076 };
	GLdouble white_cell[] = { 0.98, 0.888, 0.716 };
	GLdouble black_check[] = { 0.2, 0.2, 0.2 };
	GLdouble white_check[] = { 0.8, 0.8, 0.8 };
	GLdouble black_select_cell[] = {1.0, 0.0, 0.0};
	GLdouble white_select_cell[] = {1.0, 0.0, 0.0};
	GLdouble possible_to_move[] = { 1.0, 1.0, 0.0 };
	GLdouble black_queen[] = { 0.42, 0.42, 0.42 };
	GLdouble white_queen[] = { 0.98, 0.98, 0.88 };
	GLdouble selected[] = { 1.0, 1.0, 0.0 };


	if (Game.is_winner){
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2d((win_size_double / 2) - 100, win_size_double / 2);
		char* message;

		switch (Game.get_winner())
		{
		case game::BLACK_SIDE:
			message = "Black player won!!!";
			for (unsigned i = 0; i < strlen(message); ++i)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *(message + i));
			break;
		case game::WHITE_SIDE:
			message = "White player won!!!";
			for (unsigned i = 0; i < strlen(message); ++i)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *(message + i));
			break;
		}

		glRasterPos2d((win_size_double / 2) - 100, win_size_double - 100);
		char* message_ = "New game stars in 3 seconds. To Exit press Esc.";
		for (unsigned i = 0; i < strlen(message_); ++i)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *(message_ + i));

		Game.is_winner = false;

		glutSwapBuffers();
		Sleep(3000);
	
	}
	else{
		for (unsigned i = 0; i < board_size; ++i)
			for (unsigned j = 0; j < board_size; ++j){
				if ((i + j) % 2)
					glColor3dv(black_cell);
				else
					glColor3dv(white_cell);
				if (Game.check_board[i][j] == game::SELECTED)
					glColor3dv(selected);
				glBegin(GL_QUADS);
				glVertex2f(i * cell_size, j * cell_size);
				glVertex2f((i + 1) * cell_size, j * cell_size);
				glVertex2f((i + 1) * cell_size, (j + 1) * cell_size);
				glVertex2f(i * cell_size, (j + 1) * cell_size);
				glEnd();
				switch (Game.get_cell(i, j))
				{
				case game::EMPTY:
					break;
				case game::BLACK:
					if (Game.is_select_cell().first == i && Game.is_select_cell().second == j)
						glColor3dv(black_select_cell);
					else
						glColor3dv(black_check);
					glBegin(GL_POLYGON);
					for (unsigned k = 0; k < 10; ++k){
						GLfloat angle = 2.0 * 3.1415926f * k / 10.0;
						GLfloat x = cell_size / 2.0 * cos(angle) + (i + 0.5f) * cell_size;
						GLfloat y = cell_size / 2.0 * sin(angle) + (j + 0.5f) * cell_size;
						glVertex2f(x, y);
					}
					glEnd();
					break;
				case game::WHITE:
					if (Game.is_select_cell().first == i && Game.is_select_cell().second == j)
						glColor3dv(white_select_cell);
					else
						glColor3dv(white_check);
					glBegin(GL_POLYGON);
					for (unsigned k = 0; k < 10; ++k){
						GLfloat angle = 2.0 * 3.1415926f * k / 10.0;
						GLfloat x = cell_size / 2.0 * cos(angle) + (i + 0.5f) * cell_size;
						GLfloat y = cell_size / 2.0 * sin(angle) + (j + 0.5f) * cell_size;
						glVertex2f(x, y);
					}
					glEnd();
					break;
				case game::WHITE_QUEEN:
					if (Game.is_select_cell().first == i && Game.is_select_cell().second == j)
						glColor3dv(white_select_cell);
					else
						glColor3dv(white_queen);
					glBegin(GL_POLYGON);
					for (unsigned k = 0; k < 10; ++k){
						GLfloat angle = 2.0 * 3.1415926f * k / 10.0;
						GLfloat x = cell_size / 2.0 * cos(angle) + (i + 0.5f) * cell_size;
						GLfloat y = cell_size / 2.0 * sin(angle) + (j + 0.5f) * cell_size;
						glVertex2f(x, y);
					}
					glEnd();
					break;
				case game::BLACK_QUEEN:
					if (Game.is_select_cell().first == i && Game.is_select_cell().second == j)
						glColor3dv(white_select_cell);
					else
						glColor3dv(black_queen);
					glBegin(GL_POLYGON);
					for (unsigned k = 0; k < 10; ++k){
						GLfloat angle = 2.0 * 3.1415926f * k / 10.0;
						GLfloat x = cell_size / 2.0 * cos(angle) + (i + 0.5f) * cell_size;
						GLfloat y = cell_size / 2.0 * sin(angle) + (j + 0.5f) * cell_size;
						glVertex2f(x, y);
					}
					glEnd();
					break;
				}
			}
		glutSwapBuffers();
	}
}

void on_mouse_click(int button, int state, int x, int y){
	if (state == GLUT_LEFT_BUTTON){
		if (button = GLUT_UP){
			int i = x / cell_size;
			int j = y / cell_size;

			if (Game.is_select_cell() == std::make_pair(-1, -1))
				Game.set_select_cell(i, j);
			else{
				Game.move(i, j);
			}
			glutPostRedisplay();
		}
	}
}

void on_key_pressed(unsigned char key, int x, int y){
	switch (key)
	{
	case 27:
		exit(0);
	default:
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(win_size, win_size);
	glutInitWindowPosition(0, 100);
	glutCreateWindow("Checkers");

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glOrtho(0.0, win_size_double, win_size_double, 0.0, -1.0, 0.0);
	glutDisplayFunc(display);
	glutMouseFunc(on_mouse_click);
	glutKeyboardFunc(on_key_pressed);

	glutMainLoop();
	
	return 0;
}