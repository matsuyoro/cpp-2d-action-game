#if !defined __GAMECHECKPROCMACRO
#define __GAMECHECKPROCMACRO
//��������������������������������������������������������������������������������������������������������������������������
int CharAnime(CHR_DATA*,ANIME_DATA*,ANIME_DATA*);
void PlrAction(CHR_DATA*,ANIME_DATA*);			//�v���C���[�A�N�V�����̊֐��̃v���g�^�C�v�錾
void EnAction(CHR_DATA*,ANIME_DATA*);			//�G�l�~�[�A�N�V�����̊֐��̃v���g�^�C�v�錾
int KeyCmdChk(int);									//�R�}���h���͂̃f�[�^�̊֐��̃v���g�^�C�v�錾
void OBJON(OBJ_DATA*,int,int,int);						//�I�u�W�F�N�g���o�����߂̊֐��̃v���g�^�C�v�錾
void BgObjOn(BGOBJ_DATA*,int,int,int,int);					//�w�i�I�u�W�F�N�g���o�����߂̊֐��̃v���g�^�C�v�錾
void EFON(EF_DATA*,int,int,int);						//�G�t�F�N�g���o�����߂̊֐��̃v���g�^�C�v�錾
void EFOFF(EF_DATA*);									//�G�t�F�N�g�̃A�j���[�V�����Ƒ��݂������֐��̃v���g�^�C�v�錾
void ShotFire(int,int,int,int,int);					//�e�̔��˂������֐��̃v���g�^�C�v�錾
void ShotMove(int,int);							//�e�̈ړ��������֐��̃v���g�^�C�v�錾
void EnemyOnPos();							//�G�l�~�[�o��������
void PlrSwdChk(CHR_DATA*,CHR_DATA*);					//�L�����ƌ��̓����蔻��̃v���g�^�C�v�錾
void ChrHitChk(CHR_DATA*,CHR_DATA*);					//�L�����ƃL�����̓����蔻����s���ւ��̃v���g�^�C�v�錾
int ShotHitChk(SHOT_DATA*,CHR_DATA*);					//�e�ƃL�����̓����蔻��
int AtkHitChk(CHR_DATA*,CHR_DATA*);						//�U������͈͂ƃ_���[�W���󂯂�L�����̔���
void UpDownChk(CHR_DATA*);								//�㏸���~�̊֐��̃v���g�^�C�v�錾
void ChrXScroll();										//X�����ɃX�N���[���������L�����Ȃǂ����炷�֐�
void ChrYScroll();										//Y�����ɃX�N���[���������L���������炷�֐�
//��������������������������������������������������������������������������������������������������������������
#endif