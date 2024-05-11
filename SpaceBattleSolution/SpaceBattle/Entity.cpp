#include "pch.h"
#include "Bullet.h"
#include "Config.h"
#include "Entity.h"
#include "Globals.h"
#include <stdexcept>

Entity::Entity() :
    x(0),
    y(0),
    angle(DEFAULT_ANGLE),
    is_rotating_right(false),
    is_rotating_left(false),
    is_accelerating(false),
    is_de_accelerating(false),
    action_movement(ActionMovement::None),
    is_destroyed(false),
    bmp_info(),
    bmp_loaded(nullptr),
    width(0),
    height(0),
    points_earned(0),
    entities_destroyed(0),
    self_points(DEFAULT_ENTITY_SELF_POINTS),
    is_invincible_for_game_field_borders_clocks_left(DEFAULT_INVINCIBLE_FOR_GAME_FIELD_BORDERS_SECONDS_LEFT * 1000 / TIMER_CLOCK_LOOP_IN_MS),
    owner(nullptr),
    scale(DEFAULT_IMAGE_SCALE),
    speed(DEFAULT_SPEED),
    min_speed(DEFAULT_SPEED_MIN),
    max_speed(DEFAULT_SPEED_MAX),
    acceleration(DEFAULT_ACCELERATION),
    de_acceleration(DEFAULT_DE_ACCELERATION),
    health(DEFAULT_ENTITY_HEALTH) {
}

Entity::Entity(const int image_resource_id) :
    Entity() {
  this->SetImage(image_resource_id);
}

void Entity::SetImage(const int image_resource_id) {
  // Загружаем изображение из ресурса
  CPngImage png_image;
  png_image.Load(image_resource_id, AfxGetResourceHandle());

  // Получаем объект изображения
  this->bmp_loaded = static_cast<HBITMAP>(png_image.Detach());

  // Получаем информацию об изображении
  GetObject(this->bmp_loaded, sizeof(BITMAP), &this->bmp_info);

  this->width = this->bmp_info.bmWidth;
  this->height = this->bmp_info.bmHeight;
}

Entity::~Entity() {
  DeleteObject(this->bmp_loaded);
}

double Entity::GetX() const {
  return this->x;
}

int Entity::GetIntX() const {
  return static_cast<int>(this->x);
}

void Entity::SetX(const double new_x) {
  this->x = new_x;
}

double Entity::GetY() const {
  return this->y;
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

void Entity::StartRotatingRight() {
  this->is_rotating_right = true;
}

void Entity::StopRotatingRight() {
  this->is_rotating_right = false;
}

void Entity::StartRotatingLeft() {
  this->is_rotating_left = true;
}

void Entity::StopRotatingLeft() {
  this->is_rotating_left = false;
}

void Entity::StartAccelerating() {
  this->is_accelerating = true;
}

void Entity::StopAccelerating() {
  this->is_accelerating = false;
}

void Entity::StartDeAccelerating() {
  this->is_de_accelerating = true;
}

void Entity::StopDeAccelerating() {
  this->is_de_accelerating = false;
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

LONG Entity::GetMaxVisibleRadiusOnField() const {
  return static_cast<int>(sqrt(pow(this->width, 2) + pow(this->height, 2)) / 2 * this->scale);
}

int Entity::GetPointsEarned() const {
  return this->points_earned;
}

int Entity::GetEntitiesDestroyed() const {
  return this->entities_destroyed;
}

Entity* Entity::GetMainOwner() {
  if (this->owner != nullptr) {
    return this->owner->GetMainOwner();
  }
  return this;
}

double Entity::GetScale() const {
  return this->scale;
}

void Entity::SetScale(const double new_scale) {
  this->scale = new_scale;
}

double Entity::GetSpeed() const {
  return this->speed;
}

void Entity::SetSpeed(const double new_speed) {
  this->speed = new_speed;
}

int Entity::GetHealth() const {
  return this->health;
}

int Entity::GetIntersectRadius() const {
  return static_cast<int>(max(this->width, this->height) * this->scale * INTERSECT_RADIUS_SCALE / 2);
}

void Entity::Draw(const HDC& hdc, const HDC& hdc_bits) const {
  // Уничтоженные сущности не рисуем
  if (this->is_destroyed) {
    return;
  }

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

  BLENDFUNCTION blend_function;
  blend_function.AlphaFormat = AC_SRC_ALPHA;
  blend_function.BlendFlags = 0;
  blend_function.BlendOp = AC_SRC_OVER;
  blend_function.SourceConstantAlpha = 255;
  // Отрисовка картинки с прозрачным цветом
  AlphaBlend(hdc, entity_center_x, entity_center_y, this->width, this->height,
             hdc_bits, 0, 0, this->width, this->height,
             blend_function);

  // Возврат ротации поля отрисовки
  SetWorldTransform(hdc, &xform_saved);
}

void Entity::ProcessActions(const std::list<Entity*>& entities, const CRect& game_field) {
  // Уничтоженные сущности игнорируем
  if (this->is_destroyed) {
    return;
  }

  // ----------------------------------------
  // Обработка поворота
  // ----------------------------------------
  // Если сущность поворачивается направо
  if (this->is_rotating_right && !this->is_rotating_left) {
    this->SetAngle(this->GetAngle() - 0.1);
  }
  // Если сущность поворачивается налево
  else if (!this->is_rotating_right && this->is_rotating_left) {
    this->SetAngle(this->GetAngle() + 0.1);
  }
  // ----------------------------------------

  // ----------------------------------------
  // Обработка ускорения
  // ----------------------------------------
  // Если сущность ускоряется
  if (this->is_accelerating && !this->is_de_accelerating) {
    if (this->speed + this->acceleration >= this->max_speed) {
      this->speed = this->max_speed;
    } else {
      this->speed += this->acceleration;
    }
  }
  // Если сущность замедляется
  else if (!this->is_accelerating && this->is_de_accelerating) {
    if (this->speed - this->de_acceleration <= this->min_speed) {
      this->speed = this->min_speed;
    } else {
      this->speed -= this->de_acceleration;
    }
  }
  // ----------------------------------------

  // ----------------------------------------
  // Обработка передвижения
  // ----------------------------------------
  if (this->action_movement == ActionMovement::ToAngle) {
    const double new_x = x + cos(this->angle) * this->speed;
    if ((new_x + this->width * this->scale / 2 <= 0) || (new_x - this->width * this->scale / 2 >= game_field.Width())) {
      // Сущность уничтожается при выходе за пределы игрового экрана
      // (если неуязвимость к границам поля закончилась)
      if (this->is_invincible_for_game_field_borders_clocks_left <= 0) {
        this->Destroy();
      }
    }

    const double new_y = y - sin(this->angle) * this->speed;
    if ((new_y + this->height * this->scale / 2 <= 0) || (new_y - this->height * this->scale / 2 >= game_field.Height())) {
      // Сущность уничтожается при выходе за пределы игрового экрана
      // (если неуязвимость к границам поля закончилась)
      if (this->is_invincible_for_game_field_borders_clocks_left <= 0) {
        this->Destroy();
      }
    }

    x = new_x;
    y = new_y;
  }

  // Уменьшаем время для неуязвимости
  if (this->is_invincible_for_game_field_borders_clocks_left > 0) {
    this->is_invincible_for_game_field_borders_clocks_left--;
  }

  // Проверяем сущности на столкновения
  for (const auto entity : entities) {
    // Сущность сама с собой не столкнётся
    if (this == entity) {
      continue;
    }

    // Если одна сущность является владельцем другой - они друг на друга не влияют.
    // Пример - пуля не может уничтожить корабль, из которого вылетела.
    if (this->owner == entity || entity->owner == this) {
      continue;
    }

    // Если сущности столкнулись - наносим урон каждой.
    // Так будет происходить, пока одна или сразу обе сущности не будут уничтожены.
    if (this->IsIntersectsWith(*entity)) {
      this->Hit(entity);
      entity->Hit(this);
      return;
    }
  }
  // ----------------------------------------
}

void Entity::Hit(Entity* by_whom) {
  this->health--;
  if (this->health <= 0) {
    this->Destroy(by_whom);
  }
}

void Entity::Destroy(Entity* by_whom) {
  this->is_destroyed = true;

  // Если сущность не была уничтожена кем-либо - просто выходим
  if (by_whom == nullptr) {
    return;
  }

  // Иначе - добавим очки сущности, что уничтожила эту - уничтожителю
  const Entity* points_from_whom = this->GetMainOwner();
  Entity* points_to_who = by_whom->GetMainOwner();
  // Также проверяем, что сущность не была дочерней от уничтожителя.
  // Иначе можно было бы создавать свои объекты и уничтожать их, получая очки.
  if (points_to_who != nullptr && points_from_whom != points_to_who) {
    points_to_who->entities_destroyed++;
    points_to_who->points_earned += this->self_points;
  }
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

void Entity::AddToList(std::list<Entity*>& entities) {
  // Добавляем в начало, так как при отрисовке, последние сущности будут перекрывать новые
  entities.push_front(this);
}
