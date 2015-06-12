#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"		//�\���̂̌^�̒�`�̃w�b�_�t�@�C��
#include "Extern.h"			//�O���ϐ��̃w�b�_�t�@�C��
#include "BltProc.h"		//�`��֐��̃w�b�_

#include "GameBltProc.h"
#include "GameCheckProc.h"
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ChrBitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//�@�\�F�L������\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y+pC->h-pA->h;					//�A�j���̊G�̍����������łȂ��Ă������Ƃ͂��낦��悤��Y���W���v�Z
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;								//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//�]������Y���W���v�Z���Ă���

	MyBltFast(	Bx,By,								//�\����XY���W
				pA->Bmp,							//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
				SurL,	SurT,						//�]��������XY���W
				SurL + pA->w,	SurT + pA->h	);	//�]�����E��XY���W
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void SwdBitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//�@�\�F����\������֐�
//�������P�F�\�����錕�̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x + (pC->w>>1) - (pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y + (pC->h>>1) - (pA->h>>1);		//�V�i�����W�p
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;					//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h;					//�]������Y���W���v�Z���Ă���
		
	MyBltFast(	Bx,By,						//�\����XY���W
				pA->Bmp,					//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
				SurL,		//�]��������X���W
				SurT,		//�]��������Y���W
				SurL + pA->w,	SurT + pA->h	);	//�]�����E��XY���W

}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DamageX_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//�@�\�F���a��Ń_���[�W�������鎞�̊G��\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int i;
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y + pC->h - pA->h;				//�A�j���̊G�̍����������łȂ��Ă������Ƃ͂��낦��悤��Y���W���v�Z
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;								//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//�]������Y���W���v�Z���Ă���

	for(i = 0;i < 3;i++)	//�G���R�����炵�ĕ\������
	{		
		MyBltFast(	Bx+(i<<3),By,	//�\����XY���W
				pA->Bmp,			//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
				SurL,								//�]��������X���W
				SurT,	//�]��������Y���W
				SurL + pA->w,	SurT + pA->h	);							//�]�����E��XY���W
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DamageY_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni)	//�@�\�F�c�a��Ń_���[�W���󂯂�Ƃ��̊G��\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int i;
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y+pC->h-pA->h;				//�A�j���̊G�̍����������łȂ��Ă������Ƃ͂��낦��悤��Y���W���v�Z
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;								//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//�]������Y���W���v�Z���Ă���

	for(i = 0;i < 3;i++)	//�G���R�����炵�ĕ\��������
	{
		MyBltFast(	Bx,By+(i<<3),	//�\����XY���W
			pA->Bmp,				//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
			SurL,								//�]��������X���W
			SurT,								//�]��������Y���W
			SurL + pA->w,	SurT + pA->h	);	//�]�����E��XY���W
	}
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void Kill_X_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni,int Cnt)	//�@�\�F�G�����ɐ؂��G��\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y+pC->h-pA->h;				//�A�j���̊G�̍����������łȂ��Ă������Ƃ͂��낦��悤��Y���W���v�Z
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;								//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//�]������Y���W���v�Z���Ă���
	
	//�Q���ꂽ�G�̏㕔���̕`��
	MyBltFast(Bx-(Cnt<<1),By,									//�\����XY���W
		pA->Bmp,												//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		SurL,									//�]��������X���W
		SurT,		//�]��������Y���W
		SurL + pA->w,	SurT + (pA->h>>1)	);							//�]�����E��XY���W

	//�Q�Ɋ��ꂽ�G�̉������̕`��
	MyBltFast(Bx+(Cnt<<1),By+(pA->h>>1),				//�\����XY���W
		pA->Bmp,										//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		SurL,									//�]��������X���W
		SurT + (pA->h>>1),						//�]��������Y���W
		SurL + pA->w,	SurT+pA->h	);	//�]�����E��XY���W
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void Kill_Y_BitBlt(CHR_DATA *pC,ANIME_DATA *pA,int ChrAni,int Cnt)	//�@�\�F�G�����ɐ؂��G��\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pC->x+(pC->w>>1)-(pA->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pC->y + pC->h - pA->h;					//�A�j���̊G�̍����������łȂ��Ă������Ƃ͂��낦��悤��Y���W���v�Z
	int SurL,SurT;								//�摜�]�����T�[�t�F�[�X�̍���XY���W������

	BNum = 640/pA->w;		//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��
	SurL = (ChrAni%BNum) * pA->w;								//�]������X���W���v�Z���Ă���
	SurT = (ChrAni/BNum) * pA->h + (pC->muki*pA->h*pA->ynum);	//�]������Y���W���v�Z���Ă���

	//�Q�Ɋ��ꂽ�G�̍��̕����̕`��
	MyBltFast(Bx,	By-(Cnt<<1),					//�\����XY���W
		pA->Bmp,								//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		SurL,									//�]��������X���W
		SurT,									//�]��������Y���W
		SurL + (pA->w>>1),	SurT + pA->h	);		//�]�����E��XY���W

	//�Q�Ɋ��ꂽ�G�̉E�̕����̕`��
	MyBltFast(Bx+(pA->w>>1),	By+(Cnt<<1),		//�\����XY���W
		pA->Bmp,								//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		SurL + (pA->w>>1),						//�]��������X���W
		SurT,									//�]��������Y���W
		SurL + pA->w,	SurT + pA->h	);		//�]�����E��XY���W

}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
/*void DumBitBlt(CHR_DATA *pChr,ANIME_DATA *pAni,int ChrAni)	//�@�\�F�L�����̎c����\������֐�
//�������P�F�\������L�����̍\����
//�������Q�F�A�j���[�V�����f�[�^�̍\����
//�������R�F�A�j���[�V�����֐��̖ߒl
{
	int BNum;	//�ǂݍ��ݐ�̊G�̉����ɕ��ׂ��Ă���G�̖��������߂�
	int Bx = pChr->x+(pChr->w>>1)-(pAni->w>>1);		//�A�j���[�V�����̉摜��\������ꏊ���L�����̒����ɂ��邽�߂̕ϐ�
	int By = pChr->y+pChr->h-pAni->h;		//�V�i�����W�p
	BNum = 640/pAni->w;				//�G�̓ǂݍ��ݐ�����ɕ��ׂ����Ȃ��悤��640�𒴂����玟�̍s�ɂ����悤��

	BitBlt(hMemDC,Bx,By,pAni->w,pAni->h,
		pAni->Bmp,(ChrAni%BNum)*pAni->w,(ChrAni/BNum)*pAni->h+(pChr->muki*pAni->h*pAni->ynum),SRCPAINT);	//���z��ʂɃL������`��

}�v���C���[�Ɠ����`����@�Ŏg�p*/
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void ShotBitBlt(SHOT_DATA *pS)	//�@�\�F�e��\������֐�
//�������P�F�\������e�̃f�[�^
{
	int SBmpX;	//�摜����X���W������ 


	if(pS->Son)	//�e�����݂���Ȃ�
	{
		if(pS->mx >= 0)	//�ړ��ʂ�0�ȏ�Ȃ�
			SBmpX = pS->bx + (pS->w * pS->AniCnt) + (pS->w * (pS->AniMax+1));	//�摜��X���W���v�Z
		else			//�ړ��ʂ�0��菬�����Ȃ�
			SBmpX = pS->bx + (pS->w * pS->AniCnt);

		pS->AniCnt++;	//�A�j���[�V�����\���̃J�E���g
		if(pS->AniCnt > pS->AniMax)	pS->AniCnt = 0;	//�A�j���[�V�������Ō�܂ŕ\��������܂��O�ɖ߂�
		
		if(pS->Type != 20)
		{
			MyBltFast(pS->x,pS->y,				//�\����XY���W
			lpDDSOff_Shot,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
			SBmpX,	pS->by,						//�]��������XY���W
			SBmpX + pS->w,	pS->by + pS->h);	//�]�����E��XY���W
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EFBitBlt(EF_DATA *pE)	//�@�\�F�G�t�F�N�g��\������֐�
//�������P�F�\������G�t�F�N�g�̍\����
{
	int SurL;	//�摜�]�����T�[�t�F�[�X�̍�X���W���i�[���Ă����ϐ�
	if(pE->Son)	//�G�t�F�N�g�����݂���Ȃ�
	{
		SurL = pE->bx+(pE->w*pE->AniCnt);	//�]������X���W���v�Z���ĕۑ��i2��ȏ�g�p����̂�
	
		//�`��
		MyBltFast(	pE->x,pE->y,						//�\����XY���W
					lpDDSOff_EF,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
					SurL,	pE->by,						//�]��������XY���W
					SurL + pE->w,	pE->by + pE->h);		//�]�����E��XY���W

	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void OBJBitBlt(OBJ_DATA *pO)	//�@�\�F�I�u�W�F�N�g��\������֐�
//�������P�F�\������I�u�W�F�N�g�̍\����
{
	int SurL;	//�]�����T�[�t�F�[�X�̍�X���W���i�[���Ă������߂̕ϐ�

	if(pO->Son)	//�I�u�W�F�N�g�����݂���Ȃ�
	{
		SurL = pO->bx+(pO->w*pO->AniCnt);	//�]������X���W���v�Z���ĕۑ�
		//�`��
		MyBltFast(	pO->x,pO->y,						//�\����XY���W
					lpDDSOff_OBJ,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
					SurL,	pO->by,	//�]��������XY���W
					SurL + pO->w,	pO->by + pO->h);		//�]�����E��XY���W

	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void BgObjBlt(BGOBJ_DATA *pO)	//�@�\�F�I�u�W�F�N�g��\������֐�
//�������P�F�\������I�u�W�F�N�g�̍\����
{
	int SurL;	//�]�����T�[�t�F�[�X�̍�X���W���i�[���Ă������߂̕ϐ�
//	int AniSpd;	//�A�j���[�V�����X�s�[�h��ω������Ĉ���

	if(pO->Son)	//�I�u�W�F�N�g�����݂���Ȃ�
	{
		pO->AniCnt++;	//�A�j���[�V�����\���̃J�E���g
		if(pO->AniCnt > pO->AniMax)	pO->AniCnt = 0;	//�A�j���[�V�������Ō�܂ŕ\��������܂��O�ɖ߂�
		
		SurL = pO->bx+(pO->w*pO->AniCnt);	//�]������X���W���v�Z���ĕۑ�

		//�`��
		MyBltFast(	pO->x,pO->y,						//�\����XY���W
					lpDDSOff_Back1_OBJ,						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
					SurL,	pO->by,	//�]��������XY���W
					SurL + pO->w,	pO->by + pO->h);		//�]�����E��XY���W

	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void PlrHpBlt()	//�@�\�F�v���C���[��HP��\��
{
	static int PGAcnt;	//HP�Q�[�W�̉��̃A�j���[�V�����J�E���^
	static int SAcnt;	//���̃A�j���̃J�E���^
	
	static int SlowHp;

	if(Plr.Hp < SlowHp)	SlowHp --;
	else	SlowHp = Plr.Hp;

	PGAcnt ++;
	PGAcnt %= 5;
	SAcnt ++;
	SAcnt %= 12;

	//HP�Q�[�W�̘g
	MyBltFast(	0,457,
				lpDDSOff_Text,
				0,0,
				155,23);
	//HP�Q�[�W
	MyBltFast(	29,460,	
			lpDDSOff_Text,
			0,23+PGAcnt*17,
			(int)(Plr.Hp * 124 / Plr.MaxHp),(23+PGAcnt*17)+17);
			//���݂�HP * �Q�[�W�̍ő� / HP�̍ő�

	//���Q�[�W
	MyBltFast(0,472-(int)(Swd.Hp * 92 / Swd.MaxHp),
			lpDDSOff_Text,
			SAcnt*24,112,
			(SAcnt*24)+24,112+(int)(Swd.Hp * 92 / Swd.MaxHp));

}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EneHpBlt(CHR_DATA *pC)	//�@�\�F�G�l�~�[��HP��\������֐�
//�������P�F�G�l�~�[�̃L�����f�[�^
{
	if(pC->Son)	//�w��̃G�l�~�[�����݂���Ȃ�
	{
		//2�x�ȏ�g���̂Ő�Ɍv�Z���đ��
		int Blt_x = pC->x+(pC->w>>1)-32;	//�\���ʒuX
		int Blt_y = pC->y-16;			//�\���ʒuY

		//�g
		MyBltFast(	Blt_x,Blt_y,
					lpDDSOff_Text,
					160,0,
					224,8);
		//�Q�[�W
		MyBltFast(	Blt_x+2,Blt_y+2,
					lpDDSOff_Text,
					162,12,
					162+(int)(pC->Hp * 60 / pC->MaxHp),16);
	}				
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void MapBitBlt()		//�@�\�F�}�b�v��\������֐�
{
	int Xmap = WMoveX/TIP_W;	//���[�v���ŕς��Ȃ��l�͑�����Ă���
	int Ymap = WMoveY/TIP_H;
	int SurL,SurT;				//�摜�]�����T�[�t�F�[�X�̍��[�Ə�[��ۑ����Ă����ϐ��i2��ȏ㓯���v�Z�����邩��
	static int MapAni;
	

	MapAni += (rand()%2);
	MapAni %= 2;

	for(y = 0;y <= WINMAP_H;y++)	//�}�b�v�c
	{
		if((y + WMoveY / TIP_H) >= MapYnum) break;	//���ꂩ��g���v�f�ԍ����z��̗v�f�����I�[�o�[���Ă�����break
		for(x = 0;x <= WINMAP_W;x++)	//�}�b�v��
		{
			if((x + WMoveX / TIP_W) >= MapXnum) break;	//���ꂩ��g���v�f�ԍ����z��̗v�f�����I�[�o�[���Ă�����break

			if(Tip[pMap[((y+Ymap)*MapXnum)+(x+Xmap)]])	//�`�b�v�̎�ނ�TRUE�Ȃ�G��\��
			{	//����pMap�̃f�[�^�𒲂ׂ鎞�́@pMap[(�s * ��̒���) + ���݂̗�̈ʒu)]
				

				SurL = pMap[((y+Ymap)*MapXnum) +(x+Xmap)] % BMPTIP_W * TIP_W;	//�]�������[X���W
				SurT = pMap[((y+Ymap)*MapXnum) +(x+Xmap)] / BMPTIP_W * TIP_H;	//�]������[Y���W

				if(Tip[pMap[((y+Ymap)*MapXnum)+(x+Xmap)]] == 3)
				{	//�}�b�v�\��
					MyBltFast(	x * TIP_W - WMoveX % TIP_W,				//�\����X���W
								y * TIP_H - WMoveY % TIP_H,				//�\����Y���W
								Return_lpDDSOff(),						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X���X�e�[�W�ɂ���ĕύX���邽�߂Ɋ֐��̖ߒl���g��
								SurL+(MapAni*TIP_W),	SurT,							//�]��������XY���W
								SurL + TIP_W + (MapAni*TIP_W),	SurT + TIP_H);			//�]�����E��XY���W
				}else
				{	//�}�b�v�\��
					MyBltFast(	x * TIP_W - WMoveX % TIP_W,				//�\����X���W
								y * TIP_H - WMoveY % TIP_H,				//�\����Y���W
								Return_lpDDSOff(),						//�\������G�̃I�t�X�N���[���T�[�t�F�[�X���X�e�[�W�ɂ���ĕύX���邽�߂Ɋ֐��̖ߒl���g��
								SurL,	SurT,							//�]��������XY���W
								SurL + TIP_W,	SurT + TIP_H);			//�]�����E��XY���W
				}

			}
		}
	}
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LPDIRECTDRAWSURFACE7 Return_lpDDSOff()	//�@�\�F�}�b�v�`�b�v�摜�̃T�[�t�F�[�X���X�e�[�W�ɂ��킹�Ė߂�
{
	switch(StageNum)	//�X�e�[�W�ɂ���ĕ���
	{
	case 0:
		return(lpDDSOff_MapTip);	//�X�̃X�e�[�W�̃T�[�t�F�[�X��߂�
		break;
	case 1:
		return(lpDDSOff_MapTip2);	//�p�Ђ̃X�e�[�W�̃T�[�t�F�[�X��߂�
		break;
	case 2:
		return(lpDDSOff_MapTip2);	//������n�X�e�[�W�̃T�[�t�F�[�X��߂�
		break;
	case 3:
		return(lpDDSOff_MapTip);	//���̃X�e�[�W�̃T�[�t�F�[�X��߂�
		break;
	case 4:
		return(lpDDSOff_MapTip3);	//���J�̃X�e�[�W�̃T�[�t�F�[�X��߂�
	}
	MessageBox(NULL,"�֐� Return_lpDDSOff()","�G���[",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
	return(FALSE);
}
/*
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DIB_EF()		//�@�\�F�Q�S�r�b�gDIB�摜�𑀍삷��֐�
{
	//�����ϐ��錾
	RGBTRIPLE *rgbt2;	//DIB�̐F�f�[�^�����̐擪�A�h���X�������Ƃ�
	int x,y;			//DIB���P�h�b�g�����삷�邽�߂̃J�E���^
	static int ycnt;	//�P���C�����s�N�Z���𑀍삷�邽�߂Ɏg�p
	ycnt++;				//����ꃉ�C�����ω�������͈͂𑝂₷
	
	if(ycnt < 350)		//ycnt��350��菬�����ԂȂ�
	{
		rgbt2 = rgbt;		//DIB�̃s�N�Z���f�[�^�̐擪�A�h���X���R�s�[����
		for(y = 0;y < abs(BmpInfoH.biHeight);y++)
		{
			for(x = 0;x < abs(BmpInfoH.biWidth);x++)
			{
				if(rgbt2->rgbtRed < 255)	rgbt2->rgbtRed++;
				if(rgbt2->rgbtGreen < 255)	rgbt2->rgbtGreen++;
				if(rgbt2->rgbtBlue < 255)	rgbt2->rgbtBlue++;

				rgbt2++;	//���̃s�N�Z����
			}
			if(y > ycnt)	break;	//���[�v���ʂ���
		}
	}
}
*/