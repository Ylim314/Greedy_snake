#include "game.h"
#include <stdlib.h> // 用于srand, rand函数
#include <time.h>   // 用于time函数

// 初始化游戏
void init_game(Game *game, int width, int height) // 666   23级区块链工程jyh原创贪吃蛇

{
  game->board_width = width;
  game->board_height = height;
  init_snake(&(game->snake), width / 2, height / 2); // 在游戏板中央初始化蛇
  srand(time(NULL));                                 // 初始化随机数生成器
  generate_food(&(game->food), game->board_width, game->board_height, &(game->snake));
  game->score = 0;
  game->speed = 200;     // 初始速度（毫秒延迟）
  game->state = MENU;    // 从菜单开始
  game->menu_option = 0; // 默认选择"开始游戏"
  game->start_time = 0;
  game->elapsed_time = 0;
}

// 处理墙壁碰撞（穿墙）
void handle_wall_collision(Game *game)
{
  Point *head = &(game->snake.body[0]);
  if (head->x < 0)
    head->x = game->board_width - 1;
  else if (head->x >= game->board_width)
    head->x = 0;

  if (head->y < 0)
    head->y = game->board_height - 1;
  else if (head->y >= game->board_height)
    head->y = 0;
}

// 处理蛇吃到食物的情况
void handle_eat_food(Game *game)
{
  Point *head = &(game->snake.body[0]);
  if (head->x == game->food.x && head->y == game->food.y)
  {
    grow_snake(&(game->snake)); // 蛇身增长
    game->score += 10;          // 增加分数
    generate_food(&(game->food), game->board_width, game->board_height, &(game->snake));

    // 每得50分增加速度（减少延迟）
    if (game->score % 50 == 0 && game->speed > 50)
    {
      game->speed -= 20; // 加快速度
    }
  }
}

// 更新游戏状态
void update_game(Game *game)
{
  if (game->state != PLAYING)
    return;

  move_snake(&(game->snake));  // 移动蛇
  handle_wall_collision(game); // 处理墙壁碰撞

  if (check_self_collision(&(game->snake))) // 检查是否撞到自己
  {
    game->state = GAME_OVER;
    return;
  }
  handle_eat_food(game); // 处理吃食物

  // 更新游戏时间
  game->elapsed_time = time(NULL) - game->start_time;
}

// 菜单选项向下移动
void menu_next_option(Game *game)
{
  if (game->state == MENU)
  {
    game->menu_option = (game->menu_option + 1) % 4; // 4个菜单选项循环
  }
}

// 菜单选项向上移动
void menu_prev_option(Game *game)
{
  if (game->state == MENU)
  {
    game->menu_option = (game->menu_option - 1 + 4) % 4;
  }
}

// 选择菜单选项
// 返回值：0=退出，1=开始游戏，2=关于，3=模式选择
int menu_select_option(Game *game)
{
  if (game->state == MENU)
  {
    switch (game->menu_option)
    {
    case 0: // 开始游戏
      game->state = PLAYING;
      init_snake(&(game->snake), game->board_width / 2, game->board_height / 2);
      generate_food(&(game->food), game->board_width, game->board_height, &(game->snake));
      game->score = 0;
      game->start_time = time(NULL);
      game->elapsed_time = 0;
      return 1;
    case 1: // 模式选择
      game->state = MODE_SELECT;
      return 2;
    case 2: // 关于游戏
      game->state = ABOUT;
      return 3;
    case 3: // 退出游戏
      return 0;
    }
  }
  else if (game->state == ABOUT)
  {
    game->state = MENU;
    return -1;
  }
  return -1;
}