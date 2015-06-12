#include <windows.h>

#include "GameStruct.h"
#include "Extern.h"
#include "DirectSound.h"

#include "GameCheckProc.h"
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void PlrAction(CHR_DATA *pC,ANIME_DATA *pA)		//機能：キャラクターを動かす関数
//●引数１：CHR_DATA型構造体
//●引数２：ANIME_DATA型構造体（現在表示中のアニメが変更可能か調べるの必要
{
	int i;

	//■待機
	if(CmdNum[0] == 0 && Btn1 == 0)			//●何も押してない場合
	{
		if(pA->Change && pC->Land == 1 && pC->OldAniType != 0)//現在の絵が、他のアニメーションに変更可能か判定 && このアニメーションに切り替わったばかりなら
		{
			pC->AniType = 0;				//アニメーション０
			pC->AniNum = 0;					//アニメーションの最初から
			pC->AniTimeNow = 0;
			pC->AniTurn = 0;				//ループして戻る絵
		}
	}

	if((!Swd.Son || Swd.HitA || Nage))	//剣がなく、刺さってなく、剣をなげてなたったら（剣が出現している時はジャンプ、攻撃、移動の動作をできなくする）
	{
		//■しゃがみ攻撃終了後
		if((pC->OldAniType == 10 && pC->AniType != 10)
		|| (pC->OldAniType == 11 && pC->AniType != 11)	//前回のアニメがしゃがみ攻撃だったら			
		|| (pC->OldAniType == 17 && pC->AniType != 17)	//前回のアニメがしゃがみ剣投げだったら
		)	
		{
			pC->AniType = 3;			//しゃがみのアニメに戻す
			pC->AniNum = 9;				//９コマ目から始まる
			pC->AniTimeNow = 0;			//アニメ表示カウントを０に
			pC->AniTurn = 9;			//ループして戻る絵９
		}else if(CmdNum[0] == 8 || CmdNum[0] == 9 || CmdNum[0] == 12)	//■しゃがみ	//十字キーの下が押されたら
		//■しゃがみ	//十字キーの下が押されたら
		{	
			if(pA->Change && pC->Land == 1)//現在の絵が、他のアニメーションに変更可能か　＆ 着地しているか判定
			{
				pC->AniType = 3;		//アニメーション３（しゃがみ
				if(CmdCnt[0] == 1)		//十字キーの下を押したばかりなら
				{
					pC->AniNum = 0;			//アニメーションの最初から
					pC->AniTimeNow = 0;		//カウント時間を０に
				}
				pC->AniTurn = 9;		//ループして戻る絵
			}
		}

		//■ジャンプ上昇
		if(CmdNum[0] == 2 || CmdNum[0] == 3 || CmdNum[0] == 6 )	//●左上、上、右上　が押されたら
		{
			if(pA->Change)	//現在実行中のアニメが変更可能か		
			{
				pC->AniType = 6;		//ジャンプUPアニメーション
				if(pC->Land == 1)				//地面に足が着いているか判定
				{
					pC->AniNum = 0;			//アニメーションの０コマ目にする
					pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
					pC->U = -15.0f;				//落下する速度を扱うUを15.0にする
					EFON(EF,pC->x+(pC->w>>1),pC->y+pC->h-18,7+(rand()%2));		//砂ぼこりをたてるエフェクト
					DS_Play(9,FALSE);	//効果音を鳴らす
				}
				pC->AniTurn = 7;		//アニメーションしてもどる絵
			}
		}
		//■ジャンプ上昇2
		if((CmdNum[1] == 8 || CmdNum[2] == 8) && (CmdNum[0] == 2 || CmdNum[0] == 3 || CmdNum[0] == 6) )	//●左上、上、右上　が押されたら
		{
			if(pA->Change)	//現在実行中のアニメが変更可能か		
			{
				pC->AniType = 6;		//ジャンプUPアニメーション
				if(pC->Land == 1)				//地面に足が着いているか判定
				{
					pC->AniNum = 0;			//アニメーションの０コマ目にする
					pC->AniTimeNow = 0;		//アニメーションの時間カウントを０にする
					pC->U = -23.0f;				//落下する速度を扱うUを15.0にする
					DS_Play(9,FALSE);	//効果音を鳴らす
					for(i = 0;i < 10;i++)
						EFON(EF,pC->x+(rand()%pC->w),pC->y+pC->h-18,7+(rand()%2));		//砂ぼこりをたてるエフェクト
				}
				pC->AniTurn = 7;		//アニメーションしてもどる絵
				

			}
		}
		//■左移動
		if(CmdNum[0] == 1 || CmdNum[0] == 3)	//十字キーの左か、左上を押したら		
		{		
			if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
			{
		//■ダッシュ
				//コマンドを入力したら(←・←）
				if((CmdNum[2] == 1 && CmdCnt[2] <= 10
					&& CmdNum[1] != 1 && CmdCnt[1] <= 10 
					&& (CmdNum[0] == 1 || CmdNum[0] == 3))	//←・←入力したら OR
				|| (pC->OldAniType == 2 && CmdNum[0] == 3))	//前回がダッシュアニメーションで左上を押したら
				{
					pC->AniType = 2;	//ダッシュアニメーション
					pC->AniTurn = 8;	//ループして戻るコマ
					if(pC->x > 200-(pC->w>>1))	//キャラX座標が200より大きければ
					{	
						pC->x -= 7;					//キャラを左に移動
					}else						//キャラX座標が200以下なら
					{
						if(!(WMoveX <= 0))			//左端までいったら何もしない
							WorldX = -7;					//WordlXを－１(Mapを右にスクロール
					}
					pC->muki = 1;			//向きを１にして、左を向かせる
				}else	//ダッシュのコマンドが入力されてなかったら
		//■歩く
				{
					if(pC->Land == 1)	//地面に足が着いているなら
					{
						pC->AniType = 1;		//アニメーション１（移動			
						if(CmdCnt[0] == 1)		//左を押し始めなら（ボタンを押して1フレーム目）
						{
							pC->AniNum = 0;		//アニメーションの最初から
							pC->AniTimeNow = 0;	//カウンタを０に
						}
						pC->AniTurn = 5;				//ループして戻る絵
					}
					if(pC->x > 200-(pC->w>>1))	//キャラX座標が200より大きければ
					{	
						pC->x -= 3;					//キャラを左に移動
					}else							//キャラX座標が200以下なら
					{
						if(!(WMoveX <= 0))			//左端までいったら何もしない
							WorldX = -3;					//WordlXを－１(Mapを右にスクロール
					}
					pC->muki = 1;			//向きを１にして、左を向かせる
				}
			}
		}
		//■右移動
		if(CmdNum[0] ==  4 || CmdNum[0] == 6 )				//十字キーの右か右上を押したら
		{
			if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
			{
		//■ダッシュ
				//コマンド入力したら（→・→）
				if(	((CmdNum[2] == 4 && CmdCnt[2] <= 10)
					&& (CmdNum[1] != 4 && CmdCnt[1] <= 10) 
					&& (CmdNum[0] == 4 || CmdNum[0] == 6))	//→・→入力したら　OR
				|| (pC->OldAniType == 2 && CmdNum[0] == 6))	//前回がダッシュアニメーションで右上を押したら
				{
					pC->AniType = 2;	//ダッシュアニメーション
					pC->AniTurn = 8;	//ループして戻すコマ
					if(pC->x < 400-(pC->w>>1))	//キャラがx座標400より小さければ
					{
						pC->x += 7;					//キャラx座標＋移動速度
					}else						//条件を満たしてなければ（キャラがx座標400以上なら
					{
						if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//右端までいったら何もしない
							WorldX = 7;					//スクロール量を設定
					}
					pC->muki = 0;			//向きを０にして、右を向かせる
				}else
		//■歩く
				{
					if(pC->Land == 1)	//地面に足が着いているなら
					{
						pC->AniType = 1;	//アニメーション１（移動
						if(CmdCnt[0] == 1)		//押し始めなら（右を押して1フレーム目なら
						{
							pC->AniNum = 0;		//アニメーションの最初から
							pC->AniTimeNow = 0;	//カウント時間を０に
						}
						pC->AniTurn = 5;		//ループして戻る絵
					}
					if(pC->x < 400-(pC->w>>1))	//キャラX座標が400より小さければ
					{
						pC->x += 3;					//キャラを右に移動
					}else
					{
						if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//右端までいったら何もしない
							WorldX = 3;				//WorldXを＋１
					}
					pC->muki = 0;			//向きを０にして、右を向かせる
				}
			}
		}

	}



	//■ジャンプ下降
	if(pA->Change && pC->Land == 0 && pC->U > 0. && pC->AniType!=2)	//地面に足が着いていない状態で、下降中で、AniTypeが２以外なら
	{
		pC->AniType = 7;	//ジャンプ下降アニメーション
		if(pC->OldAniType != 7)	//前回のアニメーションの種類がジャンプ下降じゃなかったら
		{
			pC->AniNum = 0;			//アニメーションを0コマ目に戻す
			pC->AniTimeNow = 0;		//アニメーション表示カウント時間を０に戻す
		}
		pC->AniTurn = 1;		//ループして戻るアニメーションの絵
	}

	if(!Swd.Son)	//剣が存在しないなら
	{
		//●横斬り（Ｂボタンを短く押す
		if(!(Btn1 & (1<<1)) && BtnCnt < 3 && (Btn2 & (1<<1)))	//今回(押)で、かつ前回(離)だったら
		{
			if(pC->AniType != 3)	//しゃがみアニメーション以外だったら
			{
				if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
				{
					pC->AniType = 4;				//アニメーション4
					pC->AniNum = 0;					//アニメーションの最初から
					pC->AniTimeNow = 0;				//カウント時間を０に
					pC->AniTurn = 0;				//ループして戻る絵
					DS_Play( 0, FALSE );			//効果音を鳴らす
				}
			}else
			{
				//●しゃがみ横斬り
				if(pA->Change)	//現在の絵が、他のアニメーションの変更可能か判定
				{
					pC->AniType = 11;		//しゃがみ横斬りアニメーション
					pC->AniNum = 0;
					pC->AniTimeNow = 0;
					pC->AniTurn = 0;
					DS_Play( 0, FALSE );	//効果音を鳴らす
				}
			}
		}
		
		//●縦斬り（Ｂボタンを長く押す
		if((Btn1 & (1<<1)) && BtnCnt >= 3)	//今回(押)で、かつ前回(離)だったら
		{	
			if(pC->AniType != 3)	//しゃがみアニメーション以外だったら
			{
				if(pA->Change)//現在の絵が、他のアニメーションに変更可能か判定
				{
					pC->AniType = 5;				//アニメーション5
					pC->AniNum = 0;					//アニメーションの最初から
					pC->AniTimeNow = 0;				//カウント時間を０に
					pC->AniTurn = 0;				//ループして戻る絵
					DS_Play( 1, FALSE );			//効果音を鳴らす
				}
			}else	//しゃがみアニメーション中だったら
			{
				//●しゃがみ縦斬り
				if(pA->Change)	//現在の絵が、他のアニメーションに変更可能か判定
				{
					pC->AniType = 10;		//しゃがみ斬りアニメーション
					pC->AniNum = 0;			//アニメーション最初から
					pC->AniTimeNow = 0;		//アニメーションカウントを０に
					pC->AniTurn = 0;		//ループして戻る絵
					DS_Play( 1, FALSE );			//効果音を鳴らす
				}
			}
		}
		//●ジャンプ縦攻撃
		if(pA->Change && !pC->Land)	//地面に足が着いていない状態で、下降中で、AniTypeが２以外なら
		{
			if((Btn1 & (1<<1)) && BtnCnt >= 3)	//今回(押)で、かつ前回(離)だったら
			{	
					pC->AniType = 12;				//アニメーション5
					pC->AniNum = 0;					//アニメーションの最初から
					pC->AniTimeNow = 0;				//カウント時間を０に
					pC->AniTurn = 0;				//ループして戻る絵
					DS_Play( 1, FALSE );			//効果音を鳴らす
			}
		}
		//●ジャンプ横攻撃
		if(pA->Change && !pC->Land)	//地面に足が着いていない状態で、下降中で、AniTypeが２以外なら
		{
			if(!(Btn1 & (1<<1)) && BtnCnt < 3 && (Btn2 & (1<<1)))	//今回(押)で、かつ前回(離)だったら
			{	
					pC->AniType = 13;				//アニメーション5
					pC->AniNum = 0;					//アニメーションの最初から
					pC->AniTimeNow = 0;				//カウント時間を０に
					pC->AniTurn = 0;				//ループして戻る絵
					DS_Play( 0, FALSE );			//効果音を鳴らす
			}
		}

		//剣上投げ
		if(pA->Change && pC->Land == 1)	//アニメを変更可能で地面に足が着いていたら
		{
			if((CmdNum[0] == 0) && (Btn1 & 1))	//今回(押)で、かつ前回(離)だったら
			{
				pC->AniType = 14;			//剣上投げアニメーション
				pC->AniNum = 0;				//アニメーションの最初から
				pC->AniTimeNow = 0;			//カウント時間を0に
				pC->AniTurn = 0;			//ループして戻る絵
			}
		}
		//剣左右投げ
		if(pA->Change)	//アニメを変更可能で地面に足が着いていたら
		{
			if(((CmdNum[0]==4) || (CmdNum[0]==1)) && (Btn1 & 1))	//←か→とＡボタンを押していたら
			{
				pC->AniType = 15;			//剣左右投げアニメーション
				pC->AniNum = 0;				//アニメーションの最初から
				pC->AniTimeNow = 0;			//カウント時間を0に
				pC->AniTurn = 0;			//ループして戻る絵
			}
		}
		//剣ジャンプ下投げ
		if(pA->Change && !pC->Land)	//アニメ変更可能で地面に足が着いていなかったら
		{
			if((CmdNum[0]==8) && (Btn1 & 1))	//下とＡボタンを押したら
			{
				pC->AniType = 16;		//剣ジャンプ下投げアニメーション
				pC->AniNum = 0;			//アニメーションの最初から
				pC->AniTimeNow = 0;		//カウント時間を0に
				pC->AniTurn = 0;		//ループして戻る絵
			}
		}
		//剣しゃがみ投げ
		if(pA->Change && pC->Land == 1)	//アニメ変更可能で地面に足が着いていたら
		{
			if(pC->AniType == 3 && Btn1 & 1)	//しゃがみアニメでＡボタンを押したら
			{
				pC->AniType = 17;	//剣しゃがみなげアニメーション
				pC->AniNum = 0;			//アニメーションの最初から
				pC->AniTimeNow = 0;		//カウント時間を0に
				pC->AniTurn = 0;		//ループして戻る絵
			}
		}

		
	}

	//●剣操作
	if(pC->AniType != 5 && pC->AniType != 10
	&& pC->AniType != 4 && pC->AniType != 11
	&& pC->AniType != 12 && pC->AniType != 13	//攻撃アニメ中じゃないなら
	&& pC->AniType != 18 && pC->AniType != 19 && pC->AniType != 20	//バリア、剣吸収、HP入れ替えアニメじゃないなら
	&& !(pC->AniType == 15 && pC->AniNum < 4)	//剣左右投げアニメの４枚目の絵より前の絵じゃないなら
	&& !(pC->AniType == 16 && pC->AniNum < 5)	//剣ジャンプ下投げアニメの５枚目の絵より前の絵じゃないなら
	&& !(pC->AniType == 17 && pC->AniNum < 4)	//剣じゃがみ投げアニメの４枚目の絵より前の絵じゃないなら
	&& Btn1 & 1)					//Ａボタンを押しているなら
	{
		if(!Swd.Son)	//剣が存在しなかったら
		{
			Swd.HitA = FALSE;	//出現時は剣は刺さってない
			
			Nage = 0;									//剣をなげているかどうかを扱うNageを0にもどしてから
			Swd.AniType = 4;							//剣を出現アニメーションさせる
			Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
			Swd.y = pC->y - Swd.h;						


			if(pC->AniType == 15 && !pC->muki)	//剣を左になげたら
			{
				Nage = 2;							//左になげたらNageを２に
				Swd.AniType = 2;					//剣が左に飛ぶアニメーション
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
				Swd.y = pC->y - 10;						

			}
			if(pC->AniType == 15 && pC->muki)	//剣を右になげたら
			{
				Nage = 1;							//右になげたらNageを１に
				Swd.AniType = 3;					//剣が右に飛ぶアニメーション
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
				Swd.y = pC->y - 10;						

			}
			if(pC->AniType == 16)	//剣を下になげたら
			{
				Nage = 3;							//下になげたらNageを３に
				Swd.AniType = 1;					//剣が下に飛ぶアニメーション
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
				Swd.y = pC->y +30;						

			}
			if(pC->AniType == 17 && pC->muki)	//剣しゃがみ右投げしたら
			{
				Nage = 1;							//剣をしゃがみ投げしたらNageを3に
				Swd.AniType = 0;					//剣が左に飛ぶアニメーション
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
				Swd.y = pC->y + 20;
			}
			if(pC->AniType == 17 && !pC->muki)	//剣しゃがみ右投げしたら
			{
				Nage = 2;							//剣をしゃがみ右なげしたらNageを2に
				Swd.AniType = 2;					//剣が右に飛ぶアニメーション
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
				Swd.y = pC->y + 20;
			}


			//Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//剣出現位置
			//Swd.y = pC->y - Swd.h;						
			Swd.Hit.w = 22;										//当たり判定の幅
			Swd.Hit.h = 90;										//当たり判定の高さ
			Swd.Hit.x = pC->x + (pC->w>>1) - (Swd.Hit.w>>1);	//当たり判定左上X座標
			Swd.Hit.y = pC->y - (Swd.Hit.h<<1);	//当たり判定左上Y座標

			Swd.AniNum = 0;
			Swd.AniTimeNow = 0;

		}
		Swd.Son = TRUE;	//剣の存在をＴＲＵＥに
	}else if(!Swd.HitA && !Nage)	//上の条件を満たしてなくて、剣が壁にささってなく、剣をなげてなかったら
	{
		Swd.Son = FALSE;	//存在をFALSEにする
	}
	if(Swd.Son && !Nage && Swd.AniNum == 1)	//剣操作中は剣のHPを消費
	{
		if(Swd.Hp > 0)	Swd.Hp--;
	}

	//●剣爆発
	if(Swd.Son && (Swd.HitA || Nage))	//剣が存在し、壁に刺さっていたるか剣を投げていたら
	{
		if(!(Btn1 & (1<<1)) && (Btn2 & (1<<1)) && Swd.AniType != 5)	//今回(離)で、かつ前回(押)だったら
		{
			EFON(EF,Swd.x+(Swd.w>>1),Swd.y+(Swd.h>>1),0);		//剣の位置に爆発エフェクトを出す
			Swd.AniType = 5;	//剣が消えるアニメーション
			Swd.AniNum = 0;
			Swd.AniTimeNow = 0;
		}
		if(Swd.AniType == 5 && Swd.AniNum > 2)	//剣の消えるアニメーションの2枚目以降なら
		{
			//剣の破片を飛ばす
			for(i = 0;i < Swd.Hp;i++)	//剣のHp分破片を飛ばす
			{
				ShotFire(Swd.x+(rand()%Swd.w),Swd.y+(rand()%Swd.h),0,19,2);
				Swd.Hp--;
			}

			if(Swd.Land == 1)	//剣が下の方に刺さっていたら火をつける
			{
				for(i = 0;i < 6;i++)
					ShotFire(Swd.x+(rand()%Swd.w),Swd.y+48,0,7,2);	//弾の発射（地面に配置する弾
			}

			Swd.Son = FALSE;	//剣の存在をFLASEに
			Swd.HitA = FALSE;	//剣のが壁に刺さっているかのフラグをFALSEに戻す
		}
	}

	//●バリア	(弾を跳ね返す
	if(!Swd.Son && Swd.Hp > 0 && pC->Land == 1 && (CmdGet == 8 || CmdGet == 7) 
	&&(pA->Change || (pC->AniType == 18 && (Btn1 & (1<<1))))	)	//アニメ変更可能で地面に足が着いていたら
	{
		pC->AniType = 18;			//
		if(pC->OldAniType != 18)	//
		{
			pC->AniNum = 0;			//アニメーションの最初から
			pC->AniTimeNow = 0;		//カウント時間を0に
		}
		pC->AniTurn = 10;			//ループして戻る絵
	}
	else if(pC->AniType == 18 && 
	(	((Btn2 & (1<<1)) && !(Btn1 & (1<<1)))	
	|| Swd.Hp <= 1	)	)
	{	//バリアアニメ終了後に待機アニメに変更
		pC->AniType = 0;
		pC->AniNum = 0;			//アニメーションの最初から
		pC->AniTimeNow = 0;		//カウント時間を0に
		pC->AniTurn = 0;		//ループして戻る絵も戻しておく
	}
	if(pC->AniType == 18 && pC->AniNum == 10)	//このアニメーション中はプレイヤーHPを剣のHPに変える
	{
		Swd.Hp --;
	}
	//●剣吸収
	if(!Swd.Son && pC->Land == 1 && (CmdGet == 6 || CmdGet == 5) && pA->Change && (Btn1 & 1)	)	//アニメ変更可能で地面に足が着いていたら
	{
		pC->AniType = 19;			
		if(pC->OldAniType != 19)
		{
			pC->AniNum = 0;			//アニメーションの最初から
			pC->AniTimeNow = 0;		//カウント時間を0に

		}
		pC->AniTurn = 0;			//ループして戻る絵
	}else if(pC->AniType == 19 && (Btn2 & 1) && !(Btn1 & 1)	)
	{	//剣吸収アニメ終了後に待機アニメに変更
		pC->AniType = 0;
		pC->AniNum = 0;			//アニメーションの最初から
		pC->AniTimeNow = 0;		//カウント時間を0に
		pC->AniTurn = 0;		//ループして戻る絵も戻しておく
	}

	//●プレイヤーと剣のHP入れ替え
	if(!Swd.Son && pC->Land == 1 && (CmdGet == 3 || CmdGet == 4) && pA->Change && (Btn1 & 1)	)	//アニメ変更可能で地面に足が着いていたら
	{
		pC->AniType = 20;			//
		if(pC->OldAniType != 20)	//
		{
			pC->AniNum = 0;			//アニメーションの最初から
			pC->AniTimeNow = 0;		//カウント時間を0に
		}
		pC->AniTurn = 0;			//ループして戻る絵
	}else if(pC->AniType == 20 && (Btn2 & 1) && !(Btn1 & 1)	)
	{	//アニメ終了後に待機アニメに変更
		pC->AniType = 0;
		pC->AniNum = 0;			//アニメーションの最初から
		pC->AniTimeNow = 0;		//カウント時間を0に
		pC->AniTurn = 0;		//ループして戻る絵も戻しておく
	}

	if(pC->AniType == 20 && pC->Hp > 2 && Swd.Hp < Swd.MaxHp)	//このアニメーション中はプレイヤーHPを剣のHPに変える
	{
		pC->Hp -= 2;
		Swd.Hp ++;
		EFON(EF,pC->x+(rand()%pC->w),pC->y+(rand()%pC->h),11);	//弾の消える位置に弾ヒットエフェクトをON
	}

	//●ダメージをうける
	if(pC->HitD)	//ダメージをうけるフラグが０以外になったら
	{
		if(pC->AniType != 9)	//アニメが９じゃなかったら
		{
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -6;
		}
		pC->AniType = 9;	//ダメージをうけるアニメーション
		pC->AniTurn = 0;

		if(pC->muki)
		{
			if(pC->x < 400-(pC->w>>1))	//キャラX座標が400より小さければ
			{
				pC->x += 4;					//キャラを右に移動
			}else
			{
				if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//右端までいったら何もしない
					WorldX = 4;				//WorldXを＋１
			}
		}else
		{
			if(pC->x > 200-(pC->w>>1))	//キャラX座標が200より大きければ
			{	
				pC->x -= 4;					//キャラを左に移動
			}else							//キャラX座標が200以下なら
			{
				if(!(WMoveX <= 0))			//左端までいったら何もしない
					WorldX = -4;					//WordlXを－１(Mapを右にスクロール
			}
		}

		if(pC->AniNum == 6)		//ダメージアニメーションが終わる時
		{
			pC->HitD = 0;	//アニメの6番なら、ダメージフラグを０に戻す
			Muteki = 30;	//無敵時間を設定
		}
	}


	//●やられる
	if(pC->Hp < 1)		//Hpが１よりちいさかったら
	{
		pC->AniType = 8;	//やられるアニメーション

		pC->Son = FALSE;	//キャラの存在をFALSEに

		if(pC->OldAniType != 8)	//前回のアニメーションが８以外なら
		{
			pC->AniNum = 0;		//アニメーションの最初から
			pC->AniTimeNow = 0;	//アニメーション表示カウント時間も０に
		}
		pC->AniTurn = 16;		//ループして戻る絵
	}

	/*
	//剣しゃがみ斬りの弾
	if(pC->AniType == 10 && pC->AniNum > 2)
	{
		if(pC->muki == 0)	//左向きなら	
			ShotFire(pC->x +(pC->AniNum<<4),pC->y+pC->h-48 -(pC->AniNum<<2),1,6,2);	//弾の発射
			//ShotFire(pC->x+pC->w,pC->y+32,1,16,2);
		else				//左向きじゃないなら
			ShotFire(pC->x -(pC->AniNum<<4),pC->y+pC->h-48-(pC->AniNum<<2),0,6,2);		//弾の発射
			//ShotFire(pC->x-16,pC->y+32,0,16,2);

	}
	*/
	//剣縦斬りの弾
	if(pC->AniType == 5 && pC->AniNum == 4)
	{
		if(pC->muki == 0)	//左向きなら	
			//ShotFire(pC->x +(pC->AniNum<<4),pC->y+pC->h-48 -(pC->AniNum<<2),1,6,2);	//弾の発射
			for(i = 0;i < 3;i++)
				ShotFire(pC->x+pC->w+16,pC->y+(i * 16),1,16,2);
		else				//左向きじゃないなら
			//ShotFire(pC->x -(pC->AniNum<<4),pC->y+pC->h-48-(pC->AniNum<<2),0,6,2);		//弾の発射
			for(i = 0;i< 3;i++)
				ShotFire(pC->x-32,pC->y+(i*16),0,16,2);

	}


	//剣移動時のエフェクト	
	if(Swd.Son			
		&& !Swd.HitA		//剣が刺さってなく
		&& Swd.AniType != 4	//剣が出現アニメーションじゃなく
		&& (CmdNum[0] == 1 || CmdNum[0] == 2 || CmdNum[0] == 4 || CmdNum[0] == 8 || Nage)	//剣をなげているか　OR 十字キーを押しているか 
		)	//剣が存在して、十字キーを入力中で、剣が刺さってなかったら
	{
		for(i = 0;i < 3;i++)
			EFON(EF,Swd.x+(Swd.w>>1)+(rand()%32-16),Swd.y+(Swd.h>>1)+(rand()%32-16),6);	//エフェクト表示
		//ShotFire(Swd.x+(Swd.w>>1)-24,Swd.y+(Swd.h>>1)-24,1,6,2);	//弾の発射
	}

	//砂ぼこりのエフェクト
	if(pC->Land == 1 && pC->AniType == 2 && (pC->MoveChkX != pC->x || WorldX))	//プレイヤーが着地中でダッシュアニメで移動中なら
		EFON(EF,pC->x+(pC->w>>1)+(pC->muki*32-16),pC->y+pC->h-18,7+(rand()%2));		//砂ぼこりをたてるエフェクト



	//次のこの関数を実行するときに必要なデータを保存
	pC->OldAniType = pC->AniType;	//前回のアニメーションの種類を保存
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void SwdAction(CHR_DATA *pC,ANIME_DATA *pA)		//機能：剣を動かす関数
//●引数１：CHR_DATA型構造体
//●引数２：ANIME_DATA型構造体（現在表示中のアニメが変更可能か調べるの必要
{

	switch(Nage)
	{
	case 0:	//剣をなげてないなら（0なら）
		switch(CmdNum[0])	//十字キーのデータをもとに分岐
		{
		case 1:		//左を押したら
			if(pA->Change)
			{
				pC->AniType = 2;	//左向きのアニメーション
				pC->muki = 1;		//向きを左に
				
				if(CmdGet == 1)	//ダッシュコマンドを入力していたら
					pC->x -= 15;	//左に移動
				else			//ダッシュコマンドを入力していなかったら
					pC->x -= 8;

				if(pC->OldAniType != 2 || CmdNum[0])	//前回のアニメーションが２じゃないなら OR 十字キーどれかを押していたら
				{
					//向きが変わったので（OldAniTypeで判定) 剣の当たり判定範囲を変更
					pC->Hit.w = 90;		//当たり判定の幅
					pC->Hit.h = 22;		//当たり判定の高さ
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
					pC->AniNum = 0;	//アニメーションを最初から
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//ループして戻るアニメ
			}
			break;
		case 2:		//上を押したら
			if(pA->Change)	//変更可能なアニメーションなら
			{
				pC->AniType = 0;	//上向きのアニメーション
				pC->muki = 2;		//向きを上に

				if(CmdGet == 2)		//ダッシュコマンドを入力したら
					pC->y -= 15;
				else
					pC->y -= 8;
				
				if(pC->OldAniType != 0 || CmdNum[0])	//前回のアニメが０じゃないなら
				{
					//向きが変わったので（OldAniTypeで判定) 剣の当たり判定範囲を変更
					pC->Hit.w = 22;		//当たり判定の幅
					pC->Hit.h = 90;		//当たり判定の高さ
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
					pC->AniNum = 0;	//アニメーションを最初から
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//ループして戻るアニメ
			}
			break;
		case 4:		//右を押したら
			if(pA->Change)	//変更可能なアニメーションなら
			{
				pC->AniType = 3;	//右向きのアニメ
				pC->muki = 3;		//向きを右
				
				if(CmdGet == 3)		//ダッシュコマンドを入力したら
					pC->x += 15;
				else
					pC->x += 8;
				
				if(pC->OldAniType != 3 || CmdNum[0])	
				{
					//向きが変わったので（OldAniTypeで判定) 剣の当たり判定範囲を変更
					pC->Hit.w = 90;		//当たり判定の幅
					pC->Hit.h = 22;		//当たり判定の高さ
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
					pC->AniNum = 0;	//アニメーションの最初から
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//ループして戻るアニメ
			}
			break;
		case 8:		//下を押したら
			if(pA->Change)
			{
				pC->AniType = 1;	//下向きのアニメーション
				pC->muki = 4;		//向きを下

				if(CmdGet == 4)		//ダッシュコマンドを入力したら
					pC->y += 15;
				else
					pC->y += 8;
				
				if(pC->OldAniType != 1 || CmdNum[0])	
				{
					//向きが変わったので（OldAniTypeで判定) 剣の当たり判定範囲を変更
					pC->Hit.w = 22;		//当たり判定の幅
					pC->Hit.h = 90;		//当たり判定の高さ
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
					pC->AniNum = 0;	//アニメーションの最初から
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;
			}
			break;
		default:	//どの条件にもあてはまらない場合
			if(pA->Change && (pC->AniType == 4 && pC->AniNum == 7))	//出現アニメーションが終わる時なら
			{
				pC->AniType = 0;	
				pC->muki = 1;		
				if(pC->OldAniType != 0 || CmdNum[0])		//前回のアニメーションがこのアニメじゃなかったら
				{
					//向きが変わったので（OldAniTypeで判定) 剣の当たり判定範囲を変更
					pC->Hit.w = 22;		//当たり判定の幅
					pC->Hit.h = 90;		//当たり判定の高さ
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
					pC->AniNum = 0;										//アニメーションの最初から
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;
			}
			break;
		}
		break;

	case 1:	//左に剣をなげたら
		if(pA->Change)
		{
			pC->AniType = 2;	//左向きのアニメーション
			pC->muki = 1;		//向きを左に
			pC->x -= 15;	//左に移動

			if(pC->OldAniType != 2)	//前回のアニメーションが２じゃないなら
			{			//向きが変わったので
				pC->AniNum = 0;	//アニメーションを最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;	//ループして戻るアニメ

			pC->Hit.w = 90;		//当たり判定の幅
			pC->Hit.h = 22;		//当たり判定の高さ
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標

		}
		break;
	case 2:	//剣を右に投げたら
		if(pA->Change)	//変更可能なアニメーションなら
		{
			pC->AniType = 3;	//右向きのアニメ
			pC->muki = 3;		//向きを右
			pC->x += 15;		//右に移動
			
			if(pC->OldAniType != 3)	//前回のアニメーションが２じゃないなら
			{
				//向きが変わったので
				pC->AniNum = 0;	//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;	//ループして戻るアニメ
			pC->Hit.w = 90;		//当たり判定の幅
			pC->Hit.h = 22;		//当たり判定の高さ
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
		}
		break;
	case 3:	//剣を下になげたら
		if(pA->Change)
		{
			pC->AniType = 1;	//下向きのアニメーション
			pC->muki = 4;		//向きを下
			pC->y += 25;		//剣を下に移動
			
			if(pC->OldAniType != 1)	//前回のアニメーションが２じゃないなら
			{	//向きが変わったので
				pC->AniNum = 0;	//アニメーションの最初から
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;

			pC->Hit.w = 22;		//当たり判定の幅
			pC->Hit.h = 90;		//当たり判定の高さ
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定左上X座標
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定左上Y座標
		}
		break;

	}
	


	pC->OldAniType = pC->AniType;	//前回のアニメーションの種類を保存
}

//■―――――――――――――――――――――――――――――――――――――――――――――――
