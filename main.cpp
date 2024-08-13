#include <windows.h>
#include <map>
#include <iostream>
#include <deque>
#include <random>
#include <algorithm>

// Função para reposicionar a fruta em coordenadas aleatórias
void RelocateFruit(int* a, int* b, const std::deque<std::pair<int, int>>& snakeBody, int width, int height) {
    static std::random_device rd;  // Semente para o gerador
    static std::mt19937 gen(rd()); // Mersenne Twister generator inicializado com a semente
    static std::uniform_int_distribution<> distribX(1, width - 2); // Intervalo para snake[0]
    static std::uniform_int_distribution<> distribY(1, height - 2); // Intervalo para snake[1]

    do {
        *a = distribX(gen);
        *b = distribY(gen);
    } while (std::find(snakeBody.begin(), snakeBody.end(), std::make_pair(*a, *b)) != snakeBody.end());
}

int RunGame() {
    // Define a pontuação, a largura e a altura da caixa, a posição inicial da cobra, a direção inicial da cobra e o array da posição da fruta
    constexpr int boxWidth = 20, boxHeight = 20;
    constexpr int winningScore = 322; // Pontuação necessária para vencer

    int points = 0;
    int snake[2] = { boxWidth / 2, boxHeight / 2 }; // Inicializa a posição da cobra
    char currentDirection = 'D';
    int fruit[2];

    // Deque para armazenar as posições do corpo da cobra
    std::deque<std::pair<int, int>> snakeBody;
    snakeBody.emplace_front(snake[0], snake[1]);

    // Mapeamento das direções
    std::map<char, std::pair<int, int>> directions = {
        {'W', {0, -1}}, {'S', {0, 1}},
        {'A', {-1, 0}}, {'D', {1, 0}}
    };

    // Mapeamento das direções opostas
    std::map<char, char> oppositeDirection = {
        {'W', 'S'}, {'S', 'W'},
        {'A', 'D'}, {'D', 'A'}
    };

    RelocateFruit(&fruit[0], &fruit[1], snakeBody, boxWidth, boxHeight);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (true) {
        // Pausa para controlar a velocidade do jogo
        Sleep(100);

        // Atualiza a direção com base na entrada do usuário
        for (const auto& [key, move] : directions) {
            if (GetAsyncKeyState(static_cast<int>(key)) & 0x8000 && key != oppositeDirection[currentDirection]) {
                currentDirection = key;
                break;
            }
        }

        // Calcula as novas coordenadas, limitando-as dentro do campo
        snake[0] = std::clamp(snake[0] + directions[currentDirection].first, 0, boxWidth - 1);
        snake[1] = std::clamp(snake[1] + directions[currentDirection].second, 0, boxHeight - 1);

        // Verifica se o jogador pegou a fruta
        if (snake[0] == fruit[0] && snake[1] == fruit[1]) {
            points++;
            snakeBody.emplace_front(snake[0], snake[1]); // Adiciona um novo segmento ao corpo da cobra (na posição atual da cabeça)
            RelocateFruit(&fruit[0], &fruit[1], snakeBody, boxWidth, boxHeight); // Reposiciona a fruta, garantindo que não aparece no corpo da cobra
        }

        // Verifica se o jogador atingiu a pontuação de vitória
        if (points == winningScore) {
            MessageBox(nullptr, "Congratulations! You Won!", "Victory", MB_OK);
            return points;
        }

        // Verifica se a cabeça colidiu com o corpo ou com as bordas
        if (std::find(snakeBody.begin() + 1, snakeBody.end(), std::make_pair(snake[0], snake[1])) != snakeBody.end() ||
            snake[0] == boxWidth - 1 || snake[1] == boxHeight - 1 || snake[1] == 0 || snake[0] == 0) {
            return points; // Retorna o score e encerra o loop para indicar o fim do jogo
        }

        // Move o corpo da cobra (exceto a cabeça)
        if (snakeBody.size() > 1) {
            for (auto i = snakeBody.size() - 1; i > 0; --i) {
                snakeBody[i] = snakeBody[i - 1];
            }
        }

        // Atualiza a posição da cabeça
        snakeBody[0] = { snake[0], snake[1] };

        // Desenha o campo de jogo
        for (int i = 0; i < boxHeight; ++i) {
            for (int j = 0; j < boxWidth; ++j) {
                WORD color = (i == 0 || i == boxHeight - 1 || j == 0 || j == boxWidth - 1) ? 0xCC :
                    std::find(snakeBody.begin(), snakeBody.end(), std::make_pair(j, i)) != snakeBody.end() ? 0x22 :
                    (i == fruit[1] && j == fruit[0]) ? 0x1F : 0x00;

                SetConsoleTextAttribute(hConsole, color);
                std::cout << "  ";
            }
            std::cout << std::endl;
        }

        // Exibe o score
        SetConsoleTextAttribute(hConsole, 0x0C);
        std::cout << "Score: " << points << std::endl;
        SetConsoleCursorPosition(hConsole, { 0, 0 });
    }
}

// Função Principal
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // Loop principal para o jogo
    while (true) {
        // Verifica se o usuário quer jogar
        if (MessageBox(nullptr, "PLAY???", "Snake Game(Made by Luiz Gabriel)", MB_YESNO) != IDYES) {
            return 0;
        }

        // Configuração do console
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Cria uma variável com a propriedade de esconder o cursor do console
        CONSOLE_CURSOR_INFO cursorInfo = { 100, FALSE };
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        RunGame();

        // Após o jogo terminar, exibe uma MessageBox para perguntar se o usuário quer reiniciar
        std::string message = "YOU LOST! PLAY AGAIN?";
        if (MessageBox(nullptr, message.c_str(), "GAME OVER", MB_YESNO) != IDYES) {
            return 0;
        }
    }
}