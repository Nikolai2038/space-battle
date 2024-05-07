#pragma once
#include <vector>

// �������� �� ���� ����
class Entity {
  public:
    enum class ActionRotation {
      None,
      Right,
      Left
    };
    enum class ActionMovement {
      None,
      ToAngle
    };
  private:
    // ������� X �������� (������������ ������ �������� ����)
    double x;

    // ������� Y �������� (������������ ������ �������� ����)
    double y;

    // ����������� �������� � ��������
    double angle;

    // ���������� �� ����������� ��������
    BITMAP bmp_info;

    // ����������� ��������
    HBITMAP bmp_loaded;

    // ������ ��������
    LONG width;

    // ������ ��������
    LONG height;

    // �������� ��������������� �������� (1.0 - ��� ���������������)
    double scale;

    ActionRotation action_rotation;

    ActionMovement action_movement;

    bool is_destroyed;

    void Destroy();
  protected:
    /// ������ ����� ��������
    /// @param image_resource_id ID ������� ����������� ��������
    /// @param scale �������� ��������������� �������� (1.0 - ��� ���������������)
    Entity(int image_resource_id, double scale = 1);

    // �������� ��������
    double speed;

    std::vector<Entity*> childs;
  public:
    ~Entity();

    // ���������� ������� X ��������
    double GetX() const;

    // ���������� ������� X �������� (����� ������)
    int GetIntX() const;

    // ���������� ������� Y ��������
    double GetY() const;

    // ���������� ������� Y �������� (����� ������)
    int GetIntY() const;

    // ������������� ������� X ��������
    void SetX(double new_x);

    // ������������� ������� Y ��������
    void SetY(double new_y);

    // ������������� ����� ������� ��������
    void SetLocation(double new_x, double new_y);

    // ������������ ��������
    void Draw(HDC& hdc, HDC& hdcBits);

    // ������� �������� � � ��������� � ������������ �� ���� ������� �������
    void ProcessActions(CRect game_field);

    // ���������� ������ ��������
    LONG GetWidth() const;

    // ���������� ������ ��������
    LONG GetHeight() const;

    // ���������� ���� �������� �������� (� ��������)
    double GetAngle() const;

    // ������������� ���� �������� �������� (� ��������)
    void SetAngle(double new_angle);

    // ���������� �������� ��������������� ��������
    double GetScale() const;

    // ������������� �������� ��������������� ��������
    void SetScale(double new_scale);

    ActionRotation GetActionRotation();

    void SetActionRotation(ActionRotation new_action_rotation);

    ActionMovement GetActionMovement();

    void SetActionMovement(ActionMovement new_action_movement);

    // ���������� ������ ����� �������� ������� (�� ��� ������)
    int GetIntersectRadius();

    bool IsDestroyed();
};
