#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
// 666   23级区块链工程jyh原创贪吃蛇

// 游戏状态枚举
typedef enum
{
  MENU,       // 主菜单状态
  PLAYING,    // 游戏进行中状态
  PAUSED,     // 游戏暂停状态
  GAME_OVER,  // 游戏结束状态
  HELP,       // 帮助界面状态
  ABOUT,      // 关于界面状态
  SET_SPEED,  // 设置速度状态
  MODE_SELECT // 模式选择状态
} GameState;

// 游戏主结构体
typedef struct
{
  Snake snake;       // 蛇的结构体
  Food food;         // 食物的结构体
  int score;         // 游戏分数
  int speed;         // 游戏速度（控制更新间隔）
  GameState state;   // 当前游戏状态
  int board_width;   // 游戏板宽度
  int board_height;  // 游戏板高度
  int menu_option;   // 当前选中的菜单选项
  long start_time;   // 游戏开始时间（秒）
  long elapsed_time; // 已用时间（秒）
} Game;

// 游戏初始化函数
void init_game(Game *game, int width, int height);

// 更新游戏状态（在游戏循环中调用）
void update_game(Game *game);

// 处理游戏结束场景
void handle_game_over(Game *game);

// 处理蛇吃到食物的情况
void handle_eat_food(Game *game);

// 处理墙壁碰撞（穿墙）
void handle_wall_collision(Game *game);

// 菜单导航函数
void menu_next_option(Game *game);  // 选择下一个菜单选项
void menu_prev_option(Game *game);  // 选择上一个菜单选项
int menu_select_option(Game *game); // 选择当前菜单选项，返回1表示开始游戏，0表示退出，2表示帮助等

#endif // GAME_H