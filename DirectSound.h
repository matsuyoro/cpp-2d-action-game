#if !defined __DIRECTSOUNDMACRO
#define __DIRECTSOUNDMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
BOOL DS_Init();						//ダイレクトサウンドの初期化
BOOL DS_Load(int);						//音データを取得し、セカンダリバッファを作成する関数
BOOL DS_Play(int,BOOL);				//セカンダリバッファの再生を行う関数
BOOL DS_Stop(int);					//セカンダリバッファの停止を行う関数
BOOL DS_VolumeChg(int,long);			//セカンダリバッファのボリュームを設定する関数
BOOL DS_PanChg(int,long);			//セカンダリバッファのパンの設定を行う関数
BOOL DS_FrequencyChg(int,DWORD);		//セカンダリバッファの周波数の設定を行う関数
void ReleaseDS();						//DirectSound関連のオブジェクトの解放の関数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif
