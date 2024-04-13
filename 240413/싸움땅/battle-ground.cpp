#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct info {
	int x;
	int y;
	int dir;
	int stat;
	int gun;
	int tot;
};

struct play{
	int in_player;
	int number;
	info player;
};

int N, M, K; //N:격자의 크기,M:사람 수, K는 라운드 수
int dx[] = { -1,0,1,0 }; //0:상 1:우 2:하 3:좌 시계방향
int dy[] = { 0,1,0,-1 };
vector<info>players; //player buffer
priority_queue<int>gun[20][20]; //0일 경우 pq에 값이 없음 size=0
play map[20][20]; //map에 player 있는지 확인
int score[30];

int main()
{
	cin >> N >> M >> K;

	//총 pq에 값 저장
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) {
			int power;
			cin >> power;
			if (power != 0) gun[i][j].push(power); //총 능력치 있으면 추가
		}
	}

	//player 입력받기
	for (int i = 0; i < M; i++) {
		int x, y, dir, stat;
		cin >> x >> y >> dir >> stat;
		players.push_back({ x - 1,y - 1,dir,stat,0,stat });
		map[x - 1][y - 1] = { 1,i,players[i] };
	}

	//라운드 진행 //0:상 1:우 2:하 3:좌 시계방향
	while (K != 0) {
		for (int i = 0; i < M; i++) {
			//현재 이동 player 정보
			int px = players[i].x;
			int py = players[i].y;
			int pdir = players[i].dir;
			int pstat = players[i].stat;
			int pgun = players[i].gun;
			int ptot = players[i].tot;

			//1-1 player이동
			int nx = px + dx[pdir];
			int ny = py + dy[pdir];
			map[px][py].in_player = 0; //이제 현재 자리에서 벗어남

			//Out of bound 정반대로 방향 바꿈
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
				pdir = (pdir + 2) % 4;
				nx = px + dx[pdir];
				ny = py + dy[pdir];
			}

			//2-1 이동한 방향에 다른 player가 없음
			if (!map[nx][ny].in_player) {
				if (!gun[nx][ny].empty()) { //칸에 총 있으면
					if (pgun == 0) { //player가 총 없으면
						pgun = gun[nx][ny].top();
						gun[nx][ny].pop(); //총 가져감
					}
					else { //player 총 있음
						if (pgun < gun[nx][ny].top()) { //바닥에 총이 더쎔
							gun[nx][ny].push(pgun); //총 바닥에 내려놓음
							pgun = gun[nx][ny].top();
							gun[nx][ny].pop(); //총 가져감
						}
					}
				}
				//정보 저장
				players[i] = { nx,ny,pdir,pstat,pgun,pstat + pgun };
				map[nx][ny] = { 1,i,players[i] };
			}
			else { //2-2 player 있음
				//2-2-1 대결
				//진 player 정보
				int lx, ly, ldir, lstat, lgun, ltot, lnum;
				//이긴 player 정보
				int wstat, wgun, wtot, wnum, wdir;
				if (ptot > map[nx][ny].player.tot) { //움직인 player가 이김
					score[i] += ptot - map[nx][ny].player.tot; 
					//진 사람 정보
					lx = nx; ly = ny; ldir = map[nx][ny].player.dir;
					lstat = map[nx][ny].player.stat; lgun = map[nx][ny].player.gun;
					ltot = map[nx][ny].player.tot; lnum = map[nx][ny].number;
					//이긴 사람 정보
					wstat = pstat; wgun = pgun; wtot = ptot; wnum = i; wdir = pdir;
				}
				else if(ptot < map[nx][ny].player.tot){ //상대player 이김
					score[map[nx][ny].number] += map[nx][ny].player.tot - ptot;
					//진 사람 정보
					lx = nx; ly = ny; ldir = pdir; lstat = pstat; lgun = pgun;
					ltot = ptot; lnum = i;
					//이긴 사람 정보
					wstat = map[nx][ny].player.stat; wgun = map[nx][ny].player.gun;
					wtot = map[nx][ny].player.tot; wnum = map[nx][ny].number;
					wdir = map[nx][ny].player.dir;
				}
				else { //비김
					if (pstat > map[nx][ny].player.stat) { //초기 능력치가 움직인 player가 높음
						score[i] += ptot - map[nx][ny].player.tot;
						//진 사람 정보
						lx = nx; ly = ny; ldir = map[nx][ny].player.dir;
						lstat = map[nx][ny].player.stat; lgun = map[nx][ny].player.gun;
						ltot = map[nx][ny].player.tot; lnum = map[nx][ny].number;
						//이긴 사람 정보
						wstat = pstat; wgun = pgun; wtot = ptot; wnum = i; wdir = pdir;
					}
					else { //상대 player가 초기 능력치가 높음
						score[map[nx][ny].number] += map[nx][ny].player.tot - ptot;
						//진 사람 정보
						lx = nx; ly = ny; ldir = pdir; lstat = pstat; lgun = pgun;
						ltot = ptot; lnum = i;
						//이긴 사람 정보
						wstat = map[nx][ny].player.stat; wgun = map[nx][ny].player.gun;
						wtot = map[nx][ny].player.tot; wnum = map[nx][ny].number;
						wdir = map[nx][ny].player.dir;
					}
				}
				//2-2-2 진 플레이어 행동
				gun[nx][ny].push(lgun);
				lgun = 0; //총만 버림
				//이동
				int lnx = lx + dx[ldir];
				int lny = ly + dy[ldir];

				//이동한 곳이 player가 있거나 바깥이면
				if (lnx < 0 || lny < 0 || lnx >= N || lny >= N) {
					while (1) { //시계방향으로 90도씩 갈 수 있을 때까지 회전
						ldir = (ldir + 1) % 4; //90도 돌림
						lnx = lx + dx[ldir];
						lny = ly + dy[ldir];
						if (lnx < 0 || lny < 0 || lnx >= N || lny >= N) continue;
						if (!map[lnx][lny].in_player) {
							break;
						}
					}
				}
				if (map[lnx][lny].in_player) {
					while (1) { //시계방향으로 90도씩 갈 수 있을 때까지 회전
						ldir = (ldir + 1) % 4; //90도 돌림
						lnx = lx + dx[ldir];
						lny = ly + dy[ldir];
						if (lnx < 0 || lny < 0 || lnx >= N || lny >= N) continue;
						if (!map[lnx][lny].in_player) {
							break;
						}
					}
				}

				//도착한자리에 총이 있다면
				if (!gun[lnx][lny].empty()) { //칸에 총 있으면
					lgun = gun[lnx][lny].top();
					gun[lnx][lny].pop(); //총 가져감
				}

				//진 플레이어 저장
				players[lnum] = { lnx,lny,ldir,lstat,lgun,lgun + lstat };
				map[lnx][lny] = { 1,lnum,players[lnum] };

				//2-2-3 이긴 플레이어 행동
				if (wgun < gun[nx][ny].top()) { //바닥에 총이 더쎔
					gun[nx][ny].push(wgun); //총 바닥에 내려놓음
					wgun = gun[nx][ny].top();
					gun[nx][ny].pop(); //총 가져감
				}

				//이긴 플레이어 저장
				players[wnum] = { nx,ny,wdir,wstat,wgun,wgun + wstat };
				map[nx][ny] = { 1,wnum,players[wnum] };
			}
		}
		K--;
	}

	for (int i = 0; i < M; i++) {
		cout << score[i] << " ";
	}
	
	return 0;
}