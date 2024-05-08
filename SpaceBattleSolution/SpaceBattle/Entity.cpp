#include "pch.h"
#include "Bullet.h"
#include "Config.h"
#include "Entity.h"
#include "Globals.h"
#include <stdexcept>

Entity::Entity(const int image_resource_id) :
    x(0),
    y(0),
    angle(DEFAULT_ANGLE),
    action_movement(ActionMovement::None),
    is_destroyed(false),
    points_earned(0),
    entities_destroyed(0),
    self_points(DEFAULT_ENTITY_SELF_POINTS),
    owner(nullptr),
    scale(DEFAULT_IMAGE_SCALE),
    speed(DEFAULT_SPEED),
    health(DEFAULT_ENTITY_HEALTH) {
  // ��������� ����������� �� �������
  CPngImage pngImage;
  pngImage.Load(image_resource_id, AfxGetResourceHandle());

  // �������� ������ �����������
  this->bmp_loaded = static_cast<HBITMAP>(pngImage.Detach());

  // �������� ���������� �� �����������
  GetObject(this->bmp_loaded, sizeof(BITMAP), &this->bmp_info);

  this->width = bmp_info.bmWidth;
  this->height = bmp_info.bmHeight;
}

double Entity::GetX() const {
  return x;
}

int Entity::GetIntX() const {
  return static_cast<int>(this->x);
}

void Entity::SetX(const double new_x) {
  this->x = new_x;
}

double Entity::GetY() const {
  return y;
}

int Entity::GetIntY() const {
  return static_cast<int>(this->y);
}

void Entity::SetY(const double new_y) {
  this->y = new_y;
}

void Entity::SetLocation(const double new_x, const double new_y) {
  this->SetX(new_x);
  this->SetY(new_y);
}

double Entity::GetAngle() const {
  return this->angle;
}

void Entity::SetAngle(const double new_angle) {
  this->angle = new_angle;
}

Entity::ActionMovement Entity::GetActionMovement() const {
  return this->action_movement;
}

void Entity::SetActionMovement(const ActionMovement new_action_movement) {
  this->action_movement = new_action_movement;
}

bool Entity::IsDestroyed() const {
  return this->is_destroyed;
}

LONG Entity::GetWidth() const {
  return width;
}

LONG Entity::GetHeight() const {
  return height;
}

int Entity::GetPointsEarned() const {
  return this->points_earned;
}

int Entity::GetEntitiesDestroyed() const {
  return this->entities_destroyed;
}

Entity* Entity::GetMainOwner() {
  if (this->owner != nullptr) {
    const Entity* found_owner = this->owner->GetMainOwner();
    if (found_owner != this) {
      return this->owner;
    }
  }
  return nullptr;
}

double Entity::GetScale() const {
  return this->scale;
}

void Entity::SetScale(const double new_scale) {
  this->scale = new_scale;
}

int Entity::GetHealth() const {
  return this->health;
}

int Entity::GetIntersectRadius() const {
  return static_cast<int>(max(width, height) * scale * INTERSECT_RADIUS_SCALE / 2);
}

void Entity::Draw(const HDC& hdc, const HDC& hdc_bits) const {
  if (this->is_destroyed) {
    return;
  }

  // ���� ����, ������� ����� ������� ����������
  auto rgb_quad = RGBQUAD();
  rgb_quad.rgbRed = 0;
  rgb_quad.rgbGreen = 255;
  rgb_quad.rgbBlue = 0;
  // �������� ��� UINT �����
  const UINT color = rgb_quad.rgbBlue << 16 | rgb_quad.rgbGreen << 8 | rgb_quad.rgbRed;

  SelectObject(hdc_bits, this->bmp_loaded);

  // ���������� ���������� ������� ���� ���������
  XFORM xform_saved;
  GetWorldTransform(hdc, &xform_saved);

  // ������� �������
  auto xform_rotation = XFORM();
  xform_rotation.eM11 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform_rotation.eM12 = static_cast<FLOAT>(sin(this->angle + PI / 2));
  xform_rotation.eM21 = static_cast<FLOAT>(-sin(this->angle + PI / 2));
  xform_rotation.eM22 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform_rotation.eDx = static_cast<FLOAT>(0.0);
  xform_rotation.eDy = static_cast<FLOAT>(0.0);

  // ���������� �������
  SetGraphicsMode(hdc, GM_ADVANCED);
  SetWorldTransform(hdc, &xform_rotation);

  // ������� ���������������
  auto xform_scale = XFORM();
  xform_scale.eM11 = static_cast<FLOAT>(this->scale);
  xform_scale.eM12 = static_cast<FLOAT>(0.0);
  xform_scale.eM21 = static_cast<FLOAT>(0.0);
  xform_scale.eM22 = static_cast<FLOAT>(this->scale);
  xform_scale.eDx = static_cast<FLOAT>(0.0);
  xform_scale.eDy = static_cast<FLOAT>(0.0);

  // ������������ ������ - ���������� ���������������
  ModifyWorldTransform(hdc, &xform_scale, MWT_RIGHTMULTIPLY);

  // ������������������� ������� �������� �� ��������� ����
  auto entity_rectangle = CRect(this->GetIntX(), this->GetIntY(), this->GetIntX() + this->width, this->GetIntY() + this->height);
  DPtoLP(hdc, reinterpret_cast<LPPOINT>(&entity_rectangle), 2);
  const int entity_center_x = entity_rectangle.left - this->width / 2;
  const int entity_center_y = entity_rectangle.top - this->height / 2;

  // ��������� �������� � ������� ���������� ����� �� ����������
  TransparentBlt(hdc, entity_center_x, entity_center_y, this->width, this->height,
                 hdc_bits, 0, 0, this->width, this->height,
                 color);

  // ��������� �������� ��� ������ ����������� �����
  // BitBlt(hdc, entity_center_x, entity_center_y, this->width, this->height, hdcBits, 0, 0, SRCCOPY);

  // ������� ������� ���� ���������
  SetWorldTransform(hdc, &xform_saved);
}

void Entity::ProcessActions(const std::list<Entity*>& entities, const CRect& game_field) {
  // ������������ �������� ����������
  if (this->is_destroyed) {
    return;
  }

  // ��������� �������� �� ������������
  for (auto entity : entities) {
    // �������� ���� � ����� �� ����������
    if (this == entity) {
      continue;
    }

    // ���� ���� �������� �������� ���������� ������ - ��� ���� �� ����� �� ������.
    // ������ - ���� �� ����� ���������� �������, �� �������� ��������.
    if (this->owner == entity || entity->owner == this) {
      continue;
    }

    if (this->IsIntersectsWith(*entity)) {
      this->Hit(entity);
      entity->Hit(this);
      return;
    }
  }

  // �������� ������������ ��� ������ �� ������� �������� ������
  if (this->action_movement == ActionMovement::ToAngle) {
    double new_x = x + cos(angle) * speed;
    if ((new_x + width * scale / 2 <= 0) || (new_x - width * scale / 2 >= game_field.Width())) {
      this->Destroy();
      return;
    }

    double new_y = y - sin(angle) * speed;
    if ((new_y + height * scale / 2 <= 0) || (new_y - height * scale / 2 >= game_field.Height())) {
      this->Destroy();
      return;
    }

    x = new_x;
    y = new_y;
  }

  // ���� �������� �������������� �������
  if (this->is_rotating_right && !this->is_rotating_left) {
    this->SetAngle(this->GetAngle() - 0.1);
  }
  // ���� �������� �������������� ������
  else if (!this->is_rotating_right && this->is_rotating_left) {
    this->SetAngle(this->GetAngle() + 0.1);
  }
}

void Entity::Hit(Entity* by_whom) {
  this->health--;
  if (this->health <= 0) {
    this->Destroy(by_whom);
  }
}

void Entity::Destroy(Entity* by_whom) {
  this->is_destroyed = true;

  // ���� �������� �� ���� ���������� ���-���� - ������ �������
  if (by_whom == nullptr) {
    return;
  }

  // ����� - ������� ���� ��������, ��� ���������� ��� - ������������
  Entity* points_from_whom = this->GetMainOwner();
  Entity* points_to_who = by_whom->GetMainOwner();
  // ����� ���������, ��� �������� �� ���� �������� �� ������������.
  // ����� ����� ���� �� ��������� ���� ������� � ���������� ��, ������� ����.
  if (points_to_who != nullptr && points_from_whom != points_to_who) {
    points_to_who->entities_destroyed++;
    points_to_who->points_earned += this->self_points;
  }
}

bool Entity::IsIntersectsWith(const Entity& entity) const {
  // ���� ���� �� ��������� ���������� - �������� �� ������������
  if (this->is_destroyed || entity.is_destroyed) {
    return false;
  }

  // ����� - ��������� ���������� ����� �� ������� ��������
  const double distance_to_collide = this->GetIntersectRadius() + entity.GetIntersectRadius();
  const double real_distance = sqrt(pow(this->x - entity.x, 2) + pow(this->y - entity.y, 2));
  return real_distance <= distance_to_collide;
}

void Entity::AddOrReplaceInList(std::list<Entity*>& entities) {
  bool was_replaced = false;
  for (auto entity : entities) {
    if (entity != nullptr && entity->IsDestroyed()) {
      // delete entity;
    }
  }
  /*
  for (auto entity : entities) {
    if (entity == nullptr) {
      entity = this;
      was_replaced = true;
      break;
    }
  }*/

  if (!was_replaced) {
    // ��������� � ������, ��� ��� ��� ���������, ��������� �������� ����� ����������� �����
    entities.push_front(this);
  }
}
