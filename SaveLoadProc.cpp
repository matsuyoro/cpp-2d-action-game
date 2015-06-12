//�Q�[���p�̃Z�[�u�A���[�h�̊֐��{��
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include <ddraw.h>

#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_�t�@�C��
#include "Extern.h"		//�O���ϐ��ɂȂ��Ă���f�[�^���Z�[�u�A���[�h����̂ŁAextern.h���g���B

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void GameLoad(char *pFileName)	//�@�\�F�Q�[���p�̃f�[�^�����[�h����֐�(�}�b�v�f�[�^���[�h
//�������F���[�h����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)�ǂݍ��ݗp��
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)�t�@�C�����J���A�Ȃ��ꍇ�͎��s
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}
	//�Z�[�u���Ă���f�[�^�����[�h����B�Z�[�u�������ƁA�������ԂŃ��[�h���邱�ƁB
	ReadFile(hFile,&MapXnum,sizeof(int),&Dum,NULL);	//�}�b�v���R�`�b�v�������[�h�iint�^�j
	ReadFile(hFile,&MapYnum,sizeof(int),&Dum,NULL);	//�}�b�v�^�e�`�b�v�������[�h�iint�^�j
	//���ł������������K�v�����Ƃ߂邽�߂Ƀ}�b�v�̕��A���������[�h

	if(pMap != NULL)	//�����烁�����m�ۂ��悤�Ƃ��Ă���ϐ���NULL����Ȃ��Ȃ�
		MessageBox(NULL,"�|�C���^�ϐ��͂��łɃ������m�ۂ���Ă��܂�","�G���[",MB_OK);
	pMap = (int*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sizeof(int)*MapYnum*MapXnum);//int�^���}�b�v�������}�b�v�����̃��������m��
	if(pMap == NULL)	//GlobalAlloc�̖߂�l��NULL���߂��Ă�����G���[�ʒm
		MessageBox(NULL,"�������m�ێ��s","�G���[",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��

	ReadFile(hFile,&pMap[0],sizeof(int)*MapYnum*MapXnum,&Dum,NULL);	//�}�b�v�f�[�^�����[�h

	//���ɂ��Z�[�u�����f�[�^������Ȃ�A�Z�[�u�������Ɠ������ԂŃ��[�h����

	CloseHandle(hFile);		//���
	MessageBox(NULL,"���[�h���܂���","LOAD",MB_OK);	//���[�h���ꂽ���̊m�F���b�Z�[�W
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EneOnPosLoad(char *pFileName)	//�@�\�F�K�o���ʒu�����[�h����֐�
//�������F���[�h����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)�ǂݍ��ݗp��
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)�t�@�C�����J���A�Ȃ��ꍇ�͎��s
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}

	//�Z�[�u���Ă���f�[�^�����[�h����B�Z�[�u�������ƁA�������ԂŃ��[�h���邱�ƁB
	ReadFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);	//�o���ʒu�̐������[�h�iint�^�j
	//���ł������������K�v�����Ƃ߂邽�߂ɏo���ʒu�̐������[�h

	if(pEneOn != NULL)	//�����烁�����m�ۂ��悤�Ƃ��Ă���ϐ���NULL����Ȃ��Ȃ�
		MessageBox(NULL,"�|�C���^�ϐ��͂��łɃ������m�ۂ���Ă��܂�","�G���[",MB_OK);
	pEneOn = (ENE_ONPOS*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//ENE_ONPOS�^���K�o���ʒu�����̃��������m��
	if(pMap == NULL)	//GlobalAlloc�̖߂�l��NULL���߂��Ă�����G���[�ʒm
		MessageBox(NULL,"�������m�ێ��s","�G���[",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��


	ReadFile(hFile,pEneOn,sizeof(ENE_ONPOS)*EneOnPos_Max.x,&Dum,NULL);	//�K�o���ʒu�f�[�^�����[�h
	//���Ӂ@�K�o���ʒu�̍ő吔���Z�[�u�������ƃ��[�h�������̐��������łȂ��ƃ_��	//���ɂ��Z�[�u�����f�[�^������Ȃ�A�Z�[�u�������Ɠ������ԂŃ��[�h����


	CloseHandle(hFile);		//���
	MessageBox(NULL,"�K�o���ʒu���[�h���܂���","LOAD",MB_OK);	//���[�h���ꂽ���̊m�F���b�Z�[�W
}
