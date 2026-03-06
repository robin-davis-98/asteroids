#ifndef PET_MATH_H
#define PET_MATH_H

struct Vec2 {
    union {
        struct { float x, y; };
        struct { float u ,v; };
        float elements[2];
    };
};

struct Vec3 {
    union {
        struct { float x, y, z; };
        struct { float r, g, b; };
        float elements[3];
    };
};

struct Vec4 {
    union {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        float elements[4];
    };
};

struct Mat4
{
    float m[16];
};

Mat4 mat4_orthographic(float left, float right, float bottom, float top, float near, float far);
Mat4 mat4_perspective(float fov, float aspect, float near, float far);
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);
Mat4 mat4_mul(Mat4 a, Mat4 b);
void mat4_translate(Mat4* m, float x, float y, float z);

#endif