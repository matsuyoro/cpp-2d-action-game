
#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
#include "BltProc.h"
#include "GameCheckProc.h"
///////////// �v���g�^�C�v�錾 ////////////////////////
void Title_01();	//�^�C�g���̉�ʂ̃C�x���g�����𕪂��鏈���̊֐��i�f�ʋ@
void Title_02();	//���S
//void StageSetUp_2();	//�X�e�[�W�Q���͂��߂邽�߂̏����̊֐��̃v���g�^�C�v�錾

//��GameTitle��������������������������������������������������������������
void GameTitle(int *pGameNum)	//	�@�\�F�^�C�g����ʂ̏���
//	�������F�Q�[���̏�ʂ������l
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	char str[256];			//�����������
	static int TitleCnt;
	static int TitleNum;	//�^�C�g���̂��낢��ȏ�ʂ������ԍ�
	static int GameStartCnt ;	//�Q�[���X�^�[�g���̃t�F�[�h�A�E�g�J�E���g
	int i;

	void (*pTitle[2])();	//�ߒl�Ȃ��A����int�^�|�C���^�̊֐��̃A�h���X�́A�֐��̃|�C���^�z��̐錾
	pTitle[0] = Title_01;	//pTitle[0]�ɒ�`�֐�Title_01�̐擪�A�h���X����
	pTitle[1] = Title_02;	//�֐�Title_02�̐擪�A�h���X����

	TitleCnt++;

	if(TitleCnt > 3000	//�^�C�g���J�E���g��1000�𒴂�����
	|| (!(Btn2 & (1<<1)) && (Btn1 & (1<<1)))	//B�{�^����O��i���j�Ō��݁i���j�Ȃ� 
	)
	{
		
		if(TitleCnt > 540)
			GameStartCnt = 1;	//�t�F�[�h�A�E�g���ăQ�[���X�^�[�g
		else
			*pGameNum = 1;	//�ԐڎQ�Ƃ�GameNum���P�i�Q�[���{�ҁj�ɂ���B

	}
	if(GameStartCnt)	//GameStartCnt��TRUE�Ȃ�
	{
		GameStartCnt ++;	//����{�P

		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���f�N�������g���A�O�i���j�ɋ߂Â�����
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed > 0)
				SubPal[i].peRed --;	//�Ԃ̗v�f�����炷			
			if(SubPal[i].peGreen > 0)
				SubPal[i].peGreen --;	//�΂̗v�f���ւ炷
			if(SubPal[i].peBlue > 0)
				SubPal[i].peBlue --;		//�̗v�f�����炷
		}
		lpDDPal->SetEntries(0,0,255,SubPal);

		if(GameStartCnt >= 255)	//255�ȏ�ɂȂ�����Q�[���{�҂ɐ؂�ւ�
		{	
			*pGameNum = 1;	//�ԐڎQ�Ƃ�GameNum���P�i�Q�[���{�ҁj�ɂ���B
		}
	}

	if(TitleCnt < 100)
		TitleNum = 0;
	else
		TitleNum = 1;
	pTitle[TitleNum]();	//�֐��̃|�C���^�z��̗v�f�ԍ��iSlctNum�j�ɑΉ������֐������s


	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	lpDDSBackBuffer->GetDC(&hdc);

	//�����\��
	SetBkColor(hdc,RGB(255,0,0));			//�����̃o�b�N�J���[�̎w��
	SetTextColor(hdc,RGB(255,255,255));		//�����F�̎w��
	SetBkMode(hdc,TRANSPARENT);				//�����𓧖��ɂ���
	wsprintf(str,"title_______%d",TitleCnt);
	TextOut(hdc,100,140,str,lstrlen(str));

//	wsprintf(str,"TBGC %d",TitleBGClr);
//	TextOut(hdc,100,180,str,lstrlen(str));

	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);

	if(*pGameNum == 1)			
		lpDDPal->SetEntries(0,0,255,MainPal);	//�p���b�g�����ɖ߂�

}
//===========================================================================================
void Title_01()	//�f�ʋ@��\�����鏈��
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	int i;

	DDBLTFX ddbltfx;	//�ʂ�Ԃ��ɕK�v�ȍ\����
	HPEN hPen;			//�쐬�����y��������
	HPEN hPenOld;		//�Â��y����ۑ�����

	static int LineX,LineY;
	int rndLX;
	static int TitleBGClr;	//�^�C�g���̔w�i�F������
	static int TBGC_time;	//�^�C�g���w�i�F�̐F����莞�Ԃ��ƂɕύX(�ڂɈ�����������

	TBGC_time ++;	//�J�E���g
	if(TBGC_time > (7-(rand()%4)) )	//�J�E���g�����̎��Ԃ𒴂���ƃ^�C�g���w�i�F��ύX
	{
		TitleBGClr = (rand()%5)+6;
		TBGC_time = 0;
	}

	//�ʂ�Ԃ��i���j
	ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
	ddbltfx.dwFillColor = TitleBGClr;				//�ʂ�Ԃ��F���w��
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);


	//�`��
	if(rand()%5 == 1)
	{
		//���݂�\��
		MyBltFast(	140,200,	//�\����XY���W
				lpDDSOff_Text,	//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
				128,	24,		//�]��������XY���W
				136,	32);	//�]�����E��XY���W
		MyBltFast( 400,320,
				lpDDSOff_Text,
				128,	32,
				136,	40);
		MyBltFast(580,20,
				lpDDSOff_Text,
				128,	40,
				136,	48);
		MyBltFast(210,87,
				lpDDSOff_Text,
				128,	48,
				136,	64);
	}
	for(i = 0;i < 10;i++)
	{
		MyBltFast(rand()%640,rand()%480,
					lpDDSOff_Text,
					128,	32,
					129,	33);
	}		

	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	lpDDSBackBuffer->GetDC(&hdc);



	//�v���C���[�̍U�������蔻��͈̔͂�\�����̐ݒ�
	hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B
	
	for(i = 0;i < 8;i++)
	{
		//�v���C���[�̍U���͈͂�\���l�p��`��
		if(rand()%7 == 1)	//�v���C���[�U�����̓����蔻�蕔����\��
		{
			rndLX = rand()%640;
		
			if(rand()%2 == 1)
			{
				MoveToEx(hdc,rndLX,0,NULL);
				LineTo(hdc,rndLX,rand()%480);
			}else
			{
				MoveToEx(hdc,rndLX,rand()%480,NULL);
				LineTo(hdc,rndLX,480);
			}
		}
	}

	LineX += (rand()%4)-1;
	if(LineX < 0) LineX = rand()%640;
	if(LineX > 640) LineX = rand()%640;

	LineY -= (rand()%4)-2;
	if(LineY < 0)	LineY = rand()%480;
	if(LineY > 480) LineY = rand()%480;

	if(rand()%30 == 1)	LineX = rand()%640;

	if(rand()%2 == 1)
	{
		for(i = 0;i < 2;i++)
		{
			MoveToEx(hdc,LineX+(i*40),0,NULL);
			LineTo(hdc,LineX+(i*40),rand()%480);

			MoveToEx(hdc,LineX+(i*40),rand()%480,NULL);
			LineTo(hdc,LineX+(i*40),480);
		}
	}

	SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
	DeleteObject(hPen);				//�쐬�����y���̍폜

	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);

}
//=============================================================================================
void Title_021()	//�^�C�g�����S
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	int i,j;
	static int SlctMenu;	//�^�C�g���̃��j���[�I���Ŏg�p
	static int TitleCnt02;
	int RndMenu;

	DDBLTFX ddbltfx;	//�ʂ�Ԃ��ɕK�v�ȍ\����
	HPEN hPen;			//�쐬�����y��������
	HPEN hPenOld;		//�Â��y����ۑ�����

	int	RndNum = rand()%255;
	static int LineMove;	//���̓����̎�ނ�����

	TitleCnt02 ++;
	if(TitleCnt02 > 500) TitleCnt02 = 0;

	//�㉺�Ń��j���[�I��
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;

	//���j���[�̔ԍ��Ɍ��E����������
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;

	if(rand()%20 == 1)
		LineMove = rand()%4;	//�����_���Ő��̓�����ς���

	if(LineMove == 0)
	{
		for(i = 0;i < 10;i++)
		{
			ShotFire(rand()%640,rand()%480,0,19,2);
			ShotFire(rand()%640,rand()%480,0,19,1);
		}
	}
	//���e�̈ړ�

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//�e�̎�ނ�20�ŁA���݂���Ȃ�
		{
		
			if(Shot[i].Son && LineMove == 0)
			{
				
				if(Shot[i].x+4 > 320)	//�e���v���C���[���E�ɂ�����
					Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
				else								//���ɂ�����
					Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
				Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������
				
				if(Shot[i].y+4 > 240)	//�e���v���C���[��艺�ɂ�����
					Shot[i].my --;					
				else								//��ɂ�����
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
			
			}
				//�����x�̌���
			if(rand()%3 == 1)
			{
				if(Shot[i].mx > 0)	Shot[i].mx --;
				if(Shot[i].mx < 0)	Shot[i].mx ++;
				if(Shot[i].my > 0)	Shot[i].my --;
				if(Shot[i].my < 0)	Shot[i].my ++;
			}

			if(LineMove == 1)
			{
				if(Shot[i].x+4 > 320)	//�e���v���C���[���E�ɂ�����
					Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
				else								//���ɂ�����
					Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
				Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������
			}

			if(LineMove == 2)
			{
				if(Shot[i].y+4 > 240)	//�e���v���C���[��艺�ɂ�����
					Shot[i].my --;					
				else								//��ɂ�����
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
			}

			if(LineMove == 3)
			{
				if(Shot[i].x+4 > 320)	//�e���v���C���[���E�ɂ�����
					Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
				else								//���ɂ�����
					Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
				Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������
		
				if(Shot[i].y+4 > 240)	//�e���v���C���[��艺�ɂ�����
					Shot[i].my --;					
				else								//��ɂ�����
					Shot[i].my ++;
				Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
			}
			

			if(Shot[i].y > 480 || Shot[i].y < -Shot[i].h
			|| Shot[i].x > 640 || Shot[i].x < -Shot[i].w+50)	//��ʂ̊O�ɏo����
			{
				Shot[i].Son = FALSE;					//���݂�FALSE��
			}
			if(LineMove == 0)
				if(rand()%20 == 1) Shot[i].Son = FALSE;
			
		}		
	}

	if(1)//rand()%5 == 1)	//���������Ă��Ȃ��Ȃ�
	{
		//�ʂ�Ԃ��i���j
		ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
		ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);
	}

	lpDDSBackBuffer->GetDC(&hdc);


	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//�e�����݂��A��ނ��Q�O�Ȃ�
		{
			if(Shot[i].Son == 2)
				hPen = CreatePen(PS_SOLID,(TitleCnt02>>5)+(rand()%5),RGB(255,((Shot[i].y>>1)-i)%255,0));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
			else
				hPen = CreatePen(PS_SOLID,(TitleCnt02>>5)+(rand()%5),RGB(0,((Shot[i].y>>1)-i)%255,255));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�

			hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B

			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);

			SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
			DeleteObject(hPen);				//�쐬�����y���̍폜

		}
	}

	lpDDSBackBuffer->ReleaseDC(hdc);


/*
	MyBltFast(	0,0,	//�\����XY���W
		lpDDSOff_Text,	//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
		0,	240,		//�]��������XY���W
		640,	480);	//�]�����E��XY���W
*/


	if(TitleCnt02 > 200)	
	{

		MyBltFast(140,100,lpDDSOff_Text,0,432,352,468);

		//NewGame
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}else
	{
		MyBltFast(250,260+(200-TitleCnt02),lpDDSOff_Text,0,224,127,256);
		MyBltFast(250,300-(200-TitleCnt02),lpDDSOff_Text,0,288,67,320);
	}
}
//=============================================================================================
void Title_022()	//�^�C�g�����S
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	int i,j;
	static int SlctMenu;	//�^�C�g���̃��j���[�I���Ŏg�p
	static int TitleCnt02;
	int RndMenu;

	DDBLTFX ddbltfx;	//�ʂ�Ԃ��ɕK�v�ȍ\����
	HPEN hPen;			//�쐬�����y��������
	HPEN hPenOld;		//�Â��y����ۑ�����

	int LineSize;
	int	RndNum = rand()%255;
	static int fiveCnt;

	fiveCnt++;
	if(fiveCnt > 1)	fiveCnt = 0;

	TitleCnt02 ++;
	if(TitleCnt02 > 500) TitleCnt02 = 0;

	//�㉺�Ń��j���[�I��
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;

	//���j���[�̔ԍ��Ɍ��E����������
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;

	for(i = 0;i < 10;i++)
	{
		ShotFire(rand()%640,480,0,19,2);
		ShotFire(rand()%640,480,0,19,1);
	}

	//���e�̈ړ�

	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//�e�̎�ނ�20�ŁA���݂���Ȃ�
		{
	/*
			if(Shot[i].x+4 > 320)	//�e���v���C���[���E�ɂ�����
			{
				if(Shot[i].Son == 1)
					Shot[i].mx --;					//�e�̈ړ��ʂ��f�N�������g
			//	else
			//		Shot[i].mx ++;
			}else								//���ɂ�����
			{
				if(Shot[i].Son == 1)
					Shot[i].mx ++;					//�e�̈ړ��ʂ��C���N�������g
			//	else
		//			Shot[i].mx --;
			}
			Shot[i].x += Shot[i].mx;	//�ړ��ʂ�e��X���W�ɑ�������
	*/		
			
			if(Shot[i].Son == 2)
				Shot[i].my --;
			else
			{
				if(Shot[i].y+4 > 300)
					Shot[i].my --;
				else
					Shot[i].my ++;
			}
			Shot[i].y += Shot[i].my;			//�ړ��ʂ�e��Y���W�ɑ�������
		}
	

		if(Shot[i].y > 480 || Shot[i].y < -Shot[i].h
		|| Shot[i].x > 640 || Shot[i].x < -Shot[i].w+50)	//��ʂ̊O�ɏo����
		{
			Shot[i].Son = FALSE;					//���݂�FALSE��
		}
			
		//if(rand()%5 == 1) Shot[i].Son = FALSE;	
	}

	if(1)//rand()%5 == 1)	//���������Ă��Ȃ��Ȃ�
	{
		//�ʂ�Ԃ��i���j
		ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
		ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);
	}

	lpDDSBackBuffer->GetDC(&hdc);


	for(i = 0;i < SHOT_MAX;i++)
	{
		if(Shot[i].Son && Shot[i].Type == 20)	//�e�����݂��A��ނ��Q�O�Ȃ�
		{
			if(Shot[i].Son == 2)
			{
				hPen = CreatePen(PS_SOLID,10+(Shot[i].my>>1),RGB(255,((Shot[i].y>>1)-i)%255,0));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
			}else
			{
				hPen = CreatePen(PS_SOLID,10-(-Shot[i].my>>1),RGB(0,((Shot[i].y>>1)-i)%255,255));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
			}

			hPenOld = (HPEN)SelectObject(hdc,hPen);		//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B

			MoveToEx(hdc,Shot[i].x,Shot[i].y,NULL);
			LineTo(hdc,Shot[i].x+Shot[i].mx,Shot[i].y+Shot[i].my);

			SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
			DeleteObject(hPen);				//�쐬�����y���̍폜

		}
	}

	lpDDSBackBuffer->ReleaseDC(hdc);


	if(TitleCnt02 > 50)	
	{

		MyBltFast(140,100,lpDDSOff_Text,0,432,352,468);

		//NewGame
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}
}
//=============================================================================================
void Title_02()	//�^�C�g�����S
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	static int SlctMenu;	//�^�C�g���̃��j���[�I���Ŏg�p
	static int TitleCnt02;
	int RndMenu;
	int RndPalClr;	//�p���b�g�̐F�𖈉񗐐��ŐF��ω�

	DDBLTFX ddbltfx;	//�ʂ�Ԃ��ɕK�v�ȍ\����
	HPEN hPen;			//�쐬�����y��������
	HPEN hPenOld;		//�Â��y����ۑ�����
	int i,j;
	static int LineX,LineY;
	int rndLX;
	static int TitleBGClr;	//�^�C�g���̔w�i�F������
	static int TBGC_time;	//�^�C�g���w�i�F�̐F����莞�Ԃ��ƂɕύX(�ڂɈ�����������
	int RndPal;
	static int MojiZoom  = 270;

	RndPalClr = 12;

	TitleCnt02 ++;
	if(TitleCnt02 > 1000) TitleCnt02 = 541;

	//�㉺�Ń��j���[�I��
	if(CmdNum[0] == 2 && CmdNum[1] != 2)	SlctMenu --;
	if(CmdNum[0] == 8 && CmdNum[1] != 8)	SlctMenu ++;
	//���j���[�̔ԍ��Ɍ��E����������
	if(SlctMenu > 1)	SlctMenu = 1;
	if(SlctMenu < 0)	SlctMenu = 0;


	if(	TitleCnt02 == 0		//�^�C�g���������o�����鎞
	||	TitleCnt02 == 270	//�v���C���[���o�����鎞
	||	TitleCnt02 == 340	//�K���ȃ^�C�~���O�Ńt���b�V��
	||	TitleCnt02 == 380	//�K���ȃ^�C�~���O�Ńt���b�V��
	||	TitleCnt02 == 390	//�V
	||	TitleCnt02 == 420	//�V
	||	TitleCnt02 == 425	//�V
	||	TitleCnt02 == 433	//�V
	||	TitleCnt02 == 490	//�V
	||	TitleCnt02 == 520	//�V
	||	TitleCnt02 == 528	//�V
	||	TitleCnt02 == 540	//���j���[���\�������Ƃ�
	)	
	{
		lpDDPal->SetEntries(0,0,255,MainPal);	//�p���b�g�����ɖ߂�
	}

	if(TitleCnt02 >= 270 && TitleCnt02 < 540)	//�v���C���[���ړ����Ă��鎞����
	{
		lpDDPal->GetEntries(0,0,255,SubPal);
		//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���f�N�������g���A�O�i���j�ɋ߂Â�����
		for(i = 0;i < 255;i++)
		{
			if(SubPal[i].peRed > RndPalClr)
				SubPal[i].peRed -= RndPalClr;	//�Ԃ̗v�f�����炷			
			if(SubPal[i].peGreen > RndPalClr)
				SubPal[i].peGreen -= RndPalClr;	//�΂̗v�f���ւ炷
			if(SubPal[i].peBlue > RndPalClr)
				SubPal[i].peBlue -= RndPalClr;		//�̗v�f�����炷
		}
		lpDDPal->SetEntries(0,0,255,SubPal);
	}

	if(1)//rand()%5 == 1)	//���������Ă��Ȃ��Ȃ�
	{	
		
		//�ʂ�Ԃ��i���j
		ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
		ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
		lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
			DDBLT_COLORFILL | DDBLT_WAIT,
			&ddbltfx);

	}

	//�v���C���[�̃R�[�g�̖͗l�̐F��ω�
	lpDDPal->GetEntries(0,0,255,SubPal);
	SubPal[36].peRed  = 255;
	SubPal[36].peGreen = (TitleCnt02<<2)%255;
	SubPal[36].peBlue = (TitleCnt02<<2)%255;
	lpDDPal->SetEntries(0,0,255,SubPal);


	if(TitleCnt02 < 270)
	{
		//�Y�[���_�E���^�C�g��
		MojiZoom --;
		for(j = 0;j < 15;j++)
			for(i = 0;i < 20;i++)
				MyBltFast(i*32,j*32,lpDDSOff_Text,352+(((TitleCnt02>>2)%7)*32),352,384+(((TitleCnt02>>2)%7)*32),384);	//�_�o
		MyBlt(140-(MojiZoom>>1),100-(MojiZoom>>1),140+352+(MojiZoom>>1),100+64+(MojiZoom>>1),lpDDSOff_Text,0,416,352,480);		//Title
	}else
	{	
		//�^�C�g��
		for(j = 0;j < 2;j++)
			for(i = 0;i < 11;i++)
				MyBltFast(140+(i*32),100+(j*32),lpDDSOff_Text,352+(((TitleCnt02>>2)%7)*32),352,384+(((TitleCnt02>>2)%7)*32),384);	//�_�o
		MyBltFast(140,100,lpDDSOff_Text,0,352,352,416);	//�^�C�g������
	}
	if(TitleCnt02 < 540)
	{
		//�v���C���[�摜�ړ�
		MyBltFast(50,270+(540-TitleCnt02),lpDDSOff_Title,176,0,352,272);//Player
		MyBltFast(430,150-(540-TitleCnt02),lpDDSOff_Title,0,272,160,352);//Sword_Down
		MyBltFast(430+45,150-96-(540-TitleCnt02),lpDDSOff_Title,64,352,127,448);//Sword_Up
	}else
	{
		//�v���C���[�摜
		MyBltFast(50,270,lpDDSOff_Title,0,0,176,272);		//Player
		MyBltFast(430,150,lpDDSOff_Title,0,272,160,352);	//Sword_Down
		MyBltFast(430+45,150-96,lpDDSOff_Title,0,352,64,448);//Sword_Up

		//NewGame����
		if(SlctMenu == 0)
			MyBltFast(250,260+(rand()%5),lpDDSOff_Text,0,224,127,256);
		else
			MyBltFast(250,260,lpDDSOff_Text,0,256,127,288);
		//Option����
		if(SlctMenu == 1)
			MyBltFast(250,300+(rand()%5),lpDDSOff_Text,0,288,67,320);
		else
			MyBltFast(250,300,lpDDSOff_Text,0,320,67,352);
	}



	TBGC_time ++;	//�J�E���g
	if(TBGC_time > (7-(rand()%4)) )	//�J�E���g�����̎��Ԃ𒴂���ƃ^�C�g���w�i�F��ύX
	{
		TitleBGClr = (rand()%5)+6;
		TBGC_time = 0;
	}


	//�`��
	if(rand()%5 == 1)
	{
		//���݂�\��
		MyBltFast(	140,200,	//�\����XY���W
				lpDDSOff_Text,	//�\������G�̃I�t�X�N���[���T�[�t�F�[�X
				128,	24,		//�]��������XY���W
				136,	32);	//�]�����E��XY���W
		MyBltFast( 400,320,
				lpDDSOff_Text,
				128,	32,
				136,	40);
		MyBltFast(580,20,
				lpDDSOff_Text,
				128,	40,
				136,	48);
		MyBltFast(210,87,
				lpDDSOff_Text,
				128,	48,
				136,	64);
	}
	for(i = 0;i < 10;i++)
	{
		MyBltFast(rand()%640,rand()%480,
					lpDDSOff_Text,
					128,	32,
					129,	33);
	}		

	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	lpDDSBackBuffer->GetDC(&hdc);


	//�v���C���[�̍U�������蔻��͈̔͂�\�����̐ݒ�
	hPen = CreatePen(PS_SOLID,1,RGB(100,100,100));	//�_���A�����P,�ΐF�̃y�����쐬���AhPen�ɕۑ�
	hPenOld = (HPEN)SelectObject(hdc,hPen);	//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B
	
	for(i = 0;i < 8;i++)
	{
		//�v���C���[�̍U���͈͂�\���l�p��`��
		if(rand()%7 == 1)	//�v���C���[�U�����̓����蔻�蕔����\��
		{
			rndLX = rand()%640;
		
			if(rand()%2 == 1)
			{
				MoveToEx(hdc,rndLX,0,NULL);
				LineTo(hdc,rndLX,rand()%480);
			}else
			{
				MoveToEx(hdc,rndLX,rand()%480,NULL);
				LineTo(hdc,rndLX,480);
			}
		}
	}

	LineX += (rand()%4)-1;
	if(LineX < 0) LineX = rand()%640;
	if(LineX > 640) LineX = rand()%640;

	LineY -= (rand()%4)-2;
	if(LineY < 0)	LineY = rand()%480;
	if(LineY > 480) LineY = rand()%480;

	if(rand()%30 == 1)	LineX = rand()%640;

	if(rand()%2 == 1)
	{
		for(i = 0;i < 2;i++)
		{
			MoveToEx(hdc,LineX+(i*40),0,NULL);
			LineTo(hdc,LineX+(i*40),rand()%480);

			MoveToEx(hdc,LineX+(i*40),rand()%480,NULL);
			LineTo(hdc,LineX+(i*40),480);
		}
	}

	SelectObject(hdc,hPenOld);		//�y�������ɖ߂�
	DeleteObject(hPen);				//�쐬�����y���̍폜

	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);
}