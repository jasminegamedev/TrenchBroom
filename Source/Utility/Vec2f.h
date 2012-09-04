/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__Vec2f__
#define __TrenchBroom__Vec2f__

#include "Utility/Math.h"
#include "Utility/String.h"

#include <cassert>
#include <cmath>
#include <ostream>
#include <vector>

namespace TrenchBroom {
    namespace Math {
        
        class Vec2f {
        public:
            typedef std::vector<Vec2f> List;
            
            float x,y;
            
            Vec2f() : x(0), y(0) {}
            Vec2f(float x, float y) : x(x), y(y) {}
            
            Vec2f& operator= (const Vec2f& right) {
                if (this != &right) {
                    x = right.x;
                    y = right.y;
                }
                return *this;
            }
            
            const Vec2f operator+ (const Vec2f& right) const {
                return Vec2f(x + right.x,
                             y + right.y);
            }
            
            const Vec2f operator- (const Vec2f& right) const {
                return Vec2f(x - right.x,
                             y - right.y);
            }
            
            const Vec2f operator* (const float right) const {
                return Vec2f(x * right,
                             y * right);
            }
            
            const Vec2f operator/ (const float right) const {
                return Vec2f(x / right,
                             y / right);
            }
            
            Vec2f& operator+= (const Vec2f& right) {
                x += right.x;
                y += right.y;
                return *this;
            }
            
            Vec2f& operator-= (const Vec2f& right) {
                x -= right.x;
                y -= right.y;
                return *this;
            }
            
            Vec2f& operator*= (const float right) {
                x *= right;
                y *= right;
                return *this;
            }
            
            Vec2f& operator/= (const float right) {
                x /= right;
                y /= right;
                return *this;
            }
            
            float& operator[] (const unsigned int index) {
                assert(index >= 0 && index < 2);
                if (index == 0) return x;
                return y;
            }
            
            const float& operator[] (const unsigned int index) const {
                assert(index >= 0 && index < 2);
                if (index == 0) return x;
                return y;
            }
            
            const float dot(const Vec2f& right) const {
                return x * right.x + y * right.y;
            }
            
            float length() const {
                return sqrt(lengthSquared());
            }
            
            float lengthSquared() const {
                return this->dot(*this);
            }
            
            void normalize() {
                float l = length();
                x /= l;
                y /= l;
            }
            
            const Vec2f normalized() const {
                float l = length();
                return Vec2f(x / l,
                             y / l);
            }
            
            void correct() {
                x = Math::correct(x);
                y = Math::correct(y);
            }
            
            const Vec2f corrected() const {
                return Vec2f(Math::correct(x),
                             Math::correct(y));
            }
            
            bool equals(const Vec2f& other) const {
                return equals(other, AlmostZero);
            }
            
            bool equals(const Vec2f& other, float delta) const {
                Vec2f diff = other - *this;
                return diff.lengthSquared() <= delta * delta;
            }
            
            void write(std::ostream& str) const {
                str << x;
                str << ' ';
                str << y;
            }
            
            std::string asString() const {
                StringStream result;
                write(result);
                return result.str();
            }
        };
        
        inline Vec2f operator*(float left, const Vec2f& right) {
            return Vec2f(left * right.x,
                         left * right.y);
        }
    }
}

#endif /* defined(__TrenchBroom__Vec2f__) */
