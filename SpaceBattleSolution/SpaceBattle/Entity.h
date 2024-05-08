#pragma once

#include <list>

// �������� �� ���� ����
class Entity {
public:
  // �������� �������� ��������
  enum class ActionRotation {
    // �������� �� ��������������
    None,
    // �������� �������������� �� ������� ������� (�������)
    Right,
    // �������� �������������� ������ ������� ������� (������)
    Left
  };
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

  // �������� ��������, ������������ ��������� � ������ ������
  ActionRotation action_rotation;

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
protected:
  /// ������ ����� ��������
  /// @param image_resource_id ID ������� ����������� ��������
  explicit Entity(int image_resource_id);

  Entity* owner;

  // �������� ��������������� �������� (1.0 - ��� ���������������)
  double scale;

  // �������� ��������
  double speed;

  // ���������� ������ ��������.
  // ���� ������������ �������� ���� ������� ��������.
  int health;
public:
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

  // ���������� �������� ��������, ������������ ��������� � ������ ������
  ActionRotation GetActionRotation() const;

  // ������������� �������� ��������, ������������ ��������� � ������ ������
  /// @param new_action_rotation ����� �������� ��������
  void SetActionRotation(ActionRotation new_action_rotation);

  // ���������� �������� ��������, ������������ ��������� � ������ ������
  ActionMovement GetActionMovement() const;

  // ������������� �������� ��������, ������������ ��������� � ������ ������
  /// @param new_action_movement ����� �������� ��������
  void SetActionMovement(ActionMovement new_action_movement);

  // ���������� ������ ��������
  LONG GetWidth() const;

  // ���������� ������ ��������
  LONG GetHeight() const;

  // ���������� �������� ��������������� ��������
  double GetScale() const;

  // ������������� �������� ��������������� ��������
  void SetScale(double new_scale);

  // ���������� ������ ����� �������� ������� (�� ��� ������)
  int GetIntersectRadius() const;

  // ������������ ��������
  void Draw(const HDC& hdc, const HDC& hdc_bits) const;

  // ������������ �������� �������� � ������� ������� �������
  void ProcessActions(const std::list<Entity*>& entities, const CRect& game_field);
private:
  // �������� �������� ��� ������������
  void Destroy();

  bool IsIntersectsWith(const Entity& entity) const;
};
