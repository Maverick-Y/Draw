/* Title:抽奖模拟小程序
 * Description:模拟CODM中的转盘抽奖，计算每个项目的概率和期望值
 * Author: y30008578 MaverickY
 * Date: 2021/03/14
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int drawTimes = 300000;

void DrawOnce(vector<double> probability);
double TotalSum(const vector<double>& probability, int endNum);
void UpdateProbability(vector<double>& probability, int out);
int PickOne(const vector<double>& probability);
void DrawOnce(vector<double> probability);

int g_times[10][11] { 0 }; // g_times[i][j]:times of num[i]
double g_probability[10][11]{ 0.0 }; // g_probability[i][j]:probability of num[i]

void DrawOnce(vector<double> probability)
{
    for (int i = 0; i < probability.size(); ++i) {
        int out = PickOne(probability);
        ++g_times[out][i + 1];
        // cout << out << ' ';
        if (i < probability.size() - 1) {
            UpdateProbability(probability, out); // not last one
        }
    }
    // cout << endl;
}

double TotalSum(const vector<double>& probability, int endNum)
{
    if (endNum >= probability.size()) {
        cout << "TotalSum ERR! endNum larger than arry size";
        return -1;
    }
    double ret = 0;
    for (int i = 0; i <= endNum; ++i) {
        ret += probability[i];
    }
    return ret;
}

void UpdateProbability(vector<double>& probability, int out)
{
    if (out >= probability.size()) {
        cout << "UpdateProbability ERR! out larger than arry size" << endl;
        return;
    }
    if (probability[out] == 1) {
        cout << "UpdateProbability ERR! no elem left" << endl;
        return;
    }

    for (int i = 0; i < probability.size(); ++i) {
        if (i == out) {
            continue;
        }
        probability[i] = probability[i] / (1 - probability[out]);
    }
    probability[out] = 0;
}

int PickOne(const vector<double>& probability)
{
    double randNum = rand() * 1.0 / RAND_MAX;
    if (randNum < TotalSum(probability, 0)) {
        return 0;
    } else if (randNum < TotalSum(probability, 1)) {
        return 1;
    } else if (randNum < TotalSum(probability, 2)) {
        return 2;
    } else if (randNum < TotalSum(probability, 3)) {
        return 3;
    } else if (randNum < TotalSum(probability, 4)) {
        return 4;
    } else if (randNum < TotalSum(probability, 5)) {
        return 5;
    } else if (randNum < TotalSum(probability, 6)) {
        return 6;
    } else if (randNum < TotalSum(probability, 7)) {
        return 7;
    } else if (randNum < TotalSum(probability, 8)) {
        return 8;
    } else {
        return 9;
    }
}

int main()
{
    srand((int)time(0));
    vector<double> probobility{ 0.08 / 100, 1.25 / 100, 4.0 / 100, 4.67 / 100, 5.5 / 100, 6.5 / 100, 10.0 / 100, 11.0 / 100, 28.0 / 100, 29.0 / 100 };
    for (int i = 0; i < drawTimes; ++i) {
        DrawOnce(probobility);
    }

    for (int i = 0; i < 10; ++i) {
        double ex = 0;
        cout << "The probability of " << i << ": ";
        for (int j = 1; j <= 10; ++j) {
            ex += g_times[i][j] * 1.0 / drawTimes * j;
            cout << fixed << setprecision(5) << g_times[i][j] * 1.0 / drawTimes << " ";
        }
        cout << "E(x) = " << ex << endl;
    }

    return 0;
}