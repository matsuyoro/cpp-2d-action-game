///////////// �C���N���[�h ////////////////////////////
#include <windows.h>
#include <ddraw.h>

#include "Extern.h"	//�O���ϐ����������߂̃w�b�_

#include "GameTitle.h"	//�Q�[���^�C�g���̃v���g�^�C�v�錾�̃w�b�_
#include "GameMain.h"	//�Q�[�����C���̃v���g�^�C�v�錾�̃w�b�_
#include "GameOver.h"	//�Q�[���I�[�o�[�̃v���g�^�C�v�錾�̃w�b�_
#include "StageSelect.h"	//�X�e�[�W�Z���N�g��ʂ̃v���g�^�C�v�錾�̃w�b�_
#include "GameStop.h"		//�|�[�Y��ʂ̃v���g�^�C�v�錾

#include "GameCheckProc.h"
#include "DebugProc.h"	//�e�L�X�g�\���Ȃǂ������w�b�_
///////////// �v���g�^�C�v�錾 ////////////////////////
void GameClear(int *);	//�Q�[���N���A�[

//���������������������@���C���֐��@������������������������������������������������������������������������������������
void Main()
{
/*	static int GameNum = 0;	/*�ǂ̏��������s���邩�������ϐ�GameNum��0�i�ŏ��̓^�C�g����ʁj�ŏ�����
						0 �E�E�E�^�C�g��
						1 �E�E�E�Q�[���{��
						2 �E�E�E�Q�[���I�[�o�[
						3 �E�E�E�Q�[���N���A   */
	static int CtrlNum = 0;		//������Ԃ̓W���C�p�b�h��

	void (*pGame[6])(int *);	//�ߒl�Ȃ��A����int�^�|�C���^�̊֐��̃A�h���X�́A�֐��̃|�C���^�z��̐錾

	pGame[0] = GameTitle;	//pGame[0]�ɒ�`�֐�GameTitle�̐擪�A�h���X����
	pGame[1] = GameMain;	//pGame[1]�ɒ�`�֐�GameMain�̐擪�A�h���X����
	pGame[2] = GameOver;	//pGame[2]�ɒ�`�֐�GameOver�̐擪�A�h���X����
	pGame[3] = GameClear;	//pGame[3]�ɒ�`�֐�GameClear�̐擪�A�h���X����
	pGame[4] = StageSelect;	//
	pGame[5] = GameStop;


	//�� �T�[�t�F�[�X���X�g�̑΍�
	if(lpDDSPrimary->IsLost()==DDERR_SURFACELOST)
		lpDDSPrimary->Restore();	

	if(!CtrlNum)	//CtrlNum���P�Ȃ炱�̏����������Ȃ�Ȃ�
	{
		//�� �W���C�X�e�B�b�N�ȂǁA���͂̎擾
		MMRESULT ret;
		JoyData2 = JoyData;							//�O��̒l�Ƃ��āAJoyData��ۑ�
		ret = joyGetPosEx(JOYSTICKID1,&JoyData);	//JoyData�̒��ɃW���C�X�e�B�b�N�̃f�[�^������iJoyData���X�V�j
		if(ret != JOYERR_NOERROR)					//ret��JOYERR_NOERROR����Ȃ�������
		{
			MessageBox(NULL,"�W���C�X�e�B�b�N�̎擾�Ɏ��s�i������L�[�{�[�h�ōs���܂�","�G���[",MB_OK);	//�G���[�\��
			CtrlNum = 1;	//CtrlNum���P�ɂ��đ�����L�[�{�[�h�ōs��
		}

		Key = 0;					//Dum��0�i0000 [0]�j�ŃX�^�[�g
		if(JoyData.dwXpos <= 10000)	//����������Ă�����
			Key |= 1;					//�O�r�b�g�ڂ��P�Ɂi0001 [1]�j
		if(JoyData.dwYpos <= 10000)	//�オ������Ă�����
			Key |= (1<<1);				//�P�r�b�g�ڂ��P�Ɂi0010 [2]�j
		if(JoyData.dwXpos >= 50000)	//�E��������Ă�����
			Key |= (1<<2);				//�Q�r�b�g�ڂ��P�Ɂi0100 [4]�j
		if(JoyData.dwYpos >= 50000)	//����������Ă�����
			Key |= (1<<3);				//�R�r�b�g�ڂ��P�Ɂi1000 [8]�j

		//�{�^���f�[�^�̎擾
		Btn1 = 0;
		if(JoyData.dwButtons & (1<<1))	
			Btn1 |= (1<<1);				//�P�r�b�g�ڂ��P�Ɂi0010 [2]�j
		if(JoyData2.dwButtons & 1)
			Btn1 |= 1;					//�O�r�b�g�ڂ��P�Ɂi0001 [1]�j

		//�{�^���̉����Ă��鎞�Ԃ��J�E���g
		if(JoyData.dwButtons == JoyData2.dwButtons )
			BtnCnt++;
		else
			BtnCnt = 0;

	}else	//�L�[�{�[�h�Ȃ�
	{

		if(Btn1 == Btn2)
			BtnCnt++;
		else
			BtnCnt = 0;
	}


	CmdGet = KeyCmdChk(Key);	//�R�}���h�f�[�^��ۑ�����֐�


//	while(TRUE)	//TRUE�Ȃ̂ŌJ��Ԃ�
//	{
	//���Q�[������
	pGame[GameNum](&GameNum);	//�֐��̃|�C���^�z��̗v�f�ԍ��iGameNum�j�ɑΉ������֐������s
//	}

	//���e�L�X�g�\��
	//Debug_DrawText();	//�e�L�X�g�\�����܂Ƃ߂��֐�

	lpDDSPrimary->Flip( NULL,DDFLIP_WAIT );				//�t���b�v�i�ŏI�o�́j
	

	Btn2 = Btn1;	//�ŐV�̃{�^���f�[�^��O��̃{�^���f�[�^�ɑ��


}
//������������������������������������������������������������������������������������������������������������������������


//��GameClear����������������������������������������������������������������
void GameClear(int *pGameNum)	//	�@�\�F�Q�[���N���A�[��ʂ̏������s���֐�
//	�������F�Q�[���̏�ʂ������l
{
		*pGameNum = 0;	//�ԐڎQ�ƂŁAGameNum��0�ɂ���i�^�C�g���j
}