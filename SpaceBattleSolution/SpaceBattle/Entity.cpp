#include "pch.h"
#include "Entity.h"

#include <stdexcept>

#include "Config.h"
#include "Globals.h"

Entity::Entity(int image_resource_id, double scale) :
    x(0),
    y(0),
    bmp_info(BITMAP()),
    bmp_loaded(nullptr),
    speed(DEFAULT_SPEED),
    angle(0),
    scale(scale),
    action_rotation(ActionRotation::None),
    action_movement(ActionMovement::None),
    childs(std::vector<Entity*>()) {
  // ��������� ����������� �� �������
  CPngImage pngImage;
  pngImage.Load(image_resource_id, AfxGetResourceHandle());

  // �������� ������ �����������
  this->bmp_loaded = static_cast<HBITMAP>(pngImage.Detach());

  // �������� ���������� �� �����������
  GetObject(this->bmp_loaded, sizeof(BITMAP), (LPSTR) & this->bmp_info);

  this->width = bmp_info.bmWidth;
  this->height = bmp_info.bmHeight;
}

Entity::~Entity() {
  for (auto child : this->childs) {
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

void Entity::SetX(double new_x) {
  this->x = new_x;
}

void Entity::SetY(double new_y) {
  this->y = new_y;
}

void Entity::SetLocation(double new_x, double new_y) {
  this->SetX(new_x);
  this->SetY(new_y);
}

void Entity::Draw(HDC& hdc, HDC& hdcBits) {
  // ������� ������ �������� ��������
  for (auto child : this->childs) {
    child->Draw(hdc, hdcBits);
  }

  // ���� ����, ������� ����� ������ ����������
  RGBQUAD rgb_quad;
  rgb_quad.rgbRed = 0;
  rgb_quad.rgbGreen = 255;
  rgb_quad.rgbBlue = 0;
  rgb_quad.rgbReserved = 0;
  // �������� ��� UINT �����
  const UINT color = rgb_quad.rgbReserved << 32 | rgb_quad.rgbBlue << 16 | rgb_quad.rgbBlue << 16 | rgb_quad.rgbGreen << 8 | rgb_quad.rgbRed;

  SelectObject(hdcBits, this->bmp_loaded);

  // ���������� ���������� ������� ���� ���������
  XFORM xform_saved;
  GetWorldTransform(hdc, &xform_saved);

  // ������� �������
  XFORM xform_rotation;
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
  XFORM xform_scale;
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
                 hdcBits, 0, 0, this->width, this->height,
                 color);

  // ��������� �������� ��� ������ ����������� �����
  // BitBlt(hdc, entity_center_x, entity_center_y, this->width, this->height, hdcBits, 0, 0, SRCCOPY);

  // ������� ������� ���� ���������
  SetWorldTransform(hdc, &xform_saved);
}

void Entity::ProcessActions() {
  // ������� ������������ �������� ��������
  for (auto child : this->childs) {
    child->ProcessActions();
  }

  switch (this->action_movement) {
    case ActionMovement::ToAngle:
      this->SetX(this->GetX() + cos(angle) * speed);
      this->SetY(this->GetY() - sin(angle) * speed);
      break;
    default:
      break;
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

void Entity::SetAngle(double new_angle) {
  this->angle = new_angle;
}

double Entity::GetScale() const {
  return this->scale;
}

void Entity::SetScale(double new_scale) {
  this->scale = new_scale;
}

Entity::ActionRotation Entity::GetActionRotation() {
  return this->action_rotation;
}

void Entity::SetActionRotation(ActionRotation new_action_rotation) {
  this->action_rotation = new_action_rotation;
}

Entity::ActionMovement Entity::GetActionMovement() {
  return this->action_movement;
}

void Entity::SetActionMovement(ActionMovement new_action_movement) {
  this->action_movement = new_action_movement;
}
