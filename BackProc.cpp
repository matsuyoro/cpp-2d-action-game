#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"

#include "GameBltProc.h"
#include "GameCheckProc.h"

///////////// プロトタイプ宣言 ////////////////////////
void Back_0();	//ステージ０の背景処理の関数のプロトタイプ宣言
void Back_1();	//ステージ１の背景処理の関数のプロトタイプ宣言
void Back_2();	//ステージ２の背景処理の関数のプロトタイプ宣言
void Back_3();	//ステージ３の背景処理の関数のプロトタイプ宣言
void Back_4();	//ステージ４の背景処理の関数のプロトタイプ宣言

//■　BackProc　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void BGBlt()	//	機能：背景処理の関数
//	●引数：背景のステージ
{
	void (*pBG[5])();		//戻値なし、引数なしの関数のポインタ配列の宣言
	pBG[0] = Back_0;	//pBG[0]に定義関数Back_0の先頭アドレスを代入
	pBG[1] = Back_1;	//
	pBG[2] = Back_2;
	pBG[3] = Back_3;
	pBG[4] = Back_4;

	//▼StageNumの値の背景の処理を行う
	pBG[StageNum]();	//関数のポインタ配列の要素番号（StageNum）に対応した関数を実行
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

//===============================================================================================
void Back_0()			//機能：背景を表示する関数（森のステージ
{
	int i;	//カウンタ
	static int namiX = 0;	//波を扱う
	static int sx;
	


	MyBltFast(0,0,lpDDSOff_Back0,0,0,640,240);		//背景の上半分を表示

	namiX ++;	//毎回＋＋
	if(namiX == 360)	namiX = 0;	//360を超えると０に戻す

	//水面の波のうごきを表示
	for(i = 0;i < 120;i++)	
	{
		MyBltFast((int)(SinT[namiX+i]*10),240+i,		//表示先XY座標
			lpDDSOff_Back0,								//表示する絵のオフスクリーンサーフェース
			0,240-(i<<1),								//転送元左上XY座標
			640,(240-(i<<1))+1	);							//転送元右下XY座標
	}

}

//=================================================================================================
void Back_1()			//機能：背景を表示する関数(廃墟のステージ
{
	int i;	//カウンタ
	static int namiX = 0;	//波を扱う
	static int sx;
	
	//夕焼け
	namiX ++;	//毎回＋＋
	if(namiX == 360)	namiX = 0;	//360を超えると０に戻す

	for(i = 0;i < 240;i++)	//水面の波のうごきを表示
	{
		MyBltFast((int)(SinT[namiX+i]*10),i,		//表示先XY座標
			lpDDSOff_Back1,								//表示する絵のオフスクリーンサーフェース
			0,240+i,								//転送元左上XY座標
			640,(240+i)+1	);							//転送元右下XY座標
	}

	//背景地面
	for(i = 0;i < 6;i++)	//640*40の絵を６枚並べて表示
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
		sx %= 640;			//0～640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,240+(i*40),	//背景地面の右側を表示
					lpDDSOff_Back1,
					0,i*40,
					sx,(i*40)+40	);
		MyBltFast(	0,240+(i*40),		//背景地面の左側を表示
					lpDDSOff_Back1,
					sx,i*40,
					sx+(640-sx),(i*40)+40	);
	}
	//背景オブジェのスクロール
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son)	//背景オブジェが存在するなら
		{
			sx = (int)BGScrX*(BgObj[i].Line+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
			sx %= 640+BgObj[i].orgX+BgObj[i].w;			//0～640
			//if(sx <= 0)	sx = 640+BgObj[i].orgX;	//0より小さいくなったら戻す

			BgObj[i].x = (640-sx)+BgObj[i].orgX;	//スクロール量＋オブジェのメンバorgXの値の座標に設定
		}
		BgObjBlt(&BgObj[i]);		//●背景オブジェ表示
	}
}
//=================================================================================================
void Back_2()			//機能：背景を表示する関数(砂漠基地のステージ
{
	int i;	//カウンタ
	static int sx;
	static int StartPalCnt;	//少しずつ明るくするためのカウンタ

	if(StartPalCnt < 255)	//ステージが始まって一定時間は画面を明るくする処理を行う
	{
		StartPalCnt ++;	//毎回＋＋

		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素をクリメントし、元の色に近づけいく
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < MainPal[i].peRed)
				SubPal[i].peRed ++;	//赤の要素を増やす		
			if(SubPal[i].peGreen < MainPal[i].peGreen)
				SubPal[i].peGreen ++;	//緑を増やす
			if(SubPal[i].peBlue < MainPal[i].peBlue)
				SubPal[i].peBlue ++;		//青を増やす
		}
		lpDDPal->SetEntries(0,0,256,SubPal);
	}

	MyBltFast(0,0,							//表示先XY座標
		lpDDSOff_Back2,						//表示する絵のオフスクリーンサーフェース
		0,0,								//転送元左上XY座標
		640,160	);							//転送元右下XY座標


	//背景地面
	for(i = 0;i < 10;i++)	//640*40の絵を６枚並べて表示
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
		sx %= 640;			//0～640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,160+(i*32),	//背景地面の右側を表示
					lpDDSOff_Back2,
					0,160+(i*32),
					sx,160+((i*32)+32)	);
		MyBltFast(	0,160+(i*32),		//背景地面の左側を表示
					lpDDSOff_Back2,
					sx,160+(i*32),
					sx+(640-sx),160+((i*32)+32)	);
	}
	/*
	//背景オブジェのスクロール
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son)	//背景オブジェが存在するなら
		{
			sx = (int)BGScrX*(BgObj[i].Line+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
			sx %= 640+BgObj[i].orgX+BgObj[i].w;			//0～640
			//if(sx <= 0)	sx = 640+BgObj[i].orgX;	//0より小さいくなったら戻す

			BgObj[i].x = (640-sx)+BgObj[i].orgX;	//スクロール量＋オブジェのメンバorgXの値の座標に設定
		}
		BgObjBlt(&BgObj[i]);		//●背景オブジェ表示
	}
	*/
}
//===============================================================================================
void Back_3()			//機能：背景を表示する関数（嵐のステージ
{
	int i;	//カウンタ
	static int sx;
	static int kiAni;
	static int kix;
	
	kiAni++;
	if(kiAni > 6)	kiAni = 0;

	//▼葉っぱをちらす
	if(rand()%5 == 1)	
		ShotFire(640,rand()%480,0,10,10);	//存在の種類を１０して当たり判定を行わない



	//背景地面
	for(i = 0;i < 6;i++)	//640*40の絵を６枚並べて表示
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
		sx %= 640;				//0～640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,256+(i*32),	//背景地面の右側を表示
					lpDDSOff_Back3,
					0,256+(i*32),
					sx,256+((i*32)+32));
		MyBltFast(	0,256+(i*32),		//背景地面の左側を表示
					lpDDSOff_Back3,
					sx,256+(i*32),
					sx+(640-sx),256+((i*32)+32)	);
	}

	kix = (int)BGScrX*(1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
	kix %= 84;				//0～640
	if(sx <= 0)	sx = 84;

	for(i = 0;i < 8;i++)
	{
		MyBltFast(	(i*84)+84-kix,160,	//背景地面の右側を表示
					lpDDSOff_Back3,
					0+(kiAni*84),160,
					kix+(kiAni*84),160+96);
		MyBltFast(	(i*84),160,		//背景地面の左側を表示
					lpDDSOff_Back3,
					kix+(kiAni*84),160,
					kix+(84-kix)+(kiAni*84),160+96);
	}



}
//=================================================================================================
void Back_4()			//機能：背景を表示する関数(メカのステージ
{
	int i;	//カウンタ
	static int sx;
	static int StartPalCnt;	//少しずつ明るくするためのカウンタ

	if(StartPalCnt < 255)	//ステージが始まって一定時間は画面を明るくする処理を行う
	{
		StartPalCnt ++;	//毎回＋＋

		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素をクリメントし、元の色に近づけいく
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < MainPal[i].peRed)
				SubPal[i].peRed ++;	//赤の要素を増やす		
			if(SubPal[i].peGreen < MainPal[i].peGreen)
				SubPal[i].peGreen ++;	//緑を増やす
			if(SubPal[i].peBlue < MainPal[i].peBlue)
				SubPal[i].peBlue ++;		//青を増やす
		}
		lpDDPal->SetEntries(0,0,256,SubPal);
	}

	MyBltFast(0,0,							//表示先XY座標
		lpDDSOff_Back2,						//表示する絵のオフスクリーンサーフェース
		0,0,								//転送元左上XY座標
		640,160	);							//転送元右下XY座標


	//背景地面
	for(i = 0;i < 10;i++)	//640*40の絵を６枚並べて表示
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)で背景の絵のスクロールスピードを設定
		sx %= 640;			//0～640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,160+(i*32),	//背景地面の右側を表示
					lpDDSOff_Back2,
					0,160+(i*32),
					sx,160+((i*32)+32)	);
		MyBltFast(	0,160+(i*32),		//背景地面の左側を表示
					lpDDSOff_Back2,
					sx,160+(i*32),
					sx+(640-sx),160+((i*32)+32)	);
	}

}
