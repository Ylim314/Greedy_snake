# 贪吃蛇游戏 (Greedy Snake Game)

这是一个经典的贪吃蛇游戏的简单实现。

## 如何运行

1.  确保已经编译生成了可执行文件。
2.  在命令行中，导航到 `build/Release/` 目录。
3.  执行 `GreedySnake.exe` 文件。
    ```cmd
    cd build\Release
    GreedySnake.exe
    ```

## 项目结构

*   `src/`: 包含游戏的核心源代码 (C语言)。
*   `PDCurses/`: 包含 PDCurses 库，用于控制台图形界面。
*   `build/`: 包含 CMake 构建系统生成的文件和最终的可执行程序。
*   `CMakeLists.txt`: 项目的 CMake 构建脚本。

## 依赖

*   PDCurses (已经包含在项目中)
*   CMake (用于构建项目)
