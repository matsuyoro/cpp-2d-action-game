#include <windows.h>
#include <ddraw.h>
#include "Extern.h"
#include "BltProc.h"

#include "GameBltProc.h"

//■　GameStop　■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void GameStop(int *pGameNum)	//	機能：ポーズ画面の処理
//	●引数：ゲームの場面を扱う値
{
	HDC hdc;				//デバイスコンテキスト
	char str[256];			//文字列を扱う
	DDBLTFX ddbltfx;		//ぬりつぶしに必要な構造体
	static int PouseAni;	//アニメーションカウンタ

	HFONT hFont;	//用意したフォントを扱う
	HFONT hFontOld;	//古いフォントを用意する


	if(rand()%5 == 1)	PouseAni++;
	PouseAni %= 7;

	//ぬりつぶし（黒）
	ddbltfx.dwSize = sizeof(ddbltfx);		//構造体のサイズを指定する
	ddbltfx.dwFillColor = 0;				//ぬりつぶす色を指定
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//指定の色でぬりつぶし
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);

	if(!(Btn2 & (1<<1)) && (Btn1 & (1<<1)))	//Bボタンを前回（離）で現在（押）なら 
	{
		*pGameNum = 1;	//間接参照でGameNumを１（ゲーム本編）にする。
	}

	//石の壁
	MyBltFast(	32,64,
				lpDDSOff_Pouse,
				0,64,
				576,480);
	//432,168
	MyBltFast(  464,168,
				lpDDSOff_Pouse,
				PouseAni*24,0,
				PouseAni*24+24,24);

	//ゲージを表示
	PlrHpBlt();

	//描画を行うサーフェースのデバイスコンテキストを取得
	lpDDSBackBuffer->GetDC(&hdc);


	hFont = CreateFont(				//フォントを用意する。
						32,			//文字高さ
						12,			//文字幅（０にすると、高さを元に自動で決定）
						60,			//角度
						0,			//ベースラインとx軸の角度
						FW_HEAVY,	//FW_REGULAR,	//フォントの太さ
						FALSE,		//イタリック体　の有無
						TRUE,		//アンダーライン　の有無
						FALSE,		//打ち消し線　の有無
						SHIFTJIS_CHARSET,			//文字セット
						OUT_DEFAULT_PRECIS,			//出力精度
						CLIP_DEFAULT_PRECIS,		//クリッピング精度
						PROOF_QUALITY,				//出力品質
						FIXED_PITCH | FF_MODERN,	//ピッチとファミリー
						"");					//書体名

	hFontOld = (HFONT)SelectObject(hdc,hFont);
	//hdcに、hFont(新しいフォント）を設定。この時、戻値として、以前のフォントを受け取っておく。

	//※hdcにTextOut()
	//文字表示

	for(int i = 0;i < 4;i++)
	{
		SetBkColor(hdc,RGB(255,0,0));			//文字のバックカラーの指定
		SetBkMode(hdc,TRANSPARENT);				//文字を透明にする

		SetTextColor(hdc,RGB(i*80,i*80,0));		//文字色変更
		wsprintf(str,"PAUSE");
		TextOut(hdc,200-(i<<1),450-(i<<1),str,lstrlen(str));

		SetTextColor(hdc,RGB(i*80,0,0));			//文字色変更
		
		wsprintf(str,"体　%d／%d",Plr.Hp,Plr.MaxHp);
		TextOut(hdc,100-(i<<1),140-(i<<1),str,lstrlen(str));
		wsprintf(str,"攻  %d",Plr.Atk);
		TextOut(hdc,100-(i<<1),180-(i<<1),str,lstrlen(str));
		wsprintf(str,"速　%d",Plr.Spd);
		TextOut(hdc,100-(i<<1),220-(i<<1),str,lstrlen(str));
		wsprintf(str,"剣　%d／%d",Swd.Hp,Swd.MaxHp);
		TextOut(hdc,100-(i<<1),280-(i<<1),str,lstrlen(str));
	}


	SelectObject(hdc,hFontOld);
	//hdcに、hFontOld(以前のフォント)を設定。（フォントを元に戻す）
	DeleteObject(hFont);	//いらなくなったフォントを削除



	//デバイスコンテキストの解放
	lpDDSBackBuffer->ReleaseDC(hdc);

}