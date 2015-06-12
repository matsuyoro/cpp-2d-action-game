#include <windows.h>	//ウィンドウズのヘッダ

#include "Extern.h"		//外部変数のヘッダ
#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "DirectSound.h"

#include "GameCheckProc.h"	//判定関数などのプロトタイプ宣言のヘッダ
//-----------------------------------------------------
void Enemy_1(CHR_DATA*,ANIME_DATA*);	//エネミー１を扱う関数のプロトタイプ宣言
void Enemy_2(CHR_DATA*,ANIME_DATA*);
void Enemy_3(CHR_DATA*,ANIME_DATA*);	//竜
void Enemy_4(CHR_DATA*,ANIME_DATA*);	//
void Enemy_5(CHR_DATA*,ANIME_DATA*);	//兵
void Enemy_6(CHR_DATA*,ANIME_DATA*);	//炎
void Enemy_7(CHR_DATA*,ANIME_DATA*);	//根っこ
void Enemy_8(CHR_DATA*,ANIME_DATA*);	//鉄犬
void Enemy_9(CHR_DATA*,ANIME_DATA*);	//小動物
void Enemy_10(CHR_DATA*,ANIME_DATA*);	//蜂
void Enemy_11(CHR_DATA*,ANIME_DATA*);	//ツボ
void Enemy_12(CHR_DATA*,ANIME_DATA*);	//骨口
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void EnAction()		//機能：エネミーアクション関数
{
	int i;	//カウンタ
	void (*pEneAct[13])(CHR_DATA*,ANIME_DATA*);	//戻値なし、の、関数のポインタ配列の宣言

	//pEneAct[0]は使わない
	pEneAct[1] = Enemy_1;	//エネミー１の関数を関数のポインタ配列で扱う
	pEneAct[2] = Enemy_2;	//
	pEneAct[3] = Enemy_3;	//
	pEneAct[4] = Enemy_4;	//
	pEneAct[5] = Enemy_5;
	pEneAct[6] = Enemy_6;
	pEneAct[7] = Enemy_7;	//根っこ
	pEneAct[8] = Enemy_8;	//鉄犬
	pEneAct[9] = Enemy_9;	//小動物
	pEneAct[10] = Enemy_10;	//蜂
	pEneAct[11] = Enemy_11;	//ツボ
	pEneAct[12] = Enemy_12;	//骨口

	for(i = 0;i < ENE_MAX;i++)	//エネミーの最大数分繰り返す
	if(En[i].Son)					//エネミーが存在したら
	{
		if(	//適が画面内にいたらアクションを起こす
		(	(En[i].x+En[i].w+WMoveX > WMoveX && En[i].x+WMoveX < WMoveX+640)
		&&	(En[i].y+En[i].h+WMoveY > WMoveY && En[i].y+WMoveY < WMoveY+480)	)
		|| En[i].HitD	//or適が攻撃を受けるアクションは常に
		)
		{
			pEneAct[En[i].Type](&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum]);	//関数のポインタ配列の要素番号（GameNum）に対応した関数を実行
			if(En[i].Cnt > 0) En[i].Cnt--;		//カウント時間がセットされていたら毎回マイナス１
			//次のこの関数を実行するときに必要なデータを保存
			En[i].OldAniType = En[i].AniType;	//前回のアニメーションの種類を保存
		}
	}
}
//------------------------------▼エネミーアクション関数▼------------------------------------------
//////（犬）//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_1 (CHR_DATA *pC,ANIME_DATA *pA)	//機能：エネミー１の行動をまとめた関数
//●引数１：エネミーのキャラデータ
//●引数２：エネミーのアニメーションデータ
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う

		if(pC->ActNum == 0 || pC->ActNum == 1)	//右移動か左移動なら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//プレイヤーの座標を元に移動方向を変える
				pC->ActNum = 0;							//左移動のアクション
			else
				pC->ActNum = 1;							//右移動のアクション
		}
		if(pC->ActNum == 3 || pC->ActNum == 4)
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//Plrの座標を元にジャンプする方向を決める
				pC->ActNum = 4;							//左ジャンプのアクション
			else
				pC->ActNum = 3;							//右ジャンプのアクション
		}
	}
	if(pC->HitD)	//ダメージをうけたら
	{
		pC->ActNum = 5;	
	}



	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○左アタック
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション0（移動			
				if(pC->OldAniType != 1)	//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 50;		//この行動をする時間
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 3;				//ループして戻る絵
			}
			if(pC->AniNum > 2)	pC->x -= 7;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}
		break;
	case 1:	//○右アタック
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション0（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が0なら
				{
					pC->Cnt = 50;	//この行動をする時間
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 3;				//ループして戻る絵
			}
			if(pC->AniNum > 2)	pC->x += 7;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、左を向かせる
		}
		break;
	case 2:	//○待機
		if(pC->Land == 1 && pA->Change || (pC->Land == 1 && pC->OldAniType == 2))//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)			//前回のアニメが０以外なら
			{
				pC->Cnt = 20;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//ループして戻る絵
		}
		break;
	case 3:	//○右ジャンプ
		if(pA->Change && pC->Land == 1)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//ジャンプUPアニメーション
			if(pC->OldAniType == 0)				//地面に足が着いているか判定
			{
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
				pC->U = -15;				//落下する速度を扱うUを15.0にする
			}
			pC->AniTurn = 3;		//アニメーションしてもどる絵
		
			pC->muki = 1;			//右に向く
		}
		if(!pC->Land && pC->AniType == 2)
		{
			pC->Cnt = 2;	//浮いている間はCntを２にして、アクション変更できなくする（１だとー１されて０になるのでダメ
			pC->x += 6;		//右に移動
		}
		break;
	case 4:	//○左ジャンプ
		if(pA->Change && pC->Land == 1)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//ジャンプUPアニメーション
			if(pC->OldAniType == 0)				//地面に足が着いているか判定
			{
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
				pC->U = -15;				//落下する速度を扱うUを15.0にする
			}
			pC->AniTurn = 3;		//アニメーションしてもどる絵
			pC->muki = 0;			//左に向く
		}
		if(!pC->Land && pC->AniType == 2)	
		{
			pC->Cnt = 2;	//浮いている間はCntを２にして、アクション変更できなくする（１だとー１されて０になるのでダメ
			pC->x -= 6;		//左に移動
		}
		break;
	case 5:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 20;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -8;
		}
		if(pC->muki)	pC->x -=5;	//右向きなら左に飛ぶ
		else			pC->x +=5;	//左向きなら右に飛ぶ
		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;
	}
}
////（トカゲ）//////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_2(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		
		if(pC->ActNum == 1 || pC->ActNum == 2)	//右移動か左移動なら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->ActNum = 1;		//左移動のアクション
			else
				pC->ActNum = 2;		//右の移動のアクション
		}
	}
	if(pC->HitD)	//ダメージフラグがTRUEなら
	{
		pC->ActNum = 4;
	}




	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change && pC->Land == 1)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//ループして戻る絵
		}
		break;
	case 1:	//○左移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 22;		//この行動をする時間を設定
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 1;				//ループして戻る絵
			}
			pC->x -= 2;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}
		break;
	case 2:	//○右移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 22;
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 1;				//ループして戻る絵
			}
			pC->x += 2;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、右を向かせる
		}
		break;
	case 3:	//○火炎放射（近距離
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//かみつきアニメーション
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 36;			//このアクションを行う時間を設定
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;		//アニメーションしてもどる絵
		}
		if(pC->Cnt > 3 && pC->Cnt < 29)	//３９～３までの間火炎放射
		{
			if(pC->muki == 0)	//左向きなら
			{
				ShotFire(pC->x,pC->y+30,0,18,1);			//弾の発射
				DS_Play(6,FALSE);	//効果音を鳴らす
			}else				//左向きじゃないなら
			{
				ShotFire(pC->x+pC->w-48,pC->y+30,1,18,1);	//弾発射
				DS_Play(6,FALSE);
			}
		}
		break;
	case 4:	//○ダメージ
		pC->AniType = 4;
		if(pC->OldAniType != 4)
		{
			pC->Cnt = 15;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//右向きなら左に飛ぶ
		else			pC->x +=2;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;
	}
}
//////（竜）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_3(CHR_DATA *pC,ANIME_DATA *pA)
{
	int i,j;
	int AX,BX;			//ボス１の首X座標を扱う
	int	AY,BY;			//ボス１の首Y座標を扱う
	int NeckNum = 0;	//首の数を扱う

	static int ATPosX,ATPosY;	//噛み付きの突進座標を保存しておく変数

	for(i = 0;i < OBJ_MAX;i++)	//ボス１体のオブジェを探す
	{
		if(Obj[i].Son && Obj[i].Type == 0)	//ボス１体のオブジェが存在したら
		{
			NeckNum = 1;	//首の並び順を扱う

			AX = pC->x + (pC->w>>1);		//顔のX座標を扱う
			BX = Obj[i].x + (Obj[i].w>>1);	//体のX座標を扱う
			AY = pC->y + (pC->h>>1);		//顔のY座標を扱う
			BY = Obj[i].y + (Obj[i].h>>1);	//体のY座標を扱う

			for(j = 0;j < OBJ_MAX;j++)	//ボス１首のオブジェを探す
			{
				if(Obj[j].Son && (Obj[j].Type == 2 || Obj[j].Type == 3 || Obj[j].Type == 4))	//ボス１首間接のオブジェが存在したら
				{
					Obj[j].x = BX + (((AX - BX)/10)*NeckNum) - (Obj[j].w>>1);	//首オブジェのX座標を計算
					Obj[j].y = BY + (((AY - BY)/10)*NeckNum) - (Obj[j].h>>1);	//首オブジェのY座標を計算
					NeckNum++;	//次の首のオブジェで使うNeckNumを＋＋
					if(NeckNum > 10)		//首を5個表示したら
					{
						NeckNum = 1;	//１に戻す
						break;			//ループをぬける
					}
				}
			}
		}				
	}

	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う

		//プレイヤーが離れると火の玉を出す
		if((pC->x+(pC->w>>1)-300 > Plr.x+(Plr.w>>1) 
		|| pC->x+(pC->w>>1)+300 < Plr.x+(Plr.w>>1))
		&& rand()%2 == 1						  )
			pC->ActNum = 2;

		if(pC->ActNum == 0 || pC->ActNum == 2  || pC->ActNum == 3)	//通常状態なら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//プレイヤーが左側にいたら
			{
				pC->x -= 3;
				pC->muki = 0;
			}else
			{
				pC->x += 3;
				pC->muki = 1;
			}

			if(Plr.y+(Plr.h>>1) < pC->y+(pC->h>>1))	//プレイヤーが上側にいたら
				pC->y -= 3;
			else
				pC->y += 3;
		}
	}

	if(pC->HitD)	//ダメージフラグがTRUEなら
		pC->ActNum = 4;

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//ループして戻る絵
		}
		break;
	case 1:	//○かみつき
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 1;		//かみつきアニメーション
			if(pC->OldAniType != 1)
			{
				ATPosX = pC->x+(pC->w>>1);	//突進座標を保存してここに顔が戻るように
				ATPosY = pC->y+(pC->h>>1);
				pC->Cnt = 65;
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;		//アニメーションしてもどる絵
		}
		if(pC->Cnt < 52 && pC->Cnt > 32)	//プレイヤーに向かっていく
		{
			if(Dum[1].x+(Dum[1].w>>1) < pC->x+(pC->w>>1))	//プレイヤーが左側にいたら
			{	pC->x -= 8;
				pC->muki = 0;
			}else
			{	pC->x += 8;
				pC->muki = 1;
			}

			if(Dum[1].y+(Dum[1].h>>1) < pC->y+(pC->h>>1))	//プレイヤーが上側にいたら
				pC->y -= 5;
			else
				pC->y += 5;
/*
			if(pC->AniNum == 5)	//炎を吐く
			{
				if(pC->muki == 0)	//左向きなら
					ShotFire(pC->x+20,pC->y+20,0,18,1);			//弾の発射
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,18,1);	//弾の発射
			}
*/
		}
		if(pC->Cnt <= 32)	//首を戻す
		{
			if(pC->x+(pC->w>>1) < ATPosX)	//プレイヤーが左側にいたら
			{
				pC->x += 4;
				pC->muki = 0;
			}else
			{
				pC->x += 4;
				pC->muki = 1;
			}

			if(pC->y+(pC->w>>1) < ATPosY)	//プレイヤーが上側にいたら
				pC->y += 3;
			else
				pC->y -= 3;
		}
		break;
	case 2:	//○火の玉
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//かみつきアニメーション
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;		//アニメーションしてもどる絵
		}
		if(pC->Cnt == 1)
		{
			if(pC->Hp <= pC->MaxHp>>2)	//エネミーのHPが4分１以下になったら
			{	
				if(pC->muki == 0)	//左向きなら
					ShotFire(pC->x+20,pC->y+20,0,26,1);	//弾の発射
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,26,1);	//弾の発射
			}else
			{
				if(pC->muki == 0)	//左向きなら
					ShotFire(pC->x+20,pC->y+20,0,3,1);	//弾の発射
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,3,1);	//弾の発射
			}
		}

		break;
	case 3:	//○火炎放射
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//かみつきアニメーション
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;		//アニメーションしてもどる絵
		}
		if(pC->Cnt < 10 && pC->Hp <= pC->MaxHp>>2)	//炎を吐く
		{
			if(pC->muki == 0)	//左向きなら
				ShotFire(pC->x+20,pC->y+20,0,18,1);			//弾の発射
			else
				ShotFire(pC->x+pC->w-20,pC->y+20,1,18,1);	//弾の発射
		}

		break;
	case 4:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 12;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//右向きなら左に飛ぶ
		else			pC->x +=2;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;

	}

}
//////（メカ兵）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_4(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		if(pC->ActNum == 3)	//発砲のアクションなら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//左を向く
			else
				pC->muki = 1;			//右を向く
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//右移動か左移動なら	
		{
			if(pC->x > 500 || pC->x < 140)			//エネミー３が画面の外側なら
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 1;	//左移動のアクション
				else
					pC->ActNum = 2;	//右の移動のアクション
			}else	//外側でないなら
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 2;	//左移動のアクション
				else
					pC->ActNum = 1;	//右の移動のアクション
			}
			
		}
	}
	if(pC->HitD)
		pC->ActNum = 4;	//ダメージアクション

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 5;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//○左移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 20;		//この行動をする時間を設定
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
			}
			pC->x -= 3;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}
		break;
	case 2:	//○右移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 20;
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
			}
			pC->x += 3;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、右を向かせる
		}
		break;
	case 3:	//○発砲
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;			//このアニメーションを行う時間
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
		}
		if(pC->Cnt == 7)	//のこりカウントが７なら
		{
			if(pC->muki == 0)	//左向きなら	
			{	
				ShotFire(pC->x,pC->y+30,0,5,1);	//弾の発射
				DS_Play( 4, FALSE );			//効果音を鳴らす
			}else				//左向きじゃないなら
			{
				ShotFire(pC->x+pC->w,pC->y+30,1,5,1);		//弾の発射
				DS_Play( 4, FALSE );			//効果音を鳴らす
			}
		}
		break;
	case 4:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 8;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=1;	//右向きなら左に飛ぶ
		else			pC->x +=1;	//左向きなら右に飛ぶ
		
		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}		
		break;

	}
}
//////（兵）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_5(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		if(pC->ActNum == 3)	//発砲のアクションなら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//左を向く
			else
				pC->muki = 1;			//右を向く
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//右移動か左移動なら	
		{
			if(pC->x > 520 || pC->x < 120)			//エネミー３が画面の外側なら
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 1;	//左移動のアクション
				else
					pC->ActNum = 2;	//右の移動のアクション
			}else	//外側でないなら
			{
					pC->ActNum = 0 ;	//待機アクション
			}
			
		}
	}
	if(pC->HitD)
		pC->ActNum = 4;	//ダメージアクション

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 5;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//○左移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 30;		//この行動をする時間を設定
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 0;
			}
			pC->x -= 4;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}
		break;
	case 2:	//○右移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 30;
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 4;
			}
			pC->x += 4;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、右を向かせる
		}
		break;
	case 3:	//○発砲
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 33;			//このアニメーションを行う時間
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
		}
		if(pC->Cnt == 3)	//のこり３の時に弾発射
		{
			if(pC->muki == 0)	//左向きなら
			{
				ShotFire(pC->x,pC->y+18,0,1,1);	//弾の発射
				DS_Play( 3, FALSE );			//効果音を鳴らす
			}else				//左向きじゃないなら
			{
				ShotFire(pC->x+pC->w,pC->y+18,1,1,1);		//弾の発射
				DS_Play( 3, FALSE );			//効果音を鳴らす
			}
		}
		break;
	case 4:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 8;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//右向きなら左に飛ぶ
		else			pC->x +=2;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;


	}
}
/////（火人間）/////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_6(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		if(pC->ActNum == 3)	//発砲のアクションなら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//左を向く
			else
				pC->muki = 1;			//右を向く
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//右移動か左移動なら	
		{

			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->ActNum = 1;	//左移動のアクション
			else
				pC->ActNum = 2;	//右の移動のアクション			
		}
	}
	if(rand()%2 == 1 && pC->Land == 1)	//地面に足が着いていて乱数が１なら
		ShotFire(pC->x+(rand()%32),pC->y+pC->h-32+(rand()%6),0,7,1);	//弾の発射（地面に配置する弾
	if(pC->HitD)	//ダメージフラグがTRUEなら
		pC->ActNum = 4;	//ダメージアクション


	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 20;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//○左移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 50;		//この行動をする時間を設定
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 0;
			}
			pC->x -= 2;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}

		break;
	case 2:	//○右移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション1（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 50;
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 4;
			}
			pC->x += 2;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、右を向かせる
		}

		break;
	case 3:	//○発砲
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 50;			//このアクションを５０フレーム
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;
		}
		if(pC->muki == 0)	//左向きなら	
		{
			ShotFire(pC->x+(pC->w>>1)-24,pC->y,0,6,1);	//弾の発射
			DS_Play(6,FALSE);	//効果音を鳴らす
		}else				//左向きじゃないなら
		{
			ShotFire(pC->x+(pC->w>>1)-24,pC->y,1,6,1);		//弾の発射
			DS_Play(5,FALSE);	//効果音を鳴らす
		}
		break;
	case 4:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 10;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//右向きなら左に飛ぶ
		else			pC->x +=2;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;

		
	}
}
////（枝）//////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_7(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		
		if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
			pC->muki = 1;		//向きをプレイヤーの方向に
		else
			pC->muki = 0;		//

		if(Plr.x+(Plr.w>>1) > pC->x+(pC->w>>1)-32
		&& Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1)+32)
		{
			pC->ActNum = 1;
		}
	}
	if(pC->HitD)	//攻撃を受けたら
		pC->ActNum = 2;	//ダメージアクション

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change && pC->Land == 1)//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//ループして戻る絵
		}
		break;
	case 1:	//○攻撃
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 1;		//攻撃アニメーション
			if(pC->OldAniType != 1)
			{
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;		//アニメーションしてもどる絵
		}
		break;
	case 2:	//○ダメージ
		pC->AniType = 2;
		if(pC->OldAniType != 2)
		{
			pC->Cnt = 5;		//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;

	}
}
//////（鉄犬）//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_8 (CHR_DATA *pC,ANIME_DATA *pA)	//機能：エネミー８の行動をまとめた関数
//●引数１：エネミーのキャラデータ
//●引数２：エネミーのアニメーションデータ
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%5];	//敵の行動をまずはランダムで扱う

		if(pC->ActNum == 2 || pC->ActNum == 1)	//右移動か左移動なら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//プレイヤーの座標を元に移動方向を変える
				pC->ActNum = 2;							//左移動のアクション
			else
				pC->ActNum = 1;							//右移動のアクション
		}
		if(pC->ActNum == 3 || pC->ActNum == 4)
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//Plrの座標を元にジャンプする方向を決める
				pC->ActNum = 4;							//左ジャンプのアクション
			else
				pC->ActNum = 3;							//右ジャンプのアクション
		}
	}
	if(pC->HitD)	//ダメージをうけたら
	{
		pC->ActNum = 5;	
	}



	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pC->Land == 1 && pA->Change || (pC->Land == 1 && pC->OldAniType == 2))//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;				//アニメーション０
			if(pC->OldAniType != 0)			//前回のアニメが０以外なら
			{
				pC->Cnt = 50;
				pC->AniNum = 0;					//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//ループして戻る絵
		}
		break;
	
	case 1:	//○右アタック
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション0（移動			
				if(pC->OldAniType != 1)		//前回のアニメーションの種類が0なら
				{
					pC->Cnt = 50;			//この行動をする時間
					pC->AniNum = 0;			//アニメーションの最初から
					pC->AniTimeNow = 0;		//カウンタを０に
				}
				pC->AniTurn = 3;		//ループして戻る絵
			}
			if(pC->AniNum > 2)	pC->x += 7;					//キャラを左に移動
			pC->muki = 1;			//向きを１にして、左を向かせる
		}
		break;

	case 2:	//○左アタック
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 1;		//アニメーション0（移動			
				if(pC->OldAniType != 1)	//前回のアニメーションの種類が１以外なら
				{
					pC->Cnt = 50;		//この行動をする時間
					pC->AniNum = 0;		//アニメーションの最初から
					pC->AniTimeNow = 0;	//カウンタを０に
				}
				pC->AniTurn = 3;				//ループして戻る絵
			}
			if(pC->AniNum > 2)	pC->x -= 7;					//キャラを左に移動
			pC->muki = 0;			//向きを１にして、左を向かせる
		}
		break;

	case 3:	//○右ジャンプ
		if(pA->Change && pC->Land == 1)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;			//ジャンプUPアニメーション
			if(pC->OldAniType == 0)		//地面に足が着いているか判定
			{
				pC->AniNum = 0;				//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;			//アニメーションの時間カウントを０にする
				pC->U = -15;				//落下する速度を扱うUを15.0にする
			}
			pC->AniTurn = 3;			//アニメーションしてもどる絵
		
			pC->muki = 1;			//右に向く
		}
		if(!pC->Land && pC->AniType == 2)
		{
			pC->Cnt = 2;	//浮いている間はCntを２にして、アクション変更できなくする（１だとー１されて０になるのでダメ
			pC->x += 6;		//右に移動
		}

		break;
	case 4:	//○左ジャンプ
		if(pA->Change && pC->Land == 1)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;		//ジャンプUPアニメーション
			if(pC->OldAniType == 0)				//地面に足が着いているか判定
			{
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
				pC->U = -15;				//落下する速度を扱うUを15.0にする
			}
			pC->AniTurn = 3;		//アニメーションしてもどる絵
			pC->muki = 0;			//左に向く
		}
		if(!pC->Land && pC->AniType == 2)	
		{
			pC->Cnt = 2;	//浮いている間はCntを２にして、アクション変更できなくする（１だとー１されて０になるのでダメ
			pC->x -= 6;		//左に移動
		}

		break;

	case 5:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 15;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->muki)	pC->x -=3;	//右向きなら左に飛ぶ
		else			pC->x +=3;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;

	case 6:	//○発砲
		if(pA->Change && pC->Land == 1 )	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 4;
			if(pC->OldAniType != 4)
			{
				pC->Cnt = 40;			//このアクションを５０フレーム
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
			pC->AniTurn = 0;
		}
		if(pC->Cnt == 15)
		{
			if(pC->muki == 0)	//左向きなら	
			{
				ShotFire(pC->x+(pC->w>>1)-16,pC->y+32,0,20,1);	//弾の発射
				DS_Play(6,FALSE);	//効果音を鳴らす
			}else				//左向きじゃないなら
			{
				ShotFire(pC->x+(pC->w>>1)-16,pC->y+32,1,20,1);		//弾の発射
				DS_Play(5,FALSE);	//効果音を鳴らす
			}
		}
		break;
	}
}
//////（小動物）//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_9 (CHR_DATA *pC,ANIME_DATA *pA)	//機能：エネミー９の行動をまとめた関数
//●引数１：エネミーのキャラデータ
//●引数２：エネミーのアニメーションデータ
{
	int i;

	if(pC->HitD)	//ダメージをうけたら
	{
		pC->ActNum = 1;	
	}else
	{
		pC->ActNum = 0;	//通常どうり移動アクション
	}


	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			if(pC->Land == 1)	//地面に足が着いているなら
			{
				pC->AniType = 0;		//アニメーション0（移動			
				pC->AniTurn = 0;		//ループして戻る絵
			}

			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//プレイヤーの座標を元に移動方向を変える
				pC->muki = 0;	
			else
				pC->muki = 1;

			if(pC->muki)
				pC->x += 3;				//右に移動
			else
				pC->x -= 3;				//左に移動
		}
		break;
	case 1:	//○ダメージ＆攻撃
		pC->AniType = 1;
		if(pC->OldAniType != 1)
		{
			pC->Cnt = 35;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->Cnt == 0)	
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
			for(i = 0;i < 6;i++)
				ShotFire(pC->x+(pC->w>>1)-6,pC->y+12,0,21,1);	//弾の発射
			DS_Play(6,FALSE);	//効果音を鳴らす
		}
		break;
	}
}
//////（蜂）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_10(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
		if(pC->ActNum == 0)	//発砲のアクションなら
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//左を向く
			else
				pC->muki = 1;			//右を向く
		}

	}
	if(pC->HitD)
		pC->ActNum = 2;	//ダメージアクション

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○移動
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;		//アニメーション1（移動			
			if(pC->OldAniType != 0)		//前回のアニメーションの種類が１以外なら
			{
				pC->Cnt = 50;		//この行動をする時間を設定
				pC->AniNum = 0;		//アニメーションの最初から
				pC->AniTimeNow = 0;	//カウンタを０に
			}
			pC->AniTurn = 0;

			if(pC->muki)	pC->x += 4;		//キャラを移動
			else			pC->x -= 4;					

		}
		break;
	case 1:	//○攻撃
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 1;
			if(pC->OldAniType != 1)
			{
				pC->Cnt = 25;			//このアクションの行動時間
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
		}
		if(pC->Cnt == 5)	//このアクションのカウント時間がのこり５の時なら
		{
			if(pC->muki == 0)	//左向きなら
			{
				ShotFire(pC->x+(pC->w>>1),pC->y+60,0,22,1);	//弾の発射
				DS_Play( 3, FALSE );			//効果音を鳴らす
			}else				//左向きじゃないなら
			{
				ShotFire(pC->x+(pC->w>>1),pC->y+60,1,22,1);		//弾の発射
				DS_Play( 3, FALSE );			//効果音を鳴らす
			}
		}
		break;
	case 2:	//○ダメージ
		pC->AniType = 2;
		if(pC->OldAniType != 2)
		{
			pC->Cnt = 30;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->muki)	pC->x -=2;	//右向きなら左に飛ぶ
		else			pC->x +=2;	//左向きなら右に飛ぶ

		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;


	}
}
//////（ツボ）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_11(CHR_DATA *pC,ANIME_DATA *pA)
{
	pC->muki = 0;	//ツボは常に向きを一定に
	pC->Hp = 5 - pC->AniType;	//ツボはHP制じゃなく、攻撃した回数で壊す
	
	if(pC->Cnt == 0)	//アクションカウント時間が０なら
	{
		if(pC->HitD)	//ダメージフラグがTRUEなら
		{
			pC->AniType++;	//アニメーションを変更(ダメージを受けるごとに変化
			pC->Cnt = 20;	//２０カウントの間は判定を行わない
		}
	}
	if(pC->AniType > 4)	//最後の種類のアニメが終わったら
	{
		pC->Hp = 0;
		pC->Son = FALSE;	//ツボ消滅
		for(int i = 0;i < 20;i++)	//エフェクト表示
			EFON(EF,pC->x+(rand()%pC->w),pC->y+(rand()%pC->h),12);

		switch(rand()%3)	//ランダムで剣の破片がHPUPが出現
		{
		case 0:
			for(i = 0;i < 50 ;i++)	//死ぬエネミーの種類のMAXHPの数だけ魂を出現させる
				ShotFire(pC->x+(rand()%pC->w)-4,pC->y+(rand()%pC->h)-4,0,17,1);
			break;
		case 1:
			for (i = 0;i < 50 ;i++)	//剣の破片を出現
				ShotFire(pC->x+(rand()%pC->w)-4,pC->y+(rand()%pC->h)-4,0,19,2);
			break;
		case 2:
			if(pC->Land == 1)
				for(i = 0;i < 6;i++)
					ShotFire(pC->x+(rand()%pC->w)-16,pC->y+pC->h-32,0,7,1);
			break;
		}

	}
	pC->HitD = 0;	//ダメージフラグをFALSEに
}
//////（骨口）////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_12(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//カウント時間が０なら
	{
		pC->ActNum = pC->Act[rand()%4];	//敵の行動をまずはランダムで扱う
	}
	if(pC->HitD)
		pC->ActNum = 3;	//ダメージアクション

	switch(pC->ActNum)	//ActNumを元に条件分岐	
	{
	case 0:	//○待機
		if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
		{
			pC->AniType = 0;		//アニメーション1（移動			
			if(pC->OldAniType != 0)		//前回のアニメーションの種類が１以外なら
			{
				pC->Cnt = 40;		//この行動をする時間を設定
				pC->AniNum = 0;		//アニメーションの最初から
				pC->AniTimeNow = 0;	//カウンタを０に
			}
			pC->AniTurn = 0;
		}
		break;
	case 1:	//○噛む
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 1;
			if(pC->OldAniType != 1)
			{
				pC->Cnt = 14;			//このアクションの行動時間
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
		}
		break;
	case 2:	//○吐く
		if(pA->Change)	//現在実行中のアニメが変更可能か		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;			//このアクションの行動時間
				pC->AniNum = 0;			//アニメーションの０コマ目にする
				pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
			}
		}
		if(pC->Cnt == 10)
		{
			for(int i = 0;i < 3;i++)
				ShotFire(pC->x+(pC->w>>1),pC->y+60+(i<<2),0,23,1);	//弾の発射
			DS_Play( 3, FALSE );			//効果音を鳴らす
		}
		break;
	case 3:	//○ダメージ
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 30;	//ダメージアクション時間
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->Cnt == 0)	//ダメージアニメ終了時なら
		{
			pC->HitD = 0;		//ダメージフラグを０に
			pC->AniType = 0;	//終了後に変えるアニメを指定
		}
		break;
	}
}