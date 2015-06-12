#if !defined __DEFINEMACRO	//もし、マクロがまだ定義されてなければ
#define __DEFINEMACRO		//マクロを定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//#include <ddraw.h>
/*-----------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------*/
#define	SCREEN_WIDTH	640										//スクリーン幅
#define SCREEN_HEIGHT	480										//スクリーン高さ
#define	BPP				8										//カラーモード

//DirectDrawオブジェクト解放マクロ
#define	RELEASE(dds)		{if( dds != NULL )	{ dds->Release(); dds = NULL;	}}
//DirectSoundオブジェクト解放マクロ
#define RELEASEDS( ds )		{if( ( ds ) )	{ ( ds )->Release( ); ds = NULL; }}
// DirectMusic オブジェクトの解放マクロ
#define		RELEASEDM( dm )		if( ( dm ) ){ ( dm ) -> Release( ); dm = NULL; }

//エラーを知らせるためのマクロ
#define ERROR_MESSAGE(mes)	{MessageBox( hWnd,mes,mes,MB_OK ); }
//エラーを知らせ、FALSEを返すマクロ
#define ERR_MES_RETURN(mes) {MessageBox(hWnd,mes,mes,MB_OK); return FALSE;}


// ミュージックの最大数
#define	MUSIC_MAX 2		//曲の最大数

//サウンドの最大数
#define SOUND_MAX 10		//音の最大数

//エネミー
#define ENE_MAX 500		//敵キャラ最大表示数

//コマンド
#define CMD_MAX 9		//コマンドの種類の数

//エネミー出現ポイント
#define ENEONPOS_MAX 30	//エネミーを出現させるポイントの最大数(ファイルロードでデータを受け取るので得に指定しなくてよい

//エネミー
#define ENEACT_MAX 5	//エネミーのアクションの種類の数
//ショット
#define SHOT_MAX 2000		//弾の最大表示数を扱う数
//エフェクト
#define EF_MAX 50		//エフェクト最大表示数を扱うマクロ
//オブジェクト
#define OBJ_MAX 12		//オブジェクト最大表示数を扱うマクロ
//バックグラウンド（背景）オブジェクト
#define BGOBJ_MAX 30	//BGオブジェの最大表示数を扱うマクロ
//マップ
#define BMPTIP_W 20		//ﾏｯﾌﾟﾁｯﾌﾟの画像元の横に並んだチップの数
#define BMPTIP_H 15		//ﾏｯﾌﾟﾁｯﾌﾟの画像元の縦に並んだチップの数
#define TIP_MAX (20*15)		//チップの種類の数

#define TIP_W 32		//チップの幅
#define TIP_H 32		//チップの高さ
#define WINMAP_W 20		//ウィンドウ内に表示するチップのヨコの数
#define WINMAP_H 15		//ウィンドウ内に表示するチップのタテの数


// #define MY_DELETEDC(x) if(x != NULL) {DeleteDC(x); x = NULL;}	//HDCの解放とNULLを代入するマクロ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif
