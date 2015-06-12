#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void DrawText(LPDIRECTDRAWSURFACE7 lpDDS,int x,int y,char* text,int rcol,int gcol,int bcol)
//機能：テキストを表示する関数
//引数１：操作したいサーフェース
//引数２,３：文字を表示したい座標X,Y
//引数４、５、６：文字を色を指定
{
	HDC hdc;
	lpDDS->GetDC(&hdc);	//描画を行うサーフェースのデバイスコンテキストを取得

		//wsprintf(str,"%d  ",CmdNum[i]);
	SetTextColor(hdc,RGB(rcol,gcol,bcol));	//引数４，５，６で指定色を文字色に
	SetBkMode(hdc,TRANSPARENT);				//文字のバックを透明に
	TextOut(hdc,x,y,text,lstrlen(text));	//文字表示

	lpDDS->ReleaseDC(hdc);//デバイスコンテキストの解放
	
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void DrawFrameRate(LPDIRECTDRAWSURFACE7 lpDDS,int x,int y)
//機能：フレームレートを表示する関数
//引数１：操作したいサーフェース
//引数２、３：表示したい座標X,Y
{
	static DWORD frameNew, frameOld;
	static DWORD timeNew, timeOld;
	HDC hdc;
	static char string[64];
	DWORD Rate;

	frameNew ++;
	timeNew = timeGetTime();
	if(timeNew - timeOld > 1000)
	{
		Rate = frameNew - frameOld;	//Rateの値を更新
		frameOld = frameNew;
		timeOld = timeNew;
		wsprintf(string,"%dFPS   ",Rate);	//Rateの値をstringに置き換える
	}

	lpDDS->GetDC(&hdc);

	SetTextColor(hdc,RGB(255,255,255));			//文字色指定
	SetBkMode(hdc,TRANSPARENT);					//文字のバックを透明にする
	TextOut(hdc,x,y,string,lstrlen(string));	//文字を表示

	lpDDS->ReleaseDC(hdc);

}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void Debug_DrawText()	//テキスト表示をまとめた関数(メイン関数用（デバッグ用
{
	HDC hdc;
	int i;
	char str[64];

	//▼テキスト表示
	lpDDSBackBuffer->GetDC(&hdc);	//描画を行うサーフェースのデバイスコンテキストを取得
	
	SetBkMode(hdc,TRANSPARENT);						//文字背景を透明に
	SetTextColor(hdc,RGB(255,255,255));				//文字色を白に

	//コマンド表示
	for(i = 0;i < 8;i++)
	{
		wsprintf(str,"%d  ",CmdNum[i]);
		TextOut(hdc,100+(i<<5),100,str,lstrlen(str));
		wsprintf(str,"%d  ",CmdCnt[i]);
		TextOut(hdc,100+(i<<5),120,str,lstrlen(str));
	}
	
	//Cnt
	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Son)
		{
			wsprintf(str,"EneHitD= %d : EneCnt[%d]",En[i].HitD,En[i].Cnt);
			TextOut(hdc,En[i].x,En[i].y+En[i].h,str,lstrlen(str));

		}
	}

	wsprintf(str,"Btn1 [%d]  : Btn2 [%d] :: Cnt(%d)",Btn1,Btn2,BtnCnt);
	TextOut(hdc,400,400,str,lstrlen(str));

	wsprintf(str,"Plr.HitD = %d",Plr.HitD);
	TextOut(hdc,500,300,str,lstrlen(str));

	//フレームレート表示
	wsprintf(str,"FPS_Disp [ %d ]",FPS_Disp);			//FPS_Dispを文字列に置き換える
	TextOut(hdc,10,10,str,lstrlen(str));				//仮想画面にstr表示

	wsprintf(str,"FPS_ChangeNum [ %d ]",FPS_ChangeNum);			//FPS_Dispを文字列に置き換える
	TextOut(hdc,10,25,str,lstrlen(str));				//仮想画面にstr表示

	lpDDSBackBuffer->ReleaseDC(hdc);	//デバイスコンテキストの解放	
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
