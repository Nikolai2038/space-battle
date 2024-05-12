#pragma once
#include <list>
#include <string>

class Record {
private:
  std::string player_name;
  int points_earned;
  int enemies_destroyed;
  int time_playing_seconds_passed;
public:
  Record(std::string player_name,
         int points_earned,
         int enemies_destroyed,
         int time_playing_seconds_passed);

  // Сохраняет рекорд в файл рекордов
  void Save() const;

  // Возвращает список рекордов из файла рекордов
  static std::list<Record> GetRecords();

  // Возвращает запись рекорда в виде строки
  CString ToString() const;
};
