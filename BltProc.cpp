#include <windows.h>
#include <ddraw.h>

#include "Extern.h"		//外部変数を扱うヘッダ
//#include "BltProc.h"	//描画関数のプロトタイプ宣言のヘッダ
//■――――――――――――――――――――――――――――――――――――――――――――――
void MyBltFast(int x,int y,LPDIRECTDRAWSURFACE7	OffSur,int ofl,int oft,int ofr,int ofb)	//機能：BltFast関数で描画する関数
//●引数１,２：表示先X,Y座標
//●引数３：転送する画像のオフスクリーンサーフェース
//●引数４,５：転送元の画像の左上X,Y座標
//●引数６,７：転送元の画像の右下X,Y座標
{
	RECT rc;	//転送元の範囲を扱う
/*
	//クリッピング処理
	if(x+ofl < 0)					//左にはみ出ようとしたら
		ofl -= x+ofl;				//はみ出る部分を転送しない

	if(y+oft < 0)					//上にはみ出ようとしたら
		oft -= y+oft;					//はみ出る部分を転送しない

	if(x+ofr > 640)				//右にはみ出ようとしたら
		ofr -= (x+ofr)-640;			//はみ出る部分を転送しない

	if(y+ofb > 480)				//下にはみ出ようとしたら
		ofb -= (y+ofb)-480;			//はみ出る部分を転送しない

	SetRect(&rc,ofl,oft,ofr,ofb);	//転送元の範囲を更新
*/

	int w = ofr - ofl;	//幅
	int h = ofb - oft;	//高さ

	//左クリッピング
	if(x < 0)
	{
		ofl += (-x);	//leftの値を調整
		x = 0;	//表示は０（左端）から
	}

	//上クリッピング
	if(y < 0)
	{
		oft += (-y);	//topの値を調整
		y = 0;			//表示は０（上）から
	}

	//右クリッピング
	if(x + w > 640)
	{
		ofr -= ((x+w) - 640);	//rightの値を調整
	}

	//下クリッピング
	if(y+h > 480)
	{
		ofb -= ((y+h) - 480);	//bottomの値を調整
	}
	SetRect(&rc,ofl,oft,ofr,ofb);	//転送元の範囲を更新

	//指定したｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽを指定した座標に表示
	lpDDSBackBuffer->BltFast(x,y,OffSur,&rc,DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}
//■――――――――――――――――――――――――――――――――――――――――――――――
void MyBlt(int l,int t,int r,int b,LPDIRECTDRAWSURFACE7 OffSur,int ofl,int oft,int ofr,int ofb)	//機能：Blt関数で描画する関数
//●引数１,２：表示先左上X,Y座標
//●引数３,４：表示先右下X,Y座標
//●引数５：転送する画像のオフスクリーンサーフェース
//●引数６,７：転送元左上X,Y座標
//●引数８,９：転送元右下X,Y座標
{
	/*
	RECT rc1;	//転送元描画範囲を扱う
	RECT rc2;					//転送先描画範囲を扱う

	if(l < 0)					//左にはみ出ようとしたら
	{
		ofl += (-l);	
		l += (-l);
	}
	if(t < 0)					//上にはみ出ようとしたら
	{
		oft += (-t);
		t += (-t);
	}
	if(r > 640)		//右にはみ出ようとしたら
	{
		ofr -= (r-640);
		r -= (r-640);
	}
	if(b > 480)		//下にはみ出ようとしたら
	{
		ofb -= (b-480);
		b -= (b-480);
	}

	SetRect(&rc1,ofl,oft,ofr,ofb);	//描画元を設定
	SetRect(&rc2,l,t,r,b);	//描画先を扱うrc3を更新。

	lpDDSBackBuffer->Blt(&rc2,OffSur,&rc1,DDBLT_WAIT,NULL);
	*/
	RECT rc1;//={ofl,oft,ofr,ofb};	//転送元描画範囲を扱う
	RECT rc2;					//転送先描画範囲を扱う

	/*
	if(l < 0)					//左にはみ出ようとしたら
		ofl += (-l);	
	
	if(t < 0)					//上にはみ出ようとしたら
		oft += (-t);

	if(r > 640)		//右にはみ出ようとしたら
	{
		ofr -= (r-640);			//転送元の画像の幅を減らす
		if(ofr < 1)	ofr = 1;	//転送元の画像の幅が１ドットより小さくならないようにする
		r -= (r-640);			//転送先の画像も減らす
	}
	if(b > 480)		//下にはみ出ようとしたら
	{
		ofb -= (b-480);			//転送元の画像の高さを減らす
		if(ofb < 1) ofb = 1;	//転送元の画像の高さが１ドットより小さくならないようにする
		b -= (b-480);			//転送先の画像も減らす
	}*/
	SetRect(&rc1,ofl,oft,ofr,ofb);	//描画元を設定
	SetRect(&rc2,l,t,r,b);	//描画先を扱うrc3を更新。

	lpDDSBackBuffer->Blt(&rc2,OffSur,&rc1,DDBLT_KEYSRC | DDBLT_WAIT,NULL);

}