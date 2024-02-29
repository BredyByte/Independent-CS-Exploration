#include <iostream>
#include <vector>

int getRow(int bit) {
    return bit >> 4;
}

int getCol(int bit) {
    return bit % 16;
}
// check is but numebr "Index(0-7)" is in set "Number"
bool isSetBit(std::vector<int>& number, int index) {
    int indexR = getRow(index);
    int indexC = getCol(index);
    return (number[indexR] & (1 << indexC)) != 0;
}

void setBit(std::vector<int>& number, int index) {
    int indexR = getRow(index);
    int indexC = getCol(index);
    number[indexR] |= (1 << indexC);
}

void inverseBit(std::vector<int>& number, int index) {
    int indexR = getRow(index);
    int indexC = getCol(index);
    number[indexR] ^= (1 << indexC);
}

void resetBit(std::vector<int>& number, int index) {
    int indexR = getRow(index);
    int indexC = getCol(index);
    number[indexR] &= ~(1 << indexC);
}

void printDups(std::vector<int>& numbers) {
    std::vector<int> readed(256);
    for (int i = 0; i < numbers.size(); i++) {
        if (isSetBit(readed, numbers[i] - 1)) {
            std::cout << numbers[i] << ", ";
        } else {
            setBit(readed, numbers[i] - 1);
        }
    }
}

int main() {
   std::vector<int> numbers = {1,2,3,4,6,7,8,9,10,11,12,13,14,15,16,17,12, 1,3 ,5,6, 12, 18,19,20, 21,22,23,24, 22, 25,26,27,28,29,30,31,32,33,34,35};
    printDups(numbers);
    return 0;
}
