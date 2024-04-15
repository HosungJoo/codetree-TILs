#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

struct sinfo {
	int x; //가운데 셀 x
	int y; // 가운데 셀 y
	int gate;
};

struct rinfo {
	int x;
	int y;
};

int R, C, K;
int ans;
int map[70][70];
int dx[] = { -1,0,1,0 }; //시계방향 0상 1:우 2:하 3:좌
int dy[] = { 0,1,0,-1 };
vector<sinfo>spaces;

int goRobot(int x, int y) {
	queue<rinfo>q;
	int visited[70][70] = { 0, };
	q.push({ x,y });
	visited[x][y] = 1;

	int max_r = 0;

	while (!q.empty()) {
		rinfo now = q.front();
		q.pop();
		visited[now.x][now.y] = 1;

		max_r = max(max_r, now.x);

		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];

			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (map[nx][ny] == 0)continue;
			if (visited[nx][ny]) continue;
			if (map[now.x][now.y] <= -1) {
				q.push({ nx,ny });
			}
			else {
				if (map[now.x][now.y] == map[nx][ny] || (map[now.x][now.y] + map[nx][ny])==0) {
					q.push({ nx,ny });
				}
			}
		}
	}
	return max_r;
}

int main() {

	cin >> R >> C >> K;

	for (int i = 0; i < K; i++) {
		int fall_col, gate;
		cin >> fall_col >> gate;
		spaces.push_back({ -2,fall_col - 1,gate });
	}

	for (int sp = 0; sp < K; sp++) {
		//우주선 정보
		int cx = spaces[sp].x;
		int cy = spaces[sp].y;
		int gate = spaces[sp].gate;

		while (1) { //시계방향 0:상 1:우 2:하 3:좌
			bool stage2 = 0;
			bool stage3 = 0;
			bool sstop = 0;

			//1번
			int nx = cx + dx[2];
			int ny = cy + dy[2];

			for (int dir = 0; dir < 4; dir++) {
				int nsx = nx + dx[dir];
				int nsy = ny + dy[dir];

				if (nsx < 0) continue;

				if (nsx >= R) {
					stage2 = 1;
					break;
				}

				if (nsx >= 0 && nsy >= 0 && nsx < R && nsy < C) {
					if (map[nsx][nsy] >= 1 || map[nsx][nsy] <= -1) {
						stage2 = 1;
						break;
					}
				}
			}

			if (!stage2) {
				cx = nx;
				cy = ny;
				gate = gate;
				continue;
			}

			//2번 시계방향 0:상 1:우 2:하 3:좌
			//좌 먼저
			nx = cx + dx[3];
			ny = cy + dy[3];

			for (int dir = 0; dir < 4; dir++) {
				int nsx = nx + dx[dir];
				int nsy = ny + dy[dir];

				if (nsy < 0) {
					stage3 = 1;
					break;
				}

				if (nsx >= 0 && nsy >= 0 && nsx < R && nsy < C) {
					if (map[nsx][nsy] >= 1 || map[nsx][nsy] <= -1) {
						stage3 = 1;
						break;
					}
				}
			}

			if (!stage3) {
				nx = cx + dx[3] + dx[2];
				ny = cy + dy[3] + dy[2];

				for (int dir = 0; dir < 4; dir++) {
					int nsx = nx + dx[dir];
					int nsy = ny + dy[dir];

					if (nsy < 0 || nsx >= R) {
						stage3 = 1;
						break;
					}

					if (nsx >= 0 && nsy >= 0 && nsx < R && nsy < C) {
						if (map[nsx][nsy] >= 1 || map[nsx][nsy] <= -1) {
							stage3 = 1;
							break;
						}
					}
				}

				if (!stage3) {
					cx = nx;
					cy = ny;
					gate = (gate + 4 - 1) % 4;
					continue;
				}
			}

			//3번 시계방향 0:상 1:우 2:하 3:좌

			nx = cx + dx[1];
			ny = cy + dy[1];

			for (int dir = 0; dir < 4; dir++) {
				int nsx = nx + dx[dir];
				int nsy = ny + dy[dir];

				if (nsy >= C) {
					sstop = 1;
					break;
				}

				if (nsx >= 0 && nsy >= 0 && nsx < R && nsy < C) {
					if (map[nsx][nsy] >= 1 || map[nsx][nsy] <= -1) {
						sstop = 1;
						break;
					}
				}
			}

			if (!sstop) {
				nx = cx + dx[1] + dx[2];
				ny = cy + dy[1] + dy[2];

				for (int dir = 0; dir < 4; dir++) {
					int nsx = nx + dx[dir];
					int nsy = ny + dy[dir];

					if (nsy >= C || nsx >= R) {
						sstop = 1;
						break;
					}

					if (nsx >= 0 && nsy >= 0 && nsx < R && nsy < C) {
						if (map[nsx][nsy] >= 1 || map[nsx][nsy] <= -1) {
							sstop = 1;
							break;
						}
					}
				}

				if (!sstop) {
					cx = nx;
					cy = ny;
					gate = (gate + 1) % 4;
					continue;
				}
			}

			//초기화 해야하는 지 확인
			bool rezero = 0;
			for (int dir = 0; dir < 4; dir++) {
				int nsx = cx + dx[dir];
				int nsy = cy + dy[dir];

				if (nsx < 0 || nsy < 0 || nsx >= R || nsy >= C) {
					rezero = 1;
					break;
				}
			}

			if (rezero) {
				memset(map, 0, sizeof(map));
				break;
			}
			else {
				map[cx][cy] = sp + 1;
				for (int dir = 0; dir < 4; dir++) {
					int nsx = cx + dx[dir];
					int nsy = cy + dy[dir];

					if (gate == dir) {
						map[nsx][nsy] = -(sp + 1);
					}
					else {
						map[nsx][nsy] = sp + 1;
					}
				}
				int score = goRobot(cx, cy);
				ans += (score + 1);
				break;
			}
		}

	}

	cout << ans;

	return 0;
}