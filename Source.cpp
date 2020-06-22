#include "DxLib.h"

//�����ϐ����̐錾����������
float mX;			//�}���IX���W
float mY;			//�}���IY���W
float mXS;			//�}���I����
int mYS;			//�}���IY�X�s�[�h
int smG;			//�`�r�}���I�摜
int jmG[2];			//�}���I�W�����v�摜(0,�� 1,�E)
int smGR[5];		//�}���I�E�A�j���[�V�����摜
int smGL[5];		//�}���I���A�j���[�V�����摜
int mRC;			//�}���I�E�A�j���[�V�����J�E���g
int mLC;			//�}���I���A�j���[�V�����J�E���g
int mD;				//�}���I�̌���(0,�� 1,�E)
int tC;				//�e�X�g�A�j���[�V�����J�E���g
//�����ϐ����̐錾����������

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);	//�E�B���h�E���[�h�ɂ���
	SetGraphMode(1024, 896, 32);	//�E�B���h�E�T�C�Y��ݒ肷��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

	//�������̕ӂɏ�����������������
	mX = 100;
	mY = 200;
	mXS = 4;
	smG = LoadGraph("�}���I�f��\\�`�r�}���I.png");
	LoadDivGraph("�}���I�f��\\�`�r�}���I�����E.png", 5, 5, 1, 60, 64, smGR);
	LoadDivGraph("�}���I�f��\\�`�r�}���I������.png", 5, 5, 1, 60, 64, smGL);
	LoadDivGraph("�}���I�f��\\�}���I�W�����v.png", 2, 2, 1, 64, 64, jmG);
	tC = 0;
	mRC = 0;
	mLC = 0;
	mD = 1;
	//�������̕ӂɏ�����������������

	//���C������
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		//�������̕ӂɍX�V������������
		//�E�L�[�������Ƃ�
		//if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
		//	mX += mXS;
		//	mRC++;
		//	mD = 1;
		//	//�E�L�[������B�L�[���������Ƃ�
		//	if (CheckHitKey(KEY_INPUT_B) != 0) {
		//		if (mXS <= 12) {
		//			mXS += 0.25f;
		//		}
		//	}
		//	else {
		//		mXS = 4;
		//	}
		//}
		//else {
		//	mRC = -1;
		//}

		if (CheckHitKey(KEY_INPUT_RIGHT) != 0 && CheckHitKey(KEY_INPUT_B) != 0) {
			mX += mXS;
			mRC++;
			mD = 1;
			if (mXS < 12) {
				mXS += 0.25f;
			}
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) != 0 && CheckHitKey(KEY_INPUT_B) != 0) {
			mX -= mXS;
			mLC++;
			mD = 0;
			if (mXS < 12) {
				mXS += 0.25f;
			}
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
			if (mXS >= 4) {
				mXS -= 0.25f;
			}
			mX += mXS;
			mRC++;
			mD = 1;
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
			if (mXS >= 4) {
				mXS -= 0.25f;
			}
			mX -= mXS;
			mLC++;
			mD = 0;
		}
		else {
			mRC = -1;
			mLC = -1;
		}


		//���L�[�������Ƃ�
		//if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
		//	mX -= mXS;
		//	mLC++;
		//	mD = 0;
		//	//���L�[������B�L�[���������Ƃ�
		//	if (CheckHitKey(KEY_INPUT_B) != 0) {
		//		if (mXS <= 12) {
		//			mXS += 0.25f;
		//		}
		//	}
		//	else {
		//		mXS = 4;
		//	}
		//}
		//else {
		//	mLC = -1;
		//}


		//�W�����v����
		mY += mYS;
		if (mY >= 300) {
			if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
				mYS -= 20;
			}
		}
		if (mY >= 300 && mYS >= 0) {
			mYS = 0;
		}
		else {
			mYS++;
		}




		//���E�ړ����̃A�j���[�V�����J�E���g
		if (mRC == 20) {
			mRC = 0;
		}
		if (mLC == 20) {
			mLC = 0;
		}
		//�������̕ӂɍX�V������������

		//�������̕ӂɕ`�揈����������
		//�~�܂��Ă鎞�̉摜
		if (mRC == -1 && mLC == -1) {
			//������
			if (mD == 1 && mY >= 300) {
				DrawGraph(mX, mY, smG, TRUE);
			}
			//�E����
			else if (mD == 0 && mY >= 300) {
				DrawTurnGraph(mX, mY, smG, TRUE);
			}
			else if (mY <= 300) {
				DrawGraph(mX, mY, jmG[mD], TRUE);
			}
		}
		//���E�ړ����̃A�j���[�V�����摜
		else if (mRC >= 0 && mY >= 300) {
			DrawGraph(mX, mY, smGR[mRC / 5], TRUE);
		}
		else if (mLC >= 0 && mY >= 300) {
			DrawGraph(mX, mY, smGL[mLC / 5], TRUE);
		}
		else if (mY <= 300) {
			DrawGraph(mX, mY, jmG[mD], TRUE);
		}

		DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), FALSE);
		//�������̕ӂɕ`�揈����������

		ScreenFlip();		//����ʂƕ\��ʂ̓���
		ClearDrawScreen();	//����ʂ̕`���S�ď���
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}