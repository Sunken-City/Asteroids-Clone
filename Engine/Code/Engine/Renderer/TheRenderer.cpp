#include "Engine/Renderer/TheRenderer.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/MathUtils.hpp"
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library

TheRenderer* TheRenderer::instance = nullptr;

TheRenderer::TheRenderer()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
}

void TheRenderer::ClearScreen(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void TheRenderer::SetOrtho(const Vector2& bottomLeft, const Vector2& topRight)
{
	glLoadIdentity();
	glOrtho(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, 0.f, 1.f);
}

void TheRenderer::DrawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	{
		glVertex2f(x, y);
	}
	glEnd();
}

void TheRenderer::DrawPoint(const Vector2& point)
{
	DrawPoint(point.x, point.y);
}

void TheRenderer::DrawLine(const Vector2& start, const Vector2& end, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	{
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);
	}
	glEnd();
}

void TheRenderer::DrawLines(Vector2* const* verts, int numVerts, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	{
		for (int i = 0; i < numVerts; i++)
		{
			glVertex2f(verts[i]->x, verts[i]->y);
		}
	}
	glEnd();
}

void TheRenderer::SetColor(float red, float green, float blue, float alpha)
{
	glColor4f(red, green, blue, alpha);
}

void TheRenderer::SetPointSize(float size)
{
	glPointSize(size);
}

void TheRenderer::PushMatrix()
{
	glPushMatrix();
}

void TheRenderer::PopMatrix()
{
	glPopMatrix();
}

void TheRenderer::Translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void TheRenderer::Rotate(float rotationDegrees)
{
	glRotatef(rotationDegrees, 0.f, 0.f, 1.f);
}

void TheRenderer::Rotate(float rotationDegrees, float x, float y, float z)
{
	glRotatef(rotationDegrees, x, y, z);
}

void TheRenderer::Scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

void TheRenderer::DrawPolygonOutline(Vector2 center, float radius, int numSides, float radianOffset)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;

	glBegin(GL_LINE_LOOP);
	{
		for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
		{
			float adjustedRadians = radians + radianOffset;
			float x = center.x + (radius * cos(adjustedRadians));
			float y = center.y + (radius * sin(adjustedRadians));
			glVertex2f(x, y);
		}
	}
	glEnd();

}

void TheRenderer::DrawPolygon(Vector2 center, float radius, int numSides, float radianOffset)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;

	glBegin(GL_POLYGON);
	{
		for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
		{
			float adjustedRadians = radians + radianOffset;
			float x = center.x + (radius * cos(adjustedRadians));
			float y = center.y + (radius * sin(adjustedRadians));
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void TheRenderer::DrawLineLoop(Vector2* const* verts, int numVerts, float lineThickness)
{
	glLineWidth(lineThickness);
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < numVerts; i++)
		{
			glVertex2f(verts[i]->x, verts[i]->y);
		}
	}
	glEnd();
}
