#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

// Grid size
constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 20;

// Window size
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

// Cell size
constexpr int CELL_WIDTH = SCREEN_WIDTH / GRID_WIDTH;
constexpr int CELL_HEIGHT = SCREEN_HEIGHT / GRID_HEIGHT;

struct Frog {
    int x = SCREEN_WIDTH - CELL_WIDTH;
    int y = SCREEN_HEIGHT - CELL_HEIGHT;
    const int speed = 10;

    void moveUp()    { if (y > 0) y-=speed; }
    void moveDown()  { if (y < SCREEN_HEIGHT - CELL_HEIGHT) y+= speed; }
    void moveLeft()  { if (x > 0) x-=speed; }
    void moveRight() { if (x < SCREEN_WIDTH - CELL_WIDTH) x+=speed; }
};

struct Car
{
    float x;
};

enum class LaneType
{
    Grass,
    Road
};

struct Lane
{
    int y;
    LaneType type;

    // Road properties
    int direction;       // -1 = left, +1 = right
    float speed;         // cells per second
    std::vector<Car> cars;
};

bool checkCollision(const Frog& frog, const Lane& lane)
{
    if (lane.type != LaneType::Road)
        return false;

    if (frog.y != lane.y)
        return false;

    for (const Car& car : lane.cars)
    {
        int carLeft = static_cast<int>(car.x);
        int carRight = carLeft + 1; // car is 2 cells wide

        if (frog.x >= carLeft && frog.x <= carRight)
            return true;
    }

    return false;
}




int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Frogger - Movable Frog",
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0
    );

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Frog frog;
    std::vector<Lane> lanes;
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        if (y == 0 || y == GRID_HEIGHT - 1 || y % 2 == 1)
        {
            lanes.push_back({ y, LaneType::Grass, 0, 0.0f, {} });
        }
        else
        {
            Lane lane;
            lane.y = y;
            lane.type = LaneType::Road;
            lane.direction = (std::rand() % 2 == 0) ? -1 : 1;
            lane.speed = 3.0f + static_cast<float>(std::rand() % 3); // 3–5 cells/sec

            // Spawn cars
            for (int i = 0; i < 3; i++)
            {
                lane.cars.push_back({ static_cast<float>(i * 12) });
            }

            lanes.push_back(lane);
        }
    }

    bool running = true;
    SDL_Event event;
    Uint64 lastTicks = SDL_GetTicks();
    while (running)
    {
        Uint64 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                    case SDLK_W: frog.moveUp(); break;
                    case SDLK_S: frog.moveDown(); break;
                    case SDLK_A: frog.moveLeft(); break;
                    case SDLK_D: frog.moveRight(); break;
                    case SDLK_Q: running = false; break;
                    default: break;
                }
            }
        }
        bool frogHit = false;
        // -------- Update Cars --------
        for (Lane& lane : lanes)
        {
            if (lane.type != LaneType::Road)
                continue;

            for (Car& car : lane.cars)
            {
                car.x += lane.direction * lane.speed * deltaTime;

                // Wrap around
                if (lane.direction == 1 && car.x > GRID_WIDTH)
                    car.x = -2.0f;
                else if (lane.direction == -1 && car.x < -2.0f)
                    car.x = GRID_WIDTH;
            }
            if (checkCollision(frog, lane))
            {
                frogHit = true;
            }
        }

        if (frogHit)
        {
            frog.x = GRID_WIDTH / 2;
            frog.y = GRID_HEIGHT - 1;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
        SDL_RenderClear(renderer);

        for (const Lane& lane : lanes)
        {
            const SDL_FRect laneRect(
                0,
                lane.y * CELL_HEIGHT,
                SCREEN_WIDTH,
                CELL_HEIGHT
            );

            if (lane.type == LaneType::Grass)
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
            else
                SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);

            SDL_RenderFillRect(renderer, &laneRect);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (const Lane& lane : lanes)
        {
            if (lane.type != LaneType::Road)
                continue;

            for (const auto&[x] : lane.cars)
            {
                const SDL_FRect carRect(
                    static_cast<int>(x * CELL_WIDTH),
                    lane.y * CELL_HEIGHT,
                    CELL_WIDTH * 2,
                    CELL_HEIGHT);
                SDL_RenderFillRect(renderer, &carRect);
            }
        }

        // Draw frog as green rectangle
        const SDL_FRect frogRect(
            frog.x,
            frog.y,
            CELL_WIDTH/4,
            CELL_HEIGHT/4);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &frogRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}