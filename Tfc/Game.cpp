#include "Game.h"

Game::Game() : qLearning()
{
    attempts = 0;
    maxScore = score = 0;
    state = RUNNING;
    training = false;
    interval = LONG_INTERVAL;

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

bool Game::isTraining()
{
#if !FEATURE_ARDUINO
    return true;
#endif
    return training;
}

void Game::setTraining(bool newTraining)
{
    interval = newTraining ? SHORT_INTERVAL : LONG_INTERVAL;
    training = newTraining;
}

void Game::startGame()
{
    if (state == MENU || state == GAME_OVER)
    {
        attempts++;
        score = 0;
        if (attempts < MAX_ATTEMPTS)
            state = RUNNING;
        else
        {
            qLearning.printQTable();
            qLearning.setEpsilon(0);
#if !FEATURE_ARDUINO
            std::cout << "maxScore:\t" << maxScore << std::endl;
            std::cin.get();
#endif
            state = RUNNING;
        }

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

static const QLState stateMap[4][4] = {
    {BIRD_VERY_FAR_CACTUS_VERY_FAR,
     BIRD_VERY_FAR_CACTUS_FAR,
     BIRD_VERY_FAR_CACTUS_CLOSE,
     BIRD_VERY_FAR_CACTUS_VERY_CLOSE},
    {BIRD_FAR_CACTUS_VERY_FAR,
     BIRD_FAR_CACTUS_FAR,
     BIRD_FAR_CACTUS_CLOSE,
     BIRD_FAR_CACTUS_VERY_CLOSE},
    {BIRD_CLOSE_CACTUS_VERY_FAR,
     BIRD_CLOSE_CACTUS_FAR,
     BIRD_CLOSE_CACTUS_CLOSE,
     BIRD_CLOSE_CACTUS_VERY_CLOSE},
    {BIRD_VERY_CLOSE_CACTUS_VERY_FAR,
     BIRD_VERY_CLOSE_CACTUS_FAR,
     BIRD_VERY_CLOSE_CACTUS_CLOSE,
     BIRD_VERY_CLOSE_CACTUS_VERY_CLOSE}};
QLState Game::getState()
{
    int birdState, cactusState;
    birdState = cactusState = 0;
    if (bird->x + bird->w > dino->x)
    {
        if (bird->x < 30)
            birdState++;
        if (bird->x < 20)
            birdState++;
        if (bird->x < 8)
            birdState++;
    }
    if (cactus->x + cactus->w > dino->x)
    {
        if (cactus->x < 30)
            cactusState++;
        if (cactus->x < 20)
            cactusState++;
        if (cactus->x < 10)
            cactusState++;
    }
    return stateMap[birdState][cactusState];
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

        case SELECT:
            setTraining(!isTraining());
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
        dino->checkColision(cactus);
        dino->checkColision(bird);

        dino->updateState();
        bird->updateState();
        cactus->updateState();

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
        if (state == RUNNING)
        {
            if (score > maxScore)
                maxScore = score;

            update();
#if FEATURE_ARDUINO
            if (!isTraining())
            {
                handleUserInput();
            }
            render();
#endif
            if (isTraining())
            {
                QLState qlstate = getState();
                QLAction qlaction = qLearning.chooseAction(qlstate);
                handleUserInput(qlaction);
                int qlreward = score;
                if (qlaction == JUMP)
                    qlreward *= .9;
                if (qlaction == DUCK)
                    qlreward *= .9;
                if (dino->state == DEAD)
                    qlreward = 0;

                if (score > MAX_SCORE)
                {
                    state = GAME_OVER;
                    startGame();
                }

#if !FEATURE_ARDUINO
                if (attempts % LOG_EACH_N_ATTEMPTS == 0 || attempts > MAX_ATTEMPTS)
                    std::cout << attempts << " : " << qlaction << " | " << score << std::endl;
#endif

                qLearning.updateQTable(qlstate, qlaction, qlreward, getState());
            }
        }
#if FEATURE_ARDUINO
        previousMillis = currentMillis;
        button->reset();
    }
#endif
}