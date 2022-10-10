//
// Created by matteom on 02/06/22.
//

#include "Menu.hpp"
#define NUM_FRAMES 3

Menu::Menu() {
    is_menu_open = true;
    is_game_open = false;
    is_settings_open = false;
    players = 1;
    is_players_1 = false;
    is_players_2 = false;
    is_players_3 = false;
    is_players_4 = false;
    runningMenu = true;
    Settings set;
    set._AI = false;
    set._keyDown = 0;
    set._keyLeft = 0;
    set._keyRight = 0;
    set._keyUp = 0;
    set._color = BLANK;
    set._keyBomb = 0;
    vectorSettingsPointing = 0;
    Key_bomb = 0;
    key_up = 0;

    _settings.push_back(set);
    _settings.push_back(set);
    _settings.push_back(set);
    _settings.push_back(set);
}

void Menu::StartMenu() {
    std::stringstream temp_str;
    temp_str<<players;
    char const *number_array = temp_str.str().c_str();

    if(is_menu_open)
    {
        Drawing();
        ClearBackground(RAYWHITE);

        // DrawMenu();
        // DrawText(number_array, 190, 360, 50, LIGHTGRAY);
    }
    EndDrawing();
}


void Menu::init()
{
    Click = LoadSound("Assets/click_sound.wav");
    back_menu = LoadMusicStream("Assets/back_sound.mp3");
    exit_button = LoadTexture("Assets/buttontest.png");
    newgame_button = LoadTexture("Assets/buttontest.png");
    loadgame_button = LoadTexture("Assets/buttontest.png");
    settings_button = LoadTexture("Assets/buttontest.png");
    texture_parallax1 = LoadTexture("Assets/sky.png");
    texture_parallax2 = LoadTexture("Assets/clouds_1.png");
    texture_parallax3 = LoadTexture("Assets/clouds_2.png");
    texture_parallax4 = LoadTexture("Assets/clouds_3.png");
    texture_parallax5 = LoadTexture("Assets/clouds_4.png");
    texture_logo = LoadTexture("Assets/bombermanlogo.png");
    DrawMenu();
    PlayMusicStream(back_menu);
    back_menu.looping = true;
    _player.push_back("player 1");
    _player.push_back("player 2");
    _player.push_back("player 3");
    _player.push_back("player 4");
}

void Menu::DrawMenu() {
    DrawText("This is the menu", 190, 200, 50, LIGHTGRAY);
    DrawText("Select number of player", 190, 300, 50, LIGHTGRAY);

    // DrawTexture(texture, 1920/2 - texture.width/2, 1080/2 - texture.height/2, WHITE);
}

void Menu::Parallax_init()
{
    offset.x += GetFrameTime() * 50;
    offset2.x += GetFrameTime() * 75;
    offset3.x += GetFrameTime() * 95;
    offset4.x += GetFrameTime() * 125;
    offset5.x += GetFrameTime() * 150;
}

void Menu::Drawing()
{
    Mouse = GetMousePosition();
    FrameHeight = (float) exit_button.height / NUM_FRAMES;
    Rectangle SourceRec = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceNewGameRec = {0, 0, (float) newgame_button.width, FrameHeight};
    Rectangle SourceLoadGameRec = {0, 0, (float) loadgame_button.width, FrameHeight};
    Rectangle SourceSettingsRec = {0, 0, (float) settings_button.width, FrameHeight};
    Rectangle ExitButtonBounds = {screenWidth/2.00f - exit_button.width/2.0f, screenHeight/2.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    Rectangle NewGameButtonBounds = {screenWidth/2.04f - newgame_button.width/2.5f, screenHeight/1.75f - newgame_button.height/NUM_FRAMES/2.0f, (float) newgame_button.width, FrameHeight};
    Rectangle LoadGameButtonBounds = {screenWidth/2.07f - loadgame_button.width/3.0f, screenHeight/1.55f - loadgame_button.height/NUM_FRAMES/2.0f, (float) loadgame_button.width, FrameHeight};
    Rectangle SettingsButtonBounds = {screenWidth/2.09f - settings_button.width/3.5f, screenHeight/1.40f - settings_button.height/NUM_FRAMES/2.0f, (float) settings_button.width, FrameHeight};

    // Gestion du bouton EXIT (FAIT)
    if (CheckCollisionPointRec(Mouse, ExitButtonBounds)) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        ButtonState = 2;
    else
        ButtonState = 1;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        ButtonAction = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(Click);
        runningMenu = false;
    }
    } else
    ButtonState = 0;
    SourceRec.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, NewGameButtonBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        ButtonState = 2;
    else
        ButtonState = 1;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        ButtonAction = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(Click);
            is_menu_open = false;
            is_game_open = true;
            runningMenu = false;
    }
    } else
    ButtonState = 0;
    SourceNewGameRec.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, LoadGameButtonBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        ButtonState = 2;
    else
        ButtonState = 1;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        ButtonAction = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {}
    } else
    ButtonState = 0;
    SourceLoadGameRec.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, SettingsButtonBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        ButtonState = 2;
    else
        ButtonState = 1;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        ButtonAction = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        is_settings_open = true;
        is_menu_open = false;
        PlaySound(Click);
    }
    } else
    ButtonState = 0;
    SourceSettingsRec.y = ButtonState * FrameHeight;
    BeginDrawing();
    DrawTextureRec(exit_button, SourceRec, (Vector2) {ExitButtonBounds.x, ExitButtonBounds.y}, WHITE);
    DrawTextureRec(newgame_button, SourceNewGameRec, (Vector2) {NewGameButtonBounds.x, NewGameButtonBounds.y}, WHITE);
    DrawTextureRec(loadgame_button, SourceLoadGameRec, (Vector2) {LoadGameButtonBounds.x, LoadGameButtonBounds.y}, WHITE);
    DrawTextureRec(settings_button, SourceSettingsRec, (Vector2) {SettingsButtonBounds.x, SettingsButtonBounds.y}, WHITE);
    DrawText("Quit", LocationTextExit.x, LocationTextExit.y, 25, WHITE);
    DrawText("Load Game", LocationLoadGame.x, LocationLoadGame.y, 25, WHITE);
    DrawText("New Game", LocationNewGame.x, LocationNewGame.y, 25, WHITE);
    DrawText("Settings", LocationSettings.x, LocationSettings.y, 25, WHITE);
    DrawTexture(texture_logo, 695, 100, WHITE);
}

void Menu::Drawparallax()
{
    UpdateMusicStream(back_menu);
    DrawTexturePro(texture_parallax1, (Rectangle) {offset.x, offset.y, GetScreenWidth(), GetScreenHeight()},
    (Rectangle) {0, 0, GetScreenWidth(), GetScreenWidth()}, (Vector2) {0, 0}, 0, WHITE);
    DrawTexturePro(texture_parallax2, (Rectangle) {offset2.x, offset2.y, GetScreenWidth(), GetScreenHeight()},
    (Rectangle) {0, 0, GetScreenWidth(), GetScreenWidth()}, (Vector2) {0, 0}, 0, WHITE);
    DrawTexturePro(texture_parallax3, (Rectangle) {offset3.x, offset3.y, GetScreenWidth(), GetScreenHeight()},
    (Rectangle) {0, 0, GetScreenWidth(), GetScreenWidth()}, (Vector2) {0, 0}, 0, WHITE);
    DrawTexturePro(texture_parallax4, (Rectangle) {offset4.x, offset4.y, GetScreenWidth(), GetScreenHeight()},
    (Rectangle) {0, 0, GetScreenWidth(), GetScreenWidth()}, (Vector2) {0, 0}, 0, WHITE);
    DrawTexturePro(texture_parallax5, (Rectangle) {offset5.x, offset5.y, GetScreenWidth(), GetScreenHeight()},
    (Rectangle) {0, 0, GetScreenWidth(), GetScreenWidth()}, (Vector2) {0, 0}, 0, WHITE);
}
void Menu::Event_Handler()
{
    if (is_menu_open)
        Drawparallax();

    if (is_settings_open) {
        Drawparallax();
        EventSettings();
    }
}

void Menu::EventSettings()
{
    Mouse = GetMousePosition();
    Rectangle SourceRect_return = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectKEY = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectKEY2 = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectKEY3 = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectKEY4 = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectKEY5 = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectIA = {0, 0, (float) exit_button.width, FrameHeight};
    Rectangle SourceRectPlayer = {0, 0, (float) exit_button.width, FrameHeight};

    button_return = {screenWidth - 400.0f -  exit_button.width/2.0f, screenHeight-100.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_2 = {screenWidth - 1600.0f - exit_button.width/2.0f, screenHeight- 100.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_3 = {screenWidth - 1600.0f -  exit_button.width/2.0f, screenHeight-300.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_4 = {screenWidth - 1600.0f - exit_button.width/2.0f, screenHeight-500.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_5 = {screenWidth - 1600.0f -  exit_button.width/2.0f, screenHeight-700.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_6 = {screenWidth - 1600.0f - exit_button.width/2.0f, screenHeight-900.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_IA = {screenWidth  -600.0f - exit_button.width/2.0f, screenHeight-100.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};
    button_player = {screenWidth-400.0f - exit_button.width/2.0f, screenHeight-900.0f - exit_button.height/NUM_FRAMES/2.0f, (float) exit_button.width, FrameHeight};

    if (CheckCollisionPointRec(Mouse, button_return)) {
        ButtonState = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_return)) {
            PlaySound(Click);
            is_menu_open = true;
            is_settings_open = false;
            std::cout << _settings.at(0)._keyUp << std::endl;
        }
    } else ButtonState = 0; SourceRect_return.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_2)) {
        ButtonState = 1;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_2)) {
            PlaySound(Click);
            Key_bomb = 0;
            if (Key_bomb == 0) {
                Key_bomb = GetKeyPressed();
                if (Key_bomb != 0)
                    _settings.at(vectorSettingsPointing)._keyBomb = Key_bomb;
            }
        }
    } else ButtonState = 0; SourceRectKEY.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_3)) {
        ButtonState = 1;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_3)) {
            PlaySound(Click);
            key_up = 0;
            if (key_up == 0) {
                key_up = GetKeyPressed();
                if (key_up != 0)
                    _settings.at(vectorSettingsPointing)._keyUp = key_up;
            }
        }
    } else ButtonState = 0; SourceRectKEY2.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_4)) {
        ButtonState = 1;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_4)) {
            PlaySound(Click);
            key_down = 0;
            if (key_down == 0) {
                key_down = GetKeyPressed();
                if (key_down != 0)
                    _settings.at(vectorSettingsPointing)._keyDown = key_down;
            }
        }
    } else ButtonState = 0; SourceRectKEY3.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_5)) {
        ButtonState = 1;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_5)) {
            PlaySound(Click);
            key_right = 0;
            if (key_right == 0) {
                key_right = GetKeyPressed();
                if (key_right != 0)
                    _settings.at(vectorSettingsPointing)._keyRight = key_right;
            }
        }
    } else ButtonState = 0; SourceRectKEY4.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_6)) {
        ButtonState = 1;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_6)) {
            PlaySound(Click);
            key_left = 0;
            if (key_left == 0) {
                key_left = GetKeyPressed();
                if (key_left != 0)
                    _settings.at(vectorSettingsPointing)._keyLeft = key_left;
            }
        }
    } else ButtonState = 0; SourceRectKEY5.y = ButtonState * FrameHeight;

    if (CheckCollisionPointRec(Mouse, button_IA)) {
        ButtonState = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_IA) && is_ia == false) {
            PlaySound(Click);
            _settings.at(vectorSettingsPointing)._AI = true;
            status = 1;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_IA) && is_ia == true) {
            PlaySound(Click);
            _settings.at(vectorSettingsPointing)._AI = false;
            status = 2;
        }
    } else ButtonState = 0; SourceRectIA.y = ButtonState * FrameHeight;


    if (CheckCollisionPointRec(Mouse, button_player)) {
        ButtonState = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(Mouse, button_player)) {
            PlaySound(Click);
            i++;
            status = 2;
            vectorSettingsPointing++;
            if (i >= _player.size()) {
                i=0;
                vectorSettingsPointing = 0;
            }

        }
    } else ButtonState = 0; SourceRectPlayer.y = ButtonState * FrameHeight;


    DrawTextureRec(exit_button, SourceRect_return, (Vector2) {button_return.x, button_return.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectKEY, (Vector2) {button_2.x, button_2.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectKEY2, (Vector2) {button_3.x, button_3.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectKEY3, (Vector2) {button_4.x, button_4.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectKEY4, (Vector2) {button_5.x, button_5.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectKEY5, (Vector2) {button_6.x, button_6.y}, WHITE);
    DrawTextureRec(exit_button, SourceRectIA, (Vector2) {button_IA.x, button_IA.y}, RED);
    DrawTextureRec(exit_button, SourceRectPlayer, (Vector2) {button_player.x, button_player.y}, WHITE);
    if (status == 1) {
        is_ia = true;
        DrawTextureRec(exit_button, SourceRectIA, (Vector2) {button_IA.x, button_IA.y}, GREEN);
    }
    if (status == 2) {
        is_ia = false;
        DrawTextureRec(exit_button, SourceRectIA, (Vector2) {button_IA.x, button_IA.y}, RED);
    }
    DrawText("Return", button_return.x + 30.0f, button_return.y + 15.0f, 20, WHITE);
    DrawText("IA", button_IA.x+45.0f, button_IA.y+15.0f, 20, WHITE);
    DrawText("Enter Bomb Key", button_2.x+200.0f, button_2.y+15.0f, 20, BLACK);
    DrawText("Enter Forward Key", button_3.x+200.0f, button_3.y+15.0f, 20, BLACK);
    DrawText("Enter Backward Key", button_4.x+200.0f, button_4.y+15.0f, 20, BLACK);
    DrawText("Enter Right Key", button_5.x+200.0f, button_5.y+15.0f, 20, BLACK);
    DrawText("Enter Left Key", button_6.x+200.0f, button_6.y+15.0f, 20, BLACK);
    DrawText(_player.at(i), button_player.x+50.0f, button_player.y+20.0f, 20, WHITE);


}

// void Menu::bind_keys() {
//     int key = 1;
//     if (is_players_1) {
//         while (key != key_up1) {
//             key = GetKeyPressed();
//             if (key != 0 && key != 1 && key != 81) {
//                 key_up1 = key;
//             }
//         }
//         while (key != key_down1) {//             key = GetKeyPressed();
//             if (key != 0 && key != 1) {
//                 key_down1 = key;
//             }
//         }
//         while (key != key_left1) {
//             key = GetKeyPressed();
//             if (key != 0 && key != 1) {
//                 key_left1 = key;
//             }
//         }
//         while (key != key_right1) {
//             key = GetKeyPressed();
//             if (key != 0 && key != 1) {
//                 key_right1 = key;
//             }
//         }
//         printf("%d\n", key_up1);
//         printf("%d\n", key_down1);
//         printf("%d\n", key_left1);
//         printf("%d\n", key_right1);
//     }
//     if (is_players_2) {
//         key_up2 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_up2;
//         key_down2 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_down2;
//         key_left2 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_left2;
//         key_right2 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_right2;
//     }
//     if (is_players_3) {
//         key_up3 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_up3;
//         key_down3 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_down3;
//         key_left3 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_left3;
//         key_right3 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_right3;

//     }
//     if (is_players_4) {
//         key_up4 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_up4;
//         key_down4 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_down4;
//         key_left4 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_left4;
//         key_right4 = (GetKeyPressed() > 0) ? GetKeyPressed() : key_right4;
//     }
// }

Menu::~Menu() = default;