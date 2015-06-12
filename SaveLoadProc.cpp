//ゲーム用のセーブ、ロードの関数本体
#include <windows.h>	//Windows用ヘッダファイル
#include <ddraw.h>

#include "GameStruct.h"	//構造体の型の定義のヘッダファイル
#include "Extern.h"		//外部変数になっているデータをセーブ、ロードするので、extern.hを使う。

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void GameLoad(char *pFileName)	//機能：ゲーム用のデータをロードする関数(マップデータロード
//●引数：ロードするファイル名
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)読み込み用で
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)ファイルを開く、ない場合は失敗
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}
	//セーブしてあるデータをロードする。セーブした時と、同じ順番でロードすること。
	ReadFile(hFile,&MapXnum,sizeof(int),&Dum,NULL);	//マップヨコチップ数をロード（int型）
	ReadFile(hFile,&MapYnum,sizeof(int),&Dum,NULL);	//マップタテチップ数をロード（int型）
	//↑でいくつメモリが必要かもとめるためにマップの幅、高さをロード

	if(pMap != NULL)	//今からメモリ確保しようとしている変数がNULLじゃないなら
		MessageBox(NULL,"ポインタ変数はすでにメモリ確保されています","エラー",MB_OK);
	pMap = (int*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sizeof(int)*MapYnum*MapXnum);//int型＊マップ高さ＊マップ幅個分のメモリを確保
	if(pMap == NULL)	//GlobalAllocの戻り値にNULLが戻ってきたらエラー通知
		MessageBox(NULL,"メモリ確保失敗","エラー",MB_OK);					//エラーをメッセージボックスで表示

	ReadFile(hFile,&pMap[0],sizeof(int)*MapYnum*MapXnum,&Dum,NULL);	//マップデータをロード

	//他にもセーブしたデータがあるなら、セーブした時と同じ順番でロードする

	CloseHandle(hFile);		//解放
	MessageBox(NULL,"ロードしました","LOAD",MB_OK);	//ロードされたかの確認メッセージ
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――
void EneOnPosLoad(char *pFileName)	//機能：適出現位置をロードする関数
//●引数：ロードするファイル名
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)読み込み用で
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)ファイルを開く、ない場合は失敗
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}

	//セーブしてあるデータをロードする。セーブした時と、同じ順番でロードすること。
	ReadFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);	//出現位置の数をロード（int型）
	//↑でいくつメモリが必要かもとめるために出現位置の数をロード

	if(pEneOn != NULL)	//今からメモリ確保しようとしている変数がNULLじゃないなら
		MessageBox(NULL,"ポインタ変数はすでにメモリ確保されています","エラー",MB_OK);
	pEneOn = (ENE_ONPOS*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//ENE_ONPOS型＊適出現位置数分のメモリを確保
	if(pMap == NULL)	//GlobalAllocの戻り値にNULLが戻ってきたらエラー通知
		MessageBox(NULL,"メモリ確保失敗","エラー",MB_OK);					//エラーをメッセージボックスで表示


	ReadFile(hFile,pEneOn,sizeof(ENE_ONPOS)*EneOnPos_Max.x,&Dum,NULL);	//適出現位置データをロード
	//注意　適出現位置の最大数がセーブした時とロードした時の数が同じでないとダメ	//他にもセーブしたデータがあるなら、セーブした時と同じ順番でロードする


	CloseHandle(hFile);		//解放
	MessageBox(NULL,"適出現位置ロードしました","LOAD",MB_OK);	//ロードされたかの確認メッセージ
}
