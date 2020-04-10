// Math.h

#pragma once

#include <cmath>


namespace Yellow
{
struct V2
{
	float m[2];
	inline float &operator[](int index);
};

inline float &V2::operator[](int index)
{
	return m[index];
}


inline V2 operator +(V2& a, V2& b)
{
	V2 result{};
	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];

	return result;
}

inline V2 operator -(V2& a, V2& b)
{
	V2 result{};

	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];

	return result;
}

inline V2 operator *(V2& a, V2& b)
{
	V2 result{};

	result[0] = a[0] * b[0];
	result[1] = a[1] * b[1];

	return result;
}

inline V2 operator /(V2& a, V2& b)
{
	V2 result{};

	result[0] = a[0] / b[0];
	result[1] = a[1] / b[1];

	return result;
}


inline V2 operator /(V2& a, float b)
{
	V2 result{};

	result[0] = a[0] / b;
	result[1] = a[1] / b;

	return result;
}


inline V2 operator *(V2& a, float b)
{
	V2 result{};

	result[0] = a[0] * b;
	result[1] = a[1] * b;

	return result;
}


inline float Dot(V2& a, V2& b)
{
	return a[0] * b[0] + a[1] + b[1];
}

inline float Length(V2& a)
{
	return sqrt(Dot(a, a));
}

inline float Length2(V2& a)
{
	return Dot(a, a);
}

inline V2 Normalize(V2& a)
{
	V2 result = a / Length(a);

	return result;
}

struct V3
{
	float m[3];
	inline float &operator[](int index);
};

inline float &V3::operator[](int index)
{
	return m[index];
}


inline V3 operator +(V3& a, V3& b)
{
	V3 result{};

	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	result[2] = a[2] + b[2];

	return result;
}

inline V3 operator -(V3& a, V3& b)
{
	V3 result{};

	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];
	result[2] = a[2] - b[2];

	return result;
}

inline V3 operator *(V3& a, V3& b)
{
	V3 result{};

	result[0] = a[0] * b[0];
	result[1] = a[1] * b[1];
	result[2] = a[2] * b[2];

	return result;
}

inline V3 operator /(V3& a, V3& b)
{
	V3 result{};

	result[0] = a[0] / b[0];
	result[1] = a[1] / b[1];
	result[2] = a[2] / b[2];

	return result;
}


inline V3 operator /(V3& a, float b)
{
	V3 result{};

	result[0] = a[0] / b;
	result[1] = a[1] / b;
	result[2] = a[2] / b;

	return result;
}


inline V3 operator *(V3& a, float b)
{
	V3 result{};

	result[0] = a[0] * b;
	result[1] = a[1] * b;
	result[2] = a[2] * b;

	return result;
}


inline float Dot(V3& a, V3& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline float Length(V3& a)
{
	return std::sqrt(Dot(a, a));
}

inline float Length2(V3& a)
{
	return Dot(a, a);
}

inline V3 Normalize(V3& a)
{
	V3 result = a / Length(a);

	return result;
}

inline V3 Cross(V3& a, V3& b)
{
	V3 result;

	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];

	return result;
}

struct V4
{
	float m[4];
	
	inline float &operator[](int index);
};

inline float &V4::operator[](int index)
{
	return m[index];
}

inline V4 operator +(V4& a, V4& b)
{
	V4 result{};

	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	result[2] = a[2] + b[2];
	result[3] = a[3] + b[3];

	return result;
}

inline V4 operator -(V4& a, V4& b)
{
	V4 result{};

	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];
	result[2] = a[2] - b[2];
	result[3] = a[3] - b[3];

	return result;
}

inline V4 operator *(V4& a, V4& b)
{
	V4 result{};


	result[0] = a[0] * b[0];
	result[1] = a[1] * b[1];
	result[2] = a[2] * b[2];
	result[3] = a[3] * b[3];

	return result;
}

inline V4 operator /(V4& a, V4& b)
{
	V4 result{};


	result[0] = a[0] / b[0];
	result[1] = a[1] / b[1];
	result[2] = a[2] / b[2];
	result[3] = a[3] / b[3];

	return result;
}


inline V4 operator /(V4& a, float b)
{
	V4 result{};


	result[0] = a[0] / b;
	result[1] = a[1] / b;
	result[2] = a[2] / b;
	result[3] = a[3] / b;

	return result;
}


inline V4 operator *(V4& a, float b)
{
	V4 result{};

	result[0] = a[0] * b;
	result[1] = a[1] * b;
	result[2] = a[2] * b;
	result[3] = a[3] * b;

	return result;
}


inline float Dot(V4& a, V4& b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline float Length(V4& a)
{
	return std::sqrt(Dot(a, a));
}

inline float Length2(V4& a)
{
	return Dot(a, a);
}

inline V4 Normalize(V4& a)
{
	V4 result = a / Length(a);

	return result;
}


struct Mat4
{
	float m[4][4];

	inline float* operator [](int index);
};

float *Mat4::operator[](int index)
{
	return m[index];
}


inline float Mat4DotRowCol(Mat4& a, Mat4& b, int col, int row)
{
	return
		a[0][col] * b[row][0] +
		a[1][col] * b[row][1] +
		a[2][col] * b[row][2] +
		a[3][col] * b[row][3];
}

inline Mat4 Identity()
{
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}

inline Mat4 MatrixMultiply(Mat4& a, Mat4& b)
{
	Mat4 result{
		Mat4DotRowCol(a, b, 0, 0), Mat4DotRowCol(a, b, 0, 1),
		Mat4DotRowCol(a, b, 0, 2), Mat4DotRowCol(a, b, 0, 3),

		Mat4DotRowCol(a, b, 1, 0), Mat4DotRowCol(a, b, 1, 1),
		Mat4DotRowCol(a, b, 1, 2), Mat4DotRowCol(a, b, 1, 3),

		Mat4DotRowCol(a, b, 2, 0), Mat4DotRowCol(a, b, 2, 1),
		Mat4DotRowCol(a, b, 2, 2), Mat4DotRowCol(a, b, 2, 3),

		Mat4DotRowCol(a, b, 3, 0), Mat4DotRowCol(a, b, 3, 1),
		Mat4DotRowCol(a, b, 3, 2), Mat4DotRowCol(a, b, 3, 3),
	};

	return result;
}

inline Mat4 operator *(Mat4& a, Mat4& b)
{
	return MatrixMultiply(a, b);
}

inline Mat4 Scale(float scaleX, float scaleY, float scaleZ)
{
	return {
		scaleX, 0, 0, 0,
		0, scaleY, 0, 0,
		0, 0, scaleZ, 0,
		0, 0, 0, 1,
	};
}

inline Mat4 Scale(V3 scale)
{
	return Scale(scale[0], scale[1], scale[2]);
}

inline Mat4 Translate(float dX, float dY, float dZ)
{
	return {
		1, 0, 0, dX,
		0, 1, 0, dY,
		0, 0, 1, dZ,
		0, 0, 0, 1,
	};
}

inline Mat4 Translate(V3 trans)
{
	return Translate(trans[0], trans[1], trans[2]);
}

struct Vertex
{
	V3 pos;
	V3 col;
};
}
