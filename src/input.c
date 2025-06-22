#include "input.h"
#include "ui.h"
#include <pdcurses.h> // 用于getch(), KEY_UP等函数
// #include <curses.h>   // 如果路径配置正确的话

// 处理输入
int process_input(Game *game)
{
  int ch = getch(); // 获取字符（由于timeout(0)设置为非阻塞）

  if (game->state == MENU) // 在菜单状态下
  {
    switch (ch)
    {
    case KEY_UP:
      menu_prev_option(game); // 向上选择菜单选项
      break;
    case KEY_DOWN:
      menu_next_option(game); // 向下选择菜单选项
      break;
    case '\n': // 回车键
    case KEY_ENTER:
    {
      int action = menu_select_option(game);
      if (action == 0)
        return 1; // 退出游戏
                  // 如果action为1（开始游戏），2（帮助），3（关于），状态已经改变
    }
    break;
    }
  }
  else if (game->state == PLAYING) // 在游戏进行状态下
  {
    switch (ch)
    {
    case KEY_UP:
      change_snake_direction(&(game->snake), 0, -1); // dx=0, dy=-1（向上）
      break;
    case KEY_DOWN:
      change_snake_direction(&(game->snake), 0, 1); // dx=0, dy=1（向下）
      break;
    case KEY_LEFT:
      change_snake_direction(&(game->snake), -1, 0); // dx=-1, dy=0（向左）
      break;
    case KEY_RIGHT:
      change_snake_direction(&(game->snake), 1, 0); // dx=1, dy=0（向右）
      break;
    case 'p': // 暂停游戏
    case 'P':
      game->state = PAUSED;
      break;
    case 'q': // 用于测试时快速退出，或添加到菜单中
    case 'Q':
    case 27: // ESC键
      game->state = MENU;
      break;
    }
  }
  else if (game->state == PAUSED) // 在暂停状态下
  {
    if (ch == 'p' || ch == 'P')
    {
      game->state = PLAYING; // 按P继续游戏
    }
  }
  // 666   23级区块链工程jyh原创贪吃蛇

  else if (game->state == ABOUT) // 在关于界面下
  {
    if (ch != ERR)
    {
      game->state = MENU; // 按任意键返回菜单
    }
  }
  else if (game->state == GAME_OVER || game->state == HELP) // 在游戏结束或帮助界面下
  {
    if (ch != ERR)
    {
      menu_select_option(game); // 按任意键返回菜单
    }
  }
  else if (game->state == MODE_SELECT) // 在模式选择界面下
  {
    static int selected = 0;
    if (ch == KEY_UP)
    {
      selected = (selected + 2) % 3; // 向上选择模式
    }
    else if (ch == KEY_DOWN)
    {
      selected = (selected + 1) % 3; // 向下选择模式
    }
    else if (ch == '\n' || ch == KEY_ENTER)
    {
      if (selected == 0)
        game->speed = 300; // 简单模式
      else if (selected == 1)
        game->speed = 150; // 中等模式
      else if (selected == 2)
        game->speed = 70; // 困难模式
      game->state = MENU;
      selected = 0;
    }
    else if (ch == 27) // ESC键
    {
      game->state = MENU;
      selected = 0;
    }
    draw_mode_select_screen(game, selected); // 绘制模式选择界面
  }
  return 0; // 继续游戏
}