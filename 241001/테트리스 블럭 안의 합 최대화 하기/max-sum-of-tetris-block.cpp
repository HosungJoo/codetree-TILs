#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int map[201][201];
int ans;

void oneBlock(int x,int y) {

	//오른쪽
	int Rsum = 0;
	for (int i = 0; i < 4; ++i) {
		if (y + 3 >= M) break; //끝이 넘어가면 못함
		Rsum += map[x][y + i];
	}

	ans = max(ans, Rsum);

	//왼쪽
	int Lsum = 0;
	for (int i = 0; i < 4; ++i) {
		if (y - 3 < 0) break; //끝이 넘어가면 못함
		Lsum = map[x][y - i];
	}

	ans = max(ans, Lsum);

	//위
	int Usum = 0;
	for (int i = 0; i < 4; ++i) {
		if (x - 3 < 0) break; //끝이 넘어가면 못함
		Usum += map[x - i][y];
	}
	
	ans = max(ans, Usum);

	//아래
	int Dsum = 0;
	for (int i = 0; i < 4; ++i) {
		if (x + 3 >= N) break; //끝이 넘어가면 못함
		Dsum += map[x + i][y];
	}

	ans = max(ans, Dsum);
	return;
}

void sQuare(int x, int y) {
	if (x + 1 >= N || y + 1 >= M) return; //사각형이 넘어감
	ans = max(ans, map[x][y] + map[x + 1][y] + map[x][y + 1] + map[x + 1][y + 1]);
	return;
}

void ziGzag(int x, int y) {
	//아래
	if (x + 2 < N&&y + 1 < M) {
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y + 1]);
	}

	//오른쪽
	if (x - 1 >= 0 && y + 2 < M) {
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x - 1][y + 1] + map[x - 1][y + 2]);
	}

	//위
	if (x - 2 >= 0 && y - 1 >= 0) {
		ans = max(ans, map[x][y] + map[x-1][y] + map[x - 1][y - 1] + map[x - 2][y - 1]);
	}

	//왼쪽
	if (x + 1 < N&&y - 2 >= 0) {
		ans = max(ans, map[x][y] + map[x][y-1] + map[x + 1][y - 1] + map[x + 1][y - 2]);
	}
	return;
}

void niEun(int x, int y) {

	//아래
	if (x + 2 < N&&y + 1 < M) {
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 2][y] + map[x + 2][y + 1]);
	}

	//오른쪽
	if (x - 1 >= 0 && y + 2 < M) {
		ans = max(ans, map[x][y] + map[x][y+1] + map[x][y+2] + map[x - 1][y + 2]);
	}

	//위
	if (x - 2 >= 0 && y - 1 >= 0) {
		ans = max(ans, map[x][y] + map[x - 1][y] + map[x - 2][y] + map[x - 2][y - 1]);
	}

	//왼쪽
	if (x + 1 < N  && y - 2 >= 0) {
		ans = max(ans, map[x][y] + map[x][y - 1] + map[x][y - 2] + map[x + 1][y - 2]);
	}

	return;
}

void san(int x, int y) {
	//아래
	if (x + 2 < N&&y + 1 < M) {
		ans = max(ans, map[x][y] + map[x + 1][y] + map[x + 1][y + 1] + map[x + 2][y]);
	}

	//오른쪽
	if (x - 1 >= 0 && y + 2 < M) {
		ans = max(ans, map[x][y] + map[x][y + 1] + map[x-1][y + 1] + map[x][y + 2]);
	}

	//위
	if (x - 2 >= 0&&y - 1 >= 0) {
		ans = max(ans, map[x][y] + map[x - 1][y] + map[x - 1][y - 1] + map[x - 2][y]);
	}

	//왼쪽
	if (x + 1 < N&&y - 2 >= 0) {
		ans = max(ans, map[x][y] + map[x][y - 1] + map[x + 1][y - 1] + map[x][y - 2]);
	}
	return;
}

int main()
{
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			
			oneBlock(i, j); //일자 블럭
			sQuare(i, j); //사각 블럭
			ziGzag(i, j); //지그재그 블럭
			niEun(i, j); //니은 블럭
			san(i, j); //산 블럭
		}
	}

	cout << ans;

	return 0;
}