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
	printf("%d�ڂ̉�\n", resolve);
	//�S�}�X��\��
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


/*�w�肳�ꂽ�����ɑ��̃N�C�[�����Ȃ������f
n = 1�����̂܂��̐�
i = �N�C�[���̈ʒu�̗�ԍ�
j = �N�C�[���̈ʒu�̍s�ԍ�
di = ��ԍ��̑�����
dj = �s�ԍ��̑�����
*/

	int check(int n, int i, int j, int di, int dj) {
		int k;
		int ii, jj;
		for (k = 1; k < n; k++) {
			//(di,dj)�����ɂ��}�X��i�߂�
			ii = i + di * k;
			jj = j + dj * k;
			if (ii >= n || ii < 0 || jj >= n || jj < 0) {
				break;
			}
			if (board[j + dj * k][i + di * k] == QUEEN) {
				//�}�X�̏�ɃN�C�[���������NG��Ԃ�
				return NG;
			}

		}
		//���̕����ɃN�C�[�����Ȃ��̂�OK��Ԃ�
		return OK;
	}

	/*
		N�N�C�[�����𖞂����Ă��邩�ǂ����𔻒f
		n:1�����̃}�X�̐�
		*/
	int checkQueen(int n) {
		int i, j;
		//�N�C�[��������}�X��T��
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				if (board[j][i] == QUEEN) {
					/*�N�C�[���̂���}�X����c���΂߂�
					�N�C�[�������邩�ǂ������`�F�b�N*/
					//���������`�F�b�N
					if (!check(n, i, j, -1, 0)) {
						return NG;
					}
					//�E�������`�F�b�N
					if (!check(n, i, j, 1, 0)) {
						return NG;
					}
					//���������`�F�b�N
					if (!check(n, i, j, 0, -1)) {
						return NG;
					}
					//��������`�F�b�N
					if (!check(n, i, j, 0, 1)) {
						return NG;
					}
					//�����������`�F�b�N
					if (!check(n, i, j, -1, -1)) {
						return NG;
					}
					//����������`�F�b�N
					if (!check(n, i, j, -1, 1)) {
						return NG;
					}
					//�E���������`�F�b�N
					if (!check(n, i, j, 1, -1)) {
						return NG;
					}
					//�E��������`�F�b�N
					if (!check(n, i, j, 1, 1)) {
						return NG;
					}
				}
			}
		}
		return OK;
	}

	/*
	n:1�����̃}�X�̐�
	q:�z�u�ς݂̃N�C�[���̐�
	k:�z�u�J�n
	*/

	void nQueen(int n, int q, int k) {
		int i, j;
		int l;

		if (q == n) {
			//n�N�C�[���ݒu�ς݂̏ꍇ
			if (checkQueen(n)) {
				//N�N�C�[�����𖞂����Ă���ꍇ

				/*���̐����C���N�������g*/
				resolve++;

				/*�`�F�X�Ղ�\��*/
				printQueen(n);
			}
			return;
		}
		/*�z�u�ʒu�̊J�n�_���珇��
		�N�C�[����z�u���Ă���*/
		for (l = k; l < n * n; l++) {
			/*�z�u�ʒu���s�ԍ��Ɨ�ԍ����Z�o*/
			j = l / n;
			i = l % n;
			/*(i,j)�}�X�ɃN�C�[����u��*/
			board[j][i] = QUEEN;
			/*���̃N�C�[����u��*/
			nQueen(n, q + 1, l + 1);
			/*(i,j)�}�X����N�C�[������菜��*/
			board[j][i] = EMPTY;
		}
	}

	/*�`�F�X�Ղ̏�����
	n:1�����̃}�X�̐�
	*/

	void initQueen(int n) {
		int i, j;
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				/*�}�X����ɂ���*/
				board[j][i] = EMPTY;
			}
		}
	}

	int main(void) {
		clock_t start, end;
		/*�`�F�X�Ղ̏�����*/
		initQueen(N);
		start = clock();
		nQueen(N, 0, 0);
		end = clock();
		/*�������Ԃ̕\��*/
		printf("�������� = %.2f[s]", (double)(end- start) / CLOCKS_PER_SEC);
	}