#include "pch.h"
#include "Config.h"
#include "Record.h"
#include <fstream>

Record::Record(std::string player_name,
               const int points_earned,
               const int enemies_destroyed,
               const int time_playing_seconds_passed) :
    player_name(std::move(player_name)),
    points_earned(points_earned),
    enemies_destroyed(enemies_destroyed),
    time_playing_seconds_passed(time_playing_seconds_passed) {
}

void Record::Save() const {
  std::ofstream records_file(GetExeDirectory() + "/" + RECORDS_FILE_PATH, std::ios::out | std::ios::app);
  if (!records_file) {
    throw std::runtime_error("Failed to open records file for writing!");
  }
  records_file << this->player_name << RECORDS_FILE_DELIMITER;
  records_file << this->points_earned << RECORDS_FILE_DELIMITER;
  records_file << this->enemies_destroyed << RECORDS_FILE_DELIMITER;
  records_file << this->time_playing_seconds_passed;
  records_file << '\n';
  records_file.close();
}

std::list<Record> Record::GetRecords() {
  return std::list<Record>();
}
