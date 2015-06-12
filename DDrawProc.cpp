/*------------------------------------------------------------------
	ヘッダーファイルのインクルード
------------------------------------------------------------------*/
#include <windows.h>
#include <ddraw.h>

//外部変数宣言
#include "Define.h"		//マクロ定義のヘッダ
#include "Global.h"		//外部変数宣言のヘッダ

//プロトタイプ宣言
#include "DirectSound.h"
#include "DirectMusic.h"
#include "GameInit.h"	//ゲームの準備、解放をする関数のプロトタイプ宣言のヘッダ
#include "Main.h"		//ゲームメインのプロトタイプ宣言のヘッダ

#pragma comment( lib, "dsound.lib" )
#pragma comment( lib, "dxguid.lib" )

/*-------------------------------------------------------------------
	関数のプロトタイプ宣言
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND,UINT,WPARAM,LPARAM );	//ウィンドウプロシージャ
BOOL	CreateDD( HWND );		//DirectDrawの生成
void	ReleaseDD( void );		//DirectDrawの解放
BOOL	PaletteCreate( HWND );	//パレット

LPDIRECTDRAWSURFACE7 SetUp_OffScreen(char*);	//オフスクリーンサーフェースの関数のプロトタイプ宣言

/*-----------------------------------------------------------------
	WinMain関数
-----------------------------------------------------------------*/
int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance,
				    LPSTR lpszArgs,int nWinScreenMode )
{
	MSG			msg;
	WNDCLASSEX	wcex;	//ウィンドウクラス設定用の構造体
	//HWND		hWnd;

	DWORD oldtime = 0;	//前回、ゲームのメイン処理をした時の時間(フレームレートで使用）
	DWORD nowtime = 0;	//現在の時間（フレームレートで使用）
	DWORD FPS_oldtime;	//１秒間たったかどうかを判定するのに使用
	DWORD FPS_Cnt;		//ゲーム処理の実行回数を数えるカウンタ


	//ウィンドウ・クラス設定
	wcex.cbSize = sizeof(wcex);
	//WNDCLASSEX構造体のサイズ
	wcex.style = 0;												//ウィンドウクラスのスタイル
	wcex.lpfnWndProc = (WNDPROC)WndProc;						//ウィンドウプロシージャ
	wcex.cbClsExtra = 0;										//拡張用のパラメータ
	wcex.cbWndExtra = 0;										//拡張用のパラメータ
	wcex.hInstance = hInstance;									//インスタンスハンドル
	wcex.hIcon = LoadIcon(NULL,IDI_APPLICATION);				//アイコンのハンドル
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);					//カーソルのハンドル
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//背景色設定
	wcex.lpszMenuName = NULL;									//クラスのメニュー
	wcex.lpszClassName = lpszWinClsName;						//ウィンドウクラス名
	wcex.hIconSm = LoadIcon(NULL,IDI_APPLICATION);				//スモールアイコンのハンドル

	//▼ウィンドウ・クラス登録
	if(!RegisterClassEx(&wcex))	return 0;
	//▼ウィンドウ作成
	hWnd = CreateWindowEx(
		WS_EX_TOPMOST,	//拡張ウィンドウスタイル
		lpszWinClsName,	//ウィンドウクラス名
		lpszWinTitle,	//ウィンドウのタイトル
		WS_POPUP,		//ウィンドウのスタイル
		0,				//ウィンドウの左上X座標
		0,				//ウィンドウの左上Y座標
		SCREEN_WIDTH,	//ウィンドウの幅
		SCREEN_HEIGHT,	//ウィンドウの高さ
		NULL,			//親ウィンドウのハンドル
		NULL,			//メニューのハンドル
		hInstance,		//インスタンスハンドル
		NULL			//拡張用のパラメータ
		);
	ShowWindow( hWnd,nWinScreenMode );
	UpdateWindow( hWnd );
	ShowCursor( FALSE );	//マウスカーソルを非表示にする

	//DirectDrawオブジェクトの生成
	if( !CreateDD(hWnd) )	//CreateDD()でDirectDraw作成
	{
		ReleaseDD();		//失敗していたら、即座にプログラム終了
		return FALSE;
	}
	//DirectSoundオブジェクトの初期化
	if(!DS_Init())
	{
		ReleaseDS();
		return FALSE;
	}

	// セカンダリバッファを作成し、サウンドデータを読み込む
	for(int i = 0;i < SOUND_MAX;i ++)
	{
		if(!DS_Load(i))
		{
			ReleaseDS();
			return FALSE;
		}
	}

	// ダイレクトミュージックの初期化を行う
	if( !DM_Init() )
	{
		ReleaseDM( );
		return FALSE;
	}


	//----------  MessageLoop -------------------------
	while( TRUE )	
	{
		if( PeekMessage( &msg,NULL,0,0,PM_REMOVE) )	
		{
			if(msg.message == WM_QUIT )		break;
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}else
		{
			////////////////////////////////////////////////////////////////////////
			nowtime = timeGetTime();			//現在の時間取得
			if(nowtime - FPS_oldtime >= 1000)	//前に更新してから、１秒たったら
			{
				FPS_oldtime = nowtime;
				FPS_Disp = FPS_Cnt;		//１秒でゲーム処理を何回実行できたかを保存
				FPS_Cnt = 0;			//カウンタを0にして、次の1秒のカウントの準備
			}
			if(nowtime - oldtime >= 1000/FPS_ChangeNum)	//前回の実行時から、80分の１秒以上たっていたら、
			{
				oldtime = nowtime;	//oldtimeを更新
				Main();		//メイン処理をまとめた関数Mainを実行
				FPS_Cnt++;		//ゲームのメイン処理を実行するごとに、＋１
			}
		}
	}
	/////  ゲームの解放   /////
	GameRelease();	//ゲームの解放処理をまとめた関数を実行

	ReleaseDM();	//DirectMusicオブジェクトの解放
	ReleaseDS();	//DirectSoundオブジェクトの解放
	ReleaseDD();	//DirectDrawオブジェクトの解放
	return msg.wParam;
}



/*--------------------------------------------------------------------------
	DirectDrawオブジェクトの生成
--------------------------------------------------------------------------*/
BOOL	CreateDD( HWND hWnd )
{
	HRESULT				ret;
	DDSURFACEDESC2		ddsd;
	DDSCAPS2			ddscaps;
	DDCOLORKEY ddck;					//カラーキーの情報を扱う構造体


	//	■■■■■　DirectDrawオブジェクトの作成　■■■■■
	ret = DirectDrawCreateEx( NULL,(void **)&lpDD,IID_IDirectDraw7,NULL);
	if( ret != DD_OK )	ERR_MES_RETURN("DirectDrawCreateEx失敗");	//エラーチェック

	//	■■■■■　協調レベルの設定　■■■■■
	ret = lpDD->SetCooperativeLevel( hWnd,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN
										| DDSCL_ALLOWREBOOT | DDSCL_ALLOWMODEX );	//DDSCL_ALLOWMODEXは640*480以外の画面サイズを扱う時に指定（例320*280）
	if(ret != DD_OK )	ERR_MES_RETURN("SetCooperativeLevel失敗");	//エラーチェック

	//	■■■■■　画面モードの設定　■■■■■
	ret = lpDD->SetDisplayMode( SCREEN_WIDTH,SCREEN_HEIGHT,BPP,0,0 );
	if( ret != DD_OK )	ERR_MES_RETURN("SetDisplayMode失敗");	//エラーチェック

	//	■■■■■　プライマリサーフェスの作成　■■■■■
	ZeroMemory( &ddsd,sizeof( DDSURFACEDESC2 ) );	//全てのメンバを０に初期化
	ddsd.dwSize = sizeof( ddsd );					//この構造体のサイズを格納
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;//dwFlagsメンバに、DDSURFACEDESC2構造体のどのメンバを使用（有効）するかを設定する

	ddsd.ddsCaps.dwCaps =	DDSCAPS_PRIMARYSURFACE |	//このｻｰﾌｪｰｽが、ﾌﾟﾗｲﾏﾘｻｰﾌｪｰｽであることを表す
							DDSCAPS_FLIP |				//このｻｰﾌｪｰｽが、フリップ可能であることを表す
							DDSCAPS_COMPLEX;			//複合ｻｰﾌｪｰｽを表す

	ddsd.dwBackBufferCount = 1;						//バックバッファの数
	ret = lpDD->CreateSurface( &ddsd,&lpDDSPrimary,NULL );
	if(ret != DD_OK )	ERR_MES_RETURN("CreateSurface (プライマリ) 失敗");	//エラーチェック

	//■■■■■	バックバッファの作成	■■■■■
	ZeroMemory( &ddscaps,sizeof( DDSCAPS2 ) );
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ret = lpDDSPrimary->GetAttachedSurface( &ddscaps,&lpDDSBackBuffer );
	if( ret != DD_OK )	ERR_MES_RETURN("GetAttachedSurface (バックバッファ) 失敗");	//エラーチェック

	//	■■■■■　パレット　■■■■■
	if(!PaletteCreate(hWnd))	//パレットの初期化とオブジェクト作成関連づけをする関数を実行
		ERR_MES_RETURN("PaletteCreate(パレット設定)失敗");	//エラーチェック

	/*---------------------------------------------------------------------------------------------------------------
	|		ビットマップをオフスクリーンに設定
	*--------------------------------------------------------------------------------------------------------------*/
	//オフスクリーンサーフェースに、ビットマップを設定する

	//ゲージや文字など
	lpDDSOff_Text = SetUp_OffScreen("BMP\\Text.bmp");		//プレイヤーのゲージなど
	if(!lpDDSOff_Text)		ERR_MES_RETURN("lpDDSOff_Text");	//lpDDSOff_Textをオフスクリーンサーフェースに準備できなかったらエラー
	//タイトル
	lpDDSOff_Title = SetUp_OffScreen("BMP\\Title.bmp");		//タイトル
	if(!lpDDSOff_Title)		ERR_MES_RETURN("lpDDSOff_Title");
	//ステージセレクト
	lpDDSOff_StageSelect = SetUp_OffScreen("BMP\\StageSelect.bmp");		//ステージセレクト画面の絵
	if(!lpDDSOff_StageSelect)		ERR_MES_RETURN("lpDDSOff_StageSelect");
	//ポーズ画面
	lpDDSOff_Pouse = SetUp_OffScreen("BMP\\Pouse.bmp");			//ポーズ画面の絵
	if(!lpDDSOff_Pouse)		ERR_MES_RETURN("lpDDSOff_Pouse");


	//マップチップ
	lpDDSOff_MapTip = SetUp_OffScreen("BMP\\MapTip8.bmp");	//マップチップの準備を関数で実行
	if(!lpDDSOff_MapTip)	ERR_MES_RETURN("lpDDSOff_MapTip");	//lpDDSOff_MapTipをオフスクリーンに準備できなかったら（NULLなら）エラー
	lpDDSOff_MapTip2 = SetUp_OffScreen("BMP\\MapTip7.bmp");	//マップチップの準備を関数で実行
	if(!lpDDSOff_MapTip2)	ERR_MES_RETURN("lpDDSOff_MapTip2");	//lpDDSOff_MapTip2をオフスクリーンに準備できなかったら（NULLなら）エラー
	lpDDSOff_MapTip3 = SetUp_OffScreen("BMP\\MapTip9.bmp");	//マップチップの準備を関数で実行
	if(!lpDDSOff_MapTip3)	ERR_MES_RETURN("lpDDSOff_MapTip3");	//lpDDSOff_MapTip3をオフスクリーンに準備できなかったら（NULLなら）エラー


	//背景
	lpDDSOff_Back0 = SetUp_OffScreen("BMP\\6BG.bmp");					//背景０（森ステージ
	if(!lpDDSOff_Back0)		ERR_MES_RETURN("lpDDSOff_Back0");										//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_Back1 = SetUp_OffScreen("BMP\\BG12.bmp");					//背景１（廃墟ステージ
	if(!lpDDSOff_Back1)		ERR_MES_RETURN("lpDDSOff_Back1");		
	lpDDSOff_Back1_OBJ = SetUp_OffScreen("BMP\\BG_OBJ.bmp");				//背景１オブジェ（廃墟ステージ用
	if(!lpDDSOff_Back1_OBJ)		ERR_MES_RETURN("lpDDSOff_Back1_OBJ");
	lpDDSOff_Back2 = SetUp_OffScreen("BMP\\sabakuBG.bmp");					//背景２（砂漠基地ステージ
	if(!lpDDSOff_Back2)		ERR_MES_RETURN("lpDDSOff_Back2");		
	lpDDSOff_Back3 = SetUp_OffScreen("BMP\\SibaBG.bmp");					//背景３（嵐ステージ
	if(!lpDDSOff_Back3)		ERR_MES_RETURN("lpDDSOff_Back3");		


	//プレイヤーの絵
	lpDDSOff_CharWAIT = SetUp_OffScreen("BMP\\PlrWAIT.bmp");						//待機
	if(!lpDDSOff_CharWAIT)	ERR_MES_RETURN("lpDDSOff_CharWAIT");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_Char = SetUp_OffScreen("BMP\\PlrMOVE.bmp");							//移動
	if(!lpDDSOff_Char)	ERR_MES_RETURN("lpDDSOff_Char");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDash = SetUp_OffScreen("BMP\\PlrDASH.bmp");						//ダッシュ
	if(!lpDDSOff_CharDash)	ERR_MES_RETURN("lpDDSOff_CharDash");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDown = SetUp_OffScreen("BMP\\PlrSITDOWN.bmp");					//しゃがみ
	if(!lpDDSOff_CharDown)	ERR_MES_RETURN("lpDDSOff_CharDown");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharAttackY = SetUp_OffScreen("BMP\\PlrATTACK-yoko.bmp");			//横斬り
	if(!lpDDSOff_CharAttackY) ERR_MES_RETURN("lpDDSOff_CharAttackY");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharAttackT = SetUp_OffScreen("BMP\\PlrATTACK-tate.bmp");			//縦斬り
	if(!lpDDSOff_CharAttackT)	ERR_MES_RETURN("lpDDSOff_CharAttackT");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharJump = SetUp_OffScreen("BMP\\PlrJUMP.bmp");						//ジャンプ
	if(!lpDDSOff_CharJump)	ERR_MES_RETURN("lpDDSOff_CharJump");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDead = SetUp_OffScreen("BMP\\PlrDEAD.bmp");						//死ぬ
	if(!lpDDSOff_CharDead)	ERR_MES_RETURN("lpDDSOff_CharDead");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDamage = SetUp_OffScreen("BMP\\PlrDAMAGE.bmp");					//ダメージ
	if(!lpDDSOff_CharDamage)	ERR_MES_RETURN("lpDDSOff_CharDamage");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDownAttackY = SetUp_OffScreen("BMP\\PlrDOWNATTACK-yoko.bmp");	//しゃがみ横斬り
	if(!lpDDSOff_CharDownAttackY)	ERR_MES_RETURN("lpDDSOff_CharDownAttackY");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDownAttackT = SetUp_OffScreen("BMP\\PlrDOWNATTACK-tate.bmp");	//しゃがみ縦斬り
	if(!lpDDSOff_CharDownAttackT)	ERR_MES_RETURN("lpDDSOff_CharDownAttackT");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharJumpAttackY = SetUp_OffScreen("BMP\\PlrJUMPAT-yoko.bmp");		//しゃがみ横斬り
	if(!lpDDSOff_CharJumpAttackY)	ERR_MES_RETURN("lpDDSOff_CharJumpAttackY");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharJumpAttackT = SetUp_OffScreen("BMP\\PlrJUMPAT-tate.bmp");		//しゃがみ縦斬り
	if(!lpDDSOff_CharJumpAttackT)	ERR_MES_RETURN("lpDDSOff_CharJumpAttackT");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharUpSwd = SetUp_OffScreen("BMP\\PlrUp_Swd.bmp");					//剣上投げ
	if(!lpDDSOff_CharUpSwd)	ERR_MES_RETURN("lpDDSOff_CharUpSwd");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharLRSwd = SetUp_OffScreen("BMP\\PlrLR_Swd.bmp");					//剣左右投げ
	if(!lpDDSOff_CharLRSwd)	ERR_MES_RETURN("lpDDSOff_CharLRSwd");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharJumpDownSwd = SetUp_OffScreen("BMP\\PlrJumpDown_Swd.bmp");		//剣ジャンプ下投げ
	if(!lpDDSOff_CharJumpDownSwd)	ERR_MES_RETURN("lpDDSOff_CharJumpDownSwd");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharDownSwd = SetUp_OffScreen("BMP\\PlrDown_Swd.bmp");				//剣しゃがみ投げ
	if(!lpDDSOff_CharDownSwd)	ERR_MES_RETURN("lpDDSOff_CharDownSwd");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_CharBall = SetUp_OffScreen("BMP\\PlrBall.bmp");					//バリア
	if(!lpDDSOff_CharBall)	ERR_MES_RETURN("lpDDSOff_CharBall");	
	lpDDSOff_CharReturnSwd = SetUp_OffScreen("BMP\\PlrReturn_Swd.bmp");		//剣吸収
	if(!lpDDSOff_CharReturnSwd)	ERR_MES_RETURN("lpDDSOff_CharReturnSwd");	
	lpDDSOff_CharSwdHPUP = SetUp_OffScreen("BMP\\PlrSwd_HPUP.bmp");		//プレイヤー剣HP入れ替え
	if(!lpDDSOff_CharSwdHPUP)	ERR_MES_RETURN("lpDDSOff_CharSwdHPUP");	


	//剣の絵
	lpDDSOff_Swd = SetUp_OffScreen("BMP\\Swd.bmp");		//剣
	if(!lpDDSOff_Swd)	ERR_MES_RETURN("lpDDSOff_Swd.bmp");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	

	//エネミーの絵
	lpDDSOff_En1 = SetUp_OffScreen("BMP\\Ene1.bmp");		//エネミー１
	if(!lpDDSOff_En1)	ERR_MES_RETURN("lpDDSOff_En1");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_En2 = SetUp_OffScreen("BMP\\Ene2.bmp");		//エネミー２
	if(!lpDDSOff_En2)	ERR_MES_RETURN("lpDDSOff_En2");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_En3 = SetUp_OffScreen("BMP\\Ene3.bmp");		//エネミー３
	if(!lpDDSOff_En3)	ERR_MES_RETURN("lpDDSOff_En3");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	
	lpDDSOff_En4 = SetUp_OffScreen("BMP\\Ene4.bmp");		//エネミー４
	if(!lpDDSOff_En4)	ERR_MES_RETURN("lpDDSOff_En4");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En5 = SetUp_OffScreen("BMP\\Ene5.bmp");		//エネミー５
	if(!lpDDSOff_En5)	ERR_MES_RETURN("lpDDSOff_En5");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En6 = SetUp_OffScreen("BMP\\Ene6.bmp");		//エネミー６
	if(!lpDDSOff_En6)	ERR_MES_RETURN("lpDDSOff_En6");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En7 = SetUp_OffScreen("BMP\\Ene7.bmp");		//エネミー７
	if(!lpDDSOff_En7)	ERR_MES_RETURN("lpDDSOff_En7");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En8 = SetUp_OffScreen("BMP\\Ene8.bmp");		//エネミー８
	if(!lpDDSOff_En8)	ERR_MES_RETURN("lpDDSOff_En8");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En9 = SetUp_OffScreen("BMP\\Ene9.bmp");		//エネミー９
	if(!lpDDSOff_En9)	ERR_MES_RETURN("lpDDSOff_En9");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_EnTubo = SetUp_OffScreen("BMP\\EneTubo.bmp");		//エネミーツボ
	if(!lpDDSOff_EnTubo)	ERR_MES_RETURN("lpDDSOff_EnTubo");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE
	lpDDSOff_En10 = SetUp_OffScreen("BMP\\Ene10.bmp");		//エネミー10
	if(!lpDDSOff_En10)	ERR_MES_RETURN("lpDDSOff_En10");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE


	lpDDSOff_Boss1 = SetUp_OffScreen("BMP\\Boss1.bmp");	//ボス１
	if(!lpDDSOff_Boss1)	ERR_MES_RETURN("lpDDSOff_Boss1");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	

	//弾の絵
	lpDDSOff_Shot = SetUp_OffScreen("BMP\\Shot.bmp");	//弾
	if(!lpDDSOff_Shot)	ERR_MES_RETURN("lpDDSOff_Shot");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	

	//エフェクトの絵
	lpDDSOff_EF = SetUp_OffScreen("BMP\\EF.bmp");		//エフェクト
	if(!lpDDSOff_EF)	ERR_MES_RETURN("lpDDSOff_EF");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	

	//オブジェクトの絵
	lpDDSOff_OBJ = SetUp_OffScreen("BMP\\OBJ.bmp");		//オブジェ
	if(!lpDDSOff_OBJ)	ERR_MES_RETURN("lpDDSOff_OBJ");	//画像をｵﾌｽｸﾘｰﾝｻｰﾌｪｰｽに準備できなかったら　エラー＆return FALSE	


	//カラーキーの設定（※注意　WindowsXPの場合真っ黒の透過色を選ぶと透過されない）
	ddck.dwColorSpaceLowValue  = 255;
	ddck.dwColorSpaceHighValue = 255;

	lpDDSOff_Text->SetColorKey(DDCKEY_SRCBLT,&ddck);					//プレイヤーのゲージなど
	lpDDSOff_Title->SetColorKey(DDCKEY_SRCBLT,&ddck);					//タイトル画像
	lpDDSOff_StageSelect->SetColorKey(DDCKEY_SRCBLT,&ddck);				//ステージセレクト画像
	lpDDSOff_Pouse->SetColorKey(DDCKEY_SRCBLT,&ddck);					//ポーズ画面

	lpDDSOff_MapTip->SetColorKey(DDCKEY_SRCBLT,&ddck);					//マップチップのオフスクリーンサーフェースの透過色を設定
	lpDDSOff_MapTip2->SetColorKey(DDCKEY_SRCBLT,&ddck);					//マップチップのオフスクリーンサーフェースの透過色を設定
	lpDDSOff_MapTip3->SetColorKey(DDCKEY_SRCBLT,&ddck);					//マップチップのオフスクリーンサーフェースの透過色を設定

	lpDDSOff_Back0->SetColorKey(DDCKEY_SRCBLT,&ddck);					//背景０(森ステージ
	lpDDSOff_Back1->SetColorKey(DDCKEY_SRCBLT,&ddck);					//背景１（廃墟ステージ
	lpDDSOff_Back1_OBJ->SetColorKey(DDCKEY_SRCBLT,&ddck);				//背景１オブジェ（廃墟ステージ用
	lpDDSOff_Back2->SetColorKey(DDCKEY_SRCBLT,&ddck);					//背景２（砂漠基地ステージ
	lpDDSOff_Back3->SetColorKey(DDCKEY_SRCBLT,&ddck);					//背景３（嵐ステージ

	lpDDSOff_CharWAIT->SetColorKey(DDCKEY_SRCBLT,&ddck);				//プレイヤー待機
	lpDDSOff_Char->SetColorKey(DDCKEY_SRCBLT,&ddck);					//プレイヤー移動の
	lpDDSOff_CharDash->SetColorKey(DDCKEY_SRCBLT,&ddck);				//プレイヤーダッシュの
	lpDDSOff_CharDown->SetColorKey(DDCKEY_SRCBLT,&ddck);				//プレイヤーしゃがみの
	lpDDSOff_CharAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤー横斬り
	lpDDSOff_CharAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤー縦斬り
	lpDDSOff_CharJump->SetColorKey(DDCKEY_SRCBLT,&ddck);				//プレイヤージャンプ
	lpDDSOff_CharDead->SetColorKey(DDCKEY_SRCBLT,&ddck);				//プレイヤーやられる
	lpDDSOff_CharDamage->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤーダメージをうける絵
	lpDDSOff_CharDownAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤーしゃがみ横斬り
	lpDDSOff_CharDownAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤーしゃがみ縦斬り
	lpDDSOff_CharJumpAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤージャンプ横斬り
	lpDDSOff_CharJumpAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤージャンプ縦斬り
	lpDDSOff_CharUpSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤー上剣投げ
	lpDDSOff_CharLRSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤー左右剣投げ
	lpDDSOff_CharJumpDownSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤージャンプ下剣投げ
	lpDDSOff_CharDownSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤーしゃがみ剣投げ
	lpDDSOff_CharBall->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤーボール
	lpDDSOff_CharReturnSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);		//プレイヤー剣吸収
	lpDDSOff_CharSwdHPUP->SetColorKey(DDCKEY_SRCBLT,&ddck);			//プレイヤー剣HP入れ替え

	lpDDSOff_Swd->SetColorKey(DDCKEY_SRCBLT,&ddck);				//剣

	lpDDSOff_En1->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー１
	lpDDSOff_En2->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー２
	lpDDSOff_En3->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー３
	lpDDSOff_En4->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー４
	lpDDSOff_En5->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー５
	lpDDSOff_En6->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー６
	lpDDSOff_En7->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー７
	lpDDSOff_En8->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー８
	lpDDSOff_En9->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エネミー９
	lpDDSOff_EnTubo->SetColorKey(DDCKEY_SRCBLT,&ddck);			//ツボ
	lpDDSOff_En10->SetColorKey(DDCKEY_SRCBLT,&ddck);			//エネミー１０

	lpDDSOff_Boss1->SetColorKey(DDCKEY_SRCBLT,&ddck);			//ボス１

	lpDDSOff_Shot->SetColorKey(DDCKEY_SRCBLT,&ddck);				//弾
	lpDDSOff_EF->SetColorKey(DDCKEY_SRCBLT,&ddck);				//エフェクト
	lpDDSOff_OBJ->SetColorKey(DDCKEY_SRCBLT,&ddck);				//オブジェクト

	//////  ゲームの準備  //////
	GameCreate(hWnd);	//ゲームの準備をする関数を実行

	return TRUE;	//成功したらTRUEを返す
}

/*----------------------------------------------------------------------------
	DirectDrawオブジェクトの削除	(※要注意※　オブジェクトを作成した順と逆順に解放をする　※●※）
----------------------------------------------------------------------------*/
void	ReleaseDD( void )
{	//オブジェクトを作成した順と逆順に解放をする
	
	RELEASE(lpDDSOff_OBJ);				//オブジェクト
	RELEASE(lpDDSOff_EF);				//エフェクト
	RELEASE(lpDDSOff_Shot);				//弾
	
	RELEASE(lpDDSOff_Boss1);			//ボス１

	RELEASE(lpDDSOff_En10);				//エネミー１０
	RELEASE(lpDDSOff_EnTubo);				//ツボ
	RELEASE(lpDDSOff_En9);				//エネミー９
	RELEASE(lpDDSOff_En8);				//エネミー８
	RELEASE(lpDDSOff_En7);				//エネミー７
	RELEASE(lpDDSOff_En6);				//エネミー６
	RELEASE(lpDDSOff_En5);				//エネミー５
	RELEASE(lpDDSOff_En4);				//エネミー４
	RELEASE(lpDDSOff_En3);				//エネミー３
	RELEASE(lpDDSOff_En2);				//エネミー２
	RELEASE(lpDDSOff_En1);				//エネミー１

	RELEASE(lpDDSOff_CharSwdHPUP);			//プレイヤー剣HP入れ替え
	RELEASE(lpDDSOff_CharReturnSwd);		//プレイヤー剣吸収
	RELEASE(lpDDSOff_CharBall);				//プレイヤーボール
	RELEASE(lpDDSOff_CharDownSwd);			//プレイヤーしゃがみ剣投げ
	RELEASE(lpDDSOff_CharJumpDownSwd);		//プレイヤージャンプ下剣投げ
	RELEASE(lpDDSOff_CharLRSwd);			//プレイヤー左右剣投げ
	RELEASE(lpDDSOff_CharUpSwd);			//プレイヤー上剣投げ
	RELEASE(lpDDSOff_CharJumpAttackT);		//プレイヤージャンプ縦斬り
	RELEASE(lpDDSOff_CharJumpAttackY);		//プレイヤージャンプ横斬り
	RELEASE(lpDDSOff_CharDownAttackT);		//プレイヤーしゃがみ縦斬り
	RELEASE(lpDDSOff_CharDownAttackY);		//プレイヤーしゃがみ横斬り
	RELEASE(lpDDSOff_CharDamage);			//プレイヤーダメージをうける絵
	RELEASE(lpDDSOff_CharDead);				//プレイヤーやられる
	RELEASE(lpDDSOff_CharJump);				//プレイヤージャンプ
	RELEASE(lpDDSOff_CharAttackT);			//プレイヤー縦斬り
	RELEASE(lpDDSOff_CharAttackY);			//プレイヤー横斬り
	RELEASE(lpDDSOff_CharDown);				//プレイヤーしゃがみの
	RELEASE(lpDDSOff_CharDash);				//プレイヤーダッシュの
	RELEASE(lpDDSOff_Char);					//プレイヤー移動
	RELEASE(lpDDSOff_CharWAIT);				//プレイヤー待機

	RELEASE(lpDDSOff_Back3);				//背景３
	RELEASE(lpDDSOff_Back2);				//背景２
	RELEASE(lpDDSOff_Back1_OBJ);				//背景１オブジェ
	RELEASE(lpDDSOff_Back1);				//背景１
	RELEASE(lpDDSOff_Back0);				//背景０

	RELEASE(lpDDSOff_MapTip3);				//マップチップ３
	RELEASE(lpDDSOff_MapTip2);				//マップチップ２
	RELEASE(lpDDSOff_MapTip);				//マップチップのオフスクリーンサーフェースを扱う
	
	RELEASE(lpDDSOff_Pouse);				//ポーズ画面
	RELEASE(lpDDSOff_StageSelect);			//ステージセレクト画面
	RELEASE(lpDDSOff_Title);				//タイトル用画像
	RELEASE(lpDDSOff_Text);					//プレイヤーのゲージなど

	RELEASE(lpDDPal);
	RELEASE(lpDDSBackBuffer);
	RELEASE(lpDDSPrimary);
	RELEASE(lpDD);

}

/*-----------------------------------------------------------------------------------
	パレット
-----------------------------------------------------------------------------------*/
BOOL PaletteCreate(HWND hWnd)	//機能：パレットの初期化とオブジェクトの作成からパレットの関連づけを行う関数
{	
	HRESULT				ret;	//結果を受け取る変数

	//Pal_Data(パレットデータ)を元に、パレットオブジェクトを作成
	ret = lpDD->CreatePalette(
		DDPCAPS_8BIT | DDPCAPS_ALLOW256,	//パレットの種類を表すフラグ
		MainPal,							//設定したパレットデータのアドレス
		&lpDDPal,							//パレットオブジェクトへのポインタ
		NULL);
	//エラーチェック
	if(ret != DD_OK)	ERR_MES_RETURN("CreatePalette(パレットオブジェクト）作成失敗");

	//作成したパレットオブジェクトを、プライマリサーフェースに関連づける
	ret = lpDDSPrimary->SetPalette(lpDDPal);
	//エラーチェック
	if(ret != DD_OK)
	{
		ReleaseDD();	//DirectDrawオブジェクトを解放してエラーのメッセージボックスの色ばけを防ぐ
		ERR_MES_RETURN("SetPalette(パレットオブジェクトの関連づけ）に失敗");
	}

	return TRUE;	//成功ならTRUEを返す
}

/*------------------------------------------------------------------------------------
		SetUp_OffScreen関数
------------------------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE7 SetUp_OffScreen(char *pFileName)
{
	HBITMAP hBitmap,hOldBitmap;			//ビットマップハンドル
	HDC hdc,bmhdc;						//デバイスコンテキスト
	BITMAP bm;							//ビットマップ構造体
	DDSURFACEDESC2 ddsd;
	RGBQUAD rgb[256];					//RGBQUAD構造体配列（256色分）
	LPDIRECTDRAWSURFACE7 lpDDSurface;
	HRESULT res;						//戻値（エラーチェック）
	int i,Color;						//色数用

	//引数で指定したビットマップのビットマップハンドルを取得する
	hBitmap = (HBITMAP)LoadImage(
		NULL,
		pFileName,				//ファイル名
		IMAGE_BITMAP,			//ビットマップ指定
		0,0,
		LR_LOADFROMFILE |		//ファイルから読み込み
		LR_CREATEDIBSECTION	);	//DIB形式
	if(!hBitmap)	return NULL;	//エラーチェック

	//ビットマップハンドルから、ビットマップの情報を取得する
	GetObject(	hBitmap,	//オブジェクトのハンドル
				sizeof(bm),	//取得するサイズ
				&bm	);		//取得した情報を格納しておくための構造体へのポインタ
	//デバイスコンテキストとビットマップハンドルをセットにする
	bmhdc = CreateCompatibleDC(NULL);
	hOldBitmap = (HBITMAP)SelectObject(bmhdc,hBitmap);

	//オフスクリーンサーフェースに設定
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	//取得したビットマップの情報から、そのビットマップの幅と高さを指定
	ddsd.dwWidth = bm.bmWidth;						//幅
	ddsd.dwHeight = bm.bmHeight;					//高さ
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	//オフスクリーンサーフェースの作成
	res  = lpDD->CreateSurface(&ddsd,&lpDDSurface,NULL);
	if(res != DD_OK)	return NULL;	//エラーチェック

	//パレットデータ（色データ）の取得
	//ビットマップオブジェクトのデバイスコンテキストから、そのオブジェクトの色データを取得する
	Color = GetDIBColorTable(
				bmhdc,	//ビットマップオブジェクトのデバイスコンテキスト
				0,		//開始番号
				256,	//開始番号からいくつ取得するかの値
				rgb	);	//取得したデータを格納しておくためのRGBQUAD構造体へのポインタ

	//パレットデータの設定
	for(i = 0;i < Color;i++)
	{
		MainPal[i].peRed = rgb[i].rgbRed;
		MainPal[i].peGreen = rgb[i].rgbGreen;
		MainPal[i].peBlue = rgb[i].rgbBlue;
		MainPal[i].peFlags = PC_RESERVED;
	}
	lpDDPal->SetEntries(0,0,256,MainPal);	//MainPalをセット
	//サブパレット（特に必要なし
	for(i = 0;i < 255;i++)
	{
		SubPal[i].peRed = i;
		SubPal[i].peGreen = i;
		SubPal[i].peBlue = i;
		SubPal[i].peFlags = PC_RESERVED;
	}


	//↓※　256番目のパレットだけ変更しない（透明色を有効にするため
	//lpDDPal->SetEntries(0,0,255,SubPal);	//MainPalをセット

	//ビットマップを、オフスクリーンに転送
	lpDDSurface->GetDC(&hdc);
	BitBlt(hdc,0,0,bm.bmWidth,bm.bmHeight,bmhdc,0,0,SRCCOPY);
	lpDDSurface->ReleaseDC(hdc);

	//デバイスコンテキストを戻す
	SelectObject(bmhdc,hOldBitmap);

	//ビットマップハンドルとデバイスコンテキストの削除
	DeleteObject(hBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(bmhdc);


	//作成したオフスクリーンへのポインタを、戻値として戻る
	return lpDDSurface;
}

