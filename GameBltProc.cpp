#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"		//構造体の型の定義のヘッダファイル
#include "Extern.h"			//外部変数のヘッダファイル
#include "BltProc.h"		//描画関数のヘッダ

#include "GameBltProc.h"
#include "GameCheckProc.h"
//■――――――――――――――――――――――――――――――――――――――――――――――――――
void ChrBitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//機能：キャラを表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y+pC->h-pA->h;					//アニメの絵の高さが同じでなくても足もとはそろえるようにY座標を計算
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;								//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//転送元上Y座標を計算しておく

	MyBltFast(	Bx,By,								//表示先XY座標
				pA->Bmp,							//表示する絵のオフスクリーンサーフェース
				SurL,	SurT,						//転送元左上XY座標
				SurL + pA->w,	SurT + pA->h	);	//転送元右下XY座標
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――
void SwdBitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//機能：剣を表示する関数
//●引数１：表示する剣の構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x + (pC->w>>1) - (pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y + (pC->h>>1) - (pA->h>>1);		//〃（ｙ座標用
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;					//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h;					//転送元上Y座標を計算しておく
		
	MyBltFast(	Bx,By,						//表示先XY座標
				pA->Bmp,					//表示する絵のオフスクリーンサーフェース
				SurL,		//転送元左上X座標
				SurT,		//転送元左上Y座標
				SurL + pA->w,	SurT + pA->h	);	//転送元右下XY座標

}
//■――――――――――――――――――――――――――――――――――――――――――――――――――
void DamageX_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//機能：横斬りでダメージをうける時の絵を表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int i;
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y + pC->h - pA->h;				//アニメの絵の高さが同じでなくても足もとはそろえるようにY座標を計算
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;								//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//転送元上Y座標を計算しておく

	for(i = 0;i < 3;i++)	//絵を３枚ずらして表示する
	{		
		MyBltFast(	Bx+(i<<3),By,	//表示先XY座標
				pA->Bmp,			//表示する絵のオフスクリーンサーフェース
				SurL,								//転送元左上X座標
				SurT,	//転送元左上Y座標
				SurL + pA->w,	SurT + pA->h	);							//転送元右下XY座標
	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――
void DamageY_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//機能：縦斬りでダメージを受けるときの絵を表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int i;
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y+pC->h-pA->h;				//アニメの絵の高さが同じでなくても足もとはそろえるようにY座標を計算
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;								//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//転送元上Y座標を計算しておく

	for(i = 0;i < 3;i++)	//絵を３枚ずらして表示させる
	{
		MyBltFast(	Bx,By+(i<<3),	//表示先XY座標
			pA->Bmp,				//表示する絵のオフスクリーンサーフェース
			SurL,								//転送元左上X座標
			SurT,								//転送元左上Y座標
			SurL + pA->w,	SurT + pA->h	);	//転送元右下XY座標
	}
}

//■――――――――――――――――――――――――――――――――――――――――――――――――――
void Kill_X_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni,int Cnt)	//機能：敵が横に切れる絵を表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y+pC->h-pA->h;				//アニメの絵の高さが同じでなくても足もとはそろえるようにY座標を計算
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;								//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//転送元上Y座標を計算しておく
	
	//２つ割れた絵の上部分の描画
	MyBltFast(Bx-(Cnt<<1),By,									//表示先XY座標
		pA->Bmp,												//表示する絵のオフスクリーンサーフェース
		SurL,									//転送元左上X座標
		SurT,		//転送元左上Y座標
		SurL + pA->w,	SurT + (pA->h>>1)	);							//転送元右下XY座標

	//２つに割れた絵の下部分の描画
	MyBltFast(Bx+(Cnt<<1),By+(pA->h>>1),				//表示先XY座標
		pA->Bmp,										//表示する絵のオフスクリーンサーフェース
		SurL,									//転送元左上X座標
		SurT + (pA->h>>1),						//転送元左上Y座標
		SurL + pA->w,	SurT+pA->h	);	//転送元右下XY座標
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――
void Kill_Y_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni,int Cnt)	//機能：敵が横に切れる絵を表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pC->y + pC->h - pA->h;					//アニメの絵の高さが同じでなくても足もとはそろえるようにY座標を計算
	int SurL,SurT;								//画像転送元サーフェースの左上XY座標を扱う

	BNum = 640/pA->w;		//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように
	SurL = (ChrAni%BNum) * pA->w;								//転送元左X座標を計算しておく
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//転送元上Y座標を計算しておく

	//２つに割れた絵の左の部分の描画
	MyBltFast(Bx,	By-(Cnt<<1),					//表示先XY座標
		pA->Bmp,								//表示する絵のオフスクリーンサーフェース
		SurL,									//転送元左上X座標
		SurT,									//転送元左上Y座標
		SurL + (pA->w>>1),	SurT + pA->h	);		//転送元右下XY座標

	//２つに割れた絵の右の部分の描画
	MyBltFast(Bx+(pA->w>>1),	By+(Cnt<<1),		//表示先XY座標
		pA->Bmp,								//表示する絵のオフスクリーンサーフェース
		SurL + (pA->w>>1),						//転送元左上X座標
		SurT,									//転送元左上Y座標
		SurL + pA->w,	SurT + pA->h	);		//転送元右下XY座標

}

//■――――――――――――――――――――――――――――――――――――――――――――――――――
/*void DumBitBlt(CHR_DATA *pChr,ANIME_DATA *pAni,int ChrAni)	//機能：キャラの残像を表示する関数
//●引数１：表示するキャラの構造体
//●引数２：アニメーションデータの構造体
//●引数３：アニメーション関数の戻値
{
	int BNum;	//読み込み先の絵の横一列に並べられている絵の枚数を求める
	int Bx = pChr->x+(pChr->w>>1)-(pAni->w>>1);		//アニメーションの画像を表示する場所をキャラの中央にするための変数
	int By = pChr->y+pChr->h-pAni->h;		//〃（ｙ座標用
	BNum = 640/pAni->w;				//絵の読み込み先を横に並べすぎないように640を超えたら次の行にいくように

	BitBlt(hMemDC,Bx,By,pAni->w,pAni->h,
		pAni->Bmp,(ChrAni%BNum)*pAni->w,(ChrAni/BNum)*pAni->h+(pChr->muki*pAni->h*pAni->ynum),SRCPAINT);	//仮想画面にキャラを描画

}プレイヤーと同じ描画方法で使用*/
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――
void ShotBitBlt(SHOT_DATA *pS)	//機能：弾を表示する関数
//●引数１：表示する弾のデータ
{
	int SBmpX;	//画像元のX座標を扱う 


	if(pS->Son)	//弾が存在するなら
	{
		if(pS->mx >= 0)	//移動量が0以上なら
			SBmpX = pS->bx + (pS->w * pS->AniCnt) + (pS->w * (pS->AniMax+1));	//画像元X座標を計算
		else			//移動量が0より小さいなら
			SBmpX = pS->bx + (pS->w * pS->AniCnt);

		pS->AniCnt++;	//アニメーション表示のカウント
		if(pS->AniCnt > pS->AniMax)	pS->AniCnt = 0;	//アニメーションを最後まで表示したらまた０に戻る
		
		if(pS->Type != 20)
		{
			MyBltFast(pS->x,pS->y,				//表示先XY座標
			lpDDSOff_Shot,						//表示する絵のオフスクリーンサーフェース
			SBmpX,	pS->by,						//転送元左上XY座標
			SBmpX + pS->w,	pS->by + pS->h);	//転送元右下XY座標
		}
	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void EFBitBlt(EF_DATA *pE)	//機能：エフェクトを表示する関数
//●引数１：表示するエフェクトの構造体
{
	int SurL;	//画像転送元サーフェースの左X座標を格納しておく変数
	if(pE->Son)	//エフェクトが存在するなら
	{
		SurL = pE->bx+(pE->w*pE->AniCnt);	//転送元左X座標を計算して保存（2回以上使用するので
	
		//描画
		MyBltFast(	pE->x,pE->y,						//表示先XY座標
					lpDDSOff_EF,						//表示する絵のオフスクリーンサーフェース
					SurL,	pE->by,						//転送元左上XY座標
					SurL + pE->w,	pE->by + pE->h);		//転送元右下XY座標

	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void OBJBitBlt(OBJ_DATA *pO)	//機能：オブジェクトを表示する関数
//●引数１：表示するオブジェクトの構造体
{
	int SurL;	//転送元サーフェースの左X座標を格納しておくための変数

	if(pO->Son)	//オブジェクトが存在するなら
	{
		SurL = pO->bx+(pO->w*pO->AniCnt);	//転送元左X座標を計算して保存
		//描画
		MyBltFast(	pO->x,pO->y,						//表示先XY座標
					lpDDSOff_OBJ,						//表示する絵のオフスクリーンサーフェース
					SurL,	pO->by,	//転送元左上XY座標
					SurL + pO->w,	pO->by + pO->h);		//転送元右下XY座標

	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void BgObjBlt(BGOBJ_DATA *pO)	//機能：オブジェクトを表示する関数
//●引数１：表示するオブジェクトの構造体
{
	int SurL;	//転送元サーフェースの左X座標を格納しておくための変数
//	int AniSpd;	//アニメーションスピードを変化させて扱う

	if(pO->Son)	//オブジェクトが存在するなら
	{
		pO->AniCnt++;	//アニメーション表示のカウント
		if(pO->AniCnt > pO->AniMax)	pO->AniCnt = 0;	//アニメーションを最後まで表示したらまた０に戻る
		
		SurL = pO->bx+(pO->w*pO->AniCnt);	//転送元左X座標を計算して保存

		//描画
		MyBltFast(	pO->x,pO->y,						//表示先XY座標
					lpDDSOff_Back1_OBJ,						//表示する絵のオフスクリーンサーフェース
					SurL,	pO->by,	//転送元左上XY座標
					SurL + pO->w,	pO->by + pO->h);		//転送元右下XY座標

	}
}
//■――――――――――――――――――――――――――――――――――――――――――――――――
void PlrHpBlt()	//機能：プレイヤーのHPを表示
{
	static int PGAcnt;	//HPゲージの炎のアニメーションカウンタ
	static int SAcnt;	//剣のアニメのカウンタ
	
	static int SlowHp;

	if(Plr.Hp < SlowHp)	SlowHp --;
	else	SlowHp = Plr.Hp;

	PGAcnt ++;
	PGAcnt %= 5;
	SAcnt ++;
	SAcnt %= 12;

	//HPゲージの枠
	MyBltFast(	0,457,
				lpDDSOff_Text,
				0,0,
				155,23);
	//HPゲージ
	MyBltFast(	29,460,	
			lpDDSOff_Text,
			0,23+PGAcnt*17,
			(int)(Plr.Hp * 124 / Plr.MaxHp),(23+PGAcnt*17)+17);
			//現在のHP * ゲージの最大 / HPの最大

	//剣ゲージ
	MyBltFast(0,472-(int)(Swd.Hp * 92 / Swd.MaxHp),
			lpDDSOff_Text,
			SAcnt*24,112,
			(SAcnt*24)+24,112+(int)(Swd.Hp * 92 / Swd.MaxHp));

}
//■――――――――――――――――――――――――――――――――――――――――――――――――
void EneHpBlt(CHR_DATA *pC)	//機能：エネミーのHPを表示する関数
//●引数１：エネミーのキャラデータ
{
	if(pC->Son)	//指定のエネミーが存在するなら
	{
		//2度以上使うので先に計算して代入
		int Blt_x = pC->x+(pC->w>>1)-32;	//表示位置X
		int Blt_y = pC->y-16;			//表示位置Y

		//枠
		MyBltFast(	Blt_x,Blt_y,
					lpDDSOff_Text,
					160,0,
					224,8);
		//ゲージ
		MyBltFast(	Blt_x+2,Blt_y+2,
					lpDDSOff_Text,
					162,12,
					162+(int)(pC->Hp * 60 / pC->MaxHp),16);
	}				
}
//■――――――――――――――――――――――――――――――――――――――――――――――――
void MapBitBlt()		//機能：マップを表示する関数
{
	int Xmap = WMoveX/TIP_W;	//ループ内で変わらない値は代入しておく
	int Ymap = WMoveY/TIP_H;
	int SurL,SurT;				//画像転送元サーフェースの左端と上端を保存しておく変数（2回以上同じ計算をするから
	static int MapAni;
	

	MapAni += (rand()%2);
	MapAni %= 2;

	for(y = 0;y <= WINMAP_H;y++)	//マップ縦
	{
		if((y + WMoveY / TIP_H) >= MapYnum) break;	//これから使う要素番号が配列の要素数をオーバーしていたらbreak
		for(x = 0;x <= WINMAP_W;x++)	//マップ横
		{
			if((x + WMoveX / TIP_W) >= MapXnum) break;	//これから使う要素番号が配列の要素数をオーバーしていたらbreak

			if(Tip[pMap[((y+Ymap)*MapXnum)+(x+Xmap)]])	//チップの種類がTRUEなら絵を表示
			{	//↑※pMapのデータを調べる時は　pMap[(行 * 列の長さ) + 現在の列の位置)]
				

				SurL = pMap[((y+Ymap)*MapXnum) +(x+Xmap)] % BMPTIP_W * TIP_W;	//転送元左端X座標
				SurT = pMap[((y+Ymap)*MapXnum) +(x+Xmap)] / BMPTIP_W * TIP_H;	//転送元上端Y座標

				if(Tip[pMap[((y+Ymap)*MapXnum)+(x+Xmap)]] == 3)
				{	//マップ表示
					MyBltFast(	x * TIP_W - WMoveX % TIP_W,				//表示先X座標
								y * TIP_H - WMoveY % TIP_H,				//表示先Y座標
								Return_lpDDSOff(),						//表示する絵のオフスクリーンサーフェースをステージによって変更するために関数の戻値を使う
								SurL+(MapAni*TIP_W),	SurT,							//転送元左上XY座標
								SurL + TIP_W + (MapAni*TIP_W),	SurT + TIP_H);			//転送元右下XY座標
				}else
				{	//マップ表示
					MyBltFast(	x * TIP_W - WMoveX % TIP_W,				//表示先X座標
								y * TIP_H - WMoveY % TIP_H,				//表示先Y座標
								Return_lpDDSOff(),						//表示する絵のオフスクリーンサーフェースをステージによって変更するために関数の戻値を使う
								SurL,	SurT,							//転送元左上XY座標
								SurL + TIP_W,	SurT + TIP_H);			//転送元右下XY座標
				}

			}
		}
	}
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
LPDIRECTDRAWSURFACE7 Return_lpDDSOff()	//機能：マップチップ画像のサーフェースをステージにあわせて戻す
{
	switch(StageNum)	//ステージによって分岐
	{
	case 0:
		return(lpDDSOff_MapTip);	//森のステージのサーフェースを戻す
		break;
	case 1:
		return(lpDDSOff_MapTip2);	//廃墟のステージのサーフェースを戻す
		break;
	case 2:
		return(lpDDSOff_MapTip2);	//砂漠基地ステージのサーフェースを戻す
		break;
	case 3:
		return(lpDDSOff_MapTip);	//嵐のステージのサーフェースを戻す
		break;
	case 4:
		return(lpDDSOff_MapTip3);	//メカのステージのサーフェースを戻す
	}
	MessageBox(NULL,"関数 Return_lpDDSOff()","エラー",MB_OK);					//エラーをメッセージボックスで表示
	return(FALSE);
}
/*
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void DIB_EF()		//機能：２４ビットDIB画像を操作する関数
{
	//内部変数宣言
	RGBTRIPLE *rgbt2;	//DIBの色データ部分の先頭アドレスをうけとる
	int x,y;			//DIBを１ドットずつ操作するためのカウンタ
	static int ycnt;	//１ラインずつピクセルを操作するために使用
	ycnt++;				//毎回一ラインずつ変化させる範囲を増やす
	
	if(ycnt < 350)		//ycntが350より小さい間なら
	{
		rgbt2 = rgbt;		//DIBのピクセルデータの先頭アドレスをコピーする
		for(y = 0;y < abs(BmpInfoH.biHeight);y++)
		{
			for(x = 0;x < abs(BmpInfoH.biWidth);x++)
			{
				if(rgbt2->rgbtRed < 255)	rgbt2->rgbtRed++;
				if(rgbt2->rgbtGreen < 255)	rgbt2->rgbtGreen++;
				if(rgbt2->rgbtBlue < 255)	rgbt2->rgbtBlue++;

				rgbt2++;	//次のピクセルへ
			}
			if(y > ycnt)	break;	//ループをぬける
		}
	}
}
*/