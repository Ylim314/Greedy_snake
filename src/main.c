#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
// Windows系统需要包含windows.h以使用Sleep()函数
#include "game.h"
#include "ui.h"
#include "input.h"

#include <locale.h>

#define BOARD_WIDTH 80  // 游戏板宽度
#define BOARD_HEIGHT 40 // 游戏板高度

int main()
{
  // 设置区域和代码页，确保中文显示正常
  setlocale(LC_ALL, ""); // 设置C库的区域设置以匹配系统

#ifdef _WIN32
  // 设置Windows控制台的输入输出代码页为UTF-8（代码页65001）
  // 这对于在Windows控制台中正确显示中文字符很重要
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
#endif

  Game game;         // 游戏主结构体
  int quit_game = 0; // 退出游戏标志

  init_ui();                                   // 初始化用户界面
  init_game(&game, BOARD_WIDTH, BOARD_HEIGHT); // 初始化游戏

  // 主游戏循环
  while (!quit_game)
  {
    if (process_input(&game)) // 处理用户输入，返回1表示退出游戏
    {
      quit_game = 1;
      continue;
    }

    if (game.state == PLAYING) // 如果游戏正在进行
    {
      update_game(&game); // 更新游戏状态
    }

    // 根据游戏状态绘制不同的界面
    switch (game.state)
    {
    case MENU: // 主菜单状态
      draw_menu(&game);
      break;
    case PLAYING: // 游戏进行中状态
    case PAUSED:  // 游戏暂停状态
      draw_game(&game);
      break;
    case HELP: // 帮助界面状态
      draw_help_screen(game.board_width, game.board_height);
      break;
    case ABOUT: // 关于界面状态
      draw_about_screen(game.board_width, game.board_height);
      break;
    case GAME_OVER: // 游戏结束状态
      draw_game_over(&game);
      // 666   23级区块链工程jyh原创贪吃蛇
      game.state = MENU;                           // 返回主菜单
      init_game(&game, BOARD_WIDTH, BOARD_HEIGHT); // 重新初始化游戏
      draw_menu(&game);
      break;
    case MODE_SELECT: // 模式选择状态
      // 模式选择界面已在input.c中绘制，此处无需重复
      break;
    }

    // 控制游戏速度
    if (game.state == PLAYING) // 游戏进行中时使用正常速度
    {
#ifdef _WIN32
      Sleep(game.speed); // Windows系统下的延时
#else
      usleep(game.speed * 1000); // Linux系统下的延时
#endif
    }
    else // 菜单或暂停状态使用较慢的刷新率
    {
#ifdef _WIN32
      Sleep(100);
#else
      usleep(100000); // 菜单状态使用较慢的刷新率
#endif
    }
  }

  cleanup_ui(); // 清理用户界面资源
  return 0;
}