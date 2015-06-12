//ゲームのデータ準備、解放をする関数をまとめたファイル
/////　インクルード ///////
#include <windows.h>	//Windows用ヘッダファイル
#include <ddraw.h>
#include <time.h>		//時間を扱う関数などのヘッダ
#include <math.h>		//算術関数などのヘッダ

#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "Extern.h"		//外部変数を扱うためのヘッダ
#include "SaveLoadProc.h"	//セーブ、ロードの関数のプロトタイプ宣言のヘッダ

#include "GameCheckProc.h"	//判定関数などのプロトタイプ宣言のヘッダ
/*-----------------------------------------------------------------------------------------------------
　　ゲームの準備をまとめた定義関数。メッセージループの直前に実行する。
　　引数　：　WHND・・・ウィンドウハンドル
　　　　　　　HINSTANCE・・・インスタンスハンドル
-----------------------------------------------------------------------------------------------------*/
void GameCreate(HWND hwnd)
{

	HDC hdc;
	int i;					//カウンタ変数
	time_t ti;				//tiで時間を扱う
	srand(time(&ti));		//time()の戻値を使って乱数を初期化

	hdc = GetDC(hwnd);		//HDC取得

	//------ジョイスティック--------
	//現在のジョイスティックのデータを扱うJoyDataの設定
	JoyData.dwSize = sizeof(JOYINFOEX);		//構造体自体(自分自身)の大きさを代入しておく
	JoyData.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;	//どんなデータを取得するか(ボタンデータ、十字キー左右データ、十字キー上下データ）
	//前回のジョイスティックのデータを扱うJoyData2の設定
	JoyData2.dwSize = sizeof(JOYINFOEX);	//構造体自体の大きさを代入しておく
	JoyData2.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;	//どんなデータを取得するか

	ReleaseDC(hwnd,hdc);	//HDC解放

	//サインテーブル
	for(i = 0;i < 720;i++)	//sin0°～sin359°の
	{
		SinT[i] = sin(i * 3.14159/180.);	//サインの値を求めて保存しておく
	}
	for(i = 0;i < SHOT_MAX;i++)
	{
		Shot[i] = ShotData[0];	//ショットデータの０番のデータを代入
	}

	///// 初期設定 ///////////////////////////////////////////////////////////////////////////////////////

	//プレイヤーの当たり判定の範囲
	Plr.Hit.w = 32;		//当たり判定の幅、高さ
	Plr.Hit.h = 76;
	Plr.Hit.x = Plr.x + (Plr.w>>1) - (Plr.Hit.w>>1);		//当たり判定のXY座標
	Plr.Hit.y = Plr.y + (Plr.h>>1) - (Plr.Hit.h>>1);
	
	//剣の当たり判定の範囲
	Swd.Hit.w = 22;		//当たり判定の幅
	Swd.Hit.h = 90;
	Swd.Hit.x = Swd.x + (Swd.w>>1) - (Swd.Hit.w>>1);
	Swd.Hit.y = Swd.y + (Swd.h>>1) - (Swd.Hit.h>>1);
	

	//エネミー１のあたり判定の範囲
	EnemyNum[1].Hit.w = 80;
	EnemyNum[1].Hit.h = 60;
	EnemyNum[1].Hit.x = EnemyNum[1].x + (EnemyNum[1].w>>1) - (EnemyNum[1].Hit.w>>1);
	EnemyNum[1].Hit.y = EnemyNum[1].y + (EnemyNum[1].h>>1) - (EnemyNum[1].Hit.h>>1);

	//エネミー２のあたり判定の範囲
	EnemyNum[2].Hit.w = 112;
	EnemyNum[2].Hit.h = 64;
	EnemyNum[2].Hit.x = EnemyNum[2].x + (EnemyNum[2].w>>1) - (EnemyNum[2].Hit.w>>1);
	EnemyNum[2].Hit.y = EnemyNum[2].y + (EnemyNum[2].h>>1) - (EnemyNum[2].Hit.h>>1);

	//エネミー３
	EnemyNum[4].Hit.w = 32;
	EnemyNum[4].Hit.h = 76;
	EnemyNum[4].Hit.x = EnemyNum[4].x + (EnemyNum[4].w>>1) - (EnemyNum[4].Hit.w>>1);
	EnemyNum[4].Hit.y = EnemyNum[4].y + (EnemyNum[4].h>>1) - (EnemyNum[4].Hit.h>>1);

	//エネミー４
	EnemyNum[5].Hit.w = 32;
	EnemyNum[5].Hit.h = 76;
	EnemyNum[5].Hit.x = EnemyNum[5].x + (EnemyNum[5].w>>1) - (EnemyNum[5].Hit.w>>1);
	EnemyNum[5].Hit.y = EnemyNum[5].y + (EnemyNum[5].h>>1) - (EnemyNum[5].Hit.h>>1);

	//エネミー５
	EnemyNum[6].Hit.w = 48;
	EnemyNum[6].Hit.h = 108;
	EnemyNum[6].Hit.x = EnemyNum[6].x + (EnemyNum[6].w>>1) - (EnemyNum[6].Hit.w>>1);
	EnemyNum[6].Hit.y = EnemyNum[6].y + (EnemyNum[6].h>>1) - (EnemyNum[6].Hit.h>>1);

	//エネミー６
	EnemyNum[7].Hit.w = 30;
	EnemyNum[7].Hit.h = 30;
	EnemyNum[7].Hit.x = EnemyNum[7].x + (EnemyNum[7].w>>1) - (EnemyNum[7].Hit.w>>1);
	EnemyNum[7].Hit.y = EnemyNum[7].y + (EnemyNum[7].h>>1) - (EnemyNum[7].Hit.h>>1);

	//エネミー７(鉄犬
	EnemyNum[8].Hit.w = 90;
	EnemyNum[8].Hit.h = 68;
	EnemyNum[8].Hit.x = EnemyNum[8].x + (EnemyNum[8].w>>1) - (EnemyNum[8].Hit.w>>1);
	EnemyNum[8].Hit.y = EnemyNum[8].y + (EnemyNum[8].h>>1) - (EnemyNum[8].Hit.h>>1);

	//エネミー８（小動物
	EnemyNum[9].Hit.w = 32;
	EnemyNum[9].Hit.h = 28;
	EnemyNum[9].Hit.x = EnemyNum[9].x + (EnemyNum[9].w>>1) - (EnemyNum[9].Hit.w>>1);
	EnemyNum[9].Hit.y = EnemyNum[9].y + (EnemyNum[9].h>>1) - (EnemyNum[9].Hit.h>>1);

	//エネミー９（蜂
	EnemyNum[10].Hit.w = 40;
	EnemyNum[10].Hit.h = 48;
	EnemyNum[10].Hit.x = EnemyNum[10].x + (EnemyNum[10].w>>1) - (EnemyNum[10].Hit.w>>1);
	EnemyNum[10].Hit.y = EnemyNum[10].y + (EnemyNum[10].h>>1) - (EnemyNum[10].Hit.h>>1);

	//ツボ
	EnemyNum[11].Hit.w = 48;
	EnemyNum[11].Hit.h = 94;
	EnemyNum[11].Hit.x = EnemyNum[11].x + (EnemyNum[11].w>>1) - (EnemyNum[11].Hit.w>>1);
	EnemyNum[11].Hit.y = EnemyNum[11].y + (EnemyNum[11].h>>1) - (EnemyNum[11].Hit.h>>1);

	//エネミー10（骨口
	EnemyNum[12].Hit.w = 84;
	EnemyNum[12].Hit.h = 56;
	EnemyNum[12].Hit.x = EnemyNum[12].x + (EnemyNum[12].w>>1) - (EnemyNum[12].Hit.w>>1);
	EnemyNum[12].Hit.y = EnemyNum[12].y + (EnemyNum[12].h>>1) - (EnemyNum[12].Hit.h>>1);


	//ボス１
	EnemyNum[3].Hit.w = 80;
	EnemyNum[3].Hit.h = 48;


	//アニメーションで使う絵(Bmp)を設定
	Anime[0][0].Bmp = lpDDSOff_CharWAIT;			//待機アニメのBMPの準備
	Anime[1][0].Bmp = lpDDSOff_Char;				//移動
	Anime[2][0].Bmp = lpDDSOff_CharDash;			//ダッシュ
	Anime[3][0].Bmp = lpDDSOff_CharDown;			//しゃがみ
	Anime[4][0].Bmp = lpDDSOff_CharAttackY;		//横斬り
	Anime[5][0].Bmp = lpDDSOff_CharAttackT;		//縦斬り
	Anime[6][0].Bmp = lpDDSOff_CharJump;			//ジャンプUP
	Anime[7][0].Bmp = lpDDSOff_CharJump;			//ジャンプDOWN
	Anime[8][0].Bmp = lpDDSOff_CharDead;			//キャラやられ
	Anime[9][0].Bmp = lpDDSOff_CharDamage;		//キャラがダメージをうける絵
	Anime[10][0].Bmp = lpDDSOff_CharDownAttackT;	//しゃがみ縦斬り
	Anime[11][0].Bmp = lpDDSOff_CharDownAttackY;	//しゃがみ横斬り
	Anime[12][0].Bmp = lpDDSOff_CharJumpAttackT;	//ジャンプ縦斬り
	Anime[13][0].Bmp = lpDDSOff_CharJumpAttackY;	//ジャンプ横斬り
	Anime[14][0].Bmp = lpDDSOff_CharUpSwd;		//キャラ上剣投げ
	Anime[15][0].Bmp = lpDDSOff_CharLRSwd;		//キャラ左右剣投げ
	Anime[16][0].Bmp = lpDDSOff_CharJumpDownSwd;	//キャラジャンプ下剣投げ
	Anime[17][0].Bmp = lpDDSOff_CharDownSwd;		//キャラしゃがみ剣投げ
	Anime[18][0].Bmp = lpDDSOff_CharBall;			//プレイヤーバリア
	Anime[19][0].Bmp = lpDDSOff_CharReturnSwd;		//プレイヤー剣吸収
	Anime[20][0].Bmp = lpDDSOff_CharSwdHPUP;		//プレイヤー剣HP入れ替え

	//剣
	AniSwd[0][0].Bmp = lpDDSOff_Swd;		//剣上向き
	AniSwd[1][0].Bmp = lpDDSOff_Swd;		//剣下向き
	AniSwd[2][0].Bmp = lpDDSOff_Swd;		//剣左向き
	AniSwd[3][0].Bmp = lpDDSOff_Swd;		//剣右向き
	AniSwd[4][0].Bmp = lpDDSOff_Swd;		//剣出現
	AniSwd[5][0].Bmp = lpDDSOff_Swd;		//剣が消える

	//エネミー１（犬
	AniEn[1][0][0].Bmp = lpDDSOff_En1;		//待機
	AniEn[1][1][0].Bmp = lpDDSOff_En1;		//攻撃
	AniEn[1][2][0].Bmp = lpDDSOff_En1;		//ジャンプ
	AniEn[1][3][0].Bmp = lpDDSOff_En1;		//ダメージ
	//エネミー２（トカゲ
	AniEn[2][0][0].Bmp = lpDDSOff_En2;		//待機
	AniEn[2][1][0].Bmp = lpDDSOff_En2;		//移動
	AniEn[2][2][0].Bmp = lpDDSOff_En2;		//かみつき
	AniEn[2][3][0].Bmp = lpDDSOff_En2;		//攻撃２
	AniEn[2][4][0].Bmp = lpDDSOff_En2;		//ダメージ

	//エネミー３(メカ兵
	AniEn[4][0][0].Bmp = lpDDSOff_En3;		//待機
	AniEn[4][1][0].Bmp = lpDDSOff_En3;		//歩行
	AniEn[4][2][0].Bmp = lpDDSOff_En3;		//銃撃
	AniEn[4][3][0].Bmp = lpDDSOff_En3;		//ダメージ

	//エネミー４（兵
	AniEn[5][0][0].Bmp = lpDDSOff_En4;		//待機
	AniEn[5][1][0].Bmp = lpDDSOff_En4;		//移動
	AniEn[5][2][0].Bmp = lpDDSOff_En4;		//銃撃
	AniEn[5][3][0].Bmp = lpDDSOff_En4;		//ダメージ
	
	//エネミー５（火人間
	AniEn[6][0][0].Bmp = lpDDSOff_En5;		//待機
	AniEn[6][1][0].Bmp = lpDDSOff_En5;		//移動
	AniEn[6][2][0].Bmp = lpDDSOff_En5;		//チャージ
	AniEn[6][3][0].Bmp = lpDDSOff_En5;		//ダメージ

	//エネミー６（枝
	AniEn[7][0][0].Bmp = lpDDSOff_En6;		//待機
	AniEn[7][1][0].Bmp = lpDDSOff_En6;		//攻撃
	AniEn[7][2][0].Bmp = lpDDSOff_En6;		//ダメージ

	//エネミー７（鉄犬
	AniEn[8][0][0].Bmp = lpDDSOff_En7;		//待機
	AniEn[8][1][0].Bmp = lpDDSOff_En7;		//アタック
	AniEn[8][2][0].Bmp = lpDDSOff_En7;		//ジャンプ
	AniEn[8][3][0].Bmp = lpDDSOff_En7;		//ダメージ
	AniEn[8][4][0].Bmp = lpDDSOff_En7;		//発砲

	//エネミー８（小動物
	AniEn[9][0][0].Bmp = lpDDSOff_En8;		//移動
	AniEn[9][1][0].Bmp = lpDDSOff_En8;		//ダメージ＆攻撃

	//エネミー９（蜂
	AniEn[10][0][0].Bmp = lpDDSOff_En9;		//移動
	AniEn[10][1][0].Bmp = lpDDSOff_En9;		//攻撃
	AniEn[10][2][0].Bmp = lpDDSOff_En9;		//ダメージ

	//ツボ
	AniEn[11][0][0].Bmp = lpDDSOff_EnTubo;		//待機1
	AniEn[11][1][0].Bmp = lpDDSOff_EnTubo;		//待機２
	AniEn[11][2][0].Bmp = lpDDSOff_EnTubo;		//待機３
	AniEn[11][3][0].Bmp = lpDDSOff_EnTubo;		//待機４
	AniEn[11][4][0].Bmp = lpDDSOff_EnTubo;		//待機５
	
	//エネミー１０（骨口
	AniEn[12][0][0].Bmp = lpDDSOff_En10;		//待機１
	AniEn[12][1][0].Bmp = lpDDSOff_En10;		//噛む
	AniEn[12][2][0].Bmp = lpDDSOff_En10;		//吐く
	AniEn[12][3][0].Bmp = lpDDSOff_En10;		//ダメージ

	//ボス１（竜
	AniEn[3][0][0].Bmp = lpDDSOff_Boss1;
	AniEn[3][1][0].Bmp = lpDDSOff_Boss1;	//移動
	AniEn[3][2][0].Bmp = lpDDSOff_Boss1;	//かみつき
	AniEn[3][3][0].Bmp = lpDDSOff_Boss1;	//ダメージ

	//GameLoad("MapData160-40_2.map");
	GameLoad("MAP\\MAP0_320-40_tipbmp8.map");			//マップデータをロード	
	//	EneOnPosLoad("EneOnData-30.enp");				//エネミーの出現位置データをロード
	EneOnPosLoad("ENEON_木2.enp");				//エネミー出現位置データをロード（木のステージ用

	//プレイヤー初期ステータス
	Plr.MaxHp = 500;
	Plr.Atk = 15;
	Plr.Spd = 5;

	Swd.MaxHp = 30;

	WMoveX = (279<<5);
}

/*-------------------------------------------------------------------------------------------------------
　　ゲームの解放をまとめた定義関数。
　　メッセージ終了直後に実行する。
-------------------------------------------------------------------------------------------------------*/
void GameRelease()	//ゲームの解放処理を行う関数
{
	//OutputDebugString("きた");

	//▼適出現位置データのメモリ解放
	if(pEneOn == NULL)	//解放しようとしている変数のメモリが確保されていなかったら
		MessageBox(NULL,"ポインタ変数にはメモリが確保されていません(pEneOn)","エラー",MB_OK);

	pEneOn = (ENE_ONPOS *)GlobalFree(pEneOn);	//メモリ解放
	
	if(pEneOn != NULL)	//GlobalFreeの戻値がNULLじゃなかったらエラー通知
		MessageBox(NULL,"メモリ解放失敗","エラー(pEneOn)",MB_OK);		

	//▼マップデータのメモリ解放
	if(pMap == NULL)	//解放しようとしている変数のメモリが確保されていなかったら
		MessageBox(NULL,"ポインタ変数にはメモリが確保されていません(pMap)","エラー",MB_OK);
	pMap = (int *)GlobalFree(pMap);	//メモリ解放
	if(pMap != NULL)	//GlobalFreeの戻り値がNULLじゃなかったらエラー通知
		MessageBox(NULL,"メモリ解放失敗","エラー(pMap)",MB_OK);					//エラーをメッセージボックスで表示
}