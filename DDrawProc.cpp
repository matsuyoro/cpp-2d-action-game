/*------------------------------------------------------------------
	�w�b�_�[�t�@�C���̃C���N���[�h
------------------------------------------------------------------*/
#include <windows.h>
#include <ddraw.h>

//�O���ϐ��錾
#include "Define.h"		//�}�N����`�̃w�b�_
#include "Global.h"		//�O���ϐ��錾�̃w�b�_

//�v���g�^�C�v�錾
#include "DirectSound.h"
#include "DirectMusic.h"
#include "GameInit.h"	//�Q�[���̏����A���������֐��̃v���g�^�C�v�錾�̃w�b�_
#include "Main.h"		//�Q�[�����C���̃v���g�^�C�v�錾�̃w�b�_

#pragma comment( lib, "dsound.lib" )
#pragma comment( lib, "dxguid.lib" )

/*-------------------------------------------------------------------
	�֐��̃v���g�^�C�v�錾
-------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND,UINT,WPARAM,LPARAM );	//�E�B���h�E�v���V�[�W��
BOOL	CreateDD( HWND );		//DirectDraw�̐���
void	ReleaseDD( void );		//DirectDraw�̉��
BOOL	PaletteCreate( HWND );	//�p���b�g

LPDIRECTDRAWSURFACE7 SetUp_OffScreen(char*);	//�I�t�X�N���[���T�[�t�F�[�X�̊֐��̃v���g�^�C�v�錾

/*-----------------------------------------------------------------
	WinMain�֐�
-----------------------------------------------------------------*/
int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance,
				    LPSTR lpszArgs,int nWinScreenMode )
{
	MSG			msg;
	WNDCLASSEX	wcex;	//�E�B���h�E�N���X�ݒ�p�̍\����
	//HWND		hWnd;

	DWORD oldtime = 0;	//�O��A�Q�[���̃��C���������������̎���(�t���[�����[�g�Ŏg�p�j
	DWORD nowtime = 0;	//���݂̎��ԁi�t���[�����[�g�Ŏg�p�j
	DWORD FPS_oldtime;	//�P�b�Ԃ��������ǂ����𔻒肷��̂Ɏg�p
	DWORD FPS_Cnt;		//�Q�[�������̎��s�񐔂𐔂���J�E���^


	//�E�B���h�E�E�N���X�ݒ�
	wcex.cbSize = sizeof(wcex);
	//WNDCLASSEX�\���̂̃T�C�Y
	wcex.style = 0;												//�E�B���h�E�N���X�̃X�^�C��
	wcex.lpfnWndProc = (WNDPROC)WndProc;						//�E�B���h�E�v���V�[�W��
	wcex.cbClsExtra = 0;										//�g���p�̃p�����[�^
	wcex.cbWndExtra = 0;										//�g���p�̃p�����[�^
	wcex.hInstance = hInstance;									//�C���X�^���X�n���h��
	wcex.hIcon = LoadIcon(NULL,IDI_APPLICATION);				//�A�C�R���̃n���h��
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);					//�J�[�\���̃n���h��
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//�w�i�F�ݒ�
	wcex.lpszMenuName = NULL;									//�N���X�̃��j���[
	wcex.lpszClassName = lpszWinClsName;						//�E�B���h�E�N���X��
	wcex.hIconSm = LoadIcon(NULL,IDI_APPLICATION);				//�X���[���A�C�R���̃n���h��

	//���E�B���h�E�E�N���X�o�^
	if(!RegisterClassEx(&wcex))	return 0;
	//���E�B���h�E�쐬
	hWnd = CreateWindowEx(
		WS_EX_TOPMOST,	//�g���E�B���h�E�X�^�C��
		lpszWinClsName,	//�E�B���h�E�N���X��
		lpszWinTitle,	//�E�B���h�E�̃^�C�g��
		WS_POPUP,		//�E�B���h�E�̃X�^�C��
		0,				//�E�B���h�E�̍���X���W
		0,				//�E�B���h�E�̍���Y���W
		SCREEN_WIDTH,	//�E�B���h�E�̕�
		SCREEN_HEIGHT,	//�E�B���h�E�̍���
		NULL,			//�e�E�B���h�E�̃n���h��
		NULL,			//���j���[�̃n���h��
		hInstance,		//�C���X�^���X�n���h��
		NULL			//�g���p�̃p�����[�^
		);
	ShowWindow( hWnd,nWinScreenMode );
	UpdateWindow( hWnd );
	ShowCursor( FALSE );	//�}�E�X�J�[�\�����\���ɂ���

	//DirectDraw�I�u�W�F�N�g�̐���
	if( !CreateDD(hWnd) )	//CreateDD()��DirectDraw�쐬
	{
		ReleaseDD();		//���s���Ă�����A�����Ƀv���O�����I��
		return FALSE;
	}
	//DirectSound�I�u�W�F�N�g�̏�����
	if(!DS_Init())
	{
		ReleaseDS();
		return FALSE;
	}

	// �Z�J���_���o�b�t�@���쐬���A�T�E���h�f�[�^��ǂݍ���
	for(int i = 0;i < SOUND_MAX;i ++)
	{
		if(!DS_Load(i))
		{
			ReleaseDS();
			return FALSE;
		}
	}

	// �_�C���N�g�~���[�W�b�N�̏��������s��
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
			nowtime = timeGetTime();			//���݂̎��Ԏ擾
			if(nowtime - FPS_oldtime >= 1000)	//�O�ɍX�V���Ă���A�P�b��������
			{
				FPS_oldtime = nowtime;
				FPS_Disp = FPS_Cnt;		//�P�b�ŃQ�[��������������s�ł�������ۑ�
				FPS_Cnt = 0;			//�J�E���^��0�ɂ��āA����1�b�̃J�E���g�̏���
			}
			if(nowtime - oldtime >= 1000/FPS_ChangeNum)	//�O��̎��s������A80���̂P�b�ȏソ���Ă�����A
			{
				oldtime = nowtime;	//oldtime���X�V
				Main();		//���C���������܂Ƃ߂��֐�Main�����s
				FPS_Cnt++;		//�Q�[���̃��C�����������s���邲�ƂɁA�{�P
			}
		}
	}
	/////  �Q�[���̉��   /////
	GameRelease();	//�Q�[���̉���������܂Ƃ߂��֐������s

	ReleaseDM();	//DirectMusic�I�u�W�F�N�g�̉��
	ReleaseDS();	//DirectSound�I�u�W�F�N�g�̉��
	ReleaseDD();	//DirectDraw�I�u�W�F�N�g�̉��
	return msg.wParam;
}



/*--------------------------------------------------------------------------
	DirectDraw�I�u�W�F�N�g�̐���
--------------------------------------------------------------------------*/
BOOL	CreateDD( HWND hWnd )
{
	HRESULT				ret;
	DDSURFACEDESC2		ddsd;
	DDSCAPS2			ddscaps;
	DDCOLORKEY ddck;					//�J���[�L�[�̏��������\����


	//	�����������@DirectDraw�I�u�W�F�N�g�̍쐬�@����������
	ret = DirectDrawCreateEx( NULL,(void **)&lpDD,IID_IDirectDraw7,NULL);
	if( ret != DD_OK )	ERR_MES_RETURN("DirectDrawCreateEx���s");	//�G���[�`�F�b�N

	//	�����������@�������x���̐ݒ�@����������
	ret = lpDD->SetCooperativeLevel( hWnd,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN
										| DDSCL_ALLOWREBOOT | DDSCL_ALLOWMODEX );	//DDSCL_ALLOWMODEX��640*480�ȊO�̉�ʃT�C�Y���������Ɏw��i��320*280�j
	if(ret != DD_OK )	ERR_MES_RETURN("SetCooperativeLevel���s");	//�G���[�`�F�b�N

	//	�����������@��ʃ��[�h�̐ݒ�@����������
	ret = lpDD->SetDisplayMode( SCREEN_WIDTH,SCREEN_HEIGHT,BPP,0,0 );
	if( ret != DD_OK )	ERR_MES_RETURN("SetDisplayMode���s");	//�G���[�`�F�b�N

	//	�����������@�v���C�}���T�[�t�F�X�̍쐬�@����������
	ZeroMemory( &ddsd,sizeof( DDSURFACEDESC2 ) );	//�S�Ẵ����o���O�ɏ�����
	ddsd.dwSize = sizeof( ddsd );					//���̍\���̂̃T�C�Y���i�[
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;//dwFlags�����o�ɁADDSURFACEDESC2�\���̂̂ǂ̃����o���g�p�i�L���j���邩��ݒ肷��

	ddsd.ddsCaps.dwCaps =	DDSCAPS_PRIMARYSURFACE |	//���̻�̪�����A��ײ�ػ�̪���ł��邱�Ƃ�\��
							DDSCAPS_FLIP |				//���̻�̪�����A�t���b�v�\�ł��邱�Ƃ�\��
							DDSCAPS_COMPLEX;			//������̪����\��

	ddsd.dwBackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�
	ret = lpDD->CreateSurface( &ddsd,&lpDDSPrimary,NULL );
	if(ret != DD_OK )	ERR_MES_RETURN("CreateSurface (�v���C�}��) ���s");	//�G���[�`�F�b�N

	//����������	�o�b�N�o�b�t�@�̍쐬	����������
	ZeroMemory( &ddscaps,sizeof( DDSCAPS2 ) );
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	ret = lpDDSPrimary->GetAttachedSurface( &ddscaps,&lpDDSBackBuffer );
	if( ret != DD_OK )	ERR_MES_RETURN("GetAttachedSurface (�o�b�N�o�b�t�@) ���s");	//�G���[�`�F�b�N

	//	�����������@�p���b�g�@����������
	if(!PaletteCreate(hWnd))	//�p���b�g�̏������ƃI�u�W�F�N�g�쐬�֘A�Â�������֐������s
		ERR_MES_RETURN("PaletteCreate(�p���b�g�ݒ�)���s");	//�G���[�`�F�b�N

	/*---------------------------------------------------------------------------------------------------------------
	|		�r�b�g�}�b�v���I�t�X�N���[���ɐݒ�
	*--------------------------------------------------------------------------------------------------------------*/
	//�I�t�X�N���[���T�[�t�F�[�X�ɁA�r�b�g�}�b�v��ݒ肷��

	//�Q�[�W�╶���Ȃ�
	lpDDSOff_Text = SetUp_OffScreen("BMP\\Text.bmp");		//�v���C���[�̃Q�[�W�Ȃ�
	if(!lpDDSOff_Text)		ERR_MES_RETURN("lpDDSOff_Text");	//lpDDSOff_Text���I�t�X�N���[���T�[�t�F�[�X�ɏ����ł��Ȃ�������G���[
	//�^�C�g��
	lpDDSOff_Title = SetUp_OffScreen("BMP\\Title.bmp");		//�^�C�g��
	if(!lpDDSOff_Title)		ERR_MES_RETURN("lpDDSOff_Title");
	//�X�e�[�W�Z���N�g
	lpDDSOff_StageSelect = SetUp_OffScreen("BMP\\StageSelect.bmp");		//�X�e�[�W�Z���N�g��ʂ̊G
	if(!lpDDSOff_StageSelect)		ERR_MES_RETURN("lpDDSOff_StageSelect");
	//�|�[�Y���
	lpDDSOff_Pouse = SetUp_OffScreen("BMP\\Pouse.bmp");			//�|�[�Y��ʂ̊G
	if(!lpDDSOff_Pouse)		ERR_MES_RETURN("lpDDSOff_Pouse");


	//�}�b�v�`�b�v
	lpDDSOff_MapTip = SetUp_OffScreen("BMP\\MapTip8.bmp");	//�}�b�v�`�b�v�̏������֐��Ŏ��s
	if(!lpDDSOff_MapTip)	ERR_MES_RETURN("lpDDSOff_MapTip");	//lpDDSOff_MapTip���I�t�X�N���[���ɏ����ł��Ȃ�������iNULL�Ȃ�j�G���[
	lpDDSOff_MapTip2 = SetUp_OffScreen("BMP\\MapTip7.bmp");	//�}�b�v�`�b�v�̏������֐��Ŏ��s
	if(!lpDDSOff_MapTip2)	ERR_MES_RETURN("lpDDSOff_MapTip2");	//lpDDSOff_MapTip2���I�t�X�N���[���ɏ����ł��Ȃ�������iNULL�Ȃ�j�G���[
	lpDDSOff_MapTip3 = SetUp_OffScreen("BMP\\MapTip9.bmp");	//�}�b�v�`�b�v�̏������֐��Ŏ��s
	if(!lpDDSOff_MapTip3)	ERR_MES_RETURN("lpDDSOff_MapTip3");	//lpDDSOff_MapTip3���I�t�X�N���[���ɏ����ł��Ȃ�������iNULL�Ȃ�j�G���[


	//�w�i
	lpDDSOff_Back0 = SetUp_OffScreen("BMP\\6BG.bmp");					//�w�i�O�i�X�X�e�[�W
	if(!lpDDSOff_Back0)		ERR_MES_RETURN("lpDDSOff_Back0");										//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_Back1 = SetUp_OffScreen("BMP\\BG12.bmp");					//�w�i�P�i�p�ЃX�e�[�W
	if(!lpDDSOff_Back1)		ERR_MES_RETURN("lpDDSOff_Back1");		
	lpDDSOff_Back1_OBJ = SetUp_OffScreen("BMP\\BG_OBJ.bmp");				//�w�i�P�I�u�W�F�i�p�ЃX�e�[�W�p
	if(!lpDDSOff_Back1_OBJ)		ERR_MES_RETURN("lpDDSOff_Back1_OBJ");
	lpDDSOff_Back2 = SetUp_OffScreen("BMP\\sabakuBG.bmp");					//�w�i�Q�i������n�X�e�[�W
	if(!lpDDSOff_Back2)		ERR_MES_RETURN("lpDDSOff_Back2");		
	lpDDSOff_Back3 = SetUp_OffScreen("BMP\\SibaBG.bmp");					//�w�i�R�i���X�e�[�W
	if(!lpDDSOff_Back3)		ERR_MES_RETURN("lpDDSOff_Back3");		


	//�v���C���[�̊G
	lpDDSOff_CharWAIT = SetUp_OffScreen("BMP\\PlrWAIT.bmp");						//�ҋ@
	if(!lpDDSOff_CharWAIT)	ERR_MES_RETURN("lpDDSOff_CharWAIT");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_Char = SetUp_OffScreen("BMP\\PlrMOVE.bmp");							//�ړ�
	if(!lpDDSOff_Char)	ERR_MES_RETURN("lpDDSOff_Char");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDash = SetUp_OffScreen("BMP\\PlrDASH.bmp");						//�_�b�V��
	if(!lpDDSOff_CharDash)	ERR_MES_RETURN("lpDDSOff_CharDash");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDown = SetUp_OffScreen("BMP\\PlrSITDOWN.bmp");					//���Ⴊ��
	if(!lpDDSOff_CharDown)	ERR_MES_RETURN("lpDDSOff_CharDown");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharAttackY = SetUp_OffScreen("BMP\\PlrATTACK-yoko.bmp");			//���a��
	if(!lpDDSOff_CharAttackY) ERR_MES_RETURN("lpDDSOff_CharAttackY");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharAttackT = SetUp_OffScreen("BMP\\PlrATTACK-tate.bmp");			//�c�a��
	if(!lpDDSOff_CharAttackT)	ERR_MES_RETURN("lpDDSOff_CharAttackT");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharJump = SetUp_OffScreen("BMP\\PlrJUMP.bmp");						//�W�����v
	if(!lpDDSOff_CharJump)	ERR_MES_RETURN("lpDDSOff_CharJump");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDead = SetUp_OffScreen("BMP\\PlrDEAD.bmp");						//����
	if(!lpDDSOff_CharDead)	ERR_MES_RETURN("lpDDSOff_CharDead");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDamage = SetUp_OffScreen("BMP\\PlrDAMAGE.bmp");					//�_���[�W
	if(!lpDDSOff_CharDamage)	ERR_MES_RETURN("lpDDSOff_CharDamage");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDownAttackY = SetUp_OffScreen("BMP\\PlrDOWNATTACK-yoko.bmp");	//���Ⴊ�݉��a��
	if(!lpDDSOff_CharDownAttackY)	ERR_MES_RETURN("lpDDSOff_CharDownAttackY");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDownAttackT = SetUp_OffScreen("BMP\\PlrDOWNATTACK-tate.bmp");	//���Ⴊ�ݏc�a��
	if(!lpDDSOff_CharDownAttackT)	ERR_MES_RETURN("lpDDSOff_CharDownAttackT");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharJumpAttackY = SetUp_OffScreen("BMP\\PlrJUMPAT-yoko.bmp");		//���Ⴊ�݉��a��
	if(!lpDDSOff_CharJumpAttackY)	ERR_MES_RETURN("lpDDSOff_CharJumpAttackY");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharJumpAttackT = SetUp_OffScreen("BMP\\PlrJUMPAT-tate.bmp");		//���Ⴊ�ݏc�a��
	if(!lpDDSOff_CharJumpAttackT)	ERR_MES_RETURN("lpDDSOff_CharJumpAttackT");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharUpSwd = SetUp_OffScreen("BMP\\PlrUp_Swd.bmp");					//���㓊��
	if(!lpDDSOff_CharUpSwd)	ERR_MES_RETURN("lpDDSOff_CharUpSwd");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharLRSwd = SetUp_OffScreen("BMP\\PlrLR_Swd.bmp");					//�����E����
	if(!lpDDSOff_CharLRSwd)	ERR_MES_RETURN("lpDDSOff_CharLRSwd");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharJumpDownSwd = SetUp_OffScreen("BMP\\PlrJumpDown_Swd.bmp");		//���W�����v������
	if(!lpDDSOff_CharJumpDownSwd)	ERR_MES_RETURN("lpDDSOff_CharJumpDownSwd");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharDownSwd = SetUp_OffScreen("BMP\\PlrDown_Swd.bmp");				//�����Ⴊ�ݓ���
	if(!lpDDSOff_CharDownSwd)	ERR_MES_RETURN("lpDDSOff_CharDownSwd");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_CharBall = SetUp_OffScreen("BMP\\PlrBall.bmp");					//�o���A
	if(!lpDDSOff_CharBall)	ERR_MES_RETURN("lpDDSOff_CharBall");	
	lpDDSOff_CharReturnSwd = SetUp_OffScreen("BMP\\PlrReturn_Swd.bmp");		//���z��
	if(!lpDDSOff_CharReturnSwd)	ERR_MES_RETURN("lpDDSOff_CharReturnSwd");	
	lpDDSOff_CharSwdHPUP = SetUp_OffScreen("BMP\\PlrSwd_HPUP.bmp");		//�v���C���[��HP����ւ�
	if(!lpDDSOff_CharSwdHPUP)	ERR_MES_RETURN("lpDDSOff_CharSwdHPUP");	


	//���̊G
	lpDDSOff_Swd = SetUp_OffScreen("BMP\\Swd.bmp");		//��
	if(!lpDDSOff_Swd)	ERR_MES_RETURN("lpDDSOff_Swd.bmp");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	

	//�G�l�~�[�̊G
	lpDDSOff_En1 = SetUp_OffScreen("BMP\\Ene1.bmp");		//�G�l�~�[�P
	if(!lpDDSOff_En1)	ERR_MES_RETURN("lpDDSOff_En1");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_En2 = SetUp_OffScreen("BMP\\Ene2.bmp");		//�G�l�~�[�Q
	if(!lpDDSOff_En2)	ERR_MES_RETURN("lpDDSOff_En2");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_En3 = SetUp_OffScreen("BMP\\Ene3.bmp");		//�G�l�~�[�R
	if(!lpDDSOff_En3)	ERR_MES_RETURN("lpDDSOff_En3");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	
	lpDDSOff_En4 = SetUp_OffScreen("BMP\\Ene4.bmp");		//�G�l�~�[�S
	if(!lpDDSOff_En4)	ERR_MES_RETURN("lpDDSOff_En4");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En5 = SetUp_OffScreen("BMP\\Ene5.bmp");		//�G�l�~�[�T
	if(!lpDDSOff_En5)	ERR_MES_RETURN("lpDDSOff_En5");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En6 = SetUp_OffScreen("BMP\\Ene6.bmp");		//�G�l�~�[�U
	if(!lpDDSOff_En6)	ERR_MES_RETURN("lpDDSOff_En6");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En7 = SetUp_OffScreen("BMP\\Ene7.bmp");		//�G�l�~�[�V
	if(!lpDDSOff_En7)	ERR_MES_RETURN("lpDDSOff_En7");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En8 = SetUp_OffScreen("BMP\\Ene8.bmp");		//�G�l�~�[�W
	if(!lpDDSOff_En8)	ERR_MES_RETURN("lpDDSOff_En8");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En9 = SetUp_OffScreen("BMP\\Ene9.bmp");		//�G�l�~�[�X
	if(!lpDDSOff_En9)	ERR_MES_RETURN("lpDDSOff_En9");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_EnTubo = SetUp_OffScreen("BMP\\EneTubo.bmp");		//�G�l�~�[�c�{
	if(!lpDDSOff_EnTubo)	ERR_MES_RETURN("lpDDSOff_EnTubo");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE
	lpDDSOff_En10 = SetUp_OffScreen("BMP\\Ene10.bmp");		//�G�l�~�[10
	if(!lpDDSOff_En10)	ERR_MES_RETURN("lpDDSOff_En10");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE


	lpDDSOff_Boss1 = SetUp_OffScreen("BMP\\Boss1.bmp");	//�{�X�P
	if(!lpDDSOff_Boss1)	ERR_MES_RETURN("lpDDSOff_Boss1");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	

	//�e�̊G
	lpDDSOff_Shot = SetUp_OffScreen("BMP\\Shot.bmp");	//�e
	if(!lpDDSOff_Shot)	ERR_MES_RETURN("lpDDSOff_Shot");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	

	//�G�t�F�N�g�̊G
	lpDDSOff_EF = SetUp_OffScreen("BMP\\EF.bmp");		//�G�t�F�N�g
	if(!lpDDSOff_EF)	ERR_MES_RETURN("lpDDSOff_EF");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	

	//�I�u�W�F�N�g�̊G
	lpDDSOff_OBJ = SetUp_OffScreen("BMP\\OBJ.bmp");		//�I�u�W�F
	if(!lpDDSOff_OBJ)	ERR_MES_RETURN("lpDDSOff_OBJ");	//�摜��̽�ذݻ�̪���ɏ����ł��Ȃ�������@�G���[��return FALSE	


	//�J���[�L�[�̐ݒ�i�����Ӂ@WindowsXP�̏ꍇ�^�����̓��ߐF��I�ԂƓ��߂���Ȃ��j
	ddck.dwColorSpaceLowValue  = 255;
	ddck.dwColorSpaceHighValue = 255;

	lpDDSOff_Text->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�v���C���[�̃Q�[�W�Ȃ�
	lpDDSOff_Title->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�^�C�g���摜
	lpDDSOff_StageSelect->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�X�e�[�W�Z���N�g�摜
	lpDDSOff_Pouse->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�|�[�Y���

	lpDDSOff_MapTip->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�}�b�v�`�b�v�̃I�t�X�N���[���T�[�t�F�[�X�̓��ߐF��ݒ�
	lpDDSOff_MapTip2->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�}�b�v�`�b�v�̃I�t�X�N���[���T�[�t�F�[�X�̓��ߐF��ݒ�
	lpDDSOff_MapTip3->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�}�b�v�`�b�v�̃I�t�X�N���[���T�[�t�F�[�X�̓��ߐF��ݒ�

	lpDDSOff_Back0->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�w�i�O(�X�X�e�[�W
	lpDDSOff_Back1->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�w�i�P�i�p�ЃX�e�[�W
	lpDDSOff_Back1_OBJ->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�w�i�P�I�u�W�F�i�p�ЃX�e�[�W�p
	lpDDSOff_Back2->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�w�i�Q�i������n�X�e�[�W
	lpDDSOff_Back3->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�w�i�R�i���X�e�[�W

	lpDDSOff_CharWAIT->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�v���C���[�ҋ@
	lpDDSOff_Char->SetColorKey(DDCKEY_SRCBLT,&ddck);					//�v���C���[�ړ���
	lpDDSOff_CharDash->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�v���C���[�_�b�V����
	lpDDSOff_CharDown->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�v���C���[���Ⴊ�݂�
	lpDDSOff_CharAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[���a��
	lpDDSOff_CharAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[�c�a��
	lpDDSOff_CharJump->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�v���C���[�W�����v
	lpDDSOff_CharDead->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�v���C���[�����
	lpDDSOff_CharDamage->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[�_���[�W��������G
	lpDDSOff_CharDownAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[���Ⴊ�݉��a��
	lpDDSOff_CharDownAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[���Ⴊ�ݏc�a��
	lpDDSOff_CharJumpAttackY->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[�W�����v���a��
	lpDDSOff_CharJumpAttackT->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[�W�����v�c�a��
	lpDDSOff_CharUpSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[�㌕����
	lpDDSOff_CharLRSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[���E������
	lpDDSOff_CharJumpDownSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[�W�����v��������
	lpDDSOff_CharDownSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[���Ⴊ�݌�����
	lpDDSOff_CharBall->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[�{�[��
	lpDDSOff_CharReturnSwd->SetColorKey(DDCKEY_SRCBLT,&ddck);		//�v���C���[���z��
	lpDDSOff_CharSwdHPUP->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�v���C���[��HP����ւ�

	lpDDSOff_Swd->SetColorKey(DDCKEY_SRCBLT,&ddck);				//��

	lpDDSOff_En1->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�P
	lpDDSOff_En2->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�Q
	lpDDSOff_En3->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�R
	lpDDSOff_En4->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�S
	lpDDSOff_En5->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�T
	lpDDSOff_En6->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�U
	lpDDSOff_En7->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�V
	lpDDSOff_En8->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�W
	lpDDSOff_En9->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�l�~�[�X
	lpDDSOff_EnTubo->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�c�{
	lpDDSOff_En10->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�G�l�~�[�P�O

	lpDDSOff_Boss1->SetColorKey(DDCKEY_SRCBLT,&ddck);			//�{�X�P

	lpDDSOff_Shot->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�e
	lpDDSOff_EF->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�G�t�F�N�g
	lpDDSOff_OBJ->SetColorKey(DDCKEY_SRCBLT,&ddck);				//�I�u�W�F�N�g

	//////  �Q�[���̏���  //////
	GameCreate(hWnd);	//�Q�[���̏���������֐������s

	return TRUE;	//����������TRUE��Ԃ�
}

/*----------------------------------------------------------------------------
	DirectDraw�I�u�W�F�N�g�̍폜	(���v���Ӂ��@�I�u�W�F�N�g���쐬�������Ƌt���ɉ��������@�������j
----------------------------------------------------------------------------*/
void	ReleaseDD( void )
{	//�I�u�W�F�N�g���쐬�������Ƌt���ɉ��������
	
	RELEASE(lpDDSOff_OBJ);				//�I�u�W�F�N�g
	RELEASE(lpDDSOff_EF);				//�G�t�F�N�g
	RELEASE(lpDDSOff_Shot);				//�e
	
	RELEASE(lpDDSOff_Boss1);			//�{�X�P

	RELEASE(lpDDSOff_En10);				//�G�l�~�[�P�O
	RELEASE(lpDDSOff_EnTubo);				//�c�{
	RELEASE(lpDDSOff_En9);				//�G�l�~�[�X
	RELEASE(lpDDSOff_En8);				//�G�l�~�[�W
	RELEASE(lpDDSOff_En7);				//�G�l�~�[�V
	RELEASE(lpDDSOff_En6);				//�G�l�~�[�U
	RELEASE(lpDDSOff_En5);				//�G�l�~�[�T
	RELEASE(lpDDSOff_En4);				//�G�l�~�[�S
	RELEASE(lpDDSOff_En3);				//�G�l�~�[�R
	RELEASE(lpDDSOff_En2);				//�G�l�~�[�Q
	RELEASE(lpDDSOff_En1);				//�G�l�~�[�P

	RELEASE(lpDDSOff_CharSwdHPUP);			//�v���C���[��HP����ւ�
	RELEASE(lpDDSOff_CharReturnSwd);		//�v���C���[���z��
	RELEASE(lpDDSOff_CharBall);				//�v���C���[�{�[��
	RELEASE(lpDDSOff_CharDownSwd);			//�v���C���[���Ⴊ�݌�����
	RELEASE(lpDDSOff_CharJumpDownSwd);		//�v���C���[�W�����v��������
	RELEASE(lpDDSOff_CharLRSwd);			//�v���C���[���E������
	RELEASE(lpDDSOff_CharUpSwd);			//�v���C���[�㌕����
	RELEASE(lpDDSOff_CharJumpAttackT);		//�v���C���[�W�����v�c�a��
	RELEASE(lpDDSOff_CharJumpAttackY);		//�v���C���[�W�����v���a��
	RELEASE(lpDDSOff_CharDownAttackT);		//�v���C���[���Ⴊ�ݏc�a��
	RELEASE(lpDDSOff_CharDownAttackY);		//�v���C���[���Ⴊ�݉��a��
	RELEASE(lpDDSOff_CharDamage);			//�v���C���[�_���[�W��������G
	RELEASE(lpDDSOff_CharDead);				//�v���C���[�����
	RELEASE(lpDDSOff_CharJump);				//�v���C���[�W�����v
	RELEASE(lpDDSOff_CharAttackT);			//�v���C���[�c�a��
	RELEASE(lpDDSOff_CharAttackY);			//�v���C���[���a��
	RELEASE(lpDDSOff_CharDown);				//�v���C���[���Ⴊ�݂�
	RELEASE(lpDDSOff_CharDash);				//�v���C���[�_�b�V����
	RELEASE(lpDDSOff_Char);					//�v���C���[�ړ�
	RELEASE(lpDDSOff_CharWAIT);				//�v���C���[�ҋ@

	RELEASE(lpDDSOff_Back3);				//�w�i�R
	RELEASE(lpDDSOff_Back2);				//�w�i�Q
	RELEASE(lpDDSOff_Back1_OBJ);				//�w�i�P�I�u�W�F
	RELEASE(lpDDSOff_Back1);				//�w�i�P
	RELEASE(lpDDSOff_Back0);				//�w�i�O

	RELEASE(lpDDSOff_MapTip3);				//�}�b�v�`�b�v�R
	RELEASE(lpDDSOff_MapTip2);				//�}�b�v�`�b�v�Q
	RELEASE(lpDDSOff_MapTip);				//�}�b�v�`�b�v�̃I�t�X�N���[���T�[�t�F�[�X������
	
	RELEASE(lpDDSOff_Pouse);				//�|�[�Y���
	RELEASE(lpDDSOff_StageSelect);			//�X�e�[�W�Z���N�g���
	RELEASE(lpDDSOff_Title);				//�^�C�g���p�摜
	RELEASE(lpDDSOff_Text);					//�v���C���[�̃Q�[�W�Ȃ�

	RELEASE(lpDDPal);
	RELEASE(lpDDSBackBuffer);
	RELEASE(lpDDSPrimary);
	RELEASE(lpDD);

}

/*-----------------------------------------------------------------------------------
	�p���b�g
-----------------------------------------------------------------------------------*/
BOOL PaletteCreate(HWND hWnd)	//�@�\�F�p���b�g�̏������ƃI�u�W�F�N�g�̍쐬����p���b�g�̊֘A�Â����s���֐�
{	
	HRESULT				ret;	//���ʂ��󂯎��ϐ�

	//Pal_Data(�p���b�g�f�[�^)�����ɁA�p���b�g�I�u�W�F�N�g���쐬
	ret = lpDD->CreatePalette(
		DDPCAPS_8BIT | DDPCAPS_ALLOW256,	//�p���b�g�̎�ނ�\���t���O
		MainPal,							//�ݒ肵���p���b�g�f�[�^�̃A�h���X
		&lpDDPal,							//�p���b�g�I�u�W�F�N�g�ւ̃|�C���^
		NULL);
	//�G���[�`�F�b�N
	if(ret != DD_OK)	ERR_MES_RETURN("CreatePalette(�p���b�g�I�u�W�F�N�g�j�쐬���s");

	//�쐬�����p���b�g�I�u�W�F�N�g���A�v���C�}���T�[�t�F�[�X�Ɋ֘A�Â���
	ret = lpDDSPrimary->SetPalette(lpDDPal);
	//�G���[�`�F�b�N
	if(ret != DD_OK)
	{
		ReleaseDD();	//DirectDraw�I�u�W�F�N�g��������ăG���[�̃��b�Z�[�W�{�b�N�X�̐F�΂���h��
		ERR_MES_RETURN("SetPalette(�p���b�g�I�u�W�F�N�g�̊֘A�Â��j�Ɏ��s");
	}

	return TRUE;	//�����Ȃ�TRUE��Ԃ�
}

/*------------------------------------------------------------------------------------
		SetUp_OffScreen�֐�
------------------------------------------------------------------------------------*/
LPDIRECTDRAWSURFACE7 SetUp_OffScreen(char *pFileName)
{
	HBITMAP hBitmap,hOldBitmap;			//�r�b�g�}�b�v�n���h��
	HDC hdc,bmhdc;						//�f�o�C�X�R���e�L�X�g
	BITMAP bm;							//�r�b�g�}�b�v�\����
	DDSURFACEDESC2 ddsd;
	RGBQUAD rgb[256];					//RGBQUAD�\���̔z��i256�F���j
	LPDIRECTDRAWSURFACE7 lpDDSurface;
	HRESULT res;						//�ߒl�i�G���[�`�F�b�N�j
	int i,Color;						//�F���p

	//�����Ŏw�肵���r�b�g�}�b�v�̃r�b�g�}�b�v�n���h�����擾����
	hBitmap = (HBITMAP)LoadImage(
		NULL,
		pFileName,				//�t�@�C����
		IMAGE_BITMAP,			//�r�b�g�}�b�v�w��
		0,0,
		LR_LOADFROMFILE |		//�t�@�C������ǂݍ���
		LR_CREATEDIBSECTION	);	//DIB�`��
	if(!hBitmap)	return NULL;	//�G���[�`�F�b�N

	//�r�b�g�}�b�v�n���h������A�r�b�g�}�b�v�̏����擾����
	GetObject(	hBitmap,	//�I�u�W�F�N�g�̃n���h��
				sizeof(bm),	//�擾����T�C�Y
				&bm	);		//�擾���������i�[���Ă������߂̍\���̂ւ̃|�C���^
	//�f�o�C�X�R���e�L�X�g�ƃr�b�g�}�b�v�n���h�����Z�b�g�ɂ���
	bmhdc = CreateCompatibleDC(NULL);
	hOldBitmap = (HBITMAP)SelectObject(bmhdc,hBitmap);

	//�I�t�X�N���[���T�[�t�F�[�X�ɐݒ�
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	//�擾�����r�b�g�}�b�v�̏�񂩂�A���̃r�b�g�}�b�v�̕��ƍ������w��
	ddsd.dwWidth = bm.bmWidth;						//��
	ddsd.dwHeight = bm.bmHeight;					//����
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	//�I�t�X�N���[���T�[�t�F�[�X�̍쐬
	res  = lpDD->CreateSurface(&ddsd,&lpDDSurface,NULL);
	if(res != DD_OK)	return NULL;	//�G���[�`�F�b�N

	//�p���b�g�f�[�^�i�F�f�[�^�j�̎擾
	//�r�b�g�}�b�v�I�u�W�F�N�g�̃f�o�C�X�R���e�L�X�g����A���̃I�u�W�F�N�g�̐F�f�[�^���擾����
	Color = GetDIBColorTable(
				bmhdc,	//�r�b�g�}�b�v�I�u�W�F�N�g�̃f�o�C�X�R���e�L�X�g
				0,		//�J�n�ԍ�
				256,	//�J�n�ԍ����炢���擾���邩�̒l
				rgb	);	//�擾�����f�[�^���i�[���Ă������߂�RGBQUAD�\���̂ւ̃|�C���^

	//�p���b�g�f�[�^�̐ݒ�
	for(i = 0;i < Color;i++)
	{
		MainPal[i].peRed = rgb[i].rgbRed;
		MainPal[i].peGreen = rgb[i].rgbGreen;
		MainPal[i].peBlue = rgb[i].rgbBlue;
		MainPal[i].peFlags = PC_RESERVED;
	}
	lpDDPal->SetEntries(0,0,256,MainPal);	//MainPal���Z�b�g
	//�T�u�p���b�g�i���ɕK�v�Ȃ�
	for(i = 0;i < 255;i++)
	{
		SubPal[i].peRed = i;
		SubPal[i].peGreen = i;
		SubPal[i].peBlue = i;
		SubPal[i].peFlags = PC_RESERVED;
	}


	//�����@256�Ԗڂ̃p���b�g�����ύX���Ȃ��i�����F��L���ɂ��邽��
	//lpDDPal->SetEntries(0,0,255,SubPal);	//MainPal���Z�b�g

	//�r�b�g�}�b�v���A�I�t�X�N���[���ɓ]��
	lpDDSurface->GetDC(&hdc);
	BitBlt(hdc,0,0,bm.bmWidth,bm.bmHeight,bmhdc,0,0,SRCCOPY);
	lpDDSurface->ReleaseDC(hdc);

	//�f�o�C�X�R���e�L�X�g��߂�
	SelectObject(bmhdc,hOldBitmap);

	//�r�b�g�}�b�v�n���h���ƃf�o�C�X�R���e�L�X�g�̍폜
	DeleteObject(hBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(bmhdc);


	//�쐬�����I�t�X�N���[���ւ̃|�C���^���A�ߒl�Ƃ��Ė߂�
	return lpDDSurface;
}

