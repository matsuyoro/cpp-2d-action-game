
#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"
#include "GameCheckProc.h"
///////////// プロトタイプ宣言 ////////////////////////
void Title_01();	//タイトルの画面のイベント処理を分ける処理の関数（映写機
void Title_02();	//ロゴ
//void StageSetUp_2();	//ステージ２をはじめるための準備の関数のプロトタイプ宣言

//■GameTitle＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void GameTitle(int *pGameNum)	//	機能：タイトル画面の処理
//	●引数：ゲームの場面を扱う値
{
	HDC hdc;				//デバイスコンテキスト
	char str[256];			//文字列を扱う
	static int TitleCnt;
	static int TitleNum;	//タイトルのいろいろな場面を扱う番号
	static int GameStartCnt ;	//ゲームスタート時のフェードアウトカウント
	int i;

	void (*pTitle[2])();	//戻値なし、引数int型ポインタの関数のアドレスの、関数のポインタ配列の宣言
	pTitle[0] = Title_01;	//pTitle[0]に定義関数Title_01の先頭アドレスを代入
	pTitle[1] = Title_02;	//関数Title_02の先頭アドレスを代入

	TitleCnt++;

	if(TitleCnt > 3000	//タイトルカウントが1000を超えたら
	|| (!(Btn2 & (1<<1)) && (Btn1 & (1<<1)))	//Bボタンを前回（離）で現在（押）なら 
	)
	{
		
		if(TitleCnt > 540)
			GameStartCnt = 1;	//フェードアウトしてゲームスタート
		else
			*pGameNum = 1;	//間接参照でGameNumを１（ゲーム本編）にする。

	}
	if(GameStartCnt)	//GameStartCntがTRUEなら
	{
		GameStartCnt ++;	//毎回＋１

		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素をデクリメントし、０（黒）に近づけいく
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed > 0)
				SubPal[i].peRed --;	//赤の要素を減らす			
			if(SubPal[i].peGreen > 0)
				SubPal[i].peGreen --;	//緑の要素をへらす
			if(SubPal[i].peBlue > 0)
				SubPal[i].peBlue --;		//青の要素を減らす
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(GameStartCnt >= 255)	//255以上になったらゲーム本編に切り替え
		{	
			*pGameNum = 1;	//間接参照でGameNumを１（ゲーム本編）にする。
		}
	}

	if(TitleCnt < 100)
		TitleNum = 0;
	else
		TitleNum = 1;
	pTitle[TitleNum]();	//関数のポインタ配列の要素番号（SlctNum）に対応した関数を実行


	//描画を行うサーフェースのデバイスコンテキストを取得
	lpDDSBackBuffer->GetDC(&hdc);

	//文字表示
	SetBkColor(hdc,RGB(255,0,0));			//文字のバックカラーの指定
	SetTextColor(hdc,RGB(255,255,255));		//文字色の指定
	SetBkMode(hdc,TRANSPARENT);				//文字を透明にする
	wsprintf(str,"title_______%d",TitleCnt);
	TextOut(hdc,100,140,str,lstrlen(str));

//	wsprintf(str,"TBGC %d",TitleBGClr);
//	TextOut(hdc,100,180,str,lstrlen(str));

	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);

	if(*pGameNum == 1)			
		lpDDPal->SetEntries(0,0,255,MainPal);	//パレットを元に戻す

}
//===========================================================================================
void Title_01()	//映写機を表現する処理
{
	HDC hdc;				//デバイスコンテキスト
	int i;

	DDBLTFX ddbltfx;	//ぬりつぶしに必要な構造体
	HPEN hPen;			//作成したペンを扱う
	HPEN hPenOld;		//古いペンを保存する

	static int LineX,LineY;
	int rndLX;
	static int TitleBGClr;	//タイトルの背景色を扱う
	static int TBGC_time;	//タイトル背景色の色を一定時間ごとに変更(目に悪そうだから

	TBGC_time ++;	//カウント
	if(TBGC_time > (7-(rand()%4)) )	//カウントが一定の時間を超えるとタイトル背景色を変更
	{
		TitleBGClr = (rand()%5)+6;
		TBGC_time = 0;
	}

	//ぬりつぶし（黒）
	ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
	ddbltfx.dwFillColor = TitleBGClr;				//ぬりつぶす色を指定
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);


	//描画
	if(rand()%5 == 1)
	{
		//しみを表示
		MyBltFast(	140,200,	//表示先XY座標
				lpDDSOff_Text,	//表示する絵のオフスクリーンサーフェース
				128,	24,		//転送元左上XY座標
				136,	32);	//転送元右下XY座標
		MyBltFast( 400,320,
				lpDDSOff_Text,
				128,	32,
				136,	40);
		MyBltFast(580,20,
				lpDDSOff_Text,
				128,	40,
				136,	48);
		MyBltFast(210,87,
				lpDDSOff_Text,
				128,	48,
				136,	64);
	}
	for(i = 0;i < 10;i++)
	{
		MyBltFast(rand()%640,rand()%480,
					lpDDSOff_Text,
					128,	32,
					129,	33);
	}		

	//描画を行うサーフェースのデバイスコンテキストを取得
	lpDDSBackBuffer->GetDC(&hdc);



	//プレイヤーの攻撃当たり判定の範囲を表す線の設定
	hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));	//点線、太さ１,緑色のペンを作成し、hPenに保存
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。
	
	for(i = 0;i < 8;i++)
	{
		//プレイヤーの攻撃範囲を表す四角を描画
		if(rand()%7 == 1)	//プレイヤー攻撃中の当たり判定部分を表示
		{
			rndLX = rand()%640;
		
			if(rand()%2 == 1)
			{
				MoveToEx(hdc,rndLX,0,NULL);
				LineTo(hdc,rndLX,rand()%480);
			}else
			{
				MoveToEx(hdc,rndLX,rand()%480,NULL);
				LineTo(hdc,rndLX,480);
			}
		}
	}

	LineX += (rand()%4)-1;
	if(LineX < 0) LineX = rand()%640;
	if(LineX > 640) LineX = rand()%640;

	LineY -= (rand()%4)-2;
	if(LineY < 0)	LineY = rand()%480;
	if(LineY > 480) LineY = rand()%480;

	if(rand()%30 == 1)	LineX = rand()%640;

	if(rand()%2 == 1)
	{
		for(i = 0;i < 2;i++)
		{
			MoveToEx(hdc,LineX+(i*40),0,NULL);
			LineTo(hdc,LineX+(i*40),rand()%480);

			MoveToEx(hdc,LineX+(i*40),rand()%480,NULL);
			LineTo(hdc,LineX+(i*40),480);
		}
	}

	SelectObject(hdc,hPenOld);		//ペンを元に戻す
	DeleteObject(hPen);				//作成したペンの削除

	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);

}
//=============================================================================================
void Title_021()	//タイトルロゴ
{
	HDC hdc;				//デバイスコンテキスト
	int i,j;
	static int SlctMenu;	//タイトルのメニュー選択で使用
	static int TitleCnt02;
	int RndMenu;

	DDBLTFX ddbltfx;	//ぬりつぶしに必要な構造体
	HPEN hPen;			//作成したペンを扱う
	HPEN hPenOld;		//古いペンを保存する

	int	RndNum = rand()%255;
	static int LineMove;	//線の動きの種類を扱う

	TitleCnt02 ++;
	if(TitleCnt02 > 500) TitleCnt02 = 0;

	//上下でメニュー選択
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;

	//メニューの番号に限界を持たせる
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;

	if(rand()%20 == 1)
		LineMove = rand()%4;	//ランダムで線の動きを変える

	if(LineMove == 0)
	{
		for(i = 0;i < 10;i++)
		{
			ShotFire(rand()%640,rand()%480,0,19,2);
			ShotFire(rand()%640,rand()%480,0,19,1);
		}
	}
	//▽弾の移動

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//弾の種類が20で、存在するなら
		{
		
			if(Shot[i].Son && LineMove == 0)
			{
				
				if(Shot[i].x+4 > 320)	//弾がプレイヤーより右にいたら
					Shot[i].mx --;					//弾の移動量をデクリメント
				else								//左にいたら
					Shot[i].mx ++;					//弾の移動量をインクリメント
				Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ
				
				if(Shot[i].y+4 > 240)	//弾がプレイヤーより下にいたら
					Shot[i].my --;					
				else								//上にいたら
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
			
			}
				//線速度の減速
			if(rand()%3 == 1)
			{
				if(Shot[i].mx > 0)	Shot[i].mx --;
				if(Shot[i].mx < 0)	Shot[i].mx ++;
				if(Shot[i].my > 0)	Shot[i].my --;
				if(Shot[i].my < 0)	Shot[i].my ++;
			}

			if(LineMove == 1)
			{
				if(Shot[i].x+4 > 320)	//弾がプレイヤーより右にいたら
					Shot[i].mx --;					//弾の移動量をデクリメント
				else								//左にいたら
					Shot[i].mx ++;					//弾の移動量をインクリメント
				Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ
			}

			if(LineMove == 2)
			{
				if(Shot[i].y+4 > 240)	//弾がプレイヤーより下にいたら
					Shot[i].my --;					
				else								//上にいたら
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
			}

			if(LineMove == 3)
			{
				if(Shot[i].x+4 > 320)	//弾がプレイヤーより右にいたら
					Shot[i].mx --;					//弾の移動量をデクリメント
				else								//左にいたら
					Shot[i].mx ++;					//弾の移動量をインクリメント
				Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ
		
				if(Shot[i].y+4 > 240)	//弾がプレイヤーより下にいたら
					Shot[i].my --;					
				else								//上にいたら
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
			}
			

			if(Shot[i].y > 480 || Shot[i].y < -Shot[i].h
			|| Shot[i].x > 640 || Shot[i].x < -Shot[i].w+50)	//画面の外に出たら
			{
				Shot[i].Son = FALSE;					//存在をFALSEに
			}
			if(LineMove == 0)
				if(rand()%20 == 1) Shot[i].Son = FALSE;
			
		}		
	}

	if(1)//rand()%5 == 1)	//左を押していないなら
	{
		//ぬりつぶし（黒）
		ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
		ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);
	}

	lpDDSBackBuffer->GetDC(&hdc);


	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//弾が存在し、種類が２０なら
		{
			if(Shot[i].Son == 2)
				hPen = CreatePen(PS_SOLID,(TitleCnt02>>5)+(rand()%5),RGB(255,((Shot[i].y>>1)-i)%255,0));	//点線、太さ１,緑色のペンを作成し、hPenに保存
			else
				hPen = CreatePen(PS_SOLID,(TitleCnt02>>5)+(rand()%5),RGB(0,((Shot[i].y>>1)-i)%255,255));	//点線、太さ１,緑色のペンを作成し、hPenに保存

			hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。

			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);

			SelectObject(hdc,hPenOld);		//ペンを元に戻す
			DeleteObject(hPen);				//作成したペンの削除

		}
	}

	lpDDSBackBuffer->ReleaseDC(hdc);


/*
	MyBltFast(	0,0,	//表示先XY座標
		lpDDSOff_Text,	//表示する絵のオフスクリーンサーフェース
		0,	240,		//転送元左上XY座標
		640,	480);	//転送元右下XY座標
*/


	if(TitleCnt02 > 200)	
	{

		MyBltFast(140,100,lpDDSOff_Text,0,432,352,468);

		//NewGame
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}else
	{
		MyBltFast(250,260+(200-TitleCnt02),lpDDSOff_Text,0,224,127,256);
		MyBltFast(250,300-(200-TitleCnt02),lpDDSOff_Text,0,288,67,320);
	}
}
//=============================================================================================
void Title_022()	//タイトルロゴ
{
	HDC hdc;				//デバイスコンテキスト
	int i,j;
	static int SlctMenu;	//タイトルのメニュー選択で使用
	static int TitleCnt02;
	int RndMenu;

	DDBLTFX ddbltfx;	//ぬりつぶしに必要な構造体
	HPEN hPen;			//作成したペンを扱う
	HPEN hPenOld;		//古いペンを保存する

	int LineSize;
	int	RndNum = rand()%255;
	static int fiveCnt;

	fiveCnt++;
	if(fiveCnt > 1)	fiveCnt = 0;

	TitleCnt02 ++;
	if(TitleCnt02 > 500) TitleCnt02 = 0;

	//上下でメニュー選択
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;

	//メニューの番号に限界を持たせる
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;

	for(i = 0;i < 10;i++)
	{
		ShotFire(rand()%640,480,0,19,2);
		ShotFire(rand()%640,480,0,19,1);
	}

	//▽弾の移動

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//弾の種類が20で、存在するなら
		{
	/*
			if(Shot[i].x+4 > 320)	//弾がプレイヤーより右にいたら
			{
				if(Shot[i].Son == 1)
					Shot[i].mx --;					//弾の移動量をデクリメント
			//	else
			//		Shot[i].mx ++;
			}else								//左にいたら
			{
				if(Shot[i].Son == 1)
					Shot[i].mx ++;					//弾の移動量をインクリメント
			//	else
		//			Shot[i].mx --;
			}
			Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ
	*/		
			
			if(Shot[i].Son == 2)
				Shot[i].my --;
			else
			{
				if(Shot[i].y+4 > 300)
					Shot[i].my --;
				else
					Shot[i].my ++;
			}
			Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
		}
	

		if(Shot[i].y > 480 || Shot[i].y < -Shot[i].h
		|| Shot[i].x > 640 || Shot[i].x < -Shot[i].w+50)	//画面の外に出たら
		{
			Shot[i].Son = FALSE;					//存在をFALSEに
		}
			
		//if(rand()%5 == 1) Shot[i].Son = FALSE;	
	}

	if(1)//rand()%5 == 1)	//左を押していないなら
	{
		//ぬりつぶし（黒）
		ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
		ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);
	}

	lpDDSBackBuffer->GetDC(&hdc);


	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//弾が存在し、種類が２０なら
		{
			if(Shot[i].Son == 2)
			{
				hPen = CreatePen(PS_SOLID,10+(Shot[i].my>>1),RGB(255,((Shot[i].y>>1)-i)%255,0));	//点線、太さ１,緑色のペンを作成し、hPenに保存
			}else
			{
				hPen = CreatePen(PS_SOLID,10-(-Shot[i].my>>1),RGB(0,((Shot[i].y>>1)-i)%255,255));	//点線、太さ１,緑色のペンを作成し、hPenに保存
			}

			hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。

			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);

			SelectObject(hdc,hPenOld);		//ペンを元に戻す
			DeleteObject(hPen);				//作成したペンの削除

		}
	}

	lpDDSBackBuffer->ReleaseDC(hdc);


	if(TitleCnt02 > 50)	
	{

		MyBltFast(140,100,lpDDSOff_Text,0,432,352,468);

		//NewGame
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}
}
//=============================================================================================
void Title_02()	//タイトルロゴ
{
	HDC hdc;				//デバイスコンテキスト
	static int SlctMenu;	//タイトルのメニュー選択で使用
	static int TitleCnt02;
	int RndMenu;
	int RndPalClr;	//パレットの色を毎回乱数で色を変化

	DDBLTFX ddbltfx;	//ぬりつぶしに必要な構造体
	HPEN hPen;			//作成したペンを扱う
	HPEN hPenOld;		//古いペンを保存する
	int i,j;
	static int LineX,LineY;
	int rndLX;
	static int TitleBGClr;	//タイトルの背景色を扱う
	static int TBGC_time;	//タイトル背景色の色を一定時間ごとに変更(目に悪そうだから
	int RndPal;
	static int MojiZoom  = 270;

	RndPalClr = 12;

	TitleCnt02 ++;
	if(TitleCnt02 > 1000) TitleCnt02 = 541;

	//上下でメニュー選択
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;
	//メニューの番号に限界を持たせる
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;


	if(	TitleCnt02 == 0		//タイトル文字が出現する時
	||	TitleCnt02 == 270	//プレイヤーが出現する時
	||	TitleCnt02 == 340	//適当なタイミングでフラッシュ
	||	TitleCnt02 == 380	//適当なタイミングでフラッシュ
	||	TitleCnt02 == 390	//〃
	||	TitleCnt02 == 420	//〃
	||	TitleCnt02 == 425	//〃
	||	TitleCnt02 == 433	//〃
	||	TitleCnt02 == 490	//〃
	||	TitleCnt02 == 520	//〃
	||	TitleCnt02 == 528	//〃
	||	TitleCnt02 == 540	//メニューが表示されるとき
	)	
	{
		lpDDPal->SetEntries(0,0,255,MainPal);	//パレットを元に戻す
	}

	if(TitleCnt02 >= 270 && TitleCnt02 < 540)	//プレイヤーが移動している時だけ
	{
		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素をデクリメントし、０（黒）に近づけいく
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed > RndPalClr)
				SubPal[i].peRed -= RndPalClr;	//赤の要素を減らす			
			if(SubPal[i].peGreen > RndPalClr)
				SubPal[i].peGreen -= RndPalClr;	//緑の要素をへらす
			if(SubPal[i].peBlue > RndPalClr)
				SubPal[i].peBlue -= RndPalClr;		//青の要素を減らす
		}
		lpDDPal->SetEntries(0,0,255,SubPal);
	}

	if(1)//rand()%5 == 1)	//左を押していないなら
	{	
		
		//ぬりつぶし（黒）
		ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
		ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);

	}

	//プレイヤーのコートの模様の色を変化
	lpDDPal->GetEntries(0,0,255,SubPal);
	SubPal[36].peRed  = 255;
	SubPal[36].peGreen = (TitleCnt02<<2)%255;
	SubPal[36].peBlue = (TitleCnt02<<2)%255;
	lpDDPal->SetEntries(0,0,255,SubPal);


	if(TitleCnt02 < 270)
	{
		//ズームダウンタイトル
		MojiZoom --;
		for(j = 0;j < 15;j++)
			for(i = 0;i < 20;i++)
				MyBltFast(i*32,j*32,lpDDSOff_Text,352+(((TitleCnt02>>2)%7)*32),352,384+(((TitleCnt02>>2)%7)*32),384);	//神経
		MyBlt(140-(MojiZoom>>1),100-(MojiZoom>>1),140+352+(MojiZoom>>1),100+64+(MojiZoom>>1),lpDDSOff_Text,0,416,352,480);		//Title
	}else
	{	
		//タイトル
		for(j = 0;j < 2;j++)
			for(i = 0;i < 11;i++)
				MyBltFast(140+(i*32),100+(j*32),lpDDSOff_Text,352+(((TitleCnt02>>2)%7)*32),352,384+(((TitleCnt02>>2)%7)*32),384);	//神経
		MyBltFast(140,100,lpDDSOff_Text,0,352,352,416);	//タイトル文字
	}
	if(TitleCnt02 < 540)
	{
		//プレイヤー画像移動
		MyBltFast(50,270+(540-TitleCnt02),lpDDSOff_Title,176,0,352,272);//Player
		MyBltFast(430,150-(540-TitleCnt02),lpDDSOff_Title,0,272,160,352);//Sword_Down
		MyBltFast(430+45,150-96-(540-TitleCnt02),lpDDSOff_Title,64,352,127,448);//Sword_Up
	}else
	{
		//プレイヤー画像
		MyBltFast(50,270,lpDDSOff_Title,0,0,176,272);		//Player
		MyBltFast(430,150,lpDDSOff_Title,0,272,160,352);	//Sword_Down
		MyBltFast(430+45,150-96,lpDDSOff_Title,0,352,64,448);//Sword_Up

		//NewGame文字
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option文字
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}



	TBGC_time ++;	//カウント
	if(TBGC_time > (7-(rand()%4)) )	//カウントが一定の時間を超えるとタイトル背景色を変更
	{
		TitleBGClr = (rand()%5)+6;
		TBGC_time = 0;
	}


	//描画
	if(rand()%5 == 1)
	{
		//しみを表示
		MyBltFast(	140,200,	//表示先XY座標
				lpDDSOff_Text,	//表示する絵のオフスクリーンサーフェース
				128,	24,		//転送元左上XY座標
				136,	32);	//転送元右下XY座標
		MyBltFast( 400,320,
				lpDDSOff_Text,
				128,	32,
				136,	40);
		MyBltFast(580,20,
				lpDDSOff_Text,
				128,	40,
				136,	48);
		MyBltFast(210,87,
				lpDDSOff_Text,
				128,	48,
				136,	64);
	}
	for(i = 0;i < 10;i++)
	{
		MyBltFast(rand()%640,rand()%480,
					lpDDSOff_Text,
					128,	32,
					129,	33);
	}		

	//描画を行うサーフェースのデバイスコンテキストを取得
	lpDDSBackBuffer->GetDC(&hdc);


	//プレイヤーの攻撃当たり判定の範囲を表す線の設定
	hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));	//点線、太さ１,緑色のペンを作成し、hPenに保存
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。
	
	for(i = 0;i < 8;i++)
	{
		//プレイヤーの攻撃範囲を表す四角を描画
		if(rand()%7 == 1)	//プレイヤー攻撃中の当たり判定部分を表示
		{
			rndLX = rand()%640;
		
			if(rand()%2 == 1)
			{
				MoveToEx(hdc,rndLX,0,NULL);
				LineTo(hdc,rndLX,rand()%480);
			}else
			{
				MoveToEx(hdc,rndLX,rand()%480,NULL);
				LineTo(hdc,rndLX,480);
			}
		}
	}

	LineX += (rand()%4)-1;
	if(LineX < 0) LineX = rand()%640;
	if(LineX > 640) LineX = rand()%640;

	LineY -= (rand()%4)-2;
	if(LineY < 0)	LineY = rand()%480;
	if(LineY > 480) LineY = rand()%480;

	if(rand()%30 == 1)	LineX = rand()%640;

	if(rand()%2 == 1)
	{
		for(i = 0;i < 2;i++)
		{
			MoveToEx(hdc,LineX+(i*40),0,NULL);
			LineTo(hdc,LineX+(i*40),rand()%480);

			MoveToEx(hdc,LineX+(i*40),rand()%480,NULL);
			LineTo(hdc,LineX+(i*40),480);
		}
	}

	SelectObject(hdc,hPenOld);		//ペンを元に戻す
	DeleteObject(hPen);				//作成したペンの削除

	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);
}