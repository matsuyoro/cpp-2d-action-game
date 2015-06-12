#if !defined __GAMESTRUCTMACRO
#define __GAMESTRUCTMACRO
//����������������������������������������������������������������������������������������������������
#include <ddraw.h>

struct WAVE_DATA	//�g�p���� Wave �t�@�C���̃f�[�^���Ǘ����邽�߂̍\����
{
	char *	lpFileName;		// �g�p����f�[�^�̃t�@�C���p�X
	long	Vol;			// �{�����[��
	long	Pan;			// �p��
	DWORD	Frequency;		// ���g��
};
struct ANIME_DATA	//�A�j���[�V�����p�\���̂̌^�̒�`
{
	int Num;		//�A�j���[�V��������G��1���̊G�̔ԍ�������
	int TimeMax;	//�\������
	int Change;		//���̃A�j���[�V�����ɐ؂�ւ��Ă������ǂ����𔻒肷��B0���ύX�s�� 1���ύX�\
	int w;			//�A�j���[�V��������G�̕�
	int h;			//�A�j���[�V��������G�̍���
	int ynum;		//�A�j���[�V��������G���c�ɉ��s�Ȃ��ł��邩
	LPDIRECTDRAWSURFACE7 Bmp;		//�\������A�j���[�V�����̊G�̃t�@�C��
};
struct WAZA_DATA	//�Z�f�[�^�p�\���̂̌^�̒�`
{
	int Cmd[8];			//�\���L�[�̃f�[�^������
	int Btn;			//�{�^��������
	int Time;			//���͎��Ԃ�����
};
struct HIT_DATA		//�����蔻�蕔���̍\���̂̌^�̒�`
{
	int x;			//���゘���W
	int y;			//���゙���W
	int w;			//��
	int h;			//����
};
struct ENE_ONPOS	//�G�l�~�[�̏o���������\���̂̌^�̒�`
{
	int x;			//�o���ʒuX(�}�b�v�S�̂̂ł̈ʒu
	int	y;			//�o���ʒuY(�}�b�v�S�̂̂ł̈ʒu
	int type;		//�o��������G�l�~�[�̎��
	BOOL OnFlag;		//��x�o��������������̃|�C���g����o�������Ȃ����邽�߂̃t���O
};
struct CHR_DATA		//�L�����\���̂̌^�̒�`
{
	int Type;		//�L�����̎��
	int x;			//�L����X���W
	int y;			//�L����Y���W
	int w;			//�L�����̕�
	int h;			//�L�����̍���
	int muki;		//�L�����̌���(0 =�@�E���� 1 = �������j
	int AniType;		//�A�j���[�V�����̎��
	int AniNum;			//���݂̃A�j���[�V�����̉��Ԗڂ�
	int AniTimeNow;		//���݂̊G���ǂ̂��炢�\�����Ă��邩
	int AniTurn;		//�A�j���[�V�����Ń��[�v�Ŗ߂�ꏊ
	int OldAniType;		//�O��̃A�j���[�V�����̎�ނ�����
	int Land;			//�n�ʂɑ��������Ă��邩����
	double U;			//XY�����̈ړ����x������
	int MoveChkX;		//�O��̃L����X���W������
	int MoveChkY;		//�O��̃L����Y���W������
	int HitD;			//�U�����������Ă��邩�ǂ���������
	BOOL HitA;			//�U�������ǂ���������
	int Hp;				//�L�����̗͂�����
	BOOL Son;			//���݂��Ă��邩�ǂ���������
	int Act[5];			//�G�L�����Ȃǂ��ǂ������s�������邩�������ԍ�����ꂽ�z��
	int ActNum;			//�G�̌��ݎ��s���̍s���̔ԍ���ۑ����Ă����ϐ�
	int Cnt;			//�G�L�������������ȂǂɎg���i�J�E���g�ő҂������肷��j
	HIT_DATA Hit;		//�L�����̓����蔻��p
	int MaxHp;			//�L�����̍ő�HP������
	int Atk;			//�L�����̍U���͂�����
	int Spd;			//�L�����̃X�s�[�h������
};
struct SHOT_DATA	//�e�������\����
{
	int Type;	//�e�̎�ނ�����
	int x;	//�e������WX,Y
	int y;
	int w;	//�e��
	int h;
	int bx;	//�e�̉摜��X,Y
	int by;
	int mx;	//�e�ړ����xX,Y
	int my;
	int AniCnt;	//�A�j���[�V�����\���̃J�E���^
	int AniMax;	//�A�j���[�V�����ŕ\������G�̖���
	BOOL Son;	//�e�̑��݂������@�Ɓ@�N���o�����e��������
	HIT_DATA Hit;	//�e�̓����蔻��͈̔͂�����
	int Atk;	//�V���b�g�̈З�
};
struct EF_DATA		//�G�t�F�N�g�������\����
{
	int x;	//����\���ʒuX,Y
	int y;
	int w;	//���A����
	int h;
	int bx;	//EF�̉摜��X,Y
	int by;
	int AniCnt;	//�A�j���[�V�����\���̃J�E���^
	int AniMax;	//�A�j���[�V�����ŕ\������G�̖���
	BOOL Son;	//�G�t�F�N�g�̑��݂�����
};
struct OBJ_DATA		//�I�u�W�F�N�g�������\���́i���������f�[�^
{
	int Type;	//�I�u�W�F�̎�ނ�����
	int x;		//����\���ʒuX,Y
	int y;
	int w;		//���A����
	int h;
	int bx;		//�I�u�W�F�̉摜�����WX,Y
	int by;
	int AniCnt;	//�A�j���[�V�����\���J�E���^
	int AniMax;	//�A�j���[�V�����ŕ\������G�̖���
	BOOL Son;	//�I�u�W�F�̑��݂�����
};
struct BGOBJ_DATA	//�w�i�̃I�u�W�F�N�g�������\���́i�w�i�̕����������f�[�^
{
	int Type;	//�I�u�W�F�̎�ނ�����
	int x;		//�\����XY���W
	int y;
	int w;		//���A����
	int h;
	int bx;		//�I�u�W�F�̉摜�����WX,Y
	int by;
	int AniCnt;	//�A�j���[�V�����\���J�E���^
	int AniMax;	//�A�j���[�V�����ŕ\������G�̖���
	BOOL Son;	//�I�u�W�F�̑��݂�����
	int Line;	//�w�i�̂ǂ̗�ɔw�i���邩������
	int orgX;	//����x���W������
};
//������������������������������������������������������������������������������������������������������������
#endif