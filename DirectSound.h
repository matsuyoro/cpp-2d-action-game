#if !defined __DIRECTSOUNDMACRO
#define __DIRECTSOUNDMACRO
//������������������������������������������������������������������������������������������������������������������������������
BOOL DS_Init();						//�_�C���N�g�T�E���h�̏�����
BOOL DS_Load(int);						//���f�[�^���擾���A�Z�J���_���o�b�t�@���쐬����֐�
BOOL DS_Play(int,BOOL);				//�Z�J���_���o�b�t�@�̍Đ����s���֐�
BOOL DS_Stop(int);					//�Z�J���_���o�b�t�@�̒�~���s���֐�
BOOL DS_VolumeChg(int,long);			//�Z�J���_���o�b�t�@�̃{�����[����ݒ肷��֐�
BOOL DS_PanChg(int,long);			//�Z�J���_���o�b�t�@�̃p���̐ݒ���s���֐�
BOOL DS_FrequencyChg(int,DWORD);		//�Z�J���_���o�b�t�@�̎��g���̐ݒ���s���֐�
void ReleaseDS();						//DirectSound�֘A�̃I�u�W�F�N�g�̉���̊֐�
//����������������������������������������������������������������������������������������������������������������������������������������
#endif
