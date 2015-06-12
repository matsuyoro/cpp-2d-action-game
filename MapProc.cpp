
#include "Extern.h"		//�O���ϐ��̃w�b�_
#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_

#include "GameCheckProc.h"	//����֐��Ȃǂ̃v���g�^�C�v�錾
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void MapChk(CHR_DATA *pC)	//�@�\�F�z��}�b�v�ƃL�����̓����蔻��
//�������P�F�}�b�v�Ɠ����蔻�肷��CHR_DATA�^�\����
{
	int left,top,right,bottom;			//�S�_�������Ă����ϐ�
	int centerX[10],centerY[10];		//�p�Ɗp�̓_�̊Ԃ̓_�������z��(�R�Q�O���R�Q�O�̃T�C�Y�L�����܂őΉ��j
	int Hx,Hy,Hw,Hh;					//�����蔻��̕����̂�����
	int i;								//�J�E���^

	pC->Land = 0;		//�n�ʂɑ��������Ă��邩���肷�邽�߂ɂ܂��͒����ĂȂ����Ƃɂ���				

	//�@X�����̈ړ�

	if((pC->MoveChkX != pC->x) || WorldX)	//X������ �L��������������܂��̓X�N���[��������
	{
		Hx = pC->x + (pC->w>>1) - (pC->Hit.w>>1);	//�����蔻�蕔���̍���x���W
		Hy = pC->y + (pC->h>>1) - (pC->Hit.h>>1);	//�����蔻�蕔���̍���y���W
		Hw = pC->Hit.w;								//�����蔻�蕔���̕�
		Hh = pC->Hit.h;								//�����蔻�蕔���̍���
		//����O�Ƀf�[�^���X�V
		left = (Hx+WMoveX)/TIP_W;
		top = (Hy+WMoveY)/TIP_H;
		right = (Hx+WMoveX+Hw-1)/TIP_W;
		bottom = (Hy+WMoveY+Hh-1)/TIP_H;
	
		//�L�����̃T�C�Y�ɂ��킹�ē����蔻��̓_�̐����v�Z����B
		for(i = 0;i < (Hw/TIP_W);i++)		//�L������ / �`�b�v���̐������J��Ԃ�
			centerX[i] = (Hx+WMoveX+((Hw/(Hw/TIP_W+1))*(i+1))-1)/TIP_W;	//�p�̓_�Ɠ_�̊Ԃ̓_���v�Z�œ_�������z��ɑ��
		for(i = 0;i < (Hh/TIP_H);i++)		//�L�������� / �`�b�v�����̐������J��Ԃ�
			centerY[i] = (Hy+WMoveY+((Hh/(Hh/TIP_H+1))*(i+1))-1)/TIP_H;	//�p�̓_�Ɠ_�̊Ԃ̓_���v�Z�œ_�������z��ɑ��
	
		//�AX�����̔���
		if(Tip[pMap[(top*MapXnum)+left]] == 1)		//����
		{
			Hx = (left+1)*TIP_W-WMoveX;		//�������Ă�����A���������`�b�v�̂P�E�Ɉړ�
			pC->Land = 3;
		}
		if(Tip[pMap[(top*MapXnum)+right]] == 1)		//�E��
		{
			Hx = right*TIP_W-Hw-WMoveX;		//�������Ă�����A���������`�b�v�̃L����1�l�����ֈړ�
			pC->Land = 4;
		}
		if(Tip[pMap[(bottom*MapXnum)+left]] == 1)	//����
		{
			Hx = (left+1)*TIP_W-WMoveX;		//�������Ă�����A���������`�b�v�̂P�E�Ɉړ�
			pC->Land = 3;
		}
		if(Tip[pMap[(bottom*MapXnum)+right]] == 1)	//�E��
		{
			Hx = right*TIP_W-Hw-WMoveX;		//�������Ă�����A���������`�b�v�̃L����1�l�����ֈړ�
			pC->Land = 4;
		}
		for(i = 0;i < (Hw/TIP_W);i++)		//centerX�̓_�������z������ׂĔ���
		{
			if(Tip[pMap[(top*MapXnum)+centerX[i]]] == 1)		//������
			{
				Hx = (centerX[i]+1)*TIP_W-WMoveX;		//�`�b�v�̉E�Ɉړ�
				pC->Land = 3;
			}
			if(Tip[pMap[(bottom*MapXnum)+centerX[i]]] == 1)	//������
			{
				Hx = centerX[i]*TIP_W-Hw-WMoveX;		//�`�b�v�̍��Ɉړ�
				pC->Land = 4;
			}
		}

		for(i = 0;i < (Hh/TIP_H);i++)		//centerY�̓_�������z������ׂĔ���
		{
			if(Tip[pMap[(centerY[i]*MapXnum)+left]] == 1)		//������
			{
				Hx = (left+1)*TIP_W-WMoveX;			//�`�b�v�̉E�Ɉړ�
				pC->Land = 3;
			}
			if(Tip[pMap[(centerY[i]*MapXnum)+right]] == 1)	//�����E
			{
				Hx = right*TIP_W-Hw-WMoveX;			//�`�b�v�̍��Ɉړ�
				pC->Land = 4;
			}
		}
		pC->x = Hx+(Hw>>1)-(pC->w>>1);	//�}�b�v�Ɠ����蔻�肵�Ĉړ��������ʂ̃f�[�^���L���������W�ɑ��
	}
	//�By�����̈ړ�
	if(pC->Type != -2)	//�L�����̎�ނ�-2�i���j����Ȃ��Ȃ�
		UpDownChk(pC);	//�㏸�A���~�Ȃǂ̂������̈ړ�
	
	if(pC->Type == -1 && Swd.Son && Swd.HitA)	//�L�����̎�ނ�-1�i�v���C���[�j�Ȃ�
		PlrSwdChk(pC,&Swd);	//�v���C���[�ƌ��̓����蔻��


	if(pC->MoveChkY != pC->y || WorldY)	//Y������ �L��������������܂��̓X�N���[��������
	{
	//Y�����̃}�b�v�`�b�v�Ƃ̂����蔻��
		Hx = pC->x + (pC->w>>1) - (pC->Hit.w>>1);				//�����蔻�蕔���̍���x���W
		Hy = pC->y + (pC->h>>1) - (pC->Hit.h>>1);				//�����蔻�蕔���̍���y���W
		Hw = pC->Hit.w;						//�����蔻�蕔���̕�
		Hh = pC->Hit.h;						//�����蔻�蕔���̍���

		//����O�Ƀf�[�^���X�V
		left = (Hx+WMoveX)/TIP_W;
		top = (Hy+WMoveY)/TIP_H;
		right = (Hx+WMoveX+Hw-1)/TIP_W;
		bottom = (Hy+WMoveY+Hh-1)/TIP_H;
	
		for(i = 0;i < (Hw/TIP_W);i++)	//�L������ * �`�b�v���̐������J��Ԃ�
			centerX[i] = (Hx+WMoveX+((Hw/(Hw/TIP_W+1))*(i+1))-1)/TIP_W;	//�p�̓_�Ɠ_�̊Ԃ̓_���v�Z�œ_�������z��ɑ��
		for(i = 0;i < (Hh/TIP_H);i++)	//�L�������� * �`�b�v�����̐������J��Ԃ�
			centerY[i] = (Hy+WMoveY+((Hh/(Hh/TIP_H+1))*(i+1))-1)/TIP_H;	//�p�̓_�Ɠ_�̊Ԃ̓_���v�Z�œ_�������z��ɑ��
	
		//�Cy�����̔���
		if(Tip[pMap[(top*MapXnum)+left]] == 1)		//��
		{
			Hy = (top+1)*TIP_H-WMoveY;		//�������Ă�����A���������`�b�v�̂P���Ɉړ�
			pC->Land = 2;					//�V��ɓ��������̂łQ
		}
		if(Tip[pMap[(top*MapXnum)+right]] == 1)	//�E��
		{
			Hy = (top+1)*TIP_H-WMoveY;		//�������Ă�����A���������`�b�v�̂P���Ɉړ�
			pC->Land = 2;					//�V��ɓ��������̂łQ
		}
		if(Tip[pMap[(bottom*MapXnum)+left]] == 1)	//����
		{
			Hy = bottom*TIP_H-Hh-WMoveY;		//�������Ă�����A���������`�b�v�̃L����1�l����ֈړ�
			pC->Land = 1;						//�n�ʂɑ����������̂łP
		}

		if(Tip[pMap[(bottom*MapXnum)+right]] == 1)	//�E��
		{
			Hy = bottom*TIP_H-Hh-WMoveY;		//�������Ă�����A���������`�b�v�̃L����1�l����ֈړ�
			pC->Land = 1;
		}
		for(i = 0;i < (Hh/TIP_H);i++)		//centerY�̓_�������z������ׂĔ���
		{
			if(Tip[pMap[(centerY[i]*MapXnum)+left]] == 1)		//������
			{
				Hy = (centerY[i]+1)*TIP_H-WMoveY;		//�`�b�v�̉��ɖ߂�
				pC->Land = 2;
			}
			if(Tip[pMap[(centerY[i]*MapXnum)+right]] == 1)	//�E����
			{
				Hy = centerY[i]*TIP_H-Hh-WMoveY;		//�`�b�v�̏�ɖ߂�
				pC->Land = 1;
			}
		}
		for(i = 0;i < (Hw/TIP_W);i++)		//centerX�̓_�������z������ׂĔ���
		{
			if(Tip[pMap[(bottom*MapXnum)+centerX[i]]] == 1)	//������
			{
				Hy = bottom*TIP_H-Hh-WMoveY;			//�`�b�v�̏�ɖ߂�
				pC->Land = 1;
			}	
			if(Tip[pMap[(top*MapXnum)+centerX[i]]] ==1)		//�㒆��
			{
				Hy = (top+1)*TIP_H-WMoveY;				//�`�b�v�̉��ɖ߂�
				pC->Land = 2;
			}
		}
		pC->y = Hy+(Hh>>1)-(pC->h>>1);	//�}�b�v�Ɠ����蔻�肵�Ĉړ��������ʂ��L�����̂����W�ɑ��
	}

	pC->MoveChkX = pC->x;		//���̂��̊֐������s����Ƃ��ɕK�v�ȃf�[�^��ۑ�
	pC->MoveChkY = pC->y;

	if(pC->Type != -2)	//�����̃L���������ȊO�Ȃ�
	{
		if(pC->Land == 1 | pC->Land == 2)	//����Œn�ʂ��V��ɂ��Ă�����
		{
			pC->U = 0;	//�d�͂ɂ��ړ��ʂ��O��
		}
	}else	//���Ȃ�
	{
		if(pC->Land)	//���̃����oLand���O�ȊO�Ȃ�i�}�b�v�ɓ������Ă���Ȃ�
		{
			pC->HitA = TRUE;	//�������������̂�TRUE�ɂ���
			switch(pC->Land)
			{
			case 1:	//���Ɏh��������
				if(pC->muki == 4)	
					pC->y += 20;	//�������ɂ��炵�Ďh��
				break;
			case 2:	//��Ɏh��������
				if(pC->muki == 2)
					pC->y -= 20;	//������ɂ��炵�Ďh��
				break;
			case 3:	//���Ɏh��������
				if(pC->muki == 1)
					pC->x -= 20;	//�������ɂ��炵�Ďh��
				break;
			case 4:	//�E�Ɏh��������
				if(pC->muki == 3)
					pC->x += 20;	//�����E�ɂ��炵�Ďh��
				break;
			}
		}
	}
}