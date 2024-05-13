#include "pch.h"
#include "Config.h"
#include "Record.h"
#include <fstream>
#include <sstream>
#include <vector>

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
  // Итоговый возвращаемый список рекордов
  std::list<Record> records;
  // Открываем файл на чтение рекордов (используем "append", чтобы создать файл, если он ещё не существует)
  std::ifstream records_file(GetExeDirectory() + "/" + RECORDS_FILE_PATH, std::ios::in | std::ios::app);
  if (!records_file) {
    throw std::runtime_error("Failed to open records file for reading!");
  }
  // Read file by lines
  std::string file_line;
  while (std::getline(records_file, file_line)) {
    if (file_line.empty()) {
      continue;
    }

    // Split line by delimiter
    std::stringstream ss(file_line);
    std::string word;
    std::vector<std::string> words;
    while (std::getline(ss, word, RECORDS_FILE_DELIMITER)) {
      words.push_back(word);
    }

    std::string player_name = words.at(0);
    int points_earned = atoi(words.at(1).c_str());
    int enemies_destroyed = atoi(words.at(2).c_str());
    int time_playing_seconds_passed = atoi(words.at(3).c_str());

    // Создаём объект рекорда
    Record record(player_name, points_earned, enemies_destroyed, time_playing_seconds_passed);
    // Добавляем его в список рекордов
    records.push_back(record);
  }

  records_file.close();

  // Сортируем список рекордов от больших к меньшим
  records.sort([](const Record& record_1, const Record& record_2) -> bool {
    return record_1.points_earned > record_2.points_earned;
  });

  return records;
}

CString Record::ToString() const {
  CString s;
  s.Format(L"Player %hs scored %d points (%d enemies destroyed) and lasts %d seconds",
           this->player_name.data(),
           this->points_earned,
           this->enemies_destroyed,
           this->time_playing_seconds_passed);
  return s;
}
