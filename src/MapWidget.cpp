/************************************************************************
     File:        MapWidget.cpp

     Author:     
                  Stephen Chenney, schenney@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu

     Comment:    
						(c) 2001-2002 Stephen Chenney, University of Wisconsin at Madison

						Class header file for the MapWigdet class. A widget class for
						displaying a map of the maze.
		

     Platform:    Visio Studio.Net 2003 (converted to 2005)

*************************************************************************/

#include <stdio.h>
#include "MapWidget.h"
#include <Fl/Fl.h>
#include <Fl/fl_draw.h>
#include <Fl/Fl_Window.h>

//*****************************************************************************
//
// * Constructor
//=============================================================================
MapWidget::
MapWidget(int x, int y, int width, int height, const char *label, Maze *m)
	: Fl_Widget(x, y, width, height, label)
//=============================================================================
{
    maze = m;
    down = false;
    dx = dy = dr = 0.0;
}


//*****************************************************************************
//
// * Set the maze
//=============================================================================
void MapWidget::
Set_Maze(Maze *m)
//=============================================================================
{
	maze = m;

	redraw();
}


//*****************************************************************************
//
// * The draw() method. For efficiency, this should only be called when the
//   display has been damaged, or when the maze changes. It should not be
//   called if only the view frustum has changed.
//=============================================================================
void MapWidget::
draw(void)
//=============================================================================
{
	// Clear the background
	fl_color(FL_WHITE);
	fl_rectf(x(), y(), w(), h());

	if ( maze )  {
		// Push a clip region to make sure that we don't draw outside the
		// widget.
		fl_push_clip(x(), y(), w(), h());

		// The maze knows how to draw its own map
		maze->Draw_Map(x(), y(), x() + w() - 1, y() + h() - 1);

		// Draw the frustum in red
		fl_color(FL_RED);
		maze->Draw_Frustum(x(), y(), x() + w() - 1, y() + h() - 1);

		// Restore the original clip region
		fl_pop_clip();
	}
}


//*****************************************************************************
//
// * Draws the view frustum on the map
//=============================================================================
void MapWidget::
Draw_Frustum(void)
//=============================================================================
{
	if (maze && window()->visible())	{
		// Make sure we draw in the right place, since this method is
		// not generally called inside a draw() method.
		window()->make_current();

		// Make sure we only draw inside the widget.
		fl_push_clip(x(), y(), w(), h());

		// The frustum is drawn on in red.
		fl_color(FL_RED);

		// The maze knows how to draw its frustum if you give it the
		// location and dimension of the window to draw into.
		maze->Draw_Frustum(x(), y(), x() + w() - 1, y() + h() - 1);

		// Restore the clip region.
		fl_pop_clip();
	}
}


//*****************************************************************************
//
// * Gets rid of the view frustum, and cleans up
//=============================================================================
void MapWidget::
Undraw_Frustum(void)
//=============================================================================
{
	// See all the comments in Draw_Frustum above.
	if (maze && window()->visible()) {
		window()->make_current();
		fl_push_clip(x(), y(), w(), h());

		// To undraw, we draw in the background color (white).
		fl_color(FL_WHITE);

		maze->Draw_Frustum(x(), y(), x() + w() - 1, y() + h() - 1);

		// This method draws the edges of the view cell and its neighbors.
		// It is necessary because drawing the frustum in white may have
		// drawn over some edges. This redraws those without redrawing
		// everything.
		maze->Draw_Neighbors(x(), y(), x()+w()-1, y()+h()-1);

		fl_pop_clip();
	}
}


int MapWidget::
handle(int event)
{
	if (!maze)
		return 1;
	
	float vdx = cos(Maze::To_Radians(maze->viewer_dir));
	float vdy = sin(Maze::To_Radians(maze->viewer_dir));
	float rdx = cos(Maze::To_Radians(maze->viewer_dir - 90.f));
	float rdy = sin(Maze::To_Radians(maze->viewer_dir - 90.f));
	
	switch (event)
	{
		case FL_KEYBOARD:
			down = false;
			if (Fl::event_key() == FL_Up || Fl::event_key() == 'w')
			{
				dx = 0.1 * vdx;
				dy = 0.1 * vdy;
				down = true;
			}
			if (Fl::event_key() == FL_Down || Fl::event_key() == 's')
			{
				dx = -0.1 * vdx;
				dy = -0.1 * vdy;
				down = true;
			}
			if (Fl::event_key() == FL_Left || Fl::event_key() == 'a')
			{
				dx = -0.1 * rdx;
				dy = -0.1 * rdy;
				down = true;
			}
			if (Fl::event_key() == FL_Right || Fl::event_key() == 'd')
			{
				dx = 0.1 * rdx;
				dy = 0.1 * rdy;
				down = true;
			}
			if (Fl::event_key() == 'q')
			{
				dr = 5.f;
				down = true;
			}
			if (Fl::event_key() == 'e')
			{
				dr = -5.f;
				down = true;
			}
			return 1;
		case FL_KEYUP:
		case FL_RELEASE:
			down = false;
			return 1;
	}
	return 1;
}

bool MapWidget::
Update(float dt)
{
	if ( down )
	{
		maze->Move_View_Posn(dx, dy, 0.0);
		maze->Set_View_Dir(maze->viewer_dir + dr);
		dx = dy = dr = 0.0;
		return true;
	}
	return false;
}