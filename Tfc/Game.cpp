#include "Game.h"

Game::Game() : qLearning()
{
    attempts = 0;
    score = 0;
    state = RUNNING;

    dino = new Dino();
    bird = new Bird();
    cactus = new Cactus();

#if FEATURE_ARDUINO
    lcd = new LiquidCrystal(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);
    lcd->begin(16, 2);
    lcd->clear();

    dinoView = new DinoView(dino, lcd);
    birdView = new BirdView(bird, lcd);
    cactusView = new CactusView(cactus, lcd);

    button = new Button(A0);
#endif
}

void Game::startGame()
{
#if !FEATURE_ARDUINO
    std::cout << std::endl
              << "NEW ATTEMPT!" << std::endl;
#endif
    if (state == MENU || state == GAME_OVER)
    {
        attempts++;
        score = 0;

        state = RUNNING;

        dino = new Dino();
        bird = new Bird();
        cactus = new Cactus();

#if FEATURE_ARDUINO
        previousMillis = 0;
        dinoView = new DinoView(dino, lcd);
        birdView = new BirdView(bird, lcd);
        cactusView = new CactusView(cactus, lcd);
#endif
    }
}

QLState Game::getState()
{
    bool isBirdClose = (bird->x > dino->x) && (-dino->x + bird->x < 15);
    bool isCactusClose = (cactus->x > dino->x) && (-dino->x + cactus->x < 15);
    bool isBirdFar = (bird->x > dino->x) && (-dino->x + bird->x < 60);
    bool isCactusFar = (cactus->x > dino->x) && (-dino->x + cactus->x < 60);

    if (isBirdClose && isCactusClose)
        return BOTH_CLOSE;
    if (isBirdClose)
        return BIRD_CLOSE;
    if (isCactusClose)
        return CACTUS_CLOSE;
    if (isBirdFar && isCactusFar)
        return BOTH_FAR;
    if (isBirdFar)
        return BIRD_FAR;
    if (isCactusFar)
        return CACTUS_FAR;
    return NOTHING_ON_SIGHT;
}

void Game::handleUserInput()
{
#if FEATURE_ARDUINO
    switch (state)
    {
    case MENU:
        break;

    case RUNNING:
        switch (button->getState())
        {
        case UP:
            dino->jump();
            break;

        case DOWN:
            dino->duck();
            break;

        default:
            break;
        }
        break;

    case GAME_OVER:
        break;
    }
#endif
}

void Game::handleUserInput(QLAction action)
{
    switch (state)
    {
    case MENU:
        break;

    case RUNNING:
        switch (action)
        {
        case JUMP:
            dino->jump();
            break;

        case DUCK:
            dino->duck();
            break;

        default:
            break;
        }
        break;

    case GAME_OVER:
        break;
    }
}

void Game::update()
{
    if (state == RUNNING)
        score++;
    dino->move();
    bird->move();
    cactus->move();
    {
        dino->updateState();
        bird->updateState();
        cactus->updateState();

        dino->checkColision(cactus);
        dino->checkColision(bird);

        if (dino->state == DEAD)
        {
            state = GAME_OVER;
            startGame();
        }
    }
}

#if FEATURE_ARDUINO
void Game::render()
{
    lcd->setCursor(1, 1);
    lcd->print("               ");
    birdView->render();
    cactusView->render();
    dinoView->render();

    lcd->setCursor(1, 0);
    lcd->print("               ");
    lcd->setCursor(8, 0);
    lcd->print(score);
}
#endif

void Game::run()
{
#if FEATURE_ARDUINO
    unsigned long currentMillis = millis();
    button->update();
    if (currentMillis - previousMillis >= interval)
    {
#endif
Serial.println("aqui");
        if (state == RUNNING)
        {
#if FEATURE_ARDUINO
            render();
#endif
            update();
#if FEATURE_ARDUINO
            handleUserInput();
#else
        QLState state = getState();
        QLAction action = qLearning.chooseAction(state);
        handleUserInput(action);
        int reward = score;
        if (action == JUMP)
            reward -= 1;
        if (action == DUCK)
            reward -= 1;

        std::cout << action << " | " << reward << " | " << score << std::endl;

        qLearning.updateQTable(state, action, reward, getState());
#endif
        }
#if FEATURE_ARDUINO
        previousMillis = currentMillis;
        button->reset();
    }
#endif
}