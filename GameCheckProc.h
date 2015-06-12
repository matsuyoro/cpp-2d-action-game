#if !defined __GAMECHECKPROCMACRO
#define __GAMECHECKPROCMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int CharAnime(CHR_DATA*,ANIME_DATA*,ANIME_DATA*);
void PlrAction(CHR_DATA*,ANIME_DATA*);			//プレイヤーアクションの関数のプロトタイプ宣言
void EnAction(CHR_DATA*,ANIME_DATA*);			//エネミーアクションの関数のプロトタイプ宣言
int KeyCmdChk(int);									//コマンド入力のデータの関数のプロトタイプ宣言
void OBJON(OBJ_DATA*,int,int,int);						//オブジェクトを出すための関数のプロトタイプ宣言
void BgObjOn(BGOBJ_DATA*,int,int,int,int);					//背景オブジェクトを出すための関数のプロトタイプ宣言
void EFON(EF_DATA*,int,int,int);						//エフェクトを出すための関数のプロトタイプ宣言
void EFOFF(EF_DATA*);									//エフェクトのアニメーションと存在を扱う関数のプロトタイプ宣言
void ShotFire(int,int,int,int,int);					//弾の発射を扱う関数のプロトタイプ宣言
void ShotMove(int,int);							//弾の移動を扱う関数のプロトタイプ宣言
void EnemyOnPos();							//エネミー出現を扱う
void PlrSwdChk(CHR_DATA*,CHR_DATA*);					//キャラと剣の当たり判定のプロトタイプ宣言
void ChrHitChk(CHR_DATA*,CHR_DATA*);					//キャラとキャラの当たり判定を行う関すのプロトタイプ宣言
int ShotHitChk(SHOT_DATA*,CHR_DATA*);					//弾とキャラの当たり判定
int AtkHitChk(CHR_DATA*,CHR_DATA*);						//攻撃判定範囲とダメージを受けるキャラの判定
void UpDownChk(CHR_DATA*);								//上昇下降の関数のプロトタイプ宣言
void ChrXScroll();										//X方向にスクロールした分キャラなどをずらす関数
void ChrYScroll();										//Y方向にスクロールした分キャラをずらす関数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif