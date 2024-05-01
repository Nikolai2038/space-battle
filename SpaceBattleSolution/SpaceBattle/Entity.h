#pragma once

// �������� �� ���� ����
class Entity {
  private:
    // ������� ��������
    double x;
    double y;

    // ����������� �������� � ��������
    double angle;

    // �������� ��������
    double speed;

    BITMAP bmp_info;
    HBITMAP bmp_loaded;

    LONG width;
    LONG height;
  protected:
    Entity(int image_resource_id);
  public:
    int GetIntX() const;
    int GetIntY() const;

    double GetX() const;
    double GetY() const;

    void SetX(double new_x);
    void SetY(double new_y);

    // ������������� ����� ������� ��������
    void SetLocation(int new_x, int new_y);

    // ������������ ��������
    void Draw(HDC hdc) const;

    // ������� �������� � � ��������� � ������������ �� ���� ������� �������
    void Move();

    LONG GetWidth() const;
    LONG GetHeight() const;

    double GetAngle() const;
    void SetAngle(double new_angle);
};
