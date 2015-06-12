#include <windows.h>	//�E�B���h�E�Y�̃w�b�_

#include "Extern.h"		//�O���ϐ��̃w�b�_
#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "DirectSound.h"

#include "GameCheckProc.h"	//����֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
//-----------------------------------------------------
void Enemy_1(CHR_DATA*,ANIME_DATA*);	//�G�l�~�[�P�������֐��̃v���g�^�C�v�錾
void Enemy_2(CHR_DATA*,ANIME_DATA*);
void Enemy_3(CHR_DATA*,ANIME_DATA*);	//��
void Enemy_4(CHR_DATA*,ANIME_DATA*);	//
void Enemy_5(CHR_DATA*,ANIME_DATA*);	//��
void Enemy_6(CHR_DATA*,ANIME_DATA*);	//��
void Enemy_7(CHR_DATA*,ANIME_DATA*);	//������
void Enemy_8(CHR_DATA*,ANIME_DATA*);	//�S��
void Enemy_9(CHR_DATA*,ANIME_DATA*);	//������
void Enemy_10(CHR_DATA*,ANIME_DATA*);	//�I
void Enemy_11(CHR_DATA*,ANIME_DATA*);	//�c�{
void Enemy_12(CHR_DATA*,ANIME_DATA*);	//����
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EnAction()		//�@�\�F�G�l�~�[�A�N�V�����֐�
{
	int i;	//�J�E���^
	void (*pEneAct[13])(CHR_DATA*,ANIME_DATA*);	//�ߒl�Ȃ��A�́A�֐��̃|�C���^�z��̐錾

	//pEneAct[0]�͎g��Ȃ�
	pEneAct[1] = Enemy_1;	//�G�l�~�[�P�̊֐����֐��̃|�C���^�z��ň���
	pEneAct[2] = Enemy_2;	//
	pEneAct[3] = Enemy_3;	//
	pEneAct[4] = Enemy_4;	//
	pEneAct[5] = Enemy_5;
	pEneAct[6] = Enemy_6;
	pEneAct[7] = Enemy_7;	//������
	pEneAct[8] = Enemy_8;	//�S��
	pEneAct[9] = Enemy_9;	//������
	pEneAct[10] = Enemy_10;	//�I
	pEneAct[11] = Enemy_11;	//�c�{
	pEneAct[12] = Enemy_12;	//����

	for(i = 0;i < ENE_MAX;i++)	//�G�l�~�[�̍ő吔���J��Ԃ�
	if(En[i].Son)					//�G�l�~�[�����݂�����
	{
		if(	//�K����ʓ��ɂ�����A�N�V�������N����
		(	(En[i].x+En[i].w+WMoveX > WMoveX && En[i].x+WMoveX < WMoveX+640)
		&&	(En[i].y+En[i].h+WMoveY > WMoveY && En[i].y+WMoveY < WMoveY+480)	)
		|| En[i].HitD	//or�K���U�����󂯂�A�N�V�����͏��
		)
		{
			pEneAct[En[i].Type](&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum]);	//�֐��̃|�C���^�z��̗v�f�ԍ��iGameNum�j�ɑΉ������֐������s
			if(En[i].Cnt > 0) En[i].Cnt--;		//�J�E���g���Ԃ��Z�b�g����Ă����疈��}�C�i�X�P
			//���̂��̊֐������s����Ƃ��ɕK�v�ȃf�[�^��ۑ�
			En[i].OldAniType = En[i].AniType;	//�O��̃A�j���[�V�����̎�ނ�ۑ�
		}
	}
}
//------------------------------���G�l�~�[�A�N�V�����֐���------------------------------------------
//////�i���j//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_1 (CHR_DATA *pC,ANIME_DATA *pA)	//�@�\�F�G�l�~�[�P�̍s�����܂Ƃ߂��֐�
//�������P�F�G�l�~�[�̃L�����f�[�^
//�������Q�F�G�l�~�[�̃A�j���[�V�����f�[�^
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���

		if(pC->ActNum == 0 || pC->ActNum == 1)	//�E�ړ������ړ��Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//�v���C���[�̍��W�����Ɉړ�������ς���
				pC->ActNum = 0;							//���ړ��̃A�N�V����
			else
				pC->ActNum = 1;							//�E�ړ��̃A�N�V����
		}
		if(pC->ActNum == 3 || pC->ActNum == 4)
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//Plr�̍��W�����ɃW�����v������������߂�
				pC->ActNum = 4;							//���W�����v�̃A�N�V����
			else
				pC->ActNum = 3;							//�E�W�����v�̃A�N�V����
		}
	}
	if(pC->HitD)	//�_���[�W����������
	{
		pC->ActNum = 5;	
	}



	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//�����A�^�b�N
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����0�i�ړ�			
				if(pC->OldAniType != 1)	//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 50;		//���̍s�������鎞��
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 3;				//���[�v���Ė߂�G
			}
			if(pC->AniNum > 2)	pC->x -= 7;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}
		break;
	case 1:	//���E�A�^�b�N
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����0�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ�0�Ȃ�
				{
					pC->Cnt = 50;	//���̍s�������鎞��
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 3;				//���[�v���Ė߂�G
			}
			if(pC->AniNum > 2)	pC->x += 7;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA������������
		}
		break;
	case 2:	//���ҋ@
		if(pC->Land == 1 && pA->Change || (pC->Land == 1 && pC->OldAniType == 2))//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)			//�O��̃A�j�����O�ȊO�Ȃ�
			{
				pC->Cnt = 20;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
		break;
	case 3:	//���E�W�����v
		if(pA->Change && pC->Land == 1)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//�W�����vUP�A�j���[�V����
			if(pC->OldAniType == 0)				//�n�ʂɑ��������Ă��邩����
			{
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
				pC->U = -15;				//�������鑬�x������U��15.0�ɂ���
			}
			pC->AniTurn = 3;		//�A�j���[�V�������Ă��ǂ�G
		
			pC->muki = 1;			//�E�Ɍ���
		}
		if(!pC->Land && pC->AniType == 2)
		{
			pC->Cnt = 2;	//�����Ă���Ԃ�Cnt���Q�ɂ��āA�A�N�V�����ύX�ł��Ȃ�����i�P���Ɓ[�P����ĂO�ɂȂ�̂Ń_��
			pC->x += 6;		//�E�Ɉړ�
		}
		break;
	case 4:	//�����W�����v
		if(pA->Change && pC->Land == 1)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//�W�����vUP�A�j���[�V����
			if(pC->OldAniType == 0)				//�n�ʂɑ��������Ă��邩����
			{
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
				pC->U = -15;				//�������鑬�x������U��15.0�ɂ���
			}
			pC->AniTurn = 3;		//�A�j���[�V�������Ă��ǂ�G
			pC->muki = 0;			//���Ɍ���
		}
		if(!pC->Land && pC->AniType == 2)	
		{
			pC->Cnt = 2;	//�����Ă���Ԃ�Cnt���Q�ɂ��āA�A�N�V�����ύX�ł��Ȃ�����i�P���Ɓ[�P����ĂO�ɂȂ�̂Ń_��
			pC->x -= 6;		//���Ɉړ�
		}
		break;
	case 5:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 20;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -8;
		}
		if(pC->muki)	pC->x -=5;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=5;	//�������Ȃ�E�ɔ��
		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;
	}
}
////�i�g�J�Q�j//////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_2(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		
		if(pC->ActNum == 1 || pC->ActNum == 2)	//�E�ړ������ړ��Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->ActNum = 1;		//���ړ��̃A�N�V����
			else
				pC->ActNum = 2;		//�E�̈ړ��̃A�N�V����
		}
	}
	if(pC->HitD)	//�_���[�W�t���O��TRUE�Ȃ�
	{
		pC->ActNum = 4;
	}




	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change && pC->Land == 1)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
		break;
	case 1:	//�����ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 22;		//���̍s�������鎞�Ԃ�ݒ�
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 1;				//���[�v���Ė߂�G
			}
			pC->x -= 2;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}
		break;
	case 2:	//���E�ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 22;
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 1;				//���[�v���Ė߂�G
			}
			pC->x += 2;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA�E����������
		}
		break;
	case 3:	//���Ή����ˁi�ߋ���
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//���݂��A�j���[�V����
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 36;			//���̃A�N�V�������s�����Ԃ�ݒ�
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;		//�A�j���[�V�������Ă��ǂ�G
		}
		if(pC->Cnt > 3 && pC->Cnt < 29)	//�R�X�`�R�܂ł̊ԉΉ�����
		{
			if(pC->muki == 0)	//�������Ȃ�
			{
				ShotFire(pC->x,pC->y+30,0,18,1);			//�e�̔���
				DS_Play(6,FALSE);	//���ʉ���炷
			}else				//����������Ȃ��Ȃ�
			{
				ShotFire(pC->x+pC->w-48,pC->y+30,1,18,1);	//�e����
				DS_Play(6,FALSE);
			}
		}
		break;
	case 4:	//���_���[�W
		pC->AniType = 4;
		if(pC->OldAniType != 4)
		{
			pC->Cnt = 15;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=2;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;
	}
}
//////�i���j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_3(CHR_DATA *pC,ANIME_DATA *pA)
{
	int i,j;
	int AX,BX;			//�{�X�P�̎�X���W������
	int	AY,BY;			//�{�X�P�̎�Y���W������
	int NeckNum = 0;	//��̐�������

	static int ATPosX,ATPosY;	//���ݕt���̓ːi���W��ۑ����Ă����ϐ�

	for(i = 0;i < OBJ_MAX;i++)	//�{�X�P�̂̃I�u�W�F��T��
	{
		if(Obj[i].Son && Obj[i].Type == 0)	//�{�X�P�̂̃I�u�W�F�����݂�����
		{
			NeckNum = 1;	//��̕��я�������

			AX = pC->x + (pC->w>>1);		//���X���W������
			BX = Obj[i].x + (Obj[i].w>>1);	//�̂�X���W������
			AY = pC->y + (pC->h>>1);		//���Y���W������
			BY = Obj[i].y + (Obj[i].h>>1);	//�̂�Y���W������

			for(j = 0;j < OBJ_MAX;j++)	//�{�X�P��̃I�u�W�F��T��
			{
				if(Obj[j].Son && (Obj[j].Type == 2 || Obj[j].Type == 3 || Obj[j].Type == 4))	//�{�X�P��Ԑڂ̃I�u�W�F�����݂�����
				{
					Obj[j].x = BX + (((AX - BX)/10)*NeckNum) - (Obj[j].w>>1);	//��I�u�W�F��X���W���v�Z
					Obj[j].y = BY + (((AY - BY)/10)*NeckNum) - (Obj[j].h>>1);	//��I�u�W�F��Y���W���v�Z
					NeckNum++;	//���̎�̃I�u�W�F�Ŏg��NeckNum���{�{
					if(NeckNum > 10)		//���5�\��������
					{
						NeckNum = 1;	//�P�ɖ߂�
						break;			//���[�v���ʂ���
					}
				}
			}
		}				
	}

	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���

		//�v���C���[�������Ɖ΂̋ʂ��o��
		if((pC->x+(pC->w>>1)-300 > Plr.x+(Plr.w>>1) 
		|| pC->x+(pC->w>>1)+300 < Plr.x+(Plr.w>>1))
		&& rand()%2 == 1						  )
			pC->ActNum = 2;

		if(pC->ActNum == 0 || pC->ActNum == 2  || pC->ActNum == 3)	//�ʏ��ԂȂ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//�v���C���[�������ɂ�����
			{
				pC->x -= 3;
				pC->muki = 0;
			}else
			{
				pC->x += 3;
				pC->muki = 1;
			}

			if(Plr.y+(Plr.h>>1) < pC->y+(pC->h>>1))	//�v���C���[���㑤�ɂ�����
				pC->y -= 3;
			else
				pC->y += 3;
		}
	}

	if(pC->HitD)	//�_���[�W�t���O��TRUE�Ȃ�
		pC->ActNum = 4;

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
		break;
	case 1:	//�����݂�
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 1;		//���݂��A�j���[�V����
			if(pC->OldAniType != 1)
			{
				ATPosX = pC->x+(pC->w>>1);	//�ːi���W��ۑ����Ă����Ɋ炪�߂�悤��
				ATPosY = pC->y+(pC->h>>1);
				pC->Cnt = 65;
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;		//�A�j���[�V�������Ă��ǂ�G
		}
		if(pC->Cnt < 52 && pC->Cnt > 32)	//�v���C���[�Ɍ������Ă���
		{
			if(Dum[1].x+(Dum[1].w>>1) < pC->x+(pC->w>>1))	//�v���C���[�������ɂ�����
			{	pC->x -= 8;
				pC->muki = 0;
			}else
			{	pC->x += 8;
				pC->muki = 1;
			}

			if(Dum[1].y+(Dum[1].h>>1) < pC->y+(pC->h>>1))	//�v���C���[���㑤�ɂ�����
				pC->y -= 5;
			else
				pC->y += 5;
/*
			if(pC->AniNum == 5)	//����f��
			{
				if(pC->muki == 0)	//�������Ȃ�
					ShotFire(pC->x+20,pC->y+20,0,18,1);			//�e�̔���
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,18,1);	//�e�̔���
			}
*/
		}
		if(pC->Cnt <= 32)	//���߂�
		{
			if(pC->x+(pC->w>>1) < ATPosX)	//�v���C���[�������ɂ�����
			{
				pC->x += 4;
				pC->muki = 0;
			}else
			{
				pC->x += 4;
				pC->muki = 1;
			}

			if(pC->y+(pC->w>>1) < ATPosY)	//�v���C���[���㑤�ɂ�����
				pC->y += 3;
			else
				pC->y -= 3;
		}
		break;
	case 2:	//���΂̋�
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//���݂��A�j���[�V����
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;		//�A�j���[�V�������Ă��ǂ�G
		}
		if(pC->Cnt == 1)
		{
			if(pC->Hp <= pC->MaxHp>>2)	//�G�l�~�[��HP��4���P�ȉ��ɂȂ�����
			{	
				if(pC->muki == 0)	//�������Ȃ�
					ShotFire(pC->x+20,pC->y+20,0,26,1);	//�e�̔���
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,26,1);	//�e�̔���
			}else
			{
				if(pC->muki == 0)	//�������Ȃ�
					ShotFire(pC->x+20,pC->y+20,0,3,1);	//�e�̔���
				else
					ShotFire(pC->x+pC->w-20,pC->y+20,1,3,1);	//�e�̔���
			}
		}

		break;
	case 3:	//���Ή�����
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//���݂��A�j���[�V����
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;		//�A�j���[�V�������Ă��ǂ�G
		}
		if(pC->Cnt < 10 && pC->Hp <= pC->MaxHp>>2)	//����f��
		{
			if(pC->muki == 0)	//�������Ȃ�
				ShotFire(pC->x+20,pC->y+20,0,18,1);			//�e�̔���
			else
				ShotFire(pC->x+pC->w-20,pC->y+20,1,18,1);	//�e�̔���
		}

		break;
	case 4:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 12;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=2;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;

	}

}
//////�i���J���j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_4(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		if(pC->ActNum == 3)	//���C�̃A�N�V�����Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//��������
			else
				pC->muki = 1;			//�E������
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//�E�ړ������ړ��Ȃ�	
		{
			if(pC->x > 500 || pC->x < 140)			//�G�l�~�[�R����ʂ̊O���Ȃ�
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 1;	//���ړ��̃A�N�V����
				else
					pC->ActNum = 2;	//�E�̈ړ��̃A�N�V����
			}else	//�O���łȂ��Ȃ�
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 2;	//���ړ��̃A�N�V����
				else
					pC->ActNum = 1;	//�E�̈ړ��̃A�N�V����
			}
			
		}
	}
	if(pC->HitD)
		pC->ActNum = 4;	//�_���[�W�A�N�V����

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 5;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//�����ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 20;		//���̍s�������鎞�Ԃ�ݒ�
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
			}
			pC->x -= 3;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}
		break;
	case 2:	//���E�ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 20;
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
			}
			pC->x += 3;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA�E����������
		}
		break;
	case 3:	//�����C
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;			//���̃A�j���[�V�������s������
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
		}
		if(pC->Cnt == 7)	//�̂���J�E���g���V�Ȃ�
		{
			if(pC->muki == 0)	//�������Ȃ�	
			{	
				ShotFire(pC->x,pC->y+30,0,5,1);	//�e�̔���
				DS_Play( 4, FALSE );			//���ʉ���炷
			}else				//����������Ȃ��Ȃ�
			{
				ShotFire(pC->x+pC->w,pC->y+30,1,5,1);		//�e�̔���
				DS_Play( 4, FALSE );			//���ʉ���炷
			}
		}
		break;
	case 4:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 8;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=1;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=1;	//�������Ȃ�E�ɔ��
		
		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}		
		break;

	}
}
//////�i���j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_5(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		if(pC->ActNum == 3)	//���C�̃A�N�V�����Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//��������
			else
				pC->muki = 1;			//�E������
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//�E�ړ������ړ��Ȃ�	
		{
			if(pC->x > 520 || pC->x < 120)			//�G�l�~�[�R����ʂ̊O���Ȃ�
			{
				if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
					pC->ActNum = 1;	//���ړ��̃A�N�V����
				else
					pC->ActNum = 2;	//�E�̈ړ��̃A�N�V����
			}else	//�O���łȂ��Ȃ�
			{
					pC->ActNum = 0 ;	//�ҋ@�A�N�V����
			}
			
		}
	}
	if(pC->HitD)
		pC->ActNum = 4;	//�_���[�W�A�N�V����

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 5;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//�����ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 30;		//���̍s�������鎞�Ԃ�ݒ�
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 0;
			}
			pC->x -= 4;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}
		break;
	case 2:	//���E�ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 30;
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 4;
			}
			pC->x += 4;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA�E����������
		}
		break;
	case 3:	//�����C
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 33;			//���̃A�j���[�V�������s������
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
		}
		if(pC->Cnt == 3)	//�̂���R�̎��ɒe����
		{
			if(pC->muki == 0)	//�������Ȃ�
			{
				ShotFire(pC->x,pC->y+18,0,1,1);	//�e�̔���
				DS_Play( 3, FALSE );			//���ʉ���炷
			}else				//����������Ȃ��Ȃ�
			{
				ShotFire(pC->x+pC->w,pC->y+18,1,1,1);		//�e�̔���
				DS_Play( 3, FALSE );			//���ʉ���炷
			}
		}
		break;
	case 4:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 8;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=2;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;


	}
}
/////�i�ΐl�ԁj/////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_6(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		if(pC->ActNum == 3)	//���C�̃A�N�V�����Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//��������
			else
				pC->muki = 1;			//�E������
		}
		if(pC->ActNum == 1 || pC->ActNum == 2	)//�E�ړ������ړ��Ȃ�	
		{

			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->ActNum = 1;	//���ړ��̃A�N�V����
			else
				pC->ActNum = 2;	//�E�̈ړ��̃A�N�V����			
		}
	}
	if(rand()%2 == 1 && pC->Land == 1)	//�n�ʂɑ��������Ă��ė������P�Ȃ�
		ShotFire(pC->x+(rand()%32),pC->y+pC->h-32+(rand()%6),0,7,1);	//�e�̔��ˁi�n�ʂɔz�u����e
	if(pC->HitD)	//�_���[�W�t���O��TRUE�Ȃ�
		pC->ActNum = 4;	//�_���[�W�A�N�V����


	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 20;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
		}
		break;
	case 1:	//�����ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 50;		//���̍s�������鎞�Ԃ�ݒ�
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 0;
			}
			pC->x -= 2;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}

		break;
	case 2:	//���E�ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����1�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 50;
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 4;
			}
			pC->x += 2;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA�E����������
		}

		break;
	case 3:	//�����C
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 50;			//���̃A�N�V�������T�O�t���[��
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;
		}
		if(pC->muki == 0)	//�������Ȃ�	
		{
			ShotFire(pC->x+(pC->w>>1)-24,pC->y,0,6,1);	//�e�̔���
			DS_Play(6,FALSE);	//���ʉ���炷
		}else				//����������Ȃ��Ȃ�
		{
			ShotFire(pC->x+(pC->w>>1)-24,pC->y,1,6,1);		//�e�̔���
			DS_Play(5,FALSE);	//���ʉ���炷
		}
		break;
	case 4:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 10;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->muki)	pC->x -=2;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=2;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;

		
	}
}
////�i�}�j//////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_7(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		
		if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
			pC->muki = 1;		//�������v���C���[�̕�����
		else
			pC->muki = 0;		//

		if(Plr.x+(Plr.w>>1) > pC->x+(pC->w>>1)-32
		&& Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1)+32)
		{
			pC->ActNum = 1;
		}
	}
	if(pC->HitD)	//�U�����󂯂���
		pC->ActNum = 2;	//�_���[�W�A�N�V����

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change && pC->Land == 1)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)
			{
				pC->Cnt = 10;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
		break;
	case 1:	//���U��
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 1;		//�U���A�j���[�V����
			if(pC->OldAniType != 1)
			{
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;		//�A�j���[�V�������Ă��ǂ�G
		}
		break;
	case 2:	//���_���[�W
		pC->AniType = 2;
		if(pC->OldAniType != 2)
		{
			pC->Cnt = 5;		//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;

	}
}
//////�i�S���j//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_8 (CHR_DATA *pC,ANIME_DATA *pA)	//�@�\�F�G�l�~�[�W�̍s�����܂Ƃ߂��֐�
//�������P�F�G�l�~�[�̃L�����f�[�^
//�������Q�F�G�l�~�[�̃A�j���[�V�����f�[�^
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%5];	//�G�̍s�����܂��̓����_���ň���

		if(pC->ActNum == 2 || pC->ActNum == 1)	//�E�ړ������ړ��Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//�v���C���[�̍��W�����Ɉړ�������ς���
				pC->ActNum = 2;							//���ړ��̃A�N�V����
			else
				pC->ActNum = 1;							//�E�ړ��̃A�N�V����
		}
		if(pC->ActNum == 3 || pC->ActNum == 4)
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//Plr�̍��W�����ɃW�����v������������߂�
				pC->ActNum = 4;							//���W�����v�̃A�N�V����
			else
				pC->ActNum = 3;							//�E�W�����v�̃A�N�V����
		}
	}
	if(pC->HitD)	//�_���[�W����������
	{
		pC->ActNum = 5;	
	}



	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pC->Land == 1 && pA->Change || (pC->Land == 1 && pC->OldAniType == 2))//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			if(pC->OldAniType != 0)			//�O��̃A�j�����O�ȊO�Ȃ�
			{
				pC->Cnt = 50;
				pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
		break;
	
	case 1:	//���E�A�^�b�N
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����0�i�ړ�			
				if(pC->OldAniType != 1)		//�O��̃A�j���[�V�����̎�ނ�0�Ȃ�
				{
					pC->Cnt = 50;			//���̍s�������鎞��
					pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;		//�J�E���^���O��
				}
				pC->AniTurn = 3;		//���[�v���Ė߂�G
			}
			if(pC->AniNum > 2)	pC->x += 7;					//�L���������Ɉړ�
			pC->muki = 1;			//�������P�ɂ��āA������������
		}
		break;

	case 2:	//�����A�^�b�N
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 1;		//�A�j���[�V����0�i�ړ�			
				if(pC->OldAniType != 1)	//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
				{
					pC->Cnt = 50;		//���̍s�������鎞��
					pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;	//�J�E���^���O��
				}
				pC->AniTurn = 3;				//���[�v���Ė߂�G
			}
			if(pC->AniNum > 2)	pC->x -= 7;					//�L���������Ɉړ�
			pC->muki = 0;			//�������P�ɂ��āA������������
		}
		break;

	case 3:	//���E�W�����v
		if(pA->Change && pC->Land == 1)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;			//�W�����vUP�A�j���[�V����
			if(pC->OldAniType == 0)		//�n�ʂɑ��������Ă��邩����
			{
				pC->AniNum = 0;				//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;			//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
				pC->U = -15;				//�������鑬�x������U��15.0�ɂ���
			}
			pC->AniTurn = 3;			//�A�j���[�V�������Ă��ǂ�G
		
			pC->muki = 1;			//�E�Ɍ���
		}
		if(!pC->Land && pC->AniType == 2)
		{
			pC->Cnt = 2;	//�����Ă���Ԃ�Cnt���Q�ɂ��āA�A�N�V�����ύX�ł��Ȃ�����i�P���Ɓ[�P����ĂO�ɂȂ�̂Ń_��
			pC->x += 6;		//�E�Ɉړ�
		}

		break;
	case 4:	//�����W�����v
		if(pA->Change && pC->Land == 1)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;		//�W�����vUP�A�j���[�V����
			if(pC->OldAniType == 0)				//�n�ʂɑ��������Ă��邩����
			{
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
				pC->U = -15;				//�������鑬�x������U��15.0�ɂ���
			}
			pC->AniTurn = 3;		//�A�j���[�V�������Ă��ǂ�G
			pC->muki = 0;			//���Ɍ���
		}
		if(!pC->Land && pC->AniType == 2)	
		{
			pC->Cnt = 2;	//�����Ă���Ԃ�Cnt���Q�ɂ��āA�A�N�V�����ύX�ł��Ȃ�����i�P���Ɓ[�P����ĂO�ɂȂ�̂Ń_��
			pC->x -= 6;		//���Ɉړ�
		}

		break;

	case 5:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 15;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->muki)	pC->x -=3;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=3;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;

	case 6:	//�����C
		if(pA->Change && pC->Land == 1 )	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 4;
			if(pC->OldAniType != 4)
			{
				pC->Cnt = 40;			//���̃A�N�V�������T�O�t���[��
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
			pC->AniTurn = 0;
		}
		if(pC->Cnt == 15)
		{
			if(pC->muki == 0)	//�������Ȃ�	
			{
				ShotFire(pC->x+(pC->w>>1)-16,pC->y+32,0,20,1);	//�e�̔���
				DS_Play(6,FALSE);	//���ʉ���炷
			}else				//����������Ȃ��Ȃ�
			{
				ShotFire(pC->x+(pC->w>>1)-16,pC->y+32,1,20,1);		//�e�̔���
				DS_Play(5,FALSE);	//���ʉ���炷
			}
		}
		break;
	}
}
//////�i�������j//////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_9 (CHR_DATA *pC,ANIME_DATA *pA)	//�@�\�F�G�l�~�[�X�̍s�����܂Ƃ߂��֐�
//�������P�F�G�l�~�[�̃L�����f�[�^
//�������Q�F�G�l�~�[�̃A�j���[�V�����f�[�^
{
	int i;

	if(pC->HitD)	//�_���[�W����������
	{
		pC->ActNum = 1;	
	}else
	{
		pC->ActNum = 0;	//�ʏ�ǂ���ړ��A�N�V����
	}


	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
			{
				pC->AniType = 0;		//�A�j���[�V����0�i�ړ�			
				pC->AniTurn = 0;		//���[�v���Ė߂�G
			}

			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))	//�v���C���[�̍��W�����Ɉړ�������ς���
				pC->muki = 0;	
			else
				pC->muki = 1;

			if(pC->muki)
				pC->x += 3;				//�E�Ɉړ�
			else
				pC->x -= 3;				//���Ɉړ�
		}
		break;
	case 1:	//���_���[�W���U��
		pC->AniType = 1;
		if(pC->OldAniType != 1)
		{
			pC->Cnt = 35;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->Cnt == 0)	
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
			for(i = 0;i < 6;i++)
				ShotFire(pC->x+(pC->w>>1)-6,pC->y+12,0,21,1);	//�e�̔���
			DS_Play(6,FALSE);	//���ʉ���炷
		}
		break;
	}
}
//////�i�I�j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_10(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
		if(pC->ActNum == 0)	//���C�̃A�N�V�����Ȃ�
		{
			if(Plr.x+(Plr.w>>1) < pC->x+(pC->w>>1))
				pC->muki = 0;			//��������
			else
				pC->muki = 1;			//�E������
		}

	}
	if(pC->HitD)
		pC->ActNum = 2;	//�_���[�W�A�N�V����

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ړ�
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;		//�A�j���[�V����1�i�ړ�			
			if(pC->OldAniType != 0)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
			{
				pC->Cnt = 50;		//���̍s�������鎞�Ԃ�ݒ�
				pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;	//�J�E���^���O��
			}
			pC->AniTurn = 0;

			if(pC->muki)	pC->x += 4;		//�L�������ړ�
			else			pC->x -= 4;					

		}
		break;
	case 1:	//���U��
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 1;
			if(pC->OldAniType != 1)
			{
				pC->Cnt = 25;			//���̃A�N�V�����̍s������
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
		}
		if(pC->Cnt == 5)	//���̃A�N�V�����̃J�E���g���Ԃ��̂���T�̎��Ȃ�
		{
			if(pC->muki == 0)	//�������Ȃ�
			{
				ShotFire(pC->x+(pC->w>>1),pC->y+60,0,22,1);	//�e�̔���
				DS_Play( 3, FALSE );			//���ʉ���炷
			}else				//����������Ȃ��Ȃ�
			{
				ShotFire(pC->x+(pC->w>>1),pC->y+60,1,22,1);		//�e�̔���
				DS_Play( 3, FALSE );			//���ʉ���炷
			}
		}
		break;
	case 2:	//���_���[�W
		pC->AniType = 2;
		if(pC->OldAniType != 2)
		{
			pC->Cnt = 30;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -4;
		}
		if(pC->muki)	pC->x -=2;	//�E�����Ȃ獶�ɔ��
		else			pC->x +=2;	//�������Ȃ�E�ɔ��

		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;


	}
}
//////�i�c�{�j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_11(CHR_DATA *pC,ANIME_DATA *pA)
{
	pC->muki = 0;	//�c�{�͏�Ɍ���������
	pC->Hp = 5 - pC->AniType;	//�c�{��HP������Ȃ��A�U�������񐔂ŉ�
	
	if(pC->Cnt == 0)	//�A�N�V�����J�E���g���Ԃ��O�Ȃ�
	{
		if(pC->HitD)	//�_���[�W�t���O��TRUE�Ȃ�
		{
			pC->AniType++;	//�A�j���[�V������ύX(�_���[�W���󂯂邲�Ƃɕω�
			pC->Cnt = 20;	//�Q�O�J�E���g�̊Ԃ͔�����s��Ȃ�
		}
	}
	if(pC->AniType > 4)	//�Ō�̎�ނ̃A�j�����I�������
	{
		pC->Hp = 0;
		pC->Son = FALSE;	//�c�{����
		for(int i = 0;i < 20;i++)	//�G�t�F�N�g�\��
			EFON(EF,pC->x+(rand()%pC->w),pC->y+(rand()%pC->h),12);

		switch(rand()%3)	//�����_���Ō��̔j�Ђ�HPUP���o��
		{
		case 0:
			for(i = 0;i < 50 ;i++)	//���ʃG�l�~�[�̎�ނ�MAXHP�̐����������o��������
				ShotFire(pC->x+(rand()%pC->w)-4,pC->y+(rand()%pC->h)-4,0,17,1);
			break;
		case 1:
			for (i = 0;i < 50 ;i++)	//���̔j�Ђ��o��
				ShotFire(pC->x+(rand()%pC->w)-4,pC->y+(rand()%pC->h)-4,0,19,2);
			break;
		case 2:
			if(pC->Land == 1)
				for(i = 0;i < 6;i++)
					ShotFire(pC->x+(rand()%pC->w)-16,pC->y+pC->h-32,0,7,1);
			break;
		}

	}
	pC->HitD = 0;	//�_���[�W�t���O��FALSE��
}
//////�i�����j////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy_12(CHR_DATA *pC,ANIME_DATA *pA)
{
	if(pC->Cnt <= 0)	//�J�E���g���Ԃ��O�Ȃ�
	{
		pC->ActNum = pC->Act[rand()%4];	//�G�̍s�����܂��̓����_���ň���
	}
	if(pC->HitD)
		pC->ActNum = 3;	//�_���[�W�A�N�V����

	switch(pC->ActNum)	//ActNum�����ɏ�������	
	{
	case 0:	//���ҋ@
		if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
		{
			pC->AniType = 0;		//�A�j���[�V����1�i�ړ�			
			if(pC->OldAniType != 0)		//�O��̃A�j���[�V�����̎�ނ��P�ȊO�Ȃ�
			{
				pC->Cnt = 40;		//���̍s�������鎞�Ԃ�ݒ�
				pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;	//�J�E���^���O��
			}
			pC->AniTurn = 0;
		}
		break;
	case 1:	//������
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 1;
			if(pC->OldAniType != 1)
			{
				pC->Cnt = 14;			//���̃A�N�V�����̍s������
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
		}
		break;
	case 2:	//���f��
		if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
		{
			pC->AniType = 2;
			if(pC->OldAniType != 2)
			{
				pC->Cnt = 22;			//���̃A�N�V�����̍s������
				pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
				pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
			}
		}
		if(pC->Cnt == 10)
		{
			for(int i = 0;i < 3;i++)
				ShotFire(pC->x+(pC->w>>1),pC->y+60+(i<<2),0,23,1);	//�e�̔���
			DS_Play( 3, FALSE );			//���ʉ���炷
		}
		break;
	case 3:	//���_���[�W
		pC->AniType = 3;
		if(pC->OldAniType != 3)
		{
			pC->Cnt = 30;	//�_���[�W�A�N�V��������
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
		}
		if(pC->Cnt == 0)	//�_���[�W�A�j���I�����Ȃ�
		{
			pC->HitD = 0;		//�_���[�W�t���O���O��
			pC->AniType = 0;	//�I����ɕς���A�j�����w��
		}
		break;
	}
}