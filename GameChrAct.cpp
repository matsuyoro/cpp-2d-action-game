#include <windows.h>

#include "GameStruct.h"
#include "Extern.h"
#include "DirectSound.h"

#include "GameCheckProc.h"
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void PlrAction(CHR_DATA *pC,ANIME_DATA *pA)		//�@�\�F�L�����N�^�[�𓮂����֐�
//�������P�FCHR_DATA�^�\����
//�������Q�FANIME_DATA�^�\���́i���ݕ\�����̃A�j�����ύX�\�����ׂ�̕K�v
{
	int i;

	//���ҋ@
	if(CmdNum[0] == 0 && Btn1 == 0)			//�����������ĂȂ��ꍇ
	{
		if(pA->Change && pC->Land == 1 && pC->OldAniType != 0)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������ && ���̃A�j���[�V�����ɐ؂�ւ�����΂���Ȃ�
		{
			pC->AniType = 0;				//�A�j���[�V�����O
			pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
			pC->AniTimeNow = 0;
			pC->AniTurn = 0;				//���[�v���Ė߂�G
		}
	}

	if((!Swd.Son || Swd.HitA || Nage))	//�����Ȃ��A�h�����ĂȂ��A�����Ȃ��ĂȂ�������i�����o�����Ă��鎞�̓W�����v�A�U���A�ړ��̓�����ł��Ȃ�����j
	{
		//�����Ⴊ�ݍU���I����
		if((pC->OldAniType == 10 && pC->AniType != 10)
		|| (pC->OldAniType == 11 && pC->AniType != 11)	//�O��̃A�j�������Ⴊ�ݍU����������			
		|| (pC->OldAniType == 17 && pC->AniType != 17)	//�O��̃A�j�������Ⴊ�݌�������������
		)	
		{
			pC->AniType = 3;			//���Ⴊ�݂̃A�j���ɖ߂�
			pC->AniNum = 9;				//�X�R�}�ڂ���n�܂�
			pC->AniTimeNow = 0;			//�A�j���\���J�E���g���O��
			pC->AniTurn = 9;			//���[�v���Ė߂�G�X
		}else if(CmdNum[0] == 8 || CmdNum[0] == 9 || CmdNum[0] == 12)	//�����Ⴊ��	//�\���L�[�̉��������ꂽ��
		//�����Ⴊ��	//�\���L�[�̉��������ꂽ��
		{	
			if(pA->Change && pC->Land == 1)//���݂̊G���A���̃A�j���[�V�����ɕύX�\���@�� ���n���Ă��邩����
			{
				pC->AniType = 3;		//�A�j���[�V�����R�i���Ⴊ��
				if(CmdCnt[0] == 1)		//�\���L�[�̉����������΂���Ȃ�
				{
					pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;		//�J�E���g���Ԃ��O��
				}
				pC->AniTurn = 9;		//���[�v���Ė߂�G
			}
		}

		//���W�����v�㏸
		if(CmdNum[0] == 2 || CmdNum[0] == 3 || CmdNum[0] == 6 )	//������A��A�E��@�������ꂽ��
		{
			if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
			{
				pC->AniType = 6;		//�W�����vUP�A�j���[�V����
				if(pC->Land == 1)				//�n�ʂɑ��������Ă��邩����
				{
					pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
					pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
					pC->U = -15.0f;				//�������鑬�x������U��15.0�ɂ���
					EFON(EF,pC->x+(pC->w>>1),pC->y+pC->h-18,7+(rand()%2));		//���ڂ�������Ă�G�t�F�N�g
					DS_Play(9,FALSE);	//���ʉ���炷
				}
				pC->AniTurn = 7;		//�A�j���[�V�������Ă��ǂ�G
			}
		}
		//���W�����v�㏸2
		if((CmdNum[1] == 8 || CmdNum[2] == 8) && (CmdNum[0] == 2 || CmdNum[0] == 3 || CmdNum[0] == 6) )	//������A��A�E��@�������ꂽ��
		{
			if(pA->Change)	//���ݎ��s���̃A�j�����ύX�\��		
			{
				pC->AniType = 6;		//�W�����vUP�A�j���[�V����
				if(pC->Land == 1)				//�n�ʂɑ��������Ă��邩����
				{
					pC->AniNum = 0;			//�A�j���[�V�����̂O�R�}�ڂɂ���
					pC->AniTimeNow = 0;		//�A�j���[�V�����̎��ԃJ�E���g���O�ɂ���
					pC->U = -23.0f;				//�������鑬�x������U��15.0�ɂ���
					DS_Play(9,FALSE);	//���ʉ���炷
					for(i = 0;i < 10;i++)
						EFON(EF,pC->x+(rand()%pC->w),pC->y+pC->h-18,7+(rand()%2));		//���ڂ�������Ă�G�t�F�N�g
				}
				pC->AniTurn = 7;		//�A�j���[�V�������Ă��ǂ�G
				

			}
		}
		//�����ړ�
		if(CmdNum[0] == 1 || CmdNum[0] == 3)	//�\���L�[�̍����A�������������		
		{		
			if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
			{
		//���_�b�V��
				//�R�}���h����͂�����(���E���j
				if((CmdNum[2] == 1 && CmdCnt[2] <= 10
					&& CmdNum[1] != 1 && CmdCnt[1] <= 10 
					&& (CmdNum[0] == 1 || CmdNum[0] == 3))	//���E�����͂����� OR
				|| (pC->OldAniType == 2 && CmdNum[0] == 3))	//�O�񂪃_�b�V���A�j���[�V�����ō������������
				{
					pC->AniType = 2;	//�_�b�V���A�j���[�V����
					pC->AniTurn = 8;	//���[�v���Ė߂�R�}
					if(pC->x > 200-(pC->w>>1))	//�L����X���W��200���傫�����
					{	
						pC->x -= 7;					//�L���������Ɉړ�
					}else						//�L����X���W��200�ȉ��Ȃ�
					{
						if(!(WMoveX <= 0))			//���[�܂ł������牽�����Ȃ�
							WorldX = -7;					//WordlX���|�P(Map���E�ɃX�N���[��
					}
					pC->muki = 1;			//�������P�ɂ��āA������������
				}else	//�_�b�V���̃R�}���h�����͂���ĂȂ�������
		//������
				{
					if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
					{
						pC->AniType = 1;		//�A�j���[�V�����P�i�ړ�			
						if(CmdCnt[0] == 1)		//���������n�߂Ȃ�i�{�^����������1�t���[���ځj
						{
							pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
							pC->AniTimeNow = 0;	//�J�E���^���O��
						}
						pC->AniTurn = 5;				//���[�v���Ė߂�G
					}
					if(pC->x > 200-(pC->w>>1))	//�L����X���W��200���傫�����
					{	
						pC->x -= 3;					//�L���������Ɉړ�
					}else							//�L����X���W��200�ȉ��Ȃ�
					{
						if(!(WMoveX <= 0))			//���[�܂ł������牽�����Ȃ�
							WorldX = -3;					//WordlX���|�P(Map���E�ɃX�N���[��
					}
					pC->muki = 1;			//�������P�ɂ��āA������������
				}
			}
		}
		//���E�ړ�
		if(CmdNum[0] ==  4 || CmdNum[0] == 6 )				//�\���L�[�̉E���E�����������
		{
			if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
			{
		//���_�b�V��
				//�R�}���h���͂�����i���E���j
				if(	((CmdNum[2] == 4 && CmdCnt[2] <= 10)
					&& (CmdNum[1] != 4 && CmdCnt[1] <= 10) 
					&& (CmdNum[0] == 4 || CmdNum[0] == 6))	//���E�����͂�����@OR
				|| (pC->OldAniType == 2 && CmdNum[0] == 6))	//�O�񂪃_�b�V���A�j���[�V�����ŉE�����������
				{
					pC->AniType = 2;	//�_�b�V���A�j���[�V����
					pC->AniTurn = 8;	//���[�v���Ė߂��R�}
					if(pC->x < 400-(pC->w>>1))	//�L������x���W400��菬�������
					{
						pC->x += 7;					//�L����x���W�{�ړ����x
					}else						//�����𖞂����ĂȂ���΁i�L������x���W400�ȏ�Ȃ�
					{
						if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//�E�[�܂ł������牽�����Ȃ�
							WorldX = 7;					//�X�N���[���ʂ�ݒ�
					}
					pC->muki = 0;			//�������O�ɂ��āA�E����������
				}else
		//������
				{
					if(pC->Land == 1)	//�n�ʂɑ��������Ă���Ȃ�
					{
						pC->AniType = 1;	//�A�j���[�V�����P�i�ړ�
						if(CmdCnt[0] == 1)		//�����n�߂Ȃ�i�E��������1�t���[���ڂȂ�
						{
							pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
							pC->AniTimeNow = 0;	//�J�E���g���Ԃ��O��
						}
						pC->AniTurn = 5;		//���[�v���Ė߂�G
					}
					if(pC->x < 400-(pC->w>>1))	//�L����X���W��400��菬�������
					{
						pC->x += 3;					//�L�������E�Ɉړ�
					}else
					{
						if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//�E�[�܂ł������牽�����Ȃ�
							WorldX = 3;				//WorldX���{�P
					}
					pC->muki = 0;			//�������O�ɂ��āA�E����������
				}
			}
		}

	}



	//���W�����v���~
	if(pA->Change && pC->Land == 0 && pC->U > 0. && pC->AniType!=2)	//�n�ʂɑ��������Ă��Ȃ���ԂŁA���~���ŁAAniType���Q�ȊO�Ȃ�
	{
		pC->AniType = 7;	//�W�����v���~�A�j���[�V����
		if(pC->OldAniType != 7)	//�O��̃A�j���[�V�����̎�ނ��W�����v���~����Ȃ�������
		{
			pC->AniNum = 0;			//�A�j���[�V������0�R�}�ڂɖ߂�
			pC->AniTimeNow = 0;		//�A�j���[�V�����\���J�E���g���Ԃ��O�ɖ߂�
		}
		pC->AniTurn = 1;		//���[�v���Ė߂�A�j���[�V�����̊G
	}

	if(!Swd.Son)	//�������݂��Ȃ��Ȃ�
	{
		//�����a��i�a�{�^����Z������
		if(!(Btn1 & (1<<1)) && BtnCnt < 3 && (Btn2 & (1<<1)))	//����(��)�ŁA���O��(��)��������
		{
			if(pC->AniType != 3)	//���Ⴊ�݃A�j���[�V�����ȊO��������
			{
				if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
				{
					pC->AniType = 4;				//�A�j���[�V����4
					pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;				//�J�E���g���Ԃ��O��
					pC->AniTurn = 0;				//���[�v���Ė߂�G
					DS_Play( 0, FALSE );			//���ʉ���炷
				}
			}else
			{
				//�����Ⴊ�݉��a��
				if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����̕ύX�\������
				{
					pC->AniType = 11;		//���Ⴊ�݉��a��A�j���[�V����
					pC->AniNum = 0;
					pC->AniTimeNow = 0;
					pC->AniTurn = 0;
					DS_Play( 0, FALSE );	//���ʉ���炷
				}
			}
		}
		
		//���c�a��i�a�{�^���𒷂�����
		if((Btn1 & (1<<1)) && BtnCnt >= 3)	//����(��)�ŁA���O��(��)��������
		{	
			if(pC->AniType != 3)	//���Ⴊ�݃A�j���[�V�����ȊO��������
			{
				if(pA->Change)//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
				{
					pC->AniType = 5;				//�A�j���[�V����5
					pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;				//�J�E���g���Ԃ��O��
					pC->AniTurn = 0;				//���[�v���Ė߂�G
					DS_Play( 1, FALSE );			//���ʉ���炷
				}
			}else	//���Ⴊ�݃A�j���[�V��������������
			{
				//�����Ⴊ�ݏc�a��
				if(pA->Change)	//���݂̊G���A���̃A�j���[�V�����ɕύX�\������
				{
					pC->AniType = 10;		//���Ⴊ�ݎa��A�j���[�V����
					pC->AniNum = 0;			//�A�j���[�V�����ŏ�����
					pC->AniTimeNow = 0;		//�A�j���[�V�����J�E���g���O��
					pC->AniTurn = 0;		//���[�v���Ė߂�G
					DS_Play( 1, FALSE );			//���ʉ���炷
				}
			}
		}
		//���W�����v�c�U��
		if(pA->Change && !pC->Land)	//�n�ʂɑ��������Ă��Ȃ���ԂŁA���~���ŁAAniType���Q�ȊO�Ȃ�
		{
			if((Btn1 & (1<<1)) && BtnCnt >= 3)	//����(��)�ŁA���O��(��)��������
			{	
					pC->AniType = 12;				//�A�j���[�V����5
					pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;				//�J�E���g���Ԃ��O��
					pC->AniTurn = 0;				//���[�v���Ė߂�G
					DS_Play( 1, FALSE );			//���ʉ���炷
			}
		}
		//���W�����v���U��
		if(pA->Change && !pC->Land)	//�n�ʂɑ��������Ă��Ȃ���ԂŁA���~���ŁAAniType���Q�ȊO�Ȃ�
		{
			if(!(Btn1 & (1<<1)) && BtnCnt < 3 && (Btn2 & (1<<1)))	//����(��)�ŁA���O��(��)��������
			{	
					pC->AniType = 13;				//�A�j���[�V����5
					pC->AniNum = 0;					//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;				//�J�E���g���Ԃ��O��
					pC->AniTurn = 0;				//���[�v���Ė߂�G
					DS_Play( 0, FALSE );			//���ʉ���炷
			}
		}

		//���㓊��
		if(pA->Change && pC->Land == 1)	//�A�j����ύX�\�Œn�ʂɑ��������Ă�����
		{
			if((CmdNum[0] == 0) && (Btn1 & 1))	//����(��)�ŁA���O��(��)��������
			{
				pC->AniType = 14;			//���㓊���A�j���[�V����
				pC->AniNum = 0;				//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;			//�J�E���g���Ԃ�0��
				pC->AniTurn = 0;			//���[�v���Ė߂�G
			}
		}
		//�����E����
		if(pA->Change)	//�A�j����ύX�\�Œn�ʂɑ��������Ă�����
		{
			if(((CmdNum[0]==4) || (CmdNum[0]==1)) && (Btn1 & 1))	//�������Ƃ`�{�^���������Ă�����
			{
				pC->AniType = 15;			//�����E�����A�j���[�V����
				pC->AniNum = 0;				//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;			//�J�E���g���Ԃ�0��
				pC->AniTurn = 0;			//���[�v���Ė߂�G
			}
		}
		//���W�����v������
		if(pA->Change && !pC->Land)	//�A�j���ύX�\�Œn�ʂɑ��������Ă��Ȃ�������
		{
			if((CmdNum[0]==8) && (Btn1 & 1))	//���Ƃ`�{�^������������
			{
				pC->AniType = 16;		//���W�����v�������A�j���[�V����
				pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
				pC->AniTurn = 0;		//���[�v���Ė߂�G
			}
		}
		//�����Ⴊ�ݓ���
		if(pA->Change && pC->Land == 1)	//�A�j���ύX�\�Œn�ʂɑ��������Ă�����
		{
			if(pC->AniType == 3 && Btn1 & 1)	//���Ⴊ�݃A�j���ł`�{�^������������
			{
				pC->AniType = 17;	//�����Ⴊ�݂Ȃ��A�j���[�V����
				pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
				pC->AniTurn = 0;		//���[�v���Ė߂�G
			}
		}

		
	}

	//��������
	if(pC->AniType != 5 && pC->AniType != 10
	&& pC->AniType != 4 && pC->AniType != 11
	&& pC->AniType != 12 && pC->AniType != 13	//�U���A�j��������Ȃ��Ȃ�
	&& pC->AniType != 18 && pC->AniType != 19 && pC->AniType != 20	//�o���A�A���z���AHP����ւ��A�j������Ȃ��Ȃ�
	&& !(pC->AniType == 15 && pC->AniNum < 4)	//�����E�����A�j���̂S���ڂ̊G���O�̊G����Ȃ��Ȃ�
	&& !(pC->AniType == 16 && pC->AniNum < 5)	//���W�����v�������A�j���̂T���ڂ̊G���O�̊G����Ȃ��Ȃ�
	&& !(pC->AniType == 17 && pC->AniNum < 4)	//�����Ⴊ�ݓ����A�j���̂S���ڂ̊G���O�̊G����Ȃ��Ȃ�
	&& Btn1 & 1)					//�`�{�^���������Ă���Ȃ�
	{
		if(!Swd.Son)	//�������݂��Ȃ�������
		{
			Swd.HitA = FALSE;	//�o�����͌��͎h�����ĂȂ�
			
			Nage = 0;									//�����Ȃ��Ă��邩�ǂ���������Nage��0�ɂ��ǂ��Ă���
			Swd.AniType = 4;							//�����o���A�j���[�V����������
			Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
			Swd.y = pC->y - Swd.h;						


			if(pC->AniType == 15 && !pC->muki)	//�������ɂȂ�����
			{
				Nage = 2;							//���ɂȂ�����Nage���Q��
				Swd.AniType = 2;					//�������ɔ�ԃA�j���[�V����
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
				Swd.y = pC->y - 10;						

			}
			if(pC->AniType == 15 && pC->muki)	//�����E�ɂȂ�����
			{
				Nage = 1;							//�E�ɂȂ�����Nage���P��
				Swd.AniType = 3;					//�����E�ɔ�ԃA�j���[�V����
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
				Swd.y = pC->y - 10;						

			}
			if(pC->AniType == 16)	//�������ɂȂ�����
			{
				Nage = 3;							//���ɂȂ�����Nage���R��
				Swd.AniType = 1;					//�������ɔ�ԃA�j���[�V����
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
				Swd.y = pC->y +30;						

			}
			if(pC->AniType == 17 && pC->muki)	//�����Ⴊ�݉E����������
			{
				Nage = 1;							//�������Ⴊ�ݓ���������Nage��3��
				Swd.AniType = 0;					//�������ɔ�ԃA�j���[�V����
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
				Swd.y = pC->y + 20;
			}
			if(pC->AniType == 17 && !pC->muki)	//�����Ⴊ�݉E����������
			{
				Nage = 2;							//�������Ⴊ�݉E�Ȃ�������Nage��2��
				Swd.AniType = 2;					//�����E�ɔ�ԃA�j���[�V����
				Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
				Swd.y = pC->y + 20;
			}


			//Swd.x = pC->x + (pC->w>>1) - (Swd.w>>1);	//���o���ʒu
			//Swd.y = pC->y - Swd.h;						
			Swd.Hit.w = 22;										//�����蔻��̕�
			Swd.Hit.h = 90;										//�����蔻��̍���
			Swd.Hit.x = pC->x + (pC->w>>1) - (Swd.Hit.w>>1);	//�����蔻�荶��X���W
			Swd.Hit.y = pC->y - (Swd.Hit.h<<1);	//�����蔻�荶��Y���W

			Swd.AniNum = 0;
			Swd.AniTimeNow = 0;

		}
		Swd.Son = TRUE;	//���̑��݂��s�q�t�d��
	}else if(!Swd.HitA && !Nage)	//��̏����𖞂����ĂȂ��āA�����ǂɂ������ĂȂ��A�����Ȃ��ĂȂ�������
	{
		Swd.Son = FALSE;	//���݂�FALSE�ɂ���
	}
	if(Swd.Son && !Nage && Swd.AniNum == 1)	//�����쒆�͌���HP������
	{
		if(Swd.Hp > 0)	Swd.Hp--;
	}

	//��������
	if(Swd.Son && (Swd.HitA || Nage))	//�������݂��A�ǂɎh�����Ă����邩���𓊂��Ă�����
	{
		if(!(Btn1 & (1<<1)) && (Btn2 & (1<<1)) && Swd.AniType != 5)	//����(��)�ŁA���O��(��)��������
		{
			EFON(EF,Swd.x+(Swd.w>>1),Swd.y+(Swd.h>>1),0);		//���̈ʒu�ɔ����G�t�F�N�g���o��
			Swd.AniType = 5;	//����������A�j���[�V����
			Swd.AniNum = 0;
			Swd.AniTimeNow = 0;
		}
		if(Swd.AniType == 5 && Swd.AniNum > 2)	//���̏�����A�j���[�V������2���ڈȍ~�Ȃ�
		{
			//���̔j�Ђ��΂�
			for(i = 0;i < Swd.Hp;i++)	//����Hp���j�Ђ��΂�
			{
				ShotFire(Swd.x+(rand()%Swd.w),Swd.y+(rand()%Swd.h),0,19,2);
				Swd.Hp--;
			}

			if(Swd.Land == 1)	//�������̕��Ɏh�����Ă�����΂�����
			{
				for(i = 0;i < 6;i++)
					ShotFire(Swd.x+(rand()%Swd.w),Swd.y+48,0,7,2);	//�e�̔��ˁi�n�ʂɔz�u����e
			}

			Swd.Son = FALSE;	//���̑��݂�FLASE��
			Swd.HitA = FALSE;	//���̂��ǂɎh�����Ă��邩�̃t���O��FALSE�ɖ߂�
		}
	}

	//���o���A	(�e�𒵂˕Ԃ�
	if(!Swd.Son && Swd.Hp > 0 && pC->Land == 1 && (CmdGet == 8 || CmdGet == 7) 
	&&(pA->Change || (pC->AniType == 18 && (Btn1 & (1<<1))))	)	//�A�j���ύX�\�Œn�ʂɑ��������Ă�����
	{
		pC->AniType = 18;			//
		if(pC->OldAniType != 18)	//
		{
			pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
			pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
		}
		pC->AniTurn = 10;			//���[�v���Ė߂�G
	}
	else if(pC->AniType == 18 && 
	(	((Btn2 & (1<<1)) && !(Btn1 & (1<<1)))	
	|| Swd.Hp <= 1	)	)
	{	//�o���A�A�j���I����ɑҋ@�A�j���ɕύX
		pC->AniType = 0;
		pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
		pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
		pC->AniTurn = 0;		//���[�v���Ė߂�G���߂��Ă���
	}
	if(pC->AniType == 18 && pC->AniNum == 10)	//���̃A�j���[�V�������̓v���C���[HP������HP�ɕς���
	{
		Swd.Hp --;
	}
	//�����z��
	if(!Swd.Son && pC->Land == 1 && (CmdGet == 6 || CmdGet == 5) && pA->Change && (Btn1 & 1)	)	//�A�j���ύX�\�Œn�ʂɑ��������Ă�����
	{
		pC->AniType = 19;			
		if(pC->OldAniType != 19)
		{
			pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
			pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��

		}
		pC->AniTurn = 0;			//���[�v���Ė߂�G
	}else if(pC->AniType == 19 && (Btn2 & 1) && !(Btn1 & 1)	)
	{	//���z���A�j���I����ɑҋ@�A�j���ɕύX
		pC->AniType = 0;
		pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
		pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
		pC->AniTurn = 0;		//���[�v���Ė߂�G���߂��Ă���
	}

	//���v���C���[�ƌ���HP����ւ�
	if(!Swd.Son && pC->Land == 1 && (CmdGet == 3 || CmdGet == 4) && pA->Change && (Btn1 & 1)	)	//�A�j���ύX�\�Œn�ʂɑ��������Ă�����
	{
		pC->AniType = 20;			//
		if(pC->OldAniType != 20)	//
		{
			pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
			pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
		}
		pC->AniTurn = 0;			//���[�v���Ė߂�G
	}else if(pC->AniType == 20 && (Btn2 & 1) && !(Btn1 & 1)	)
	{	//�A�j���I����ɑҋ@�A�j���ɕύX
		pC->AniType = 0;
		pC->AniNum = 0;			//�A�j���[�V�����̍ŏ�����
		pC->AniTimeNow = 0;		//�J�E���g���Ԃ�0��
		pC->AniTurn = 0;		//���[�v���Ė߂�G���߂��Ă���
	}

	if(pC->AniType == 20 && pC->Hp > 2 && Swd.Hp < Swd.MaxHp)	//���̃A�j���[�V�������̓v���C���[HP������HP�ɕς���
	{
		pC->Hp -= 2;
		Swd.Hp ++;
		EFON(EF,pC->x+(rand()%pC->w),pC->y+(rand()%pC->h),11);	//�e�̏�����ʒu�ɒe�q�b�g�G�t�F�N�g��ON
	}

	//���_���[�W��������
	if(pC->HitD)	//�_���[�W��������t���O���O�ȊO�ɂȂ�����
	{
		if(pC->AniType != 9)	//�A�j�����X����Ȃ�������
		{
			pC->AniNum = 0;
			pC->AniTimeNow = 0;
			pC->U = -6;
		}
		pC->AniType = 9;	//�_���[�W��������A�j���[�V����
		pC->AniTurn = 0;

		if(pC->muki)
		{
			if(pC->x < 400-(pC->w>>1))	//�L����X���W��400��菬�������
			{
				pC->x += 4;					//�L�������E�Ɉړ�
			}else
			{
				if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//�E�[�܂ł������牽�����Ȃ�
					WorldX = 4;				//WorldX���{�P
			}
		}else
		{
			if(pC->x > 200-(pC->w>>1))	//�L����X���W��200���傫�����
			{	
				pC->x -= 4;					//�L���������Ɉړ�
			}else							//�L����X���W��200�ȉ��Ȃ�
			{
				if(!(WMoveX <= 0))			//���[�܂ł������牽�����Ȃ�
					WorldX = -4;					//WordlX���|�P(Map���E�ɃX�N���[��
			}
		}

		if(pC->AniNum == 6)		//�_���[�W�A�j���[�V�������I��鎞
		{
			pC->HitD = 0;	//�A�j����6�ԂȂ�A�_���[�W�t���O���O�ɖ߂�
			Muteki = 30;	//���G���Ԃ�ݒ�
		}
	}


	//�������
	if(pC->Hp < 1)		//Hp���P��肿������������
	{
		pC->AniType = 8;	//�����A�j���[�V����

		pC->Son = FALSE;	//�L�����̑��݂�FALSE��

		if(pC->OldAniType != 8)	//�O��̃A�j���[�V�������W�ȊO�Ȃ�
		{
			pC->AniNum = 0;		//�A�j���[�V�����̍ŏ�����
			pC->AniTimeNow = 0;	//�A�j���[�V�����\���J�E���g���Ԃ��O��
		}
		pC->AniTurn = 16;		//���[�v���Ė߂�G
	}

	/*
	//�����Ⴊ�ݎa��̒e
	if(pC->AniType == 10 && pC->AniNum > 2)
	{
		if(pC->muki == 0)	//�������Ȃ�	
			ShotFire(pC->x +(pC->AniNum<<4),pC->y+pC->h-48 -(pC->AniNum<<2),1,6,2);	//�e�̔���
			//ShotFire(pC->x+pC->w,pC->y+32,1,16,2);
		else				//����������Ȃ��Ȃ�
			ShotFire(pC->x -(pC->AniNum<<4),pC->y+pC->h-48-(pC->AniNum<<2),0,6,2);		//�e�̔���
			//ShotFire(pC->x-16,pC->y+32,0,16,2);

	}
	*/
	//���c�a��̒e
	if(pC->AniType == 5 && pC->AniNum == 4)
	{
		if(pC->muki == 0)	//�������Ȃ�	
			//ShotFire(pC->x +(pC->AniNum<<4),pC->y+pC->h-48 -(pC->AniNum<<2),1,6,2);	//�e�̔���
			for(i = 0;i < 3;i++)
				ShotFire(pC->x+pC->w+16,pC->y+(i * 16),1,16,2);
		else				//����������Ȃ��Ȃ�
			//ShotFire(pC->x -(pC->AniNum<<4),pC->y+pC->h-48-(pC->AniNum<<2),0,6,2);		//�e�̔���
			for(i = 0;i< 3;i++)
				ShotFire(pC->x-32,pC->y+(i*16),0,16,2);

	}


	//���ړ����̃G�t�F�N�g	
	if(Swd.Son			
		&& !Swd.HitA		//�����h�����ĂȂ�
		&& Swd.AniType != 4	//�����o���A�j���[�V��������Ȃ�
		&& (CmdNum[0] == 1 || CmdNum[0] == 2 || CmdNum[0] == 4 || CmdNum[0] == 8 || Nage)	//�����Ȃ��Ă��邩�@OR �\���L�[�������Ă��邩 
		)	//�������݂��āA�\���L�[����͒��ŁA�����h�����ĂȂ�������
	{
		for(i = 0;i < 3;i++)
			EFON(EF,Swd.x+(Swd.w>>1)+(rand()%32-16),Swd.y+(Swd.h>>1)+(rand()%32-16),6);	//�G�t�F�N�g�\��
		//ShotFire(Swd.x+(Swd.w>>1)-24,Swd.y+(Swd.h>>1)-24,1,6,2);	//�e�̔���
	}

	//���ڂ���̃G�t�F�N�g
	if(pC->Land == 1 && pC->AniType == 2 && (pC->MoveChkX != pC->x || WorldX))	//�v���C���[�����n���Ń_�b�V���A�j���ňړ����Ȃ�
		EFON(EF,pC->x+(pC->w>>1)+(pC->muki*32-16),pC->y+pC->h-18,7+(rand()%2));		//���ڂ�������Ă�G�t�F�N�g



	//���̂��̊֐������s����Ƃ��ɕK�v�ȃf�[�^��ۑ�
	pC->OldAniType = pC->AniType;	//�O��̃A�j���[�V�����̎�ނ�ۑ�
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void SwdAction(CHR_DATA *pC,ANIME_DATA *pA)		//�@�\�F���𓮂����֐�
//�������P�FCHR_DATA�^�\����
//�������Q�FANIME_DATA�^�\���́i���ݕ\�����̃A�j�����ύX�\�����ׂ�̕K�v
{

	switch(Nage)
	{
	case 0:	//�����Ȃ��ĂȂ��Ȃ�i0�Ȃ�j
		switch(CmdNum[0])	//�\���L�[�̃f�[�^�����Ƃɕ���
		{
		case 1:		//������������
			if(pA->Change)
			{
				pC->AniType = 2;	//�������̃A�j���[�V����
				pC->muki = 1;		//����������
				
				if(CmdGet == 1)	//�_�b�V���R�}���h����͂��Ă�����
					pC->x -= 15;	//���Ɉړ�
				else			//�_�b�V���R�}���h����͂��Ă��Ȃ�������
					pC->x -= 8;

				if(pC->OldAniType != 2 || CmdNum[0])	//�O��̃A�j���[�V�������Q����Ȃ��Ȃ� OR �\���L�[�ǂꂩ�������Ă�����
				{
					//�������ς�����̂ŁiOldAniType�Ŕ���) ���̓����蔻��͈͂�ύX
					pC->Hit.w = 90;		//�����蔻��̕�
					pC->Hit.h = 22;		//�����蔻��̍���
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
					pC->AniNum = 0;	//�A�j���[�V�������ŏ�����
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//���[�v���Ė߂�A�j��
			}
			break;
		case 2:		//�����������
			if(pA->Change)	//�ύX�\�ȃA�j���[�V�����Ȃ�
			{
				pC->AniType = 0;	//������̃A�j���[�V����
				pC->muki = 2;		//���������

				if(CmdGet == 2)		//�_�b�V���R�}���h����͂�����
					pC->y -= 15;
				else
					pC->y -= 8;
				
				if(pC->OldAniType != 0 || CmdNum[0])	//�O��̃A�j�����O����Ȃ��Ȃ�
				{
					//�������ς�����̂ŁiOldAniType�Ŕ���) ���̓����蔻��͈͂�ύX
					pC->Hit.w = 22;		//�����蔻��̕�
					pC->Hit.h = 90;		//�����蔻��̍���
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
					pC->AniNum = 0;	//�A�j���[�V�������ŏ�����
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//���[�v���Ė߂�A�j��
			}
			break;
		case 4:		//�E����������
			if(pA->Change)	//�ύX�\�ȃA�j���[�V�����Ȃ�
			{
				pC->AniType = 3;	//�E�����̃A�j��
				pC->muki = 3;		//�������E
				
				if(CmdGet == 3)		//�_�b�V���R�}���h����͂�����
					pC->x += 15;
				else
					pC->x += 8;
				
				if(pC->OldAniType != 3 || CmdNum[0])	
				{
					//�������ς�����̂ŁiOldAniType�Ŕ���) ���̓����蔻��͈͂�ύX
					pC->Hit.w = 90;		//�����蔻��̕�
					pC->Hit.h = 22;		//�����蔻��̍���
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
					pC->AniNum = 0;	//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;	//���[�v���Ė߂�A�j��
			}
			break;
		case 8:		//������������
			if(pA->Change)
			{
				pC->AniType = 1;	//�������̃A�j���[�V����
				pC->muki = 4;		//��������

				if(CmdGet == 4)		//�_�b�V���R�}���h����͂�����
					pC->y += 15;
				else
					pC->y += 8;
				
				if(pC->OldAniType != 1 || CmdNum[0])	
				{
					//�������ς�����̂ŁiOldAniType�Ŕ���) ���̓����蔻��͈͂�ύX
					pC->Hit.w = 22;		//�����蔻��̕�
					pC->Hit.h = 90;		//�����蔻��̍���
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
					pC->AniNum = 0;	//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;
			}
			break;
		default:	//�ǂ̏����ɂ����Ă͂܂�Ȃ��ꍇ
			if(pA->Change && (pC->AniType == 4 && pC->AniNum == 7))	//�o���A�j���[�V�������I��鎞�Ȃ�
			{
				pC->AniType = 0;	
				pC->muki = 1;		
				if(pC->OldAniType != 0 || CmdNum[0])		//�O��̃A�j���[�V���������̃A�j������Ȃ�������
				{
					//�������ς�����̂ŁiOldAniType�Ŕ���) ���̓����蔻��͈͂�ύX
					pC->Hit.w = 22;		//�����蔻��̕�
					pC->Hit.h = 90;		//�����蔻��̍���
					pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
					pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
					pC->AniNum = 0;										//�A�j���[�V�����̍ŏ�����
					pC->AniTimeNow = 0;
				}
				pC->AniTurn = 0;
			}
			break;
		}
		break;

	case 1:	//���Ɍ����Ȃ�����
		if(pA->Change)
		{
			pC->AniType = 2;	//�������̃A�j���[�V����
			pC->muki = 1;		//����������
			pC->x -= 15;	//���Ɉړ�

			if(pC->OldAniType != 2)	//�O��̃A�j���[�V�������Q����Ȃ��Ȃ�
			{			//�������ς�����̂�
				pC->AniNum = 0;	//�A�j���[�V�������ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;	//���[�v���Ė߂�A�j��

			pC->Hit.w = 90;		//�����蔻��̕�
			pC->Hit.h = 22;		//�����蔻��̍���
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W

		}
		break;
	case 2:	//�����E�ɓ�������
		if(pA->Change)	//�ύX�\�ȃA�j���[�V�����Ȃ�
		{
			pC->AniType = 3;	//�E�����̃A�j��
			pC->muki = 3;		//�������E
			pC->x += 15;		//�E�Ɉړ�
			
			if(pC->OldAniType != 3)	//�O��̃A�j���[�V�������Q����Ȃ��Ȃ�
			{
				//�������ς�����̂�
				pC->AniNum = 0;	//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;	//���[�v���Ė߂�A�j��
			pC->Hit.w = 90;		//�����蔻��̕�
			pC->Hit.h = 22;		//�����蔻��̍���
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
		}
		break;
	case 3:	//�������ɂȂ�����
		if(pA->Change)
		{
			pC->AniType = 1;	//�������̃A�j���[�V����
			pC->muki = 4;		//��������
			pC->y += 25;		//�������Ɉړ�
			
			if(pC->OldAniType != 1)	//�O��̃A�j���[�V�������Q����Ȃ��Ȃ�
			{	//�������ς�����̂�
				pC->AniNum = 0;	//�A�j���[�V�����̍ŏ�����
				pC->AniTimeNow = 0;
			}
			pC->AniTurn = 0;

			pC->Hit.w = 22;		//�����蔻��̕�
			pC->Hit.h = 90;		//�����蔻��̍���
			pC->Hit.x = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�荶��X���W
			pC->Hit.y = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�荶��Y���W
		}
		break;

	}
	


	pC->OldAniType = pC->AniType;	//�O��̃A�j���[�V�����̎�ނ�ۑ�
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
