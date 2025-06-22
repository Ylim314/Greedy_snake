# 🐍 Greedy Snake Game

一个基于 C 语言和 PDCurses 库开发的经典贪吃蛇游戏，作为数据结构课程设计项目。

## ✨ 特性

- 🎮 经典贪吃蛇玩法
- 🎨 彩色终端界面
- ⚡ 三种难度模式（简单/中等/困难）
- 🌐 支持中文界面
- 🔄 穿墙模式
- ⏱️ 实时计时和计分
- 🎯 流畅的游戏体验

## 🚀 快速开始

### 环境要求

- Windows 10/11
- MSYS2 或 MinGW-w64
- PDCurses 库

### 安装步骤

1. **克隆项目**

```bash
git clone https://github.com/Ylim314/Greedy_snake.git
cd Greedy_snake
```

2. **安装依赖**

```bash
# 使用MSYS2
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-pdcurses

# 或使用MinGW-w64
# 下载并配置PDCurses库
```

3. **编译运行**

```bash
gcc -o snake.exe src/*.c -lpdcurses
./snake.exe
```

## 🎮 游戏控制

- **方向键**：控制蛇的移动
- **P 键**：暂停/继续游戏
- **ESC 键**：返回主菜单
- **回车键**：确认选择

## 🏗️ 项目结构

```
src/
├── main.c          # 主程序入口
├── game.h/c        # 游戏核心逻辑
├── snake.h/c       # 蛇的数据结构和操作
├── food.h/c        # 食物生成逻辑
├── ui.h/c          # 用户界面显示
└── input.h/c       # 输入处理
```

## 🔧 数据结构设计

- **蛇身**：使用数组实现，支持 O(1)移动操作
- **游戏状态**：枚举类型管理不同游戏状态
- **坐标系统**：Point 结构体表示位置信息

## 🤝 贡献指南

我们欢迎所有形式的贡献！

### 如何贡献

1. Fork 这个项目
2. 创建你的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交你的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开一个 Pull Request

### 贡献方向

- 🎨 界面优化和美化
- 🎵 添加音效支持
- 🗺️ 新游戏模式
- 📱 跨平台支持
- 🐛 Bug 修复
- 📚 文档完善

## 📝 开发计划

- [ ] 添加图形化界面（SDL/SFML）
- [ ] 实现游戏存档功能
- [ ] 添加网络对战模式
- [ ] 支持自定义地图
- [ ] 添加音效和背景音乐
- [ ] 移动端适配

## 📄 许可证

本项目采用 MIT 许可证

## 👨‍💻 作者

**Ylim314** - 数据结构课程设计项目

## 🙏 致谢

- PDCurses 库提供终端图形支持
- 感谢所有贡献者的支持和建议

## 📞 联系方式

- GitHub: [@Ylim314](https://github.com/Ylim314)
- 项目链接: [https://github.com/Ylim314/Greedy_snake](https://github.com/Ylim314/Greedy_snake)

---

⭐ 如果这个项目对你有帮助，请给它一个星标！
