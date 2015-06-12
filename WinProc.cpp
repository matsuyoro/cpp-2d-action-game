#include <windows.h>
#include <ddraw.h>
	
#include "GameStruct.h"	//�\���̂̌^�̒�`�̃w�b�_
#include "Extern.h"		//�O���ϐ��̃w�b�_

#include "DirectSound.h"
#include "DirectMusic.h"
#include "GameCheckProc.h"	//�L�����`��֐��Ȃǂ̃v���g�^�C�v�錾�̃w�b�_
/*--------------------------------------------------------------------------
	�R�[���o�b�N�֐�
--------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int i;				//�J�E���^�ϐ�
	static int PalCtrl;	//�p���b�g�؂�ւ��ň����ϐ�
	
	Key = 0;	//
	Btn1 = 0;	//�{�^���������Ȃ�������O��
	switch( message )
	{
	case WM_KEYDOWN:	//�L�[�{�[�h�������ꂽ��
		switch( wParam )
		{

		case VK_UP:
			Key |= (1<<1);				//�P�r�b�g�ڂ��P�Ɂi0010 [2]�j
			break;
		case VK_LEFT:
			Key |= 1;					//�O�r�b�g�ڂ��P�Ɂi0001 [1]�j
			break;
		case VK_RIGHT:
			Key |= (1<<2);				//�Q�r�b�g�ڂ��P�Ɂi0100 [4]�j
			break;
		case VK_DOWN:
			Key |= (1<<3);				//�R�r�b�g�ڂ��P�Ɂi1000 [8]�j
			break;

		case VK_SHIFT:
			Btn1 |= 1;					//�O�r�b�g�ڂ��P�Ɂi0001 [1]�j
			break;
		case VK_CONTROL:
			Btn1 |= (1<<1);				//�P�r�b�g�ڂ��P�Ɂi0010 [2]�j
			break;

		/*
		case VK_UP:			//���������ꂽ��
			BGScrX -= 5.0;
			break;
		case VK_DOWN:		//���������ꂽ��
			BGScrX += 5.0;
			break;
		case VK_LEFT:		//���������ꂽ��
			BGScrX -= 0.5;
			break;
		case VK_RIGHT:		//���������ꂽ��
			BGScrX += 0.5;
			break;
		*/

		case VK_F1:			//F1�L�[
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[1];			//�G�l�~�[�P�𑶍݂�����
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F2:			//F2�L�[
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[2];			//�G�l�~�[�P�𑶍݂�����
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F3:					//��F3�L�[
			Plr.Hp = 100;			//�v���C���[�𕜊�������
			Plr.Son = TRUE;			//���݂�TRUE��
			Plr.AniType = 0;
			Plr.AniNum =0;
			break;
		case VK_F4:					//��F4�L�[�������ꂽ��
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[5];			//�{�X�𑶍݂�����
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F5:					//��F5�L�[�������ꂽ��
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[3];			//�{�X�𑶍݂�����
					En[i].Son = TRUE;
					break;
				}
			}

			break;
		case VK_F6:					//��F6�������ꂽ��
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[4];			//�G�l�~�[�P�𑶍݂�����
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_SPACE:					//��6�������ꂽ��
			for(i = 0;i < 30;i++)
			{
				for(i = 0;i < ENE_MAX;i++)
				{
					if(!En[i].Son)
					{
						En[i] = EnemyNum[(int)(rand()%6+1)];			//�G�l�~�[�P�𑶍݂�����
						En[i].Son = TRUE;
						break;
					}
				}
			}
			break;


		case VK_F7:					//��F7�������ꂽ��
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[7];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case VK_F8:					//��F8�������ꂽ��
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[6];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x30:	//��0�L�[
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[8];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x31:	//��1�L�[
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[10];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		case 0x32:	//��2�L�[
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[12];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		
		/////////////////////////////////////////////////////////////////
		case 0x44:	//��D�L�[
			Plr.Hp --;
			break;

		//�V���b�g�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		case VK_NUMPAD0:	//�t���ϗ���	
			ShotFire(Plr.x+(Plr.w>>1)+(rand()%20-10),rand()%480,0,9,2);	//�e�̔���
			break;
		case VK_NUMPAD1:	//�t���ϐ���
			for(i = 0;i < 20;i++)
				ShotFire(640-i,rand()%480,0,10,2);	//���݂̎�ނ��P�O���ē����蔻����s��Ȃ�
			
			//�v���C���[�ƓK�����ɐ�����΂����
			if(Plr.x > 200-(Plr.w>>1))	//�L����X���W��200���傫�����
			{	
				Plr.x --;					//�L���������Ɉړ�
			}else						//�L����X���W��200�ȉ��Ȃ�
			{
				if(!(WMoveX <= 0))			//���[�܂ł������牽�����Ȃ�
					WorldX --;					//WordlX���|�P(Map���E�ɃX�N���[��
			}
			for(i = 0;i < ENE_MAX;i++)
				if(En[i].Son)	En[i].x --;


			break;
		case VK_NUMPAD2:	//���̃o���A
			ShotFire(Plr.x+(rand()%Plr.w),Plr.y+(rand()%Plr.h),0,8,2);
			break;
		case VK_NUMPAD3:	//�������
			for(i = 0;i < 40;i++)
				if(rand()%3 == 1)	ShotFire(i*16,rand()%48-48,0,4,2);
			break;
		case VK_NUMPAD4:	//���I�̗���
			ShotFire(Plr.x+(Plr.w>>1)+(rand()%64-32),rand()%480,0,11+rand()%5,2);	//�e�̔���
			break;
		case VK_NUMPAD5:	//�|�C�Y��
			for(i = 0 ;i < 10;i++)
			ShotFire(rand()%640,rand()%480,0,17,1);
			break;
		case VK_NUMPAD6:	//���̔j��
			ShotFire(Swd.x+(Swd.w>>1),Swd.y+(Swd.h>>1),0,19,2);
			break;

		case VK_NUMPAD9:	//�|�[�Y
			GameNum = 5;
			break;

		case VK_TAB:	//�X�e�[�W�I���ɖ߂�
			GameNum = 4;	//�Q�[���̏�ʂ������l���S�Ɂi�X�e�[�W�I��
			break;

		case VK_NUMPAD7:
			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[11];
					En[i].Son = TRUE;
					break;
				}
			}
			break;
		//�����ʉ���炷
		case VK_NUMPAD8:
			DS_Play( 1, FALSE );

			for(i = 0;i < ENE_MAX;i++)
			{
				if(!En[i].Son)
				{
					En[i] = EnemyNum[9];
					En[i].Son = TRUE;
					break;
				}
			}
			break;



		case 0x52:	//���q�L�[
			lpDDPal->GetEntries(0,0,255,SubPal);
			//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���f�N�������g���A�O�i���j�ɋ߂Â�����
			for(i = 0;i < 255;i++)
			{
				//if(SubPal[i].peRed > 0)
				//	SubPal[i].peRed --;	//�Ԃ̗v�f�����炷			
				if(SubPal[i].peGreen > 0)
					SubPal[i].peGreen --;	//�΂̗v�f���ւ炷
				if(SubPal[i].peBlue > 0)
					SubPal[i].peBlue --;		//�̗v�f�����炷
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
		case 0x47:	//���f�L�[
			lpDDPal->GetEntries(0,0,255,SubPal);
			//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���f�N�������g���A�O�i���j�ɋ߂Â�����
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed > 0)
					SubPal[i].peRed --;	//�Ԃ̗v�f�����炷			
				//if(SubPal[i].peGreen > 0)
				//	SubPal[i].peGreen --;	//�΂̗v�f���ւ炷
				if(SubPal[i].peBlue > 0)
					SubPal[i].peBlue --;		//�̗v�f�����炷
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
		case 0x42:	//���a�L�[
			lpDDPal->GetEntries(0,0,255,SubPal);
			//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���f�N�������g���A�O�i���j�ɋ߂Â�����
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed > 0)
					SubPal[i].peRed --;	//�Ԃ̗v�f�����炷			
				if(SubPal[i].peGreen > 0)
					SubPal[i].peGreen --;	//�΂̗v�f���ւ炷
				//if(SubPal[i].peBlue > 0)
				//	SubPal[i].peBlue --;		//�̗v�f�����炷
			}
			lpDDPal->SetEntries(0,0,256,SubPal);

			break;

		case VK_ADD:		//�����y��炷(	+�@�L�[
			// �Z�O�����g�̉��t
			DM_Play(0);
			break;
		case VK_MULTIPLY:
			DM_Play(1);
			break;
		case VK_SUBTRACT:	//�����y���~�߂�i�@-�@�L�[
			DM_Stop(-1);
			break;




		case VK_DIVIDE:	//�u/�v�L�[
			lpDDPal->GetEntries(0,0,255,SubPal);
			//�擾�����p���b�g�f�[�^�́A�ԁA�΁A�̗v�f���N�������g���A���̐F�ɋ߂Â�����
			for(i = 0;i < 255;i++)
			{
				if(SubPal[i].peRed < MainPal[i].peRed)
					SubPal[i].peRed ++;	//�Ԃ̗v�f�𑝂₷		
				if(SubPal[i].peGreen < MainPal[i].peGreen)
					SubPal[i].peGreen ++;	//�΂𑝂₷
				if(SubPal[i].peBlue < MainPal[i].peBlue)
					SubPal[i].peBlue ++;		//�𑝂₷
			}
			lpDDPal->SetEntries(0,0,256,SubPal);
			break;
			
		//case VK_F10:	//���̃L�[�{�[�h��F10�L�[���Ή����Ă��Ȃ�
		case VK_F11:
			/*
			//���F�̃O���f�[�V�����p���b�g�ɕύX
			lpDDPal->GetEntries(0,0,255,SubPal);
			for(i = 0;i < 255;i++)
			{
				SubPal[i].peRed = i;
				SubPal[i].peGreen = i;
				SubPal[i].peBlue = 0;
				SubPal[i].peFlags = PC_RESERVED;
			}
			lpDDPal->SetEntries(0,0,255,SubPal);	//�T�u�p���b�g���Z�b�g
			*/
			//���̃p���b�g�ɖ߂�
			lpDDPal->SetEntries(0,0,255,MainPal);
		
			break;

		//�X�N���[��
		case VK_PRIOR:	//��PageUp�L�[
			WorldX = +96;
			break;
		case VK_NEXT:	//��PageDown�L�[
			WorldX = -96;
			break;

		case VK_HOME:		//��HOME�L�[�i�������x�A�b�v
			FPS_ChangeNum ++;
			break;
		case VK_END:		//��END�L�[�i�������x�_�E��
			if(FPS_ChangeNum > 1)	FPS_ChangeNum --;
			break;

		case VK_ESCAPE:
			PostMessage( hWnd,WM_CLOSE,0,0 );	//WM_CLOSE�𔭐������A�E�B���h�E�����悤����
			break;
		}
		break;
	case WM_DESTROY:	//�E�B���h�E���I�����ꂽ��
		PostQuitMessage(0);
		break;
	default:	//��L�ȊO�̃��b�Z�[�W��Windows�ɔC����
		return	DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

