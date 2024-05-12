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

  void Save() const;

  static std::list<Record> GetRecords();
};
