#if !defined __GAMESTRUCTMACRO
#define __GAMESTRUCTMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <ddraw.h>

struct WAVE_DATA	//使用する Wave ファイルのデータを管理するための構造体
{
	char *	lpFileName;		// 使用するデータのファイルパス
	long	Vol;			// ボリューム
	long	Pan;			// パン
	DWORD	Frequency;		// 周波数
};
struct ANIME_DATA	//アニメーション用構造体の型の定義
{
	int Num;		//アニメーションする絵の1枚の絵の番号を扱う
	int TimeMax;	//表示時間
	int Change;		//他のアニメーションに切り替えていいかどうかを判定する。0＝変更不可 1＝変更可能
	int w;			//アニメーションする絵の幅
	int h;			//アニメーションする絵の高さ
	int ynum;		//アニメーションする絵が縦に何行ならんでいるか
	LPDIRECTDRAWSURFACE7 Bmp;		//表示するアニメーションの絵のファイル
};
struct WAZA_DATA	//技データ用構造体の型の定義
{
	int Cmd[8];			//十字キーのデータを扱う
	int Btn;			//ボタンを扱う
	int Time;			//入力時間を扱う
};
struct HIT_DATA		//当たり判定部分の構造体の型の定義
{
	int x;			//左上ｘ座標
	int y;			//左上ｙ座標
	int w;			//幅
	int h;			//高さ
};
struct ENE_ONPOS	//エネミーの出現を扱う構造体の型の定義
{
	int x;			//出現位置X(マップ全体のでの位置
	int	y;			//出現位置Y(マップ全体のでの位置
	int type;		//出現させるエネミーの種類
	BOOL OnFlag;		//一度出現したらもうそのポイントから出現させなくするためのフラグ
};
struct CHR_DATA		//キャラ構造体の型の定義
{
	int Type;		//キャラの種類
	int x;			//キャラX座標
	int y;			//キャラY座標
	int w;			//キャラの幅
	int h;			//キャラの高さ
	int muki;		//キャラの向き(0 =　右向き 1 = 左向き）
	int AniType;		//アニメーションの種類
	int AniNum;			//現在のアニメーションの何番目か
	int AniTimeNow;		//現在の絵をどのくらい表示しているか
	int AniTurn;		//アニメーションでループで戻る場所
	int OldAniType;		//前回のアニメーションの種類を扱う
	int Land;			//地面に足が着いているか判定
	double U;			//XY方向の移動速度を扱う
	int MoveChkX;		//前回のキャラX座標を扱う
	int MoveChkY;		//前回のキャラY座標を扱う
	int HitD;			//攻撃が当たっているかどうかを扱う
	BOOL HitA;			//攻撃中かどうかを扱う
	int Hp;				//キャラ体力を扱う
	BOOL Son;			//存在しているかどうかを扱う
	int Act[5];			//敵キャラなどがどういう行動をするかを扱う番号を入れた配列
	int ActNum;			//敵の現在実行中の行動の番号を保存しておく変数
	int Cnt;			//敵キャラを扱う時などに使う（カウントで待たせたりする）
	HIT_DATA Hit;		//キャラの当たり判定用
	int MaxHp;			//キャラの最大HPを扱う
	int Atk;			//キャラの攻撃力を扱う
	int Spd;			//キャラのスピードを扱う
};
struct SHOT_DATA	//弾を扱う構造体
{
	int Type;	//弾の種類を扱う
	int x;	//弾左上座標X,Y
	int y;
	int w;	//弾幅
	int h;
	int bx;	//弾の画像元X,Y
	int by;
	int mx;	//弾移動速度X,Y
	int my;
	int AniCnt;	//アニメーション表示のカウンタ
	int AniMax;	//アニメーションで表示する絵の枚数
	BOOL Son;	//弾の存在を扱う　と　誰が出した弾かを扱う
	HIT_DATA Hit;	//弾の当たり判定の範囲を扱う
	int Atk;	//ショットの威力
};
struct EF_DATA		//エフェクトを扱う構造体
{
	int x;	//左上表示位置X,Y
	int y;
	int w;	//幅、高さ
	int h;
	int bx;	//EFの画像元X,Y
	int by;
	int AniCnt;	//アニメーション表示のカウンタ
	int AniMax;	//アニメーションで表示する絵の枚数
	BOOL Son;	//エフェクトの存在を扱う
};
struct OBJ_DATA		//オブジェクトを扱う構造体（物を扱うデータ
{
	int Type;	//オブジェの種類を扱う
	int x;		//左上表示位置X,Y
	int y;
	int w;		//幅、高さ
	int h;
	int bx;		//オブジェの画像元座標X,Y
	int by;
	int AniCnt;	//アニメーション表示カウンタ
	int AniMax;	//アニメーションで表示する絵の枚数
	BOOL Son;	//オブジェの存在を扱う
};
struct BGOBJ_DATA	//背景のオブジェクトを扱う構造体（背景の物をを扱うデータ
{
	int Type;	//オブジェの種類を扱う
	int x;		//表示先XY座標
	int y;
	int w;		//幅、高さ
	int h;
	int bx;		//オブジェの画像元座標X,Y
	int by;
	int AniCnt;	//アニメーション表示カウンタ
	int AniMax;	//アニメーションで表示する絵の枚数
	BOOL Son;	//オブジェの存在を扱う
	int Line;	//背景のどの列に背景するかを扱う
	int orgX;	//元のx座標を扱う
};
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif