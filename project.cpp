#include <iostream>
using namespace std;

// Width and height of the game grid
const int WIDTH = 10;
const int HEIGHT = 10;

// Base class representing any object in the game (player or enemy)
class GameObject
{
public:
    int x, y;    // position of the object on the grid
    char symbol; // character used to display the object

    // Constructor to initialize object position and symbol
    GameObject(int x, int y, char symbol)
    {
        this->x = x;
        this->y = y;
        this->symbol = symbol;
    }
};

// Main Game class which controls the game logic
class Game
{
private:
    bool isRunning;             // controls whether the game loop runs or stops
    int score;                  // player's score
    GameObject player;          // player object
    vector<GameObject> enemies; // list storing enemy objects

public:
    // Constructor initializes player and enemies
    Game() : player(WIDTH / 2, HEIGHT / 2, 'P') // player starts in center
    {
        isRunning = true; // game starts in running state
        score = 0;        // initial score

        // Creating 3 enemies at random positions on the grid
        for (int i = 0; i < 3; i++)
        {
            enemies.push_back(GameObject(rand() % WIDTH, rand() % HEIGHT, 'E'));
        }
    }

    // Main game loop
    void run()
    {
        while (isRunning) // loop runs until user quits
        {
            render();       // display the grid
            processInput(); // take user input
            update();       // update game state
        }
    }

    // Function to take player movement input
    void processInput()
    {
        char input;

        cout << "\nMove (W A S D) | Q Quit : ";
        cin >> input;

        // Quit game
        if (input == 'q' || input == 'Q')
            isRunning = false;

        // Move player up
        else if (input == 'w' || input == 'W')
            player.y--;

        // Move player down
        else if (input == 's' || input == 'S')
            player.y++;

        // Move player left
        else if (input == 'a' || input == 'A')
            player.x--;

        // Move player right
        else if (input == 'd' || input == 'D')
            player.x++;
    }

    // Updates the game state
    void update()
    {
        // Prevent player from going outside the grid boundaries
        if (player.x < 0)
            player.x = 0;
        if (player.y < 0)
            player.y = 0;
        if (player.x >= WIDTH)
            player.x = WIDTH - 1;
        if (player.y >= HEIGHT)
            player.y = HEIGHT - 1;

        // Move each enemy randomly
        for (auto &enemy : enemies)
        {
            int dir = rand() % 4; // choose random direction

            if (dir == 0)
                enemy.x++; // move right
            if (dir == 1)
                enemy.x--; // move left
            if (dir == 2)
                enemy.y++; // move down
            if (dir == 3)
                enemy.y--; // move up

            // Prevent enemies from leaving the grid
            if (enemy.x < 0)
                enemy.x = 0;
            if (enemy.y < 0)
                enemy.y = 0;
            if (enemy.x >= WIDTH)
                enemy.x = WIDTH - 1;
            if (enemy.y >= HEIGHT)
                enemy.y = HEIGHT - 1;
        }

        // Check if player collides with any enemy
        checkCollision();
    }

    // Function to check collision between player and enemies
    void checkCollision()
    {
        for (auto &enemy : enemies)
        {
            // If player and enemy are at same position
            if (enemy.x == player.x && enemy.y == player.y)
            {
                cout << "\n Collision! Enemy defeated!\n";

                score++; // increase score

                // Respawn enemy at a new random position
                enemy.x = rand() % WIDTH;
                enemy.y = rand() % HEIGHT;
            }
        }
    }

    // Function to render the game grid on screen
    void render()
    {
        cout << "\nScore: " << score << endl;
        cout << "------------------\n";

        // Loop through the grid rows
        for (int y = 0; y < HEIGHT; y++)
        {
            // Loop through the grid columns
            for (int x = 0; x < WIDTH; x++)
            {
                bool printed = false; // track if something is printed

                // Print player if player is at this position
                if (player.x == x && player.y == y)
                {
                    cout << "P ";
                    printed = true;
                }

                // Check if any enemy is at this position
                for (auto &enemy : enemies)
                {
                    if (enemy.x == x && enemy.y == y)
                    {
                        cout << "E ";
                        printed = true;
                        break;
                    }
                }

                // If nothing is at this position, print empty cell
                if (!printed)
                    cout << ". ";
            }

            cout << endl; // move to next row
        }
    }
};

// Program entry point
int main()
{
    srand(time(0)); // seed random number generator

    Game game;  // create game object
    game.run(); // start the game loop

    cout << "\nGame Over! Final Score: " << endl;

    return 0; // end program
}