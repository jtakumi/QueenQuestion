#include<stdio.h>
#include<time.h>

#define N 7
#define QUEEN 1
#define EMPTY 0
#define OK 1
#define NG 0

void printQueen(int);
int check(int, int, int, int, int);
int checkQueen(int);
void nQueen(int,int,int);
void initQueen(int);

int resolve = 0;

int board[N][N];

void printQueen(int n) {
	int i, j;
	printf("%d個目の解\n", resolve);
	//全マスを表示
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			if (board[j][i] == QUEEN) {
				printf("Q");
			}
			else {
				printf("*");
			}
		}
		printf("\n");
	}
	printf("\n\n");
   }


/*指定された方向に他のクイーンがないか判断
n = 1方向のますの数
i = クイーンの位置の列番号
j = クイーンの位置の行番号
di = 列番号の増加量
dj = 行番号の増加量
*/

	int check(int n, int i, int j, int di, int dj) {
		int k;
		int ii, jj;
		for (k = 1; k < n; k++) {
			//(di,dj)方向にｋマスを進める
			ii = i + di * k;
			jj = j + dj * k;
			if (ii >= n || ii < 0 || jj >= n || jj < 0) {
				break;
			}
			if (board[j + dj * k][i + di * k] == QUEEN) {
				//マスの上にクイーンがあればNGを返す
				return NG;
			}

		}
		//その方向にクイーンがないのでOKを返す
		return OK;
	}

	/*
		Nクイーン問題を満たしているかどうかを判断
		n:1方向のマスの数
		*/
	int checkQueen(int n) {
		int i, j;
		//クイーンがあるマスを探索
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				if (board[j][i] == QUEEN) {
					/*クイーンのあるマスから縦横斜めに
					クイーンがあるかどうかをチェック*/
					//左方向をチェック
					if (!check(n, i, j, -1, 0)) {
						return NG;
					}
					//右方向をチェック
					if (!check(n, i, j, 1, 0)) {
						return NG;
					}
					//下方向をチェック
					if (!check(n, i, j, 0, -1)) {
						return NG;
					}
					//上方向をチェック
					if (!check(n, i, j, 0, 1)) {
						return NG;
					}
					//左下方向をチェック
					if (!check(n, i, j, -1, -1)) {
						return NG;
					}
					//左上方向をチェック
					if (!check(n, i, j, -1, 1)) {
						return NG;
					}
					//右下方向をチェック
					if (!check(n, i, j, 1, -1)) {
						return NG;
					}
					//右上方向をチェック
					if (!check(n, i, j, 1, 1)) {
						return NG;
					}
				}
			}
		}
		return OK;
	}

	/*
	n:1方向のマスの数
	q:配置済みのクイーンの数
	k:配置開始
	*/

	void nQueen(int n, int q, int k) {
		int i, j;
		int l;

		if (q == n) {
			//n個クイーン設置済みの場合
			if (checkQueen(n)) {
				//Nクイーン問題を満たしている場合

				/*解の数をインクリメント*/
				resolve++;

				/*チェス盤を表示*/
				printQueen(n);
			}
			return;
		}
		/*配置位置の開始点から順に
		クイーンを配置していく*/
		for (l = k; l < n * n; l++) {
			/*配置位置より行番号と列番号を算出*/
			j = l / n;
			i = l % n;
			/*(i,j)マスにクイーンを置く*/
			board[j][i] = QUEEN;
			/*次のクイーンを置く*/
			nQueen(n, q + 1, l + 1);
			/*(i,j)マスからクイーンを取り除く*/
			board[j][i] = EMPTY;
		}
	}

	/*チェス盤の初期化
	n:1方向のマスの数
	*/

	void initQueen(int n) {
		int i, j;
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				/*マスを空にする*/
				board[j][i] = EMPTY;
			}
		}
	}

	int main(void) {
		clock_t start, end;
		/*チェス盤の初期化*/
		initQueen(N);
		start = clock();
		nQueen(N, 0, 0);
		end = clock();
		/*処理時間の表示*/
		printf("処理時間 = %.2f[s]", (double)(end- start) / CLOCKS_PER_SEC);
	}