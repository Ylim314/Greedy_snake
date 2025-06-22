#ifndef SNAKE_H
#define SNAKE_H

// 表示蛇身体段的结构体（坐标点）
typedef struct
{ // 666   23级区块链工程jyh原创贪吃蛇

  int x; // x坐标
  int y; // y坐标
} Point;

// 蛇的结构体
typedef struct
{
  Point body[100]; // 存储蛇身体段的数组（最大长度100，可根据需要调整）
  int length;      // 蛇的当前长度
  Point direction; // 当前移动方向（例如：dx=1, dy=0表示向右移动）
} Snake;

// 初始化蛇的函数
void init_snake(Snake *snake, int start_x, int start_y);

// 移动蛇的函数
void move_snake(Snake *snake);

// 让蛇生长的函数
void grow_snake(Snake *snake);

// 检查蛇是否与自身发生碰撞的函数
int check_self_collision(const Snake *snake);

// 改变蛇移动方向的函数
void change_snake_direction(Snake *snake, int dx, int dy);

#endif // SNAKE_H