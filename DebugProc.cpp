#include <windows.h>
#include <ddraw.h>

#include "Extern.h"
//����������������������������������������������������������������������������������������������������
void DrawText(LPDIRECTDRAWSURFACE7 lpDDS,int x,int y,char* text,int rcol,int gcol,int bcol)
//�@�\�F�e�L�X�g��\������֐�
//�����P�F���삵�����T�[�t�F�[�X
//�����Q,�R�F������\�����������WX,Y
//�����S�A�T�A�U�F������F���w��
{
	HDC hdc;
	lpDDS->GetDC(&hdc);	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾

		//wsprintf(str,"%d  ",CmdNum[i]);
	SetTextColor(hdc,RGB(rcol,gcol,bcol));	//�����S�C�T�C�U�Ŏw��F�𕶎��F��
	SetBkMode(hdc,TRANSPARENT);				//�����̃o�b�N�𓧖���
	TextOut(hdc,x,y,text,lstrlen(text));	//�����\��

	lpDDS->ReleaseDC(hdc);//�f�o�C�X�R���e�L�X�g�̉��
	
}
//����������������������������������������������������������������������������������������������������
void DrawFrameRate(LPDIRECTDRAWSURFACE7 lpDDS,int x,int y)
//�@�\�F�t���[�����[�g��\������֐�
//�����P�F���삵�����T�[�t�F�[�X
//�����Q�A�R�F�\�����������WX,Y
{
	static DWORD frameNew, frameOld;
	static DWORD timeNew, timeOld;
	HDC hdc;
	static char string[64];
	DWORD Rate;

	frameNew ++;
	timeNew = timeGetTime();
	if(timeNew - timeOld > 1000)
	{
		Rate = frameNew - frameOld;	//Rate�̒l���X�V
		frameOld = frameNew;
		timeOld = timeNew;
		wsprintf(string,"%dFPS   ",Rate);	//Rate�̒l��string�ɒu��������
	}

	lpDDS->GetDC(&hdc);

	SetTextColor(hdc,RGB(255,255,255));			//�����F�w��
	SetBkMode(hdc,TRANSPARENT);					//�����̃o�b�N�𓧖��ɂ���
	TextOut(hdc,x,y,string,lstrlen(string));	//������\��

	lpDDS->ReleaseDC(hdc);

}

//����������������������������������������������������������������������������������������������������
void Debug_DrawText()	//�e�L�X�g�\�����܂Ƃ߂��֐�(���C���֐��p�i�f�o�b�O�p
{
	HDC hdc;
	int i;
	char str[64];

	//���e�L�X�g�\��
	lpDDSBackBuffer->GetDC(&hdc);	//�`����s���T�[�t�F�[�X�̃f�o�C�X�R���e�L�X�g���擾
	
	SetBkMode(hdc,TRANSPARENT);						//�����w�i�𓧖���
	SetTextColor(hdc,RGB(255,255,255));				//�����F�𔒂�

	//�R�}���h�\��
	for(i = 0;i < 8;i++)
	{
		wsprintf(str,"%d  ",CmdNum[i]);
		TextOut(hdc,100+(i<<5),100,str,lstrlen(str));
		wsprintf(str,"%d  ",CmdCnt[i]);
		TextOut(hdc,100+(i<<5),120,str,lstrlen(str));
	}
	
	//Cnt
	for(i = 0;i < ENE_MAX;i++)
	{
		if(En[i].Son)
		{
			wsprintf(str,"EneHitD= %d : EneCnt[%d]",En[i].HitD,En[i].Cnt);
			TextOut(hdc,En[i].x,En[i].y+En[i].h,str,lstrlen(str));

		}
	}

	wsprintf(str,"Btn1 [%d]  : Btn2 [%d] :: Cnt(%d)",Btn1,Btn2,BtnCnt);
	TextOut(hdc,400,400,str,lstrlen(str));

	wsprintf(str,"Plr.HitD = %d",Plr.HitD);
	TextOut(hdc,500,300,str,lstrlen(str));

	//�t���[�����[�g�\��
	wsprintf(str,"FPS_Disp [ %d ]",FPS_Disp);			//FPS_Disp�𕶎���ɒu��������
	TextOut(hdc,10,10,str,lstrlen(str));				//���z��ʂ�str�\��

	wsprintf(str,"FPS_ChangeNum [ %d ]",FPS_ChangeNum);			//FPS_Disp�𕶎���ɒu��������
	TextOut(hdc,10,25,str,lstrlen(str));				//���z��ʂ�str�\��

	lpDDSBackBuffer->ReleaseDC(hdc);	//�f�o�C�X�R���e�L�X�g�̉��	
}
//��������������������������������������������������������������������������������������������������������������������������������������������������������
