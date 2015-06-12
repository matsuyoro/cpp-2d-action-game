////////�C���N���[�h///////////
#include <windows.h>	//Windows�p�̃w�b�_�[�t�@�C��(windows�Ŏg�p���閽�߂�f�[�^�^���܂Ƃ߂��Ă���)
#include "extern.h"		//�O���ϐ����������߂̃w�b�_�t�@�C��
/////////�֐��{��/////////////////
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL LoadBmp(char *pFileName,HDC hdc,HDC *phBmpDC,HINSTANCE hInst)	//�@�\�FBMP�t�@�C������������֐�
//�������P�F�ǂݍ��ރt�@�C����
//�������Q�F�E�B���h�E��HDC
//�������R�F�쐬���ꂽHDC�������Ƃ�A�h���X
//�������S�FLoadImage�Ŏg�p����C���X�^���X�n���h��
{
//�����ϐ��錾
HBITMAP hBit;	//�r�b�g�}�b�v�n���h��hBit��錾
char str[256];	//�G���[���b�Z�[�W�ň���������������ϐ�

//�G�̃f�[�^����
hBit = (HBITMAP)LoadImage(hInst,pFileName,			//�����P�̃t�@�C����(pFIleName)�̃f�[�^��ǂݍ���
						  IMAGE_BITMAP,0,0,			//0,0�Ŏ����œǂݍ��މ摜�̑傫���������Őݒ�
						  LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//�ǂݍ��݃t���O
if(!hBit)		//LoadImage()�Ɏ��s������(NULL�Ȃ�)
{
	wsprintf(str,"%s�̗p�ӂɎ��s(LoadImage)",pFileName);	//LoadImage�Ɏ��s�����t�@�C�����𕶎���ɒu��������
	MessageBox(NULL,str,"�G���[",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
	return FALSE;											//FALSE��߂�
}

*phBmpDC = CreateCompatibleDC(hdc);		//hCharDC�i������DC�j���쐬
if(!*phBmpDC)	//CreateCompatibleDC()�Ɏ��s������(NULL�Ȃ�)
{
	wsprintf(str,"%s��HDC�쐬�Ɏ��s(CreateCompatibleDC)",pFileName);	//CreateComaptibleDC�Ɏ��s�����t�@�C�����𕶎���ɒu��������
	MessageBox(NULL,str,"�G���[",MB_OK);								//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
	DeleteObject(hBit);													//��������LoadImage()��hBit�͉��
	return FALSE;														//FALSE��߂�
}

SelectObject(*phBmpDC,hBit);		//hCharDC�Ƀr�b�g�}�b�v�n���h����I��
DeleteObject(hBit);					//�r�b�g�}�b�v�n���h��hBit�����
return TRUE;						//����������TRUE��n��
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL LoadDIB(char *pFileName,HDC hdc,HDC *BmpDC)	//�@�\�FDIB�t�@�C������������֐�
//�������P�F���[�h����BMP�t�@�C����(�Q�S�r�b�gBMP
//�������Q�F�E�B���h�E��HDC
//�������R�F�쐬���ꂽHDC�������Ƃ�A�h���X
{
	HBITMAP hBit;	//�r�b�g�}�b�v�n���h���iDIB�쐬�̎��̖ߒl�������Ƃ�
	HANDLE hFile;			//�t�@�C������Ŏg�p
	DWORD dwSize;
	char str[256];			//�\�����镶���������

	hFile = CreateFile(pFileName,GENERIC_READ,0,NULL,	//BMP�t�@�C�����J��
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//���s�����ꍇ
	{
		wsprintf(str,"CreateFile���s");
		MessageBox(NULL,str,"�G���[",MB_OK);	//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
		return FALSE;											//FALSE��߂�
	}

	ReadFile(hFile,&BmpFileH,sizeof(BITMAPFILEHEADER),	//BITMAPFILEHEADER�����[�h
		&dwSize,NULL);

	ReadFile(hFile,&BmpInfoH,sizeof(BITMAPINFOHEADER),	//BITMAPINFOHEADER�����[�h
		&dwSize,NULL);

	*BmpDC = CreateCompatibleDC(hdc);	
	
	hBit = CreateDIBSection(hdc,	//DIB�쐬�iBMP�t�@�C���Ɠ����傫���A�����J���[���[�h��DIB�쐬
		(BITMAPINFO*)&BmpInfoH,
		DIB_RGB_COLORS,(void**)&rgbt,NULL,0);
		
	ReadFile(hFile,rgbt,			//rgbt �� BMP�t�@�C���̃s�N�Z���f�[�^�������[�h
		BmpFileH.bfSize -
		sizeof(BITMAPINFOHEADER) -
		sizeof(BITMAPFILEHEADER),	//INFOH��FILEH�̕��������ăs�N�Z���f�[�^�݂̂ɂȂ�
		&dwSize,NULL);				//rgbt(DIB�̗̈�j��BMP�t�@�C���̃s�N�Z���f�[�^�����[�h����
	
	SelectObject(*BmpDC,hBit);

	DeleteObject(hBit);
	CloseHandle(hFile);	//�t�@�C���̌�n���i����j�@�G�ߒl�@�F�@�����Ȃ�TRUE�A���s�Ȃ�FALSE�B
	return TRUE;	//�����Ȃ�TRUE��Ԃ�
}
