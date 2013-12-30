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
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TrenchBroom_PlanePointsPolicies_h
#define TrenchBroom_PlanePointsPolicies_h

#include "TrenchBroom.h"
#include "VecMath.h"
#include "Model/BrushFace.h"

namespace TrenchBroom {
    namespace Model {
        class FloatPlanePointsPolicy {
        public:
            static void computePoints(const Plane3& plane, BrushFace::Points& points);
        };

        class RoundDownIntegerPlanePointsPolicy {
        public:
            static void computePoints(const Plane3& plane, BrushFace::Points& points);
        };
        
        class GridSearchPlanePointsPolicy {
        public:
            static void computePoints(const Plane3& plane, BrushFace::Points& points);
        };
    }
}

#endif
