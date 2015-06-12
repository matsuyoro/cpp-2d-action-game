#include <windows.h>
#include <ddraw.h>
	
#include "GameStruct.h"	//構造体の型の定義のヘッダ
#include "Extern.h"		//外部変数のヘッダ

#include "DirectSound.h"
#include "DirectMusic.h"
#include "GameCheckProc.h"	//キャラ描画関数などのプロトタイプ宣言のヘッダ
/*--------------------------------------------------------------------------
	コールバック関数
--------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int i;				//カウンタ変数
	static int PalCtrl;	//パレット切り替えで扱う変数
	
	Key = 0;	//
	Btn1 = 0;	//ボタンを押さなかったら０に
	switch( message )
	{
	case WM_KEYDOWN:	//キーボードが押されたら
		switch( wParam )
		{

		case VK_UP:
			Key |= (1<<1);				//１ビット目を１に（0010 [2]）
			break;
		case VK_LEFT:
			Key |= 1;					//０ビット目を１に（0001 [1]）
			break;
		case VK_RIGHT:
			Key |= (1<<2);				//２ビット目を１に（0100 [4]）
			break;
		case VK_DOWN:
			Key |= (1<<3);				//３ビット目を１に（1000 [8]）
			break;

		case VK_SHIFT:
			Btn1 |= 1;					//０ビット目を１に（0001 [1]）
			break;
		case VK_CONTROL:
			Btn1 |= (1<<1);				//１ビット目を１に（0010 [2]）
			break;

		/*
		case VK_UP:			//↑が押されたら
			BGScrX -= 5.0;
			break;
		case VK_DOWN:		//↓が押されたら
			BGScrX += 5.0;
			break;
		case VK_LEFT:		//←が押されたら
			BGScrX -= 0.5;
			break;
		case VK_RIGHT:		//→が押されたら
			BGScrX += 0.5;
			break;
		*/

		case VK_F1:			//F1キー
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[1];			//エネミー１を存在させる
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F2:			//F2キー
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[2];			//エネミー１を存在させる
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F3:					//●F3キー
			Plr.Hp = 100;			//プレイヤーを復活させる
			Plr.Son = TRUE;			//存在をTRUEに
			Plr.AniType = 0;
			Plr.AniNum =0;
			break;
		case VK_F4:					//●F4キーが押されたら
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[5];			//ボスを存在させる
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F5:					//●F5キーが押されたら
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[3];			//ボスを存在させる
					En[i].Son = TRUE;
					break;
				}
			}

			break;
		case VK_F6:					//●F6が押されたら
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[4];			//エネミー１を存在させる
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_SPACE:					//●6が押されたら
			for(i = 0;i < 30;i++)
			{
				for(i = 0;i < ENE_MAX;i++)
				{
					if(!En[i].Son)
					{
						En[i] = EnemyNum[(int)(rand()%6+1)];			//エネミー１を存在させる
						En[i].Son = TRUE;
						break;
					}
				}
			}
			break;


		case VK_F7:					//●F7が押されたら
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[7];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F8:					//●F8が押されたら
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[6];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x30:	//●0キー
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[8];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x31:	//●1キー
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[10];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x32:	//●2キー
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[12];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		
		/////////////////////////////////////////////////////////////////
		case 0x44:	//●Dキー
			Plr.Hp --;
			break;

		//ショットーーーーーーーーーーーーーーーーーーーーーー
		case VK_NUMPAD0:	//葉っぱ竜巻	
			ShotFire(Plr.x+(Plr.w>>1)+(rand()%20-10),rand()%480,0,9,2);	//弾の発射
			break;
		case VK_NUMPAD1:	//葉っぱ吹雪
			for(i = 0;i < 20;i++)
				ShotFire(640-i,rand()%480,0,10,2);	//存在の種類を１０して当たり判定を行わない
			
			//プレイヤーと適が左に吹き飛ばされる
			if(Plr.x > 200-(Plr.w>>1))	//キャラX座標が200より大きければ
			{	
				Plr.x --;					//キャラを左に移動
			}else						//キャラX座標が200以下なら
			{
				if(!(WMoveX <= 0))			//左端までいったら何もしない
					WorldX --;					//WordlXを－１(Mapを右にスクロール
			}
			for(i = 0;i < ENE_MAX;i++)
				if(En[i].Son)	En[i].x --;


			break;
		case VK_NUMPAD2:	//光のバリア
			ShotFire(Plr.x+(rand()%Plr.w),Plr.y+(rand()%Plr.h),0,8,2);
			break;
		case VK_NUMPAD3:	//落ちる火
			for(i = 0;i < 40;i++)
				if(rand()%3 == 1)	ShotFire(i*16,rand()%48-48,0,4,2);
			break;
		case VK_NUMPAD4:	//瓦礫の竜巻
			ShotFire(Plr.x+(Plr.w>>1)+(rand()%64-32),rand()%480,0,11+rand()%5,2);	//弾の発射
			break;
		case VK_NUMPAD5:	//ポイズン
			for(i = 0 ;i < 10;i++)
			ShotFire(rand()%640,rand()%480,0,17,1);
			break;
		case VK_NUMPAD6:	//剣の破片
			ShotFire(Swd.x+(Swd.w>>1),Swd.y+(Swd.h>>1),0,19,2);
			break;

		case VK_NUMPAD9:	//ポーズ
			GameNum = 5;
			break;

		case VK_TAB:	//ステージ選択に戻る
			GameNum = 4;	//ゲームの場面を扱う値を４に（ステージ選択
			break;

		case VK_NUMPAD7:
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[11];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		//●効果音を鳴らす
		case VK_NUMPAD8:
			DS_Play( 1, FALSE );

			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[9];
					En[i].Son = TRUE;
					break;
				}
			}
			break;



		case 0x52:	//●Ｒキー
			lpDDPal->GetEntries(0,0,255,SubPal);
			//取得したパレットデータの、赤、緑、青の要素をデクリメントし、０（黒）に近づけいく
			for(i = 0;i < 255;i++)
			{
				//if(SubPal[i].peRed > 0)
				//	SubPal[i].peRed --;	//赤の要素を減らす			
				if(SubPal[i].peGreen > 0)
					SubPal[i].peGreen --;	//緑の要素をへらす
				if(SubPal[i].peBlue > 0)
					SubPal[i].peBlue --;		//青の要素を減らす
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
		case 0x47:	//●Ｇキー
			lpDDPal->GetEntries(0,0,255,SubPal);
			//取得したパレットデータの、赤、緑、青の要素をデクリメントし、０（黒）に近づけいく
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed > 0)
					SubPal[i].peRed --;	//赤の要素を減らす			
				//if(SubPal[i].peGreen > 0)
				//	SubPal[i].peGreen --;	//緑の要素をへらす
				if(SubPal[i].peBlue > 0)
					SubPal[i].peBlue --;		//青の要素を減らす
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
		case 0x42:	//●Ｂキー
			lpDDPal->GetEntries(0,0,255,SubPal);
			//取得したパレットデータの、赤、緑、青の要素をデクリメントし、０（黒）に近づけいく
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed > 0)
					SubPal[i].peRed --;	//赤の要素を減らす			
				if(SubPal[i].peGreen > 0)
					SubPal[i].peGreen --;	//緑の要素をへらす
				//if(SubPal[i].peBlue > 0)
				//	SubPal[i].peBlue --;		//青の要素を減らす
			}
			lpDDPal->SetEntries(0,0,256,SubPal);

			break;

		case VK_ADD:		//●音楽を鳴らす(	+　キー
			// セグメントの演奏
			DM_Play(0);
			break;
		case VK_MULTIPLY:
			DM_Play(1);
			break;
		case VK_SUBTRACT:	//●音楽を止める（　-　キー
			DM_Stop(-1);
			break;




		case VK_DIVIDE:	//「/」キー
			lpDDPal->GetEntries(0,0,255,SubPal);
			//取得したパレットデータの、赤、緑、青の要素をクリメントし、元の色に近づけいく
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed < MainPal[i].peRed)
					SubPal[i].peRed ++;	//赤の要素を増やす		
				if(SubPal[i].peGreen < MainPal[i].peGreen)
					SubPal[i].peGreen ++;	//緑を増やす
				if(SubPal[i].peBlue < MainPal[i].peBlue)
					SubPal[i].peBlue ++;		//青を増やす
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
			
		//case VK_F10:	//このキーボードはF10キーが対応していない
		case VK_F11:
			/*
			//黄色のグラデーションパレットに変更
			lpDDPal->GetEntries(0,0,255,SubPal);
			for(i = 0;i < 255;i++)
			{
				SubPal[i].peRed = i;
				SubPal[i].peGreen = i;
				SubPal[i].peBlue = 0;
				SubPal[i].peFlags = PC_RESERVED;
			}
			lpDDPal->SetEntries(0,0,255,SubPal);	//サブパレットをセット
			*/
			//元のパレットに戻す
			lpDDPal->SetEntries(0,0,255,MainPal);
		
			break;

		//スクロール
		case VK_PRIOR:	//●PageUpキー
			WorldX = +96;
			break;
		case VK_NEXT:	//●PageDownキー
			WorldX = -96;
			break;

		case VK_HOME:		//●HOMEキー（処理速度アップ
			FPS_ChangeNum ++;
			break;
		case VK_END:		//●ENDキー（処理速度ダウン
			if(FPS_ChangeNum > 1)	FPS_ChangeNum --;
			break;

		case VK_ESCAPE:
			PostMessage( hWnd,WM_CLOSE,0,0 );	//WM_CLOSEを発生させ、ウィンドウを閉じるよう促す
			break;
		}
		break;
	case WM_DESTROY:	//ウィンドウが終了されたら
		PostQuitMessage(0);
		break;
	default:	//上記以外のメッセージはWindowsに任せる
		return	DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

