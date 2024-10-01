#include <iostream>

using namespace std;

int N, M;
int map[200][200];
int ans = 0;

void line_blk(int x, int y) {

	int cnt = map[x][y];
	int nx = x;
	int ny = y;

	//오른쪽으로
	int right = cnt;
	bool setting = true;
	int brks = 1;
	
	while (1) {
		ny++;
		brks++;

		if (ny >= M) {
			setting = false;
			break;
		}

		right += map[nx][ny];

		if (brks == 4) break;
	}

	if (setting) {
		ans = max(ans, right);
	}
	ny = y;

	//왼쪽으로
	int left = cnt;
	setting = true;
	brks = 1;

	while (1) {
		ny--;
		brks++;

		if (ny < 0) {
			setting = false;
			break;
		}

		left += map[nx][ny];

		if (brks == 4) break;
	}

	if (setting) {
		ans = max(ans, left);
	}
	ny = y;

	//위쪽으로
	int up = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx--;
		brks++;

		if (nx < 0) {
			setting = false;
			break;
		}

		up += map[nx][ny];

		if (brks == 4) break;
	}

	if (setting) {
		ans = max(ans, up);
	}
	nx = x;

	//아래쪽으로
	int down = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx++;
		brks++;

		if (nx >= N) {
			setting = false;
			break;
		}

		down += map[nx][ny];

		if (brks == 4) break;
	}

	if (setting) {
		ans = max(ans, left);
	}
	nx = x;
}

void cube_blk(int x, int y) {
	if (x == N - 1 || y == M - 1) return;

	int brk = map[x][y] + map[x + 1][y] + map[x][y + 1] + map[x + 1][y + 1];
	ans = max(ans, brk);
}

void L_blk(int x, int y) {
	int cnt = map[x][y];
	int nx = x;
	int ny = y;

	//오른쪽으로
	int right = cnt;
	bool setting = true;
	int brks = 1;

	while (1) {
		ny++;
		brks++;

		if (ny >= M) {
			setting = false;
			break;
		}

		right += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {
		
		if (nx-1 >= 0) { //정방향
			ans = max(ans, right+map[nx-1][ny]);
		}
		if (nx + 1 < N) { //대칭
			ans = max(ans, right + map[nx + 1][ny]);
		}
		
	}

	nx = x;
	ny = y;

	//왼쪽으로
	int left = cnt;
	setting = true;
	brks = 1;

	while (1) {
		ny--;
		brks++;

		if (ny < 0) {
			setting = false;
			break;
		}

		left += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (nx - 1 >= 0) { //정방향
			ans = max(ans, left + map[nx - 1][ny]);
		}
		if (nx + 1 < N) { //대칭
			ans = max(ans, left + map[nx + 1][ny]);
		}
	}

	nx = x;
	ny = y;

	//위쪽으로
	int up = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx--;
		brks++;

		if (nx < 0) {
			setting = false;
			break;
		}

		up += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (ny - 1 >= 0) { //정방향
			ans = max(ans, up + map[nx][ny-1]);
		}
		if (ny + 1 < M) { //대칭
			ans = max(ans, up + map[nx][ny+1]);
		}
	}

	nx = x;
	ny = y;

	//아래쪽으로
	int down = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx++;
		brks++;

		if (nx >= N) {
			setting = false;
			break;
		}

		down += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (ny - 1 >= 0) { //정방향
			ans = max(ans, down + map[nx][ny - 1]);
		}
		if (ny + 1 < M) { //대칭
			ans = max(ans, down + map[nx][ny + 1]);
		}

	}
}

void N_blk(int x, int y) {
	int cnt = map[x][y];
	int nx = x;
	int ny = y;

	//오른쪽으로
	int right = cnt;
	bool setting = true;
	int brks = 1;

	while (1) {
		ny++;
		brks++;

		if (ny >= M) {
			setting = false;
			break;
		}

		right += map[nx][ny];

		if (brks == 2) break;
	}

	if (setting) {
		if (ny + 1 < M) {
			if (nx - 1 >= 0) { //정방향
				int r_u = map[nx - 1][ny] + map[nx - 1][ny + 1];
				ans = max(ans, right + r_u);
			}
			if (nx + 1 < N) { //대칭
				int r_d = map[nx + 1][ny] + map[nx + 1][ny + 1];
				ans = max(ans, right + r_d);
			}
		}
	}

	nx = x;
	ny = y;

	//왼쪽으로
	int left = cnt;
	setting = true;
	brks = 1;

	while (1) {
		ny--;
		brks++;

		if (ny < 0) {
			setting = false;
			break;
		}

		left += map[nx][ny];

		if (brks == 2) break;
	}

	if (setting) {
		if (ny - 1 >= 0) {
			if (nx - 1 >= 0) { //정방향
				int l_u = map[nx - 1][ny] + map[nx - 1][ny - 1];
				ans = max(ans, left + l_u);
			}
			if (nx + 1 < N) { //대칭
				int l_d = map[nx + 1][ny] + map[nx + 1][ny - 1];
				ans = max(ans, left + l_d);
			}
		}
	}

	nx = x;
	ny = y;

	//위쪽으로
	int up = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx--;
		brks++;

		if (nx < 0) {
			setting = false;
			break;
		}

		up += map[nx][ny];

		if (brks == 2) break;
	}

	if (setting) {
		if (nx - 1 >= 0) {
			if (ny - 1 >= 0) { //정방향
				ans = max(ans, up + map[nx][ny - 1] + map[nx-1][ny-1]);
			}
			if (ny + 1 < M) { //대칭
				ans = max(ans, up + map[nx][ny + 1] + map[nx-1][ny+1]);
			}
		}
	}

	nx = x;
	ny = y;

	//아래쪽으로
	int down = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx++;
		brks++;

		if (nx >= N) {
			setting = false;
			break;
		}

		up += map[nx][ny];

		if (brks == 2) break;
	}

	if (setting) {
		if (nx + 1 < N) {
			if (ny - 1 >= 0) { //정방향
				ans = max(ans, down + map[nx][ny - 1] + map[nx + 1][ny - 1]);
			}
			if (ny + 1 < M) { //대칭
				ans = max(ans, down + map[nx][ny + 1] + map[nx + 1][ny + 1]);
			}
		}
	}
}

void Y_blk(int x, int y) {
	int cnt = map[x][y];
	int nx = x;
	int ny = y;

	//오른쪽으로
	int right = cnt;
	bool setting = true;
	int brks = 1;

	while (1) {
		ny++;
		brks++;

		if (ny >= M) {
			setting = false;
			break;
		}

		right += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (nx - 1 >= 0) { //정방향
			ans = max(ans, right + map[nx - 1][ny-1]);
		}
		if (nx + 1 < N) { //대칭
			ans = max(ans, right + map[nx + 1][ny-1]);
		}

	}

	nx = x;
	ny = y;

	//왼쪽으로
	int left = cnt;
	setting = true;
	brks = 1;

	while (1) {
		ny--;
		brks++;

		if (ny < 0) {
			setting = false;
			break;
		}

		left += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (nx - 1 >= 0) { //정방향
			ans = max(ans, left + map[nx - 1][ny+1]);
		}
		if (nx + 1 < N) { //대칭
			ans = max(ans, left + map[nx + 1][ny+1]);
		}
	}

	nx = x;
	ny = y;

	//위쪽으로
	int up = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx--;
		brks++;

		if (nx < 0) {
			setting = false;
			break;
		}

		up += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (ny - 1 >= 0) { //정방향
			ans = max(ans, up + map[nx+1][ny - 1]);
		}
		if (ny + 1 < M) { //대칭
			ans = max(ans, up + map[nx+1][ny + 1]);
		}
	}

	nx = x;
	ny = y;

	//아래쪽으로
	int down = cnt;
	setting = true;
	brks = 1;

	while (1) {
		nx++;
		brks++;

		if (nx >= N) {
			setting = false;
			break;
		}

		down += map[nx][ny];

		if (brks == 3) break;
	}

	if (setting) {

		if (ny - 1 >= 0) { //정방향
			ans = max(ans, down + map[nx-1][ny - 1]);
		}
		if (ny + 1 < M) { //대칭
			ans = max(ans, down + map[nx-1][ny + 1]);
		}

	}
}

int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			line_blk(i, j);
			cube_blk(i, j);
			L_blk(i, j);
			N_blk(i, j);
			Y_blk(i, j);

		}
	}

	cout << ans;

	return 0;
}