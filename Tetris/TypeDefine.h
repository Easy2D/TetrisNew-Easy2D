#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define BRICK_WIDTH 30     // 砖块边长
#define N_BRICK 4          // 每个形状态包含的砖块数

#define WINDOW_WIDTH 16    // 总窗口宽度（单位：BRICK_WIDTH）
#define WINDOW_HEIGHT 21   // 总窗口高度（单位：BRICK_WIDTH）

#define BOARD_WIDTH 12     // 游戏面板宽度（单位：BRICK_WIDTH）
#define BOARD_HEIGHT 21    // 游戏面板高度（单位：BRICK_WIDTH）

#define PREVIEW_BRICK_WIDTH 15 // 预览区砖块边长
#define PREVIEW_WIDTH 5 // 预览边长（单位：PREVIEW_BRICK_WIDTH）

enum class Color_t
{
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    PURPLE,
    GRAY,
};

enum class Shape_t
{
    I_SHAPE,
    J_SHAPE,
    L_SHAPE,
    O_SHAPE,
    S_SHAPE,
    T_SHAPE,
    Z_SHAPE,
};

enum class Direction_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DROP
};

class Pos_t
{
public:
    Pos_t() : X(0), Y(0) {};
    Pos_t(int x, int y) : X(x), Y(y) {};
    int X;
    int Y;

    inline const Pos_t operator + (const Pos_t & other) const
    {
        return Pos_t(X + other.X, Y + other.Y);
    }

    inline const Pos_t operator - (const Pos_t & other) const
    {
        return Pos_t(X - other.X, Y - other.Y);
    }
};

#endif