#include "vec2.h"
#include <SDL_assert.h>
#include <math.h>

TGfxVec2::TGfxVec2()
{
	
}

TGfxVec2::TGfxVec2(float x, float y)
	: x(x)
	, y(y)
{
	
}

bool operator == (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	return (t0.x == t1.x && t0.y == t1.y);
}

bool operator != (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	return (t0.x != t1.x || t0.y != t1.y);
}

TGfxVec2 operator + (const TGfxVec2 & t0)
{
	return t0;
}

TGfxVec2 operator - (const TGfxVec2 & t0)
{
	return TGfxVec2(-t0.x, -t0.y);
}

TGfxVec2 operator + (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	return TGfxVec2(t0.x + t1.x, t0.y + t1.y);
}

TGfxVec2 operator - (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	return TGfxVec2(t0.x - t1.x, t0.y - t1.y);
}

TGfxVec2 operator * (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	return TGfxVec2(t0.x * t1.x, t0.y * t1.y);
}

TGfxVec2 operator / (const TGfxVec2 & t0, const TGfxVec2 & t1)
{
	SDL_assert(t1.x != 0.0f && t1.y != 0.0f);
	return TGfxVec2(t0.x / t1.x, t0.y / t1.y);
}

TGfxVec2 & operator += (TGfxVec2 & t0, const TGfxVec2 & t1)
{
	t0.x += t1.x;
	t0.y += t1.y;
	return t0;
}

TGfxVec2 & operator -= (TGfxVec2 & t0, const TGfxVec2 & t1)
{
	t0.x -= t1.x;
	t0.y -= t1.y;
	return t0;
}

TGfxVec2 operator * (const TGfxVec2 & t0, float f1)
{
	return TGfxVec2(t0.x * f1, t0.y * f1);
}

TGfxVec2 operator * (float f0, const TGfxVec2 & t1)
{
	return TGfxVec2(f0 * t1.x, f0 * t1.y);
}

TGfxVec2 operator / (const TGfxVec2 & t0, float f1)
{
	SDL_assert(f1 != 0.0f);
	return TGfxVec2(t0.x / f1, t0.y / f1);
}

TGfxVec2 & operator *= (TGfxVec2 & t0, float f1)
{
	t0.x *= f1;
	t0.y *= f1;
	return t0;
}

TGfxVec2 & operator /= (TGfxVec2 & t0, float f1)
{
	SDL_assert(f1 != 0.0f);
	t0.x /= f1;
	t0.y /= f1;
	return t0;
}

float TGfxVec2::DotProduct(const TGfxVec2 & t1) const
{
	return (x * t1.x + y * t1.y);
}

float TGfxVec2::SquaredLength() const
{
	return DotProduct(*this);
}

float TGfxVec2::Length() const
{
	return sqrt(SquaredLength());
}

TGfxVec2 TGfxVec2::Normalize() const
{
	const float fLen = Length();
	SDL_assert(fLen > 0.0f);
	return (*this / fLen);
}

TGfxVec2 TGfxVec2::Rotate(float f1) const
{
	const float sin_f1 = sin(f1);
	const float cos_f1 = cos(f1);
	return TGfxVec2(x * cos_f1 - y * sin_f1, y * cos_f1 + x * sin_f1);
}

TGfxVec2 TGfxVec2::Rotate90() const
{
	return TGfxVec2(-y, x);
}

TGfxVec2 TGfxVec2::Rotate180() const
{
	return TGfxVec2(-x, -y);
}

TGfxVec2 TGfxVec2::Rotate270() const
{
	return TGfxVec2(y, -x);
}
