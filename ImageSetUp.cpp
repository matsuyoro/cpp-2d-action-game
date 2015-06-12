////////インクルード///////////
#include <windows.h>	//Windows用のヘッダーファイル(windowsで使用する命令やデータ型がまとめられている)
#include "extern.h"		//外部変数を扱うためのヘッダファイル
/////////関数本体/////////////////
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――
BOOL LoadBmp(char *pFileName,HDC hdc,HDC *phBmpDC,HINSTANCE hInst)	//機能：BMPファイルを準備する関数
//●引数１：読み込むファイル名
//●引数２：ウィンドウのHDC
//●引数３：作成されたHDCをうけとるアドレス
//●引数４：LoadImageで使用するインスタンスハンドル
{
//内部変数宣言
HBITMAP hBit;	//ビットマップハンドルhBitを宣言
char str[256];	//エラーメッセージで扱う文字列を扱う変数

//絵のデータ準備
hBit = (HBITMAP)LoadImage(hInst,pFileName,			//引数１のファイル名(pFIleName)のデータを読み込む
						  IMAGE_BITMAP,0,0,			//0,0で自動で読み込む画像の大きさを自動で設定
						  LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//読み込みフラグ
if(!hBit)		//LoadImage()に失敗したら(NULLなら)
{
	wsprintf(str,"%sの用意に失敗(LoadImage)",pFileName);	//LoadImageに失敗したファイル名を文字列に置き換える
	MessageBox(NULL,str,"エラー",MB_OK);					//エラーをメッセージボックスで表示
	return FALSE;											//FALSEを戻す
}

*phBmpDC = CreateCompatibleDC(hdc);		//hCharDC（メモリDC）を作成
if(!*phBmpDC)	//CreateCompatibleDC()に失敗したら(NULLなら)
{
	wsprintf(str,"%sのHDC作成に失敗(CreateCompatibleDC)",pFileName);	//CreateComaptibleDCに失敗したファイル名を文字列に置き換える
	MessageBox(NULL,str,"エラー",MB_OK);								//エラーをメッセージボックスで表示
	DeleteObject(hBit);													//成功したLoadImage()のhBitは解放
	return FALSE;														//FALSEを戻す
}

SelectObject(*phBmpDC,hBit);		//hCharDCにビットマップハンドルを選択
DeleteObject(hBit);					//ビットマップハンドルhBitを解放
return TRUE;						//成功したらTRUEを渡す
}
//■――――――――――――――――――――――――――――――――――――――――――――――
BOOL LoadDIB(char *pFileName,HDC hdc,HDC *BmpDC)	//機能：DIBファイルを準備する関数
//●引数１：ロードするBMPファイル名(２４ビットBMP
//●引数２：ウィンドウのHDC
//●引数３：作成されたHDCをうけとるアドレス
{
	HBITMAP hBit;	//ビットマップハンドル（DIB作成の時の戻値をうけとる
	HANDLE hFile;			//ファイル操作で使用
	DWORD dwSize;
	char str[256];			//表示する文字列を扱う

	hFile = CreateFile(pFileName,GENERIC_READ,0,NULL,	//BMPファイルを開く
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//失敗した場合
	{
		wsprintf(str,"CreateFile失敗");
		MessageBox(NULL,str,"エラー",MB_OK);	//エラーをメッセージボックスで表示
		return FALSE;											//FALSEを戻す
	}

	ReadFile(hFile,&BmpFileH,sizeof(BITMAPFILEHEADER),	//BITMAPFILEHEADERをロード
		&dwSize,NULL);

	ReadFile(hFile,&BmpInfoH,sizeof(BITMAPINFOHEADER),	//BITMAPINFOHEADERをロード
		&dwSize,NULL);

	*BmpDC = CreateCompatibleDC(hdc);	
	
	hBit = CreateDIBSection(hdc,	//DIB作成（BMPファイルと同じ大きさ、同じカラーモードのDIB作成
		(BITMAPINFO*)&BmpInfoH,
		DIB_RGB_COLORS,(void**)&rgbt,NULL,0);
		
	ReadFile(hFile,rgbt,			//rgbt に BMPファイルのピクセルデータだけロード
		BmpFileH.bfSize -
		sizeof(BITMAPINFOHEADER) -
		sizeof(BITMAPFILEHEADER),	//INFOHとFILEHの分を引いてピクセルデータのみになる
		&dwSize,NULL);				//rgbt(DIBの領域）にBMPファイルのピクセルデータをロードする
	
	SelectObject(*BmpDC,hBit);

	DeleteObject(hBit);
	CloseHandle(hFile);	//ファイルの後始末（解放）　；戻値　：　成功ならTRUE、失敗ならFALSE。
	return TRUE;	//成功ならTRUEを返す
}
