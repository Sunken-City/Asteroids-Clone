#pragma once

class Vector2;

class TheRenderer
{
public:
	TheRenderer();
	void ClearScreen(float red, float green, float blue);
	void SetOrtho(const Vector2& bottomLeft, const Vector2& topRight);
	void SetColor(float red, float green, float blue, float alpha);
	void SetPointSize(float size);
	void PushMatrix();
	void PopMatrix();
	void Translate(float x, float y, float z);
	void Rotate(float rotationDegrees);
	void Rotate(float rotationDegrees, float x, float y, float z);
	void Scale(float x, float y, float z);

	void DrawPoint(const Vector2& point);
	void DrawPoint(float x, float y);
	void DrawLine(const Vector2& start, const Vector2& end, float lineThickness);
	void DrawLines(Vector2* const* verts, int numVerts, float lineThickness);
	void DrawLineLoop(Vector2* const* verts, int numVerts, float lineThickness);
	void DrawPolygonOutline(Vector2 center, float radius, int numSides, float radianOffset);
	void DrawPolygon(Vector2 center, float radius, int numSides, float radianOffset);
	static TheRenderer* instance;

	static const int CIRCLE_SIDES = 50;
	static const int HEXAGON_SIDES = 6;
private:
};