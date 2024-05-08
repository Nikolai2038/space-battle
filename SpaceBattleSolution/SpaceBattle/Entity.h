#pragma once

#include <list>

// �������� �� ���� ����
class Entity {
protected:
  // �������� �������� ��������
  enum class ActionMovement {
    // �������� �� ���������
    None,
    // �������� ��������� � �����������, � ������� ��� ������� (���� ��������)
    ToAngle
  };
private:
  // ������� X �������� (������������ ������ �������� ����)
  double x;

  // ������� Y �������� (������������ ������ �������� ����)
  double y;

  // ����������� �������� � ��������
  double angle;

  // ��������� �� �������� � ������ �������
  bool is_rotating_right;

  // ��������� �� �������� � ����� �������
  bool is_rotating_left;

  // �������� ��������, ������������ ��������� � ������ ������
  ActionMovement action_movement;

  // �������� �� �������� ������������.
  // ������������ �������� �� ���������� �������� � �� ��������.
  bool is_destroyed;

  // ���������� �� ����������� ��������
  BITMAP bmp_info;

  // ����������� ��������
  HBITMAP bmp_loaded;

  // ������ ��������
  LONG width;

  // ������ ��������
  LONG height;

  // ������� ����� ���������� ��� ��������
  int points_earned;

  // ������� ��������� ���������� ��� ��������
  int entities_destroyed;

  // ������� ����� ����� ��� ��������
  int self_points;
protected:
  Entity* owner;

  // �������� ��������������� �������� (1.0 - ��� ���������������)
  double scale;

  // �������� ��������
  double speed;

  // ���������� ������ ��������.
  // ���� ������������ �������� ���� ������� ��������.
  int health;

  /// ������ ����� ��������
  /// @param image_resource_id ID ������� ����������� ��������
  explicit Entity(int image_resource_id);
public:
  ~Entity();

  // ���������� ������� X ��������
  double GetX() const;

  // ���������� ������� X �������� (����� ������)
  int GetIntX() const;

  /// ������������� ������� X ��������
  /// @param new_x ����� ������� X
  void SetX(double new_x);

  // ���������� ������� Y ��������
  double GetY() const;

  // ���������� ������� Y �������� (����� ������)
  int GetIntY() const;

  /// ������������� ������� Y ��������
  /// @param new_y ����� ������� Y
  void SetY(double new_y);

  // ������������� ����� ������� ��������
  /// @param new_x ����� ������� X
  /// @param new_y ����� ������� Y
  void SetLocation(double new_x, double new_y);

  // ���������� ���� �������� �������� (� ��������)
  double GetAngle() const;

  // ������������� ���� �������� �������� (� ��������)
  void SetAngle(double new_angle);

  // �������� ����� �������������� �������
  void StartRotatingRight() {
    this->is_rotating_right = true;
  }

  // �������� ���������� �������������� �������
  void StopRotatingRight() {
    this->is_rotating_right = false;
  }

  // �������� ����� �������������� ������
  void StartRotatingLeft() {
    this->is_rotating_left = true;
  }

  // �������� ���������� �������������� ������
  void StopRotatingLeft() {
    this->is_rotating_left = false;
  }

  // ���������� �������� ��������, ������������ ��������� � ������ ������
  ActionMovement GetActionMovement() const;

  // ������������� �������� ��������, ������������ ��������� � ������ ������
  /// @param new_action_movement ����� �������� ��������
  void SetActionMovement(ActionMovement new_action_movement);

  // �������� �� �������� ������������
  bool IsDestroyed() const;

  // ���������� ������ ��������
  LONG GetWidth() const;

  // ���������� ������ ��������
  LONG GetHeight() const;

  // ���������� ���������� ������������ �����
  int GetPointsEarned() const;

  // ���������� ���������� ������������ ��������� ���� ���������
  int GetEntitiesDestroyed() const;

  // ���������� ������ ������� ��������� ���� �������� (����������)
  Entity* GetMainOwner();

  // ���������� �������� ��������������� ��������
  double GetScale() const;

  // ������������� �������� ��������������� ��������
  void SetScale(double new_scale);

  // ���������� ���������� �������� ��������
  int GetHealth() const;

  // ���������� ������ ����� �������� ������� (�� ��� ������)
  int GetIntersectRadius() const;

  // ������������ ��������
  void Draw(const HDC& hdc, const HDC& hdc_bits) const;

  // ������������ �������� �������� � ������� ������� �������
  void ProcessActions(const std::list<Entity*>& entities, const CRect& game_field);
private:
  // ��������� �������� �������� �� ���� �������.
  // ���� �������� �� ��������� - �������� ����� ����������.
  void Hit(Entity* by_whom);

  // �������� �������� ��� ������������
  void Destroy(Entity* by_whom = nullptr);

  // ���������, ������������ �� ��� �������� � ���������
  bool IsIntersectsWith(const Entity& entity) const;
public:
  // ��������� ��� �������� � ��������� ������ (������� ����� ������������ �������� � ���� ������)
  void AddToList(std::list<Entity*>& entities);
};
