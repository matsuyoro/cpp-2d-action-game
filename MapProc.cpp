
#include "Extern.h"		//外部変数のヘッダ
#include "GameStruct.h"	//構造体の型の定義のヘッダ

#include "GameCheckProc.h"	//判定関数などのプロトタイプ宣言
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void MapChk(CHR_DATA *pC)	//機能：配列マップとキャラの当たり判定
//●引数１：マップと当たり判定するCHR_DATA型構造体
{
	int left,top,right,bottom;			//４つ点を代入しておく変数
	int centerX[10],centerY[10];		//角と角の点の間の点を扱う配列(３２０＊３２０のサイズキャラまで対応）
	int Hx,Hy,Hw,Hh;					//当たり判定の部分のを扱う
	int i;								//カウンタ

	pC->Land = 0;		//地面に足が着いているか判定するためにまずは着いてないことにする				

	//①X方向の移動

	if((pC->MoveChkX != pC->x) || WorldX)	//X方向に キャラが動いたらまたはスクロールしたら
	{
		Hx = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//当たり判定部分の左上x座標
		Hy = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//当たり判定部分の左上y座標
		Hw = pC->Hit.w;								//当たり判定部分の幅
		Hh = pC->Hit.h;								//当たり判定部分の高さ
		//判定前にデータを更新
		left = (Hx+WMoveX)/TIP_W;
		top = (Hy+WMoveY)/TIP_H;
		right = (Hx+WMoveX+Hw-1)/TIP_W;
		bottom = (Hy+WMoveY+Hh-1)/TIP_H;
	
		//キャラのサイズにあわせて当たり判定の点の数を計算する。
		for(i = 0;i < (Hw/TIP_W);i++)		//キャラ幅 / チップ幅の数だけ繰り返す
			centerX[i] = (Hx+WMoveX+((Hw/(Hw/TIP_W+1))*(i+1))-1)/TIP_W;	//角の点と点の間の点を計算で点を扱う配列に代入
		for(i = 0;i < (Hh/TIP_H);i++)		//キャラ高さ / チップ高さの数だけ繰り返す
			centerY[i] = (Hy+WMoveY+((Hh/(Hh/TIP_H+1))*(i+1))-1)/TIP_H;	//角の点と点の間の点を計算で点を扱う配列に代入
	
		//②X方向の判定
		if(Tip[pMap[(top*MapXnum)+left]] == 1)		//左上
		{
			Hx = (left+1)*TIP_W-WMoveX;		//当たっていたら、当たったチップの１つ右に移動
			pC->Land = 3;
		}
		if(Tip[pMap[(top*MapXnum)+right]] == 1)		//右上
		{
			Hx = right*TIP_W-Hw-WMoveX;		//当たっていたら、当たったチップのキャラ1人分左へ移動
			pC->Land = 4;
		}
		if(Tip[pMap[(bottom*MapXnum)+left]] == 1)	//左下
		{
			Hx = (left+1)*TIP_W-WMoveX;		//当たっていたら、当たったチップの１つ右に移動
			pC->Land = 3;
		}
		if(Tip[pMap[(bottom*MapXnum)+right]] == 1)	//右下
		{
			Hx = right*TIP_W-Hw-WMoveX;		//当たっていたら、当たったチップのキャラ1人分左へ移動
			pC->Land = 4;
		}
		for(i = 0;i < (Hw/TIP_W);i++)		//centerXの点を扱う配列をすべて判定
		{
			if(Tip[pMap[(top*MapXnum)+centerX[i]]] == 1)		//中央上
			{
				Hx = (centerX[i]+1)*TIP_W-WMoveX;		//チップの右に移動
				pC->Land = 3;
			}
			if(Tip[pMap[(bottom*MapXnum)+centerX[i]]] == 1)	//中央下
			{
				Hx = centerX[i]*TIP_W-Hw-WMoveX;		//チップの左に移動
				pC->Land = 4;
			}
		}

		for(i = 0;i < (Hh/TIP_H);i++)		//centerYの点を扱う配列をすべて判定
		{
			if(Tip[pMap[(centerY[i]*MapXnum)+left]] == 1)		//中央左
			{
				Hx = (left+1)*TIP_W-WMoveX;			//チップの右に移動
				pC->Land = 3;
			}
			if(Tip[pMap[(centerY[i]*MapXnum)+right]] == 1)	//中央右
			{
				Hx = right*TIP_W-Hw-WMoveX;			//チップの左に移動
				pC->Land = 4;
			}
		}
		pC->x = Hx+(Hw>>1)-(pC->w>>1);	//マップと当たり判定して移動した結果のデータをキャラｘ座標に代入
	}
	//③y方向の移動
	if(pC->Type != -2)	//キャラの種類が-2（剣）じゃないなら
		UpDownChk(pC);	//上昇、下降などのｙ方向の移動
	
	if(pC->Type == -1 && Swd.Son && Swd.HitA)	//キャラの種類が-1（プレイヤー）なら
		PlrSwdChk(pC,&Swd);	//プレイヤーと剣の当たり判定


	if(pC->MoveChkY != pC->y || WorldY)	//Y方向に キャラが動いたらまたはスクロールしたら
	{
	//Y方向のマップチップとのあたり判定
		Hx = pC->x + (pC->w>>1) - (pC->Hit.w>>1);				//当たり判定部分の左上x座標
		Hy = pC->y + (pC->h>>1) - (pC->Hit.h>>1);				//当たり判定部分の左上y座標
		Hw = pC->Hit.w;						//当たり判定部分の幅
		Hh = pC->Hit.h;						//当たり判定部分の高さ

		//判定前にデータを更新
		left = (Hx+WMoveX)/TIP_W;
		top = (Hy+WMoveY)/TIP_H;
		right = (Hx+WMoveX+Hw-1)/TIP_W;
		bottom = (Hy+WMoveY+Hh-1)/TIP_H;
	
		for(i = 0;i < (Hw/TIP_W);i++)	//キャラ幅 * チップ幅の数だけ繰り返す
			centerX[i] = (Hx+WMoveX+((Hw/(Hw/TIP_W+1))*(i+1))-1)/TIP_W;	//角の点と点の間の点を計算で点を扱う配列に代入
		for(i = 0;i < (Hh/TIP_H);i++)	//キャラ高さ * チップ高さの数だけ繰り返す
			centerY[i] = (Hy+WMoveY+((Hh/(Hh/TIP_H+1))*(i+1))-1)/TIP_H;	//角の点と点の間の点を計算で点を扱う配列に代入
	
		//④y方向の判定
		if(Tip[pMap[(top*MapXnum)+left]] == 1)		//左
		{
			Hy = (top+1)*TIP_H-WMoveY;		//当たっていたら、当たったチップの１つ下に移動
			pC->Land = 2;					//天井に当たったので２
		}
		if(Tip[pMap[(top*MapXnum)+right]] == 1)	//右上
		{
			Hy = (top+1)*TIP_H-WMoveY;		//当たっていたら、当たったチップの１つ下に移動
			pC->Land = 2;					//天井に当たったので２
		}
		if(Tip[pMap[(bottom*MapXnum)+left]] == 1)	//左下
		{
			Hy = bottom*TIP_H-Hh-WMoveY;		//当たっていたら、当たったチップのキャラ1人分上へ移動
			pC->Land = 1;						//地面に足が着いたので１
		}

		if(Tip[pMap[(bottom*MapXnum)+right]] == 1)	//右下
		{
			Hy = bottom*TIP_H-Hh-WMoveY;		//当たっていたら、当たったチップのキャラ1人分上へ移動
			pC->Land = 1;
		}
		for(i = 0;i < (Hh/TIP_H);i++)		//centerYの点を扱う配列をすべて判定
		{
			if(Tip[pMap[(centerY[i]*MapXnum)+left]] == 1)		//左中央
			{
				Hy = (centerY[i]+1)*TIP_H-WMoveY;		//チップの下に戻す
				pC->Land = 2;
			}
			if(Tip[pMap[(centerY[i]*MapXnum)+right]] == 1)	//右中央
			{
				Hy = centerY[i]*TIP_H-Hh-WMoveY;		//チップの上に戻す
				pC->Land = 1;
			}
		}
		for(i = 0;i < (Hw/TIP_W);i++)		//centerXの点を扱う配列をすべて判定
		{
			if(Tip[pMap[(bottom*MapXnum)+centerX[i]]] == 1)	//下中央
			{
				Hy = bottom*TIP_H-Hh-WMoveY;			//チップの上に戻す
				pC->Land = 1;
			}	
			if(Tip[pMap[(top*MapXnum)+centerX[i]]] ==1)		//上中央
			{
				Hy = (top+1)*TIP_H-WMoveY;				//チップの下に戻す
				pC->Land = 2;
			}
		}
		pC->y = Hy+(Hh>>1)-(pC->h>>1);	//マップと当たり判定して移動した結果をキャラのｙ座標に代入
	}

	pC->MoveChkX = pC->x;		//次のこの関数を実行するときに必要なデータを保存
	pC->MoveChkY = pC->y;

	if(pC->Type != -2)	//引数のキャラが剣以外なら
	{
		if(pC->Land == 1 | pC->Land == 2)	//判定で地面か天井についていたら
		{
			pC->U = 0;	//重力による移動量を０に
		}
	}else	//剣なら
	{
		if(pC->Land)	//剣のメンバLandが０以外なら（マップに当たっているなら
		{
			pC->HitA = TRUE;	//剣がささったのでTRUEにする
			switch(pC->Land)
			{
			case 1:	//下に刺さったら
				if(pC->muki == 4)	
					pC->y += 20;	//剣を下にずらして刺す
				break;
			case 2:	//上に刺さったら
				if(pC->muki == 2)
					pC->y -= 20;	//剣を上にずらして刺す
				break;
			case 3:	//左に刺さったら
				if(pC->muki == 1)
					pC->x -= 20;	//剣を左にずらして刺す
				break;
			case 4:	//右に刺さったら
				if(pC->muki == 3)
					pC->x += 20;	//剣を右にずらして刺す
				break;
			}
		}
	}
}