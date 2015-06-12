#include "Extern.h"

#include "GameCheckProc.h"

///////////// �v���g�^�C�v�錾 ////////////////////////
void SEvent_0();	//�X�e�[�W�O�̃C�x���g�֐��̃v���g�^�C�v�錾
void SEvent_1();	//�X�e�[�W�P�̃C�x���g�֐��̃v���g�^�C�v�錾
void SEvent_2();	//�X�e�[�W�Q�̃C�x���g�֐��̃v���g�^�C�v�錾
void SEvent_3();	//�X�e�[�W�R�̃C�x���g�֐��̃v���g�^�C�v�錾
void SEvent_4();	//�X�e�[�W�S�̃C�x���g�֐��̃v���g�^�C�v�錾

//���@StageEvent�@������������������������������������������������������������������������������������������
void StageEvent()	//	�@�\�F�e�X�e�[�W�̃C�x���g�������֐�
//	�������F�X�e�[�W
{
	void (*pSEv[5])();	//�ߒl�Ȃ��A�����Ȃ��̊֐��̃|�C���^�z��̐錾
	pSEv[0] = SEvent_0;	//pSEv[0]�ɒ�`�֐�SEvent_0�̐擪�A�h���X����
	pSEv[1] = SEvent_1;
	pSEv[2] = SEvent_2;
	pSEv[3] = SEvent_3;
	pSEv[4] = SEvent_4;

	//��StageNum�̒l�̃X�e�[�W�C�x���g�������s��
	pSEv[StageNum]();	//�֐��̃|�C���^�z��̗v�f�ԍ��iStageNum�j�ɑΉ������֐������s
}
//��������������������������������������������������������������������������������������������������������
//===============================================================================================
void SEvent_0()			//�@�\�F�X�̃X�e�[�W
{
	int i,j;
	static BOOL BossChk;	//�{�X���o���������`�F�b�N
	static int BossDCnt;	//�{�X�����ʂƂ��̃J�E���g
	


	//���t���ς����炷
	if(rand()%5 == 1)	
		ShotFire(640,rand()%480,0,10,10);	//���݂̎�ނ��P�O���ē����蔻����s��Ȃ�
	
	//���{�X�̗̈�ɓ�������߂�Ȃ�����B
	if(WMoveX > (279<<5))
	{
		if(WMoveX < (279<<5)+30 && WorldX < 0)
				WorldX = 0;
	}

	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Type == 3 && En[i].Son)
		{
			for(j = 0;j < OBJ_MAX;j++)
			{
				if(Obj[j].Type == 0 && En[i].AniType != 1)
				{
					//�{�X��X�ړ��ʂ𐧌�
					if(Obj[j].x-400 > En[i].x)
						En[i].x = Obj[j].x-400;
					//�{�X��Y�ړ��ʂ𐧌�
					if(Obj[j].y-300 > En[i].y)
						En[i].y = Obj[j].y-300;
					if(Obj[j].y+300 < En[i].y)
						En[i].y = Obj[j].y+300;
				}
			}
		}
	}

	if(!BossChk)	//�{�X�̏o���`�F�b�N
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 3 && En[i].Son)
			{
				BossChk = TRUE;	//�{�X�o���`�F�b�N
				En[i].Hp -= 250;
			}
		}
	}else	//�{�X�����񂾂�
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 3 && !En[i].Son)
			{
				for(j = 0;j < 30;j++)
				{
					ShotFire(En[i].x+(rand()%En[i].w),En[i].y+(rand()%En[i].h),0,28,1);	//�e�̔���
					BossChk = FALSE;
					BossDCnt = 1;	//�{�X�̃_�E���J�E���g�i�z���C�g�A�E�g
				}
			}
		}
	}
	if(BossDCnt > 0)	//�{�X�̎��񂾂Ƃ��̃J�E���g
	{
		BossDCnt ++;
	
		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < 255)
				SubPal[i].peRed ++;	//�Ԃ̗v�f�����炷			
			if(SubPal[i].peGreen < 255)
				SubPal[i].peGreen ++;	//�΂̗v�f���ւ炷
			if(SubPal[i].peBlue < 255)
				SubPal[i].peBlue ++;		//�̗v�f�����炷
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(BossDCnt > 300)
		{
			GameNum = 4;
			BossDCnt = 0;
			lpDDPal->SetEntries(0,0,255,MainPal);	//�p���b�g�����ɖ߂�
		}
	}
}

//=================================================================================================
void SEvent_1()			//�@�\�F�p�Ђ̃X�e�[�W
{
	int i,j;
	static BOOL BossChk;	//�{�X���o���������`�F�b�N
	static int BossDCnt;	//�{�X�����ʂƂ��̃J�E���g

	//���S�̓I�ɏ��������D��\��
	ShotFire(rand()%640,rand()%240+240,0,24,10);	//�D����

	/*
	for(i = 0;i < BGOBJ_MAX;i++)
	{
		if(BgObj[i].Son && (BgObj[i].Type == 23 || BgObj[i].Type == 24))
		{
			for(j = 0;j < 3;j++)
				ShotFire(BgObj[i].x+(rand()%10),470+(rand()%10),0,24,10);
		}
	}*/

	//���{�X�̗̈�ɓ�������߂�Ȃ�����B
	if(WMoveX > (503<<5))
	{
		if(WMoveX < (503<<5)+30 && WorldX < 0)
				WorldX = 0;
	}

	if(!BossChk)	//�{�X�̏o���`�F�b�N
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 8 && En[i].Son)
			{
				BossChk = TRUE;	//�{�X�o���`�F�b�N
				En[i].Hp = (En[i].MaxHp>>3);
			}
		}
	}else	//�{�X�����񂾂�
	{
		for(i = 0;i < ENE_MAX;i++)
		{
			if(En[i].Type == 8 && !En[i].Son)
			{
				for(j = 0;j < 30;j++)
				{
					ShotFire(En[i].x+(rand()%En[i].w),En[i].y+(rand()%En[i].h),0,28,1);	//�e�̔���
					BossChk = FALSE;
					BossDCnt = 1;	//�{�X�̃_�E���J�E���g�i�z���C�g�A�E�g
				}
			}
		}
	}
	if(BossDCnt > 0)	//�{�X�̎��񂾂Ƃ��̃J�E���g
	{
		BossDCnt ++;
	
		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed < 255)
				SubPal[i].peRed ++;	//�Ԃ̗v�f�����炷			
			if(SubPal[i].peGreen < 255)
				SubPal[i].peGreen ++;	//�΂̗v�f���ւ炷
			if(SubPal[i].peBlue < 255)
				SubPal[i].peBlue ++;		//�̗v�f�����炷
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(BossDCnt > 300)
		{
			GameNum = 4;
			BossDCnt = 0;
			lpDDPal->SetEntries(0,0,255,MainPal);	//�p���b�g�����ɖ߂�
		}
	}
}
//=================================================================================================
void SEvent_2()			//�@�\�F������n�̃X�e�[�W
{

}
//===============================================================================================
void SEvent_3()			//�@�\�F���̃X�e�[�W
{

}
//=================================================================================================
void SEvent_4()			//�@�\�F���J�̃X�e�[�W
{

}
