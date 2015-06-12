#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"
#include "GameBltProc.h"
#include "GameCheckProc.h"
//■GameOver＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void GameOver(int *pGameNum)	//	機能：ゲームオーバー画面の処理を行う関数
//●引数：ゲームの場面を扱う値（GameNum）
{
	int i,j;
	HDC hdc;				//デバイスコンテキスト
	char str[256];			//文字列を扱う
	DDBLTFX ddbltfx;		//ぬりつぶしに必要な構造体
	static int BkX;			//上下の■
	static int BkSpd;		//■のスクロールスピード

	//四角いプレートをスクロール
	BkSpd ++;
	if(BkSpd > 640)	BkSpd = 0;
	
	//ぬりつぶし（黒）
	ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
	ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);


	if((!(Btn2 & (1<<1)) && (Btn1 & (1<<1))) || Plr.Hp > 0)	//Bボタンを前回（離）で現在（押）なら 
	{
		*pGameNum = 1;	//間接参照でGameNumを１（ゲーム本編）にする。
		lpDDPal->SetEntries(0,0,255,MainPal);
	}

	ShotFire(Plr.x+(rand()%Plr.w),Plr.y+64+(rand()%32),0,25,10);	//Plr　から灰発射
	ShotFire(200+(rand()%128),200+(rand()%32),0,25,10);				//文字　から灰発射
	ShotMove(0,0);	//弾の移動

	//パレット７１番目の色を変更（GameOverの文字の色を変更
	lpDDPal->GetEntries(0,71,1,SubPal);
	SubPal[0].peRed  = 255;
	SubPal[0].peGreen = rand()%255;
	SubPal[0].peBlue = rand()%255;
	lpDDPal->SetEntries(0,71,1,SubPal);

	//●灰色のプレートをスクロールして表示
	BkX = BkSpd;				//スクロールスピードを設定
	BkX %= 32;					//0～32
	if(BkX <= 0)	BkX = 32;
	for(j = 0;j < 2;j++)
	{
		for(i = 0;i < 20;i++)
		{
			MyBltFast(	(i*32)+32-BkX,(j*464),	
						lpDDSOff_Text,
						288,320,	288+BkX+32,320+16);
			MyBltFast(	(i*32),(j*464),	
						lpDDSOff_Text,
						288+BkX,320,	288+BkX+(32-BkX),320+16);
		}
	}


	//●弾（灰
	for(i = 0;i < SHOT_MAX;i++)	//弾の数だけ繰り返す
		ShotBitBlt(&Shot[i]);		//●弾表示

	//●プレイヤー
	ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//プレイヤー表示

	//●GameOver文字
	MyBltFast(	200,200,
		lpDDSOff_Text,
		160,320,
		288,352);

	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);
}