///////////// インクルード ////////////////////////////
#include <windows.h>
#include <ddraw.h>

#include "Extern.h"	//外部変数を扱うためのヘッダ

#include "GameTitle.h"	//ゲームタイトルのプロトタイプ宣言のヘッダ
#include "GameMain.h"	//ゲームメインのプロトタイプ宣言のヘッダ
#include "GameOver.h"	//ゲームオーバーのプロトタイプ宣言のヘッダ
#include "StageSelect.h"	//ステージセレクト画面のプロトタイプ宣言のヘッダ
#include "GameStop.h"		//ポーズ画面のプロトタイプ宣言

#include "GameCheckProc.h"
#include "DebugProc.h"	//テキスト表示などを扱うヘッダ
///////////// プロトタイプ宣言 ////////////////////////
void GameClear(int *);	//ゲームクリアー

//■■■■■■■■■■　メイン関数　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void Main()
{
/*	static int GameNum = 0;	/*どの処理を実行するかを扱う変数GameNumを0（最初はタイトル画面）で初期化
						0 ・・・タイトル
						1 ・・・ゲーム本編
						2 ・・・ゲームオーバー
						3 ・・・ゲームクリア   */
	static int CtrlNum = 0;		//初期状態はジョイパッドで

	void (*pGame[6])(int *);	//戻値なし、引数int型ポインタの関数のアドレスの、関数のポインタ配列の宣言

	pGame[0] = GameTitle;	//pGame[0]に定義関数GameTitleの先頭アドレスを代入
	pGame[1] = GameMain;	//pGame[1]に定義関数GameMainの先頭アドレスを代入
	pGame[2] = GameOver;	//pGame[2]に定義関数GameOverの先頭アドレスを代入
	pGame[3] = GameClear;	//pGame[3]に定義関数GameClearの先頭アドレスを代入
	pGame[4] = StageSelect;	//
	pGame[5] = GameStop;


	//▼ サーフェースロストの対策
	if(lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
		lpDDSPrimary->Restore();	

	if(!CtrlNum)	//CtrlNumが１ならこの処理をおこなわない
	{
		//▼ ジョイスティックなど、入力の取得
		MMRESULT ret;
		JoyData2 = JoyData;							//前回の値として、JoyDataを保存
		ret = joyGetPosEx(JOYSTICKID1,&JoyData);	//JoyDataの中にジョイスティックのデータが入る（JoyDataを更新）
		if(ret != JOYERR_NOERROR)					//retがJOYERR_NOERRORじゃなかったら
		{
			MessageBox(NULL,"ジョイスティックの取得に失敗（操作をキーボードで行います","エラー",MB_OK);	//エラー表示
			CtrlNum = 1;	//CtrlNumを１にして操作をキーボードで行う
		}

		Key = 0;					//Dumは0（0000 [0]）でスタート
		if(JoyData.dwXpos <= 10000)	//左が押されていたら
			Key |= 1;					//０ビット目を１に（0001 [1]）
		if(JoyData.dwYpos <= 10000)	//上が押されていたら
			Key |= (1<<1);				//１ビット目を１に（0010 [2]）
		if(JoyData.dwXpos >= 50000)	//右が押されていたら
			Key |= (1<<2);				//２ビット目を１に（0100 [4]）
		if(JoyData.dwYpos >= 50000)	//下が押されていたら
			Key |= (1<<3);				//３ビット目を１に（1000 [8]）

		//ボタンデータの取得
		Btn1 = 0;
		if(JoyData.dwButtons & (1<<1))	
			Btn1 |= (1<<1);				//１ビット目を１に（0010 [2]）
		if(JoyData2.dwButtons & 1)
			Btn1 |= 1;					//０ビット目を１に（0001 [1]）

		//ボタンの押している時間をカウント
		if(JoyData.dwButtons == JoyData2.dwButtons )
			BtnCnt++;
		else
			BtnCnt = 0;

	}else	//キーボードなら
	{

		if(Btn1 == Btn2)
			BtnCnt++;
		else
			BtnCnt = 0;
	}


	CmdGet = KeyCmdChk(Key);	//コマンドデータを保存する関数


//	while(TRUE)	//TRUEなので繰り返す
//	{
	//▼ゲーム処理
	pGame[GameNum](&GameNum);	//関数のポインタ配列の要素番号（GameNum）に対応した関数を実行
//	}

	//▼テキスト表示
	//Debug_DrawText();	//テキスト表示をまとめた関数

	lpDDSPrimary->Flip( NULL,DDFLIP_WAIT );				//フリップ（最終出力）
	

	Btn2 = Btn1;	//最新のボタンデータを前回のボタンデータに代入


}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


//■GameClear＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void GameClear(int *pGameNum)	//	機能：ゲームクリアー画面の処理を行う関数
//	●引数：ゲームの場面を扱う値
{
		*pGameNum = 0;	//間接参照で、GameNumを0にする（タイトル）
}