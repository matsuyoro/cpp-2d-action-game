#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"
#include "GameBltProc.h"
#include "GameCheckProc.h"
//��GameOver����������������������������������������������������������������
void GameOver(int *pGameNum)	//	�@�\�F�Q�[���I�[�o�[��ʂ̏������s���֐�
//�������F�Q�[���̏�ʂ������l�iGameNum�j
{
	int i,j;
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	char str[256];			//�����������
	DDBLTFX ddbltfx;		//�ʂ�Ԃ��ɕK�v�ȍ\����
	static int BkX;			//�㉺�́�
	static int BkSpd;		//���̃X�N���[���X�s�[�h

	//�l�p���v���[�g���X�N���[��
	BkSpd ++;
	if(BkSpd > 640)	BkSpd = 0;
	
	//�ʂ�Ԃ��i���j
	ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
	ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);


	if((!(Btn2 & (1<<1)) && (Btn1 & (1<<1))) || Plr.Hp > 0)	//B�{�^����O��i���j�Ō��݁i���j�Ȃ� 
	{
		*pGameNum = 1;	//�ԐڎQ�Ƃ�GameNum���P�i�Q�[���{�ҁj�ɂ���B
		lpDDPal->SetEntries(0,0,255,MainPal);
	}

	ShotFire(Plr.x+(rand()%Plr.w),Plr.y+64+(rand()%32),0,25,10);	//Plr�@����D����
	ShotFire(200+(rand()%128),200+(rand()%32),0,25,10);				//�����@����D����
	ShotMove(0,0);	//�e�̈ړ�

	//�p���b�g�V�P�Ԗڂ̐F��ύX�iGameOver�̕����̐F��ύX
	lpDDPal->GetEntries(0,71,1,SubPal);
	SubPal[0].peRed  = 255;
	SubPal[0].peGreen = rand()%255;
	SubPal[0].peBlue = rand()%255;
	lpDDPal->SetEntries(0,71,1,SubPal);

	//���D�F�̃v���[�g���X�N���[�����ĕ\��
	BkX = BkSpd;				//�X�N���[���X�s�[�h��ݒ�
	BkX %= 32;					//0�`32
	if(BkX <= 0)	BkX = 32;
	for(j = 0;j < 2;j++)
	{
		for(i = 0;i < 20;i++)
		{
			MyBltFast(	(i*32)+32-BkX,(j*464),	
						lpDDSOff_Text,
						288,320,	288+BkX+32,320+16);
			MyBltFast(	(i*32),(j*464),	
						lpDDSOff_Text,
						288+BkX,320,	288+BkX+(32-BkX),320+16);
		}
	}


	//���e�i�D
	for(i = 0;i < SHOT_MAX;i++)	//�e�̐������J��Ԃ�
		ShotBitBlt(&Shot[i]);		//���e�\��

	//���v���C���[
	ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//�v���C���[�\��

	//��GameOver����
	MyBltFast(	200,200,
		lpDDSOff_Text,
		160,320,
		288,352);

	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);
}