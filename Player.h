//
// Created by Luiz on 24/08/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <unordered_map>

using namespace std;



class Player {
public:
    pair<int, int> PlayerPosition = {1, 1};
    deque<pair<int, int>> PlayerBody = {PlayerPosition};
    int score = 0;
    char CurrentDirection = 'D';

    int CheckPlayerMovement(const pair<int, int>& FruitPosition, const pair<int, int>& FieldSize) {
        unordered_map<char, pair<int, int>> directions = {
            {'W', {0, -1}}, {'S', {0, 1}},
            {'A', {-1, 0}}, {'D', {1, 0}}
        };

        unordered_map<char, char> oppositeDirection = {
            {'W', 'S'}, {'S', 'W'},
            {'A', 'D'}, {'D', 'A'}
        };

        Sleep(100);

        for (const auto& [key, move] : directions) {
            if (GetAsyncKeyState(static_cast<int>(key)) & 0x8000 && key != oppositeDirection[CurrentDirection]) {
                CurrentDirection = key;
                break;
            }
        }

        pair<int, int> newHeadPosition = {
            PlayerPosition.first + directions[CurrentDirection].first,
            PlayerPosition.second + directions[CurrentDirection].second
        };

        PlayerBody.emplace_front(newHeadPosition);
        PlayerPosition = newHeadPosition;

        if (PlayerPosition == FruitPosition) {
            return 1;
        }

        PlayerBody.pop_back();

        if (PlayerPosition.first >= FieldSize.first - 1 || PlayerPosition.second >= FieldSize.second - 1 ||
            PlayerPosition.first <= 0 || PlayerPosition.second <= 0 ||
            find(PlayerBody.begin() + 1, PlayerBody.end(), PlayerPosition) != PlayerBody.end()) {
            return 2;
            }

        return 0;
    }
};

#endif //PLAYER_H