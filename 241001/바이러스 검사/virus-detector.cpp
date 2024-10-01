#include<iostream>

using namespace std;

int N; //식당의 수
int dining[1000000]; //식당 배열
int leader;
int follower;
int ans;

int main()
{
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> dining[i];
	}

	cin >> leader >> follower;

	for (int i = 0; i < N; i++) {
		int temp = dining[i];
		temp -= leader; //팀장 뺴기
		++ans;
		if (temp > 0) {
			if (temp / follower > 0) {
				if (temp%follower == 0) {
					ans += (temp / follower);
				}
				else {
					ans += ((temp / follower) + 1);
				}
			}
			else {
				if (temp%follower > 0) {
					++ans;
				}
			}
		}
	}

	cout << ans;

	return 0;
}