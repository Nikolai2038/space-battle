#pragma once
#include "Point.h"

// �������� �� ���� ����
class Entity {
  private:
    // ������� �������� � ������������� �����������
    Point location;

    BITMAP bmp_info;
    HBITMAP bmp_loaded;

    // �������� ��������
    double SPEED = 2;

    // ����������� �������� � ��������
    double angle = 0;

    LONG width;
    LONG height;
  protected:
    Entity(int image_resource_id);
  public:
    // ���������� ������� ��������
    Point GetLocation() const;

    // ������������� ����� ������� ��������
    void SetLocation(const Point new_location);

    // ������������ ��������
    void Draw(CPaintDC& dc, HDC hdc, CRect game_screen_rectangle);

    // ������� �������� � � ��������� � ������������ �� ���� ������� �������
    void Move();

    LONG GetWidth();
    LONG GetHeight();
};
