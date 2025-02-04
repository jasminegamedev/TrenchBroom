/*
 Copyright (C) 2010-2017 Kristian Duske

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

#pragma once

#include "FloatType.h"
#include "Model/HitType.h"

#include <vecmath/bbox.h>

#include <map>
#include <memory>
#include <vector>

namespace TrenchBroom::Model
{

class BrushFaceHandle;
class Node;
class GroupNode;
class BrushNode;
class EntityNode;
class LayerNode;
class EditorContext;

HitType::Type nodeHitType();

LayerNode* findContainingLayer(Node* node);

std::vector<LayerNode*> collectContainingLayersUserSorted(
  const std::vector<Node*>& nodes);

GroupNode* findContainingGroup(Node* node);
const GroupNode* findContainingGroup(const Node* node);

/**
 * Searches the ancestor chain of `node` for the outermost closed group and returns
 * it if one is found, otherwise returns nullptr.
 */
GroupNode* findOutermostClosedGroup(Node* node);
const GroupNode* findOutermostClosedGroup(const Node* node);

std::vector<GroupNode*> collectGroups(const std::vector<Node*>& nodes);

std::map<Node*, std::vector<Node*>> parentChildrenMap(const std::vector<Node*>& nodes);

std::vector<Node*> collectTouchingNodes(
  const std::vector<Node*>& nodes, const std::vector<BrushNode*>& brushes);
std::vector<Node*> collectContainedNodes(
  const std::vector<Node*>& nodes, const std::vector<BrushNode*>& brushes);

std::vector<Node*> collectSelectedNodes(const std::vector<Node*>& nodes);

std::vector<Node*> collectSelectableNodes(
  const std::vector<Node*>& nodes, const EditorContext& editorContext);

std::vector<BrushFaceHandle> collectSelectedBrushFaces(const std::vector<Node*>& nodes);
std::vector<BrushFaceHandle> collectSelectableBrushFaces(
  const std::vector<Node*>& nodes, const EditorContext& editorContext);

vm::bbox3 computeLogicalBounds(
  const std::vector<Node*>& nodes, const vm::bbox3& defaultBounds = vm::bbox3());
vm::bbox3 computePhysicalBounds(
  const std::vector<Node*>& nodes, const vm::bbox3& defaultBounds = vm::bbox3());

std::vector<BrushNode*> filterBrushNodes(const std::vector<Node*>& nodes);
std::vector<EntityNode*> filterEntityNodes(const std::vector<Node*>& nodes);

} // namespace TrenchBroom::Model
