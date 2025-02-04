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

#include "Assets/DecalDefinition.h"
#include "Assets/ModelDefinition.h"
#include "Color.h"
#include "FloatType.h"

#include <vecmath/bbox.h>

#include <atomic>
#include <memory>
#include <string>
#include <vector>

namespace TrenchBroom
{
namespace Assets
{
class PropertyDefinition;
class FlagsPropertyDefinition;
class FlagsPropertyOption;

enum class EntityDefinitionType
{
  PointEntity,
  BrushEntity
};

enum class EntityDefinitionSortOrder
{
  Name,
  Usage
};

class EntityDefinition
{
private:
  size_t m_index;
  std::string m_name;
  Color m_color;
  std::string m_description;
  std::atomic<size_t> m_usageCount;
  std::vector<std::shared_ptr<PropertyDefinition>> m_propertyDefinitions;

public:
  virtual ~EntityDefinition();

  size_t index() const;
  void setIndex(size_t index);

  virtual EntityDefinitionType type() const = 0;
  const std::string& name() const;
  std::string shortName() const;
  std::string groupName() const;
  const Color& color() const;
  const std::string& description() const;
  size_t usageCount() const;
  void incUsageCount();
  void decUsageCount();

  const FlagsPropertyDefinition* spawnflags() const;
  const std::vector<std::shared_ptr<PropertyDefinition>>& propertyDefinitions() const;
  const PropertyDefinition* propertyDefinition(const std::string& propertyKey) const;

  static const PropertyDefinition* safeGetPropertyDefinition(
    const EntityDefinition* entityDefinition, const std::string& propertyKey);
  static const FlagsPropertyDefinition* safeGetFlagsPropertyDefinition(
    const EntityDefinition* entityDefinition, const std::string& propertyKey);

  static std::vector<EntityDefinition*> filterAndSort(
    const std::vector<EntityDefinition*>& definitions,
    EntityDefinitionType type,
    EntityDefinitionSortOrder prder = EntityDefinitionSortOrder::Name);

protected:
  EntityDefinition(
    std::string name,
    const Color& color,
    std::string description,
    std::vector<std::shared_ptr<PropertyDefinition>> propertyDefinitions);
};

class PointEntityDefinition : public EntityDefinition
{
private:
  vm::bbox3 m_bounds;
  ModelDefinition m_modelDefinition;
  DecalDefinition m_decalDefinition;

public:
  PointEntityDefinition(
    std::string name,
    const Color& color,
    const vm::bbox3& bounds,
    std::string description,
    std::vector<std::shared_ptr<PropertyDefinition>> propertyDefinitions,
    ModelDefinition modelDefinition,
    DecalDefinition decalDefinition);

  EntityDefinitionType type() const override;
  const vm::bbox3& bounds() const;
  const ModelDefinition& modelDefinition() const;
  const DecalDefinition& decalDefinition() const;
};

class BrushEntityDefinition : public EntityDefinition
{
public:
  BrushEntityDefinition(
    std::string name,
    const Color& color,
    std::string description,
    std::vector<std::shared_ptr<PropertyDefinition>> propertyDefinitions);
  EntityDefinitionType type() const override;
};
} // namespace Assets
} // namespace TrenchBroom
