#include "Game.h"

Game::Game()
{
    lcd = new LiquidCrystal(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);
    lcd->begin(16, 2);
    lcd->clear();

    score = 0;
    state = RUNNING;

    dino = new Dino();
    bird = new Bird();
    cactus = new Cactus();

    dinoView = new DinoView(dino, lcd);
    birdView = new BirdView(bird, lcd);
    cactusView = new CactusView(cactus, lcd);

    button = new Button(A0);
}

void Game::startGame()
{
    if (state == MENU || state == GAME_OVER)
    {
        score = 0;

        previousMillis = 0;
        state = RUNNING;

        dino = new Dino();
        bird = new Bird();
        cactus = new Cactus();

        dinoView = new DinoView(dino, lcd);
        birdView = new BirdView(bird, lcd);
        cactusView = new CactusView(cactus, lcd);
    }
}

void Game::handleUserInput()
{
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
            dino->crouch();
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
        }
    }
}

void Game::render()
{
    // dinoView->updateBitmaps();
    // birdView->updateBitmaps();
    // cactusView->updateBitmaps();
    lcd->setCursor(1, 1);
    lcd->print("               ");
    birdView->render();
    cactusView->render();
    dinoView->render();

    lcd->setCursor(1, 0);
    lcd->print("               ");
    lcd->setCursor(8, 0);
    lcd->print(score);
    // if (dino->checkColision(cactus))
    // {
    //     lcd->setCursor(8, 0);
    //     lcd->print(" 1cactus");
    // }
    // if (dino->checkColision(bird))
    // {
    //     lcd->setCursor(1, 0);
    //     lcd->print(" bird");
    // }
}

void Game::run()
{
    unsigned long currentMillis = millis(); // Get the current millis() value
    button->update();
    if (currentMillis - previousMillis >= interval)
    {
      if(state == RUNNING) {
        render();
        update();
      }
        handleUserInput();
        previousMillis = currentMillis;
        button->reset();
    }
}