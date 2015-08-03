#ifndef _VEC2_H_INCLUDED
#define _VEC2_H_INCLUDED

struct TGfxVec2
{
	float x;
	float y;

	TGfxVec2();
	TGfxVec2(float x, float y);

	float DotProduct(const TGfxVec2 & t1) const;
	float SquaredLength() const;
	float Length() const;

	TGfxVec2 Normalize() const;
	TGfxVec2 Rotate(float f1) const;

	TGfxVec2 Rotate90() const;
	TGfxVec2 Rotate180() const;
	TGfxVec2 Rotate270() const;
};

bool operator == (const TGfxVec2 & t0, const TGfxVec2 & t1);
bool operator != (const TGfxVec2 & t0, const TGfxVec2 & t1);

TGfxVec2 operator + (const TGfxVec2 & t0);
TGfxVec2 operator - (const TGfxVec2 & t0);

TGfxVec2 operator + (const TGfxVec2 & t0, const TGfxVec2 & t1);
TGfxVec2 operator - (const TGfxVec2 & t0, const TGfxVec2 & t1);
TGfxVec2 operator * (const TGfxVec2 & t0, const TGfxVec2 & t1);
TGfxVec2 operator / (const TGfxVec2 & t0, const TGfxVec2 & t1);

TGfxVec2 & operator += (TGfxVec2 & t0, const TGfxVec2 & t1);
TGfxVec2 & operator -= (TGfxVec2 & t0, const TGfxVec2 & t1);

TGfxVec2 operator * (const TGfxVec2 & t0, float f1);
TGfxVec2 operator * (float f0, const TGfxVec2 & t1);
TGfxVec2 operator / (const TGfxVec2 & t0, float f1);

TGfxVec2 & operator *= (TGfxVec2 & t0, float f1);
TGfxVec2 & operator /= (TGfxVec2 & t0, float f1);


#endif