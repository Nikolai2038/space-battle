#include "pch.h"
#include "Entity.h"

#include <stdexcept>

#include "Config.h"
#include "Globals.h"

void Entity::Destroy() {
  this->is_destroyed = true;
}

Entity::Entity(int image_resource_id, double scale) :
    x(0),
    y(0),
    angle(DEFAULT_ANGLE),
    scale(scale),
    action_rotation(ActionRotation::None),
    action_movement(ActionMovement::None),
    is_destroyed(false),
    speed(DEFAULT_SPEED),
    childs(std::vector<Entity*>()) {
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

Entity::~Entity() {
  for (const auto child : this->childs) {
    delete child;
  }
}

int Entity::GetIntX() const {
  return static_cast<int>(this->x);
}

int Entity::GetIntY() const {
  return static_cast<int>(this->y);
}

double Entity::GetX() const {
  return x;
}

double Entity::GetY() const {
  return y;
}

void Entity::SetX(const double new_x) {
  this->x = new_x;
}

void Entity::SetY(const double new_y) {
  this->y = new_y;
}

void Entity::SetLocation(const double new_x, const double new_y) {
  this->SetX(new_x);
  this->SetY(new_y);
}

void Entity::Draw(HDC& hdc, HDC& hdc_bits) const {
  // Сначала рисуем дочерние сущности
  for (auto child : this->childs) {
    child->Draw(hdc, hdc_bits);
  }

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

void Entity::ProcessActions(CRect game_field) {
  // Сначала обрабатываем дочерние сущности
  for (auto child : this->childs) {
    child->ProcessActions(game_field);
  }

  if (this->is_destroyed) {
    return;
  }

  if (this->action_movement == ActionMovement::ToAngle) {
    double new_x = x + cos(angle) * speed;
    if ((new_x + width * scale / 2 <= 0) || (new_x - width * scale / 2 >= game_field.Width())) {
      Destroy();
      return;
    }

    double new_y = y - sin(angle) * speed;
    if ((new_y + height * scale / 2 <= 0) || (new_y - height * scale / 2 >= game_field.Height())) {
      Destroy();
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
    default:
      break;
  }
}

LONG Entity::GetWidth() const {
  return width;
}

LONG Entity::GetHeight() const {
  return height;
}

double Entity::GetAngle() const {
  return this->angle;
}

void Entity::SetAngle(const double new_angle) {
  this->angle = new_angle;
}

double Entity::GetScale() const {
  return this->scale;
}

void Entity::SetScale(const double new_scale) {
  this->scale = new_scale;
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

int Entity::GetIntersectRadius() const {
  return static_cast<int>(max(width, height) * scale * INTERSECT_RADIUS_SCALE) / 2;
}

bool Entity::IsDestroyed() const {
  return is_destroyed;
}
