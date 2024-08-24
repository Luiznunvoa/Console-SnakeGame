//
// Created by Luiz on 24/08/2024.
//

#ifndef FRUIT_H
#define FRUIT_H

#include <random>

using namespace std;

class Fruit {
public:
    pair<int, int> FruitPosition = {5, 5};

    pair<int, int> RelocateFruit(const pair<int, int>& Player, const deque<pair<int, int>>& Body, const pair<int, int>& FieldSize) {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distribX(1, FieldSize.first - 2);
        uniform_int_distribution<> distribY(1, FieldSize.second - 2);

        do {
            FruitPosition.first = distribX(gen);
            FruitPosition.second = distribY(gen);
        } while (find(Body.begin(), Body.end(), FruitPosition) != Body.end());

        return FruitPosition;
    }
};



#endif //FRUIT_H
