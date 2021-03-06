#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <assert.h>

namespace paint
{
    template<class T>
    struct LinearCoefficients {
        T a;
        T b;
        T c;
    };


    struct Index
    {
        unsigned int x;
        unsigned int y;
        unsigned int z;

        Index(unsigned int x, unsigned int y, unsigned int z) :
            x(x),
            y(y),
            z(z)
            {};
    };

    struct Vec2
    {
        float x;
        float y;

        Vec2() : x(0.0f), y(0.0f){};
        Vec2(float x, float y) : x(x), y(y){};

        //add another Vec2
        Vec2 operator+(const Vec2 &other) const
        {
            return {this->x + other.x, this->y + other.y};
        }

        //subtract vector
        Vec2 operator-(const Vec2 &other) const
        {
            return {this->x - other.x, this->y - other.y};
        }

        //multiple by scaler
        Vec2 operator*(float other) const
        {
            return {this->x * other, this->y * other};
        }

        //dot product
        float operator*(const Vec2 &other) const
        {
            return {this->x * other.x + this->y * other.y};
        }

        float magnitude() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }

    };

    //print Vec2
    /*
std::ostream &operator<<(std::ostream &os, const Vec2& other)
{
    os << "[ " << other.x << std::endl;
    os << "  " << other.y << " ]";
    return os;
}*/

    struct Mat2
    {
        Vec2 leftCol;
        Vec2 rightCol;

        //add another Mat2
        Mat2 operator+(const Mat2 &other) const
        {
            return {this->leftCol + other.leftCol, this->rightCol + other.rightCol};
        }

        //sub another Mat2
        Mat2 operator-(const Mat2 &other) const
        {
            return {this->leftCol - other.leftCol, this->rightCol - other.rightCol};
        }

        //multiply by scalar
        Mat2 operator*(float other) const
        {
            return {this->leftCol * other, this->rightCol * other};
        }

        //multiply with Vec2
        Vec2 operator*(const Vec2 &other) const
        {
            return {this->leftCol.x * other.x + this->rightCol.x * other.y,
                    this->leftCol.y * other.x + this->rightCol.y * other.y};
        }

        //multiply with Mat2
        Mat2 operator*(const Mat2 &other) const
        {
            return {*this * other.leftCol, *this * other.rightCol};
        }
    };

    /*
std::ostream& operator<<(std::ostream& os, const Mat2& mat) {
    os << "[ " << mat.leftCol.x << "  " << mat.rightCol.x << std::endl;
    os << "  " << mat.leftCol.y << "  " << mat.rightCol.y << " ]";
    return os;
}*/

    struct Vec3
    {
        float x;
        float y;
        float z;


        Vec3() : x(0.0f), y(0.0f), z(0.0f) {};
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

        //add another Vec3
        Vec3 operator+(const Vec3 &other) const
        {
            return {this->x + other.x, this->y + other.y, this->z + other.z};
        }

        //subtract Vec3
        Vec3 operator-(const Vec3 &other) const
        {
            return {this->x - other.x, this->y - other.y, this->z - other.z};
        }

        //multiple by scaler
        Vec3 operator*(float other) const
        {
            return {this->x * other, this->y * other, this->z * other};
        }

        //dot product
        float operator*(const Vec3 &other) const
        {
            return {this->x * other.x + this->y * other.y + this->z * other.z};
        }

        float magnitude() const {
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        Vec3 crossProduct(Vec3 v) {
            Vec3 ret;
            ret.x = this->y * v.z - this->z * v.y;
            ret.y = this->z * v.x - this->x * v.z;
            ret.z = this->x * v.y - this->y * v.x;
            return ret;
        }
    };


    struct Mat3
    {
        Vec3 leftCol = {1.0f, 0.0f, 0.0f};
        Vec3 midCol = {0.0f, 1.0f, 0.0f};
        Vec3 rightCol = {0.0f, 0.0f, 1.0f};

        //add another Mat3
        Mat3 operator+(const Mat3 &other) const
        {
            return {this->leftCol + other.leftCol, this->midCol + other.midCol, this->rightCol + other.rightCol};
        }

        //sub another Mat3
        Mat3 operator-(const Mat3 &other) const
        {
            return {this->leftCol - other.leftCol, this->midCol - other.midCol, this->rightCol - other.rightCol};
        }

        //multiply by scalar
        Mat3 operator*(float other) const
        {
            return {this->leftCol * other, this->midCol * other, this->rightCol * other};
        }

        //multiply with Vec3
        Vec3 operator*(const Vec3 &other) const
        {
            return {this->leftCol.x * other.x + this->midCol.x * other.y + this->rightCol.x * other.z,
                    this->leftCol.y * other.x + this->midCol.y * other.y + this->rightCol.y * other.z,
                    this->leftCol.z * other.x + this->midCol.z * other.y + this->rightCol.z * other.z};
        }

        //multiply with Mat3
        Mat3 operator*(const Mat3 &other) const
        {
            return {*this * other.leftCol, *this * other.midCol, *this * other.rightCol};
        }

        //Matrix transforms
        //translate Mat3
        static Mat3 translate(Vec2 translation) {
            Mat3 m; //identity matrix
            m.rightCol.x = translation.x;
            m.rightCol.y = translation.y;
            return m;
        }
        //scale Mat3 (scale all translations too)
        static Mat3 scale(Vec2 scale) {
            Mat3 m; //identity matrix
            m.leftCol.x = scale.x;
            m.midCol.y = scale.y;
            return m;
        }
        //rotate Mat3 (rotate all translations too)
        static Mat3 rotate(float angle) {
            Mat3 m; //identity matrix
            //precalculate sine and cosine of angle
            float cosTheta = cos(angle);
            float sinTheta = sin(angle);
            //
            m.leftCol.x = cosTheta;
            m.leftCol.y = sinTheta;
            m.midCol.x = -sinTheta;
            m.midCol.y = cosTheta;
            return m;
        }
    };


    struct Vec4
    {
        float x;
        float y;
        float z;
        float w;

        Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

        //add another Vec4
        Vec4 operator+(const Vec4 &other) const
        {
            return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
        }

        //subtract Vec4
        Vec4 operator-(const Vec4 &other) const
        {
            return {this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
        }

        //multiple by scaler
        Vec4 operator*(float other) const
        {
            return {this->x * other, this->y * other, this->z * other, this->w * other};
        }

        //dot product
        float operator*(const Vec4 &other) const
        {
            return {this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w};
        }
    };


    struct Mat4
    {
        Vec4 firstCol = {1.0f, 0.0f, 0.0f, 0.0f};
        Vec4 secondCol = {0.0f, 1.0f, 0.0f, 0.0f};
        Vec4 thirdCol = {0.0f, 0.0f, 1.0f, 0.0f};
        Vec4 fourthCol = {0.0f, 0.0f, 0.0f, 1.0f};

        //add another Mat4
        Mat4 operator+(const Mat4 &other) const
        {
            return {this->firstCol + other.firstCol, this->secondCol + other.secondCol, 
                    this->thirdCol + other.thirdCol, this->fourthCol + other.fourthCol};
        }

        //sub another Mat4
        Mat4 operator-(const Mat4 &other) const
        {
            return {this->firstCol - other.firstCol, this->secondCol - other.secondCol,
                    this->thirdCol - other.thirdCol, this->fourthCol - other.fourthCol};
        }

        //multiply by scalar
        Mat4 operator*(float other) const
        {
            return {this->firstCol * other, this->secondCol * other, this->thirdCol * other, this->fourthCol * other};
        }

        //multiply with Vec4
        Vec4 operator*(const Vec4 &other) const
        {
            return {this->firstCol.x * other.x + this->secondCol.x * other.y + this->thirdCol.x * other.z + this->fourthCol.x * other.w,
                    this->firstCol.y * other.x + this->secondCol.y * other.y + this->thirdCol.y * other.z + this->fourthCol.y * other.w,
                    this->firstCol.z * other.x + this->secondCol.z * other.y + this->thirdCol.z * other.z + this->fourthCol.z * other.w,
                    this->firstCol.w * other.x + this->secondCol.w * other.y + this->thirdCol.w * other.z + this->fourthCol.w * other.w};
        }

        //multiply with Mat4
        Mat4 operator*(const Mat4 &other) const
        {
            return {*this * other.firstCol, *this * other.secondCol, *this * other.thirdCol, *this * other.fourthCol};
        }

        //Matrix transforms
        //translate Mat3
        static Mat4 translate(Vec3 translation) {
            Mat4 m; //identity matrix
            m.fourthCol.x = translation.x;
            m.fourthCol.y = translation.y;
            m.fourthCol.z = translation.z;
            return m;
        }
        //scale Mat3 (scale all translations too)
        static Mat4 scale(Vec3 scale) {
            Mat4 m; //identity matrix
            m.firstCol.x = scale.x;
            m.secondCol.y = scale.y;
            m.thirdCol.z = scale.z;
            return m;
        }

        //rotate Mat3 (rotate all translations too)
        static Mat4 rotate(float angle, Vec3 ra ) {
            Vec3 rotationAxis = ra;
            assert(abs(rotationAxis.magnitude()) > 0.001f); //user must specify non-zero axis of rotation

            Mat4 m; //identity matrix

            float cosTheta = cos(angle);
            float sinTheta = sin(angle);

            ra = ra * (1.0f / ra.magnitude());
            //got this formula from wikipedia!!! (rotation matrix from axis and angle)
            //column 1
            m.firstCol.x = cosTheta + ra.x * ra.x * (1.0f - cosTheta);
            m.firstCol.y = ra.y * ra.x * (1.0f - cosTheta) + ra.z * sinTheta;
            m.firstCol.z = ra.z * ra.x * (1.0f - cosTheta) - ra.y * sinTheta;
            //column 2
            m.secondCol.x = ra.x * ra.y * (1.0f - cosTheta) - ra.z * sinTheta;
            m.secondCol.y = cosTheta + ra.y * ra.y * (1.0f - cosTheta);
            m.secondCol.z = ra.z * ra.y * (1.0f - cosTheta) + ra.x * sinTheta;
            //column 3
            m.thirdCol.x = ra.x * ra.z * (1.0f - cosTheta) + ra.y * sinTheta;
            m.thirdCol.y = ra.y * ra.z * (1.0f - cosTheta) - ra.x * sinTheta;
            m.thirdCol.z = cosTheta + ra.z * ra.z * (1.0f - cosTheta);

            return m;
        }

        //NDC x:[-1, 1], y:[-1, 1], z:[0,1]
        static Mat4 perspective() {
            Mat4 m;
            float l = -133.0f; //
            float r = 133.0f;
            float t = 100.0f;
            float b = -100.0f;
            float n = 200.0f; //near clipping plane
            float f = 10000.0f; //far clipping plane
            
            m.firstCol.x = (2 * n) / (r - l);
            m.secondCol.y = (2 * n) / (t - b);

            m.thirdCol.x = (-r - l) / (r - l);
            m.thirdCol.y = (-t - b) / (t - b);
            m.thirdCol.z = (f) / (f - n);
            m.thirdCol.w = 1.0f;

            m.fourthCol.z = (-f * n) / (f - n);
            m.fourthCol.w = 0.0f;

            return m;
        }

        //need to change how camera moves if using orthographic projection
        static Mat4 orthogonal() {
            Mat4 m;

            float l = -400.0f; 
            float r = 400.0f;
            float t = 300.0f;
            float b = -300.0f;
            float n = 200.0f; //near clipping plane
            float f = 10000.0f; //far clipping plane

            m.firstCol.x = 2.0f / (r - l);
            m.secondCol.y = 2.0f / (t - b); 
            m.thirdCol.z = 2.0f / (f - n);

            m.fourthCol.x = -(r + l) / (r - l);
            m.fourthCol.y = -(t + b) / (t - b);
            m.fourthCol.z = -(f + n) / (f - n);
            m.fourthCol.w = 1.0f;

            return m;
        }

    };

    static bool hasPlaneLineIntersection(Vec3 planeNormal, Vec3 lineDirection){
        if(planeNormal * lineDirection != 0)
            return true;
        else
            return false;
    }


    struct Plane {
        Vec3 point;
        Vec3 normal;
    };

    struct Line {
        Vec3 point;
        Vec3 direction;
    };


    static Vec3 getPlaneLineIntersection(Plane plane, Line line) {
        assert(hasPlaneLineIntersection(plane.normal, line.direction));
        float num = (plane.point - line.point) * plane.normal;
        float den = line.direction * plane.normal;
        float scalar = num / den;
        return line.point + line.direction * scalar;
    }

    static Vec3 getIntersection(Vec4 v1, Vec4 v2) {
        float a = (v1.z * (-1.0f)) / (v2.z - v1.z);
        Vec4 ret = v1 * (1.0f - a) + v2 * a;
        return {ret.x, ret.y, ret.z};
    }




} // namespace paint

#endif //MATH_H