//外部変数宣言のヘッダ
#if !defined __GLOBALMACRO
#define __GLOBALMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <windows.h>
#include <ddraw.h>	

#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "Define.h"	//外部変数を扱うためのヘッダ
/*-----------------------------------------------------------------
	変数宣言
-----------------------------------------------------------------*/
LPSTR lpszWinClsName = "DirectDraw_Sample";					//ウィンドウクラス名
LPSTR lpszWinTitle = "DirectDraw Skeleton Program Sample";	//ウィンドウタイトル
//-------------------------------------------------------------------

HWND hWnd;									//ウィンドウのハンドル

LPDIRECTDRAW7			lpDD;				//DirectDraw7オブジェクトへのポインタ
LPDIRECTDRAWSURFACE7	lpDDSPrimary;		//DirectDrawSurface7オブジェクトへのポインタ
LPDIRECTDRAWSURFACE7	lpDDSBackBuffer;	//DirectDrawSurface7オブジェクトへのポインタ

LPDIRECTDRAWPALETTE		lpDDPal;			//オブジェクトへのポインタを受け取るための変数

PALETTEENTRY MainPal[256];					//２５６色分用意
PALETTEENTRY SubPal[256];					//変更用


//オフスクリーンサーフェース（　※ 解放は逆順
LPDIRECTDRAWSURFACE7 lpDDSOff_Text;					//プレイヤーのゲージなどの画像
LPDIRECTDRAWSURFACE7 lpDDSOff_Title;				//タイトル用の絵
LPDIRECTDRAWSURFACE7 lpDDSOff_StageSelect;			//ステージセレクト画面の絵
LPDIRECTDRAWSURFACE7 lpDDSOff_Pouse;				//ポーズ画面の絵

LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip;				//マップチップ(森）のオフスクリーンサーフェースを扱う
LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip2;				//マップチップ２(廃墟、砂漠基地
LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip3;				//マップチップ３（メカ

LPDIRECTDRAWSURFACE7 lpDDSOff_Back0;				//背景０(森ステージ用
LPDIRECTDRAWSURFACE7 lpDDSOff_Back1;				//背景１（廃墟ステージ用
LPDIRECTDRAWSURFACE7 lpDDSOff_Back1_OBJ;			//背景１オブジェ（廃墟ステージ用
LPDIRECTDRAWSURFACE7 lpDDSOff_Back2;				//背景２（砂漠基地ステージ用
LPDIRECTDRAWSURFACE7 lpDDSOff_Back3;				//背景３（嵐ステージ

LPDIRECTDRAWSURFACE7 lpDDSOff_CharWAIT;				//プレイヤー待機
LPDIRECTDRAWSURFACE7 lpDDSOff_Char;					//プレイヤー移動の
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDash;				//プレイヤーダッシュの
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDown;				//プレイヤーしゃがみの
LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackY;			//プレイヤー横斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackT;			//プレイヤー縦斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJump;				//プレイヤージャンプ
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDead;				//プレイヤーやられる
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDamage;			//プレイヤーダメージをうける絵
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackY;		//プレイヤーしゃがみ横斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackT;		//プレイヤーしゃがみ縦斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackY;		//プレイヤージャンプ横斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackT;		//プレイヤージャンプ縦斬り
LPDIRECTDRAWSURFACE7 lpDDSOff_CharUpSwd;			//プレイヤー上剣投げ
LPDIRECTDRAWSURFACE7 lpDDSOff_CharLRSwd;			//プレイヤー左右剣投げ
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpDownSwd;		//プレイヤージャンプ下剣投げ
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownSwd;			//プレイヤーしゃがみ剣投げ
LPDIRECTDRAWSURFACE7 lpDDSOff_CharBall;				//プレイヤーバリア
LPDIRECTDRAWSURFACE7 lpDDSOff_CharReturnSwd;		//プレイヤー剣吸収
LPDIRECTDRAWSURFACE7 lpDDSOff_CharSwdHPUP;			//プレイヤーと剣のHP入れ替え画像

LPDIRECTDRAWSURFACE7 lpDDSOff_Swd;				//剣

LPDIRECTDRAWSURFACE7 lpDDSOff_En1;				//エネミー１（犬
LPDIRECTDRAWSURFACE7 lpDDSOff_En2;				//エネミー２（とかげ
LPDIRECTDRAWSURFACE7 lpDDSOff_En3;				//エネミー３（未来兵
LPDIRECTDRAWSURFACE7 lpDDSOff_En4;				//エネミー４（兵
LPDIRECTDRAWSURFACE7 lpDDSOff_En5;				//エネミー５（炎人
LPDIRECTDRAWSURFACE7 lpDDSOff_En6;				//エネミー６（根っこ
LPDIRECTDRAWSURFACE7 lpDDSOff_En7;				//エネミー７（鉄犬
LPDIRECTDRAWSURFACE7 lpDDSOff_En8;				//エネミー８（小動物
LPDIRECTDRAWSURFACE7 lpDDSOff_En9;				//エネミー９（蜂
LPDIRECTDRAWSURFACE7 lpDDSOff_EnTubo;			//ツボ
LPDIRECTDRAWSURFACE7 lpDDSOff_En10;				//エネミー１０（骨口


LPDIRECTDRAWSURFACE7 lpDDSOff_Boss1;			//ボス１

LPDIRECTDRAWSURFACE7 lpDDSOff_Shot;				//弾

LPDIRECTDRAWSURFACE7 lpDDSOff_EF;				//エフェクト

LPDIRECTDRAWSURFACE7 lpDDSOff_OBJ;				//オブジェクト


DWORD FPS_Disp;			//１秒間で、ゲーム処理を何回実行できたか
JOYINFOEX JoyData;		//JOYINFOEX型構造体（現在のジョイスティックのデータ）
JOYINFOEX JoyData2;		//（前回のジョイスティックのデータ）

int GameNum = 0;	//どの処理を実行するかを扱う変数GameNumを0（最初はタイトル画面）で初期化
int StageNum = 0;	//ステージを選ぶのに扱う値	

double SinT[720];		//サインテーブル

int CmdNum[8]={0,0,0,0,0,0,0,0};	//４つまでのコマンド入力のキーデータを扱う
int CmdCnt[8]={0,0,0,0,0,0,0,0};	//ボタンを押した時間を扱う
int WMoveChkX,WMoveChkY;	//前回のマップチップスクロールXYを使い、どれだけ移動したかを扱う(スクロールすると敵とマップを一緒ずらす）

int Nage = 0;	//剣をなげたかどうかを扱う
int Muteki = 0;	//プレイヤーの無敵時間を扱う


//▼プレイヤー▼
struct CHR_DATA Plr = {-1,320,240,64,96,0,0,0,0,0,0,FALSE,0.,230,200,0,FALSE,50,TRUE};	//プレイヤーの構造体
struct CHR_DATA Dum[3];	//プレイヤー残像用キャラデータ

//▼　剣　▼
struct CHR_DATA Swd = {-2,230,200,92,92,0,0,0,0,0,0,FALSE,0.,230,200,0,FALSE,30,TRUE};	//剣の構造体

//▼エネミー▼
struct CHR_DATA EnemyNum[] =	//エネミーのデータ
{//																								  Atk					
	{0,0,0,0,0,0,0,0,0,0,0,FALSE,0.,0,0,0,FALSE,0,FALSE,				{0,0,0,0,0},},				//空
	{1,400,100,96,64,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,10,FALSE,		{0,1,2,3,0},0,0,0,0,0,0,10,3},		//エネミーの構造体
	{2,500,100,128,80,1,0,0,0,0,0,FALSE,0.,500,100,0,FALSE,20,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,20,3},		//エネミー２の構造体
	{3,550,250,112,80,1,0,0,0,0,0,FALSE,0.,500,100,0,FALSE,300,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,300,3},		//エネミー３（ボス１の構造体
	{4,400,100,64,84,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,30,FALSE,		{0,3,2,1,0},0,0,0,0,0,0,30,3},			//エネミー３の構造体
	{5,100,200,72,84,1,0,0,0,0,0,FALSE,0.,100,200,0,FALSE,18,FALSE,		{0,1,3,0,2},0,0,0,0,0,0,18,3},			
	{6,100,150,64,116,1,0,0,0,0,0,FALSE,0.,100,150,0,FALSE,50,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,50,5},
	{7,240,100,32,32,1,0,0,0,0,0,FALSE,0.,240,100,0,FALSE,1,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,1,3},
	{8,400,100,128,80,2,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,120,FALSE,	{0,6,2,3,0},0,0,0,0,0,0,120,5},		//エネミーの構造体
	{9,400,100,32,32,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,5,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,5,1},		//（小動物
	{10,90,100,56,64,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,30,FALSE,		{0,1,0,0,0},0,0,0,0,0,0,30,3},		//エネミー（蜂	
	{11,280,100,64,96,1,0,0,0,0,0,FALSE,0.,280,100,0,FALSE,5,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,5,0},		//ツボ
	{12,280,100,96,64,1,0,0,0,0,0,FALSE,0.,280,100,0,FALSE,60,FALSE,	{0,0,1,2,0},0,0,0,0,0,0,60,10}		//骨口
};
struct CHR_DATA En[ENE_MAX];		//エネミーの構造体

//▼　弾　▼
struct SHOT_DATA ShotData[] =	//ショットのデータ
{ //Type x	 y	 w	 h	 bx  by	 mx  my  Cnt Max Son&EneOrPlr Hit(x,y,w,h) Atk
	{0	,0	,0	,8	,8	,0	,0	,5	,0	,0	,5	,FALSE	,{0,0,6,6}		,2},	//8*8のサイズの弾
	{1	,0	,0	,8	,8	,96	,0	,7	,0	,0	,1	,FALSE	,{0,0,6,6}		,2},	//8*8のサイズの弾
	{2	,0	,0	,16	,16	,0	,8	,4	,0	,0	,5	,FALSE	,{0,0,12,12}	,5},	//16*16のサイズの弾
	{3	,0	,0	,48	,32	,0	,24	,3	,0	,0	,4	,FALSE	,{0,0,40,28}	,6},	//48*32のサイズの火の玉
	{4	,0	,0	,16	,48	,0	,56	,0	,0	,0	,3	,FALSE	,{0,0,14,46}	,4},	//16*48のサイズの火
	{5	,0	,0	,32	,4	,0	,104,16	,0	,0	,2	,FALSE	,{0,0,32,4}		,8},	//32*4のレーザー
	{6	,0	,0	,48	,48	,0	,108,5	,0	,0	,5	,FALSE	,{0,0,40,40}	,2},	//48*48の炎（遠距離火炎放射
	{7	,0	,0	,32	,32	,0	,156,0	,0	,0	,3	,FALSE	,{0,0,24,24}	,2},	//32*32の炎
	{8	,0	,0	,4	,4	,128,0	,0	,0	,0	,6	,FALSE	,{0,0,4,4}		,-2},	//4*4の光
	{9	,0	,0	,8	,8	,180,0	,0	,0	,0	,3	,FALSE	,{0,0,6,6}		,3},		//葉っぱ竜巻
	{10	,0	,0	,8	,8	,180,0	,0	,0	,0	,3	,FALSE	,{0,0,6,6}		,2},		//葉っぱ吹雪
	{11	,0	,0	,8	,8	,192,8	,0	,0	,0	,0	,FALSE	,{0,0,4,4}		,3},		//瓦礫小１
	{12	,0	,0	,8	,8	,208,8	,0	,0	,0	,0	,FALSE	,{0,0,4,4}		,4},		//瓦礫小２
	{14	,0	,0	,16	,16	,224,8	,0	,0	,0	,0	,FALSE	,{0,0,12,12}	,5},		//瓦礫中１
	{15	,0	,0	,16	,16	,256,8	,0	,0	,0	,0	,FALSE	,{0,0,12,12}	,6},		//瓦礫中２
	{16	,0	,0	,24	,24	,288,0	,0	,0	,0	,0	,FALSE	,{0,0,20,16}	,7},		//瓦礫大
	{17	,0	,0	,16	,64	,480,0	,13	,0	,0	,4	,FALSE	,{0,0,16,56}	,3},		//真空
	{18	,0	,0	,8	,8	,0	,192,0	,0	,0	,7	,FALSE	,{0,0,6,6}		,1},		//ポイズン
	{19	,0	,0	,48	,48	,0	,108,15	,0	,0	,5	,FALSE	,{0,0,32,32}	,4},	//48*48の炎(火炎放射
	{20	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,FALSE	,{0,0,2,2}		,5},	//剣の破片
	{21	,0	,0	,32	,32	,192,64	,12	,0	,0	,2	,FALSE	,{0,0,32,30}	,5},	//鉄の真空
	{22	,0	,0	,12	,12	,384,72	,0	,-15,0	,7	,FALSE	,{0,0,10,10}	,5},		//毒弾
	{23	,0	,0	,24	,24	,0	,200,5	,5	,0	,3	,FALSE	,{0,0,12,12}	,10},	//緑斜め弾
	{24	,0	,0	,24	,24	,384,84	,0	,-20,0	,3	,FALSE	,{0,0,16,16}	,6},		//骨弾
	{25	,0	,0	,1	,1	,128,4	,0	,-1	,0	,15	,FALSE	,{0,0,1,1}		,0},		//灰（１＊１）
	{26	,0	,0	,2	,2	,128,6	,0	,-1	,0	,7	,FALSE	,{0,0,2,2}		,0},			//灰２（２＊２）
	{27	,0	,0	,48	,32	,0	,24	,8	,0	,0	,4	,FALSE	,{0,0,40,28}	,10},	//48*32の拡散する炎
	{28	,0	,0	,16	,16	,256,160,1	,0	,0	,5	,FALSE	,{0,0,14,14}	,10},		//火ボール
	{29	,0	,0	,1	,1	,128,4	,0	,0	,0	,15	,FALSE	,{0,0,80,80}		,0}		//灰爆発（エフェクトを使用

};
struct SHOT_DATA Shot[SHOT_MAX];		//弾を扱う構造体

//▼エフェクト▼
struct EF_DATA EFData[]=	//エフェクトのデータ
{  //x	 y	 w	 h	 bx	 by	 Cnt Max Son
	{0	,0	,96	,96	,0	,0	,0	,6	,FALSE},	//爆発エフェクト
	{0	,0	,20	,96	,0	,96	,0	,7	,FALSE},	//縦斬りエフェクト
	{0	,0	,96	,20	,0	,192,0	,5	,FALSE},	//横斬りエフェクト
	{0	,0	,48	,48	,160,96	,0	,5	,FALSE},	//弾ヒットエフェクト
	{0	,0	,8	,8	,576,0	,0	,6	,FALSE},	//８＊８のサイズのエフェクト
	{0	,0	,8	,8	,576,8	,0	,7	,FALSE},	//８＊８のサイズのエフェクト（紫
	{0	,0	,8	,8	,576,16	,0	,7	,FALSE},	//８＊８のサイズのエフェクト
	{0	,0	,24	,24	,448,96	,0	,4	,FALSE},	//24*24のほこり
	{0	,0	,24	,24	,448,120,0	,4	,FALSE},	//24*24のほこり２
	{0	,0	,8	,20	,160,144,0	,9	,FALSE},	//８＊２０の魂の消えるエフェクト
	{0	,0	,16	,16	,240,144,0	,4	,FALSE},	//紫の吸い込む光のエフェクト
	{0	,0	,16	,24	,160,168,0	,5	,FALSE},	//緑の癒しの光のエフェクト
	{0	,0	,32	,32	,256,160,0	,8	,FALSE}		//煙のエフェクト
};
struct EF_DATA EF[EF_MAX];		//エフェクトを扱う構造体

//▼オブジェクト▼
struct OBJ_DATA OBJData[]=	//オブジェクトのデータ
{ //Type x	 y	 w	 h	 bx	 by	 Cnt Max Son
	{0	,0	,0	,152,72	,0	,0	,0	,0	,FALSE},	//ボス１の体
	{1	,0	,0	,92	,64	,152,0	,0	,0	,FALSE},	//ボス１の手
	{2	,0	,0	,52	,52	,244,0	,0	,0	,FALSE},	//ボス１の首(100％
	{3	,0	,0	,48	,44	,296,0	,0	,0	,FALSE},	//ボス１の首（90％
	{4	,0	,0	,40	,40	,344,0	,0	,0	,FALSE}		//ボス１の首（80%
};
struct OBJ_DATA Obj[OBJ_MAX];	//オブジェクトを扱う構造体

//▼バックグランドオブジェクト▼
struct BGOBJ_DATA BGOBJData[] =		//BGオブジェクトのデータ1
{ //Type x	 y	 w	 h	 bx	 by	 Cnt Max Son Line
	{0	,0	,0	,64	,64	,0	,0	,0	,0	,0	,},	//瓦礫
	{1	,0	,0	,64	,64	,64	,0	,0	,0	,0	,},	//瓦礫２
	{2	,0	,0	,64	,64	,128,0	,0	,0	,0	,},	//瓦礫３
	{3	,0	,0	,64	,64	,192,0	,0	,0	,0	,},	//瓦礫４
	{4	,0	,0	,64	,64	,256,0	,0	,0	,0	,},	//瓦礫５
	{5	,0	,0	,64	,64	,320,0	,0	,0	,0	,},	//柱（小）
	{6	,0	,0	,96	,64	,384,0	,0	,0	,0	,3},	//瓦礫（中）
	{7	,0	,0	,128,64	,480,0	,0	,0	,0	,3},	//瓦礫（大）
	{8	,0	,0	,96	,96	,0	,64	,0	,0	,0	,4},	//瓦礫（大）２
	{9	,0	,0	,64	,96	,96	,64	,0	,0	,0	,},	//柱（中）
	{10	,0	,0	,32	,96	,160,64	,0	,0	,0	,},	//柱（小）２
	{11	,0	,0	,96	,64	,192,64	,0	,0	,0	,4},	//車
	{12	,0	,0	,96	,96	,288,64	,0	,0	,0	,4},	//壁
	{13	,0	,0	,128,96	,416,64	,0	,0	,0	,4},	//家
	//{14	,0	,0	,128,96	,512,64	,0	,0	,0	,3},	//バイク家
	{14	,0	,0	,160,96	,0	,160,0	,0	,0	,5},	//瓦礫（大）３
	{15	,0	,0	,128,96	,160,160,0	,0	,0	,},	//壁２
	{16	,0	,0	,128,128,288,160,0	,0	,0	,(rand()%3)+2},	//家２
	{17	,0	,0	,192,64	,416,160,0	,0	,0	,4},	//電柱
	{18	,0	,0	,64	,128,416,224,0	,0	,0	,5},	//柱（中）２
	{19	,0	,0	,128,32	,480,224,0	,0	,0	,},	//穴
	//{21	,0	,0	,288,224,0	,256,0	,0	,0	,6},		//家（特大）
	{20	,0	,0	,32	,32	,480,256,0	,2	,0	,},		//布
	{21	,0	,0	,96	,96	,288,352,0	,2	,0	,},		//炎
	{22	,0	,0	,32	,32	,480,288,0	,4	,0	,},		//火
	{23	,0	,0	,288,224,0	,256,0	,0	,0	,6},	//家（特大）
	{24	,0	,0	,128,96	,512,64	,0	,0	,0	,3}		//バイク家


};
struct BGOBJ_DATA BgObj[BGOBJ_MAX];	//背景オブジェを扱う構造体

//▼プレイヤーアニメーション▼
struct ANIME_DATA Anime[][21] =	//アニメーションのデータ
{
	//待機アニメーション
				                             //↓「-1」で指定場所のアニメーションに戻りループ、「-2」でそのアニメーションを終了し、基本のアニメーションに戻る。
	{{0,10,1,64,96,1},{1,13,1},{2,20,1},{1,7,1},{-1,2,1}},
		  //↑と↑に絵をサイズを入れる
	//移動アニメーション
	{{0,4,1,64,96,2},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{5,4,1},{6,4,1},{7,4,1},{8,4,1},{9,4,1},{10,4,1},{11,4,1},{12,4,1},{13,4,1},{14,4,1},{-1,0,1}},	//アニメーション０
	//ダッシュアニメーション
	{{0,2,1,64,96,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{9,2,1},{10,2,1},{11,2,1},{12,2,1},{-1,0,1}},						//アニメーション１
	//しゃがみアニメーション
	{{0,1,1,64,96,2},{1,1,1},{2,1,1},{3,1,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{9,2,1},{-1,0,1}},													//アニメーション２
	//横斬り
	{{0,3,0,128,96,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,1}},
	//縦斬り
	{{0,5,0,160,112,2},{1,4,0},{2,4,0},{3,1,0},{4,1,0},{5,1,0},{6,2,0},{7,2,0},{-2,0,1}},
	//ジャンプUP
	{{0,2,1,64,96,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{-1,0,1}},
	//ジャンプDOWN
	{{10,2,1,64,96,2},{11,2,1},{12,2,1},{13,2,1},{14,2,1},{-1,0,1}},
	//やられる
	{{0,5,0,64,96,2},{1,5,0},{2,5,0},{3,5,0},{4,5,0},{5,5,0},{6,5,0},{7,5,0},{8,5,0},{9,5,0},{10,5,0},{11,5,0},{12,5,0},{13,5,0},{14,5,0},{15,5,0},{16,5,0},{17,2,0},{18,2,0},{19,2,0},{-1,0,1}},
	//ダメージをうける
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,3,0},{2,2,0},{3,2,0},{3,1,0},{-2,0,0}},
	//しゃがみ縦斬り
	{{0,2,0,128,96,2},{1,3,0},{2,3,0},{3,3,0},{4,1,0},{5,2,0},{6,2,0},{7,2,0},{8,2,0},{9,4,0},{-2,0,0}},
	//しゃがみ横斬り
	{{0,3,0,112,96,2},{1,2,0},{2,2,0},{3,2,0},{4,1,0},{5,2,0},{6,3,0},{-2,0,0}},
	//ジャンプ縦斬り
	{{0,2,0,160,96,2},{1,2,0},{2,3,0},{3,1,0},{4,2,0},{6,4,0},{-2,0,0}},
	//ジャンプ横斬り
	{{0,2,0,112,88,2},{1,1,0},{2,2,0},{3,1,0},{4,1,0},{5,2,0},{-2,0,0}},
	//上剣投げ
	{{0,4,0,64,96,1},{1,3,0},{2,2,0},{3,2,0},{4,2,0},{-2,0,0}},
	//左右剣投げ
	{{0,2,0,72,96,1},{1,1,0},{2,1,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,0}},
	//ジャンプ下剣投げ
	{{0,1,0,80,96,1},{1,1,0},{2,1,0},{3,1,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,0}},
	//しゃがみ剣投げ
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{-2,0,0}},
	//バリア
	{{0,2,0,96,96,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{8,2,0},{9,2,0},{10,2,0},{11,2,0},{-1,0,0}},
	//剣吸収
	{{0,2,0,64,96,1},{1,1,0},{2,1,0},{3,1,0},{-1,0,0}},
	//プレイヤーと剣のHP入れ替え
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,2,0},{-1,0,0}}
};

//▼剣アニメーション▼
struct ANIME_DATA AniSwd[][9] =	//剣のアニメーションデータ
{	//剣上向き
	{{0,1,1,92,92,3},{1,1,1},{2,10,1},{-1,0,1}},
	//剣下向き
	{{3,1,1,92,92,3},{4,1,1},{5,10,1},{-1,0,1}},
	//剣左向き
	{{6,1,1,92,92,3},{7,1,1},{8,10,1},{-1,0,1}},
	//剣右向き
	{{9,1,1,92,92,3},{10,1,1},{11,10,1},{-1,0,1}},
	//剣出現
	{{12,2,0,92,92,3},{13,2,0},{14,2,0},{15,2,0},{16,2,0},{17,2,0},{18,2,0},{19,2,0},{-2,0,0}},
	//剣消える
	{{15,1,0,92,92,3},{14,1,0},{13,1,0},{12,1,0},{-2,0,0}}
};

//▼エネミーアニメーション▼
struct ANIME_DATA AniEn[][ENEACT_MAX][11] =	//敵のアニメーションデータ
{
	{//空
		{{0,0,0,0,0,0},{-1,0,1}},
	},
	{//エネミー１(犬
		{{0,15,1,96,64,1},{1,2,1},{2,4,1},{-1,0,1}},				//待機
		{{0,4,1,96,64,1},{1,5,1},{2,15,1},{3,1,1},{4,1,1},{-1,0,1}},//アタック
		{{0,4,0,96,64,1},{1,4,1},{2,2,1},{3,1,1},{4,1,1},{-1,0,1}},	//ジャンプ
		{{5,10,0,96,64,1},{-2,0,1}}									//ダメージ
	},
	{//エネミー２（トカゲ
		{{0,5,1,128,80,2},{5,4,1},{-1,0,1}},									//待機
		{{0,2,1,128,80,2},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{-1,0,1}},			//移動
		{{0,2,0,128,80,2},{5,2,0},{6,3,0},{7,26,0},{6,2,0},{5,1,0},{-2,0,1}},	//かみつき
		{{0,2,0,128,80,2},{5,3,0},{6,4,0},{7,10,0},{-1,0,1}},					//
		{{8,5,0,128,80,2},{9,20,0},{-2,0,1}}									//ダメージ
	},
	{//ボス１（竜
		{{7,2,0,112,80,2},{6,2,0},{0,1,1},{6,3,0},{7,2,0},{-1,0,1}},											//通常
		{{0,5,0,112,80,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,20,0},{6,16,0},{7,16,0},{-2,0,1}},	//噛み付き
		{{7,5,0,112,80,2},{0,2,0},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,7,0},{-2,0,1}},			//火の玉
		{{8,10,0,112,80,2},{-2,0,1}}									//ダメージ
	},
	{//エネミー３（メカ兵
		{{0,1,1,64,84,1},{0,1,1},{-2,0,1}},									//待機
		{{0,4,1,64,84,1},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{3,4,1},{2,4,1},{1,4,1},{-2,0,0}},		//歩行
		{{5,15,0,64,84,1},{6,1,0},{5,6,0},{-2,0,0}},							//銃撃
		{{7,5,0,64,84,1},{-2,0,1}}										//ダメージ
	},
	{//エネミー４（兵
		{{4,15,1,72,84,2},{4,1,1},{-2,0,1}},						//待機
		{{0,5,1,72,84,2},{1,5,1},{2,5,1},{3,5,1},{4,5,1},{-2,0,1}},	//移動
		{{6,30,0,72,84,2},{5,1,0},{7,2,0},{-2,0,1}},				//銃撃
		{{8,3,0,72,84,2},{9,5,0},{-2,0,1}}							//ダメージ
	},
	{//エネミー５（炎
		{{0,2,1,64,116,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{-2,0,1}},	//待機
		{{5,3,1,64,116,2},{6,3,1},{7,3,1},{8,3,1},{9,3,1},{10,3,1},{11,3,1},{12,3,1},{13,3,1},{14,3,1},{-2,0,1}},	//移動
		{{14,1,1,64,116,2},{15,1,1},{16,1,1},{-1,0,1}},	//チャージ
		{{17,10,0,64,116,2},{-2,0,1}}		//ダメージ
	},
	{//エネミー６（枝
		{{0,30,1,32,32,1},{1,3,1},{0,50,1},{-2,0,1}},	//待機
		{{2,2,0,32,32,1},{3,2,0},{4,2,0},{5,2,0},{-2,0,1}},	//攻撃
		{{6,5,0,32,32,1},{-2,0,1}}	//ダメージ
	},
	{//エネミー７（鉄犬
		{{0,8,1,128,80,2},{1,5,1},{0,10,1},{1,7,1},{-1,0,1}},	//待機
		{{1,10,1,128,80,2},{2,5,1},{3,3,1},{4,1,1},{5,1,1},{6,1,1},{7,1,1},{4,1,1},{-1,0,1}},	//アタック
		{{0,3,0,128,80,2},{1,5,0},{3,3,0},{4,1,1},{5,1,1},{6,1,1},{7,1,1},{-1,0,1}},	//ジャンプ
		{{8,6,0,128,80,2},{-2,0,1}},													//ダメージ
		{{2,15,1,128,80,2},{1,25,0},{-1,0,1}}	//発砲
	},
	{//エネミー８（小動物
		{{0,3,1,32,32,1},{1,3,1},{2,3,1},{3,3,1},{4,3,1},{-1,0,1}},	//移動
		{{5,5,0,32,32,1},{6,7,0},{7,8,0},{8,10,0},{9,15,0},{-2,0,1}}	//ダメージ
	},
	{//エネミー９（蜂
		{{0,3,1,56,64,1},{1,3,1},{2,3,1},{3,3,1},{4,3,1},{-1,0,1}},	//移動
		{{5,20,0,56,64,1},{6,5,0},{-2,0,1}},						//攻撃
		{{7,30,0,56,64,1},{-2,0,1}}									//ダメージ
	},
	{//ツボ
		{{0,2,1,64,96,1},{-1,0,1}},	//待機1
		{{1,2,1,64,96,1},{-1,0,1}},
		{{2,2,1,64,96,1},{-1,0,1}},
		{{3,2,1,64,96,1},{-1,0,1}},
		{{4,2,1,64,96,1},{-1,0,1}}
	},
	{//骨口
		{{0,40,1,96,64,1},{-1,0,1}},										//待機
		{{0,5,0,96,64,1},{1,4,0},{2,5,0},{-2,0,1}},						//噛み付き
		{{0,3,0,96,64,1},{1,2,0},{2,6,0},{1,1,0},{0,10,0},{-2,0,1}},	//吐く
		{{3,30,0,96,64,1},{-2,0,1}}												//ダメージ
	}
};


//コマンドデータ
struct WAZA_DATA WazaCmd[CMD_MAX] =	//キーの3回分の入力まで扱う
{
	{{8,12,4,-1},(1<<1),20},	//下、右下、右　＋　ボタン１
	{{1,0,1,-1},0,20},
	{{2,0,2,-1},0,100},
	{{1,0,4,-1},1,20},			//Plrと剣のHP入れ替え
	{{4,0,1,-1},1,20},			//Plrと剣のHP入れ替え
	{{1,8,9,-1},1,20},			//剣吸収左
	{{4,8,12,-1},1,20},			//剣吸収右
	{{1,8,9,-1},(1<<1),20},		//バリア左
	{{4,8,12,-1},(1<<1),20}		//バリア右
};
int CmdGet = 0;	//成立したコマンドの番号を扱う


//エネミー出現位置
struct ENE_ONPOS EneOnPos_Max = {0,0,0,FALSE};	//適出現位置の数を扱う（後で　ファイルロードで値を受け取る
//メモリ確保
struct ENE_ONPOS *pEneOn;			//適出現位置のデータ //使用してないポインタ変数にはNULLを入れておく

/*struct ENE_ONPOS EneOn[ENEONPOS_MAX] =	//エネミーの出現するポイントを１００個まで設定
{
	{650,400,1,FALSE},				//エネミー１を650,400のポイントに出現させる
};*/


//マップ
//メモリ確保
int *pMap = NULL;			//マップのデータ //使用してないポインタ変数にはNULLを入れておく

int MapXnum = 100;			//マップチップのヨコの数(後でマップデータからデータを取る
int MapYnum = 100;			//マップチップのタテの数
//int Map[MAP_YNUM][MAP_XNUM];			//マップのデータ


//マップチップの種類を扱う(0＝配置しないチップ、１＝通れないチップ、２＝透き通るチップ、３＝アニメーションするチップ 
int Tip[TIP_MAX] =	//ゲームで使用するチップ通過フラグ
//最初は森のステージなので森のステージのチップ通過フラグをTipに初期化
//	0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0	//森のステージ
{	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
	1,1,1,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,
	1,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,2,2,2,2,	//5
	1,1,1,1,1,1,2,2,2,1,2,2,2,1,2,1,2,2,2,2,
	1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,1,1,1,
	1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2,2,1,1,1,
	1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,1,1,1,1,
	1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,	//10
	1,1,1,1,1,1,1,1,1,1,3,2,3,2,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,3,2,3,2,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	};//15
	
     
int x=0;
int y=0;
int WorldX=0,WorldY=0;		//X方向、Y方向にスクロールした量
int WMoveX = 0,WMoveY = 0;
double BGScrX=0;			//背景のスクロールを扱う


int xbox,ybox,wbox,hbox;

int Key = 0;	//十字キーのデータを保存する
int AllCnt = 0;	//コマンド入力の時間を扱う
int Btn1 = 0;	//押しているボタンを扱う（キーボード専用）
int Btn2 = 0;	//１つ前の押しているか押していないかを扱う
int BtnCnt = 0;	//ボタンの押している時間を扱うデータを保存する



int FPS_ChangeNum = 80;	//WinMainで使用
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif

