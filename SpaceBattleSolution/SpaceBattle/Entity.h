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

    double scale;
  protected:
    Entity(int image_resource_id, double scale = 1);
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
    void Draw(HDC& hdc, HDC& hdcBits);

    // ������� �������� � � ��������� � ������������ �� ���� ������� �������
    void Move();

    // ���������� ������ ��������
    LONG GetWidth() const;

    // ���������� ������ ��������
    LONG GetHeight() const;

    // ���������� ���� �������� �������� (� ��������)
    double GetAngle() const;

    // ������������� ���� �������� �������� (� ��������)
    void SetAngle(double new_angle);

    // ���������� ������� ��������
    double GetScale() const;

    // ������������� ������� ��������
    void SetScale(double new_scale);
};
