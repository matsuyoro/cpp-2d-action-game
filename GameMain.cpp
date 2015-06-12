/// �C���N���[�h ///
#include <windows.h>
#include <ddraw.h>

#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "Extern.h"		//�O���ϐ��������w�b�_
#include "BltProc.h"	//�`��֐����܂Ƃ߂��w�b�_
#include "DebugProc.h"	//�f�o�b�N�p�֐����܂Ƃ߂��w�b�_

#include "BackProc.h"		//�w�i�����̊֐��̃v���g�^�C�v�錾�̃w�b�_
#include "StageEventProc.h"	//�e�X�e�[�W�̃C�x���g�������֐��̃w�b�_
#include "GameBltProc.h"	//�L�����̕`��Ȃǂ̊֐��̃v���g�^�C�v�錾�̃w�b�_
#include "GameCheckProc.h"	//����֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
#include "MapProc.h"		//�}�b�v�֘A�̊֐��̃v���g�^�C�v�錾�̃w�b�_
#include "GameChrActProc.h"	//�L�����A�N�V�����֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
#include "EnemyAct.h"		//�G�l�~�[�A�N�V�����֐��̃v���g�^�C�v�錾�̃w�b�_

/*--------------------------------------------------------------------------
	�Q�[���̃��C������
--------------------------------------------------------------------------*/
void	GameMain(int *pGameNum)	//�Q�[���{�҂̊֐�
//�������P�F�Q�[���̏�ʂ������l
{
	//�������ϐ��錾��
	HDC hdc;			//�f�o�C�X�R���e�L�X�g
	DDBLTFX ddbltfx;	//�ʂ�Ԃ��ɕK�v�ȍ\����
	char str[256];		//�����������

	HPEN hPen;			//�쐬�����y��������
	HPEN hPenOld;		//�Â��y����ۑ�����

	int i,j;			//�J�E���^
	int HitWaza;		//�v���C���[���G�l�~�[�ɓ��Ă��Z��������
	static int Tengen;	//�v���C���[�c���̓_�ł���̂Ɏg�p
	int RndNum;			//�����������ϐ�
	static int DamageEneNum = -1;	//�_���[�W���󂯂��G�l�~�[�̔ԍ������Ă����ϐ�

	
	//���Q�[���̃f�[�^������

	WorldX = 0;	//�X�N���[���ʂ𖈉�O�ɖ߂�
	WorldY = 0;

	Tengen++;	//����{���ĂO�ƂP���J��Ԃ�(�L�����_�łȂǂŎg���j
	Tengen %= 2;

	if(Muteki > 0)
	{
		Muteki--;
		if(Muteki == 0)	Plr.HitD = 0;
	}

	for(i = 2;i > 0;i--)	//Plr���R�s�[���Ďc�������B
		Dum[i] = Dum[i-1];
	Dum[0] = Plr;


	Plr.Atk = Swd.Hp>>2;	//�v���C���[�̍U���͂͌���Hp�Ō��܂�


	//�K���G���A�O�ɏo����G������
	for(i = 0;i < ENE_MAX;i++)	//�G�l�~�[�̐������J��Ԃ�
	{
		if(En[i].Son)	//�G�l�~�[�����݂�����
		{			
			if(En[i].x+En[i].w + WMoveX +32 > ((MapXnum)*TIP_W) || En[i].x+WMoveX < 1+32
			|| En[i].y+En[i].h + WMoveY +32 > ((MapYnum)*TIP_H) || En[i].y+WMoveY < 1+32)	//�X�e�[�W�͈͊O�i�]����32�s�N�Z���{�j�ɂł���
			{
				En[i].Son = FALSE;	//�G�l�~�[������
			}
		}
	}

	//�G���A�O�ɂł��猕���h��
	if(Swd.Son)	//�������݂���Ȃ�
	{

		if(Swd.x+Swd.w + WMoveX + 32 > ((MapXnum)*TIP_W) || Swd.x+WMoveX < 1 +32
		|| Swd.y+Swd.h + WMoveY + 32 > ((MapYnum)*TIP_H) || Swd.y+WMoveY < 1 +32)	//�X�e�[�W�͈͊O�i�]���ɏc��32�s�N�Z���{�j�ɏo����
		{
			Swd.HitA = TRUE;
		}
	}

	//���G�l�~�[�o��
	EnemyOnPos();	//�G�l�~�[���w��̏ꏊ�ɏo��������


	//���L�����A�N�V����
	if(Plr.Son)					//�v���C���[�����݂���Ȃ�
		PlrAction(&Plr,&Anime[Plr.AniType][Plr.AniNum]);	//�v���C���[�A�N�V�����̊֐�
	if(Swd.Son && !Swd.HitA)	//�������݂��h�����Ă��Ȃ�������
		SwdAction(&Swd,&AniSwd[Swd.AniType][Swd.AniNum]);	//���̃A�N�V�����֐�
	EnAction();		//�G�l�~�[�A�N�V�����֐�



	if(CmdGet == 0)	//�R�}���h����͂�����
		Plr.y = 50;

	//���e�̈ړ�
	ShotMove(0,0);	//�e�̈ړ�

	//���G�t�F�N�g�̃A�j���[�V����������
	EFOFF(EF);	//���݂��Ă���G�t�F�N�g�̃A�j���[�V�����Ƒ��݂������֐�

	//���������������@����Ȃǁ@��������������


	if(!Plr.HitD && !Muteki)
	{
		for(i = 0;i < ENE_MAX;i++)	//�G�l�~�[�̐������J��Ԃ�
		{
			if(En[i].Son && Plr.Son)	//������s���L�������m�����݂�����
			{
				ChrHitChk(&Plr,&En[i]);		//�v���C���[�ƓG�̓����蔻��
				if(Plr.HitD)	break;		//�U�����󂯂���TRUE�i���[�v�I��
			}
		}
	}	

	for(i = 0;i < SHOT_MAX;i++)	//�e�̍ő吔���J��Ԃ�
	{
		if((Shot[i].Son == 1 || Shot[i].Son == 3) && (!Plr.HitD && !Muteki))	//�e�̑��݂��P�Ȃ�e�ƃv���C���[�̔���
		{
			ShotHitChk(&Shot[i],&Plr);			//�e�ƃv���C���[�̓����蔻��
			if(Plr.HitD)	break;				//�ꔭ������Δ�����
		}
	}


	//�v���C���[�̍U���͈͂ƃG�l�~�[�̂����蔻��
	for(i = 0;i < ENE_MAX;i++)	//�G�l�~�[�̐������J��Ԃ�
	{
		if(En[i].Son && Plr.Son)	//������s���L�������m�����݂�����
		{
			if(En[i].HitD == 0)
			{
				HitWaza = AtkHitChk(&Plr,&En[i]);	//���v���C���[�̍U���ƓG�̓����蔻��

				if(!HitWaza)	//HitWaza���O�Ȃ��̍U���̔����D��i�����ɒe�ƍU���̓��蔻����s��Ȃ��悤��
				{
					for(j = 0;j < SHOT_MAX;j++)				//�e�̍ő吔���J��Ԃ�
					{	
						if(Shot[j].Son == 2 || Shot[j].Son == 3)					//�e�̑��݂��Q�Ȃ�e�ƓK�̔���
						{
							HitWaza = ShotHitChk(&Shot[j],&En[i]);	//���e�̓K�̓����蔻��
							if(En[i].HitD)	break;	//�ꔭ������Δ���͏I��
						}
					}
				}
				if(HitWaza)	DamageEneNum = i;		//�_���[�W���󂯂��G�l�~�[�̔ԍ������i�G�l�~�[��HP�\�����Ɏg�p
				if(!En[i].Son) DamageEneNum = -1;	//���̔ԍ��̓K���o�����ɃQ�[�W���\������Ȃ��悤�ɁA���񂾂�\�����Ȃ�
			}

			if(!(En[i].Son))					//�v���C���[�Ƃ̓����蔻���G�l�~�[�����݂��ĂȂ�������(�|������
			{	
				//�K�����ʂƓ����Ɏ��̌����o��������
				for(j = 0;j < EnemyNum[En[i].Type].Hp ;j++)	//���ʃG�l�~�[�̎�ނ�MAXHP�̐����������o��������
					ShotFire(En[i].x+(rand()%En[i].w)-4,En[i].y+(rand()%En[i].h)-4,0,17,1);

				if(HitWaza == 1)		//���Ă��U�������a��Ȃ�
					En[i].Hp = -99;			//�G�l�~�[Hp�𑀍삵�āA�G�̂����G��ς���
				else if(HitWaza == 2)	//���Ă��U�����c�a��Ȃ�
					En[i].Hp = -199;		//�G�l�~�[Hp�𑀍삵�āA�G�̂����G��ς���
			}
		}
	}

	StageEvent();	//���e�X�e�[�W�̃C�x���g�֐�

	//���w�i�̒n�ʂ̃X�N���[��
	BGScrX += (double)WorldX/10;	//�X�N���[���ʂɂƔ�Ⴕ�Ĕw�i�̃X�N���[�����x�ω�������

	//��X�����X�N���[��
	ChrXScroll();		//X�����̃X�N���[��
	WMoveX += WorldX;	//�}�b�v�̃X�N���[���l�ɍ����X�X�N���[���ʂ𑫂�

	//���}�b�v�̃L�����̓����蔻��
	if(Plr.Son)	MapChk(&Plr);				//�v���C���[�ƃ}�b�v�̓����蔻��
	
	if(Swd.Son && !Swd.HitA)				//�������݂��A�ǂɓ������ĂȂ�������
		MapChk(&Swd);							//���ƃ}�b�v�̓����蔻��

	for(i = 0;i < ENE_MAX;i++)				//�G�l�~�[�����݂�����}�b�v�Ɠ����蔻��
		if(En[i].Son && En[i].Type != 3 && En[i].Type != 10)
			MapChk(&En[i]);			//�G�l�~�[�ƃ}�b�v�̓����蔻��


	if(Plr.Hp < 1 && Plr.AniType == 8)		//Hp���P��肿������������
		*pGameNum = 2;



	//�������������� �`�� ������������
	//�ʂ�Ԃ��i���j
	ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
	ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);

	BGBlt();					//���w�i�\��
	MapBitBlt();				//���}�b�v��\��

	if(!(Plr.Son))	//�v���C���[�����݂��Ȃ��Ȃ�����
	{
		for(i = 0;i < ENE_MAX;i++)	//�G�L������S�����݂����Ȃ�����
		{
			En[i].Son = FALSE;			//���݂�FALSE��
		}
		//�w�i��^�����ɂ���
		ddbltfx.dwSize = sizeof(ddbltfx);
		ddbltfx.dwFillColor = 0;			//�p���b�g�O�Ԃ�
		lpDDSBackBuffer->Blt(NULL,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&ddbltfx);
	}


	//�L�����̎c����\��
	if(Plr.Son || Plr.AniType == 8)	//�v���C���[�����݂��邩�A����Ă���A�j���[�V���������Ă���ꍇ�̂ݕ\��
	{
		for(i = 2;i >= 0;i--)	//�c���̐������J��Ԃ�
		{
			//���c���\��
			if(Tengen)	//�_�Ńt���O���P�̎������\��
				ChrBitBlt(&Dum[i],&Anime[Dum[i].AniType][0],CharAnime(&Dum[i],&Anime[Dum[i].AniType][Dum[i].AniNum-1],&Anime[Dum[i].AniType][Dum[i].AniNum]));		//�v���C���[�\��
		}

		//���v���C���[�\��
		if(!Muteki)	//���G���Ԃ���Ȃ��Ȃ�
		{
			ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//�v���C���[�\��
		}else if(Tengen)	//���G���ԓ��Ȃ�
			ChrBitBlt(&Plr,&Anime[Plr.AniType][0],CharAnime(&Plr,&Anime[Plr.AniType][Plr.AniNum],&Anime[Plr.AniType][Plr.AniNum+1]));		//�v���C���[�\��

	}

	//���\��
	if(Swd.Son)	//�������݂�����
		SwdBitBlt(&Swd,&AniSwd[Swd.AniType][0],CharAnime(&Swd,&AniSwd[Swd.AniType][Swd.AniNum],&AniSwd[Swd.AniType][Swd.AniNum+1]));		//���\��

	//�I�u�W�F�N�g�\��
	for(i = 0;i < OBJ_MAX;i++)
		OBJBitBlt(&Obj[i]);	//�I�u�W�F�\���֐����s

	//���G�\��
	for(i = 0;i < ENE_MAX;i++)	//�G�̐������J��Ԃ�
	{

		if(En[i].Son)		//�G[i]�����݂�����
		{
			/*
			if(Tengen)
			{
				if(En[i].HitD == 1)		//���a��_���[�W�������Ă���Ȃ�
					DamageX_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//�G�l�~�[�\��
				else if(En[i].HitD == 2)	//�c�a��Ń_���[�W�������Ă���Ȃ�
					DamageY_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//�G�l�~�[�\��			
			}*/	
			//if(!En[i].HitD)	//�ʏ�ǂ���Ȃ�
				ChrBitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//�G�l�~�[�\��
			//else if(Tengen)	//�_���[�W���󂯂Ă���Ȃ�
				//ChrBitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],CharAnime(&En[i],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum],&AniEn[En[i].Type][En[i].AniType][En[i].AniNum+1]));	//�G�l�~�[�\��
		}

		if(!En[i].Son && Tengen && En[i].Hp < 0)	//�G�����݂��Ă��Ȃ��āA�_�Ńt���O���P�ŁA�̗͂��O��菬����������(����鎞�ɃG�l�~�[��HP��-99��-199�ɂȂ�
		{
			En[i].Hp ++;	//�O�ɂȂ�܂Ŗ���{�iHp���g���ăG�l�~�[�̂��؂�铮��������
			if(En[i].Hp > -100 && En[i].Hp <= -75)	//Hp�̒l���g���ăG�l�~�[�̂�����𕪂���
			{ 	//�L���������ɐ؂��G��\��
				Kill_X_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],En[i].AniNum,En[i].Hp+100);	//�G�l�~�[����\��
				if(En[i].Hp >= -75)	En[i].Hp = 0;	//-75���傫���Ȃ�����Hp���O��	
			}else if(En[i].Hp > -200 && En[i].Hp <= -175)
			{	//�L�������c�ɐ؂��G��\��
				Kill_Y_BitBlt(&En[i],&AniEn[En[i].Type][En[i].AniType][0],En[i].AniNum,En[i].Hp+200);	//�G�l�~�[����\��
				if(En[i].Hp >= -175) En[i].Hp = 0;	//-175���傫���Ȃ�����Hp���O��
			}
		}
	}

	for(i = 0;i < SHOT_MAX;i++)	//�e�̐������J��Ԃ�
		ShotBitBlt(&Shot[i]);		//���e�\��
	for(i = 0;i < EF_MAX;i++)	//�G�t�F�N�g�̐������J��Ԃ�
		EFBitBlt(&EF[i]);			//���G�t�F�N�g�\��
	
	PlrHpBlt();						//���v���C���[��HP��\��
	if(DamageEneNum >= 0)	EneHpBlt(&En[DamageEneNum]);	//���_���[�W���󂯂��G�l�~�[��HP��\��

	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	lpDDSBackBuffer->GetDC(&hdc);


	//���e�L�X�g�\����
	

	//�v���C���[�̍U�������蔻��͈̔͂�\�����̐ݒ�
	hPen = CreatePen(PS_SOLID,1,RGB(0,255,0));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B
	
	//�v���C���[�̍U���͈͂�\���l�p��`��
	if(Plr.HitA)	//�v���C���[�U�����̓����蔻�蕔����\��
	{
		MoveToEx(hdc,xbox,ybox,NULL);
		LineTo(hdc,xbox+wbox,ybox);
		LineTo(hdc,xbox+wbox,ybox+hbox);
		LineTo(hdc,xbox,ybox+hbox);
		LineTo(hdc,xbox,ybox);
	}

	SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
	DeleteObject(hPen);				//�쐬�����y���̍폜

	//�����̔j�Ђ�\��
	RndNum = rand()%255;

	if(Plr.AniType == 19)	//�v���C���[�����j�Ћz���A�j���Ȃ�	
		hPen = CreatePen(PS_SOLID,rand()%7+2,RGB(255,RndNum,RndNum));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
	else					//��������Ȃ��Ȃ�
		hPen = CreatePen(PS_SOLID,rand()&5,RGB(255,RndNum,255));
	hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B

	for(i = 0;i < SHOT_MAX; i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)
		{
			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);
		}
	}

	SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
	DeleteObject(hPen);				//�쐬�����y���̍폜

	//�����\��
	SetBkColor(hdc,RGB(255,0,0));			//�����̃o�b�N�J���[�̎w��
	SetTextColor(hdc,RGB(255,255,255));		//�����F�̎w��
	SetBkMode(hdc,TRANSPARENT);				//�����𓧖��ɂ���
/*
	
	wsprintf(str,"Nage = %d",Nage);
	TextOut(hdc,100,140,str,lstrlen(str));

	wsprintf(str,"%d",BtnCnt);
	TextOut(hdc,200,150,str,lstrlen(str));


	//WMoveX�\��(�X�N���[�������ʁj
	wsprintf(str,"WMoveX [%d]  WMove [%d]",WMoveX,WMoveY);
	TextOut(hdc,320,5,str,lstrlen(str));

	//�v���C���[Hp�\��
	wsprintf(str,"Hp %d    ",Plr.Hp);
	TextOut(hdc,Plr.x,Plr.y-15,str,lstrlen(str));

	//�G�l�~�[Hp�\��
	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Son)
		{
			wsprintf(str,"Hp %d    ",En[i].Hp);
			TextOut(hdc,En[i].x,En[i].y-12,str,lstrlen(str));
		}
	}

	wsprintf(str,"EneMax %d:%d:%d:%d",EneOnPos_Max.x,EneOnPos_Max.y,EneOnPos_Max.type,EneOnPos_Max.OnFlag); 
	TextOut(hdc,240,200,str,lstrlen(str));

	//wsprintf(str,"Eneon %d:%d:%d:%d",pEneOn[0].x,pEneOn[0].y,pEneOn[0].type,pEneOn[0].OnFlag); 
	//TextOut(hdc,240,200,str,lstrlen(str));


	wsprintf(str,"%d  :waza = %d",AllCnt,CmdGet);
	TextOut(hdc,100,80,str,lstrlen(str));
*/

	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);
	//DrawFrameRate(lpDDSBackBuffer,0,0);					//�t���[�����[�g��\������֐�

}