#if !defined __GAMEBLTPROCMACRO
#define __GAMEBLTPROCMACRO
//��������������������������������������������������������������������������������������������������������������������������������������������
void MapBitBlt();						//�}�b�v�\���֐��̃v���g�^�C�v�錾
LPDIRECTDRAWSURFACE7 Return_lpDDSOff();	//�}�b�v�`�b�v�̉摜���T�[�t�F�[�X���X�e�[�W�ɂ���ĕύX����֐��̃v���g�^�C�v�錾
void ChrBitBlt(CHR_DATA*,ANIME_DATA*,int);	//�L�����\���֐��̃v���g�^�C�v�錾
void SwdBitBlt(CHR_DATA*,ANIME_DATA*,int);	//���\���֐��̃v���g�^�C�v�錾
//void DumBitBlt(CHR_DATA*,ANIME_DATA*,int);	//���g�\���֐�
void ShotBitBlt(SHOT_DATA*);				//�e��\������֐��̃v���g�^�C�v�錾
void EFBitBlt(EF_DATA*);					//�G�t�F�N�g��\������֐��̃v���g�^�C�v�錾
void OBJBitBlt(OBJ_DATA*);					//�I�u�W�F�N�g��\������֐��̃v���g�^�C�v�錾
void BgObjBlt(BGOBJ_DATA*);					//�w�i�I�u�W�F�N�g��\������֐��̃v���g�^�C�v�錾
void PlrHpBlt();								//�v���C���[��HP��\������֐��̃v���g�^�C�v�錾
void EneHpBlt(CHR_DATA*);						//�_���[�W���󂯂��G�l�~�[��HP��\������֐��̃v���g�^�C�v�錾
void DamageX_BitBlt(CHR_DATA*,ANIME_DATA*,int);	//������Ń_���[�W��������Ƃ��̊G��\������֐��̃v���g�^�C�v�錾
void DamageY_BitBlt(CHR_DATA*,ANIME_DATA*,int);	//�c�a��Ń_���[�W���󂯂鎞�̊G��\������֐��̃v���g�^�C�v�錾
void Kill_X_BitBlt(CHR_DATA*,ANIME_DATA*,int,int);	//�G�����ɐ؂��G��\������֐��̃v���g�^�C�v�錾
void Kill_Y_BitBlt(CHR_DATA*,ANIME_DATA*,int,int);	//�G���c�ɐ؂��G��\������֐��̃v���g�^�C�v�錾
//void DIB_EF();										//24�r�b�gDIB�摜�𑀍삷��֐��̃v���g�^�C�v�錾
//������������������������������������������������������������������������������������������������������������������������������������������������
#endif