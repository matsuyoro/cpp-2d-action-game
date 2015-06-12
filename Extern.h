//�O���ϐ����ADirectDraw�X�P���g���̂���\�[�X�t�@�C���ȊO�Ŏg�p���邽�߂̃w�b�_�t�@�C��
#if !defined __EXTERNMACRO
#define __EXTERNMACRO
//������������������������������������������������������������������������������������������������������������
#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "Define.h"		//�O���ϐ����������߂̃w�b�_
/*-----------------------------------------------------------------
	�ϐ��錾
-----------------------------------------------------------------*/
extern HWND hWnd;									//�E�B���h�E�̃n���h��

extern LPDIRECTDRAW7		lpDD;				//DirectDraw7�I�u�W�F�N�g�ւ̃|�C���^
extern LPDIRECTDRAWSURFACE7	lpDDSPrimary;			//DirectDrawSurface7�I�u�W�F�N�g�ւ̃|�C���^
extern LPDIRECTDRAWSURFACE7	lpDDSBackBuffer;		//DirectDrawSurface7�I�u�W�F�N�g�ւ̃|�C���^

extern LPDIRECTDRAWPALETTE lpDDPal;	//�I�u�W�F�N�g�ւ̃|�C���^���󂯎�邽�߂̕ϐ�

extern PALETTEENTRY MainPal[256];	//�Q�T�U�F���p��
extern PALETTEENTRY SubPal[256];	//�ύX�p

//extern LPDIRECTDRAWSURFACE7	lpDDSOff;
//extern LPDIRECTDRAWSURFACE7	lpDDSOff2;

extern LPDIRECTDRAWSURFACE7 lpDDSOff_Text;					//�v���C���[�̃Q�[�W�Ȃǂ̉摜
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Title;					//�^�C�g���p�̊G
extern LPDIRECTDRAWSURFACE7 lpDDSOff_StageSelect;			//�X�e�[�W�Z���N�g��ʂ̊G
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Pouse;				//�|�[�Y��ʂ̊G


extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip;				//�}�b�v�`�b�v�̃I�t�X�N���[���T�[�t�F�[�X������
extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip2;				//�}�b�v�`�b�v�Q(�p��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_MapTip3;				//�}�b�v�`�b�v�R�i���J


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back0;				//�w�i�O(�X�X�e�[�W�p
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back1;				//�w�i�P�i�p�ЃX�e�[�W�p
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back1_OBJ;			//�w�i�P�I�u�W�F�i�p�ЃX�e�[�W�p
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back2;				//�w�i�Q�i������n�X�e�[�W�p
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Back3;				//�w�i�R�i���X�e�[�W

extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharWAIT;				//�v���C���[�ҋ@
extern LPDIRECTDRAWSURFACE7 lpDDSOff_Char;					//�v���C���[�ړ���
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDash;				//�v���C���[�_�b�V����
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDown;				//�v���C���[���Ⴊ�݂�
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackY;			//�v���C���[���a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharAttackT;			//�v���C���[�c�a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJump;				//�v���C���[�W�����v
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDead;				//�v���C���[�����
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDamage;			//�v���C���[�_���[�W��������G
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackY;		//�v���C���[���Ⴊ�݉��a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownAttackT;		//�v���C���[���Ⴊ�ݏc�a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackY;		//�v���C���[�W�����v���a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpAttackT;		//�v���C���[�W�����v�c�a��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharUpSwd;			//�v���C���[�㌕����
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharLRSwd;			//�v���C���[���E������
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharJumpDownSwd;		//�v���C���[�W�����v��������
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharDownSwd;			//�v���C���[���Ⴊ�݌�����
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharBall;				//�v���C���[�{�[��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharReturnSwd;		//�v���C���[���z��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_CharSwdHPUP;			//�v���C���[�ƌ���HP����ւ��摜


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Swd;				//��

extern LPDIRECTDRAWSURFACE7 lpDDSOff_En1;				//�G�l�~�[�P
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En2;				//�G�l�~�[�Q
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En3;				//�G�l�~�[�R
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En4;				//�G�l�~�[�S
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En5;				//�G�l�~�[�T
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En6;				//�G�l�~�[�U�i������
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En7;				//�G�l�~�[�V�i�S��
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En8;				//�G�l�~�[�W�i������
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En9;				//�G�l�~�[�X�i�I
extern LPDIRECTDRAWSURFACE7 lpDDSOff_EnTubo;			//�c�{
extern LPDIRECTDRAWSURFACE7 lpDDSOff_En10;				//�G�l�~�[�P�O�i����


extern LPDIRECTDRAWSURFACE7 lpDDSOff_Boss1;			//�{�X�P

extern LPDIRECTDRAWSURFACE7 lpDDSOff_Shot;				//�e

extern LPDIRECTDRAWSURFACE7 lpDDSOff_EF;				//�G�t�F�N�g

extern LPDIRECTDRAWSURFACE7 lpDDSOff_OBJ;				//�I�u�W�F�N�g

extern DWORD FPS_Disp;			//�P�b�ԂŁA�Q�[��������������s�ł�����
extern JOYINFOEX JoyData;		//JOYINFOEX�^�\���́i���݂̃W���C�X�e�B�b�N�̃f�[�^�j
extern JOYINFOEX JoyData2;		//�i�O��̃W���C�X�e�B�b�N�̃f�[�^�j

extern int GameNum;		//�ǂ̏��������s���邩�������ϐ�GameNum��0�i�ŏ��̓^�C�g����ʁj�ŏ�����
extern int StageNum;	//�X�e�[�W��I�Ԃ̂Ɉ����l	

extern double SinT[720];	//�T�C���e�[�u��

extern int CmdNum[8];	//�S�܂ł̃R�}���h���͂̃L�[�f�[�^������
extern int CmdCnt[8];	//�{�^�������������Ԃ�����
extern int WMoveChkX,WMoveChkY;	//�O��̃}�b�v�`�b�v�X�N���[��XY���g���A�ǂꂾ���ړ�������������
extern int Nage;	//�����Ȃ������ǂ���������
extern int Muteki;	//�v���C���[�̖��G���Ԃ�����


extern struct CHR_DATA Plr;				//�v���C���[�̍\����
extern struct CHR_DATA Dum[3];	//�v���C���[�c���p�L�����f�[�^
extern struct CHR_DATA Swd;				//���̍\����
extern struct CHR_DATA EnemyNum[];			//�G�l�~�[�f�[�^
extern struct CHR_DATA En[ENE_MAX];			//�G�l�~�[�̍\����
extern struct SHOT_DATA ShotData[];			//�V���b�g�̃f�[�^
extern struct SHOT_DATA Shot[SHOT_MAX];		//�e�������\����
extern struct EF_DATA EFData[];			//�G�t�F�N�g�̃f�[�^
extern struct EF_DATA EF[EF_MAX];		//�G�t�F�N�g�������\����
extern struct OBJ_DATA OBJData[];		//�I�u�W�F�N�g�̃f�[�^
extern struct OBJ_DATA Obj[OBJ_MAX];	//�I�u�W�F�N�g�������\����
extern struct BGOBJ_DATA BGOBJData[]; 		//BG�I�u�W�F�N�g�̃f�[�^
extern struct BGOBJ_DATA BgObj[BGOBJ_MAX];	//�w�i�I�u�W�F�������\����

extern struct ANIME_DATA Anime[][21];	//�A�j���[�V�����f�[�^
extern struct ANIME_DATA AniSwd[][9];	//���̃A�j���[�V�����f�[�^
extern struct ANIME_DATA AniEn[][ENEACT_MAX][11];	//�G�̃A�j���[�V�����f�[�^

extern struct WAZA_DATA WazaCmd[CMD_MAX];	//�R�}���h�f�[�^������
extern int CmdGet;	//���������R�}���h�̔ԍ�������


//�G�l�~�[�o���ʒu
extern struct ENE_ONPOS EneOnPos_Max;	//�K�o���ʒu�̐��������i��Ł@�t�@�C�����[�h�Œl���󂯎��
//�������m��
extern struct ENE_ONPOS *pEneOn;			//�K�o���ʒu�̃f�[�^ //�g�p���ĂȂ��|�C���^�ϐ��ɂ�NULL�����Ă���

//extern struct ENE_ONPOS EneOn[ENEONPOS_MAX];	//�G�l�~�[�̏o������|�C���g���P�O�O�܂Őݒ�


//�}�b�v
extern int *pMap;	//�g�p���ĂȂ��|�C���^�ϐ��ɂ�NULL�����Ă���

extern int MapXnum;			//�}�b�v�`�b�v�̃��R�̐�
extern int MapYnum;			//�}�b�v�`�b�v�̃^�e�̐�
//extern int Map[MAP_YNUM][MAP_XNUM];			//�}�b�v�̃f�[�^
extern int Tip[100];						//�}�b�v�`�b�v�̎�ނ�����
extern int x;
extern int y;
extern int WorldX,WorldY;		//X�����AY�����ɃX�N���[��������
extern int WMoveX,WMoveY;
extern double BGScrX;			//�w�i�̃X�N���[��������


extern int xbox,ybox,wbox,hbox;

extern int Key;		//�\���L�[�̃f�[�^��ۑ�����
extern int AllCnt;	//�R�}���h���͂̎��Ԃ�����
extern int Btn1;	//�����Ă���{�^���������i�L�[�{�[�h��p�j
extern int Btn2;	//�P�O�̉������邩���Ȃ���������
extern int BtnCnt;	//�{�^���̉����Ă��鎞�Ԃ������f�[�^��ۑ�����



extern int FPS_ChangeNum;	//�Q�[���̏������x�����R�ɒ��߂��邽�߂̕ϐ�
//��������������������������������������������������������������������������������������������������������������
#endif
