#include "snake.h"
#include <string.h> // 用于memmove函数

// 在指定位置初始化蛇
void init_snake(Snake *snake, int start_x, int start_y)
{
  snake->length = 3; // 初始长度为3
  // 蛇头
  snake->body[0].x = start_x;
  snake->body[0].y = start_y;
  // 蛇身（初始为直线）
  snake->body[1].x = start_x - 1;
  snake->body[1].y = start_y;
  snake->body[2].x = start_x - 2;
  snake->body[2].y = start_y;

  snake->direction.x = 1; // 初始方向：向右
  snake->direction.y = 0;
}

// 根据当前方向移动蛇
void move_snake(Snake *snake)
{
  // 从尾部开始，将所有身体段向前移动一步
  // 旧的头部位置变成新的第二节，以此类推
  // 新的头部位置根据当前方向计算
  for (int i = snake->length - 1; i > 0; --i)
  {
    snake->body[i] = snake->body[i - 1];
  }

  // 更新头部位置
  snake->body[0].x += snake->direction.x;
  snake->body[0].y += snake->direction.y;
}

// 让蛇生长（通常在吃到食物后调用）
// 在尾部添加新的身体段
// 由于move_snake会移动所有段，实际上是在尾部延伸
void grow_snake(Snake *snake)
{
  if (snake->length < 100) // 检查是否超过最大长度
  {
    // 新的身体段会被添加在尾部移动前的位置
    // 在move_snake中，最后一个段实际上会成为新的"待添加"段
    // 如果我们简单地增加长度
    // 为了简单起见，当吃到食物时，我们可以在当前尾部位置添加新的段
    // 然后让move_snake()处理它
    // 一个常见的方法是将新段设置为与移动前的最后一个段相同
    // 现在，我们假设新段被添加在尾部当前位置
    // 更精确的方法是在旧尾部的坐标处添加它
    snake->length++;
    // 新的段会在下一次move_snake()中自然填充
    // 因为move_snake中的循环现在会多迭代一步
  }
}

// 检查自身碰撞
int check_self_collision(const Snake *snake)
{
  // 检查头部是否与身体的任何部分发生碰撞
  for (int i = 1; i < snake->length; ++i)
  {
    if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
    {
      // 666   23级区块链工程jyh原创贪吃蛇

      return 1; // 检测到碰撞
    }
  }
  return 0; // 没有碰撞
}

// 改变蛇的方向
// 防止蛇立即反向移动到自己身上
void change_snake_direction(Snake *snake, int dx, int dy)
{
  // 如果当前方向是水平的，新方向不能是相反的水平方向
  if (snake->direction.x != 0 && dx != 0 && snake->direction.x == -dx)
  {
    return;
  }
  // 如果当前方向是垂直的，新方向不能是相反的垂直方向
  if (snake->direction.y != 0 && dy != 0 && snake->direction.y == -dy)
  {
    return;
  }
  snake->direction.x = dx;
  snake->direction.y = dy;
}