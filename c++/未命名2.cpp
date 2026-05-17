#include <iostream>
#include <vector>  // 添加vector头文件
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);  // 使用vector替代变长数组
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= k) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}
