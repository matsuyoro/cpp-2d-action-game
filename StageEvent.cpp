#include "Extern.h"

#include "GameCheckProc.h"

///////////// プロトタイプ宣言 ////////////////////////
void SEvent_0();	//ステージ０のイベント関数のプロトタイプ宣言
void SEvent_1();	//ステージ１のイベント関数のプロトタイプ宣言
void SEvent_2();	//ステージ２のイベント関数のプロトタイプ宣言
void SEvent_3();	//ステージ３のイベント関数のプロトタイプ宣言
void SEvent_4();	//ステージ４のイベント関数のプロトタイプ宣言

//■　StageEvent　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void StageEvent()	//	機能：各ステージのイベントを扱う関数
//	●引数：ステージ
{
	void (*pSEv[5])();	//戻値なし、引数なしの関数のポインタ配列の宣言
	pSEv[0] = SEvent_0;	//pSEv[0]に定義関数SEvent_0の先頭アドレスを代入
	pSEv[1] = SEvent_1;
	pSEv[2] = SEvent_2;
	pSEv[3] = SEvent_3;
	pSEv[4] = SEvent_4;

	//▼StageNumの値のステージイベント処理を行う
	pSEv[StageNum]();	//関数のポインタ配列の要素番号（StageNum）に対応した関数を実行
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//===============================================================================================
void SEvent_0()			//機能：森のステージ
{
	int i,j;
	static BOOL BossChk;	//ボスが出現したかチェック
	static int BossDCnt;	//ボスが死ぬときのカウント
	


	//▼葉っぱをちらす
	if(rand()%5 == 1)	
		ShotFire(640,rand()%480,0,10,10);	//存在の種類を１０して当たり判定を行わない
	
	//■ボスの領域に入ったら戻れなくする。
	if(WMoveX > (279<<5))
	{
		if(WMoveX < (279<<5)+30 && WorldX < 0)
				WorldX = 0;
	}

	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Type == 3 && En[i].Son)
		{
			for(j = 0;j < OBJ_MAX;j++)
			{
				if(Obj[j].Type == 0 && En[i].AniType != 1)
				{
					//ボスのX移動量を制限
					if(Obj[j].x-400 > En[i].x)
						En[i].x = Obj[j].x-400;
					//ボスのY移動量を制限
					if(Obj[j].y-300 > En[i].y)
						En[i].y = Obj[j].y-300;
					if(Obj[j].y+300 < En[i].y)
						En[i].y = Obj[j].y+300;
				}
			}
		}
	}

	if(!BossChk)	//ボスの出現チェック
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 3 && En[i].Son)
			{
				BossChk = TRUE;	//ボス出現チェック
				En[i].Hp -= 250;
			}
		}
	}else	//ボスが死んだら
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 3 && !En[i].Son)
			{
				for(j = 0;j < 30;j++)
				{
					ShotFire(En[i].x+(rand()%En[i].w),En[i].y+(rand()%En[i].h),0,28,1);	//弾の発射
					BossChk = FALSE;
					BossDCnt = 1;	//ボスのダウンカウント（ホワイトアウト
				}
			}
		}
	}
	if(BossDCnt > 0)	//ボスの死んだときのカウント
	{
		BossDCnt ++;
	
		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < 255)
				SubPal[i].peRed ++;	//赤の要素を減らす			
			if(SubPal[i].peGreen < 255)
				SubPal[i].peGreen ++;	//緑の要素をへらす
			if(SubPal[i].peBlue < 255)
				SubPal[i].peBlue ++;		//青の要素を減らす
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(BossDCnt > 300)
		{
			GameNum = 4;
			BossDCnt = 0;
			lpDDPal->SetEntries(0,0,255,MainPal);	//パレットを元に戻す
		}
	}
}

//=================================================================================================
void SEvent_1()			//機能：廃墟のステージ
{
	int i,j;
	static BOOL BossChk;	//ボスが出現したかチェック
	static int BossDCnt;	//ボスが死ぬときのカウント

	//○全体的に少しだけ灰を表示
	ShotFire(rand()%640,rand()%240+240,0,24,10);	//灰発射

	/*
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son && (BgObj[i].Type == 23 || BgObj[i].Type == 24))
		{
			for(j = 0;j < 3;j++)
				ShotFire(BgObj[i].x+(rand()%10),470+(rand()%10),0,24,10);
		}
	}*/

	//■ボスの領域に入ったら戻れなくする。
	if(WMoveX > (503<<5))
	{
		if(WMoveX < (503<<5)+30 && WorldX < 0)
				WorldX = 0;
	}

	if(!BossChk)	//ボスの出現チェック
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 8 && En[i].Son)
			{
				BossChk = TRUE;	//ボス出現チェック
				En[i].Hp = (En[i].MaxHp>>3);
			}
		}
	}else	//ボスが死んだら
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 8 && !En[i].Son)
			{
				for(j = 0;j < 30;j++)
				{
					ShotFire(En[i].x+(rand()%En[i].w),En[i].y+(rand()%En[i].h),0,28,1);	//弾の発射
					BossChk = FALSE;
					BossDCnt = 1;	//ボスのダウンカウント（ホワイトアウト
				}
			}
		}
	}
	if(BossDCnt > 0)	//ボスの死んだときのカウント
	{
		BossDCnt ++;
	
		lpDDPal->GetEntries(0,0,255,SubPal);
		//取得したパレットデータの、赤、緑、青の要素
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < 255)
				SubPal[i].peRed ++;	//赤の要素を減らす			
			if(SubPal[i].peGreen < 255)
				SubPal[i].peGreen ++;	//緑の要素をへらす
			if(SubPal[i].peBlue < 255)
				SubPal[i].peBlue ++;		//青の要素を減らす
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(BossDCnt > 300)
		{
			GameNum = 4;
			BossDCnt = 0;
			lpDDPal->SetEntries(0,0,255,MainPal);	//パレットを元に戻す
		}
	}
}
//=================================================================================================
void SEvent_2()			//機能：砂漠基地のステージ
{

}
//===============================================================================================
void SEvent_3()			//機能：嵐のステージ
{

}
//=================================================================================================
void SEvent_4()			//機能：メカのステージ
{

}
