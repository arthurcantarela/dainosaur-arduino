#include "Game.h"

Game::Game() : qLearning()
{
    // lcd = new LiquidCrystal(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);
    // lcd->begin(16, 2);
    // lcd->clear();

    attempts = 0;
    score = 0;
    state = RUNNING;

    dino = new Dino();
    bird = new Bird();
    cactus = new Cactus();

    // dinoView = new DinoView(dino, lcd);
    // birdView = new BirdView(bird, lcd);
    // cactusView = new CactusView(cactus, lcd);

    // button = new Button(A0);
}

void Game::startGame()
{
    if (state == MENU || state == GAME_OVER)
    {
        attempts++;
        score = 0;

        // previousMillis = 0;
        state = RUNNING;

        dino = new Dino();
        bird = new Bird();
        cactus = new Cactus();

        // dinoView = new DinoView(dino, lcd);
        // birdView = new BirdView(bird, lcd);
        // cactusView = new CactusView(cactus, lcd);
    }
}

QLState Game::getState()
{
    bool isBirdClose = (bird->x > dino->x) && (-dino->x + bird->x < 15);
    bool isCactusClose = (cactus->x > dino->x) && (-dino->x + cactus->x < 15);

    if (isBirdClose && isCactusClose)
        return BOTH_CLOSE;
    if (isBirdClose)
        return BIRD_CLOSE;
    if (isCactusClose)
        return CACTUS_CLOSE;
    return NONE_CLOSE;
}

void Game::handleUserInput()
{
    //     switch (state)
    //     {
    //     case MENU:
    //         break;

    //     case RUNNING:
    //         switch (button->getState())
    //         {
    //         case UP:
    //             dino->jump();
    //             break;

    //         case DOWN:
    //             dino->duck();
    //             break;

    //         default:
    //             break;
    //         }
    //         break;

    //     case GAME_OVER:
    //         break;
    //     }
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

// void Game::render()
// {
//     lcd->setCursor(1, 1);
//     lcd->print("               ");
//     birdView->render();
//     cactusView->render();
//     dinoView->render();

//     lcd->setCursor(1, 0);
//     lcd->print("               ");
//     lcd->setCursor(8, 0);
//     lcd->print(score);
// }

void Game::run()
{
    // unsigned long currentMillis = millis(); // Get the current millis() value
    // button->update();
    // if (currentMillis - previousMillis >= interval)
    // {
    if (state == RUNNING)
    {
        // render();
        update();
        QLState state = getState();
        QLAction action = qLearning.chooseAction(state);
        handleUserInput(action);
        int reward = score;
        if (action == UP)
            reward -= 10;
        if (action == DOWN)
            reward += 10;

        qLearning.updateQTable(state, action, reward, getState());
    }
    //     previousMillis = currentMillis;
    //     button->reset();
    // }
}