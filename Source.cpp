#include "DxLib.h"

//▼▼変数等の宣言部▼▼▼▼
float mX;			//マリオX座標
float mY;			//マリオY座標
float mXS;			//マリオ加速
int mYS;			//マリオYスピード
int smG;			//チビマリオ画像
int jmG[2];			//マリオジャンプ画像(0,左 1,右)
int smGR[5];		//マリオ右アニメーション画像
int smGL[5];		//マリオ左アニメーション画像
int mRC;			//マリオ右アニメーションカウント
int mLC;			//マリオ左アニメーションカウント
int mD;				//マリオの向き(0,左 1,右)
int tC;				//テストアニメーションカウント
//▲▲変数等の宣言部▲▲▲▲

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);	//ウィンドウモードにする
	SetGraphMode(1024, 896, 32);	//ウィンドウサイズを設定する

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	//▼▼この辺に初期化処理▼▼▼▼
	mX = 100;
	mY = 200;
	mXS = 4;
	smG = LoadGraph("マリオ素材\\チビマリオ.png");
	LoadDivGraph("マリオ素材\\チビマリオ歩き右.png", 5, 5, 1, 60, 64, smGR);
	LoadDivGraph("マリオ素材\\チビマリオ歩き左.png", 5, 5, 1, 60, 64, smGL);
	LoadDivGraph("マリオ素材\\マリオジャンプ.png", 2, 2, 1, 64, 64, jmG);
	tC = 0;
	mRC = 0;
	mLC = 0;
	mD = 1;
	//▲▲この辺に初期化処理▲▲▲▲

	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		//▼▼この辺に更新処理▼▼▼▼
		//右キー押したとき
		//if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
		//	mX += mXS;
		//	mRC++;
		//	mD = 1;
		//	//右キー押しつつBキーを押したとき
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


		//左キー押したとき
		//if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
		//	mX -= mXS;
		//	mLC++;
		//	mD = 0;
		//	//左キー押しつつBキーを押したとき
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


		//ジャンプ処理
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




		//左右移動時のアニメーションカウント
		if (mRC == 20) {
			mRC = 0;
		}
		if (mLC == 20) {
			mLC = 0;
		}
		//▲▲この辺に更新処理▲▲▲▲

		//▼▼この辺に描画処理▼▼▼▼
		//止まってる時の画像
		if (mRC == -1 && mLC == -1) {
			//左向き
			if (mD == 1 && mY >= 300) {
				DrawGraph(mX, mY, smG, TRUE);
			}
			//右向き
			else if (mD == 0 && mY >= 300) {
				DrawTurnGraph(mX, mY, smG, TRUE);
			}
			else if (mY <= 300) {
				DrawGraph(mX, mY, jmG[mD], TRUE);
			}
		}
		//左右移動時のアニメーション画像
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
		//▲▲この辺に描画処理▲▲▲▲

		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}