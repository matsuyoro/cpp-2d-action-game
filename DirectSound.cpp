#include <dsound.h>			//DirectSound�̋@�\�g���̂ɕK�v�ȃw�b�_
#include "Define.h"			//�}�N���w�b�_
#include "Extern.h"			//�O���ϐ��w�b�_
#include "GameStruct.h"		//�\���̂̌^�̐錾�̃w�b�_

#include "DirectSound.h"

//DirectSound �֌W�̍\����

WAVEFORMATEX	wfex;			//���f�[�^�̃t�H�[�}�b�g���i�[�p
DSBUFFERDESC	dsbd;			//�T�E���h�o�b�t�@�̔\�͐ݒ�p
MMCKINFO	parent, child;		// RIFF�t�@�C�����̃`�����N�Ɋւ�������i�[����\���́i�e�`�����N �� �T�u( �q )�`�����N�p�j 

//DirectSound �֌W�̕ϐ�
LPDIRECTSOUND			lpDS;							//DirectSound �I�u�W�F�N�g
LPDIRECTSOUNDBUFFER		lpDSPrimary;					//�v���C�}���o�b�t�@
LPDIRECTSOUNDBUFFER		lpDSSoundBuffer[ SOUND_MAX ];	//�Z�J���_���o�b�t�@


// �t�@�C���ǂ݂��݁E���ʂ̏������p�\����
WAVE_DATA	Wave_Data[ SOUND_MAX ] =
{
//	 �t�@�C����					�{�����[��	�p��		���g��
	{ "WAVE\\���a��2.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\���a��.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\���a��_���[�W.wav",	-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\�e.wav",				-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\���[�U�[.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\Plr�_���[�W.wav",		-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\�Ή�����.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\�o���A���˕Ԃ艹.wav",	-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\�a���.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL },
	{ "WAVE\\�W�����v.wav",			-2000,			0,		DSBFREQUENCY_ORIGINAL }
};


//��������������������������������������������������������������������������������������������������������������������
BOOL DS_Init()	//�@�\�F�_�C���N�g�T�E���h�̏�����
{
	HRESULT	res;			//�ߒl�p

	//��DirectSound�I�u�W�F�N�g�쐬�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	res = DirectSoundCreate(NULL,&lpDS,NULL);
	if(res != DS_OK)								//�G���[�`�F�b�N	
		ERR_MES_RETURN("DirectSoundCreate")			//DS_OK�ȊO�Ȃ玸�s

	//���������x���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	res = lpDS->SetCooperativeLevel(hWnd,			//�E�B���h�E�n���h��
									DSSCL_NORMAL);	//�����t���O
	if(res != DS_OK)								//�G���[�`�F�b�N
		ERR_MES_RETURN("SetCooperativeLevel(�������x��)");

	//���X�s�[�J�[�̐ݒ�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	res = lpDS->SetSpeakerConfig(DSSPEAKER_COMBINED(DSSPEAKER_STEREO,DSSPEAKER_GEOMETRY_WIDE));
	//�X�e���I�p�ōœK���B�X�s�[�J�[�́A���𕷂��l����Q�O���̉~�ʏ�ōœK��
	if(res != DS_OK)	//�G���[�`�F�b�N�i���X�e���I�ȊO�̎��́A���̂܂܃t���O���w�肷�邾����OK
		ERR_MES_RETURN("SetSpeakerConfig(STEREO��GEOMETRY_WIDE)");

	//���v���C�}���o�b�t�@�쐬�i	���T�E���h�J�[�h�������I�ɍ쐬���Ă����\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

	ZeroMemory(&dsbd,sizeof(dsbd));		//�S�Ẵ����o���O�ŏ�����
	dsbd.dwSize = sizeof(dsbd);			//�\���̂̃T�C�Y
	dsbd.dwFlags =	DSBCAPS_CTRLVOLUME |	//���S�̂̃{�����[�����ߋ@�\������
					DSBCAPS_PRIMARYBUFFER;	//�v���C�}���o�b�t�@�ł��邱�Ƃ�����
	dsbd.dwBufferBytes = 0;		//�T�E���h�o�b�t�@�̃o�C�g�P�ʂ̃T�C�Y
	dsbd.lpwfxFormat = NULL;	//��(WAVE)�f�[�^���Ǘ����邽�߂̍\���̂ւ̃|�C���^

	//DSBUFFERDESC�\���̂ɐݒ肵���f�[�^�����ƂɃv���C�}���o�b�t�@���쐬����B
	res = lpDS->CreateSoundBuffer(&dsbd,&lpDSPrimary,NULL);
	if(FAILED(res))	//�v���C�}���o�b�t�@�̍쐬�Ɏ��s	�i��FAILED�����s�𔻒肷��@�\�̃}�N��
		ERR_MES_RETURN("�v���C�}���o�b�t�@�̍쐬�Ɏ��s")

	return TRUE;	//�����Ȃ̂ŁATRUE��Ԃ��B
}


//������������������������������������������������������������������������������������������������������������������������
BOOL DS_Load(int No)	//�@�\�F�����̃f�[�^�i���j���擾���A��������ƂɃZ�J���_���o�b�t�@���쐬����
//�������P�F�E�B���h�E�̃n���h��
//�������Q�F���ʉ��̔ԍ�
{
	HMMIO hmmio = NULL;				//mmio�t�@�C���n���h���p
	HRESULT			res;			//�ߒl�p
	LPVOID			p1,		p2;		// ���b�N�������̃u���b�N�P�ƁA�u���b�N�Q�̃|�C���^�i�[�p
	DWORD			size1,	size2;	// ���b�N�������̃u���b�N�P�ƁA�u���b�N�Q�̃o�C�g���i�[�p
	LONG			WaveBytes;		// �ǂݍ��񂾉��f�[�^�̃o�C�g���i�[�p

	parent.ckid = 0;				// �`�����N���ʎq
	parent.cksize = 0;				// �`�����N�̃f�[�^�����o�̃o�C�g��
	parent.fccType = ( FOURCC )0;	// �t�H�[���^�C�v
	parent.dwDataOffset = 0;		// �f�[�^�����o�̐擪�A�h���X
	parent.dwFlags = 0;				// �`�����N�Ɋւ���t�������w�肷��t���O

	child = parent;


	//�t�@�C�����J��
	hmmio = mmioOpen(	Wave_Data[ No ].lpFileName,	//�J���t�@�C����
						NULL,
						MMIO_READ);					//�ǂݎ���p�ŊJ��
	if(!hmmio)										//�G���[�`�F�b�N
	{
		ERROR_MESSAGE("mmioOpen");					//NULL���Ԃ��Ă����玸�s
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- Wave �`�����N�փf�B�Z���h���� ----------- //

	// Wave �`�����N�փf�B�Z���h(�ړ��j����
	parent.ckid =		mmioFOURCC( 'R', 'I', 'F', 'F' );
	parent.fccType =	mmioFOURCC( 'W', 'A', 'V', 'E' );

	if( mmioDescend( hmmio, &parent, NULL, MMIO_FINDRIFF ) )	//�`�����N���ʎq�uRIFF�v�Ǝw��̃t�H�[���^�C�v�����`�����N��T���B
	{	//���s����ƁAMMIOERR_CHUNKNOTFOUND���Ԃ�B
		ERROR_MESSAGE("Wave�t�@�C���ł͂Ȃ�");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- fmt �`�����N�փf�B�Z���h���� ------------ //

	// fmt �`�����N�փf�B�Z���h�i�ړ��j����
	child.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );

	if( mmioDescend( hmmio, &child, &parent, 0 ) )
	{	// Wave �t�@�C���� fmt �`�����N���Ȃ�
		ERROR_MESSAGE("Wave�t�@�C���� fmt �`�����N���Ȃ�");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ------- mmioRead �֐����g�p���� Wave �t�@�C������t�H�[�}�b�g����ǂݏo���� ------- //
	// -------------------------- WAVEFORMATEX �\���̂Ɋi�[���� ---------------------------- //

	// WAVEFORMATEX �\���̂̂��ׂẴ����o���O�ŏ�����
	ZeroMemory( &wfex, sizeof( WAVEFORMATEX ) );

	// Wave �t�@�C������A�t�H�[�}�b�g�����擾����
	if( mmioRead( hmmio, ( char * )&wfex, sizeof( WAVEFORMATEX ) ) != sizeof( WAVEFORMATEX ) )
	{	// fmt �`�����N�̓ǂݎ��Ɏ��s
		ERROR_MESSAGE("fmt �`�����N�̓ǂݎ��Ɏ��s");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// �ǂݎ�����t�@�C���� PCM �t�H�[�}�b�g�����ׂ�
	if( wfex.wFormatTag != WAVE_FORMAT_PCM )
	{	// PCM �t�H�[�}�b�g�ł͂Ȃ�
		ERROR_MESSAGE("PCM �t�H�[�}�b�g�ł͂Ȃ�");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- fmt �`�����N����A�Z���h���� ------------ //

	// mmioAscend �֐��ɂ��
	// fmt�`�����N����̃A�Z���h(�f�B�Z���h�����Ƃ��납��̕��A)���s��
	if( mmioAscend( hmmio, &child, 0 ) )
	{	// fmt �`�����N����̃A�Z���h�Ɏ��s
		ERROR_MESSAGE("fmt �`�����N����̃A�Z���h�Ɏ��s");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ----------- data �`�����N�փf�B�Z���h���� ----------- //

	// data �`�����N�փf�B�Z���h����
	child.ckid = mmioFOURCC( 'd','a','t','a' );

	if( mmioDescend( hmmio , &child , &parent , MMIO_FINDCHUNK ) )
	{	// Wave �t�@�C���Ƀf�[�^�`�����N���Ȃ�
		ERROR_MESSAGE("WAVE�t�@�C���Ƀf�[�^�`�����N���Ȃ�");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	// ---------------- Wave �T�E���h���i�[���邽�߂̃Z�J���_���o�b�t�@�� ------------------ // 
	// - DSBUFFERDESC �\���̂ɐݒ肵���f�[�^�����ɁACreateSoundBuffer �֐����g�p���쐬���� - //

	ZeroMemory( &dsbd, sizeof( dsbd ) );			// �\���̂̂��ׂẴ����o���O�ŏ�����
	dsbd.dwSize = sizeof( dsbd );					// �\���̂̃T�C�Y���w��

	dsbd.dwFlags =	DSBCAPS_GETCURRENTPOSITION2 |	// �Đ��J�[�\���̈ʒu���L������@�\
					DSBCAPS_GLOBALFOCUS |			// �O���[�o���ȃT�E���h�o�b�t�@�ƂȂ�
					DSBCAPS_STATIC |				// �P�x�ǂݍ��� Wave �f�[�^��ێ���������@�\
					DSBCAPS_CTRLPAN |				// �p�����ߋ@�\
					DSBCAPS_CTRLVOLUME |			// �{�����[�����ߋ@�\
					DSBCAPS_CTRLFREQUENCY;			// ���g�����ߋ@�\

	dsbd.dwBufferBytes = child.cksize;			// �擾���Ă���f�[�^�T�C�Y���i�[
	dsbd.lpwfxFormat = &wfex;					// �擾���Ă���t�H�[�}�b�g�����i�[

	//��DSBUFFERDESC �\���̂Ɏw�肵���f�[�^�����ɁA�Z�J���_���o�b�t�@���쐬����
	res	= lpDS->CreateSoundBuffer(&dsbd,&lpDSSoundBuffer[No],NULL);
	if( DS_OK != res )	//�G���[�`�F�b�N	
	{	// �Z�J���_���o�b�t�@�̍쐬�Ɏ��s
		ERROR_MESSAGE("�Z�J���_���o�b�t�@�̍쐬�Ɏ��s");
		mmioClose( hmmio , 0 );
		return FALSE;
	}
		 
	// ------ �Z�J���_���o�b�t�@�ɉ��f�[�^��ǂݍ��� ------- //

	//���Z�J���_���o�b�t�@�����b�N����
	res = lpDSSoundBuffer[ No ] -> Lock( 0, child.cksize, &p1, &size1, &p2, &size2, 0 );
	if( DS_OK != res )
	{	// ���b�N�Ɏ��s
		ERROR_MESSAGE("���b�N�Ɏ��s");
		mmioClose( hmmio , 0 );	
		return FALSE;
	}

	//�����b�N�����Z�J���_���o�b�t�@�ɁA���f�[�^��ǂݍ���
	WaveBytes = mmioRead( hmmio, ( char * )p1, child.cksize );

	//�t�@�C��������ۂɓǂݎ�����o�C�g�T�C�Y�𒲂ׂ�
	if( WaveBytes < 0 )
	{	// ���f�[�^�̓ǂݍ��݂Ɏ��s
		ERROR_MESSAGE("���f�[�^�̓ǂݍ��݂Ɏ��s");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	//���Z�J���_���o�b�t�@�̃��b�N���A�����b�N ( ���� ) ����
	res = lpDSSoundBuffer[ No ] -> Unlock( p1, size1, p2, size2 );
	if( DS_OK != res )
	{	// �A�����b�N�Ɏ��s
		ERROR_MESSAGE("�A�����b�N�Ɏ��s");
		mmioClose( hmmio , 0 );
		return FALSE;
	}

	//��Wave �t�@�C������
	mmioClose( hmmio , 0 );	// mmio �t�@�C�������


	//���{�����[���̐ݒ�
	res = lpDSSoundBuffer[ No ] -> SetVolume( Wave_Data[ No ].Vol );
	if( DS_OK != res )							//�G���[�`�F�b�N
		ERR_MES_RETURN("�{�����[���ݒ莸�s");	//�{�����[���ݒ莸�s

	//���p���̐ݒ�
	res = lpDSSoundBuffer[ No ] -> SetPan( Wave_Data[ No ].Pan );
	if( DS_OK != res )							//�G���[�`�F�b�N
		ERR_MES_RETURN("�p���ݒ莸�s");			//�p���ݒ莸�s


	//�����g���̐ݒ�
	res = lpDSSoundBuffer[ No ] -> SetFrequency( Wave_Data[ No ].Frequency );
	if( DS_OK != res )							//�G���[�`�F�b�N
		ERR_MES_RETURN("���g���ݒ莸�s");		//���g���ݒ莸�s


	return TRUE;
}

//������������������������������������������������������������������������������������������������������������������
void ReleaseDS()	//�@�\�F��DirectSound �֘A�̃I�u�W�F�N�g�̊J�����s���֐�
{
	int	i;

	//�쐬�����Z�J���_���o�b�t�@�̐������������
	for( i = 0 ; i < SOUND_MAX ; i ++ )
	{
		RELEASEDS( lpDSSoundBuffer[ i ] );
	}

	RELEASEDS( lpDSPrimary );			// �v���C�}���o�b�t�@
	RELEASEDS( lpDS );					// DirectSound �I�u�W�F�N�g
}


//����������������������������������������������������������������������������������������������������������������������������������������������������������
BOOL DS_Play(int No,BOOL LoopFlag)	//�@�\�F�Z�J���_���o�b�t�@(�T�E���h�f�[�^)�̍Đ����s���֐�
//�������P�F�Đ�������ʉ��̔ԍ�
//�������Q�F���[�v���邩�ǂ������w��	TRUE = ���[�v	FALSE = ���[�v����
{
	HRESULT		res;					//�ߒl�p
	DWORD		floop = 0;				//�T�E���h�̍Đ��t���O���Ǘ����邽�߂̕ϐ�

	if(LoopFlag)	//������TRUE�Ȃ�A���[�v�Đ�
		floop = DSBPLAY_LOOPING;

	res = lpDSSoundBuffer[No]->SetCurrentPosition(0);	//�Đ��J�[�\�������f�[�^�̐擪�ɃZ�b�g����
	if(DS_OK != res)									//�G���[�`�F�b�N
		ERR_MES_RETURN("�Đ��J�[�\���̐ݒ莸�s");

	res = lpDSSoundBuffer[No]->Play(0,0,floop);	//�Đ��J�[�\���̈ʒu����Z�J���_���o�b�t�@�̍Đ����s��
	if( DS_OK != res )									//�G���[�`�F�b�N
		ERR_MES_RETURN("�Đ����s");
	
	return TRUE;	//�Ō�܂ł����̂Ő����ATRUE��Ԃ��B
}

//������������������������������������������������������������������������������������������������������������������������������������
BOOL DS_Stop(int No )	//�@�\�F�Z�J���_���o�b�t�@ (�T�E���h�f�[�^) �̒�~���s���֐�
//�������P�F�Đ�������ʉ��̔ԍ�
{
	HRESULT res;	//�ߒl�p

	res = lpDSSoundBuffer[ No ]->Stop();	//�T�E���h���~����
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("�T�E���h��~���s");

	return TRUE;	//�����Ȃ̂ŁATRUE��Ԃ��B
}

//������������������������������������������������������������������������������������������������������������������������������������������
BOOL DS_VolumeChg(int No, long Val )	//�@�\�F�Z�J���_���o�b�t�@(�T�E���h�f�[�^)�̃{�����[����ݒ肷��֐�
//�������P�F�ύX������ʉ��̔ԍ�
//�������Q�F���݂���ح�т���̕ω���
{
	long		vol;		//�T�E���h�̃{�����[�����i�[���邽�߂̕ϐ�
	HRESULT		res;		//�ߒl�p

	res = lpDSSoundBuffer[No]->GetVolume(&vol);	//�T�E���h�̃{�����[�����擾����
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("�{�����[���擾���s");

	vol += Val;		//�擾������ح�т̒l(���݂���ح�т̒l)�Ɉ����Ŏw�肵����ح�т̒l��������

	// �{�����[���̕␳
	if(vol > 0		)	//�{�����[���̍ő�𒴂��Ȃ��悤��
		vol = 0;
	if(vol < -10000	)	//�{�����[���̍ŏ���菬�����Ȃ�Ȃ��悤��
		vol = -10000;

	res = lpDSSoundBuffer[ No ] -> SetVolume( vol );	//�{�����[����ݒ肷��
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("�{�����[���ݒ莸�s");

	return TRUE;	//�����Ȃ̂�TRUE��Ԃ��B
}


//������������������������������������������������������������������������������������������������������������������������������
BOOL DS_PanChg(int No,long Val)	//�@�\�F�Z�J���_���o�b�t�@ ( �T�E���h�f�[�^ ) �̃p���̐ݒ���s���֐�
//�������P�F�ύX������ʉ��̔ԍ�
//�������Q�F���݂̃p������̕ω���
{
	long		pan;			//�p���̒l���i�[���邽�߂̕ϐ�
	HRESULT		res;			//�ߒl�p

	res = lpDSSoundBuffer[No]->GetPan(&pan);	//�p���̒l���擾����
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("�p���̒l�擾���s");

	pan += Val;	//�擾�����p���̒l(���݂̃p���̒l)�ɁA�����Ŏw�肵���p���̒l��������

	// �p���̕␳
	if( pan > 10000 )
		pan = 10000;
	if( pan < -10000 )
		pan = -10000;

	res = lpDSSoundBuffer[No]->SetPan(pan);	//�p���̐ݒ�
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("�p���ݒ莸�s");

	return TRUE;	//�����Ȃ̂�TRUE��Ԃ�
}


//������������������������������������������������������������������������������������������������������������������������������
BOOL DS_FrequencyChg(int No, DWORD Frequency )	//�Z�J���_���o�b�t�@(�T�E���h�f�[�^)�̎��g���̐ݒ���s���֐�
//�������P�F�ύX������ʉ��̔ԍ�
//�������Q�F���݂̎��g������̕ω���
{
	DWORD		Freq_Val;		//���g���̒l���i�[���邽�߂̕ϐ�
	HRESULT		res;			//�ߒl�p

	res = lpDSSoundBuffer[No]->GetFrequency(&Freq_Val);	//���g���̒l���擾����
	//	ERR_MES_RETURN("���g���̒l�擾���s");

	Freq_Val += Frequency;	//�擾�������g���̒l(���݂̎��g���̒l)�ɁA�����Ŏw�肵�����g���̒l��������

	res = lpDSSoundBuffer[No]->SetFrequency(Freq_Val);	//���g���̐ݒ�
	if( DS_OK != res )	//�G���[�`�F�b�N
		ERR_MES_RETURN("���g���ݒ莸�s");

	return TRUE;	//�����Ȃ̂�TRUE��Ԃ��B
}
