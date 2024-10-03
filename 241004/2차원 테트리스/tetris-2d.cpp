#include<iostream>
#include<stack>

using namespace std;

int Red[4][6];
int Yellow[6][4];
int score;
int tot;
int K;

int main()
{
	cin >> K;

	for (int i = 0; i < K; i++) {
		int x, y, t;
		cin >> t >> x >> y;

		bool Rpush = 0;
		bool Ypush = 0;

		if (t == 1) {
			//Red
			
			for (int rc = 2; rc < 6; ++rc) {
				if (Red[x][rc] == 1) {
					Red[x][rc - 1] = 1; //전에 블럭에 쌓임
					break;
				}
				else if (Red[x][rc] == 0 && rc==5) {
					Red[x][rc] = 1;
				}
			}
			
			
			//Yellow
			for (int rr = 2; rr < 6; ++rr) {
				if (Yellow[rr][y] == 1) {
					Yellow[rr - 1][y] = 1; //전에 블럭에 쌓임
					break;
				}
				else if (Yellow[rr][y] == 0 && rr == 5) {
					Yellow[rr][y] = 1;
				}
			}

		}
		else if (t == 2) {

			//R
			for (int rc = 2; rc < 6; ++rc) {
				if (Red[x][rc] == 1) {
					Red[x][rc - 1] = 1;
					Red[x][rc - 2] = 1;
					break;
				}
				else if (Red[x][rc] == 0 && rc == 5) {
					Red[x][rc] = 1;
					Red[x][rc - 1] = 1;
				}
			}

			//Yellow
			for (int rr = 2; rr < 6; ++rr) {
				if (Yellow[rr][y] == 1 || Yellow[rr][y + 1] == 1) {

					Yellow[rr - 1][y] = 1; //전에 블럭에 쌓임
					Yellow[rr - 1][y+1] = 1; //전에 블럭에 쌓임
					break;

				}
				else if (Yellow[rr][y] == 0 && Yellow[rr][y + 1] == 0 && rr == 5) {
					Yellow[rr][y] = 1; //전에 블럭에 쌓임
					Yellow[rr][y + 1] = 1; //전에 블럭에 쌓임
				}
			}
		}
		else {
			//Red
			for (int rc = 2; rc < 6; ++rc) {
				if (Red[x][rc] == 1 || Red[x+1][rc]==1) {
						Red[x][rc - 1] = 1; //전에 블럭에 쌓임
						Red[x+1][rc - 1] = 1; //전에 블럭에 쌓임
						break;
				}
				else if (Red[x][rc] == 0 && Red[x + 1][rc] == 0 && rc == 5) {
					Red[x][rc] = 1; //전에 블럭에 쌓임
					Red[x + 1][rc] = 1; //전에 블럭에 쌓임
				}
			}

			//Yellow
			for (int rr = 2; rr < 6; ++rr) {
				if (Yellow[rr][y] == 1) {
						Yellow[rr - 1][y] = 1; //전에 블럭에 쌓임
						Yellow[rr - 2][y] = 1; //전에 블럭에 쌓임
						break;
				}
				else if (Yellow[rr][y] == 0 && rr == 5) {
					Yellow[rr][y] = 1; //전에 블럭에 쌓임
					Yellow[rr-1][y] = 1; //전에 블럭에 쌓임
				}
			}
		}
		//Red Zone 지우기
		for (int col = 2; col < 6; ++col) {
			int sum = 0;
			for (int row = 0; row < 4; ++row) {
				sum += Red[row][col];
			}
			if (sum == 4) {
				score++; //점수 획득
				Rpush = 1;
				for (int row = 0; row < 4; ++row) {
					Red[row][col] = 0;
				}
			}
		}

		if (Rpush) {

			stack<int>st[4];
			for (int row = 0; row < 4; ++row) {
				for (int col = 0; col < 6; ++col) {
					if (Red[row][col] == 1) {
						st[row].push(1);
					}
				}
			}

			for (int row = 0; row < 4; ++row) {
				for (int col = 5; col >= 0; --col) {
					if (st[row].empty()) {
						Red[row][col] = 0;
					}
					else {
						Red[row][col] = st[row].top();
						st[row].pop();
					}
				}
			}
		}

		int Rlrm = 0;
		for (int col = 0; col < 2; ++col) {
			for (int row = 0; row < 4; ++row) {
				if (Red[row][col] == 1) {
					Rlrm++;
					break;
				}
			}
		}

		if (Rlrm > 0) {
			for (int row = 0; row < 4; ++row) {
				for (int col = 4 - Rlrm + 1; col >= 0; --col) {
					Red[row][col + Rlrm] = Red[row][col]; //옆으로 밀기
				}
			}
		}

		for (int col = 0; col < 2; ++col) {
			for (int row = 0; row < 4; ++row) {
				if (Red[row][col] == 1) {
					Red[row][col] = 0;
				}
			}
		}
		

		//Yellow Zone지우기

		for (int row = 2; row < 6; ++row) {
			int sum = 0;
			for (int col = 0; col < 4; ++col) {
				sum += Yellow[row][col];
			}
			if (sum == 4) {
				Ypush = 1;
				score++;//점수 획득
				for (int col = 0; col < 4; ++col) {
					Yellow[row][col] = 0;
				}
			}
		}

		if (Ypush) {
			stack<int>st[4];
			for (int col = 0; col < 4; ++col) {
				for (int row = 0; row < 6; ++row) {
					if (Yellow[row][col] == 1) {
						st[col].push(1);
					}
				}
			}

			for (int col = 0; col < 4; ++col) {
				for (int row = 5; row >= 0; --row) {
					if (st[col].empty()) {
						Yellow[row][col] = 0;
					}
					else {
						Yellow[row][col] = st[col].top();
						st[col].pop();
					}
				}
			}
		}

		int Llrm = 0;
		for (int row = 0; row < 2; ++row) {
			for (int col= 0; col < 4; ++col) {
				if (Yellow[row][col] == 1) {
					Llrm++;
					break;
				}
			}
		}


		if (Llrm > 0) {
			for (int col = 0; col < 4; ++col) {
				for (int row = 4 - Rlrm + 1; row >= 0; --row) {
					Yellow[row+Llrm][col] = Yellow[row][col]; //옆으로 밀기
				}
			}
		}

		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (Yellow[row][col] == 1) {
					Yellow[row][col] = 0;
				}
			}
		}
	}

	cout << score << "\n";

	for (int i = 0; i < 4; ++i) {
		for (int j = 2; j < 6; ++j) {
			if (Red[i][j] == 1) tot += 1;
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 2; j < 6; ++j) {
			if (Yellow[j][i] == 1) tot += 1;
		}
	}

	cout << tot;

	return 0;
}