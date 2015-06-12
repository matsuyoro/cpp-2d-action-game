#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"

#include "GameBltProc.h"
#include "GameCheckProc.h"

///////////// �v���g�^�C�v�錾 ////////////////////////
void Back_0();	//�X�e�[�W�O�̔w�i�����̊֐��̃v���g�^�C�v�錾
void Back_1();	//�X�e�[�W�P�̔w�i�����̊֐��̃v���g�^�C�v�錾
void Back_2();	//�X�e�[�W�Q�̔w�i�����̊֐��̃v���g�^�C�v�錾
void Back_3();	//�X�e�[�W�R�̔w�i�����̊֐��̃v���g�^�C�v�錾
void Back_4();	//�X�e�[�W�S�̔w�i�����̊֐��̃v���g�^�C�v�錾

//���@BackProc�@������������������������������������������������������������������������������������������
void BGBlt()	//	�@�\�F�w�i�����̊֐�
//	�������F�w�i�̃X�e�[�W
{
	void (*pBG[5])();		//�ߒl�Ȃ��A�����Ȃ��̊֐��̃|�C���^�z��̐錾
	pBG[0] = Back_0;	//pBG[0]�ɒ�`�֐�Back_0�̐擪�A�h���X����
	pBG[1] = Back_1;	//
	pBG[2] = Back_2;
	pBG[3] = Back_3;
	pBG[4] = Back_4;

	//��StageNum�̒l�̔w�i�̏������s��
	pBG[StageNum]();	//�֐��̃|�C���^�z��̗v�f�ԍ��iStageNum�j�ɑΉ������֐������s
}
//��������������������������������������������������������������������������������������������������������

//===============================================================================================
void Back_0()			//�@�\�F�w�i��\������֐��i�X�̃X�e�[�W
{
	int i;	//�J�E���^
	static int namiX = 0;	//�g������
	static int sx;
	


	MyBltFast(0,0,lpDDSOff_Back0,0,0,640,240);		//�w�i�̏㔼����\��

	namiX ++;	//����{�{
	if(namiX == 360)	namiX = 0;	//360�𒴂���ƂO�ɖ߂�

	//���ʂ̔g�̂�������\��
	for(i = 0;i < 120;i++)	
	{
		MyBltFast((int)(SinT[namiX+i]*10),240+i,		//�\����XY���W
			lpDDSOff_Back0,								//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
			0,240-(i<<1),								//�]��������XY���W
			640,(240-(i<<1))+1	);							//�]�����E��XY���W
	}

}

//=================================================================================================
void Back_1()			//�@�\�F�w�i��\������֐�(�p�Ђ̃X�e�[�W
{
	int i;	//�J�E���^
	static int namiX = 0;	//�g������
	static int sx;
	
	//�[�Ă�
	namiX ++;	//����{�{
	if(namiX == 360)	namiX = 0;	//360�𒴂���ƂO�ɖ߂�

	for(i = 0;i < 240;i++)	//���ʂ̔g�̂�������\��
	{
		MyBltFast((int)(SinT[namiX+i]*10),i,		//�\����XY���W
			lpDDSOff_Back1,								//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
			0,240+i,								//�]��������XY���W
			640,(240+i)+1	);							//�]�����E��XY���W
	}

	//�w�i�n��
	for(i = 0;i < 6;i++)	//640*40�̊G���U�����ׂĕ\��
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
		sx %= 640;			//0�`640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,240+(i*40),	//�w�i�n�ʂ̉E����\��
					lpDDSOff_Back1,
					0,i*40,
					sx,(i*40)+40	);
		MyBltFast(	0,240+(i*40),		//�w�i�n�ʂ̍�����\��
					lpDDSOff_Back1,
					sx,i*40,
					sx+(640-sx),(i*40)+40	);
	}
	//�w�i�I�u�W�F�̃X�N���[��
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son)	//�w�i�I�u�W�F�����݂���Ȃ�
		{
			sx = (int)BGScrX*(BgObj[i].Line+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
			sx %= 640+BgObj[i].orgX+BgObj[i].w;			//0�`640
			//if(sx <= 0)	sx = 640+BgObj[i].orgX;	//0��菬�������Ȃ�����߂�

			BgObj[i].x = (640-sx)+BgObj[i].orgX;	//�X�N���[���ʁ{�I�u�W�F�̃����oorgX�̒l�̍��W�ɐݒ�
		}
		BgObjBlt(&BgObj[i]);		//���w�i�I�u�W�F�\��
	}
}
//=================================================================================================
void Back_2()			//�@�\�F�w�i��\������֐�(������n�̃X�e�[�W
{
	int i;	//�J�E���^
	static int sx;
	static int StartPalCnt;	//���������邭���邽�߂̃J�E���^

	if(StartPalCnt < 255)	//�X�e�[�W���n�܂��Ĉ�莞�Ԃ͉�ʂ𖾂邭���鏈�����s��
	{
		StartPalCnt ++;	//����{�{

		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���N�������g���A���̐F�ɋ߂Â�����
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < MainPal[i].peRed)
				SubPal[i].peRed ++;	//�Ԃ̗v�f�𑝂₷		
			if(SubPal[i].peGreen < MainPal[i].peGreen)
				SubPal[i].peGreen ++;	//�΂𑝂₷
			if(SubPal[i].peBlue < MainPal[i].peBlue)
				SubPal[i].peBlue ++;		//�𑝂₷
		}
		lpDDPal->SetEntries(0,0,256,SubPal);
	}

	MyBltFast(0,0,							//�\����XY���W
		lpDDSOff_Back2,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		0,0,								//�]��������XY���W
		640,160	);							//�]�����E��XY���W


	//�w�i�n��
	for(i = 0;i < 10;i++)	//640*40�̊G���U�����ׂĕ\��
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
		sx %= 640;			//0�`640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,160+(i*32),	//�w�i�n�ʂ̉E����\��
					lpDDSOff_Back2,
					0,160+(i*32),
					sx,160+((i*32)+32)	);
		MyBltFast(	0,160+(i*32),		//�w�i�n�ʂ̍�����\��
					lpDDSOff_Back2,
					sx,160+(i*32),
					sx+(640-sx),160+((i*32)+32)	);
	}
	/*
	//�w�i�I�u�W�F�̃X�N���[��
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son)	//�w�i�I�u�W�F�����݂���Ȃ�
		{
			sx = (int)BGScrX*(BgObj[i].Line+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
			sx %= 640+BgObj[i].orgX+BgObj[i].w;			//0�`640
			//if(sx <= 0)	sx = 640+BgObj[i].orgX;	//0��菬�������Ȃ�����߂�

			BgObj[i].x = (640-sx)+BgObj[i].orgX;	//�X�N���[���ʁ{�I�u�W�F�̃����oorgX�̒l�̍��W�ɐݒ�
		}
		BgObjBlt(&BgObj[i]);		//���w�i�I�u�W�F�\��
	}
	*/
}
//===============================================================================================
void Back_3()			//�@�\�F�w�i��\������֐��i���̃X�e�[�W
{
	int i;	//�J�E���^
	static int sx;
	static int kiAni;
	static int kix;
	
	kiAni++;
	if(kiAni > 6)	kiAni = 0;

	//���t���ς����炷
	if(rand()%5 == 1)	
		ShotFire(640,rand()%480,0,10,10);	//���݂̎�ނ��P�O���ē����蔻����s��Ȃ�



	//�w�i�n��
	for(i = 0;i < 6;i++)	//640*40�̊G���U�����ׂĕ\��
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
		sx %= 640;				//0�`640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,256+(i*32),	//�w�i�n�ʂ̉E����\��
					lpDDSOff_Back3,
					0,256+(i*32),
					sx,256+((i*32)+32));
		MyBltFast(	0,256+(i*32),		//�w�i�n�ʂ̍�����\��
					lpDDSOff_Back3,
					sx,256+(i*32),
					sx+(640-sx),256+((i*32)+32)	);
	}

	kix = (int)BGScrX*(1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
	kix %= 84;				//0�`640
	if(sx <= 0)	sx = 84;

	for(i = 0;i < 8;i++)
	{
		MyBltFast(	(i*84)+84-kix,160,	//�w�i�n�ʂ̉E����\��
					lpDDSOff_Back3,
					0+(kiAni*84),160,
					kix+(kiAni*84),160+96);
		MyBltFast(	(i*84),160,		//�w�i�n�ʂ̍�����\��
					lpDDSOff_Back3,
					kix+(kiAni*84),160,
					kix+(84-kix)+(kiAni*84),160+96);
	}



}
//=================================================================================================
void Back_4()			//�@�\�F�w�i��\������֐�(���J�̃X�e�[�W
{
	int i;	//�J�E���^
	static int sx;
	static int StartPalCnt;	//���������邭���邽�߂̃J�E���^

	if(StartPalCnt < 255)	//�X�e�[�W���n�܂��Ĉ�莞�Ԃ͉�ʂ𖾂邭���鏈�����s��
	{
		StartPalCnt ++;	//����{�{

		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���N�������g���A���̐F�ɋ߂Â�����
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < MainPal[i].peRed)
				SubPal[i].peRed ++;	//�Ԃ̗v�f�𑝂₷		
			if(SubPal[i].peGreen < MainPal[i].peGreen)
				SubPal[i].peGreen ++;	//�΂𑝂₷
			if(SubPal[i].peBlue < MainPal[i].peBlue)
				SubPal[i].peBlue ++;		//�𑝂₷
		}
		lpDDPal->SetEntries(0,0,256,SubPal);
	}

	MyBltFast(0,0,							//�\����XY���W
		lpDDSOff_Back2,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		0,0,								//�]��������XY���W
		640,160	);							//�]�����E��XY���W


	//�w�i�n��
	for(i = 0;i < 10;i++)	//640*40�̊G���U�����ׂĕ\��
	{
		sx = (int)BGScrX*(i+1);	//BGScrX*(i+1)�Ŕw�i�̊G�̃X�N���[���X�s�[�h��ݒ�
		sx %= 640;			//0�`640
		if(sx <= 0)	sx = 640;

		MyBltFast(	640-sx,160+(i*32),	//�w�i�n�ʂ̉E����\��
					lpDDSOff_Back2,
					0,160+(i*32),
					sx,160+((i*32)+32)	);
		MyBltFast(	0,160+(i*32),		//�w�i�n�ʂ̍�����\��
					lpDDSOff_Back2,
					sx,160+(i*32),
					sx+(640-sx),160+((i*32)+32)	);
	}

}
