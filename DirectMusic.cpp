#include "Extern.h"
#include "DirectSound.h"
#include "DirectMusic.h"
#include "Define.h"
#include < dmusicc.h >		// コア・レイヤインターフェース
#include < dmusici.h >		// パフォーマンス・レイヤインターフェース


///// 変数宣言 ///////

IDirectMusicPerformance*	lpDMPerformance;	// DirectMusicPerformance オブジェクト

IDirectMusic*			lpDMusic = NULL;						// DirectMusic オブジェクト
IDirectMusicLoader*		lpDMLoader;								// ローダーオブジェクト
IDirectMusicSegment*	lpDMSegment[ MUSIC_MAX ] = { NULL };	// セグメントオブジェクト

extern LPDIRECTSOUND	lpDS;	//DirectMusicオブジェクト作成で引数に使用する　DirectSoundオブジェクトを

int	MusicNumber = 0;	// 現在のミュージック番号管理用

//―――――― ダイレクトミュージック関係の初期化を行う関数 ――――――――――――――――――――――――
BOOL DM_Init()
{
	HRESULT				res;			// 戻値用
	DMUS_OBJECTDESC		dmod;			// オブジェクト ( MIDI ) の情報を管理するための構造体
	MUSIC_TIME			start_time = 0;	// セグメントの開始時刻 ( 曲のどこから再生するか ) を格納するための変数
										// ０の場合、曲の最初から
	MUSIC_TIME			end_time;		// ループ再生時の終了時刻を格納するための変数
	MUSIC_TIME			seg_length;		// セグメントの長さを格納するための変数

	//MIDIファイルネーム
	WCHAR *				Midi_FileNeme[ MUSIC_MAX ] =
						{
							{ L"MIDI\\BGM1.mid" },
							{ L"MIDI\\おまけの曲.mid" }
							//{ L"MIDI\\DQ3.mid" },
							//{ L"MIDI\\Z.mid" },
							//{ L"MIDI\\FF4.mid" },
							//{ L"MIDI\\( ^-^ ).mid" }
						};


	///// COM の初期化 /////
	res = CoInitialize( NULL );
	if(FAILED(res))	//エラーチェック
		ERR_MES_RETURN("COMの初期化に失敗");


	///// DirectMusicPerformance オブジェクトの作成 //////
	res = CoCreateInstance(
						CLSID_DirectMusicPerformance,
						NULL,
						CLSCTX_INPROC,
						IID_IDirectMusicPerformance2,
						( void ** )&lpDMPerformance );
	if(FAILED(res))	//エラーチェック
		ERR_MES_RETURN("DirectMusicPerformance オブジェクトの作成に失敗")


	///// DirectMusic オブジェクトの作成 //////
	res = lpDMPerformance -> Init( &lpDMusic, lpDS, NULL );
	if( FAILED( res ) )	//エラーチェック
		ERR_MES_RETURN("DirectMusic オブジェクト の作成に失敗");


	////// DirectMusicLoader オブジェクトの作成 //////
	res = CoCreateInstance(
						CLSID_DirectMusicLoader,
						NULL,
						CLSCTX_INPROC,
						IID_IDirectMusicLoader,
						( void ** )&lpDMLoader );
	if(FAILED(res))	//エラーチェック
		ERR_MES_RETURN("DirectMusicLoader オブジェクト の作成に失敗");

	///// ポート ( シンセサイザ ) の選択 ///////
	res = lpDMPerformance -> AddPort( NULL );		// デフォルトのポートを選択
	if(FAILED(res))	//エラーチェック
		ERR_MES_RETURN("デフォルト・ポートの選択に失敗");

	// ------------------ セグメントの作成 ----------------- //

	// ミュージックの数分、セグメントを作成する
	for( int i = 0; i < MUSIC_MAX; i ++ )
	{
		dmod.dwSize = sizeof( dmod );								// 構造体のサイズ指定
		dmod.guidClass = CLSID_DirectMusicSegment;					// DirectMusicSegment を指定
		wcscpy( dmod.wszFileName, Midi_FileNeme[ i ] );				// mid ファイルを指定
		dmod.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;		// 有効メンバを指定

		// セグメントの作成 ( 構造体からデータを取り出す )
		res = lpDMLoader -> GetObject( &dmod, IID_IDirectMusicSegment2, ( void ** )&lpDMSegment[ i ] );
		if(FAILED(res))	//エラーチェック
			ERR_MES_RETURN("セグメントのロードに失敗");

		// セグメントのパラメータの設定
		lpDMSegment[ i ] -> SetParam( GUID_StandardMIDIFile, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );

		// DLS コレクションのダウンロード
		lpDMSegment[ i ] -> SetParam( GUID_Download, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );

		// セグメントの長さを取得する
		lpDMSegment[ i ]-> GetLength( &seg_length );

		// セグメントの開始時刻を設定する
		lpDMSegment[ i ] -> SetStartPoint( start_time );

		// 再生させる長さを設定する
		end_time = seg_length;
		lpDMSegment[ i ] -> SetLoopPoints( start_time, end_time );

		// ループ再生させる回数を設定する
		lpDMSegment[ i ] -> SetRepeats( 0xFFFF );

	}

	return TRUE;

}
//―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――

//――――――――― ダイレクトミュージック関係のオブジェクトの解放　――――――――――――――――――
void ReleaseDM( )
{
	int		i;

	// DLS のアンロード ( 解放 )
	for( i = 0; i < MUSIC_MAX; i ++ )
	{
		lpDMSegment[ i ] -> SetParam( GUID_Unload, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );
	}

	// セグメントオブジェクトの解放
	for( i = 0; i < MUSIC_MAX; i ++ )
	{		
		RELEASEDM( lpDMSegment[ i ] );
	}

	if( lpDMPerformance != NULL )
	{
		lpDMPerformance -> CloseDown( );	// Performance オブジェクトを閉じる
	}

	RELEASEDM( lpDMPerformance );			// lpDMPerformance オブジェクトの解放
	RELEASEDM( lpDMusic );					// lpDirectMusic オブジェクトの解放
	RELEASEDM( lpDMLoader );				// ローダーオブジェクトの解放
	CoUninitialize( );						// COM の解放

}
//――――――――――――――――――――――――――――――――――――――――――――――――――――――――――

//――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void DM_Play(int MusicNum)	//機能：セグメントを再生する
//●引数１：再生させるセグメントの番号
{
	// セグメントの演奏
	lpDMPerformance -> PlaySegment( lpDMSegment[ MusicNum ], DMUS_SEGF_DEFAULT, 0, NULL );

}

//―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void DM_Stop(int MusicNum)	//機能：セグメントを停止する
//●引数１：停止させるセグメントの番号(-1で全て停止
{	
	if(MusicNum == -1)	//引数がー１なら全ての曲を停止
		lpDMPerformance -> Stop(NULL, NULL, 0, 0 );
	else
		lpDMPerformance -> Stop( lpDMSegment[ MusicNum ], NULL, 0, 0 );
}