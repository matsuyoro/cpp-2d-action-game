#include <windows.h>

#include "GameStruct.h"		//構造体の型の定義のヘッダファイル
#include "Extern.h"			//外部変数の宣言のヘッダファイル
#include "DirectSound.h"

#include "GameCheckProc.h"
	//判定関数などのプロトタイプ宣言のヘッダ
////関数本体//////
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――
int CharAnime(CHR_DATA *pC,ANIME_DATA *pA,ANIME_DATA *pA2)		//機能：キャラクターをアニメーションさせる関数
//●引数１：アニメーションするキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーションデータの構造体の第２要素数の１つ先のデータ
{
	pC->AniTimeNow++;	//表示時間カウンタを＋１
	if(pC->AniTimeNow >= pA->TimeMax)	//表示時間が、今表示している要素のの最大表示時間以上になったら	
	{
		pC->AniNum++;	//次の絵に進む
		if(pA2->Num == -1)	//もし、進んだ先の要素のNumメンバがー１だったら
		{
			pC->AniNum = pC->AniTurn;	//-1が出た後どの絵に戻るか	
		}else if(pA2->Num == -2)	//もし、進んだ先の要素のNumメンバがー２だったら
		{
			pC->AniType = 0;		//基本となるアニメーションの最初からスタート
			pC->AniNum = 0;
		}
		pC->AniTimeNow = 0;	//表示時間を０に
	}
	return(pA->Num);	//Anime構造体のメンバNumを戻す
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――
int KeyCmdChk(int Key)		//機能：コマンド入力関数
//●引数１：十字キーデータ
//●戻値：どのコマンドを入力したかを戻す
{
	int i,j;						//カウンタ変数
	static int Cnt;					//コマンドの順番を表す配列の何番目を調べているか
	//static int AllCnt;			//コマンド入力の全ての時間の合計を扱う

	if(Key == CmdNum[0])	//前回と同じキーが押されていたら
	{
		CmdCnt[0]++;		//押しているボタンの時間とカウント
	}else					//同じでないなら
	{
		for(i = 7;i > 0;i--)	//7～１の順番にずらす
		{
			CmdNum[i] = CmdNum[i-1];	//配列の中身をずらす
			CmdCnt[i] = CmdCnt[i-1];	//押している時間を扱う配列もずらす
		}
		CmdNum[0] = Key;	//0に最新のデータを代入
		CmdCnt[0] = 1;		//時間のカウントが１から始まるように
	}

	for(j = 0;j < CMD_MAX;j++)	//コマンドデータの分だけ繰り返す
	{
		Cnt = 0;					//コマンドの配列の何番目を調べるかを扱うCntを０に戻す

		for(i = 3;i >= 0;i--)		//3回分のデータだけ調べる
		{
			if(CmdNum[i] == WazaCmd[j].Cmd[Cnt])	//もし、十字キーとコマンドデータが同じだったら
			{						
				Cnt++;									//次のコマンドデータを調べる
				//if(Cnt >= 3) break;					//コマンドデータが３つ判定できたら、ループ終了
				if(WazaCmd[j].Cmd[Cnt] == -1)			//技データで-1が出たらそこで技の終了
					break;
			}
		
		}

		if(	WazaCmd[j].Cmd[Cnt] == -1				//コマンドが３つ判定でき
		&& CmdNum[0] == WazaCmd[j].Cmd[Cnt-1]		//最新のコマンドデータと技データの最後のデータが同じなら
		&& (!WazaCmd[j].Btn							//ボタン無しの技なら
		|| (Btn1 & WazaCmd[j].Btn)					//現在押しているボタンと技データのボタンが同じなら
		&& Btn2 != Btn1))							//１つ前のボタンデータと最新のボタンデータが異なるなら
		{
			AllCnt = 0;	//技入力時間をまずは０に
			for(i = 0;i < Cnt;i++)	//技入力の全ての時間をAllCntに代入
				AllCnt += CmdCnt[i];
			if(AllCnt < WazaCmd[j].Time)	//入力した時間が技入力時間以下なら
			{
				return(j);	//成立したコマンドの番号を戻す
			}
		}
	}
	return(-1);	//どのコマンドも入力しなかったら
}

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void EnemyOnPos()	//機能：エネミーを特定の位置に出現させる関数
{
	int i,j;	//カウンタ変数

	for(i = 0;i < EneOnPos_Max.x;i++)	//出現ポイントの数だけ繰り返す
	{
		if(pEneOn[i].OnFlag)	//フラグがTRUEなら（まだ出現してないポイントの敵なら
		{
			if((pEneOn[i].x > WMoveX && pEneOn[i].x < WMoveX+640)
			&& (pEneOn[i].y > WMoveY && pEneOn[i].y < WMoveY+480))	//出現ポイントが画面内にきたら
			{
				for(j = 0;j < ENE_MAX;j++)
				{
					if(!En[j].Son)	//エネミーが存在しないなら
					{
						En[j] = EnemyNum[pEneOn[i].type];	//指定のエネミーを設定
						En[j].x = pEneOn[i].x - WMoveX;				//エネミーを指定のX座標に設定
						En[j].y = pEneOn[i].y - WMoveY;				//エネミーを指定のY座標に設定
						En[j].Son = TRUE;					//エネミーを存在させる
						pEneOn[i].OnFlag = FALSE;			//一度出現させるともう出現しなくする
						
						if(En[i].Type == 3 && En[i].Son)	//適が竜なら
						{
							//En[i] = EnemyNum[3];			//エネミー１を存在させる
							//En[i].Son = TRUE;
							OBJON(Obj,(320<<5)-WMoveX,(25<<5)-WMoveY,0);			//オブジェ（ボス１体
						//	OBJON(Obj,En[i].x+60,En[i].y+240,0);
						//	OBJON(Obj,En[i].x+50,En[i].y+200,0);
							OBJON(Obj,En[i].x+40,En[i].y+170,4);			//オブジェ（ボス１間接
							OBJON(Obj,En[i].x+37,En[i].y+160,4);
							OBJON(Obj,En[i].x+34,En[i].y+150,4);
							OBJON(Obj,En[i].x+30,En[i].y+140,3);
							OBJON(Obj,En[i].x+27,En[i].y+130,3);
							OBJON(Obj,En[i].x+24,En[i].y+120,3);
							OBJON(Obj,En[i].x+20,En[i].y+110,3);
							OBJON(Obj,En[i].x+15,En[i].y+90,2);
							OBJON(Obj,En[i].x+10,En[i].y+80,2);
							OBJON(Obj,En[i].x+5,En[i].y+50,2);
							break;
						}
						break;
					}
				}
			}
		}
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void OBJON(OBJ_DATA *pO,int x,int y,int OBJType)	//機能：オブジェクトをだすための関数
//●引数１：オブジェクトの構造体
//●引数２：オブジェクトの表示位置X
//●引数３：オブジェクトの表示位置Y
//●引数４：オブジェクトの種類
{
	int i;

	for(i = 0;i < OBJ_MAX;i++)	//オブジェクトの数だけ繰り返す
	{
		if(!pO[i].Son)	//オブジェクトの存在がFALSEなら
		{
			pO[i] = OBJData[OBJType];	//オブジェクトのデータを代入
			pO[i].x = x - (pO[i].w>>1);	//オブジェクトを出す位置X
			pO[i].y = y - (pO[i].h>>1);	//オブジェクトを出す位置Y
			pO[i].Son = TRUE;			//オブジェクトの存在をTRUEにする
			break;
		}
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void BgObjOn(BGOBJ_DATA *pO,int x,int y,int OBJType,int BGLine)	//機能：オブジェクトをだすための関数
//●引数１：オブジェクトの構造体
//●引数２：オブジェクトの表示位置X
//●引数３：オブジェクトの表示位置Y
//●引数４：オブジェクトの種類
//●引数５：背景のどの部分にオブジェを設置するか
{
	int i;

	for(i = 0;i < BGOBJ_MAX;i++)	//オブジェクトの数だけ繰り返す
	{
		if(!pO[i].Son)	//オブジェクトの存在がFALSEなら
		{
			while(TRUE)	//オブジェが設置されるまで繰り返す
			{
				pO[i] = BGOBJData[OBJType];	//オブジェクトのデータを代入

				if((BGLine == (pO[i].Line-1)) || (!pO[i].Line))	//列が指定されているオブジェと乱数のオブジェの列が同じか　指定なしなら（０なら）
				{
					pO[i].Line = BGLine;		//背景のどの部分に設置するかを設定
					pO[i].x = x;				//オブジェクトを出す位置X
					pO[i].y = y - pO[i].h;		//オブジェクトを出す位置Y
					pO[i].orgX = x;				//ｘ座標保存用（スクロール時使う

					pO[i].Son = TRUE;			//オブジェクトの存在をTRUEにする
					break;
				}
				OBJType = rand()%22;	//オブジェの種類を乱数で変える
			}
			break;
		}
	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void EFON(EF_DATA *pE,int x,int y,int EType)	//機能：エフェクトを出すための関数
//●引数１：エフェクトの構造体
//●引数２：エフェクト表示位置X
//●引数３：エフェクト表示位置Y
//●引数４：エフェクトの種類
{
	int i;

	//エフェクトの発生
	for(i = 0;i < EF_MAX;i++)	//エフェクトの数だけ繰り返す
	{
		if(!pE[i].Son)	//エフェクトの存在がFALSEなら
		{	
			pE[i] = EFData[EType];		//エフェクトのデータを代入
			pE[i].x = x - (pE[i].w>>1);	//エフェクトを出す位置X
			pE[i].y = y - (pE[i].h>>1);	//エフェクトを出す位置Y
			pE[i].Son = TRUE;			//エフェクトの存在をTRUEにする
			break;
		}
	}

}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void EFOFF(EF_DATA *pE)	//機能：エフェクトのアニメーションと存在を扱う関数
//●引数１：エフェクトの構造体
{
	int i;

	//エフェクトアニメーションと存在
	for(i = 0;i < EF_MAX;i++)
	{
		if(pE[i].Son)	//エフェクトが存在したら
		{
			pE[i].AniCnt++;	//アニメーション表示のカウント
			if(pE[i].AniCnt > pE[i].AniMax)	
				pE[i].Son = FALSE;	//アニメーションを最後まで表示したエフェクトの存在を消す
		}
	}
}

//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void ShotFire(int x,int y,int muki,int SType,int EnePlr)	//機能：弾を発射する関数
//●引数１：弾発射位置X
//●引数２：弾発射位置Y
//●引数３：移動方向（０＝左
//●引数４：弾の種類
//●引数５：当たり判定対象のキャラ（1 = エネミー :2 = プレイヤー
{
	int i;

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(!Shot[i].Son)	//弾の存在がFALSEなら
		{	
			Shot[i] = ShotData[SType];	//弾のデータを代入
			Shot[i].x = x;	//弾を発射する位置X
			Shot[i].y = y;	//弾を発射する位置Y
			if(muki == 0)	Shot[i].mx = -Shot[i].mx;		//向きが左向きなら左に弾を飛ばす
			Shot[i].Son = EnePlr;								//弾の存在をTRUEにする
			break;
		}
	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void ShotMove(int mx,int my)	//機能：弾を移動させる関数
//●引数1，2：弾XY移動量
{
	int i;	//カウンタ

	for(i = 0;i < SHOT_MAX;i++)	//弾の数だけ繰り返す
	{
		if(Shot[i].Son)	//弾が存在するなら
		{
			
			switch(Shot[i].Type)	//弾の種類を元に分岐
			{
			//--------------------------------------------------------------------------------------
			case 4://○上から落ちる火
				Shot[i].my++;
				Shot[i].y += Shot[i].my;
				break;
			case 22://○噴火する毒弾
			case 24://○骨弾
				Shot[i].mx = (i%8)-4;	//ショットの配列番号で使用x座標移動量を決める
				Shot[i].my++;			//落下速度を除々に上げる
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				break;
			case 26://○灰２（２＊２）
				Shot[i].mx = (i%3)-3;
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt == 7)
				{
					ShotFire(Shot[i].x,Shot[i].y,0,24,Shot[i].Son);	//弾の発射
					Shot[i].Son = FALSE;
				}
			case 25://○灰
				Shot[i].mx = (i%3)-3;
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				break;
			case 27://○分散する炎
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt == 4)
				{
					//Shot[i].mx -= (rand()%5-2);
					//Shot[i].mx %= 4;
					Shot[i].my -= (rand()%5-2);
					Shot[i].my %= 4;
					
					if(Shot[i].mx < 0)
						ShotFire(Shot[i].x,Shot[i].y,0,26,Shot[i].Son);	//弾の発射
					else
						ShotFire(Shot[i].x,Shot[i].y,1,26,Shot[i].Son);	//弾の発射
				}

				break;
			case 29://○爆発弾(エフェクトを使用
				if(Shot[i].AniCnt == (rand()%15))
					EFON(EF,Shot[i].x,Shot[i].y,0);
				break;

			//--------------------------------------------------------------------------------------
			case 7://○地面の火
				if(Shot[i].AniCnt >= 3 && (rand()%10 ==1))	
					Shot[i].Son = FALSE;	//アニメーションが４枚目で乱数が１なら弾を消す
				break;
			//--------------------------------------------------------------------------------------
			case 11:	//瓦礫
			case 12:	//〃
			case 13:
			case 14:
			case 15:
			case 16:
		

			case 9://○葉っぱ竜巻
			case 8://光
			case 18:
				if(Shot[i].Type != 18 || rand()%5 == 1)
				{
					if(Shot[i].x+4 > Plr.x+(Plr.w>>1))	//弾がプレイヤーより右にいたら
						Shot[i].mx --;					//弾の移動量をデクリメント
					else								//左にいたら
						Shot[i].mx ++;					//弾の移動量をインクリメント
					Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ

					if(Shot[i].y+4 > Plr.y+(Plr.h>>1))	//弾がプレイヤーより下にいたら
						Shot[i].my --;					
					else								//上にいたら
						Shot[i].my ++;
					Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
				}
				break;
			case 20:	//剣破片
				if(Plr.AniType == 19)	//プレイヤーが吸収アニメーション中なら
				{
					Shot[i].Son = 3;	//弾の判定キャラを両方にする

					if(Shot[i].x+4 > Plr.x+(Plr.w>>1))	//弾がプレイヤーより右にいたら
						Shot[i].mx --;					//弾の移動量をデクリメント
					else								//左にいたら
						Shot[i].mx ++;					//弾の移動量をインクリメント
					Shot[i].mx %= 16;
					Shot[i].x += Shot[i].mx;	//移動量を弾のX座標に足しこむ

					if(Shot[i].y+4 > Plr.y+(Plr.h>>1))	//弾がプレイヤーより下にいたら
						Shot[i].my --;					
					else								//上にいたら
						Shot[i].my ++;
					Shot[i].my %= 16;
					Shot[i].y += Shot[i].my;			//移動量を弾のY座標に足しこむ
				}else if(rand()%3 == 1)	//そうでないなら
				{
					Shot[i].Son = 1;	//剣破片の判定キャラをプレイヤーにする
					Shot[i].mx += rand()%3-1;
					Shot[i].my += rand()%3-1;
					Shot[i].x += Shot[i].mx;
					Shot[i].y += Shot[i].my;
				}
				break;

			case 10://○葉っぱ吹雪
				if(Shot[i].x+4 > 320)	//弾が画面中央より右にいたら
					Shot[i].mx --;
				else					//左にいたら
					if(Shot[i].mx > 1)	Shot[i].mx ++;	//絶対に右には流れないようにする
				Shot[i].x += Shot[i].mx;

				if(Shot[i].y+4 > 240)	//弾が画面中央より下にいたら
					Shot[i].my --;
				else					//上にいたら
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;
				break;
			case 19://○火炎放射
				Shot[i].y += (rand()%16-8);
				if(Shot[i].mx > 0) Shot[i].mx--;	//移動速度が０じゃないならじょじょに速度を落とす
				if(Shot[i].mx < 0) Shot[i].mx++;
				Shot[i].x += Shot[i].mx;		//弾を移動量の分だけ移動させる
				Shot[i].y += Shot[i].my;
				if(Shot[i].mx == 0)		//弾のアニメーションが４より大きくなったら
					Shot[i].Son = FALSE;	//弾を消す

				break;

			case 6://○火炎放射(遠距離
				Shot[i].y += (rand()%10)-5;	//弾のY座標を乱数で変える
				Shot[i].AniCnt %= 5;
				Shot[i].x += Shot[i].mx;		//弾を移動量の分だけ移動させる
				Shot[i].y += Shot[i].my;
				break;
			case 17:
				Shot[i].x += Shot[i].mx;		//弾を移動量の分だけ移動させる
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt > 3)	//アニメーションが５以上なら
					Shot[i].Son = FALSE;	//弾を消す
				break;

			default:	//通常の弾なら
				Shot[i].x += Shot[i].mx;		//弾を移動量の分だけ移動させる
				Shot[i].y += Shot[i].my;
				break;
			}

			if(Shot[i].Type != 20)	//剣の破片弾じゃないなら
			{
				if(Shot[i].y > 480 || Shot[i].y < -Shot[i].w
				|| Shot[i].x > 640 || Shot[i].x < -Shot[i].h)	//画面の外に出たら
				{
					Shot[i].Son = FALSE;					//存在をFALSEに
				}
			}else
			{	//剣の破片の有効範囲
				if(Shot[i].y > Plr.y+(Plr.h>>1)+800 || Shot[i].y < Plr.y+(Plr.h>>1)-800
				|| Shot[i].x > Plr.x+(Plr.w>>1)+800 || Shot[i].x < Plr.x+(Plr.w>>1)-800)
				{	//剣の破片の有効範囲は普通の弾より広い
					Shot[i].Son = FALSE;
				}
			}
		}
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void PlrSwdChk(CHR_DATA *p1,CHR_DATA *p2)	//機能：プレイヤーと剣の当たり判定
//●引数１：判定をするCHR_DATA型のキャラデータ
//●引数２：判定をする剣のキャラデータ

{
	int x1,y1,w1,h1;	//判定をするキャラ１の左上XY座標と幅、高さを扱う
	int x2,y2,w2,h2;	//もうひとりの判定をするキャラの当たり判定範囲
		
	//キャラ１
	x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);				//当たり判定部分の左上x座標
	y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1);				//当たり判定部分の左上y座標
	w1 = p1->Hit.w;											//当たり判定部分の幅
	h1 = p1->Hit.h;											//当たり判定部分の高さ
	//剣
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//キャラ１とキャラ２が重なっていたら
	{
		if(y1+((h1>>2)*3) < y2+(h2>>2) && p1->U > 0)	//	剣の高さを4分の1　より　キャラ当たり判定Y座標＋キャラ4分の3のところに当たったら &&　落下中なら
		{
			p1->Land = 1;	//着地判定
			y1 = y2 - h1;	//キャラを戻すの座標をもとめて代入
			p1->y = y1 + (h1>>1) - (p1->h>>1);
		}
	}
}

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void ChrHitChk(CHR_DATA *p1,CHR_DATA *p2)	//機能：プレイヤーとキャラの当たり判定
//●引数１：判定をするCHR_DATA型のキャラデータ
//●引数２：判定をするもう一人のキャラデータ
//●戻り値：どういう攻撃をうけたかを数値で返す
{
	int x1,y1,w1,h1;	//判定をするキャラ１の左上XY座標と幅、高さを扱う
	int x2,y2,w2,h2;	//もうひとりの判定をするキャラの当たり判定範囲
		
	//キャラ１
	if(p1->Type == -1								//キャラがプレイヤーなら
	&& ((p1->AniType == 3 && p1->AniNum > 3)		//しゃがみ中なら
	|| (p1->AniType == 10) || (p1->AniType == 11)	//しゃがみ攻撃中なら
	|| (p1->AniType == 17)))						//剣しゃがみ投げ中だったら
	{
		x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);					//当たり判定部分の左上x座標
		y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1) + (p1->Hit.h>>1);								//当たり判定部分の左上y座標
		w1 = p1->Hit.w;												//当たり判定部分の幅
		h1 = p1->Hit.h>>1;											//当たり判定部分の高さ
	}else		//条件にあてまらなかったら
	{
		x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);				//当たり判定部分の左上x座標
		y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1);				//当たり判定部分の左上y座標
		w1 = p1->Hit.w;											//当たり判定部分の幅
		h1 = p1->Hit.h;											//当たり判定部分の高さ
	}

	//キャラ２
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//キャラ１とキャラ２が重なっていたら
	{
		if(p2->Type != 11)	p1->HitD = 1;		//攻撃を受けたらTRUE(エネミーがツボならダメージフラグを１にしない
		p1->Hp -= p2->Atk;	//適の攻撃力分ダメージ
		DS_Play(5,FALSE);	//効果音を鳴らす

		if(x2+(w2>>1) < x1+(w1>>1))		//キャラ２の右側にいたら
		{
			if(p1->x < 400-(p1->w>>1))	//キャラがx座標400より小さければ
			{
				p1->x += 15;				//キャラ右にふきとばす
				p2->x -= 2;					//攻撃したキャラはすこし左にずれる
			}else						//条件を満たしてなければ（キャラがx座標400以上なら
			{
				if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//右端までいったら何もしない
				{
					WorldX = 15;				//WorldXを＋１
					p2->x -= 2;
				}
			}
			p1->muki = 1;	//左を向かせる
		}else							//右側じゃなかったら
		{	
			if(p1->x > 200-(p1->w>>1))	//キャラX座標が200より大きければ
			{	
				p1->x -= 15;					//キャラを左にふき飛ばす
				p2->x += 2;
			}else						//キャラX座標が200以下なら
			{
				if(!(WMoveX <= 0))			//左端までいったら何もしない
				{	
					WorldX = -15;					//WordlXを－１(Mapを右にスクロール
					p2->x -= 2;
				}
			}
			p1->muki = 0;	//右を向かせる
		}
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
int ShotHitChk(SHOT_DATA *pS,CHR_DATA *pC)	//機能：弾とキャラの判定
//●引数１：判定を行う弾のデータ
//●引数２：ダメージをうけるキャラのデータ
{
	int x1,y1,w1,h1;	//判定をするキャラ１の左上XY座標と幅、高さを扱う
	int x2,y2,w2,h2;	//もうひとりの判定をするキャラの当たり判定範囲
		
	//弾
	x1 = pS->x + (pS->w>>1) - (pS->Hit.w>>1);				//当たり判定部分の左上x座標
	y1 = pS->y + (pS->h>>1) - (pS->Hit.h>>1);				//当たり判定部分の左上y座標
	w1 = pS->Hit.w;											//当たり判定部分の幅
	h1 = pS->Hit.h;											//当たり判定部分の高さ
	
	//キャラ
	if(pC->Type == -1	//判定キャラがプレイヤーで
	&& ((pC->AniType == 3 && pC->AniNum > 3)		//しゃがみ中なら
	|| (pC->AniType == 10) || (pC->AniType == 11)	//しゃがみ攻撃中なら
	|| (pC->AniType == 17)))						//剣しゃがみ投げ中だったら
	{
		x2 = pC->x + (pC->w>>1) - (pC->Hit.w>>1);						//当たり判定部分の左上x座標
		y2 = pC->y + (pC->h>>1) - (pC->Hit.h>>1) + (pC->Hit.h>>1);		//当たり判定部分の左上y座標
		w2 = pC->Hit.w;													//当たり判定部分の幅
		h2 = pC->Hit.h>>1;												//当たり判定部分の高さ
	}else		//適キャラか　プレイヤーがしゃがみ中じゃない場合
	{
		x2 = pC->x + (pC->w>>1) - (pC->Hit.w>>1);
		y2 = pC->y + (pC->h>>1) - (pC->Hit.h>>1);
		w2 = pC->Hit.w;
		h2 = pC->Hit.h;
	}

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//弾とキャラの当たり判定部分が重なっていたら
	{
		/*
		if(pS->mx > 0)		//キャラ２の右側にいたら
		{
			pC->muki = 1;	//左を向かせる
		}else							//右側じゃなかったら
		{	
			pC->muki = 0;	//右を向かせる
		}
		*/
		

		if(pC->Type == -1)	//ダメージを受けるキャラがプレイヤーなら
		{
			if(pC->AniType == 18 && pC->AniNum > 9 && pS->Type != 18)		//プレイヤーアニメがバリアで、弾が１８じゃないなら
			{	
				pS->Son = 2;				//弾の存在を２変え自分の弾にする
				pS->mx = -pS->mx;			//弾の向きを逆にする
				//pS->my = -pS->my;			//上下は反転しない
				DS_Play( 7, FALSE);			//効果音を鳴らす
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),10);	//弾の消える位置にエフェクトをON
			}else if(pS->Type == 18)	//○弾が魂でダメージを受けるキャラがプレイヤーなら
			{
				pS->Son = FALSE;								//当たった弾を消す
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),9);	//弾の消える位置にエフェクトをON
				if(pC->Hp < pC->MaxHp)
					pC->Hp += pS->Atk;							//プレイヤーのHpを回復
				else											//Plr.Hpが満タンで回復したら剣のHpが増える
					if(Swd.Hp < Swd.MaxHp)	Swd.Hp ++;
			}else if(pS->Type == 20)	//○弾が剣の破片なら
			{
				pS->Son = FALSE;
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),9);	//弾の消える位置にエフェクトをON
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),10);	//弾の消える位置に弾ヒットエフェクトをON
				if(Swd.Hp < Swd.MaxHp)	Swd.Hp ++;
				DS_Play(5,FALSE);								//効果音を鳴らす
			}else
			{
				pC->HitD = 1;									//攻撃を受けたらTRUE
				pC->Hp -= pS->Atk;								//弾の威力分ダメージ
				DS_Play(5,FALSE);								//効果音を鳴らす
				pS->Son = FALSE;								//当たって終わったら存在をFALSEに
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),3);	//弾の消える位置に弾ヒットエフェクトをON
			}
		}else	//そうでないなら
		{
			if(pS->Type == 8)	pC->Hp += 5;				//※デバッグ（適HP回復
			pC->HitD = 10;									//攻撃を受けたらTRUE
			pS->Son = FALSE;
			EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),3);	//弾の消える位置に弾ヒットエフェクトをON
			pC->Hp -= pS->Atk;								//弾のダメージ分Hpを減らす
			if(pC->Hp < 1 && pC->Type != 11)	pC->Son = FALSE;				//攻撃をうけたキャラのHpが１より小さくなったら & 適がツボじゃないなら//キャラ２を消す
		}
		return(pC->HitD);		//どういう攻撃をうけたかを戻す
	}
	return FALSE;	//当たってないときは０を返す
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――
int AtkHitChk(CHR_DATA *p1,CHR_DATA *p2)	//機能：プレイヤーの攻撃範囲とキャラ２の当たり判定
//●引数１：キャラの攻撃範囲を判定をするCHR_DATA型のキャラデータ
//●引数２：攻撃を受けるキャラデータ
//●戻り値：どういう攻撃をうけたかを数値で返す
{
	int x2,y2,w2,h2;	//もうひとりの判定をするキャラの当たり判定範囲
	int ax,ay,aw,ah;	//攻撃の当たり判定部分を扱う

	int WazaAT = 0;	//当てた攻撃の種類によってダメージを変える
	//p2->HitD = 0;//どの攻撃が当たったかを扱うHitDを、判定前は0にする(1＝横斬り、2=縦斬り）
	
	//キャラ２(ダメージをうけるキャラ
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	//キャラ１攻撃の当たり判定範囲
	p1->HitA = TRUE;	//まずはTRUEで攻撃中にする

	if(p1->AniType == 4 && p1->AniNum == 4)	//横斬りの場合
	{
		aw = 70;									//攻撃の当たり判定部分の幅
		ah = 20;									//攻撃の当たり判定部分の高さ
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;	//左向きの場合の当たり攻撃範囲判定部分の左上x座標
		else			ax = p1->x+(p1->w>>1);		//右向きの場合の当たり攻撃範囲判定部分の左上x座標					
		ay = p1->y + 28;								//攻撃の当たり判定部分の左上y座標
		WazaAT = (p1->Atk>>1);	//横切りの場合のダメージを設定
	}
	else if(p1->AniType == 5 && p1->AniNum > 2)	//縦斬りの場合
	{
		aw = 85;									//攻撃範囲の幅
		ah = 85;									//高さ
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;	//左上X座標
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y;									//左上Y座標
		WazaAT = p1->Atk;	//縦斬りの場合のダメージを設定
	}
	else if(p1->AniType == 11 && p1->AniNum == 4)	//しゃがみ横斬りの場合
	{
		aw = 65;
		ah = 20;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y + 50;
		WazaAT = (p1->Atk>>1);
	}
	else if(p1->AniType == 10 && p1->AniNum > 4)	//しゃがみ縦斬りの場合
	{
		aw = 60;
		ah = 56;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y + 20;
		WazaAT = p1->Atk + (p1->Atk>>1);
	}
	else if(p1->AniType == 12 && p1->AniNum > 2)	//ジャンプ縦斬りの場合
	{
		aw = 90;
		ah = 80;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y;
		WazaAT = p1->Atk;
	}
	else if(p1->AniType == 13 && p1->AniNum > 2)	//ジャンプ横斬りの場合
	{
		aw = 70;
		ah = 20;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y+25;
		WazaAT = (p1->Atk>>1);
	}
	else if(Swd.Son			
		&& !Swd.HitA		//剣が刺さってなく
		&& Swd.AniType != 4 && Swd.AniType != 5	//剣が出現&消えアニメーションじゃなく
		&& (CmdNum[0] || Nage)	//剣をなげているか　OR 十字キーを押しているか 
		)	//剣が存在して、十字キーを入力中で、剣が刺さってなかったら
	{
		aw = Swd.Hit.w;		//剣の当たり判定範囲をそのまま代入
		ah = Swd.Hit.h;
		ax = Swd.Hit.x;
		ay = Swd.Hit.y;
		WazaAT = (p1->Atk>>1);
	}
	else if(Swd.Son && Swd.AniType == 5)	//剣が存在して、剣のアニメーションが５なら(剣爆破
	{
		aw = Swd.w;
		ah = Swd.h;
		ax = Swd.x;
		ay = Swd.y;
		WazaAT = (p1->Atk<<1);
	}
	else	//どの条件にもあてはまらない場合
		p1->HitA = FALSE;	//上の条件にあてはまらなかったらFALSEに（攻撃中じゃない

	//当たり判定範囲を表示する四角の座標を代入
	xbox = ax;
	ybox = ay;
	wbox = aw;
	hbox = ah;

	if(p1->HitA)	//攻撃中なら（攻撃の当たり判定が有効なら
	{
		if(ax+aw > x2 && ax < x2+w2
		&& ay+ah > y2 && ay < y2+h2)	//キャラ１の攻撃の当たり判定範囲とキャラ２が重なっていたら
		{
			p2->Hp -= WazaAT;				//攻撃をうけたキャラはHpー
			DS_Play( 2, FALSE );			//効果音を鳴らす

			if((!Swd.Son && (p1->AniType == 4 || p1->AniType == 11 || p1->AniType == 13))
			|| (Swd.Son && (Swd.muki == 1 || Swd.muki == 3)))	//横斬り攻撃なら	
			{
				p2->HitD = 1;	//横斬りなら１
				EFON(EF,((ax+x2)+((aw+w2)>>1))>>1,((ay+y2)+((ah+h2)>>1))>>1,2);		//適と攻撃範囲の中間の位置に横斬りエフェクトをON
			}else							//縦斬り攻撃なら
			{
				p2->HitD = 2;	//縦斬りなら２
				EFON(EF,((ax+x2)+((aw+w2)>>1))>>1,((ay+y2)+((ah+h2)>>1))>>1,1);		//適と攻撃範囲の中間の位置に縦斬りエフェクトをON
			}
			
			/*
			switch(p1->muki)		//攻撃したキャラの向きで判定
			{
			case 1:				//攻撃したキャラが左向きなら
				p2->x -= 8;			//左に飛ばされる
				break;
			case 0:				//右向きなら	
				p2->x += 8;			//右に飛ばされる
				break;
			case 2:				//上向きなら
				p2->y -= 4;			//上に飛ばされる
				break;
			case 4:				//下向きなら
				p2->y += 4;
				break;
			}
			*/

			if(p2->Hp < 1 && p2->Type != 11)	//攻撃をうけたキャラのHpが１より小さくなったら & 相手のTypeがツボだったら
				p2->Son = FALSE;		//キャラ２を消す

			return(p2->HitD);		//どういう攻撃をうけたかを戻す
		}
	}
	return(0);
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void UpDownChk(CHR_DATA *pC)	//機能：上昇、下降の移動
//●：引数１：移動するキャラのデータ
{
	// 重力で下に落ちる ///
	if(pC->Land != 1 | pC->Land != 2)	//地面か天井についていなかったら
		pC->U += 0.7f;	//下に落下

	if(pC->U > 0.0f && pC->U < 1.0f)	pC->U = 1.0f;	//落下速度が０以上１未満にならないようにする、でないと着地がきれいにできなくなる	
	if(pC->U < -30)	pC->U = -30;	//上昇速度の最大
	if(pC->U > 15)	pC->U = 15;		//下降速度の最小
	
	if(pC->Type == -1)	//引数として受け取ったキャラがプレイヤーなら	
	{
		if(pC->U > 0)	//落下中なら
		{
			if(pC->y < 350-(pC->h>>1))	//キャラYがY350より小さければ
				pC->y += (int)(pC->U);		//キャラを移動
			else						//キャラYがY350以上なら
				if(WMoveY < (MapYnum-WINMAP_H)*TIP_H)	//マップの下端じゃないなら
					WorldY = (int)(pC->U);					//マップスクロール
		}else			//上昇中なら
		{
			if(pC->y > 150-(pC->h>>1))	//キャラYがY150より大きければ
				pC->y += (int)(pC->U);		//キャラを移動
			else						//キャラYがY150以下なら
				if(WMoveY > 0)				//マップの上端じゃないなら
					WorldY = (int)(pC->U);		//マップスクロール
		}				

		WMoveY += WorldY;	//マップのYスクロール値を今回のスクロール量だけずらす
		ChrYScroll();		//Y方向にスクロールした分ずらすもの

	}else if(pC->Type != -2)	//プレイヤー以外なら（敵なら
	{
		pC->y += (int)(pC->U);	//キャラが上下に移動する速度分キャラを移動
	}
	
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void ChrYScroll()	//機能：画面がY方向にスクロールしているときにキャラをスクロールした分ずらす関数
{
	int i;	//カウンタ

	if(WorldY)	//Y方向にスクロールしたなら
	{
		for(i = 2;i >= 0;i--)	//残像の数だけ繰り返す
			Dum[i].y -= WorldY;		//プレイヤーの残像をY方向にスクロールした分ずらす

		if(Swd.Son)				//剣が存在し、刺さっていたら
			Swd.y -= WorldY;			//Y方向に剣をスクロールした分ずらす

		//上下にスクロールした分だけ敵もずらす
		for(i = 0;i < ENE_MAX;i++)	//敵の数だけループ
			if(En[i].Son)				//存在しているエネミーなら
			{
				En[i].y -= WorldY;		//Y方向にスクロールした分エネミーをずらす
			}
		for(i = 0;i < SHOT_MAX;i++)	//弾の数だけループ
			if(Shot[i].Son)			//弾が存在するなら
			{
				Shot[i].y -= WorldY;	//スクロールした分弾をずらす
			}
		for(i = 0;i < EF_MAX;i++)	//エフェクトの数だけループ
			if(EF[i].Son)				//エフェクトが存在するなら
				EF[i].y -= WorldY;			//スクロールした分ずらす
		for(i = 0;i < OBJ_MAX;i++)	//オブジェの数だけループ
			if(Obj[i].Son)				//オブジェが存在するなら
				Obj[i].y -= WorldY;			//スクロールした分オブジェをずらす
	}

}	
//■――――――――――――――――――――――――――――――――――――――――――――――――――――
void ChrXScroll()	//機能：画面がX方向にスクロールしたときにキャラなどをずらす関数
{
	int i;	//カウンタ

	//⇔スクロール時にずらすもの(X方向
	if(WorldX)	//X方向にスクロールしたなら
	{
		for(i = 2;i >= 0;i--)		//残像の数だけ繰り返す
			Dum[i].x -= WorldX;			//プレイヤーの残像をX方向にスクロールした分ずらす

		if(Swd.Son)					//剣が存在し、刺さっていたら
			Swd.x -= WorldX;			//X方向に剣をスクロールした分ずらす
		for(i = 0;i < ENE_MAX;i++)	//敵の数だけループ
			if(En[i].Son)				//存在しているエネミーなら
				En[i].x -= WorldX;			//X方向にスクロールした分敵をずらす
		for(i = 0;i < SHOT_MAX;i++)	//弾の数だけループ
			if(Shot[i].Son)				//弾が存在するなら
				Shot[i].x -= WorldX;		//X方向にスクロールした分弾をずらす
		for(i = 0;i < EF_MAX;i++)	//エフェクトの数だけループ
			if(EF[i].Son)				//存在しているエフェクトなら
				EF[i].x -= WorldX;		//X方向にスクロールした分エフェクトをずらす
		for(i = 0;i < OBJ_MAX;i++)	//オブジェクトの数だけループ
			if(Obj[i].Son)				//存在しているオブジェなら
				Obj[i].x -= WorldX;		//x方向にスクロールした分オブジェをずらす
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――
