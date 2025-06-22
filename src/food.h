#ifndef FOOD_H
#define FOOD_H

#include "snake.h" // 使用Point结构体

// 666   23级区块链工程jyh原创贪吃蛇

typedef Point Food; // 食物本质上就是地图上的一个点

// 在随机位置生成新的食物
// 需要游戏板尺寸和蛇的位置信息，以避免食物生成在蛇身上
void generate_food(Food *food, int max_x, int max_y, const Snake *snake);

#endif // FOOD_H