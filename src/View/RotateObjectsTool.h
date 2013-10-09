/*
 Copyright (C) 2010-2013 Kristian Duske
 
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

#ifndef __TrenchBroom__RotateObjectsTool__
#define __TrenchBroom__RotateObjectsTool__

#include "TrenchBroom.h"
#include "VecMath.h"
#include "Model/Picker.h"
#include "View/MoveToolHelper.h"
#include "View/RotateObjectsHandle.h"
#include "View/Tool.h"
#include "View/ViewTypes.h"

namespace TrenchBroom {
    namespace View {
        struct RotateInfo {
            Vec3 center;
            Vec3 axis;
            Vec3 origin;
            Plane3 plane;
        };
        
        class RotateDelegate {
        public:
            virtual ~RotateDelegate();
            
            bool handleRotate(const InputState& inputState) const;
            RotateInfo getRotateInfo(const InputState& inputState) const;
            bool startRotate(const InputState& inputState);
            FloatType getAngle(const InputState& inputState, const Vec3& handlePoint, const Vec3& curPoint, const Vec3& axis) const;
            bool rotate(const Vec3& center, const Vec3& axis, const FloatType angle);
            void endRotate(const InputState& inputState);
            void cancelRotate(const InputState& inputState);
        private:
            virtual bool doHandleRotate(const InputState& inputState) const = 0;
            virtual RotateInfo doGetRotateInfo(const InputState& inputState) const = 0;
            virtual bool doStartRotate(const InputState& inputState) = 0;
            virtual FloatType doGetAngle(const InputState& inputState, const Vec3& handlePoint, const Vec3& curPoint, const Vec3& axis) const = 0;
            virtual bool doRotate(const Vec3& center, const Vec3& axis, const FloatType angle) = 0;
            virtual void doEndRotate(const InputState& inputState) = 0;
            virtual void doCancelRotate(const InputState& inputState) = 0;
        };
        
        class RotateHelper : public PlaneDragHelper {
        private:
            RotateDelegate& m_delegate;
            Vec3 m_center;
            Vec3 m_axis;
            FloatType m_lastAngle;
            Vec3 m_firstPoint;
        public:
            RotateHelper(RotateDelegate& delegate);
            
            bool startPlaneDrag(const InputState& inputState, Plane3& plane, Vec3& initialPoint);
            bool planeDrag(const InputState& inputState, const Vec3& lastPoint, const Vec3& curPoint, Vec3& refPoint);
            void endPlaneDrag(const InputState& inputState);
            void cancelPlaneDrag(const InputState& inputState);
            void resetPlane(const InputState& inputState, Plane3& plane, Vec3& initialPoint);
            void render(const InputState& inputState, const bool dragging, Renderer::RenderContext& renderContext);
        };

        class RotateObjectsTool : public Tool<ActivationPolicy, PickingPolicy, MousePolicy, PlaneDragPolicy, RenderPolicy>, public MoveDelegate, public RotateDelegate {
        private:
            static const Model::Hit::HitType HandleHit;

            RotateObjectsHandle m_handle;
            PlaneDragHelper* m_helper;
            MoveHelper m_moveHelper;
            RotateHelper m_rotateHelper;
        public:
            RotateObjectsTool(BaseTool* next, MapDocumentPtr document, ControllerPtr controller, MovementRestriction& movementRestriction);
        private:
            bool initiallyActive() const;
            bool doActivate(const InputState& inputState);
            bool doDeactivate(const InputState& inputState);
            
            void doPick(const InputState& inputState, Model::PickResult& pickResult);

            bool doMouseDown(const InputState& inputState);
            bool doMouseUp(const InputState& inputState);
            void doMouseMove(const InputState& inputState);
            
            bool doStartPlaneDrag(const InputState& inputState, Plane3& plane, Vec3& initialPoint);
            bool doPlaneDrag(const InputState& inputState, const Vec3& lastPoint, const Vec3& curPoint, Vec3& refPoint);
            void doEndPlaneDrag(const InputState& inputState);
            void doCancelPlaneDrag(const InputState& inputState);
            
            void doRender(const InputState& inputState, Renderer::RenderContext& renderContext);
            bool renderHandle(const InputState& inputState) const;
            RotateObjectsHandle::HitArea highlightHandleArea(const InputState& inputState) const;
            
            void resetHandlePosition();
            void updateHandleAxes(const InputState& inputState);

            // MoveDelegate protocol
            bool doHandleMove(const InputState& inputState) const;
            Vec3 doGetMoveOrigin(const InputState& inputState) const;
            bool doStartMove(const InputState& inputState);
            Vec3 doSnapDelta(const InputState& inputState, const Vec3& delta) const;
            MoveResult doMove(const Vec3& delta);
            void doEndMove(const InputState& inputState);
            void doCancelMove(const InputState& inputState);
            
            // RotateDelegate protocol
            bool doHandleRotate(const InputState& inputState) const;
            RotateInfo doGetRotateInfo(const InputState& inputState) const;
            bool doStartRotate(const InputState& inputState);
            FloatType doGetAngle(const InputState& inputState, const Vec3& handlePoint, const Vec3& curPoint, const Vec3& axis) const;
            bool doRotate(const Vec3& center, const Vec3& axis, const FloatType angle);
            void doEndRotate(const InputState& inputState);
            void doCancelRotate(const InputState& inputState);
        };
    }
}

#endif /* defined(__TrenchBroom__RotateObjectsTool__) */
