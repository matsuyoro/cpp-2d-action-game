#if !defined __DEFINEMACRO	//�����A�}�N�����܂���`����ĂȂ����
#define __DEFINEMACRO		//�}�N�����`
//��������������������������������������������������������������������������������������������������������������
//#include <ddraw.h>
/*-----------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------*/
#define	SCREEN_WIDTH	640										//�X�N���[����
#define SCREEN_HEIGHT	480										//�X�N���[������
#define	BPP				8										//�J���[���[�h

//DirectDraw�I�u�W�F�N�g����}�N��
#define	RELEASE(dds)		{if( dds != NULL )	{ dds->Release(); dds = NULL;	}}
//DirectSound�I�u�W�F�N�g����}�N��
#define RELEASEDS( ds )		{if( ( ds ) )	{ ( ds )->Release( ); ds = NULL; }}
// DirectMusic �I�u�W�F�N�g�̉���}�N��
#define		RELEASEDM( dm )		if( ( dm ) ){ ( dm ) -> Release( ); dm = NULL; }

//�G���[��m�点�邽�߂̃}�N��
#define ERROR_MESSAGE(mes)	{MessageBox( hWnd,mes,mes,MB_OK ); }
//�G���[��m�点�AFALSE��Ԃ��}�N��
#define ERR_MES_RETURN(mes) {MessageBox(hWnd,mes,mes,MB_OK); return FALSE;}


// �~���[�W�b�N�̍ő吔
#define	MUSIC_MAX 2		//�Ȃ̍ő吔

//�T�E���h�̍ő吔
#define SOUND_MAX 10		//���̍ő吔

//�G�l�~�[
#define ENE_MAX 500		//�G�L�����ő�\����

//�R�}���h
#define CMD_MAX 9		//�R�}���h�̎�ނ̐�

//�G�l�~�[�o���|�C���g
#define ENEONPOS_MAX 30	//�G�l�~�[���o��������|�C���g�̍ő吔(�t�@�C�����[�h�Ńf�[�^���󂯎��̂œ��Ɏw�肵�Ȃ��Ă悢

//�G�l�~�[
#define ENEACT_MAX 5	//�G�l�~�[�̃A�N�V�����̎�ނ̐�
//�V���b�g
#define SHOT_MAX 2000		//�e�̍ő�\������������
//�G�t�F�N�g
#define EF_MAX 50		//�G�t�F�N�g�ő�\�����������}�N��
//�I�u�W�F�N�g
#define OBJ_MAX 12		//�I�u�W�F�N�g�ő�\�����������}�N��
//�o�b�N�O���E���h�i�w�i�j�I�u�W�F�N�g
#define BGOBJ_MAX 30	//BG�I�u�W�F�̍ő�\�����������}�N��
//�}�b�v
#define BMPTIP_W 20		//ϯ�����߂̉摜���̉��ɕ��񂾃`�b�v�̐�
#define BMPTIP_H 15		//ϯ�����߂̉摜���̏c�ɕ��񂾃`�b�v�̐�
#define TIP_MAX (20*15)		//�`�b�v�̎�ނ̐�

#define TIP_W 32		//�`�b�v�̕�
#define TIP_H 32		//�`�b�v�̍���
#define WINMAP_W 20		//�E�B���h�E���ɕ\������`�b�v�̃��R�̐�
#define WINMAP_H 15		//�E�B���h�E���ɕ\������`�b�v�̃^�e�̐�


// #define MY_DELETEDC(x) if(x != NULL) {DeleteDC(x); x = NULL;}	//HDC�̉����NULL��������}�N��
//����������������������������������������������������������������������������������������������������������������
#endif
