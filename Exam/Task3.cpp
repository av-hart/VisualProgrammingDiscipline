#include <iostream>
#include <vector>
using namespace std;

float sum(const vector<float>& vec, size_t index = 0) {
    if (index == vec.size())
        return 0;
    return vec[index] + sum(vec, index+1);
}

int main() {
    float num, result;
    int q=0;
    vector<float> arr;
    cout << "If you want to finish entering, enter 0" << endl;
    while (true) {
        cout << "Enter array element #" << q+1 << ": ";
        cin >> num;
        if (num != 0) {
            arr.push_back(num);
            q++;
        } else {
            break;
        }
    }
    
    cout << "So the array consists of the following elements:" << endl;
    for (size_t i=0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    
    result = sum(arr);
    cout << "\nAnd the sum of these " << q << " elements is " << result << endl;

    // Гарт А.
    return 0;
}
