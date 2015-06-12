#include "Extern.h"
#include "DirectSound.h"
#include "DirectMusic.h"
#include "Define.h"
#include < dmusicc.h >		// �R�A�E���C���C���^�[�t�F�[�X
#include < dmusici.h >		// �p�t�H�[�}���X�E���C���C���^�[�t�F�[�X


///// �ϐ��錾 ///////

IDirectMusicPerformance*	lpDMPerformance;	// DirectMusicPerformance �I�u�W�F�N�g

IDirectMusic*			lpDMusic = NULL;						// DirectMusic �I�u�W�F�N�g
IDirectMusicLoader*		lpDMLoader;								// ���[�_�[�I�u�W�F�N�g
IDirectMusicSegment*	lpDMSegment[ MUSIC_MAX ] = { NULL };	// �Z�O�����g�I�u�W�F�N�g

extern LPDIRECTSOUND	lpDS;	//DirectMusic�I�u�W�F�N�g�쐬�ň����Ɏg�p����@DirectSound�I�u�W�F�N�g��

int	MusicNumber = 0;	// ���݂̃~���[�W�b�N�ԍ��Ǘ��p

//�\�\�\�\�\�\ �_�C���N�g�~���[�W�b�N�֌W�̏��������s���֐� �\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL DM_Init()
{
	HRESULT				res;			// �ߒl�p
	DMUS_OBJECTDESC		dmod;			// �I�u�W�F�N�g ( MIDI ) �̏����Ǘ����邽�߂̍\����
	MUSIC_TIME			start_time = 0;	// �Z�O�����g�̊J�n���� ( �Ȃ̂ǂ�����Đ����邩 ) ���i�[���邽�߂̕ϐ�
										// �O�̏ꍇ�A�Ȃ̍ŏ�����
	MUSIC_TIME			end_time;		// ���[�v�Đ����̏I���������i�[���邽�߂̕ϐ�
	MUSIC_TIME			seg_length;		// �Z�O�����g�̒������i�[���邽�߂̕ϐ�

	//MIDI�t�@�C���l�[��
	WCHAR *				Midi_FileNeme[ MUSIC_MAX ] =
						{
							{ L"MIDI\\BGM1.mid" },
							{ L"MIDI\\���܂��̋�.mid" }
							//{ L"MIDI\\DQ3.mid" },
							//{ L"MIDI\\Z.mid" },
							//{ L"MIDI\\FF4.mid" },
							//{ L"MIDI\\( ^-^ ).mid" }
						};


	///// COM �̏����� /////
	res = CoInitialize( NULL );
	if(FAILED(res))	//�G���[�`�F�b�N
		ERR_MES_RETURN("COM�̏������Ɏ��s");


	///// DirectMusicPerformance �I�u�W�F�N�g�̍쐬 //////
	res = CoCreateInstance(
						CLSID_DirectMusicPerformance,
						NULL,
						CLSCTX_INPROC,
						IID_IDirectMusicPerformance2,
						( void ** )&lpDMPerformance );
	if(FAILED(res))	//�G���[�`�F�b�N
		ERR_MES_RETURN("DirectMusicPerformance �I�u�W�F�N�g�̍쐬�Ɏ��s")


	///// DirectMusic �I�u�W�F�N�g�̍쐬 //////
	res = lpDMPerformance -> Init( &lpDMusic, lpDS, NULL );
	if( FAILED( res ) )	//�G���[�`�F�b�N
		ERR_MES_RETURN("DirectMusic �I�u�W�F�N�g �̍쐬�Ɏ��s");


	////// DirectMusicLoader �I�u�W�F�N�g�̍쐬 //////
	res = CoCreateInstance(
						CLSID_DirectMusicLoader,
						NULL,
						CLSCTX_INPROC,
						IID_IDirectMusicLoader,
						( void ** )&lpDMLoader );
	if(FAILED(res))	//�G���[�`�F�b�N
		ERR_MES_RETURN("DirectMusicLoader �I�u�W�F�N�g �̍쐬�Ɏ��s");

	///// �|�[�g ( �V���Z�T�C�U ) �̑I�� ///////
	res = lpDMPerformance -> AddPort( NULL );		// �f�t�H���g�̃|�[�g��I��
	if(FAILED(res))	//�G���[�`�F�b�N
		ERR_MES_RETURN("�f�t�H���g�E�|�[�g�̑I���Ɏ��s");

	// ------------------ �Z�O�����g�̍쐬 ----------------- //

	// �~���[�W�b�N�̐����A�Z�O�����g���쐬����
	for( int i = 0; i < MUSIC_MAX; i ++ )
	{
		dmod.dwSize = sizeof( dmod );								// �\���̂̃T�C�Y�w��
		dmod.guidClass = CLSID_DirectMusicSegment;					// DirectMusicSegment ���w��
		wcscpy( dmod.wszFileName, Midi_FileNeme[ i ] );				// mid �t�@�C�����w��
		dmod.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;		// �L�������o���w��

		// �Z�O�����g�̍쐬 ( �\���̂���f�[�^�����o�� )
		res = lpDMLoader -> GetObject( &dmod, IID_IDirectMusicSegment2, ( void ** )&lpDMSegment[ i ] );
		if(FAILED(res))	//�G���[�`�F�b�N
			ERR_MES_RETURN("�Z�O�����g�̃��[�h�Ɏ��s");

		// �Z�O�����g�̃p�����[�^�̐ݒ�
		lpDMSegment[ i ] -> SetParam( GUID_StandardMIDIFile, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );

		// DLS �R���N�V�����̃_�E�����[�h
		lpDMSegment[ i ] -> SetParam( GUID_Download, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );

		// �Z�O�����g�̒������擾����
		lpDMSegment[ i ]-> GetLength( &seg_length );

		// �Z�O�����g�̊J�n������ݒ肷��
		lpDMSegment[ i ] -> SetStartPoint( start_time );

		// �Đ������钷����ݒ肷��
		end_time = seg_length;
		lpDMSegment[ i ] -> SetLoopPoints( start_time, end_time );

		// ���[�v�Đ�������񐔂�ݒ肷��
		lpDMSegment[ i ] -> SetRepeats( 0xFFFF );

	}

	return TRUE;

}
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�\�\�\�\�\�\�\�\�\ �_�C���N�g�~���[�W�b�N�֌W�̃I�u�W�F�N�g�̉���@�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ReleaseDM( )
{
	int		i;

	// DLS �̃A�����[�h ( ��� )
	for( i = 0; i < MUSIC_MAX; i ++ )
	{
		lpDMSegment[ i ] -> SetParam( GUID_Unload, 0xFFFFFFFF, 0, 0, ( void * )lpDMPerformance );
	}

	// �Z�O�����g�I�u�W�F�N�g�̉��
	for( i = 0; i < MUSIC_MAX; i ++ )
	{		
		RELEASEDM( lpDMSegment[ i ] );
	}

	if( lpDMPerformance != NULL )
	{
		lpDMPerformance -> CloseDown( );	// Performance �I�u�W�F�N�g�����
	}

	RELEASEDM( lpDMPerformance );			// lpDMPerformance �I�u�W�F�N�g�̉��
	RELEASEDM( lpDMusic );					// lpDirectMusic �I�u�W�F�N�g�̉��
	RELEASEDM( lpDMLoader );				// ���[�_�[�I�u�W�F�N�g�̉��
	CoUninitialize( );						// COM �̉��

}
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DM_Play(int MusicNum)	//�@�\�F�Z�O�����g���Đ�����
//�������P�F�Đ�������Z�O�����g�̔ԍ�
{
	// �Z�O�����g�̉��t
	lpDMPerformance -> PlaySegment( lpDMSegment[ MusicNum ], DMUS_SEGF_DEFAULT, 0, NULL );

}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DM_Stop(int MusicNum)	//�@�\�F�Z�O�����g���~����
//�������P�F��~������Z�O�����g�̔ԍ�(-1�őS�Ē�~
{	
	if(MusicNum == -1)	//�������[�P�Ȃ�S�Ă̋Ȃ��~
		lpDMPerformance -> Stop(NULL, NULL, 0, 0 );
	else
		lpDMPerformance -> Stop( lpDMSegment[ MusicNum ], NULL, 0, 0 );
}