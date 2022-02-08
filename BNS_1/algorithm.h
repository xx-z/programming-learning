#ifndef ALGORITHM_H
#define ALGORITHM_H
#define  T_WHITE 0x0f
#define  T_RED 0x0c

//最大キー入力回数
#define MAXKEY 30
//最大マップサイズ
#define MAXMAP 20

//説明までの間隔
#define EXPLAIN_INTERVAL 8
//マップから矢印までの間隔
#define MAP_INTERVAL 10

//実行時のスピード
#define EXECUTIONSPEED 300

//クリアテキスト行数
#define GAMECLEARTXT 1
//失敗テキスト行数
#define GAMEFAILURE 2
//パズルゲームテキスト行数
#define EXPLAIN 3

//キー入力
#define ARROW 0xe0
#define BACKSPACE 0x08
#define ENTER 0x0d
#define ESC 0x1b

//矢印キー入力
#define UP 0x48
#define DOWN 0x50
#define RIGHT 0x4d
#define LEFT 0x4b

#define NOPLACE '0'
#define OKPLACE '1'
#define PLAYER '2'
#define WALL '3'

#endif