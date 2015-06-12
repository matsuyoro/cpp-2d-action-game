#include <dsound.h>			//DirectSoundの機能使うのに必要なヘッダ
#include "Define.h"			//マクロヘッダ
#include "Extern.h"			//外部変数ヘッダ
#include "GameStruct.h"		//構造体の型の宣言のヘッダ

#include "DirectSound.h"

//DirectSound 関係の構造体

WAVEFORMATEX	wfex;			//音データのフォーマット情報格納用
DSBUFFERDESC	dsbd;			//サウンドバッファの能力設定用
MMCKINFO	parent, child;		// RIFFファイル内のチャンクに関する情報を格納する構造体（親チャンク と サブ( 子 )チャンク用） 

//DirectSound 関係の変数
LPDIRECTSOUND			lpDS;							//DirectSound オブジェクト
LPDIRECTSOUNDBUFFER		lpDSPrimary;					//プライマリバッファ
LPDIRECTSOUNDBUFFER		lpDSSoundBuffer[ SOUND_MAX ];	//セカンダリバッファ


// ファイル読みこみ・音量の初期化用構造体
WAVE_DATA	Wave_Data[ SOUND_MAX ] =
{
//	 ファイル名					ボリューム	パン		周波数
	{ "WAVE\\剣斬り2.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\剣斬り.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\剣斬りダメージ.wav",	-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\銃.wav",				-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\レーザー.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\Plrダメージ.wav",		-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\火炎放射.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\バリア跳ね返り音.wav",	-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\斬りつけ.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\ジャンプ.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL }
};


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_Init()	//機能：ダイレクトサウンドの初期化
{
	HRESULT	res;			//戻値用

	//●DirectSoundオブジェクト作成――――――――――――――――――――――――――――――――――――――――――
	res = DirectSoundCreate(NULL,&lpDS,NULL);
	if(res != DS_OK)								//エラーチェック	
		ERR_MES_RETURN("DirectSoundCreate")			//DS_OK以外なら失敗

	//●協調レベル―――――――――――――――――――――――――――――――――――――――――――――――――――
	res = lpDS->SetCooperativeLevel(hWnd,			//ウィンドウハンドル
									DSSCL_NORMAL);	//協調フラグ
	if(res != DS_OK)								//エラーチェック
		ERR_MES_RETURN("SetCooperativeLevel(協調レベル)");

	//●スピーカーの設定――――――――――――――――――――――――――――――――――――――――――――――――
	res = lpDS->SetSpeakerConfig(DSSPEAKER_COMBINED(DSSPEAKER_STEREO,DSSPEAKER_GEOMETRY_WIDE));
	//ステレオ用で最適化。スピーカーは、音を聞く人から２０°の円弧上で最適化
	if(res != DS_OK)	//エラーチェック（※ステレオ以外の時は、そのままフラグを指定するだけでOK
		ERR_MES_RETURN("SetSpeakerConfig(STEREO→GEOMETRY_WIDE)");

	//●プライマリバッファ作成（	※サウンドカードが自動的に作成してくれる――――――――――――――――――――――

	ZeroMemory(&dsbd,sizeof(dsbd));		//全てのメンバを０で初期化
	dsbd.dwSize = sizeof(dsbd);			//構造体のサイズ
	dsbd.dwFlags =	DSBCAPS_CTRLVOLUME |	//音全体のボリューム調節機能をもつ
					DSBCAPS_PRIMARYBUFFER;	//プライマリバッファであることを示す
	dsbd.dwBufferBytes = 0;		//サウンドバッファのバイト単位のサイズ
	dsbd.lpwfxFormat = NULL;	//音(WAVE)データを管理するための構造体へのポインタ

	//DSBUFFERDESC構造体に設定したデータをもとにプライマリバッファを作成する。
	res = lpDS->CreateSoundBuffer(&dsbd,&lpDSPrimary,NULL);
	if(FAILED(res))	//プライマリバッファの作成に失敗	（※FAILED＝失敗を判定する機能のマクロ
		ERR_MES_RETURN("プライマリバッファの作成に失敗")

	return TRUE;	//成功なので、TRUEを返す。
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_Load(int No)	//機能：●音のデータ（情報）を取得し、それをもとにセカンダリバッファを作成する
//●引数１：ウィンドウのハンドル
//●引数２：効果音の番号
{
	HMMIO hmmio = NULL;				//mmioファイルハンドル用
	HRESULT			res;			//戻値用
	LPVOID			p1,		p2;		// ロックした時のブロック１と、ブロック２のポインタ格納用
	DWORD			size1,	size2;	// ロックした時のブロック１と、ブロック２のバイト数格納用
	LONG			WaveBytes;		// 読み込んだ音データのバイト数格納用

	parent.ckid = 0;				// チャンク識別子
	parent.cksize = 0;				// チャンクのデータメンバのバイト数
	parent.fccType = ( FOURCC )0;	// フォームタイプ
	parent.dwDataOffset = 0;		// データメンバの先頭アドレス
	parent.dwFlags = 0;				// チャンクに関する付加情報を指定するフラグ

	child = parent;


	//ファイルを開く
	hmmio = mmioOpen(	Wave_Data[ No ].lpFileName,	//開くファイル名
						NULL,
						MMIO_READ);					//読み取り専用で開く
	if(!hmmio)										//エラーチェック
	{
		ERROR_MESSAGE("mmioOpen");					//NULLが返ってきたら失敗
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- Wave チャンクへディセンドする ----------- //

	// Wave チャンクへディセンド(移動）する
	parent.ckid =		mmioFOURCC( 'R', 'I', 'F', 'F' );
	parent.fccType =	mmioFOURCC( 'W', 'A', 'V', 'E' );

	if( mmioDescend( hmmio, &parent, NULL, MMIO_FINDRIFF ) )	//チャンク識別子「RIFF」と指定のフォームタイプをもつチャンクを探す。
	{	//失敗すると、MMIOERR_CHUNKNOTFOUNDが返る。
		ERROR_MESSAGE("Waveファイルではない");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- fmt チャンクへディセンドする ------------ //

	// fmt チャンクへディセンド（移動）する
	child.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );

	if( mmioDescend( hmmio, &child, &parent, 0 ) )
	{	// Wave ファイルに fmt チャンクがない
		ERROR_MESSAGE("Waveファイルに fmt チャンクがない");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ------- mmioRead 関数を使用して Wave ファイルからフォーマット情報を読み出して ------- //
	// -------------------------- WAVEFORMATEX 構造体に格納する ---------------------------- //

	// WAVEFORMATEX 構造体のすべてのメンバを０で初期化
	ZeroMemory( &wfex, sizeof( WAVEFORMATEX ) );

	// Wave ファイルから、フォーマット情報を取得する
	if( mmioRead( hmmio, ( char * )&wfex, sizeof( WAVEFORMATEX ) ) != sizeof( WAVEFORMATEX ) )
	{	// fmt チャンクの読み取りに失敗
		ERROR_MESSAGE("fmt チャンクの読み取りに失敗");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// 読み取ったファイルが PCM フォーマットか調べる
	if( wfex.wFormatTag != WAVE_FORMAT_PCM )
	{	// PCM フォーマットではない
		ERROR_MESSAGE("PCM フォーマットではない");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- fmt チャンクからアセンドする ------------ //

	// mmioAscend 関数により
	// fmtチャンクからのアセンド(ディセンドしたところからの復帰)を行う
	if( mmioAscend( hmmio, &child, 0 ) )
	{	// fmt チャンクからのアセンドに失敗
		ERROR_MESSAGE("fmt チャンクからのアセンドに失敗");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- data チャンクへディセンドする ----------- //

	// data チャンクへディセンドする
	child.ckid = mmioFOURCC( 'd','a','t','a' );

	if( mmioDescend( hmmio , &child , &parent , MMIO_FINDCHUNK ) )
	{	// Wave ファイルにデータチャンクがない
		ERROR_MESSAGE("WAVEファイルにデータチャンクがない");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ---------------- Wave サウンドを格納するためのセカンダリバッファを ------------------ // 
	// - DSBUFFERDESC 構造体に設定したデータを元に、CreateSoundBuffer 関数を使用し作成する - //

	ZeroMemory( &dsbd, sizeof( dsbd ) );			// 構造体のすべてのメンバを０で初期化
	dsbd.dwSize = sizeof( dsbd );					// 構造体のサイズを指定

	dsbd.dwFlags =	DSBCAPS_GETCURRENTPOSITION2 |	// 再生カーソルの位置を記憶する機能
					DSBCAPS_GLOBALFOCUS |			// グローバルなサウンドバッファとなる
					DSBCAPS_STATIC |				// １度読み込んだ Wave データを保持し続ける機能
					DSBCAPS_CTRLPAN |				// パン調節機能
					DSBCAPS_CTRLVOLUME |			// ボリューム調節機能
					DSBCAPS_CTRLFREQUENCY;			// 周波数調節機能

	dsbd.dwBufferBytes = child.cksize;			// 取得してあるデータサイズを格納
	dsbd.lpwfxFormat = &wfex;					// 取得してあるフォーマット情報を格納

	//●DSBUFFERDESC 構造体に指定したデータを元に、セカンダリバッファを作成する
	res	= lpDS->CreateSoundBuffer(&dsbd,&lpDSSoundBuffer[No],NULL);
	if( DS_OK != res )	//エラーチェック	
	{	// セカンダリバッファの作成に失敗
		ERROR_MESSAGE("セカンダリバッファの作成に失敗");
		mmioClose( hmmio , 0 );
		return FALSE;
	}
		 
	// ------ セカンダリバッファに音データを読み込む ------- //

	//●セカンダリバッファをロックする
	res = lpDSSoundBuffer[ No ] -> Lock( 0, child.cksize, &p1, &size1, &p2, &size2, 0 );
	if( DS_OK != res )
	{	// ロックに失敗
		ERROR_MESSAGE("ロックに失敗");
		mmioClose( hmmio , 0 );	
		return FALSE;
	}

	//●ロックしたセカンダリバッファに、音データを読み込む
	WaveBytes = mmioRead( hmmio, ( char * )p1, child.cksize );

	//ファイルから実際に読み取ったバイトサイズを調べる
	if( WaveBytes < 0 )
	{	// 音データの読み込みに失敗
		ERROR_MESSAGE("音データの読み込みに失敗");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	//●セカンダリバッファのロックをアンロック ( 解除 ) する
	res = lpDSSoundBuffer[ No ] -> Unlock( p1, size1, p2, size2 );
	if( DS_OK != res )
	{	// アンロックに失敗
		ERROR_MESSAGE("アンロックに失敗");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	//●Wave ファイル閉じる
	mmioClose( hmmio , 0 );	// mmio ファイルを閉じる


	//●ボリュームの設定
	res = lpDSSoundBuffer[ No ] -> SetVolume( Wave_Data[ No ].Vol );
	if( DS_OK != res )							//エラーチェック
		ERR_MES_RETURN("ボリューム設定失敗");	//ボリューム設定失敗

	//●パンの設定
	res = lpDSSoundBuffer[ No ] -> SetPan( Wave_Data[ No ].Pan );
	if( DS_OK != res )							//エラーチェック
		ERR_MES_RETURN("パン設定失敗");			//パン設定失敗


	//●周波数の設定
	res = lpDSSoundBuffer[ No ] -> SetFrequency( Wave_Data[ No ].Frequency );
	if( DS_OK != res )							//エラーチェック
		ERR_MES_RETURN("周波数設定失敗");		//周波数設定失敗


	return TRUE;
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void ReleaseDS()	//機能：●DirectSound 関連のオブジェクトの開放を行う関数
{
	int	i;

	//作成したセカンダリバッファの数だけ解放する
	for( i = 0 ; i < SOUND_MAX ; i ++ )
	{
		RELEASEDS( lpDSSoundBuffer[ i ] );
	}

	RELEASEDS( lpDSPrimary );			// プライマリバッファ
	RELEASEDS( lpDS );					// DirectSound オブジェクト
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_Play(int No,BOOL LoopFlag)	//機能：セカンダリバッファ(サウンドデータ)の再生を行う関数
//●引数１：再生する効果音の番号
//●引数２：ループするかどうかを指定	TRUE = ループ	FALSE = ループ無し
{
	HRESULT		res;					//戻値用
	DWORD		floop = 0;				//サウンドの再生フラグを管理するための変数

	if(LoopFlag)	//引数がTRUEなら、ループ再生
		floop = DSBPLAY_LOOPING;

	res = lpDSSoundBuffer[No]->SetCurrentPosition(0);	//再生カーソルを音データの先頭にセットする
	if(DS_OK != res)									//エラーチェック
		ERR_MES_RETURN("再生カーソルの設定失敗");

	res = lpDSSoundBuffer[No]->Play(0,0,floop);	//再生カーソルの位置からセカンダリバッファの再生を行う
	if( DS_OK != res )									//エラーチェック
		ERR_MES_RETURN("再生失敗");
	
	return TRUE;	//最後まできたので成功、TRUEを返す。
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_Stop(int No )	//機能：セカンダリバッファ (サウンドデータ) の停止を行う関数
//●引数１：再生する効果音の番号
{
	HRESULT res;	//戻値用

	res = lpDSSoundBuffer[ No ]->Stop();	//サウンドを停止する
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("サウンド停止失敗");

	return TRUE;	//成功なので、TRUEを返す。
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_VolumeChg(int No, long Val )	//機能：セカンダリバッファ(サウンドデータ)のボリュームを設定する関数
//●引数１：変更する効果音の番号
//●引数２：現在のﾎﾞﾘｭｰﾑからの変化量
{
	long		vol;		//サウンドのボリュームを格納するための変数
	HRESULT		res;		//戻値用

	res = lpDSSoundBuffer[No]->GetVolume(&vol);	//サウンドのボリュームを取得する
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("ボリューム取得失敗");

	vol += Val;		//取得したﾎﾞﾘｭｰﾑの値(現在のﾎﾞﾘｭｰﾑの値)に引数で指定したﾎﾞﾘｭｰﾑの値を加える

	// ボリュームの補正
	if(vol > 0		)	//ボリュームの最大を超えないように
		vol = 0;
	if(vol < -10000	)	//ボリュームの最小より小さくならないように
		vol = -10000;

	res = lpDSSoundBuffer[ No ] -> SetVolume( vol );	//ボリュームを設定する
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("ボリューム設定失敗");

	return TRUE;	//成功なのでTRUEを返す。
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_PanChg(int No,long Val)	//機能：セカンダリバッファ ( サウンドデータ ) のパンの設定を行う関数
//●引数１：変更する効果音の番号
//●引数２：現在のパンからの変化量
{
	long		pan;			//パンの値を格納するための変数
	HRESULT		res;			//戻値用

	res = lpDSSoundBuffer[No]->GetPan(&pan);	//パンの値を取得する
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("パンの値取得失敗");

	pan += Val;	//取得したパンの値(現在のパンの値)に、引数で指定したパンの値を加える

	// パンの補正
	if( pan > 10000 )
		pan = 10000;
	if( pan < -10000 )
		pan = -10000;

	res = lpDSSoundBuffer[No]->SetPan(pan);	//パンの設定
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("パン設定失敗");

	return TRUE;	//成功なのでTRUEを返す
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
BOOL DS_FrequencyChg(int No, DWORD Frequency )	//セカンダリバッファ(サウンドデータ)の周波数の設定を行う関数
//●引数１：変更する効果音の番号
//●引数２：現在の周波数からの変化量
{
	DWORD		Freq_Val;		//周波数の値を格納するための変数
	HRESULT		res;			//戻値用

	res = lpDSSoundBuffer[No]->GetFrequency(&Freq_Val);	//周波数の値を取得する
	//	ERR_MES_RETURN("周波数の値取得失敗");

	Freq_Val += Frequency;	//取得した周波数の値(現在の周波数の値)に、引数で指定した周波数の値を加える

	res = lpDSSoundBuffer[No]->SetFrequency(Freq_Val);	//周波数の設定
	if( DS_OK != res )	//エラーチェック
		ERR_MES_RETURN("周波数設定失敗");

	return TRUE;	//成功なのでTRUEを返す。
}
