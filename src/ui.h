#ifndef UI_H
#define UI_H

#include "game.h"
#include <pdcurses.h> // 包含curses库
                      // 666   23级区块链工程jyh原创贪吃蛇

// 初始化ncurses屏幕
void init_ui();

// 绘制游戏界面，包括游戏板、蛇、食物和分数
void draw_game(const Game *game);

// 绘制主菜单
void draw_menu(const Game *game);

// 绘制帮助界面
void draw_help_screen(int width, int height);

// 绘制关于界面
void draw_about_screen(int width, int height);

// 绘制游戏结束信息
void draw_game_over(const Game *game);

// 绘制模式选择界面
void draw_mode_select_screen(const Game *game, int selected);

// 清理ncurses屏幕资源
void cleanup_ui();

#endif // UI_H