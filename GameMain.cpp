/// インクルード ///
#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "Extern.h"		//外部変数を扱うヘッダ
#include "BltProc.h"	//描画関数をまとめたヘッダ
#include "DebugProc.h"	//デバック用関数をまとめたヘッダ

#include "BackProc.h"		//背景処理の関数のプロトタイプ宣言のヘッダ
#include "StageEventProc.h"	//各ステージのイベントを扱う関数のヘッダ
#include "GameBltProc.h"	//キャラの描画などの関数のプロトタイプ宣言のヘッダ
#include "GameCheckProc.h"	//判定関数などのプロトタイプ宣言のヘッダ
#include "MapProc.h"		//マップ関連の関数のプロトタイプ宣言のヘッダ
#include "GameChrActProc.h"	//キャラアクション関数などのプロトタイプ宣言のヘッダ
#include "EnemyAct.h"		//エネミーアクション関数のプロトタイプ宣言のヘッダ

/*--------------------------------------------------------------------------
	ゲームのメイン処理
--------------------------------------------------------------------------*/
void	GameMain(int *pGameNum)	//ゲーム本編の関数
//●引数１：ゲームの場面を扱う値
{
	//▼内部変数宣言▼
	HDC hdc;			//デバイスコンテキスト
	DDBLTFX ddbltfx;	//ぬりつぶしに必要な構造体
	char str[256];		//文字列を扱う

	HPEN hPen;			//作成したペンを扱う
	HPEN hPenOld;		//古いペンを保存する

	int i,j;			//カウンタ
	int HitWaza;		//プレイヤーがエネミーに当てた技をを扱う
	static int Tengen;	//プレイヤー残像の点滅するのに使用
	int RndNum;			//乱数を扱う変数
	static int DamageEneNum = -1;	//ダメージを受けたエネミーの番号を入れておく変数

	
	//▼ゲームのデータ処理▼

	WorldX = 0;	//スクロール量を毎回０に戻す
	WorldY = 0;

	Tengen++;	//毎回＋して０と１を繰り返す(キャラ点滅などで使う）
	Tengen %= 2;

	if(Muteki > 0)
	{
		Muteki--;
		if(Muteki == 0)	Plr.HitD = 0;
	}

	for(i = 2;i > 0;i--)	//Plrをコピーして残像を作る。
		Dum[i] = Dum[i-1];
	Dum[0] = Plr;


	Plr.Atk = Swd.Hp>>2;	//プレイヤーの攻撃力は剣のHpで決まる


	//適がエリア外に出たら敵を消す
	for(i = 0;i < ENE_MAX;i++)	//エネミーの数だけ繰り返す
	{
		if(En[i].Son)	//エネミーが存在したら
		{			
			if(En[i].x+En[i].w + WMoveX +32 > ((MapXnum)*TIP_W) || En[i].x+WMoveX < 1+32
			|| En[i].y+En[i].h + WMoveY +32 > ((MapYnum)*TIP_H) || En[i].y+WMoveY < 1+32)	//ステージ範囲外（余分に32ピクセル＋）にでたら
			{
				En[i].Son = FALSE;	//エネミーを消す
			}
		}
	}

	//エリア外にでたら剣を刺す
	if(Swd.Son)	//剣が存在するなら
	{

		if(Swd.x+Swd.w + WMoveX + 32 > ((MapXnum)*TIP_W) || Swd.x+WMoveX < 1 +32
		|| Swd.y+Swd.h + WMoveY + 32 > ((MapYnum)*TIP_H) || Swd.y+WMoveY < 1 +32)	//ステージ範囲外（余分に縦横32ピクセル＋）に出たら
		{
			Swd.HitA = TRUE;
		}
	}

	//▼エネミー出現
	EnemyOnPos();	//エネミーを指定の場所に出現させる


	//▼キャラアクション
	if(Plr.Son)					//プレイヤーが存在するなら
		PlrAction(&Plr,&Anime[Plr.AniType][Plr.AniNum]);	//プレイヤーアクションの関数
	if(Swd.Son && !Swd.HitA)	//剣が存在し刺さっていなかったら
		SwdAction(&Swd,&AniSwd[Swd.AniType][Swd.AniNum]);	//剣のアクション関数
	EnAction();		//エネミーアクション関数



	if(CmdGet == 0)	//コマンドを入力したら
		Plr.y = 50;

	//▽弾の移動
	ShotMove(0,0);	//弾の移動

	//▽エフェクトのアニメーション＆消去
	EFOFF(EF);	//存在しているエフェクトのアニメーションと存在を扱う関数

	//▼▼▼▼▼▼▼　判定など　▼▼▼▼▼▼▼


	if(!Plr.HitD && !Muteki)
	{
		for(i = 0;i < ENE_MAX;i++)	//エネミーの数だけ繰り返す
		{
			if(En[i].Son && Plr.Son)	//判定を行うキャラ同士が存在したら
			{
				ChrHitChk(&Plr,&En[i]);		//プレイヤーと敵の当たり判定
				if(Plr.HitD)	break;		//攻撃を受けたらTRUE（ループ終了
			}
		}
	}	

	for(i = 0;i < SHOT_MAX;i++)	//弾の最大数分繰り返す
	{
		if((Shot[i].Son == 1 || Shot[i].Son == 3) && (!Plr.HitD && !Muteki))	//弾の存在が１なら弾とプレイヤーの判定
		{
			ShotHitChk(&Shot[i],&Plr);			//弾とプレイヤーの当たり判定
			if(Plr.HitD)	break;				//一発当たれば抜ける
		}
	}


	//プレイヤーの攻撃範囲とエネミーのあたり判定
	for(i = 0;i < ENE_MAX;i++)	//エネミーの数だけ繰り返す
	{
		if(En[i].Son && Plr.Son)	//判定を行うキャラ同士が存在したら
		{
			if(En[i].HitD == 0)
			{
				HitWaza = AtkHitChk(&Plr,&En[i]);	//○プレイヤーの攻撃と敵の当たり判定

				if(!HitWaza)	//HitWazaが０なら上の攻撃の判定を優先（同時に弾と攻撃の当り判定を行わないように
				{
					for(j = 0;j < SHOT_MAX;j++)				//弾の最大数分繰り返す
					{	
						if(Shot[j].Son == 2 || Shot[j].Son == 3)					//弾の存在が２なら弾と適の判定
						{
							HitWaza = ShotHitChk(&Shot[j],&En[i]);	//○弾の適の当たり判定
							if(En[i].HitD)	break;	//一発当たれば判定は終了
						}
					}
				}
				if(HitWaza)	DamageEneNum = i;		//ダメージを受けたエネミーの番号を代入（エネミーのHP表示等に使用
				if(!En[i].Son) DamageEneNum = -1;	//この番号の適が出現時にゲージが表示されないように、死んだら表示しない
			}

			if(!(En[i].Son))					//プレイヤーとの当たり判定後エネミーが存在してなかったら(倒したら
			{	
				//適が死ぬと同時に紫の光を出現させる
				for(j = 0;j < EnemyNum[En[i].Type].Hp ;j++)	//死ぬエネミーの種類のMAXHPの数だけ魂を出現させる
					ShotFire(En[i].x+(rand()%En[i].w)-4,En[i].y+(rand()%En[i].h)-4,0,17,1);

				if(HitWaza == 1)		//当てた攻撃が横斬りなら
					En[i].Hp = -99;			//エネミーHpを操作して、敵のやられる絵を変える
				else if(HitWaza == 2)	//当てた攻撃が縦斬りなら
					En[i].Hp = -199;		//エネミーHpを操作して、敵のやられる絵を変える
			}
		}
	}

	StageEvent();	//●各ステージのイベント関数

	//▼背景の地面のスクロール
	BGScrX += (double)WorldX/10;	//スクロール量にと比例して背景のスクロール速度変化させる

	//▼X方向スクロール
	ChrXScroll();		//X方向のスクロール
	WMoveX += WorldX;	//マップのスクロール値に今回のXスクロール量を足す

	//▼マップのキャラの当たり判定
	if(Plr.Son)	MapChk(&Plr);				//プレイヤーとマップの当たり判定
	
	if(Swd.Son && !Swd.HitA)				//剣が存在し、壁に当たってなかったら
		MapChk(&Swd);							//剣とマップの当たり判定

	for(i = 0;i < ENE_MAX;i++)				//エネミーが存在したらマップと当たり判定
		if(En[i].Son && En[i].Type != 3 && En[i].Type != 10)
			MapChk(&En[i]);			//エネミーとマップの当たり判定


	if(Plr.Hp < 1 && Plr.AniType == 8)		//Hpが１よりちいさかったら
		*pGameNum = 2;



	//▼▼▼▼▼▼▼ 描画 ▼▼▼▼▼▼
	//ぬりつぶし（黒）
	ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
	ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);

	BGBlt();					//●背景表示
	MapBitBlt();				//●マップを表示

	if(!(Plr.Son))	//プレイヤーが存在しなくなったら
	{
		for(i = 0;i < ENE_MAX;i++)	//敵キャラを全部存在させなくする
		{
			En[i].Son = FALSE;			//存在をFALSEに
		}
		//背景を真っ黒にする
		ddbltfx.dwSize = sizeof(ddbltfx);
		ddbltfx.dwFillColor = 0;			//パレット０番で
		lpDDSBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
	}


	//キャラの残像を表示
	if(Plr.Son || Plr.AniType == 8)	//プレイヤーが存在するか、やられているアニメーションをしている場合のみ表示
	{
		for(i = 2;i >= 0;i--)	//残像の数だけ繰り返す
		{
			//●残像表示
			if(Tengen)	//点滅フラグが１の時だけ表示
				ChrBitBlt(&Dum[i],&Anime[Dum[i].AniType][0],CharAnime(&Dum[i],&Anime[Dum[i].AniType][Dum[i].AniNum-1],&Anime[Dum[i].AniType][Dum[i].AniNum]));		//プレイヤー表示
		}

		//●プレイヤー表示
		if(!Muteki)	//無敵時間じゃないなら
		{
			ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//プレイヤー表示
		}else if(Tengen)	//無敵時間内なら
			ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//プレイヤー表示

	}

	//剣表示
	if(Swd.Son)	//剣が存在したら
		SwdBitBlt(&Swd,&AniSwd[Swd.AniType][0],CharAnime(&Swd,&AniSwd[Swd.AniType][Swd.AniNum],&AniSwd[Swd.AniType][Swd.AniNum+1]));		//剣表示

	//オブジェクト表示
	for(i = 0;i < OBJ_MAX;i++)
		OBJBitBlt(&Obj[i]);	//オブジェ表示関数実行

	//●敵表示
	for(i = 0;i < ENE_MAX;i++)	//敵の数だけ繰り返す
	{

		if(En[i].Son)		//敵[i]が存在したら
		{
			/*
			if(Tengen)
			{
				if(En[i].HitD == 1)		//横斬りダメージをうけているなら
					DamageX_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//エネミー表示
				else if(En[i].HitD == 2)	//縦斬りでダメージをうけているなら
					DamageY_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//エネミー表示			
			}*/	
			//if(!En[i].HitD)	//通常どうりなら
				ChrBitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//エネミー表示
			//else if(Tengen)	//ダメージを受けているなら
				//ChrBitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//エネミー表示
		}

		if(!En[i].Son && Tengen && En[i].Hp < 0)	//敵が存在していなくて、点滅フラグが１で、体力が０より小さかったら(やられる時にエネミーのHPは-99か-199になる
		{
			En[i].Hp ++;	//０になるまで毎回＋（Hpを使ってエネミーのが切れる動きを扱う
			if(En[i].Hp > -100 && En[i].Hp <= -75)	//Hpの値を使ってエネミーのやられ方を分ける
			{ 	//キャラが横に切れる絵を表示
				Kill_X_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],En[i].AniNum,En[i].Hp+100);	//エネミーやられ表示
				if(En[i].Hp >= -75)	En[i].Hp = 0;	//-75より大きくなったらHpを０に	
			}else if(En[i].Hp > -200 && En[i].Hp <= -175)
			{	//キャラが縦に切れる絵を表示
				Kill_Y_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],En[i].AniNum,En[i].Hp+200);	//エネミーやられ表示
				if(En[i].Hp >= -175) En[i].Hp = 0;	//-175より大きくなったらHpを０に
			}
		}
	}

	for(i = 0;i < SHOT_MAX;i++)	//弾の数だけ繰り返す
		ShotBitBlt(&Shot[i]);		//●弾表示
	for(i = 0;i < EF_MAX;i++)	//エフェクトの数だけ繰り返す
		EFBitBlt(&EF[i]);			//●エフェクト表示
	
	PlrHpBlt();						//●プレイヤーのHPを表示
	if(DamageEneNum >= 0)	EneHpBlt(&En[DamageEneNum]);	//●ダメージを受けたエネミーのHPを表示

	//描画を行うサーフェースのデバイスコンテキストを取得
	lpDDSBackBuffer->GetDC(&hdc);


	//▼テキスト表示▼
	

	//プレイヤーの攻撃当たり判定の範囲を表す線の設定
	hPen = CreatePen(PS_SOLID,1,RGB(0,255,0));	//点線、太さ１,緑色のペンを作成し、hPenに保存
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。
	
	//プレイヤーの攻撃範囲を表す四角を描画
	if(Plr.HitA)	//プレイヤー攻撃中の当たり判定部分を表示
	{
		MoveToEx(hdc,xbox,ybox,NULL);
		LineTo(hdc,xbox+wbox,ybox);
		LineTo(hdc,xbox+wbox,ybox+hbox);
		LineTo(hdc,xbox,ybox+hbox);
		LineTo(hdc,xbox,ybox);
	}

	SelectObject(hdc,hPenOld);		//ペンを元に戻す
	DeleteObject(hPen);				//作成したペンの削除

	//○剣の破片を表示
	RndNum = rand()%255;

	if(Plr.AniType == 19)	//プレイヤーが剣破片吸収アニメなら	
		hPen = CreatePen(PS_SOLID,rand()%7+2,RGB(255,RndNum,RndNum));	//点線、太さ１,緑色のペンを作成し、hPenに保存
	else					//そうじゃないなら
		hPen = CreatePen(PS_SOLID,rand()&5,RGB(255,RndNum,255));
	hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。

	for(i = 0;i < SHOT_MAX; i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)
		{
			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);
		}
	}

	SelectObject(hdc,hPenOld);		//ペンを元に戻す
	DeleteObject(hPen);				//作成したペンの削除

	//文字表示
	SetBkColor(hdc,RGB(255,0,0));			//文字のバックカラーの指定
	SetTextColor(hdc,RGB(255,255,255));		//文字色の指定
	SetBkMode(hdc,TRANSPARENT);				//文字を透明にする
/*
	
	wsprintf(str,"Nage = %d",Nage);
	TextOut(hdc,100,140,str,lstrlen(str));

	wsprintf(str,"%d",BtnCnt);
	TextOut(hdc,200,150,str,lstrlen(str));


	//WMoveX表示(スクロールした量）
	wsprintf(str,"WMoveX [%d]  WMove [%d]",WMoveX,WMoveY);
	TextOut(hdc,320,5,str,lstrlen(str));

	//プレイヤーHp表示
	wsprintf(str,"Hp %d    ",Plr.Hp);
	TextOut(hdc,Plr.x,Plr.y-15,str,lstrlen(str));

	//エネミーHp表示
	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Son)
		{
			wsprintf(str,"Hp %d    ",En[i].Hp);
			TextOut(hdc,En[i].x,En[i].y-12,str,lstrlen(str));
		}
	}

	wsprintf(str,"EneMax %d:%d:%d:%d",EneOnPos_Max.x,EneOnPos_Max.y,EneOnPos_Max.type,EneOnPos_Max.OnFlag); 
	TextOut(hdc,240,200,str,lstrlen(str));

	//wsprintf(str,"Eneon %d:%d:%d:%d",pEneOn[0].x,pEneOn[0].y,pEneOn[0].type,pEneOn[0].OnFlag); 
	//TextOut(hdc,240,200,str,lstrlen(str));


	wsprintf(str,"%d  :waza = %d",AllCnt,CmdGet);
	TextOut(hdc,100,80,str,lstrlen(str));
*/

	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);
	//DrawFrameRate(lpDDSBackBuffer,0,0);					//フレームレートを表示する関数

}