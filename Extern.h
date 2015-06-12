//外部変数を、DirectDrawスケルトンのあるソースファイル以外で使用するためのヘッダファイル
#if !defined __EXTERNMACRO
#define __EXTERNMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "Define.h"		//外部変数を扱うためのヘッダ
/*-----------------------------------------------------------------
	変数宣言
-----------------------------------------------------------------*/
extern HWND hWnd;									//ウィンドウのハンドル

extern LPDIRECTDRAW7		lpDD;				//DirectDraw7オブジェクトへのポインタ
extern LPDIRECTDRAWSURFACE7	lpDDSPrimary;			//DirectDrawSurface7オブジェクトへのポインタ
extern LPDIRECTDRAWSURFACE7	lpDDSBackBuffer;		//DirectDrawSurface7オブジェクトへのポインタ

extern LPDIRECTDRAWPALETTE lpDDPal;	//オブジェクトへのポインタを受け取るための変数

extern PALETTEENTRY MainPal[256];	//２５６色分用意
extern PALETTEENTRY SubPal[256];	//変更用

//extern LPDIRECTDRAWSURFACE7	lpDDSOff;
//extern LPDIRECTDRAWSURFACE7	lpDDSOff2;

extern LPDIRECTDRAWSURFACE7 lpDDSOff_Text;					//プレイヤーのゲージなどの画像
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Title;					//タイトル用の絵
extern LPDIRECTDRAWSURFACE7 lpDDSOff_StageSelect;			//ステージセレクト画面の絵
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Pouse;				//ポーズ画面の絵


extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip;				//マップチップのオフスクリーンサーフェースを扱う
extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip2;				//マップチップ２(廃墟
extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip3;				//マップチップ３（メカ


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back0;				//背景０(森ステージ用
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back1;				//背景１（廃墟ステージ用
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back1_OBJ;			//背景１オブジェ（廃墟ステージ用
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back2;				//背景２（砂漠基地ステージ用
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back3;				//背景３（嵐ステージ

extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharWAIT;				//プレイヤー待機
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Char;					//プレイヤー移動の
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDash;				//プレイヤーダッシュの
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDown;				//プレイヤーしゃがみの
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackY;			//プレイヤー横斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackT;			//プレイヤー縦斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJump;				//プレイヤージャンプ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDead;				//プレイヤーやられる
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDamage;			//プレイヤーダメージをうける絵
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackY;		//プレイヤーしゃがみ横斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackT;		//プレイヤーしゃがみ縦斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackY;		//プレイヤージャンプ横斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackT;		//プレイヤージャンプ縦斬り
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharUpSwd;			//プレイヤー上剣投げ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharLRSwd;			//プレイヤー左右剣投げ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpDownSwd;		//プレイヤージャンプ下剣投げ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownSwd;			//プレイヤーしゃがみ剣投げ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharBall;				//プレイヤーボール
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharReturnSwd;		//プレイヤー剣吸収
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharSwdHPUP;			//プレイヤーと剣のHP入れ替え画像


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Swd;				//剣

extern LPDIRECTDRAWSURFACE7 lpDDSOff_En1;				//エネミー１
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En2;				//エネミー２
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En3;				//エネミー３
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En4;				//エネミー４
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En5;				//エネミー５
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En6;				//エネミー６（根っこ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En7;				//エネミー７（鉄犬
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En8;				//エネミー８（小動物
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En9;				//エネミー９（蜂
extern LPDIRECTDRAWSURFACE7 lpDDSOff_EnTubo;			//ツボ
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En10;				//エネミー１０（骨口


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Boss1;			//ボス１

extern LPDIRECTDRAWSURFACE7 lpDDSOff_Shot;				//弾

extern LPDIRECTDRAWSURFACE7 lpDDSOff_EF;				//エフェクト

extern LPDIRECTDRAWSURFACE7 lpDDSOff_OBJ;				//オブジェクト

extern DWORD FPS_Disp;			//１秒間で、ゲーム処理を何回実行できたか
extern JOYINFOEX JoyData;		//JOYINFOEX型構造体（現在のジョイスティックのデータ）
extern JOYINFOEX JoyData2;		//（前回のジョイスティックのデータ）

extern int GameNum;		//どの処理を実行するかを扱う変数GameNumを0（最初はタイトル画面）で初期化
extern int StageNum;	//ステージを選ぶのに扱う値	

extern double SinT[720];	//サインテーブル

extern int CmdNum[8];	//４つまでのコマンド入力のキーデータを扱う
extern int CmdCnt[8];	//ボタンを押した時間を扱う
extern int WMoveChkX,WMoveChkY;	//前回のマップチップスクロールXYを使い、どれだけ移動したかを扱う
extern int Nage;	//剣をなげたかどうかを扱う
extern int Muteki;	//プレイヤーの無敵時間を扱う


extern struct CHR_DATA Plr;				//プレイヤーの構造体
extern struct CHR_DATA Dum[3];	//プレイヤー残像用キャラデータ
extern struct CHR_DATA Swd;				//剣の構造体
extern struct CHR_DATA EnemyNum[];			//エネミーデータ
extern struct CHR_DATA En[ENE_MAX];			//エネミーの構造体
extern struct SHOT_DATA ShotData[];			//ショットのデータ
extern struct SHOT_DATA Shot[SHOT_MAX];		//弾を扱う構造体
extern struct EF_DATA EFData[];			//エフェクトのデータ
extern struct EF_DATA EF[EF_MAX];		//エフェクトを扱う構造体
extern struct OBJ_DATA OBJData[];		//オブジェクトのデータ
extern struct OBJ_DATA Obj[OBJ_MAX];	//オブジェクトを扱う構造体
extern struct BGOBJ_DATA BGOBJData[]; 		//BGオブジェクトのデータ
extern struct BGOBJ_DATA BgObj[BGOBJ_MAX];	//背景オブジェを扱う構造体

extern struct ANIME_DATA Anime[][21];	//アニメーションデータ
extern struct ANIME_DATA AniSwd[][9];	//剣のアニメーションデータ
extern struct ANIME_DATA AniEn[][ENEACT_MAX][11];	//敵のアニメーションデータ

extern struct WAZA_DATA WazaCmd[CMD_MAX];	//コマンドデータを扱う
extern int CmdGet;	//成立したコマンドの番号を扱う


//エネミー出現位置
extern struct ENE_ONPOS EneOnPos_Max;	//適出現位置の数を扱う（後で　ファイルロードで値を受け取る
//メモリ確保
extern struct ENE_ONPOS *pEneOn;			//適出現位置のデータ //使用してないポインタ変数にはNULLを入れておく

//extern struct ENE_ONPOS EneOn[ENEONPOS_MAX];	//エネミーの出現するポイントを１００個まで設定


//マップ
extern int *pMap;	//使用してないポインタ変数にはNULLを入れておく

extern int MapXnum;			//マップチップのヨコの数
extern int MapYnum;			//マップチップのタテの数
//extern int Map[MAP_YNUM][MAP_XNUM];			//マップのデータ
extern int Tip[100];						//マップチップの種類を扱う
extern int x;
extern int y;
extern int WorldX,WorldY;		//X方向、Y方向にスクロールした量
extern int WMoveX,WMoveY;
extern double BGScrX;			//背景のスクロールを扱う


extern int xbox,ybox,wbox,hbox;

extern int Key;		//十字キーのデータを保存する
extern int AllCnt;	//コマンド入力の時間を扱う
extern int Btn1;	//押しているボタンを扱う（キーボード専用）
extern int Btn2;	//１つ前の押しいるかいないかを扱う
extern int BtnCnt;	//ボタンの押している時間を扱うデータを保存する



extern int FPS_ChangeNum;	//ゲームの処理速度を自由に調節するための変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif
