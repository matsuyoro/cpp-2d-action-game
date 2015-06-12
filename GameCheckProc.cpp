#include <windows.h>

#include "GameStruct.h"		//�\���̂̌^�̒�`�̃w�b�_�t�@�C��
#include "Extern.h"			//�O���ϐ��̐錾�̃w�b�_�t�@�C��
#include "DirectSound.h"

#include "GameCheckProc.h"
	//����֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
////�֐��{��//////
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int CharAnime(CHR_DATA *pC,ANIME_DATA *pA,ANIME_DATA *pA2)		//�@�\�F�L�����N�^�[���A�j���[�V����������֐�
//�������P�F�A�j���[�V��������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����f�[�^�̍\���̂̑�Q�v�f���̂P��̃f�[�^
{
	pC->AniTimeNow++;	//�\�����ԃJ�E���^���{�P
	if(pC->AniTimeNow >= pA->TimeMax)	//�\�����Ԃ��A���\�����Ă���v�f�̂̍ő�\�����Ԉȏ�ɂȂ�����	
	{
		pC->AniNum++;	//���̊G�ɐi��
		if(pA2->Num == -1)	//�����A�i�񂾐�̗v�f��Num�����o���[�P��������
		{
			pC->AniNum = pC->AniTurn;	//-1���o����ǂ̊G�ɖ߂邩	
		}else if(pA2->Num == -2)	//�����A�i�񂾐�̗v�f��Num�����o���[�Q��������
		{
			pC->AniType = 0;		//��{�ƂȂ�A�j���[�V�����̍ŏ�����X�^�[�g
			pC->AniNum = 0;
		}
		pC->AniTimeNow = 0;	//�\�����Ԃ��O��
	}
	return(pA->Num);	//Anime�\���̂̃����oNum��߂�
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int KeyCmdChk(int Key)		//�@�\�F�R�}���h���͊֐�
//�������P�F�\���L�[�f�[�^
//���ߒl�F�ǂ̃R�}���h����͂�������߂�
{
	int i,j;						//�J�E���^�ϐ�
	static int Cnt;					//�R�}���h�̏��Ԃ�\���z��̉��Ԗڂ𒲂ׂĂ��邩
	//static int AllCnt;			//�R�}���h���͂̑S�Ă̎��Ԃ̍��v������

	if(Key == CmdNum[0])	//�O��Ɠ����L�[��������Ă�����
	{
		CmdCnt[0]++;		//�����Ă���{�^���̎��ԂƃJ�E���g
	}else					//�����łȂ��Ȃ�
	{
		for(i = 7;i > 0;i--)	//7�`�P�̏��Ԃɂ��炷
		{
			CmdNum[i] = CmdNum[i-1];	//�z��̒��g�����炷
			CmdCnt[i] = CmdCnt[i-1];	//�����Ă��鎞�Ԃ������z������炷
		}
		CmdNum[0] = Key;	//0�ɍŐV�̃f�[�^����
		CmdCnt[0] = 1;		//���Ԃ̃J�E���g���P����n�܂�悤��
	}

	for(j = 0;j < CMD_MAX;j++)	//�R�}���h�f�[�^�̕������J��Ԃ�
	{
		Cnt = 0;					//�R�}���h�̔z��̉��Ԗڂ𒲂ׂ邩������Cnt���O�ɖ߂�

		for(i = 3;i >= 0;i--)		//3�񕪂̃f�[�^�������ׂ�
		{
			if(CmdNum[i] == WazaCmd[j].Cmd[Cnt])	//�����A�\���L�[�ƃR�}���h�f�[�^��������������
			{						
				Cnt++;									//���̃R�}���h�f�[�^�𒲂ׂ�
				//if(Cnt >= 3) break;					//�R�}���h�f�[�^���R����ł�����A���[�v�I��
				if(WazaCmd[j].Cmd[Cnt] == -1)			//�Z�f�[�^��-1���o���炻���ŋZ�̏I��
					break;
			}
		
		}

		if(	WazaCmd[j].Cmd[Cnt] == -1				//�R�}���h���R����ł�
		&& CmdNum[0] == WazaCmd[j].Cmd[Cnt-1]		//�ŐV�̃R�}���h�f�[�^�ƋZ�f�[�^�̍Ō�̃f�[�^�������Ȃ�
		&& (!WazaCmd[j].Btn							//�{�^�������̋Z�Ȃ�
		|| (Btn1 & WazaCmd[j].Btn)					//���݉����Ă���{�^���ƋZ�f�[�^�̃{�^���������Ȃ�
		&& Btn2 != Btn1))							//�P�O�̃{�^���f�[�^�ƍŐV�̃{�^���f�[�^���قȂ�Ȃ�
		{
			AllCnt = 0;	//�Z���͎��Ԃ��܂��͂O��
			for(i = 0;i < Cnt;i++)	//�Z���͂̑S�Ă̎��Ԃ�AllCnt�ɑ��
				AllCnt += CmdCnt[i];
			if(AllCnt < WazaCmd[j].Time)	//���͂������Ԃ��Z���͎��Ԉȉ��Ȃ�
			{
				return(j);	//���������R�}���h�̔ԍ���߂�
			}
		}
	}
	return(-1);	//�ǂ̃R�}���h�����͂��Ȃ�������
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EnemyOnPos()	//�@�\�F�G�l�~�[�����̈ʒu�ɏo��������֐�
{
	int i,j;	//�J�E���^�ϐ�

	for(i = 0;i < EneOnPos_Max.x;i++)	//�o���|�C���g�̐������J��Ԃ�
	{
		if(pEneOn[i].OnFlag)	//�t���O��TRUE�Ȃ�i�܂��o�����ĂȂ��|�C���g�̓G�Ȃ�
		{
			if((pEneOn[i].x > WMoveX && pEneOn[i].x < WMoveX+640)
			&& (pEneOn[i].y > WMoveY && pEneOn[i].y < WMoveY+480))	//�o���|�C���g����ʓ��ɂ�����
			{
				for(j = 0;j < ENE_MAX;j++)
				{
					if(!En[j].Son)	//�G�l�~�[�����݂��Ȃ��Ȃ�
					{
						En[j] = EnemyNum[pEneOn[i].type];	//�w��̃G�l�~�[��ݒ�
						En[j].x = pEneOn[i].x - WMoveX;				//�G�l�~�[���w���X���W�ɐݒ�
						En[j].y = pEneOn[i].y - WMoveY;				//�G�l�~�[���w���Y���W�ɐݒ�
						En[j].Son = TRUE;					//�G�l�~�[�𑶍݂�����
						pEneOn[i].OnFlag = FALSE;			//��x�o��������Ƃ����o�����Ȃ�����
						
						if(En[i].Type == 3 && En[i].Son)	//�K�����Ȃ�
						{
							//En[i] = EnemyNum[3];			//�G�l�~�[�P�𑶍݂�����
							//En[i].Son = TRUE;
							OBJON(Obj,(320<<5)-WMoveX,(25<<5)-WMoveY,0);			//�I�u�W�F�i�{�X�P��
						//	OBJON(Obj,En[i].x+60,En[i].y+240,0);
						//	OBJON(Obj,En[i].x+50,En[i].y+200,0);
							OBJON(Obj,En[i].x+40,En[i].y+170,4);			//�I�u�W�F�i�{�X�P�Ԑ�
							OBJON(Obj,En[i].x+37,En[i].y+160,4);
							OBJON(Obj,En[i].x+34,En[i].y+150,4);
							OBJON(Obj,En[i].x+30,En[i].y+140,3);
							OBJON(Obj,En[i].x+27,En[i].y+130,3);
							OBJON(Obj,En[i].x+24,En[i].y+120,3);
							OBJON(Obj,En[i].x+20,En[i].y+110,3);
							OBJON(Obj,En[i].x+15,En[i].y+90,2);
							OBJON(Obj,En[i].x+10,En[i].y+80,2);
							OBJON(Obj,En[i].x+5,En[i].y+50,2);
							break;
						}
						break;
					}
				}
			}
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void OBJON(OBJ_DATA *pO,int x,int y,int OBJType)	//�@�\�F�I�u�W�F�N�g���������߂̊֐�
//�������P�F�I�u�W�F�N�g�̍\����
//�������Q�F�I�u�W�F�N�g�̕\���ʒuX
//�������R�F�I�u�W�F�N�g�̕\���ʒuY
//�������S�F�I�u�W�F�N�g�̎��
{
	int i;

	for(i = 0;i < OBJ_MAX;i++)	//�I�u�W�F�N�g�̐������J��Ԃ�
	{
		if(!pO[i].Son)	//�I�u�W�F�N�g�̑��݂�FALSE�Ȃ�
		{
			pO[i] = OBJData[OBJType];	//�I�u�W�F�N�g�̃f�[�^����
			pO[i].x = x - (pO[i].w>>1);	//�I�u�W�F�N�g���o���ʒuX
			pO[i].y = y - (pO[i].h>>1);	//�I�u�W�F�N�g���o���ʒuY
			pO[i].Son = TRUE;			//�I�u�W�F�N�g�̑��݂�TRUE�ɂ���
			break;
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void BgObjOn(BGOBJ_DATA *pO,int x,int y,int OBJType,int BGLine)	//�@�\�F�I�u�W�F�N�g���������߂̊֐�
//�������P�F�I�u�W�F�N�g�̍\����
//�������Q�F�I�u�W�F�N�g�̕\���ʒuX
//�������R�F�I�u�W�F�N�g�̕\���ʒuY
//�������S�F�I�u�W�F�N�g�̎��
//�������T�F�w�i�̂ǂ̕����ɃI�u�W�F��ݒu���邩
{
	int i;

	for(i = 0;i < BGOBJ_MAX;i++)	//�I�u�W�F�N�g�̐������J��Ԃ�
	{
		if(!pO[i].Son)	//�I�u�W�F�N�g�̑��݂�FALSE�Ȃ�
		{
			while(TRUE)	//�I�u�W�F���ݒu�����܂ŌJ��Ԃ�
			{
				pO[i] = BGOBJData[OBJType];	//�I�u�W�F�N�g�̃f�[�^����

				if((BGLine == (pO[i].Line-1)) || (!pO[i].Line))	//�񂪎w�肳��Ă���I�u�W�F�Ɨ����̃I�u�W�F�̗񂪓������@�w��Ȃ��Ȃ�i�O�Ȃ�j
				{
					pO[i].Line = BGLine;		//�w�i�̂ǂ̕����ɐݒu���邩��ݒ�
					pO[i].x = x;				//�I�u�W�F�N�g���o���ʒuX
					pO[i].y = y - pO[i].h;		//�I�u�W�F�N�g���o���ʒuY
					pO[i].orgX = x;				//�����W�ۑ��p�i�X�N���[�����g��

					pO[i].Son = TRUE;			//�I�u�W�F�N�g�̑��݂�TRUE�ɂ���
					break;
				}
				OBJType = rand()%22;	//�I�u�W�F�̎�ނ𗐐��ŕς���
			}
			break;
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EFON(EF_DATA *pE,int x,int y,int EType)	//�@�\�F�G�t�F�N�g���o�����߂̊֐�
//�������P�F�G�t�F�N�g�̍\����
//�������Q�F�G�t�F�N�g�\���ʒuX
//�������R�F�G�t�F�N�g�\���ʒuY
//�������S�F�G�t�F�N�g�̎��
{
	int i;

	//�G�t�F�N�g�̔���
	for(i = 0;i < EF_MAX;i++)	//�G�t�F�N�g�̐������J��Ԃ�
	{
		if(!pE[i].Son)	//�G�t�F�N�g�̑��݂�FALSE�Ȃ�
		{	
			pE[i] = EFData[EType];		//�G�t�F�N�g�̃f�[�^����
			pE[i].x = x - (pE[i].w>>1);	//�G�t�F�N�g���o���ʒuX
			pE[i].y = y - (pE[i].h>>1);	//�G�t�F�N�g���o���ʒuY
			pE[i].Son = TRUE;			//�G�t�F�N�g�̑��݂�TRUE�ɂ���
			break;
		}
	}

}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EFOFF(EF_DATA *pE)	//�@�\�F�G�t�F�N�g�̃A�j���[�V�����Ƒ��݂������֐�
//�������P�F�G�t�F�N�g�̍\����
{
	int i;

	//�G�t�F�N�g�A�j���[�V�����Ƒ���
	for(i = 0;i < EF_MAX;i++)
	{
		if(pE[i].Son)	//�G�t�F�N�g�����݂�����
		{
			pE[i].AniCnt++;	//�A�j���[�V�����\���̃J�E���g
			if(pE[i].AniCnt > pE[i].AniMax)	
				pE[i].Son = FALSE;	//�A�j���[�V�������Ō�܂ŕ\�������G�t�F�N�g�̑��݂�����
		}
	}
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ShotFire(int x,int y,int muki,int SType,int EnePlr)	//�@�\�F�e�𔭎˂���֐�
//�������P�F�e���ˈʒuX
//�������Q�F�e���ˈʒuY
//�������R�F�ړ������i�O����
//�������S�F�e�̎��
//�������T�F�����蔻��Ώۂ̃L�����i1 = �G�l�~�[ :2 = �v���C���[
{
	int i;

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(!Shot[i].Son)	//�e�̑��݂�FALSE�Ȃ�
		{	
			Shot[i] = ShotData[SType];	//�e�̃f�[�^����
			Shot[i].x = x;	//�e�𔭎˂���ʒuX
			Shot[i].y = y;	//�e�𔭎˂���ʒuY
			if(muki == 0)	Shot[i].mx = -Shot[i].mx;		//�������������Ȃ獶�ɒe���΂�
			Shot[i].Son = EnePlr;								//�e�̑��݂�TRUE�ɂ���
			break;
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ShotMove(int mx,int my)	//�@�\�F�e���ړ�������֐�
//������1�C2�F�eXY�ړ���
{
	int i;	//�J�E���^

	for(i = 0;i < SHOT_MAX;i++)	//�e�̐������J��Ԃ�
	{
		if(Shot[i].Son)	//�e�����݂���Ȃ�
		{
			
			switch(Shot[i].Type)	//�e�̎�ނ����ɕ���
			{
			//--------------------------------------------------------------------------------------
			case 4://���ォ�痎�����
				Shot[i].my++;
				Shot[i].y += Shot[i].my;
				break;
			case 22://�����΂���Œe
			case 24://�����e
				Shot[i].mx = (i%8)-4;	//�V���b�g�̔z��ԍ��Ŏg�px���W�ړ��ʂ����߂�
				Shot[i].my++;			//�������x�����X�ɏグ��
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				break;
			case 26://���D�Q�i�Q���Q�j
				Shot[i].mx = (i%3)-3;
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt == 7)
				{
					ShotFire(Shot[i].x,Shot[i].y,0,24,Shot[i].Son);	//�e�̔���
					Shot[i].Son = FALSE;
				}
			case 25://���D
				Shot[i].mx = (i%3)-3;
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				break;
			case 27://�����U���鉊
				Shot[i].x += Shot[i].mx;
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt == 4)
				{
					//Shot[i].mx -= (rand()%5-2);
					//Shot[i].mx %= 4;
					Shot[i].my -= (rand()%5-2);
					Shot[i].my %= 4;
					
					if(Shot[i].mx < 0)
						ShotFire(Shot[i].x,Shot[i].y,0,26,Shot[i].Son);	//�e�̔���
					else
						ShotFire(Shot[i].x,Shot[i].y,1,26,Shot[i].Son);	//�e�̔���
				}

				break;
			case 29://�������e(�G�t�F�N�g���g�p
				if(Shot[i].AniCnt == (rand()%15))
					EFON(EF,Shot[i].x,Shot[i].y,0);
				break;

			//--------------------------------------------------------------------------------------
			case 7://���n�ʂ̉�
				if(Shot[i].AniCnt >= 3 && (rand()%10 ==1))	
					Shot[i].Son = FALSE;	//�A�j���[�V�������S���ڂŗ������P�Ȃ�e������
				break;
			//--------------------------------------------------------------------------------------
			case 11:	//���I
			case 12:	//�V
			case 13:
			case 14:
			case 15:
			case 16:
		

			case 9://���t���ϗ���
			case 8://��
			case 18:
				if(Shot[i].Type != 18 || rand()%5 == 1)
				{
					if(Shot[i].x+4 > Plr.x+(Plr.w>>1))	//�e���v���C���[���E�ɂ�����
						Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
					else								//���ɂ�����
						Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
					Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������

					if(Shot[i].y+4 > Plr.y+(Plr.h>>1))	//�e���v���C���[��艺�ɂ�����
						Shot[i].my --;					
					else								//��ɂ�����
						Shot[i].my ++;
					Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
				}
				break;
			case 20:	//���j��
				if(Plr.AniType == 19)	//�v���C���[���z���A�j���[�V�������Ȃ�
				{
					Shot[i].Son = 3;	//�e�̔���L�����𗼕��ɂ���

					if(Shot[i].x+4 > Plr.x+(Plr.w>>1))	//�e���v���C���[���E�ɂ�����
						Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
					else								//���ɂ�����
						Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
					Shot[i].mx %= 16;
					Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������

					if(Shot[i].y+4 > Plr.y+(Plr.h>>1))	//�e���v���C���[��艺�ɂ�����
						Shot[i].my --;					
					else								//��ɂ�����
						Shot[i].my ++;
					Shot[i].my %= 16;
					Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
				}else if(rand()%3 == 1)	//�����łȂ��Ȃ�
				{
					Shot[i].Son = 1;	//���j�Ђ̔���L�������v���C���[�ɂ���
					Shot[i].mx += rand()%3-1;
					Shot[i].my += rand()%3-1;
					Shot[i].x += Shot[i].mx;
					Shot[i].y += Shot[i].my;
				}
				break;

			case 10://���t���ϐ���
				if(Shot[i].x+4 > 320)	//�e����ʒ������E�ɂ�����
					Shot[i].mx --;
				else					//���ɂ�����
					if(Shot[i].mx > 1)	Shot[i].mx ++;	//��΂ɉE�ɂ͗���Ȃ��悤�ɂ���
				Shot[i].x += Shot[i].mx;

				if(Shot[i].y+4 > 240)	//�e����ʒ�����艺�ɂ�����
					Shot[i].my --;
				else					//��ɂ�����
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;
				break;
			case 19://���Ή�����
				Shot[i].y += (rand()%16-8);
				if(Shot[i].mx > 0) Shot[i].mx--;	//�ړ����x���O����Ȃ��Ȃ炶�傶��ɑ��x�𗎂Ƃ�
				if(Shot[i].mx < 0) Shot[i].mx++;
				Shot[i].x += Shot[i].mx;		//�e���ړ��ʂ̕������ړ�������
				Shot[i].y += Shot[i].my;
				if(Shot[i].mx == 0)		//�e�̃A�j���[�V�������S���傫���Ȃ�����
					Shot[i].Son = FALSE;	//�e������

				break;

			case 6://���Ή�����(������
				Shot[i].y += (rand()%10)-5;	//�e��Y���W�𗐐��ŕς���
				Shot[i].AniCnt %= 5;
				Shot[i].x += Shot[i].mx;		//�e���ړ��ʂ̕������ړ�������
				Shot[i].y += Shot[i].my;
				break;
			case 17:
				Shot[i].x += Shot[i].mx;		//�e���ړ��ʂ̕������ړ�������
				Shot[i].y += Shot[i].my;
				if(Shot[i].AniCnt > 3)	//�A�j���[�V�������T�ȏ�Ȃ�
					Shot[i].Son = FALSE;	//�e������
				break;

			default:	//�ʏ�̒e�Ȃ�
				Shot[i].x += Shot[i].mx;		//�e���ړ��ʂ̕������ړ�������
				Shot[i].y += Shot[i].my;
				break;
			}

			if(Shot[i].Type != 20)	//���̔j�Вe����Ȃ��Ȃ�
			{
				if(Shot[i].y > 480 || Shot[i].y < -Shot[i].w
				|| Shot[i].x > 640 || Shot[i].x < -Shot[i].h)	//��ʂ̊O�ɏo����
				{
					Shot[i].Son = FALSE;					//���݂�FALSE��
				}
			}else
			{	//���̔j�Ђ̗L���͈�
				if(Shot[i].y > Plr.y+(Plr.h>>1)+800 || Shot[i].y < Plr.y+(Plr.h>>1)-800
				|| Shot[i].x > Plr.x+(Plr.w>>1)+800 || Shot[i].x < Plr.x+(Plr.w>>1)-800)
				{	//���̔j�Ђ̗L���͈͕͂��ʂ̒e���L��
					Shot[i].Son = FALSE;
				}
			}
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void PlrSwdChk(CHR_DATA *p1,CHR_DATA *p2)	//�@�\�F�v���C���[�ƌ��̓����蔻��
//�������P�F���������CHR_DATA�^�̃L�����f�[�^
//�������Q�F��������錕�̃L�����f�[�^

{
	int x1,y1,w1,h1;	//���������L�����P�̍���XY���W�ƕ��A����������
	int x2,y2,w2,h2;	//�����ЂƂ�̔��������L�����̓����蔻��͈�
		
	//�L�����P
	x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);				//�����蔻�蕔���̍���x���W
	y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1);				//�����蔻�蕔���̍���y���W
	w1 = p1->Hit.w;											//�����蔻�蕔���̕�
	h1 = p1->Hit.h;											//�����蔻�蕔���̍���
	//��
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//�L�����P�ƃL�����Q���d�Ȃ��Ă�����
	{
		if(y1+((h1>>2)*3) < y2+(h2>>2) && p1->U > 0)	//	���̍�����4����1�@���@�L���������蔻��Y���W�{�L����4����3�̂Ƃ���ɓ��������� &&�@�������Ȃ�
		{
			p1->Land = 1;	//���n����
			y1 = y2 - h1;	//�L������߂��̍��W�����Ƃ߂đ��
			p1->y = y1 + (h1>>1) - (p1->h>>1);
		}
	}
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ChrHitChk(CHR_DATA *p1,CHR_DATA *p2)	//�@�\�F�v���C���[�ƃL�����̓����蔻��
//�������P�F���������CHR_DATA�^�̃L�����f�[�^
//�������Q�F��������������l�̃L�����f�[�^
//���߂�l�F�ǂ������U�������������𐔒l�ŕԂ�
{
	int x1,y1,w1,h1;	//���������L�����P�̍���XY���W�ƕ��A����������
	int x2,y2,w2,h2;	//�����ЂƂ�̔��������L�����̓����蔻��͈�
		
	//�L�����P
	if(p1->Type == -1								//�L�������v���C���[�Ȃ�
	&& ((p1->AniType == 3 && p1->AniNum > 3)		//���Ⴊ�ݒ��Ȃ�
	|| (p1->AniType == 10) || (p1->AniType == 11)	//���Ⴊ�ݍU�����Ȃ�
	|| (p1->AniType == 17)))						//�����Ⴊ�ݓ�������������
	{
		x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);					//�����蔻�蕔���̍���x���W
		y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1) + (p1->Hit.h>>1);								//�����蔻�蕔���̍���y���W
		w1 = p1->Hit.w;												//�����蔻�蕔���̕�
		h1 = p1->Hit.h>>1;											//�����蔻�蕔���̍���
	}else		//�����ɂ��Ă܂�Ȃ�������
	{
		x1 = p1->x + (p1->w>>1) - (p1->Hit.w>>1);				//�����蔻�蕔���̍���x���W
		y1 = p1->y + (p1->h>>1) - (p1->Hit.h>>1);				//�����蔻�蕔���̍���y���W
		w1 = p1->Hit.w;											//�����蔻�蕔���̕�
		h1 = p1->Hit.h;											//�����蔻�蕔���̍���
	}

	//�L�����Q
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//�L�����P�ƃL�����Q���d�Ȃ��Ă�����
	{
		if(p2->Type != 11)	p1->HitD = 1;		//�U�����󂯂���TRUE(�G�l�~�[���c�{�Ȃ�_���[�W�t���O���P�ɂ��Ȃ�
		p1->Hp -= p2->Atk;	//�K�̍U���͕��_���[�W
		DS_Play(5,FALSE);	//���ʉ���炷

		if(x2+(w2>>1) < x1+(w1>>1))		//�L�����Q�̉E���ɂ�����
		{
			if(p1->x < 400-(p1->w>>1))	//�L������x���W400��菬�������
			{
				p1->x += 15;				//�L�����E�ɂӂ��Ƃ΂�
				p2->x -= 2;					//�U�������L�����͂��������ɂ����
			}else						//�����𖞂����ĂȂ���΁i�L������x���W400�ȏ�Ȃ�
			{
				if(!(WMoveX >= (MapXnum-WINMAP_W) * TIP_W))		//�E�[�܂ł������牽�����Ȃ�
				{
					WorldX = 15;				//WorldX���{�P
					p2->x -= 2;
				}
			}
			p1->muki = 1;	//������������
		}else							//�E������Ȃ�������
		{	
			if(p1->x > 200-(p1->w>>1))	//�L����X���W��200���傫�����
			{	
				p1->x -= 15;					//�L���������ɂӂ���΂�
				p2->x += 2;
			}else						//�L����X���W��200�ȉ��Ȃ�
			{
				if(!(WMoveX <= 0))			//���[�܂ł������牽�����Ȃ�
				{	
					WorldX = -15;					//WordlX���|�P(Map���E�ɃX�N���[��
					p2->x -= 2;
				}
			}
			p1->muki = 0;	//�E����������
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int ShotHitChk(SHOT_DATA *pS,CHR_DATA *pC)	//�@�\�F�e�ƃL�����̔���
//�������P�F������s���e�̃f�[�^
//�������Q�F�_���[�W��������L�����̃f�[�^
{
	int x1,y1,w1,h1;	//���������L�����P�̍���XY���W�ƕ��A����������
	int x2,y2,w2,h2;	//�����ЂƂ�̔��������L�����̓����蔻��͈�
		
	//�e
	x1 = pS->x + (pS->w>>1) - (pS->Hit.w>>1);				//�����蔻�蕔���̍���x���W
	y1 = pS->y + (pS->h>>1) - (pS->Hit.h>>1);				//�����蔻�蕔���̍���y���W
	w1 = pS->Hit.w;											//�����蔻�蕔���̕�
	h1 = pS->Hit.h;											//�����蔻�蕔���̍���
	
	//�L����
	if(pC->Type == -1	//����L�������v���C���[��
	&& ((pC->AniType == 3 && pC->AniNum > 3)		//���Ⴊ�ݒ��Ȃ�
	|| (pC->AniType == 10) || (pC->AniType == 11)	//���Ⴊ�ݍU�����Ȃ�
	|| (pC->AniType == 17)))						//�����Ⴊ�ݓ�������������
	{
		x2 = pC->x + (pC->w>>1) - (pC->Hit.w>>1);						//�����蔻�蕔���̍���x���W
		y2 = pC->y + (pC->h>>1) - (pC->Hit.h>>1) + (pC->Hit.h>>1);		//�����蔻�蕔���̍���y���W
		w2 = pC->Hit.w;													//�����蔻�蕔���̕�
		h2 = pC->Hit.h>>1;												//�����蔻�蕔���̍���
	}else		//�K�L�������@�v���C���[�����Ⴊ�ݒ�����Ȃ��ꍇ
	{
		x2 = pC->x + (pC->w>>1) - (pC->Hit.w>>1);
		y2 = pC->y + (pC->h>>1) - (pC->Hit.h>>1);
		w2 = pC->Hit.w;
		h2 = pC->Hit.h;
	}

	if(x1+w1 > x2 && x1 < x2+w2
	&& y1+h1 > y2 && y1 < y2+h2)	//�e�ƃL�����̓����蔻�蕔�����d�Ȃ��Ă�����
	{
		/*
		if(pS->mx > 0)		//�L�����Q�̉E���ɂ�����
		{
			pC->muki = 1;	//������������
		}else							//�E������Ȃ�������
		{	
			pC->muki = 0;	//�E����������
		}
		*/
		

		if(pC->Type == -1)	//�_���[�W���󂯂�L�������v���C���[�Ȃ�
		{
			if(pC->AniType == 18 && pC->AniNum > 9 && pS->Type != 18)		//�v���C���[�A�j�����o���A�ŁA�e���P�W����Ȃ��Ȃ�
			{	
				pS->Son = 2;				//�e�̑��݂��Q�ς������̒e�ɂ���
				pS->mx = -pS->mx;			//�e�̌������t�ɂ���
				//pS->my = -pS->my;			//�㉺�͔��]���Ȃ�
				DS_Play( 7, FALSE);			//���ʉ���炷
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),10);	//�e�̏�����ʒu�ɃG�t�F�N�g��ON
			}else if(pS->Type == 18)	//���e�����Ń_���[�W���󂯂�L�������v���C���[�Ȃ�
			{
				pS->Son = FALSE;								//���������e������
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),9);	//�e�̏�����ʒu�ɃG�t�F�N�g��ON
				if(pC->Hp < pC->MaxHp)
					pC->Hp += pS->Atk;							//�v���C���[��Hp����
				else											//Plr.Hp�����^���ŉ񕜂����猕��Hp��������
					if(Swd.Hp < Swd.MaxHp)	Swd.Hp ++;
			}else if(pS->Type == 20)	//���e�����̔j�ЂȂ�
			{
				pS->Son = FALSE;
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),9);	//�e�̏�����ʒu�ɃG�t�F�N�g��ON
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),10);	//�e�̏�����ʒu�ɒe�q�b�g�G�t�F�N�g��ON
				if(Swd.Hp < Swd.MaxHp)	Swd.Hp ++;
				DS_Play(5,FALSE);								//���ʉ���炷
			}else
			{
				pC->HitD = 1;									//�U�����󂯂���TRUE
				pC->Hp -= pS->Atk;								//�e�̈З͕��_���[�W
				DS_Play(5,FALSE);								//���ʉ���炷
				pS->Son = FALSE;								//�������ďI������瑶�݂�FALSE��
				EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),3);	//�e�̏�����ʒu�ɒe�q�b�g�G�t�F�N�g��ON
			}
		}else	//�����łȂ��Ȃ�
		{
			if(pS->Type == 8)	pC->Hp += 5;				//���f�o�b�O�i�KHP��
			pC->HitD = 10;									//�U�����󂯂���TRUE
			pS->Son = FALSE;
			EFON(EF,pS->x+(pS->w>>1),pS->y+(pS->h>>1),3);	//�e�̏�����ʒu�ɒe�q�b�g�G�t�F�N�g��ON
			pC->Hp -= pS->Atk;								//�e�̃_���[�W��Hp�����炷
			if(pC->Hp < 1 && pC->Type != 11)	pC->Son = FALSE;				//�U�����������L������Hp���P��菬�����Ȃ����� & �K���c�{����Ȃ��Ȃ�//�L�����Q������
		}
		return(pC->HitD);		//�ǂ������U��������������߂�
	}
	return FALSE;	//�������ĂȂ��Ƃ��͂O��Ԃ�
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int AtkHitChk(CHR_DATA *p1,CHR_DATA *p2)	//�@�\�F�v���C���[�̍U���͈͂ƃL�����Q�̓����蔻��
//�������P�F�L�����̍U���͈͂𔻒������CHR_DATA�^�̃L�����f�[�^
//�������Q�F�U�����󂯂�L�����f�[�^
//���߂�l�F�ǂ������U�������������𐔒l�ŕԂ�
{
	int x2,y2,w2,h2;	//�����ЂƂ�̔��������L�����̓����蔻��͈�
	int ax,ay,aw,ah;	//�U���̓����蔻�蕔��������

	int WazaAT = 0;	//���Ă��U���̎�ނɂ���ă_���[�W��ς���
	//p2->HitD = 0;//�ǂ̍U��������������������HitD���A����O��0�ɂ���(1�����a��A2=�c�a��j
	
	//�L�����Q(�_���[�W��������L����
	x2 = p2->x + (p2->w>>1) - (p2->Hit.w>>1);
	y2 = p2->y + (p2->h>>1) - (p2->Hit.h>>1);
	w2 = p2->Hit.w;
	h2 = p2->Hit.h;

	//�L�����P�U���̓����蔻��͈�
	p1->HitA = TRUE;	//�܂���TRUE�ōU�����ɂ���

	if(p1->AniType == 4 && p1->AniNum == 4)	//���a��̏ꍇ
	{
		aw = 70;									//�U���̓����蔻�蕔���̕�
		ah = 20;									//�U���̓����蔻�蕔���̍���
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;	//�������̏ꍇ�̓�����U���͈͔��蕔���̍���x���W
		else			ax = p1->x+(p1->w>>1);		//�E�����̏ꍇ�̓�����U���͈͔��蕔���̍���x���W					
		ay = p1->y + 28;								//�U���̓����蔻�蕔���̍���y���W
		WazaAT = (p1->Atk>>1);	//���؂�̏ꍇ�̃_���[�W��ݒ�
	}
	else if(p1->AniType == 5 && p1->AniNum > 2)	//�c�a��̏ꍇ
	{
		aw = 85;									//�U���͈͂̕�
		ah = 85;									//����
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;	//����X���W
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y;									//����Y���W
		WazaAT = p1->Atk;	//�c�a��̏ꍇ�̃_���[�W��ݒ�
	}
	else if(p1->AniType == 11 && p1->AniNum == 4)	//���Ⴊ�݉��a��̏ꍇ
	{
		aw = 65;
		ah = 20;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y + 50;
		WazaAT = (p1->Atk>>1);
	}
	else if(p1->AniType == 10 && p1->AniNum > 4)	//���Ⴊ�ݏc�a��̏ꍇ
	{
		aw = 60;
		ah = 56;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y + 20;
		WazaAT = p1->Atk + (p1->Atk>>1);
	}
	else if(p1->AniType == 12 && p1->AniNum > 2)	//�W�����v�c�a��̏ꍇ
	{
		aw = 90;
		ah = 80;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y;
		WazaAT = p1->Atk;
	}
	else if(p1->AniType == 13 && p1->AniNum > 2)	//�W�����v���a��̏ꍇ
	{
		aw = 70;
		ah = 20;
		if(p1->muki)	ax = p1->x+(p1->w>>1)-aw;
		else			ax = p1->x+(p1->w>>1);
		ay = p1->y+25;
		WazaAT = (p1->Atk>>1);
	}
	else if(Swd.Son			
		&& !Swd.HitA		//�����h�����ĂȂ�
		&& Swd.AniType != 4 && Swd.AniType != 5	//�����o��&�����A�j���[�V��������Ȃ�
		&& (CmdNum[0] || Nage)	//�����Ȃ��Ă��邩�@OR �\���L�[�������Ă��邩 
		)	//�������݂��āA�\���L�[����͒��ŁA�����h�����ĂȂ�������
	{
		aw = Swd.Hit.w;		//���̓����蔻��͈͂����̂܂ܑ��
		ah = Swd.Hit.h;
		ax = Swd.Hit.x;
		ay = Swd.Hit.y;
		WazaAT = (p1->Atk>>1);
	}
	else if(Swd.Son && Swd.AniType == 5)	//�������݂��āA���̃A�j���[�V�������T�Ȃ�(�����j
	{
		aw = Swd.w;
		ah = Swd.h;
		ax = Swd.x;
		ay = Swd.y;
		WazaAT = (p1->Atk<<1);
	}
	else	//�ǂ̏����ɂ����Ă͂܂�Ȃ��ꍇ
		p1->HitA = FALSE;	//��̏����ɂ��Ă͂܂�Ȃ�������FALSE�Ɂi�U��������Ȃ�

	//�����蔻��͈͂�\������l�p�̍��W����
	xbox = ax;
	ybox = ay;
	wbox = aw;
	hbox = ah;

	if(p1->HitA)	//�U�����Ȃ�i�U���̓����蔻�肪�L���Ȃ�
	{
		if(ax+aw > x2 && ax < x2+w2
		&& ay+ah > y2 && ay < y2+h2)	//�L�����P�̍U���̓����蔻��͈͂ƃL�����Q���d�Ȃ��Ă�����
		{
			p2->Hp -= WazaAT;				//�U�����������L������Hp�[
			DS_Play( 2, FALSE );			//���ʉ���炷

			if((!Swd.Son && (p1->AniType == 4 || p1->AniType == 11 || p1->AniType == 13))
			|| (Swd.Son && (Swd.muki == 1 || Swd.muki == 3)))	//���a��U���Ȃ�	
			{
				p2->HitD = 1;	//���a��Ȃ�P
				EFON(EF,((ax+x2)+((aw+w2)>>1))>>1,((ay+y2)+((ah+h2)>>1))>>1,2);		//�K�ƍU���͈͂̒��Ԃ̈ʒu�ɉ��a��G�t�F�N�g��ON
			}else							//�c�a��U���Ȃ�
			{
				p2->HitD = 2;	//�c�a��Ȃ�Q
				EFON(EF,((ax+x2)+((aw+w2)>>1))>>1,((ay+y2)+((ah+h2)>>1))>>1,1);		//�K�ƍU���͈͂̒��Ԃ̈ʒu�ɏc�a��G�t�F�N�g��ON
			}
			
			/*
			switch(p1->muki)		//�U�������L�����̌����Ŕ���
			{
			case 1:				//�U�������L�������������Ȃ�
				p2->x -= 8;			//���ɔ�΂����
				break;
			case 0:				//�E�����Ȃ�	
				p2->x += 8;			//�E�ɔ�΂����
				break;
			case 2:				//������Ȃ�
				p2->y -= 4;			//��ɔ�΂����
				break;
			case 4:				//�������Ȃ�
				p2->y += 4;
				break;
			}
			*/

			if(p2->Hp < 1 && p2->Type != 11)	//�U�����������L������Hp���P��菬�����Ȃ����� & �����Type���c�{��������
				p2->Son = FALSE;		//�L�����Q������

			return(p2->HitD);		//�ǂ������U��������������߂�
		}
	}
	return(0);
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void UpDownChk(CHR_DATA *pC)	//�@�\�F�㏸�A���~�̈ړ�
//���F�����P�F�ړ�����L�����̃f�[�^
{
	// �d�͂ŉ��ɗ����� ///
	if(pC->Land != 1 | pC->Land != 2)	//�n�ʂ��V��ɂ��Ă��Ȃ�������
		pC->U += 0.7f;	//���ɗ���

	if(pC->U > 0.0f && pC->U < 1.0f)	pC->U = 1.0f;	//�������x���O�ȏ�P�����ɂȂ�Ȃ��悤�ɂ���A�łȂ��ƒ��n�����ꂢ�ɂł��Ȃ��Ȃ�	
	if(pC->U < -30)	pC->U = -30;	//�㏸���x�̍ő�
	if(pC->U > 15)	pC->U = 15;		//���~���x�̍ŏ�
	
	if(pC->Type == -1)	//�����Ƃ��Ď󂯎�����L�������v���C���[�Ȃ�	
	{
		if(pC->U > 0)	//�������Ȃ�
		{
			if(pC->y < 350-(pC->h>>1))	//�L����Y��Y350��菬�������
				pC->y += (int)(pC->U);		//�L�������ړ�
			else						//�L����Y��Y350�ȏ�Ȃ�
				if(WMoveY < (MapYnum-WINMAP_H)*TIP_H)	//�}�b�v�̉��[����Ȃ��Ȃ�
					WorldY = (int)(pC->U);					//�}�b�v�X�N���[��
		}else			//�㏸���Ȃ�
		{
			if(pC->y > 150-(pC->h>>1))	//�L����Y��Y150���傫�����
				pC->y += (int)(pC->U);		//�L�������ړ�
			else						//�L����Y��Y150�ȉ��Ȃ�
				if(WMoveY > 0)				//�}�b�v�̏�[����Ȃ��Ȃ�
					WorldY = (int)(pC->U);		//�}�b�v�X�N���[��
		}				

		WMoveY += WorldY;	//�}�b�v��Y�X�N���[���l������̃X�N���[���ʂ������炷
		ChrYScroll();		//Y�����ɃX�N���[�����������炷����

	}else if(pC->Type != -2)	//�v���C���[�ȊO�Ȃ�i�G�Ȃ�
	{
		pC->y += (int)(pC->U);	//�L�������㉺�Ɉړ����鑬�x���L�������ړ�
	}
	
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ChrYScroll()	//�@�\�F��ʂ�Y�����ɃX�N���[�����Ă���Ƃ��ɃL�������X�N���[�����������炷�֐�
{
	int i;	//�J�E���^

	if(WorldY)	//Y�����ɃX�N���[�������Ȃ�
	{
		for(i = 2;i >= 0;i--)	//�c���̐������J��Ԃ�
			Dum[i].y -= WorldY;		//�v���C���[�̎c����Y�����ɃX�N���[�����������炷

		if(Swd.Son)				//�������݂��A�h�����Ă�����
			Swd.y -= WorldY;			//Y�����Ɍ����X�N���[�����������炷

		//�㉺�ɃX�N���[�������������G�����炷
		for(i = 0;i < ENE_MAX;i++)	//�G�̐��������[�v
			if(En[i].Son)				//���݂��Ă���G�l�~�[�Ȃ�
			{
				En[i].y -= WorldY;		//Y�����ɃX�N���[���������G�l�~�[�����炷
			}
		for(i = 0;i < SHOT_MAX;i++)	//�e�̐��������[�v
			if(Shot[i].Son)			//�e�����݂���Ȃ�
			{
				Shot[i].y -= WorldY;	//�X�N���[���������e�����炷
			}
		for(i = 0;i < EF_MAX;i++)	//�G�t�F�N�g�̐��������[�v
			if(EF[i].Son)				//�G�t�F�N�g�����݂���Ȃ�
				EF[i].y -= WorldY;			//�X�N���[�����������炷
		for(i = 0;i < OBJ_MAX;i++)	//�I�u�W�F�̐��������[�v
			if(Obj[i].Son)				//�I�u�W�F�����݂���Ȃ�
				Obj[i].y -= WorldY;			//�X�N���[���������I�u�W�F�����炷
	}

}	
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ChrXScroll()	//�@�\�F��ʂ�X�����ɃX�N���[�������Ƃ��ɃL�����Ȃǂ����炷�֐�
{
	int i;	//�J�E���^

	//�̃X�N���[�����ɂ��炷����(X����
	if(WorldX)	//X�����ɃX�N���[�������Ȃ�
	{
		for(i = 2;i >= 0;i--)		//�c���̐������J��Ԃ�
			Dum[i].x -= WorldX;			//�v���C���[�̎c����X�����ɃX�N���[�����������炷

		if(Swd.Son)					//�������݂��A�h�����Ă�����
			Swd.x -= WorldX;			//X�����Ɍ����X�N���[�����������炷
		for(i = 0;i < ENE_MAX;i++)	//�G�̐��������[�v
			if(En[i].Son)				//���݂��Ă���G�l�~�[�Ȃ�
				En[i].x -= WorldX;			//X�����ɃX�N���[���������G�����炷
		for(i = 0;i < SHOT_MAX;i++)	//�e�̐��������[�v
			if(Shot[i].Son)				//�e�����݂���Ȃ�
				Shot[i].x -= WorldX;		//X�����ɃX�N���[���������e�����炷
		for(i = 0;i < EF_MAX;i++)	//�G�t�F�N�g�̐��������[�v
			if(EF[i].Son)				//���݂��Ă���G�t�F�N�g�Ȃ�
				EF[i].x -= WorldX;		//X�����ɃX�N���[���������G�t�F�N�g�����炷
		for(i = 0;i < OBJ_MAX;i++)	//�I�u�W�F�N�g�̐��������[�v
			if(Obj[i].Son)				//���݂��Ă���I�u�W�F�Ȃ�
				Obj[i].x -= WorldX;		//x�����ɃX�N���[���������I�u�W�F�����炷
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
