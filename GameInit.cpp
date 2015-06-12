//�Q�[���̃f�[�^�����A���������֐����܂Ƃ߂��t�@�C��
/////�@�C���N���[�h ///////
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include <ddraw.h>
#include <time.h>		//���Ԃ������֐��Ȃǂ̃w�b�_
#include <math.h>		//�Z�p�֐��Ȃǂ̃w�b�_

#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "Extern.h"		//�O���ϐ����������߂̃w�b�_
#include "SaveLoadProc.h"	//�Z�[�u�A���[�h�̊֐��̃v���g�^�C�v�錾�̃w�b�_

#include "GameCheckProc.h"	//����֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
/*-----------------------------------------------------------------------------------------------------
�@�@�Q�[���̏������܂Ƃ߂���`�֐��B���b�Z�[�W���[�v�̒��O�Ɏ��s����B
�@�@�����@�F�@WHND�E�E�E�E�B���h�E�n���h��
�@�@�@�@�@�@�@HINSTANCE�E�E�E�C���X�^���X�n���h��
-----------------------------------------------------------------------------------------------------*/
void GameCreate(HWND hwnd)
{

	HDC hdc;
	int i;					//�J�E���^�ϐ�
	time_t ti;				//ti�Ŏ��Ԃ�����
	srand(time(&ti));		//time()�̖ߒl���g���ė�����������

	hdc = GetDC(hwnd);		//HDC�擾

	//------�W���C�X�e�B�b�N--------
	//���݂̃W���C�X�e�B�b�N�̃f�[�^������JoyData�̐ݒ�
	JoyData.dwSize = sizeof(JOYINFOEX);		//�\���̎���(�������g)�̑傫���������Ă���
	JoyData.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;	//�ǂ�ȃf�[�^���擾���邩(�{�^���f�[�^�A�\���L�[���E�f�[�^�A�\���L�[�㉺�f�[�^�j
	//�O��̃W���C�X�e�B�b�N�̃f�[�^������JoyData2�̐ݒ�
	JoyData2.dwSize = sizeof(JOYINFOEX);	//�\���̎��̂̑傫���������Ă���
	JoyData2.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNX | JOY_RETURNY;	//�ǂ�ȃf�[�^���擾���邩

	ReleaseDC(hwnd,hdc);	//HDC���

	//�T�C���e�[�u��
	for(i = 0;i < 720;i++)	//sin0���`sin359����
	{
		SinT[i] = sin(i * 3.14159/180.);	//�T�C���̒l�����߂ĕۑ����Ă���
	}
	for(i = 0;i < SHOT_MAX;i++)
	{
		Shot[i] = ShotData[0];	//�V���b�g�f�[�^�̂O�Ԃ̃f�[�^����
	}

	///// �����ݒ� ///////////////////////////////////////////////////////////////////////////////////////

	//�v���C���[�̓����蔻��͈̔�
	Plr.Hit.w = 32;		//�����蔻��̕��A����
	Plr.Hit.h = 76;
	Plr.Hit.x = Plr.x + (Plr.w>>1) - (Plr.Hit.w>>1);		//�����蔻���XY���W
	Plr.Hit.y = Plr.y + (Plr.h>>1) - (Plr.Hit.h>>1);
	
	//���̓����蔻��͈̔�
	Swd.Hit.w = 22;		//�����蔻��̕�
	Swd.Hit.h = 90;
	Swd.Hit.x = Swd.x + (Swd.w>>1) - (Swd.Hit.w>>1);
	Swd.Hit.y = Swd.y + (Swd.h>>1) - (Swd.Hit.h>>1);
	

	//�G�l�~�[�P�̂����蔻��͈̔�
	EnemyNum[1].Hit.w = 80;
	EnemyNum[1].Hit.h = 60;
	EnemyNum[1].Hit.x = EnemyNum[1].x + (EnemyNum[1].w>>1) - (EnemyNum[1].Hit.w>>1);
	EnemyNum[1].Hit.y = EnemyNum[1].y + (EnemyNum[1].h>>1) - (EnemyNum[1].Hit.h>>1);

	//�G�l�~�[�Q�̂����蔻��͈̔�
	EnemyNum[2].Hit.w = 112;
	EnemyNum[2].Hit.h = 64;
	EnemyNum[2].Hit.x = EnemyNum[2].x + (EnemyNum[2].w>>1) - (EnemyNum[2].Hit.w>>1);
	EnemyNum[2].Hit.y = EnemyNum[2].y + (EnemyNum[2].h>>1) - (EnemyNum[2].Hit.h>>1);

	//�G�l�~�[�R
	EnemyNum[4].Hit.w = 32;
	EnemyNum[4].Hit.h = 76;
	EnemyNum[4].Hit.x = EnemyNum[4].x + (EnemyNum[4].w>>1) - (EnemyNum[4].Hit.w>>1);
	EnemyNum[4].Hit.y = EnemyNum[4].y + (EnemyNum[4].h>>1) - (EnemyNum[4].Hit.h>>1);

	//�G�l�~�[�S
	EnemyNum[5].Hit.w = 32;
	EnemyNum[5].Hit.h = 76;
	EnemyNum[5].Hit.x = EnemyNum[5].x + (EnemyNum[5].w>>1) - (EnemyNum[5].Hit.w>>1);
	EnemyNum[5].Hit.y = EnemyNum[5].y + (EnemyNum[5].h>>1) - (EnemyNum[5].Hit.h>>1);

	//�G�l�~�[�T
	EnemyNum[6].Hit.w = 48;
	EnemyNum[6].Hit.h = 108;
	EnemyNum[6].Hit.x = EnemyNum[6].x + (EnemyNum[6].w>>1) - (EnemyNum[6].Hit.w>>1);
	EnemyNum[6].Hit.y = EnemyNum[6].y + (EnemyNum[6].h>>1) - (EnemyNum[6].Hit.h>>1);

	//�G�l�~�[�U
	EnemyNum[7].Hit.w = 30;
	EnemyNum[7].Hit.h = 30;
	EnemyNum[7].Hit.x = EnemyNum[7].x + (EnemyNum[7].w>>1) - (EnemyNum[7].Hit.w>>1);
	EnemyNum[7].Hit.y = EnemyNum[7].y + (EnemyNum[7].h>>1) - (EnemyNum[7].Hit.h>>1);

	//�G�l�~�[�V(�S��
	EnemyNum[8].Hit.w = 90;
	EnemyNum[8].Hit.h = 68;
	EnemyNum[8].Hit.x = EnemyNum[8].x + (EnemyNum[8].w>>1) - (EnemyNum[8].Hit.w>>1);
	EnemyNum[8].Hit.y = EnemyNum[8].y + (EnemyNum[8].h>>1) - (EnemyNum[8].Hit.h>>1);

	//�G�l�~�[�W�i������
	EnemyNum[9].Hit.w = 32;
	EnemyNum[9].Hit.h = 28;
	EnemyNum[9].Hit.x = EnemyNum[9].x + (EnemyNum[9].w>>1) - (EnemyNum[9].Hit.w>>1);
	EnemyNum[9].Hit.y = EnemyNum[9].y + (EnemyNum[9].h>>1) - (EnemyNum[9].Hit.h>>1);

	//�G�l�~�[�X�i�I
	EnemyNum[10].Hit.w = 40;
	EnemyNum[10].Hit.h = 48;
	EnemyNum[10].Hit.x = EnemyNum[10].x + (EnemyNum[10].w>>1) - (EnemyNum[10].Hit.w>>1);
	EnemyNum[10].Hit.y = EnemyNum[10].y + (EnemyNum[10].h>>1) - (EnemyNum[10].Hit.h>>1);

	//�c�{
	EnemyNum[11].Hit.w = 48;
	EnemyNum[11].Hit.h = 94;
	EnemyNum[11].Hit.x = EnemyNum[11].x + (EnemyNum[11].w>>1) - (EnemyNum[11].Hit.w>>1);
	EnemyNum[11].Hit.y = EnemyNum[11].y + (EnemyNum[11].h>>1) - (EnemyNum[11].Hit.h>>1);

	//�G�l�~�[10�i����
	EnemyNum[12].Hit.w = 84;
	EnemyNum[12].Hit.h = 56;
	EnemyNum[12].Hit.x = EnemyNum[12].x + (EnemyNum[12].w>>1) - (EnemyNum[12].Hit.w>>1);
	EnemyNum[12].Hit.y = EnemyNum[12].y + (EnemyNum[12].h>>1) - (EnemyNum[12].Hit.h>>1);


	//�{�X�P
	EnemyNum[3].Hit.w = 80;
	EnemyNum[3].Hit.h = 48;


	//�A�j���[�V�����Ŏg���G(Bmp)��ݒ�
	Anime[0][0].Bmp = lpDDSOff_CharWAIT;			//�ҋ@�A�j����BMP�̏���
	Anime[1][0].Bmp = lpDDSOff_Char;				//�ړ�
	Anime[2][0].Bmp = lpDDSOff_CharDash;			//�_�b�V��
	Anime[3][0].Bmp = lpDDSOff_CharDown;			//���Ⴊ��
	Anime[4][0].Bmp = lpDDSOff_CharAttackY;		//���a��
	Anime[5][0].Bmp = lpDDSOff_CharAttackT;		//�c�a��
	Anime[6][0].Bmp = lpDDSOff_CharJump;			//�W�����vUP
	Anime[7][0].Bmp = lpDDSOff_CharJump;			//�W�����vDOWN
	Anime[8][0].Bmp = lpDDSOff_CharDead;			//�L��������
	Anime[9][0].Bmp = lpDDSOff_CharDamage;		//�L�������_���[�W��������G
	Anime[10][0].Bmp = lpDDSOff_CharDownAttackT;	//���Ⴊ�ݏc�a��
	Anime[11][0].Bmp = lpDDSOff_CharDownAttackY;	//���Ⴊ�݉��a��
	Anime[12][0].Bmp = lpDDSOff_CharJumpAttackT;	//�W�����v�c�a��
	Anime[13][0].Bmp = lpDDSOff_CharJumpAttackY;	//�W�����v���a��
	Anime[14][0].Bmp = lpDDSOff_CharUpSwd;		//�L�����㌕����
	Anime[15][0].Bmp = lpDDSOff_CharLRSwd;		//�L�������E������
	Anime[16][0].Bmp = lpDDSOff_CharJumpDownSwd;	//�L�����W�����v��������
	Anime[17][0].Bmp = lpDDSOff_CharDownSwd;		//�L�������Ⴊ�݌�����
	Anime[18][0].Bmp = lpDDSOff_CharBall;			//�v���C���[�o���A
	Anime[19][0].Bmp = lpDDSOff_CharReturnSwd;		//�v���C���[���z��
	Anime[20][0].Bmp = lpDDSOff_CharSwdHPUP;		//�v���C���[��HP����ւ�

	//��
	AniSwd[0][0].Bmp = lpDDSOff_Swd;		//�������
	AniSwd[1][0].Bmp = lpDDSOff_Swd;		//��������
	AniSwd[2][0].Bmp = lpDDSOff_Swd;		//��������
	AniSwd[3][0].Bmp = lpDDSOff_Swd;		//���E����
	AniSwd[4][0].Bmp = lpDDSOff_Swd;		//���o��
	AniSwd[5][0].Bmp = lpDDSOff_Swd;		//����������

	//�G�l�~�[�P�i��
	AniEn[1][0][0].Bmp = lpDDSOff_En1;		//�ҋ@
	AniEn[1][1][0].Bmp = lpDDSOff_En1;		//�U��
	AniEn[1][2][0].Bmp = lpDDSOff_En1;		//�W�����v
	AniEn[1][3][0].Bmp = lpDDSOff_En1;		//�_���[�W
	//�G�l�~�[�Q�i�g�J�Q
	AniEn[2][0][0].Bmp = lpDDSOff_En2;		//�ҋ@
	AniEn[2][1][0].Bmp = lpDDSOff_En2;		//�ړ�
	AniEn[2][2][0].Bmp = lpDDSOff_En2;		//���݂�
	AniEn[2][3][0].Bmp = lpDDSOff_En2;		//�U���Q
	AniEn[2][4][0].Bmp = lpDDSOff_En2;		//�_���[�W

	//�G�l�~�[�R(���J��
	AniEn[4][0][0].Bmp = lpDDSOff_En3;		//�ҋ@
	AniEn[4][1][0].Bmp = lpDDSOff_En3;		//���s
	AniEn[4][2][0].Bmp = lpDDSOff_En3;		//�e��
	AniEn[4][3][0].Bmp = lpDDSOff_En3;		//�_���[�W

	//�G�l�~�[�S�i��
	AniEn[5][0][0].Bmp = lpDDSOff_En4;		//�ҋ@
	AniEn[5][1][0].Bmp = lpDDSOff_En4;		//�ړ�
	AniEn[5][2][0].Bmp = lpDDSOff_En4;		//�e��
	AniEn[5][3][0].Bmp = lpDDSOff_En4;		//�_���[�W
	
	//�G�l�~�[�T�i�ΐl��
	AniEn[6][0][0].Bmp = lpDDSOff_En5;		//�ҋ@
	AniEn[6][1][0].Bmp = lpDDSOff_En5;		//�ړ�
	AniEn[6][2][0].Bmp = lpDDSOff_En5;		//�`���[�W
	AniEn[6][3][0].Bmp = lpDDSOff_En5;		//�_���[�W

	//�G�l�~�[�U�i�}
	AniEn[7][0][0].Bmp = lpDDSOff_En6;		//�ҋ@
	AniEn[7][1][0].Bmp = lpDDSOff_En6;		//�U��
	AniEn[7][2][0].Bmp = lpDDSOff_En6;		//�_���[�W

	//�G�l�~�[�V�i�S��
	AniEn[8][0][0].Bmp = lpDDSOff_En7;		//�ҋ@
	AniEn[8][1][0].Bmp = lpDDSOff_En7;		//�A�^�b�N
	AniEn[8][2][0].Bmp = lpDDSOff_En7;		//�W�����v
	AniEn[8][3][0].Bmp = lpDDSOff_En7;		//�_���[�W
	AniEn[8][4][0].Bmp = lpDDSOff_En7;		//���C

	//�G�l�~�[�W�i������
	AniEn[9][0][0].Bmp = lpDDSOff_En8;		//�ړ�
	AniEn[9][1][0].Bmp = lpDDSOff_En8;		//�_���[�W���U��

	//�G�l�~�[�X�i�I
	AniEn[10][0][0].Bmp = lpDDSOff_En9;		//�ړ�
	AniEn[10][1][0].Bmp = lpDDSOff_En9;		//�U��
	AniEn[10][2][0].Bmp = lpDDSOff_En9;		//�_���[�W

	//�c�{
	AniEn[11][0][0].Bmp = lpDDSOff_EnTubo;		//�ҋ@1
	AniEn[11][1][0].Bmp = lpDDSOff_EnTubo;		//�ҋ@�Q
	AniEn[11][2][0].Bmp = lpDDSOff_EnTubo;		//�ҋ@�R
	AniEn[11][3][0].Bmp = lpDDSOff_EnTubo;		//�ҋ@�S
	AniEn[11][4][0].Bmp = lpDDSOff_EnTubo;		//�ҋ@�T
	
	//�G�l�~�[�P�O�i����
	AniEn[12][0][0].Bmp = lpDDSOff_En10;		//�ҋ@�P
	AniEn[12][1][0].Bmp = lpDDSOff_En10;		//����
	AniEn[12][2][0].Bmp = lpDDSOff_En10;		//�f��
	AniEn[12][3][0].Bmp = lpDDSOff_En10;		//�_���[�W

	//�{�X�P�i��
	AniEn[3][0][0].Bmp = lpDDSOff_Boss1;
	AniEn[3][1][0].Bmp = lpDDSOff_Boss1;	//�ړ�
	AniEn[3][2][0].Bmp = lpDDSOff_Boss1;	//���݂�
	AniEn[3][3][0].Bmp = lpDDSOff_Boss1;	//�_���[�W

	//GameLoad("MapData160-40_2.map");
	GameLoad("MAP\\MAP0_320-40_tipbmp8.map");			//�}�b�v�f�[�^�����[�h	
	//	EneOnPosLoad("EneOnData-30.enp");				//�G�l�~�[�̏o���ʒu�f�[�^�����[�h
	EneOnPosLoad("ENEON_��2.enp");				//�G�l�~�[�o���ʒu�f�[�^�����[�h�i�؂̃X�e�[�W�p

	//�v���C���[�����X�e�[�^�X
	Plr.MaxHp = 500;
	Plr.Atk = 15;
	Plr.Spd = 5;

	Swd.MaxHp = 30;

	WMoveX = (279<<5);
}

/*-------------------------------------------------------------------------------------------------------
�@�@�Q�[���̉�����܂Ƃ߂���`�֐��B
�@�@���b�Z�[�W�I������Ɏ��s����B
-------------------------------------------------------------------------------------------------------*/
void GameRelease()	//�Q�[���̉���������s���֐�
{
	//OutputDebugString("����");

	//���K�o���ʒu�f�[�^�̃��������
	if(pEneOn == NULL)	//������悤�Ƃ��Ă���ϐ��̃��������m�ۂ���Ă��Ȃ�������
		MessageBox(NULL,"�|�C���^�ϐ��ɂ̓��������m�ۂ���Ă��܂���(pEneOn)","�G���[",MB_OK);

	pEneOn = (ENE_ONPOS *)GlobalFree(pEneOn);	//���������
	
	if(pEneOn != NULL)	//GlobalFree�̖ߒl��NULL����Ȃ�������G���[�ʒm
		MessageBox(NULL,"������������s","�G���[(pEneOn)",MB_OK);		

	//���}�b�v�f�[�^�̃��������
	if(pMap == NULL)	//������悤�Ƃ��Ă���ϐ��̃��������m�ۂ���Ă��Ȃ�������
		MessageBox(NULL,"�|�C���^�ϐ��ɂ̓��������m�ۂ���Ă��܂���(pMap)","�G���[",MB_OK);
	pMap = (int *)GlobalFree(pMap);	//���������
	if(pMap != NULL)	//GlobalFree�̖߂�l��NULL����Ȃ�������G���[�ʒm
		MessageBox(NULL,"������������s","�G���[(pMap)",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
}