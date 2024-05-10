#pragma once

#include "afxdialogex.h"
#include "Player.h"
#include <list>

#include "Globals.h"

class CSpaceBattleDlgGame : public CDialogEx {
private:
  DECLARE_DYNAMIC(CSpaceBattleDlgGame)

  // Идентификаторы таймеров
  enum class Timers {
    // Идентификатор таймера действий сущностей
    TimerClock,

    // Идентификатор таймера отрисовки
    TimerRedraw,

    // Идентификатор таймера времени игры
    TimerPlaying,

    // Идентификатор таймера чистки мусора в памяти
    TimerGarbageCollector
  };

  // Идентификаторы состояний игры
  enum class GameState {
    // Игра создана
    Created,

    // Игра приостановлена (пауза)
    Paused,

    // Игра идёт
    Playing,

    // Игра завершена
    Finished,
  };

  HDC hdc;

  HDC hdc_bits;

  CWnd* game_screen;

  // Область отрисовки игрового поля
  CRect game_screen_rectangle;

  // Область всего диалога с игровым полем
  CRect game_screen_rectangle_window;

  // Состояние игры
  GameState game_state;

  int time_playing_seconds_passed;

  // Кнопка паузы/продолжения игры
  CButton button_pause_or_resume_game;

  // Кнопка начала/завершения игры
  CButton button_start_or_end_game;

  // Текстовое поле с количеством заработанных очков
  CStatic cstatic_points_earned;

  // Текстовое поле с количеством уничтоженных врагов
  CStatic cstatic_enemies_defeated;

  // Текстовое поле с количеством здоровья игрока
  CStatic cstatic_health_left;

  // Текстовое поле со временем игры
  CStatic cstatic_time_playing;

  // Список всех сущностей (включая игрока)
  std::list<Entity*> entities;

  // Игрок
  Player* player;

  // Количество пройденных волн
  int waves_passed;

  // Время в секундах, спустя которое запускается новая волна
  int wave_time;

  // Количество генерируемых врагов за один раз
  int wave_enemies_count;

  // Количество секунд, прошедших с последней волны
  int seconds_passed_since_last_wave;

  // Количество пройденных волн с момента последнего уменьшения времени до следующей волны
  int waves_passed_since_last_wave_time_decrease;

  // Количество пройденных волн с момента последнего увеличения количества врагов волны
  int waves_passed_since_last_wave_enemies_count_increase;

  // Нужно ли очистить фон
  BOOL need_to_erase_background;
protected:
  // Иконка окна
  HICON window_icon;

  void DoDataExchange(CDataExchange* p_dx) override; // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  // Конструктор
  explicit CSpaceBattleDlgGame(CWnd* p_parent = nullptr);

  // Деструктор
  ~CSpaceBattleDlgGame() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_GAME };
#endif

  // Событие создания диалогового окна
  afx_msg BOOL OnInitDialog() override;

  // Событие изменения размеров формы
  afx_msg void OnSize(UINT n_type, int cx, int cy);

  // Событие очистки фона.
  // Убираем обработку по умолчанию, так как у нас реализована своя отрисовка.
  afx_msg BOOL OnEraseBkgnd(CDC* p_dc);

  // Событие отрисовки формы
  afx_msg void OnPaint();

  // Метод обработки событий формы.
  // Используем его для захвата нажатий клавиш, так как в OnKeyDown они не захватываются.
  afx_msg BOOL PreTranslateMessage(MSG* p_msg) override;

  // Событие возникновения таймера
  afx_msg void OnTimer(UINT_PTR n_id_event);

  // Событие закрытия окна
  afx_msg void OnClose();

  // Событие нажатия на кнопку возврата в меню
  afx_msg void OnBnClickedButtonReturnToTheMenu();

  // Событие нажатия на кнопку паузы/возобновления игры
  afx_msg void OnBnClickedButtonPauseOrResumeGame();

  // Событие нажатия на кнопку начала/завершения игры
  afx_msg void OnBnClickedButtonStartOrEndGame();
private:
  // Обновляет информацию об игровом поле
  // (например, при изменении его размеров - пересчитывает область отрисовки)
  void UpdateGameScreenInfo();

  // Приостанавливает игру (пауза)
  void PauseGame();

  // Возобновляет приостановленную игру
  void ResumeGame();

  // Завершает игру без сохранения рекорда
  void EndGameAndDoNotSaveRecord();

  // Завершает игру с сохранением рекорда
  void EndGameAndSaveRecord();

  // Располагает игрока по центру экрана
  void CenterPlayer() const;

  // Запускает новую волну врагов
  void CreateNewEnemiesWave();

  // Создаёт нового врага на поле
  void CreateNewEnemy();
public:
  afx_msg void OnNcPaint();
};
