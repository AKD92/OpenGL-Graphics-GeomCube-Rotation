

/************************************************************************************
	Driver File (MAIN)
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/



#include <math.h>
#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iup.h>                /* For GUI toolkit */
#include <iupgl.h>
#include <list.h>


#define CYCLE_COUNT			5
#define BTN_CLOSE			"btnClose"
#define GL_CANVAS			"GLCanvas"
#define MAIN_WINDOW			"423Classwork03MainWindow"



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/


struct cube_ {
	
	float x0, y0;
	float x1, y1;
	float x2, y2;
	float x3, y3;
	
	float x4, y4;
	float x5, y5;
	float x6, y6;
	float x7, y7;
	
};

struct loc_ {
	float x, y;
};





struct cube_ cube;
List cirList;

char *labTitle = "Graphics Classwork (11301002)\n"
					"Geometric Cube Rotation (Cycle count: %d)";







int main(void);

Ihandle * createMainWindow(void);
int repaint_cb(Ihandle *canvas);
int btnRotate_cb(Ihandle *btn);
int exit_cb(Ihandle *btn);

void util_calculateCoordinates(struct cube_ *pCube);
void util_rotateCoordinates(struct cube_ *pCube, float fAngle);



/*	OpenGL related functions	*/

void clipal_drawClipRectangle(void);
void mygl_drawGenericLine(float x0, float y0, float x1, float y1);






/************************************************************************************
*
*   Implementation of driver routines
*
*************************************************************************************/


Ihandle * createMainWindow(void) {

	Ihandle *bottomHbox, *mainVbox;
	Ihandle *lblTitle, *glCanvas;
	Ihandle *btnRotate, *btnClose;
	Ihandle *dialog;

	lblTitle = IupLabel(0);
	IupSetfAttribute(lblTitle, "TITLE", labTitle, CYCLE_COUNT);
	IupSetAttribute(lblTitle, "EXPAND", "HORIZONTAL");
	IupSetAttribute(lblTitle, "ALIGNMENT", "ALEFT:ACENTER");
	IupSetAttribute(lblTitle, "FONTSIZE", "10");

	glCanvas = IupGLCanvas(0);
	IupSetAttribute(glCanvas, "EXPAND", "YES");
	IupSetAttribute(glCanvas, "BORDER", "NO");
	IupSetAttribute(glCanvas, "CANFOCUS", "NO");
	IupSetCallback(glCanvas, "ACTION", (Icallback) repaint_cb);

	btnRotate = IupButton("Rotate", 0);
	IupSetAttribute(btnRotate, "RASTERSIZE", "60x33");
	IupSetCallback(btnRotate, "ACTION", (Icallback) btnRotate_cb);
	
	btnClose = IupButton("Close", 0);
	IupSetAttribute(btnClose, "RASTERSIZE", "80x33");
	IupSetCallback(btnClose, "ACTION", (Icallback) exit_cb);

	bottomHbox = IupHbox(btnRotate, IupFill(), btnClose, 0);
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	IupSetAttribute(bottomHbox, "NGAP", "5");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x5");

	mainVbox = IupVbox(lblTitle, glCanvas, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	IupSetAttribute(mainVbox, "NGAP", "10");
	
	IupSetHandle(BTN_CLOSE, btnClose);
	IupSetHandle(GL_CANVAS, glCanvas);

	dialog = IupDialog(mainVbox);
	IupSetAttribute(dialog, "TITLE", "GL Labwork");
	IupSetAttribute(dialog, "RASTERSIZE", "425x550");
	IupSetAttribute(dialog, "SHRINK", "YES");
	IupSetAttribute(dialog, "DEFAULTESC", BTN_CLOSE);
	
	IupSetHandle(MAIN_WINDOW, dialog);

	return dialog;
}




int repaint_cb(Ihandle *canvas) {
	
	register ListElem *elem;
	register struct loc_ *pLoc;
	
	if (IupGLIsCurrent(canvas) == 0) {
		IupGLMakeCurrent(canvas);                   /* Declare our canvas for OpenGL */
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glPointSize(1.0);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	/* Draw the cube by using Midpoint LineDraw Algorithm */
	glBegin(GL_POINTS);
		
		mygl_drawGenericLine(cube.x0, cube.y0, cube.x1, cube.y1);
		
		mygl_drawGenericLine(cube.x4, cube.y4, cube.x6, cube.y6);
		
		mygl_drawGenericLine(cube.x5, cube.y5, cube.x7, cube.y7);
		
		mygl_drawGenericLine(cube.x2, cube.y2, cube.x3, cube.y3);
		
		mygl_drawGenericLine(cube.x0, cube.y0, cube.x4, cube.y4);
		
		mygl_drawGenericLine(cube.x1, cube.y1, cube.x6, cube.y6);
		
		mygl_drawGenericLine(cube.x5, cube.y5, cube.x2, cube.y2);
		
		mygl_drawGenericLine(cube.x7, cube.y7, cube.x3, cube.y3);
		
		mygl_drawGenericLine(cube.x0, cube.y0, cube.x5, cube.y5);
		
		mygl_drawGenericLine(cube.x4, cube.y4, cube.x2, cube.y2);
		
		mygl_drawGenericLine(cube.x6, cube.y6, cube.x3, cube.y3);
		
		mygl_drawGenericLine(cube.x1, cube.y1, cube.x7, cube.y7);
		
		
		/* Draw the points of the circle */
		elem = list_head(&cirList);
		while (elem != 0) {
			pLoc = (struct loc_ *) list_data(elem);
			glVertex2f(pLoc->x, pLoc->y);
			elem = list_next(elem);
		}
	
	glEnd();

	glFlush();

	return IUP_DEFAULT;
}


int btnRotate_cb(Ihandle *btn) {
	
	unsigned int iCycle;
	register unsigned int isCycleComplete;
	Ihandle *canvas;
	struct loc_ *pLoc;
	struct loc_ *pLoc_s;
	float difx, dify;
	void (*f_destroy) (void *data);
	
	canvas = IupGetHandle(GL_CANVAS);
	
	
	/* Store pointer to the destroy() function of our Linked List */
	f_destroy = cirList.destroy;
	
	
	/* Destroy and Re-Initialize our Linked List */
	list_destroy(&cirList);
	list_init(&cirList, f_destroy);
	
	iCycle = 0;
	while (iCycle < CYCLE_COUNT) {
		
		
		/* Rotate our cube by the ANGLE 0.05 */
		util_rotateCoordinates(&cube, 0.05f);
		
		pLoc = (struct loc_ *) malloc(sizeof(struct loc_));
		pLoc->x = cube.x0;
		pLoc->y = cube.y0;
		
		
		/* Determine if we have completed a cycle */
		if (list_head(&cirList) != 0) {
			
			/* Obtain pointer to the first (x,y) location object */
			/* The starting point of current circle being drawn */
			/* Also, calculate difference of starting position relative to current position */
			pLoc_s = (struct loc_ *) list_data(list_head(&cirList));
			difx = pLoc->x - pLoc_s->x;
			dify = pLoc->y - pLoc_s->y;
			
			
			/* If a cycle is complete, we erase whole circle from the screen */
			/* And then start drawing the circle for a new cycle */
			/* To ensure this, differences must be very near, not so far */
			isCycleComplete = (difx < 0.01) & (difx > -0.01) & (dify < 0.01) & (dify > -0.01);
			
			if (isCycleComplete != 0) {
				list_destroy(&cirList);
				list_init(&cirList, f_destroy);
				iCycle = iCycle + 1;
			}
		}
		
		list_ins_next(&cirList, list_tail(&cirList), (const void *) pLoc);
		
		IupRedraw(canvas, 0);
		
		/* Wait for a very short time */
		/* This Delay() function is defined in conio2.h file */
		delay(20);
	}
	
	return IUP_DEFAULT;
}



int exit_cb(Ihandle *btn) {

	return IUP_CLOSE;
}





int main(void) {

	Ihandle *dlgMainWindow;
	
	
	/* Define some initial value as per instructed in the lab PDF requirement document */
	cube.x0 = 0.3f;
	cube.y0 = 0.2f;
	cube.x1 = 0.5f;
	cube.y1 = 0.4f;
	
	cube.x2 = 0.6f;
	cube.y2 = 0.5f;
	cube.x3 = 0.8f;
	cube.y3 = 0.7f;
	
	list_init(&cirList, free);
	util_calculateCoordinates(&cube);
	
	IupOpen(0, 0);
		IupGLCanvasOpen();

		dlgMainWindow = createMainWindow();
		IupShowXY(dlgMainWindow, IUP_CENTER, IUP_CENTER);

		IupMainLoop();
	IupClose();
	
	list_destroy(&cirList);
	
	return 0;
}
