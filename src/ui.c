#include "ui.h"
#include <pdcurses.h> // 用于curses函数
#include <string.h>   // 用于strlen函数

// 初始化用户界面
void init_ui()
{
  initscr();            // 启动curses模式
  cbreak();             // 禁用行缓冲，立即传递每个字符
  noecho();             // 不显示输入的字符
  curs_set(0);          // 隐藏光标
  keypad(stdscr, TRUE); // 启用功能键（如方向键）
  timeout(0);           // 非阻塞的getch()
  start_color();        // 启用颜色
  // 定义颜色对（ID，前景色，背景色）
  init_pair(1, COLOR_GREEN, COLOR_BLACK);  // 蛇的颜色
  init_pair(2, COLOR_RED, COLOR_BLACK);    // 食物的颜色
  init_pair(3, COLOR_WHITE, COLOR_BLACK);  // 墙壁/文本的颜色
  init_pair(4, COLOR_YELLOW, COLOR_BLACK); // 分数的颜色
  init_pair(5, COLOR_CYAN, COLOR_BLACK);   // 菜单高亮的颜色
}

// 绘制游戏界面
void draw_game(const Game *game)
{
  clear(); // 清屏

  // 绘制边框（墙壁）
  attron(COLOR_PAIR(3));
  for (int x = 0; x < game->board_width + 2; ++x)
  {
    mvprintw(0, x, "#");
    mvprintw(game->board_height + 1, x, "#");
  }
  for (int y = 0; y < game->board_height + 2; ++y)
  {
    mvprintw(y, 0, "#");
    mvprintw(y, game->board_width + 1, "#");
  }
  attroff(COLOR_PAIR(3));

  // 绘制蛇
  attron(COLOR_PAIR(1));
  for (int i = 0; i < game->snake.length; ++i)
  {
    mvprintw(game->snake.body[i].y + 1, game->snake.body[i].x + 1, "o"); // +1用于边框偏移
  }
  // 可选：用不同字符绘制蛇头
  if (game->snake.length > 0)
  {
    mvprintw(game->snake.body[0].y + 1, game->snake.body[0].x + 1, "@");
  }
  attroff(COLOR_PAIR(1));

  // 绘制食物
  attron(COLOR_PAIR(2));
  mvprintw(game->food.y + 1, game->food.x + 1, "*"); // +1用于边框偏移
  attroff(COLOR_PAIR(2));

  // 绘制分数（顶部居中）
  attron(COLOR_PAIR(4) | A_BOLD);
  char score_str[32];
  sprintf(score_str, "Score: %d", game->score);
  mvprintw(0, (game->board_width + 2 - (int)strlen(score_str)) / 2, "%s", score_str);
  attroff(COLOR_PAIR(4) | A_BOLD);
  // 666   23级区块链工程jyh原创贪吃蛇

  // 绘制时间（分数下方居中）
  char time_str[32];
  int min = game->elapsed_time / 60;
  int sec = game->elapsed_time % 60;
  sprintf(time_str, "Time: %02d:%02d", min, sec);
  attron(COLOR_PAIR(5) | A_BOLD);
  mvprintw(1, (game->board_width + 2 - (int)strlen(time_str)) / 2, "%s", time_str);
  attroff(COLOR_PAIR(5) | A_BOLD);

  if (game->state == PAUSED)
  {
    mvprintw(game->board_height / 2, game->board_width / 2 - 3, "PAUSED");
  }

  refresh(); // 刷新屏幕显示更改
}

// 绘制主菜单
void draw_menu(const Game *game)
{
  clear();
  int mid_y = game->board_height / 2;
  int mid_x = game->board_width / 2;

  const char *options[] = {"Start Game(开始游戏)", "Mode Select(模式选择)", "About Game(关于游戏)", "Exit Game(退出游戏)"};
  mvprintw(mid_y - 3, mid_x - strlen("Greedy Snake(贪吃蛇游戏)") / 2, "Greedy Snake(贪吃蛇游戏)");

  for (int i = 0; i < 4; ++i)
  {
    if (i == game->menu_option)
    {
      attron(COLOR_PAIR(5) | A_BOLD); // 高亮选中的选项
      mvprintw(mid_y + i, mid_x - strlen(options[i]) / 2 - 1, "> %s <", options[i]);
      attroff(COLOR_PAIR(5) | A_BOLD);
    }
    else
    {
      attron(COLOR_PAIR(3));
      mvprintw(mid_y + i, mid_x - strlen(options[i]) / 2, "%s", options[i]);
      attroff(COLOR_PAIR(3));
    }
  }
  mvprintw(game->board_height - 1, 2, "使用上下方向键导航，回车键选择。");
  refresh();
}

// 绘制帮助界面
void draw_help_screen(int width, int height)
{
  clear();
  mvprintw(height / 2 - 3, width / 2 - 10, "--- Game Help(游戏帮助) ---");
  mvprintw(height / 2 - 1, width / 2 - 15, "方向键控制蛇移动（↑↓←→）");
  mvprintw(height / 2 + 0, width / 2 - 15, "吃食物(*)增长并得分，撞到自己会失败");
  mvprintw(height / 2 + 1, width / 2 - 15, "墙壁可穿越，按'p'暂停/恢复");
  mvprintw(height / 2 + 2, width / 2 - 15, "游戏中可按ESC或q/Q随时返回主菜单");
  mvprintw(height / 2 + 4, width / 2 - 10, "按任意键返回菜单");
  refresh();
}

// 绘制关于界面
void draw_about_screen(int width, int height)
{
  clear();
  mvprintw(height / 2 - 2, width / 2 - 10, "--- About Game ---");
  mvprintw(height / 2 + 0, width / 2 - 15, "Greedy Snake v1.0");
  mvprintw(height / 2 + 1, width / 2 - 15, "Data Structures Course Project");
  mvprintw(height / 2 + 2, width / 2 - 15, "Data Structures Course Design Class 6 Senior");
  mvprintw(height / 2 + 4, width / 2 - 10, "按任意键返回菜单。");
  refresh();
}

// 绘制游戏结束界面
void draw_game_over(const Game *game)
{
  int mid_y = game->board_height / 2;
  int mid_x = game->board_width / 2;
  attron(COLOR_PAIR(2) | A_BOLD);
  mvprintw(mid_y - 1, mid_x - 5, "GAME OVER!");
  attroff(COLOR_PAIR(2) | A_BOLD);
  attron(COLOR_PAIR(4));
  mvprintw(mid_y + 1, mid_x - 6, "最终得分: %d", game->score);
  attroff(COLOR_PAIR(4));
  mvprintw(mid_y + 3, mid_x - 12, "按任意键返回菜单。");
  refresh();
  timeout(-1); // 等待按键（阻塞）
  getch();
  timeout(0); // 恢复非阻塞
}

// 绘制模式选择界面
void draw_mode_select_screen(const Game *game, int selected)
{
  clear();
  int mid_y = game->board_height / 2;
  int mid_x = game->board_width / 2;
  const char *modes[] = {"1. 简单模式 (Slow)", "2. 中等模式 (Medium)", "3. 困难模式 (Fast)"};
  mvprintw(mid_y - 2, mid_x - 6, "选择游戏模式:");
  for (int i = 0; i < 3; ++i)
  {
    if (i == selected)
    {
      attron(COLOR_PAIR(5) | A_BOLD);
      mvprintw(mid_y + i, mid_x - 8, "> %s <", modes[i]);
      attroff(COLOR_PAIR(5) | A_BOLD);
    }
    else
    {
      mvprintw(mid_y + i, mid_x - 6, "%s", modes[i]);
    }
  }
  mvprintw(mid_y + 4, mid_x - 12, "上下键选择，回车确定，ESC返回主菜单");
  refresh();
}

// 清理用户界面
void cleanup_ui()
{
  endwin(); // 结束curses模式
}