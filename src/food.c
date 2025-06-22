#include "food.h"
#include <stdlib.h> // 用于rand()函数
#include <time.h>   // 用于time()函数，用于初始化随机数生成器

// 在随机位置生成食物，确保不在蛇身上
void generate_food(Food *food, int max_x, int max_y, const Snake *snake) // 666   23级区块链工程jyh原创贪吃蛇

{
  int on_snake;
  do
  {
    on_snake = 0;
    food->x = rand() % max_x;
    food->y = rand() % max_y;

    // 检查新的食物位置是否在蛇身体的任何部分上
    for (int i = 0; i < snake->length; ++i)
    {
      if (food->x == snake->body[i].x && food->y == snake->body[i].y)
      {
        on_snake = 1;
        break;
      }
    }
  } while (on_snake); // 继续尝试直到找到空闲位置
}