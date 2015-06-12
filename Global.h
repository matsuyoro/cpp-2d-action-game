//�O���ϐ��錾�̃w�b�_
#if !defined __GLOBALMACRO
#define __GLOBALMACRO
//��������������������������������������������������������������������������������������������������������������
#include <windows.h>
#include <ddraw.h>	

#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "Define.h"	//�O���ϐ����������߂̃w�b�_
/*-----------------------------------------------------------------
	�ϐ��錾
-----------------------------------------------------------------*/
LPSTR lpszWinClsName = "DirectDraw_Sample";					//�E�B���h�E�N���X��
LPSTR lpszWinTitle = "DirectDraw Skeleton Program Sample";	//�E�B���h�E�^�C�g��
//-------------------------------------------------------------------

HWND hWnd;									//�E�B���h�E�̃n���h��

LPDIRECTDRAW7			lpDD;				//DirectDraw7�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTDRAWSURFACE7	lpDDSPrimary;		//DirectDrawSurface7�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTDRAWSURFACE7	lpDDSBackBuffer;	//DirectDrawSurface7�I�u�W�F�N�g�ւ̃|�C���^

LPDIRECTDRAWPALETTE		lpDDPal;			//�I�u�W�F�N�g�ւ̃|�C���^���󂯎�邽�߂̕ϐ�

PALETTEENTRY MainPal[256];					//�Q�T�U�F���p��
PALETTEENTRY SubPal[256];					//�ύX�p


//�I�t�X�N���[���T�[�t�F�[�X�i�@�� ����͋t��
LPDIRECTDRAWSURFACE7 lpDDSOff_Text;					//�v���C���[�̃Q�[�W�Ȃǂ̉摜
LPDIRECTDRAWSURFACE7 lpDDSOff_Title;				//�^�C�g���p�̊G
LPDIRECTDRAWSURFACE7 lpDDSOff_StageSelect;			//�X�e�[�W�Z���N�g��ʂ̊G
LPDIRECTDRAWSURFACE7 lpDDSOff_Pouse;				//�|�[�Y��ʂ̊G

LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip;				//�}�b�v�`�b�v(�X�j�̃I�t�X�N���[���T�[�t�F�[�X������
LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip2;				//�}�b�v�`�b�v�Q(�p�ЁA������n
LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip3;				//�}�b�v�`�b�v�R�i���J

LPDIRECTDRAWSURFACE7 lpDDSOff_Back0;				//�w�i�O(�X�X�e�[�W�p
LPDIRECTDRAWSURFACE7 lpDDSOff_Back1;				//�w�i�P�i�p�ЃX�e�[�W�p
LPDIRECTDRAWSURFACE7 lpDDSOff_Back1_OBJ;			//�w�i�P�I�u�W�F�i�p�ЃX�e�[�W�p
LPDIRECTDRAWSURFACE7 lpDDSOff_Back2;				//�w�i�Q�i������n�X�e�[�W�p
LPDIRECTDRAWSURFACE7 lpDDSOff_Back3;				//�w�i�R�i���X�e�[�W

LPDIRECTDRAWSURFACE7 lpDDSOff_CharWAIT;				//�v���C���[�ҋ@
LPDIRECTDRAWSURFACE7 lpDDSOff_Char;					//�v���C���[�ړ���
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDash;				//�v���C���[�_�b�V����
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDown;				//�v���C���[���Ⴊ�݂�
LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackY;			//�v���C���[���a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackT;			//�v���C���[�c�a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJump;				//�v���C���[�W�����v
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDead;				//�v���C���[�����
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDamage;			//�v���C���[�_���[�W��������G
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackY;		//�v���C���[���Ⴊ�݉��a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackT;		//�v���C���[���Ⴊ�ݏc�a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackY;		//�v���C���[�W�����v���a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackT;		//�v���C���[�W�����v�c�a��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharUpSwd;			//�v���C���[�㌕����
LPDIRECTDRAWSURFACE7 lpDDSOff_CharLRSwd;			//�v���C���[���E������
LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpDownSwd;		//�v���C���[�W�����v��������
LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownSwd;			//�v���C���[���Ⴊ�݌�����
LPDIRECTDRAWSURFACE7 lpDDSOff_CharBall;				//�v���C���[�o���A
LPDIRECTDRAWSURFACE7 lpDDSOff_CharReturnSwd;		//�v���C���[���z��
LPDIRECTDRAWSURFACE7 lpDDSOff_CharSwdHPUP;			//�v���C���[�ƌ���HP����ւ��摜

LPDIRECTDRAWSURFACE7 lpDDSOff_Swd;				//��

LPDIRECTDRAWSURFACE7 lpDDSOff_En1;				//�G�l�~�[�P�i��
LPDIRECTDRAWSURFACE7 lpDDSOff_En2;				//�G�l�~�[�Q�i�Ƃ���
LPDIRECTDRAWSURFACE7 lpDDSOff_En3;				//�G�l�~�[�R�i������
LPDIRECTDRAWSURFACE7 lpDDSOff_En4;				//�G�l�~�[�S�i��
LPDIRECTDRAWSURFACE7 lpDDSOff_En5;				//�G�l�~�[�T�i���l
LPDIRECTDRAWSURFACE7 lpDDSOff_En6;				//�G�l�~�[�U�i������
LPDIRECTDRAWSURFACE7 lpDDSOff_En7;				//�G�l�~�[�V�i�S��
LPDIRECTDRAWSURFACE7 lpDDSOff_En8;				//�G�l�~�[�W�i������
LPDIRECTDRAWSURFACE7 lpDDSOff_En9;				//�G�l�~�[�X�i�I
LPDIRECTDRAWSURFACE7 lpDDSOff_EnTubo;			//�c�{
LPDIRECTDRAWSURFACE7 lpDDSOff_En10;				//�G�l�~�[�P�O�i����


LPDIRECTDRAWSURFACE7 lpDDSOff_Boss1;			//�{�X�P

LPDIRECTDRAWSURFACE7 lpDDSOff_Shot;				//�e

LPDIRECTDRAWSURFACE7 lpDDSOff_EF;				//�G�t�F�N�g

LPDIRECTDRAWSURFACE7 lpDDSOff_OBJ;				//�I�u�W�F�N�g


DWORD FPS_Disp;			//�P�b�ԂŁA�Q�[��������������s�ł�����
JOYINFOEX JoyData;		//JOYINFOEX�^�\���́i���݂̃W���C�X�e�B�b�N�̃f�[�^�j
JOYINFOEX JoyData2;		//�i�O��̃W���C�X�e�B�b�N�̃f�[�^�j

int GameNum = 0;	//�ǂ̏��������s���邩�������ϐ�GameNum��0�i�ŏ��̓^�C�g����ʁj�ŏ�����
int StageNum = 0;	//�X�e�[�W��I�Ԃ̂Ɉ����l	

double SinT[720];		//�T�C���e�[�u��

int CmdNum[8]={0,0,0,0,0,0,0,0};	//�S�܂ł̃R�}���h���͂̃L�[�f�[�^������
int CmdCnt[8]={0,0,0,0,0,0,0,0};	//�{�^�������������Ԃ�����
int WMoveChkX,WMoveChkY;	//�O��̃}�b�v�`�b�v�X�N���[��XY���g���A�ǂꂾ���ړ�������������(�X�N���[������ƓG�ƃ}�b�v���ꏏ���炷�j

int Nage = 0;	//�����Ȃ������ǂ���������
int Muteki = 0;	//�v���C���[�̖��G���Ԃ�����


//���v���C���[��
struct CHR_DATA Plr = {-1,320,240,64,96,0,0,0,0,0,0,FALSE,0.,230,200,0,FALSE,50,TRUE};	//�v���C���[�̍\����
struct CHR_DATA Dum[3];	//�v���C���[�c���p�L�����f�[�^

//���@���@��
struct CHR_DATA Swd = {-2,230,200,92,92,0,0,0,0,0,0,FALSE,0.,230,200,0,FALSE,30,TRUE};	//���̍\����

//���G�l�~�[��
struct CHR_DATA EnemyNum[] =	//�G�l�~�[�̃f�[�^
{//																								  Atk					
	{0,0,0,0,0,0,0,0,0,0,0,FALSE,0.,0,0,0,FALSE,0,FALSE,				{0,0,0,0,0},},				//��
	{1,400,100,96,64,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,10,FALSE,		{0,1,2,3,0},0,0,0,0,0,0,10,3},		//�G�l�~�[�̍\����
	{2,500,100,128,80,1,0,0,0,0,0,FALSE,0.,500,100,0,FALSE,20,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,20,3},		//�G�l�~�[�Q�̍\����
	{3,550,250,112,80,1,0,0,0,0,0,FALSE,0.,500,100,0,FALSE,300,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,300,3},		//�G�l�~�[�R�i�{�X�P�̍\����
	{4,400,100,64,84,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,30,FALSE,		{0,3,2,1,0},0,0,0,0,0,0,30,3},			//�G�l�~�[�R�̍\����
	{5,100,200,72,84,1,0,0,0,0,0,FALSE,0.,100,200,0,FALSE,18,FALSE,		{0,1,3,0,2},0,0,0,0,0,0,18,3},			
	{6,100,150,64,116,1,0,0,0,0,0,FALSE,0.,100,150,0,FALSE,50,FALSE,	{0,1,2,3,0},0,0,0,0,0,0,50,5},
	{7,240,100,32,32,1,0,0,0,0,0,FALSE,0.,240,100,0,FALSE,1,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,1,3},
	{8,400,100,128,80,2,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,120,FALSE,	{0,6,2,3,0},0,0,0,0,0,0,120,5},		//�G�l�~�[�̍\����
	{9,400,100,32,32,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,5,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,5,1},		//�i������
	{10,90,100,56,64,1,0,0,0,0,0,FALSE,0.,400,100,0,FALSE,30,FALSE,		{0,1,0,0,0},0,0,0,0,0,0,30,3},		//�G�l�~�[�i�I	
	{11,280,100,64,96,1,0,0,0,0,0,FALSE,0.,280,100,0,FALSE,5,FALSE,		{0,0,0,0,0},0,0,0,0,0,0,5,0},		//�c�{
	{12,280,100,96,64,1,0,0,0,0,0,FALSE,0.,280,100,0,FALSE,60,FALSE,	{0,0,1,2,0},0,0,0,0,0,0,60,10}		//����
};
struct CHR_DATA En[ENE_MAX];		//�G�l�~�[�̍\����

//���@�e�@��
struct SHOT_DATA ShotData[] =	//�V���b�g�̃f�[�^
{ //Type x	 y	 w	 h	 bx  by	 mx  my  Cnt Max Son&EneOrPlr Hit(x,y,w,h) Atk
	{0	,0	,0	,8	,8	,0	,0	,5	,0	,0	,5	,FALSE	,{0,0,6,6}		,2},	//8*8�̃T�C�Y�̒e
	{1	,0	,0	,8	,8	,96	,0	,7	,0	,0	,1	,FALSE	,{0,0,6,6}		,2},	//8*8�̃T�C�Y�̒e
	{2	,0	,0	,16	,16	,0	,8	,4	,0	,0	,5	,FALSE	,{0,0,12,12}	,5},	//16*16�̃T�C�Y�̒e
	{3	,0	,0	,48	,32	,0	,24	,3	,0	,0	,4	,FALSE	,{0,0,40,28}	,6},	//48*32�̃T�C�Y�̉΂̋�
	{4	,0	,0	,16	,48	,0	,56	,0	,0	,0	,3	,FALSE	,{0,0,14,46}	,4},	//16*48�̃T�C�Y�̉�
	{5	,0	,0	,32	,4	,0	,104,16	,0	,0	,2	,FALSE	,{0,0,32,4}		,8},	//32*4�̃��[�U�[
	{6	,0	,0	,48	,48	,0	,108,5	,0	,0	,5	,FALSE	,{0,0,40,40}	,2},	//48*48�̉��i�������Ή�����
	{7	,0	,0	,32	,32	,0	,156,0	,0	,0	,3	,FALSE	,{0,0,24,24}	,2},	//32*32�̉�
	{8	,0	,0	,4	,4	,128,0	,0	,0	,0	,6	,FALSE	,{0,0,4,4}		,-2},	//4*4�̌�
	{9	,0	,0	,8	,8	,180,0	,0	,0	,0	,3	,FALSE	,{0,0,6,6}		,3},		//�t���ϗ���
	{10	,0	,0	,8	,8	,180,0	,0	,0	,0	,3	,FALSE	,{0,0,6,6}		,2},		//�t���ϐ���
	{11	,0	,0	,8	,8	,192,8	,0	,0	,0	,0	,FALSE	,{0,0,4,4}		,3},		//���I���P
	{12	,0	,0	,8	,8	,208,8	,0	,0	,0	,0	,FALSE	,{0,0,4,4}		,4},		//���I���Q
	{14	,0	,0	,16	,16	,224,8	,0	,0	,0	,0	,FALSE	,{0,0,12,12}	,5},		//���I���P
	{15	,0	,0	,16	,16	,256,8	,0	,0	,0	,0	,FALSE	,{0,0,12,12}	,6},		//���I���Q
	{16	,0	,0	,24	,24	,288,0	,0	,0	,0	,0	,FALSE	,{0,0,20,16}	,7},		//���I��
	{17	,0	,0	,16	,64	,480,0	,13	,0	,0	,4	,FALSE	,{0,0,16,56}	,3},		//�^��
	{18	,0	,0	,8	,8	,0	,192,0	,0	,0	,7	,FALSE	,{0,0,6,6}		,1},		//�|�C�Y��
	{19	,0	,0	,48	,48	,0	,108,15	,0	,0	,5	,FALSE	,{0,0,32,32}	,4},	//48*48�̉�(�Ή�����
	{20	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,FALSE	,{0,0,2,2}		,5},	//���̔j��
	{21	,0	,0	,32	,32	,192,64	,12	,0	,0	,2	,FALSE	,{0,0,32,30}	,5},	//�S�̐^��
	{22	,0	,0	,12	,12	,384,72	,0	,-15,0	,7	,FALSE	,{0,0,10,10}	,5},		//�Œe
	{23	,0	,0	,24	,24	,0	,200,5	,5	,0	,3	,FALSE	,{0,0,12,12}	,10},	//�Ύ΂ߒe
	{24	,0	,0	,24	,24	,384,84	,0	,-20,0	,3	,FALSE	,{0,0,16,16}	,6},		//���e
	{25	,0	,0	,1	,1	,128,4	,0	,-1	,0	,15	,FALSE	,{0,0,1,1}		,0},		//�D�i�P���P�j
	{26	,0	,0	,2	,2	,128,6	,0	,-1	,0	,7	,FALSE	,{0,0,2,2}		,0},			//�D�Q�i�Q���Q�j
	{27	,0	,0	,48	,32	,0	,24	,8	,0	,0	,4	,FALSE	,{0,0,40,28}	,10},	//48*32�̊g�U���鉊
	{28	,0	,0	,16	,16	,256,160,1	,0	,0	,5	,FALSE	,{0,0,14,14}	,10},		//�΃{�[��
	{29	,0	,0	,1	,1	,128,4	,0	,0	,0	,15	,FALSE	,{0,0,80,80}		,0}		//�D�����i�G�t�F�N�g���g�p

};
struct SHOT_DATA Shot[SHOT_MAX];		//�e�������\����

//���G�t�F�N�g��
struct EF_DATA EFData[]=	//�G�t�F�N�g�̃f�[�^
{  //x	 y	 w	 h	 bx	 by	 Cnt Max Son
	{0	,0	,96	,96	,0	,0	,0	,6	,FALSE},	//�����G�t�F�N�g
	{0	,0	,20	,96	,0	,96	,0	,7	,FALSE},	//�c�a��G�t�F�N�g
	{0	,0	,96	,20	,0	,192,0	,5	,FALSE},	//���a��G�t�F�N�g
	{0	,0	,48	,48	,160,96	,0	,5	,FALSE},	//�e�q�b�g�G�t�F�N�g
	{0	,0	,8	,8	,576,0	,0	,6	,FALSE},	//�W���W�̃T�C�Y�̃G�t�F�N�g
	{0	,0	,8	,8	,576,8	,0	,7	,FALSE},	//�W���W�̃T�C�Y�̃G�t�F�N�g�i��
	{0	,0	,8	,8	,576,16	,0	,7	,FALSE},	//�W���W�̃T�C�Y�̃G�t�F�N�g
	{0	,0	,24	,24	,448,96	,0	,4	,FALSE},	//24*24�̂ق���
	{0	,0	,24	,24	,448,120,0	,4	,FALSE},	//24*24�̂ق���Q
	{0	,0	,8	,20	,160,144,0	,9	,FALSE},	//�W���Q�O�̍��̏�����G�t�F�N�g
	{0	,0	,16	,16	,240,144,0	,4	,FALSE},	//���̋z�����ތ��̃G�t�F�N�g
	{0	,0	,16	,24	,160,168,0	,5	,FALSE},	//�΂̖����̌��̃G�t�F�N�g
	{0	,0	,32	,32	,256,160,0	,8	,FALSE}		//���̃G�t�F�N�g
};
struct EF_DATA EF[EF_MAX];		//�G�t�F�N�g�������\����

//���I�u�W�F�N�g��
struct OBJ_DATA OBJData[]=	//�I�u�W�F�N�g�̃f�[�^
{ //Type x	 y	 w	 h	 bx	 by	 Cnt Max Son
	{0	,0	,0	,152,72	,0	,0	,0	,0	,FALSE},	//�{�X�P�̑�
	{1	,0	,0	,92	,64	,152,0	,0	,0	,FALSE},	//�{�X�P�̎�
	{2	,0	,0	,52	,52	,244,0	,0	,0	,FALSE},	//�{�X�P�̎�(100��
	{3	,0	,0	,48	,44	,296,0	,0	,0	,FALSE},	//�{�X�P�̎�i90��
	{4	,0	,0	,40	,40	,344,0	,0	,0	,FALSE}		//�{�X�P�̎�i80%
};
struct OBJ_DATA Obj[OBJ_MAX];	//�I�u�W�F�N�g�������\����

//���o�b�N�O�����h�I�u�W�F�N�g��
struct BGOBJ_DATA BGOBJData[] =		//BG�I�u�W�F�N�g�̃f�[�^1
{ //Type x	 y	 w	 h	 bx	 by	 Cnt Max Son Line
	{0	,0	,0	,64	,64	,0	,0	,0	,0	,0	,},	//���I
	{1	,0	,0	,64	,64	,64	,0	,0	,0	,0	,},	//���I�Q
	{2	,0	,0	,64	,64	,128,0	,0	,0	,0	,},	//���I�R
	{3	,0	,0	,64	,64	,192,0	,0	,0	,0	,},	//���I�S
	{4	,0	,0	,64	,64	,256,0	,0	,0	,0	,},	//���I�T
	{5	,0	,0	,64	,64	,320,0	,0	,0	,0	,},	//���i���j
	{6	,0	,0	,96	,64	,384,0	,0	,0	,0	,3},	//���I�i���j
	{7	,0	,0	,128,64	,480,0	,0	,0	,0	,3},	//���I�i��j
	{8	,0	,0	,96	,96	,0	,64	,0	,0	,0	,4},	//���I�i��j�Q
	{9	,0	,0	,64	,96	,96	,64	,0	,0	,0	,},	//���i���j
	{10	,0	,0	,32	,96	,160,64	,0	,0	,0	,},	//���i���j�Q
	{11	,0	,0	,96	,64	,192,64	,0	,0	,0	,4},	//��
	{12	,0	,0	,96	,96	,288,64	,0	,0	,0	,4},	//��
	{13	,0	,0	,128,96	,416,64	,0	,0	,0	,4},	//��
	//{14	,0	,0	,128,96	,512,64	,0	,0	,0	,3},	//�o�C�N��
	{14	,0	,0	,160,96	,0	,160,0	,0	,0	,5},	//���I�i��j�R
	{15	,0	,0	,128,96	,160,160,0	,0	,0	,},	//�ǂQ
	{16	,0	,0	,128,128,288,160,0	,0	,0	,(rand()%3)+2},	//�ƂQ
	{17	,0	,0	,192,64	,416,160,0	,0	,0	,4},	//�d��
	{18	,0	,0	,64	,128,416,224,0	,0	,0	,5},	//���i���j�Q
	{19	,0	,0	,128,32	,480,224,0	,0	,0	,},	//��
	//{21	,0	,0	,288,224,0	,256,0	,0	,0	,6},		//�Ɓi����j
	{20	,0	,0	,32	,32	,480,256,0	,2	,0	,},		//�z
	{21	,0	,0	,96	,96	,288,352,0	,2	,0	,},		//��
	{22	,0	,0	,32	,32	,480,288,0	,4	,0	,},		//��
	{23	,0	,0	,288,224,0	,256,0	,0	,0	,6},	//�Ɓi����j
	{24	,0	,0	,128,96	,512,64	,0	,0	,0	,3}		//�o�C�N��


};
struct BGOBJ_DATA BgObj[BGOBJ_MAX];	//�w�i�I�u�W�F�������\����

//���v���C���[�A�j���[�V������
struct ANIME_DATA Anime[][21] =	//�A�j���[�V�����̃f�[�^
{
	//�ҋ@�A�j���[�V����
				                             //���u-1�v�Ŏw��ꏊ�̃A�j���[�V�����ɖ߂胋�[�v�A�u-2�v�ł��̃A�j���[�V�������I�����A��{�̃A�j���[�V�����ɖ߂�B
	{{0,10,1,64,96,1},{1,13,1},{2,20,1},{1,7,1},{-1,2,1}},
		  //���Ɓ��ɊG���T�C�Y������
	//�ړ��A�j���[�V����
	{{0,4,1,64,96,2},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{5,4,1},{6,4,1},{7,4,1},{8,4,1},{9,4,1},{10,4,1},{11,4,1},{12,4,1},{13,4,1},{14,4,1},{-1,0,1}},	//�A�j���[�V�����O
	//�_�b�V���A�j���[�V����
	{{0,2,1,64,96,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{9,2,1},{10,2,1},{11,2,1},{12,2,1},{-1,0,1}},						//�A�j���[�V�����P
	//���Ⴊ�݃A�j���[�V����
	{{0,1,1,64,96,2},{1,1,1},{2,1,1},{3,1,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{9,2,1},{-1,0,1}},													//�A�j���[�V�����Q
	//���a��
	{{0,3,0,128,96,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,1}},
	//�c�a��
	{{0,5,0,160,112,2},{1,4,0},{2,4,0},{3,1,0},{4,1,0},{5,1,0},{6,2,0},{7,2,0},{-2,0,1}},
	//�W�����vUP
	{{0,2,1,64,96,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{5,2,1},{6,2,1},{7,2,1},{8,2,1},{-1,0,1}},
	//�W�����vDOWN
	{{10,2,1,64,96,2},{11,2,1},{12,2,1},{13,2,1},{14,2,1},{-1,0,1}},
	//�����
	{{0,5,0,64,96,2},{1,5,0},{2,5,0},{3,5,0},{4,5,0},{5,5,0},{6,5,0},{7,5,0},{8,5,0},{9,5,0},{10,5,0},{11,5,0},{12,5,0},{13,5,0},{14,5,0},{15,5,0},{16,5,0},{17,2,0},{18,2,0},{19,2,0},{-1,0,1}},
	//�_���[�W��������
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,3,0},{2,2,0},{3,2,0},{3,1,0},{-2,0,0}},
	//���Ⴊ�ݏc�a��
	{{0,2,0,128,96,2},{1,3,0},{2,3,0},{3,3,0},{4,1,0},{5,2,0},{6,2,0},{7,2,0},{8,2,0},{9,4,0},{-2,0,0}},
	//���Ⴊ�݉��a��
	{{0,3,0,112,96,2},{1,2,0},{2,2,0},{3,2,0},{4,1,0},{5,2,0},{6,3,0},{-2,0,0}},
	//�W�����v�c�a��
	{{0,2,0,160,96,2},{1,2,0},{2,3,0},{3,1,0},{4,2,0},{6,4,0},{-2,0,0}},
	//�W�����v���a��
	{{0,2,0,112,88,2},{1,1,0},{2,2,0},{3,1,0},{4,1,0},{5,2,0},{-2,0,0}},
	//�㌕����
	{{0,4,0,64,96,1},{1,3,0},{2,2,0},{3,2,0},{4,2,0},{-2,0,0}},
	//���E������
	{{0,2,0,72,96,1},{1,1,0},{2,1,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,0}},
	//�W�����v��������
	{{0,1,0,80,96,1},{1,1,0},{2,1,0},{3,1,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{-2,0,0}},
	//���Ⴊ�݌�����
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{-2,0,0}},
	//�o���A
	{{0,2,0,96,96,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,2,0},{6,2,0},{7,2,0},{8,2,0},{9,2,0},{10,2,0},{11,2,0},{-1,0,0}},
	//���z��
	{{0,2,0,64,96,1},{1,1,0},{2,1,0},{3,1,0},{-1,0,0}},
	//�v���C���[�ƌ���HP����ւ�
	{{0,2,0,64,96,1},{1,2,0},{2,2,0},{3,2,0},{-1,0,0}}
};

//�����A�j���[�V������
struct ANIME_DATA AniSwd[][9] =	//���̃A�j���[�V�����f�[�^
{	//�������
	{{0,1,1,92,92,3},{1,1,1},{2,10,1},{-1,0,1}},
	//��������
	{{3,1,1,92,92,3},{4,1,1},{5,10,1},{-1,0,1}},
	//��������
	{{6,1,1,92,92,3},{7,1,1},{8,10,1},{-1,0,1}},
	//���E����
	{{9,1,1,92,92,3},{10,1,1},{11,10,1},{-1,0,1}},
	//���o��
	{{12,2,0,92,92,3},{13,2,0},{14,2,0},{15,2,0},{16,2,0},{17,2,0},{18,2,0},{19,2,0},{-2,0,0}},
	//��������
	{{15,1,0,92,92,3},{14,1,0},{13,1,0},{12,1,0},{-2,0,0}}
};

//���G�l�~�[�A�j���[�V������
struct ANIME_DATA AniEn[][ENEACT_MAX][11] =	//�G�̃A�j���[�V�����f�[�^
{
	{//��
		{{0,0,0,0,0,0},{-1,0,1}},
	},
	{//�G�l�~�[�P(��
		{{0,15,1,96,64,1},{1,2,1},{2,4,1},{-1,0,1}},				//�ҋ@
		{{0,4,1,96,64,1},{1,5,1},{2,15,1},{3,1,1},{4,1,1},{-1,0,1}},//�A�^�b�N
		{{0,4,0,96,64,1},{1,4,1},{2,2,1},{3,1,1},{4,1,1},{-1,0,1}},	//�W�����v
		{{5,10,0,96,64,1},{-2,0,1}}									//�_���[�W
	},
	{//�G�l�~�[�Q�i�g�J�Q
		{{0,5,1,128,80,2},{5,4,1},{-1,0,1}},									//�ҋ@
		{{0,2,1,128,80,2},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{-1,0,1}},			//�ړ�
		{{0,2,0,128,80,2},{5,2,0},{6,3,0},{7,26,0},{6,2,0},{5,1,0},{-2,0,1}},	//���݂�
		{{0,2,0,128,80,2},{5,3,0},{6,4,0},{7,10,0},{-1,0,1}},					//
		{{8,5,0,128,80,2},{9,20,0},{-2,0,1}}									//�_���[�W
	},
	{//�{�X�P�i��
		{{7,2,0,112,80,2},{6,2,0},{0,1,1},{6,3,0},{7,2,0},{-1,0,1}},											//�ʏ�
		{{0,5,0,112,80,2},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,20,0},{6,16,0},{7,16,0},{-2,0,1}},	//���ݕt��
		{{7,5,0,112,80,2},{0,2,0},{1,2,0},{2,2,0},{3,2,0},{4,2,0},{5,7,0},{-2,0,1}},			//�΂̋�
		{{8,10,0,112,80,2},{-2,0,1}}									//�_���[�W
	},
	{//�G�l�~�[�R�i���J��
		{{0,1,1,64,84,1},{0,1,1},{-2,0,1}},									//�ҋ@
		{{0,4,1,64,84,1},{1,4,1},{2,4,1},{3,4,1},{4,4,1},{3,4,1},{2,4,1},{1,4,1},{-2,0,0}},		//���s
		{{5,15,0,64,84,1},{6,1,0},{5,6,0},{-2,0,0}},							//�e��
		{{7,5,0,64,84,1},{-2,0,1}}										//�_���[�W
	},
	{//�G�l�~�[�S�i��
		{{4,15,1,72,84,2},{4,1,1},{-2,0,1}},						//�ҋ@
		{{0,5,1,72,84,2},{1,5,1},{2,5,1},{3,5,1},{4,5,1},{-2,0,1}},	//�ړ�
		{{6,30,0,72,84,2},{5,1,0},{7,2,0},{-2,0,1}},				//�e��
		{{8,3,0,72,84,2},{9,5,0},{-2,0,1}}							//�_���[�W
	},
	{//�G�l�~�[�T�i��
		{{0,2,1,64,116,2},{1,2,1},{2,2,1},{3,2,1},{4,2,1},{-2,0,1}},	//�ҋ@
		{{5,3,1,64,116,2},{6,3,1},{7,3,1},{8,3,1},{9,3,1},{10,3,1},{11,3,1},{12,3,1},{13,3,1},{14,3,1},{-2,0,1}},	//�ړ�
		{{14,1,1,64,116,2},{15,1,1},{16,1,1},{-1,0,1}},	//�`���[�W
		{{17,10,0,64,116,2},{-2,0,1}}		//�_���[�W
	},
	{//�G�l�~�[�U�i�}
		{{0,30,1,32,32,1},{1,3,1},{0,50,1},{-2,0,1}},	//�ҋ@
		{{2,2,0,32,32,1},{3,2,0},{4,2,0},{5,2,0},{-2,0,1}},	//�U��
		{{6,5,0,32,32,1},{-2,0,1}}	//�_���[�W
	},
	{//�G�l�~�[�V�i�S��
		{{0,8,1,128,80,2},{1,5,1},{0,10,1},{1,7,1},{-1,0,1}},	//�ҋ@
		{{1,10,1,128,80,2},{2,5,1},{3,3,1},{4,1,1},{5,1,1},{6,1,1},{7,1,1},{4,1,1},{-1,0,1}},	//�A�^�b�N
		{{0,3,0,128,80,2},{1,5,0},{3,3,0},{4,1,1},{5,1,1},{6,1,1},{7,1,1},{-1,0,1}},	//�W�����v
		{{8,6,0,128,80,2},{-2,0,1}},													//�_���[�W
		{{2,15,1,128,80,2},{1,25,0},{-1,0,1}}	//���C
	},
	{//�G�l�~�[�W�i������
		{{0,3,1,32,32,1},{1,3,1},{2,3,1},{3,3,1},{4,3,1},{-1,0,1}},	//�ړ�
		{{5,5,0,32,32,1},{6,7,0},{7,8,0},{8,10,0},{9,15,0},{-2,0,1}}	//�_���[�W
	},
	{//�G�l�~�[�X�i�I
		{{0,3,1,56,64,1},{1,3,1},{2,3,1},{3,3,1},{4,3,1},{-1,0,1}},	//�ړ�
		{{5,20,0,56,64,1},{6,5,0},{-2,0,1}},						//�U��
		{{7,30,0,56,64,1},{-2,0,1}}									//�_���[�W
	},
	{//�c�{
		{{0,2,1,64,96,1},{-1,0,1}},	//�ҋ@1
		{{1,2,1,64,96,1},{-1,0,1}},
		{{2,2,1,64,96,1},{-1,0,1}},
		{{3,2,1,64,96,1},{-1,0,1}},
		{{4,2,1,64,96,1},{-1,0,1}}
	},
	{//����
		{{0,40,1,96,64,1},{-1,0,1}},										//�ҋ@
		{{0,5,0,96,64,1},{1,4,0},{2,5,0},{-2,0,1}},						//���ݕt��
		{{0,3,0,96,64,1},{1,2,0},{2,6,0},{1,1,0},{0,10,0},{-2,0,1}},	//�f��
		{{3,30,0,96,64,1},{-2,0,1}}												//�_���[�W
	}
};


//�R�}���h�f�[�^
struct WAZA_DATA WazaCmd[CMD_MAX] =	//�L�[��3�񕪂̓��͂܂ň���
{
	{{8,12,4,-1},(1<<1),20},	//���A�E���A�E�@�{�@�{�^���P
	{{1,0,1,-1},0,20},
	{{2,0,2,-1},0,100},
	{{1,0,4,-1},1,20},			//Plr�ƌ���HP����ւ�
	{{4,0,1,-1},1,20},			//Plr�ƌ���HP����ւ�
	{{1,8,9,-1},1,20},			//���z����
	{{4,8,12,-1},1,20},			//���z���E
	{{1,8,9,-1},(1<<1),20},		//�o���A��
	{{4,8,12,-1},(1<<1),20}		//�o���A�E
};
int CmdGet = 0;	//���������R�}���h�̔ԍ�������


//�G�l�~�[�o���ʒu
struct ENE_ONPOS EneOnPos_Max = {0,0,0,FALSE};	//�K�o���ʒu�̐��������i��Ł@�t�@�C�����[�h�Œl���󂯎��
//�������m��
struct ENE_ONPOS *pEneOn;			//�K�o���ʒu�̃f�[�^ //�g�p���ĂȂ��|�C���^�ϐ��ɂ�NULL�����Ă���

/*struct ENE_ONPOS EneOn[ENEONPOS_MAX] =	//�G�l�~�[�̏o������|�C���g���P�O�O�܂Őݒ�
{
	{650,400,1,FALSE},				//�G�l�~�[�P��650,400�̃|�C���g�ɏo��������
};*/


//�}�b�v
//�������m��
int *pMap = NULL;			//�}�b�v�̃f�[�^ //�g�p���ĂȂ��|�C���^�ϐ��ɂ�NULL�����Ă���

int MapXnum = 100;			//�}�b�v�`�b�v�̃��R�̐�(��Ń}�b�v�f�[�^����f�[�^�����
int MapYnum = 100;			//�}�b�v�`�b�v�̃^�e�̐�
//int Map[MAP_YNUM][MAP_XNUM];			//�}�b�v�̃f�[�^


//�}�b�v�`�b�v�̎�ނ�����(0���z�u���Ȃ��`�b�v�A�P���ʂ�Ȃ��`�b�v�A�Q�������ʂ�`�b�v�A�R���A�j���[�V��������`�b�v 
int Tip[TIP_MAX] =	//�Q�[���Ŏg�p����`�b�v�ʉ߃t���O
//�ŏ��͐X�̃X�e�[�W�Ȃ̂ŐX�̃X�e�[�W�̃`�b�v�ʉ߃t���O��Tip�ɏ�����
//	0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0	//�X�̃X�e�[�W
{	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,
	1,1,1,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,
	1,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1,2,2,2,2,	//5
	1,1,1,1,1,1,2,2,2,1,2,2,2,1,2,1,2,2,2,2,
	1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,1,1,1,
	1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2,2,1,1,1,
	1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,2,1,1,1,1,
	1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,	//10
	1,1,1,1,1,1,1,1,1,1,3,2,3,2,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,3,2,3,2,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	};//15
	
     
int x=0;
int y=0;
int WorldX=0,WorldY=0;		//X�����AY�����ɃX�N���[��������
int WMoveX = 0,WMoveY = 0;
double BGScrX=0;			//�w�i�̃X�N���[��������


int xbox,ybox,wbox,hbox;

int Key = 0;	//�\���L�[�̃f�[�^��ۑ�����
int AllCnt = 0;	//�R�}���h���͂̎��Ԃ�����
int Btn1 = 0;	//�����Ă���{�^���������i�L�[�{�[�h��p�j
int Btn2 = 0;	//�P�O�̉����Ă��邩�����Ă��Ȃ���������
int BtnCnt = 0;	//�{�^���̉����Ă��鎞�Ԃ������f�[�^��ۑ�����



int FPS_ChangeNum = 80;	//WinMain�Ŏg�p
//��������������������������������������������������������������������������������������������������������������
#endif
