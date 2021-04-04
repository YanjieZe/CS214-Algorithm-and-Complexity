#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int alpha(char c1, char c2) {
	return abs(c1 - c2);
}

int editDistanceDP(string &X, string &Y, const int &delta) {
	int m = X.length();
	int n = Y.length();
	vector<vector<int> > dp(m + 1);
	for (int i = 0; i <= m; ++i) {
		dp[i].resize(n + 1);
	}
	for (int j = 0; j <= n; ++j) {
		dp[0][j] = j > 0 ? dp[0][j - 1] + delta : 0;
	}
	for (int i = 1; i <= m; ++i) {
		dp[i][0] = dp[i - 1][0] + delta;
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = dp[i - 1][j - 1] + alpha(X[i - 1], Y[j - 1]);
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + delta);
			dp[i][j] = min(dp[i][j], dp[i][j - 1] + delta);
		}
	}
	return dp[m][n];
}

int editDistanceDP(string &X, string &Y, int xLow, int yLow, int xHigh, int yHigh, const int &delta, bool reverse, vector<int> &dist) {
	if(!reverse)
	{
		vector<vector<int> > dp(xHigh-xLow+1);
		for(int i=0; i<=xHigh-xLow; ++i)
			dp[i].resize(yHigh-yLow+1);
		for(int j=0; j<= yHigh-yLow;++j)
			dp[0][j] = j>0 ? dp[0][j-1] + delta : 0;
		
		dist.push_back(dp[0][yHigh-yLow]);
		for(int i=1; i<=xHigh-xLow; ++i)
		{
			dp[i][0] = dp[i-1][0] + delta;
			for(int j=1; j<= yHigh-yLow; ++j)
			{
				dp[i][j] = dp[i - 1][j - 1] + alpha(X[i - 1+xLow], Y[j - 1+yLow]);// here
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + delta);
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + delta);
			}
			dist.push_back(dp[i][yHigh-yLow]);
		}
		return 0;
	}
	else
	{
		vector<vector<int> > dp(xHigh-xLow+1);
		for(int i=0; i<=xHigh-xLow; ++i)
			dp[i].resize(yHigh-yLow+1);
		for(int j=0; j<= yHigh-yLow;++j)
			dp[0][j] = j>0 ? dp[0][j-1] + delta : 0;
		
		dist.push_back(dp[0][yHigh-yLow]);

		for(int i=1; i<=xHigh-xLow; ++i)
		{
			dp[i][0] = dp[i-1][0] + delta;
			for(int j=1; j<= yHigh-yLow; ++j)
			{
				dp[i][j] = dp[i - 1][j - 1] + alpha(X[xHigh-i], Y[yHigh-j]);// here
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + delta);
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + delta);
			}
			dist.push_back(dp[i][yHigh-yLow]);
		}
		return 0;
	}
	return 1;
}

int editDistanceDC(string &X, string &Y, int xLow, int yLow, int xHigh, int yHigh, const int &delta, vector<vector<int> > &points) {
	if (yHigh - yLow <= 1) {
		vector<int> dist;
		editDistanceDP(X, Y, xLow, yLow, xHigh, yHigh, delta, false, dist);
		int QMin = xLow;
		int Min = dist[0] + (xHigh - xLow) * delta;
		for (int q = 1; q <= xHigh - xLow; ++q) {
			int tmp = dist[q] + (xHigh - xLow - q) * delta;
			if (tmp < Min) {
				QMin = xLow + q;
				Min = tmp;
			}
		}
		if (QMin == xLow) {
			points[xLow].push_back(yLow);
		}
		else if ((QMin - xLow - 1) * delta + alpha(X[QMin - 1], Y[yHigh - 1]) <= (QMin - xLow) * delta + delta) {
			for (int x = xLow; x < QMin; ++x) {
				points[x].push_back(yLow);
			}
		}
		else {
			for (int x = xLow; x <= QMin; ++x) {
				points[x].push_back(yLow);
			}
		}
		for (int x = QMin; x <= xHigh; ++x) {
			points[x].push_back(yHigh);
		}
		return Min;
	}
	int yMid = (yLow + yHigh) / 2;
	vector<int> dist1, dist2;
	editDistanceDP(X, Y, xLow, yLow, xHigh, yMid, delta, false, dist1);
	editDistanceDP(X, Y, xLow, yMid, xHigh, yHigh, delta, true, dist2);
	int QMin = xLow;
	int Min = dist1[0] + dist2[xHigh - xLow];
	for (int q = 1; q <= xHigh - xLow; ++q) {
		int tmp = dist1[q] + dist2[xHigh - xLow - q];
		if (tmp < Min) {
			QMin = xLow + q;
			Min = tmp;
		}
	}
	points[QMin].push_back(yMid);
	return editDistanceDC(X, Y, xLow, yLow, QMin, yMid, delta, points) + editDistanceDC(X, Y, QMin, yMid, xHigh, yHigh, delta, points);
}

int editDistanceDPDC(string &X, string &Y, const int &delta, vector<vector<int> > &points) {
	return editDistanceDC(X, Y, 0, 0, X.length(), Y.length(), delta, points);
}


int main() {
	ifstream Xin("X.txt", ifstream::in);
	ifstream Yin("Y.txt", ifstream::in);
	if (!Xin.is_open() || !Yin.is_open()) {
		cerr << "Error: cannot open input file" << endl;
		exit(-1);
	}
	int delta = 13;
	string X, Y;
	Xin >> X;
	Yin >> Y;
	Xin.close();
	Yin.close();
	vector<vector<int> > points(X.length() + 1);
	cout << "DP:\t" << editDistanceDP(X, Y, delta) << endl;
	cout << "DP+DC:\t" << editDistanceDPDC(X, Y, delta, points) << endl;
	for (int i = 0; i < points.size(); ++i) {
		set<int> tmp(points[i].begin(), points[i].end());
		points[i].assign(tmp.begin(), tmp.end());
		sort(points[i].begin(), points[i].end());
	}
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[i].size(); ++j) {
			cout << "(" << i << ", " << points[i][j] << ") ";
		}
		cout << endl;
	}
	return 0;
}