#if !defined __GAMEBLTPROCMACRO
#define __GAMEBLTPROCMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void MapBitBlt();						//マップ表示関数のプロトタイプ宣言
LPDIRECTDRAWSURFACE7 Return_lpDDSOff();	//マップチップの画像元サーフェースをステージによって変更する関数のプロトタイプ宣言
void ChrBitBlt(CHR_DATA*,ANIME_DATA*,int);	//キャラ表示関数のプロトタイプ宣言
void SwdBitBlt(CHR_DATA*,ANIME_DATA*,int);	//剣表示関数のプロトタイプ宣言
//void DumBitBlt(CHR_DATA*,ANIME_DATA*,int);	//分身表示関数
void ShotBitBlt(SHOT_DATA*);				//弾を表示する関数のプロトタイプ宣言
void EFBitBlt(EF_DATA*);					//エフェクトを表示する関数のプロトタイプ宣言
void OBJBitBlt(OBJ_DATA*);					//オブジェクトを表示する関数のプロトタイプ宣言
void BgObjBlt(BGOBJ_DATA*);					//背景オブジェクトを表示する関数のプロトタイプ宣言
void PlrHpBlt();								//プレイヤーのHPを表示する関数のプロトタイプ宣言
void EneHpBlt(CHR_DATA*);						//ダメージを受けたエネミーのHPを表示する関数のプロトタイプ宣言
void DamageX_BitBlt(CHR_DATA*,ANIME_DATA*,int);	//横きりでダメージをうけるときの絵を表示する関数のプロトタイプ宣言
void DamageY_BitBlt(CHR_DATA*,ANIME_DATA*,int);	//縦斬りでダメージを受ける時の絵を表示する関数のプロトタイプ宣言
void Kill_X_BitBlt(CHR_DATA*,ANIME_DATA*,int,int);	//敵が横に切れる絵を表示する関数のプロトタイプ宣言
void Kill_Y_BitBlt(CHR_DATA*,ANIME_DATA*,int,int);	//敵が縦に切れる絵を表示する関数のプロトタイプ宣言
//void DIB_EF();										//24ビットDIB画像を操作する関数のプロトタイプ宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif