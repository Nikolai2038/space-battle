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
    action_rotation(ActionRotation::None),
    action_movement(ActionMovement::None),
    health(DEFAULT_ENTITY_HEALTH),
    is_destroyed(false),
    scale(DEFAULT_IMAGE_SCALE),
    speed(DEFAULT_SPEED),
    owner(nullptr) {
  // Загружаем изображение из ресурса
  CPngImage pngImage;
  pngImage.Load(image_resource_id, AfxGetResourceHandle());

  // Получаем объект изображения
  this->bmp_loaded = static_cast<HBITMAP>(pngImage.Detach());

  // Получаем информацию об изображении
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

Entity::ActionRotation Entity::GetActionRotation() const {
  return this->action_rotation;
}

void Entity::SetActionRotation(const ActionRotation new_action_rotation) {
  this->action_rotation = new_action_rotation;
}

Entity::ActionMovement Entity::GetActionMovement() const {
  return this->action_movement;
}

void Entity::SetActionMovement(const ActionMovement new_action_movement) {
  this->action_movement = new_action_movement;
}

LONG Entity::GetWidth() const {
  return width;
}

LONG Entity::GetHeight() const {
  return height;
}

double Entity::GetScale() const {
  return this->scale;
}

void Entity::SetScale(const double new_scale) {
  this->scale = new_scale;
}

int Entity::GetIntersectRadius() const {
  return static_cast<int>(max(width, height) * scale * INTERSECT_RADIUS_SCALE / 2);
}

void Entity::Draw(const HDC& hdc, const HDC& hdc_bits) const {
  if (this->is_destroyed) {
    return;
  }

  // Цвет фона, который будет заменён прозрачным
  auto rgb_quad = RGBQUAD();
  rgb_quad.rgbRed = 0;
  rgb_quad.rgbGreen = 255;
  rgb_quad.rgbBlue = 0;
  // Получаем код UINT цвета
  const UINT color = rgb_quad.rgbBlue << 16 | rgb_quad.rgbGreen << 8 | rgb_quad.rgbRed;

  SelectObject(hdc_bits, this->bmp_loaded);

  // Сохранение параметров ротации поля отрисовки
  XFORM xform_saved;
  GetWorldTransform(hdc, &xform_saved);

  // Матрица ротации
  auto xform_rotation = XFORM();
  xform_rotation.eM11 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform_rotation.eM12 = static_cast<FLOAT>(sin(this->angle + PI / 2));
  xform_rotation.eM21 = static_cast<FLOAT>(-sin(this->angle + PI / 2));
  xform_rotation.eM22 = static_cast<FLOAT>(cos(this->angle - PI / 2));
  xform_rotation.eDx = static_cast<FLOAT>(0.0);
  xform_rotation.eDy = static_cast<FLOAT>(0.0);

  // Применение ротации
  SetGraphicsMode(hdc, GM_ADVANCED);
  SetWorldTransform(hdc, &xform_rotation);

  // Матрица масштабирования
  auto xform_scale = XFORM();
  xform_scale.eM11 = static_cast<FLOAT>(this->scale);
  xform_scale.eM12 = static_cast<FLOAT>(0.0);
  xform_scale.eM21 = static_cast<FLOAT>(0.0);
  xform_scale.eM22 = static_cast<FLOAT>(this->scale);
  xform_scale.eDx = static_cast<FLOAT>(0.0);
  xform_scale.eDy = static_cast<FLOAT>(0.0);

  // Перемножение матриц - применение масштабирования
  ModifyWorldTransform(hdc, &xform_scale, MWT_RIGHTMULTIPLY);

  // Реинтерпретирование позиции сущности на повёрнутом поле
  auto entity_rectangle = CRect(this->GetIntX(), this->GetIntY(), this->GetIntX() + this->width, this->GetIntY() + this->height);
  DPtoLP(hdc, reinterpret_cast<LPPOINT>(&entity_rectangle), 2);
  const int entity_center_x = entity_rectangle.left - this->width / 2;
  const int entity_center_y = entity_rectangle.top - this->height / 2;

  // Отрисовка картинки с заменой указанного цвета на прозрачный
  TransparentBlt(hdc, entity_center_x, entity_center_y, this->width, this->height,
                 hdc_bits, 0, 0, this->width, this->height,
                 color);

  // Отрисовка картинки без замены прозрачного цвета
  // BitBlt(hdc, entity_center_x, entity_center_y, this->width, this->height, hdcBits, 0, 0, SRCCOPY);

  // Возврат ротации поля отрисовки
  SetWorldTransform(hdc, &xform_saved);
}

void Entity::ProcessActions(const std::list<Entity*>& entities, const CRect& game_field) {
  // Уничтоженные сущности игнорируем
  if (this->is_destroyed) {
    return;
  }

  // Проверяем сущности на столкновения
  for (auto entity : entities) {
    // Сущность сама с собой не столкнётся
    if (this == entity) {
      continue;
    }

    // Если одна сущность является владельцем другой - они друг на друга не влияют.
    // Пример - пуля не может уничтожить корабль, из которого вылетела.
    if (this->owner == entity || entity->owner == this) {
      continue;
    }

    if (this->IsIntersectsWith(*entity)) {
      this->Destroy();
      entity->Destroy();
      return;
    }
  }

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

  switch (this->action_rotation) {
    case ActionRotation::Right:
      this->SetAngle(this->GetAngle() - 0.1);
      break;
    case ActionRotation::Left:
      this->SetAngle(this->GetAngle() + 0.1);
      break;
    case ActionRotation::None:
      break;
    default:
      break;
  }
}

void Entity::Destroy() {
  this->is_destroyed = true;
}

bool Entity::IsIntersectsWith(const Entity& entity) const {
  // Если одна из сущностей уничтожена - сущности не сталкиваются
  if (this->is_destroyed || entity.is_destroyed) {
    return false;
  }

  // Иначе - проверяем расстояние между их точками коллизии
  const double distance_to_collide = this->GetIntersectRadius() + entity.GetIntersectRadius();
  const double real_distance = sqrt(pow(this->x - entity.x, 2) + pow(this->y - entity.y, 2));
  return real_distance <= distance_to_collide;
}
