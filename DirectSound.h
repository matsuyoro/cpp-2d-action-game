#if !defined __DIRECTSOUNDMACRO
#define __DIRECTSOUNDMACRO
//
BOOL DS_Init();						//_CNgTEhΜϊ»
BOOL DS_Load(int);						//Ήf[^πζΎ΅AZJ_obt@πμ¬·ιΦ
BOOL DS_Play(int,BOOL);				//ZJ_obt@ΜΔΆπs€Φ
BOOL DS_Stop(int);					//ZJ_obt@Μβ~πs€Φ
BOOL DS_VolumeChg(int,long);			//ZJ_obt@Μ{[πέθ·ιΦ
BOOL DS_PanChg(int,long);			//ZJ_obt@ΜpΜέθπs€Φ
BOOL DS_FrequencyChg(int,DWORD);		//ZJ_obt@ΜόgΜέθπs€Φ
void ReleaseDS();						//DirectSoundΦAΜIuWFNgΜπϊΜΦ
//
#endif
