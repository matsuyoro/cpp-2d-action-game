#include <windows.h>
#include <ddraw.h>
#include "Extern.h"
#include "BltProc.h"

#include "GameBltProc.h"

//���@GameStop�@������������������������������������������������������������������������������������������
void GameStop(int *pGameNum)	//	�@�\�F�|�[�Y��ʂ̏���
//	�������F�Q�[���̏�ʂ������l
{
	HDC hdc;				//�f�o�C�X�R���e�L�X�g
	char str[256];			//�����������
	DDBLTFX ddbltfx;		//�ʂ�Ԃ��ɕK�v�ȍ\����
	static int PouseAni;	//�A�j���[�V�����J�E���^

	HFONT hFont;	//�p�ӂ����t�H���g������
	HFONT hFontOld;	//�Â��t�H���g��p�ӂ���


	if(rand()%5 == 1)	PouseAni++;
	PouseAni %= 7;

	//�ʂ�Ԃ��i���j
	ddbltfx.dwSize = sizeof(ddbltfx);		//�\���̂̃T�C�Y���w�肷��
	ddbltfx.dwFillColor = 0;				//�ʂ�Ԃ��F���w��
	lpDDSBackBuffer -> Blt(NULL,NULL,NULL,	//�w��̐F�łʂ�Ԃ�
		DDBLT_COLORFILL | DDBLT_WAIT,
		&ddbltfx);

	if(!(Btn2 & (1<<1)) && (Btn1 & (1<<1)))	//B�{�^����O��i���j�Ō��݁i���j�Ȃ� 
	{
		*pGameNum = 1;	//�ԐڎQ�Ƃ�GameNum���P�i�Q�[���{�ҁj�ɂ���B
	}

	//�΂̕�
	MyBltFast(	32,64,
				lpDDSOff_Pouse,
				0,64,
				576,480);
	//432,168
	MyBltFast(  464,168,
				lpDDSOff_Pouse,
				PouseAni*24,0,
				PouseAni*24+24,24);

	//�Q�[�W��\��
	PlrHpBlt();

	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	lpDDSBackBuffer->GetDC(&hdc);


	hFont = CreateFont(				//�t�H���g��p�ӂ���B
						32,			//��������
						12,			//�������i�O�ɂ���ƁA���������Ɏ����Ō���j
						60,			//�p�x
						0,			//�x�[�X���C����x���̊p�x
						FW_HEAVY,	//FW_REGULAR,	//�t�H���g�̑���
						FALSE,		//�C�^���b�N�́@�̗L��
						TRUE,		//�A���_�[���C���@�̗L��
						FALSE,		//�ł��������@�̗L��
						SHIFTJIS_CHARSET,			//�����Z�b�g
						OUT_DEFAULT_PRECIS,			//�o�͐��x
						CLIP_DEFAULT_PRECIS,		//�N���b�s���O���x
						PROOF_QUALITY,				//�o�͕i��
						FIXED_PITCH | FF_MODERN,	//�s�b�`�ƃt�@�~���[
						"");					//���̖�

	hFontOld = (HFONT)SelectObject(hdc,hFont);
	//hdc�ɁAhFont(�V�����t�H���g�j��ݒ�B���̎��A�ߒl�Ƃ��āA�ȑO�̃t�H���g���󂯎���Ă����B

	//��hdc��TextOut()
	//�����\��

	for(int i = 0;i < 4;i++)
	{
		SetBkColor(hdc,RGB(255,0,0));			//�����̃o�b�N�J���[�̎w��
		SetBkMode(hdc,TRANSPARENT);				//�����𓧖��ɂ���

		SetTextColor(hdc,RGB(i*80,i*80,0));		//�����F�ύX
		wsprintf(str,"PAUSE");
		TextOut(hdc,200-(i<<1),450-(i<<1),str,lstrlen(str));

		SetTextColor(hdc,RGB(i*80,0,0));			//�����F�ύX
		
		wsprintf(str,"�́@%d�^%d",Plr.Hp,Plr.MaxHp);
		TextOut(hdc,100-(i<<1),140-(i<<1),str,lstrlen(str));
		wsprintf(str,"�U  %d",Plr.Atk);
		TextOut(hdc,100-(i<<1),180-(i<<1),str,lstrlen(str));
		wsprintf(str,"���@%d",Plr.Spd);
		TextOut(hdc,100-(i<<1),220-(i<<1),str,lstrlen(str));
		wsprintf(str,"���@%d�^%d",Swd.Hp,Swd.MaxHp);
		TextOut(hdc,100-(i<<1),280-(i<<1),str,lstrlen(str));
	}


	SelectObject(hdc,hFontOld);
	//hdc�ɁAhFontOld(�ȑO�̃t�H���g)��ݒ�B�i�t�H���g�����ɖ߂��j
	DeleteObject(hFont);	//����Ȃ��Ȃ����t�H���g���폜



	//�f�o�C�X�R���e�L�X�g�̉��
	lpDDSBackBuffer->ReleaseDC(hdc);

}