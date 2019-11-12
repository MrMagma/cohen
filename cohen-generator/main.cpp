#include <iostream>
#include <fstream>
#include <random>

int** loadTriangle(const std::string& path, int SIZE) {
    std::ifstream input(path);
    int** triangle = new int*[SIZE];
    int data = 0;
    for (int i = 0; i < SIZE; i++) {
        triangle[i] = new int[SIZE];
        for (int j = 0; j < SIZE; j++) {
            triangle[i][j] = input.get() - '0';
            input.get();
        }
    }
    input.close();
    return triangle;
}

void writeIterate(std::string path, int SIZE, int** triangle) {
    std::ofstream out(path);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j == 0) out << 1;
            else if (i == j) out << 1;
            else if (j > i) out << 0;
            else {
                bool gcdGteOne = false;
                bool gcdGtOne = false;
                for (int k = 0; k <= i; k++) {
                    if (triangle[i - j][k] * triangle[j][k] == 1) {
                        if (gcdGteOne) {
                            out << 0;
                            gcdGtOne = true;
                            break;
                        } else {
                            gcdGteOne = true;
                        }
                    }
                }
                if (!gcdGtOne) out << 1;
            }
            if (j < SIZE - 1) out << ' ';
        }
        if (i < SIZE - 1) out << std::endl;
    }
    out.close();
}

void writeInitial(std::string path, int SIZE) {
    std::ofstream out(path);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j == 0) out << 1;
            else if (i == j) out << 1;
            else if (j > i) out << 0;
            else out << (rand()%2);
            if (j < SIZE - 1) out << ' ';
        }
        out << std::endl;
    }
    out.close();
}

int main(int argc, char** argv) {
    if (argc == 3) {
        writeInitial(argv[1], atoi(argv[2]));
    } else if (argc == 4) {
        int SIZE = atoi(argv[2]);
        writeIterate(argv[1], SIZE, loadTriangle(argv[3], SIZE));
    } else {
        return -1;
    }
    return 0;
}