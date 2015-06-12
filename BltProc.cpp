#include <windows.h>
#include <ddraw.h>

#include "Extern.h"		//�O���ϐ��������w�b�_
//#include "BltProc.h"	//�`��֐��̃v���g�^�C�v�錾�̃w�b�_
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void MyBltFast(int x,int y,LPDIRECTDRAWSURFACE7	OffSur,int ofl,int oft,int ofr,int ofb)	//�@�\�FBltFast�֐��ŕ`�悷��֐�
//�������P,�Q�F�\����X,Y���W
//�������R�F�]������摜�̃I�t�X�N���[���T�[�t�F�[�X
//�������S,�T�F�]�����̉摜�̍���X,Y���W
//�������U,�V�F�]�����̉摜�̉E��X,Y���W
{
	RECT rc;	//�]�����͈̔͂�����
/*
	//�N���b�s���O����
	if(x+ofl < 0)					//���ɂ͂ݏo�悤�Ƃ�����
		ofl -= x+ofl;				//�͂ݏo�镔����]�����Ȃ�

	if(y+oft < 0)					//��ɂ͂ݏo�悤�Ƃ�����
		oft -= y+oft;					//�͂ݏo�镔����]�����Ȃ�

	if(x+ofr > 640)				//�E�ɂ͂ݏo�悤�Ƃ�����
		ofr -= (x+ofr)-640;			//�͂ݏo�镔����]�����Ȃ�

	if(y+ofb > 480)				//���ɂ͂ݏo�悤�Ƃ�����
		ofb -= (y+ofb)-480;			//�͂ݏo�镔����]�����Ȃ�

	SetRect(&rc,ofl,oft,ofr,ofb);	//�]�����͈̔͂��X�V
*/

	int w = ofr - ofl;	//��
	int h = ofb - oft;	//����

	//���N���b�s���O
	if(x < 0)
	{
		ofl += (-x);	//left�̒l�𒲐�
		x = 0;	//�\���͂O�i���[�j����
	}

	//��N���b�s���O
	if(y < 0)
	{
		oft += (-y);	//top�̒l�𒲐�
		y = 0;			//�\���͂O�i��j����
	}

	//�E�N���b�s���O
	if(x + w > 640)
	{
		ofr -= ((x+w) - 640);	//right�̒l�𒲐�
	}

	//���N���b�s���O
	if(y+h > 480)
	{
		ofb -= ((y+h) - 480);	//bottom�̒l�𒲐�
	}
	SetRect(&rc,ofl,oft,ofr,ofb);	//�]�����͈̔͂��X�V

	//�w�肵���̽�ذݻ�̪�����w�肵�����W�ɕ\��
	lpDDSBackBuffer->BltFast(x,y,OffSur,&rc,DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void MyBlt(int l,int t,int r,int b,LPDIRECTDRAWSURFACE7 OffSur,int ofl,int oft,int ofr,int ofb)	//�@�\�FBlt�֐��ŕ`�悷��֐�
//�������P,�Q�F�\���捶��X,Y���W
//�������R,�S�F�\����E��X,Y���W
//�������T�F�]������摜�̃I�t�X�N���[���T�[�t�F�[�X
//�������U,�V�F�]��������X,Y���W
//�������W,�X�F�]�����E��X,Y���W
{
	/*
	RECT rc1;	//�]�����`��͈͂�����
	RECT rc2;					//�]����`��͈͂�����

	if(l < 0)					//���ɂ͂ݏo�悤�Ƃ�����
	{
		ofl += (-l);	
		l += (-l);
	}
	if(t < 0)					//��ɂ͂ݏo�悤�Ƃ�����
	{
		oft += (-t);
		t += (-t);
	}
	if(r > 640)		//�E�ɂ͂ݏo�悤�Ƃ�����
	{
		ofr -= (r-640);
		r -= (r-640);
	}
	if(b > 480)		//���ɂ͂ݏo�悤�Ƃ�����
	{
		ofb -= (b-480);
		b -= (b-480);
	}

	SetRect(&rc1,ofl,oft,ofr,ofb);	//�`�挳��ݒ�
	SetRect(&rc2,l,t,r,b);	//�`��������rc3���X�V�B

	lpDDSBackBuffer->Blt(&rc2,OffSur,&rc1,DDBLT_WAIT,NULL);
	*/
	RECT rc1;//={ofl,oft,ofr,ofb};	//�]�����`��͈͂�����
	RECT rc2;					//�]����`��͈͂�����

	/*
	if(l < 0)					//���ɂ͂ݏo�悤�Ƃ�����
		ofl += (-l);	
	
	if(t < 0)					//��ɂ͂ݏo�悤�Ƃ�����
		oft += (-t);

	if(r > 640)		//�E�ɂ͂ݏo�悤�Ƃ�����
	{
		ofr -= (r-640);			//�]�����̉摜�̕������炷
		if(ofr < 1)	ofr = 1;	//�]�����̉摜�̕����P�h�b�g��菬�����Ȃ�Ȃ��悤�ɂ���
		r -= (r-640);			//�]����̉摜�����炷
	}
	if(b > 480)		//���ɂ͂ݏo�悤�Ƃ�����
	{
		ofb -= (b-480);			//�]�����̉摜�̍��������炷
		if(ofb < 1) ofb = 1;	//�]�����̉摜�̍������P�h�b�g��菬�����Ȃ�Ȃ��悤�ɂ���
		b -= (b-480);			//�]����̉摜�����炷
	}*/
	SetRect(&rc1,ofl,oft,ofr,ofb);	//�`�挳��ݒ�
	SetRect(&rc2,l,t,r,b);	//�`��������rc3���X�V�B

	lpDDSBackBuffer->Blt(&rc2,OffSur,&rc1,DDBLT_KEYSRC | DDBLT_WAIT,NULL);

}