//#include <iostream>
//using namespace std;
//
//#define ROW 10
//#define COL 10
//
//class RepeatedValue {
//private:
//    int row;
//    int col;
//    double repeatedValue;
//public:
//    RepeatedValue(int row, int col, double repeatedValue) {
//        this->row = row;
//        this->col = col;
//        this->repeatedValue = repeatedValue;
//    }
//
//    int getRow() {
//        return row;
//    }
//
//    int getCol() {
//        return col;
//    }
//
//    double getRepeatedValue() {
//        return repeatedValue;
//    }
//};
//
//int main() {
//    int matrix[ROW][COL];
//    int valueCounts[10] = { 0, };
//    RepeatedValue** rv;
//
//    for (int i = 0; i < ROW; i++) {
//        for (int j = 0; j < COL; j++) {
//            matrix[i][j] = (rand() % 10) + 1; // Random number generation
//            valueCounts[matrix[i][j] - 1]++; // Count generated number
//        }
//    }
//
//    int rvCount = 0;
//    for (int i = 0; i < 10; i++) {
//        if (valueCounts[i] > 1)
//            rvCount += valueCounts[i];
//    }
//
//    rv = new RepeatedValue * [rvCount];
//
//    int idx = 0;
//    for (int i = 0; i < ROW; i++) {
//        for (int j = 0; j < COL; j++) {
//            if (valueCounts[matrix[i][j] - 1] > 1) {
//                rv[idx++] = new RepeatedValue(i, j, (double)matrix[i][j]);
//            }
//        }
//    }
//
//    for (int i = 0; i < rvCount; i++) {
//        cout << "Repeated Value: " << rv[i]->getRepeatedValue() << " (" << rv[i]->getRow() << ", " << rv[i]->getCol() << ")" << endl;
//    }
//
//    return 0;
//}