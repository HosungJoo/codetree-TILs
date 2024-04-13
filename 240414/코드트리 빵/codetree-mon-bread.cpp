#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct minfo { //사람에 대한 정보
	int forward; //몇번 편의점에 가는지
	int dest; //종착인지 아닌지
};

struct binfo {//건물에 대한 정보
	int x;
	int y;
};

struct bw { //편의점과 캠프 사이의 관계
	int x;
	int y;
	int dist;
	bool operator<(bw right)const {
		if (dist < right.dist)return true;
		else if (dist == right.dist) {
			if (x < right.x)return true;
			else if (x == right.x) {
				if (y < right.y)return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
};

int N, M; //N:격자의 크기 M:사람수
int map[15][15]; //사용한 basecamp 2, 도착한 편의점 3
int dx[] = { -1,0,0,1 };
int dy[] = { 0,-1,1,0 };
int visited[30][15][15];
vector<minfo>mans;
vector<binfo>bcamps;
vector<binfo>convi;
queue<binfo>q[30];

int main()
{
	cin >> N >> M;

	int camp = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j]) {
				bcamps.push_back({ i,j }); //베이스캠프 위치 받기
				camp++;
			}
		}
	}
	
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		convi.push_back({ x - 1,y - 1 }); //편의점 위치 받기
	}

	int cnt = 0;
	int ans = 0;

	while (1) {
		//1번
		if (mans.size() > 0) { //격자의 사람들이 있음
			for (int i = 0; i < mans.size(); i++) {
				if (mans[i].dest == 1) continue;
				binfo now = q[i].front(); //현재 사람의 정보
				q[i].pop();

				// 2번 편의점 도착
				if (now.x == convi[mans[i].forward].x && now.y == convi[mans[i].forward].y) {
					mans[i].dest = 1;
					map[now.x][now.y] = 3;
					ans = max(ans, visited[i][now.x][now.y]);
					continue;
				}

				for (int j = 0; j < 4; j++) {
					int nx = now.x + dx[j];
					int ny = now.y + dy[j];

					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
					if (visited[i][nx][ny]!=0) continue;
					if (map[nx][ny] == 2 || map[nx][ny] == 3) continue;

					visited[i][nx][ny] = visited[i][now.x][now.y] + 1;
					q[i].push({ nx,ny });
				}
				
			}
		}
		//3번
		if (cnt < M) { //아직 사람들 다 안나옴
			//편의점 기준 베이스 캠프 거리 확인해서 사람 배치
			//편의점 정보
			int cx = convi[cnt].x;
			int cy = convi[cnt].y;
			vector<bw>dists; //거리와 좌표를 담는 벡터
			for (int i = 0; i < camp; i++) {
				int bx = bcamps[i].x;
				int by = bcamps[i].y;
				if (map[bx][by] == 2) continue;//사용한 베이스캠프

				dists.push_back({ bx,by,abs(bx - cx) + abs(by - cy) });
			}
			sort(dists.begin(), dists.end()); //가장 가까운 베이스 캠프 정렬
			mans.push_back({ cnt,0 }); //사람이 베이스 캠프에 감
			map[dists[0].x][dists[0].y] = 2;//사용된 베이스 캠프
			q[cnt].push({ dists[0].x ,dists[0].y }); //이동가능
			visited[cnt][dists[0].x][dists[0].y] = cnt+1; //방문처리
			dists.clear(); //비워주기
			cnt++;
		}
		if(cnt >=M){
			bool done = 1;
			for (int i = 0; i < M; i++) {
				if (mans[i].dest == 0) {
					done = 0;
					break;
				}
			}
			if (done) break;
		}
	}

	cout << ans;

	return 0;
}