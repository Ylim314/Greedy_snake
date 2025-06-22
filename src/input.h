#ifndef INPUT_H
#define INPUT_H

#include "game.h" // 使用Game结构体（用于改变方向和状态）

// 666   23级区块链工程jyh原创贪吃蛇

// 处理键盘输入
// 返回值：0表示游戏继续，1表示从菜单请求退出
int process_input(Game *game);

#endif // INPUT_H