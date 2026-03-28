#include "GameManager.h"
#include "ItemScene.h"
#include "PuzzleScene.h"
#include "CombatScene.h"
#include "SaveManager.h"
#include <iostream>
using namespace std;

GameManager::GameManager() {
    current_scene_ID = 0;
    setupScenes();
}

GameManager::~GameManager() {
    for (int i = 0; i < scenes.size(); i++) {
        delete scenes[i];
    }
}

void GameManager::setupScenes() {

    // ---- SCENE 0: Dungeon Entrance (Item) ----
    scenes.push_back(new ItemScene(
        0,
        "You stand at the entrance of Kael'Drath dungeon.\n"
        "A dead adventurer lies near the door.\n"
        "He has two items. You can only take one.",
        "Take the old sword",
        "Take the bread",
        "You take the sword. It is heavy but sharp.",
        "You take the bread and eat it. You feel stronger.",
        1, 1,
        Item("Old Sword", ItemType::WEAPON, 5,  "A heavy sword. Attack +5", 10),
        Item("Bread",     ItemType::FOOD,   20, "Restores health. Health +20", 0)
    ));

    // ---- SCENE 1: The Dark Hall (Lore) ----
    // Splits into East Wing (2) or West Wing (10)
    scenes.push_back(new Scene(
        1,
        "You enter a long dark hall.\n"
        "There are old paintings on the walls.\n"
        "At the end of the hall there are two corridors.\n"
        "A sign reads: EAST WING -> and <- WEST WING.",
        "Go to the East Wing",
        "Go to the West Wing",
        "You head down the east corridor. It is cold and dark.",
        "You head down the west corridor. You smell fire.",
        2, 10
    ));

    // ==================== EAST WING ====================

    // ---- SCENE 2: Sheep Puzzle (Puzzle) ----
    // Solved -> Scene 3 (combat - skeleton was behind door)
    // Skipped -> Scene 4 (item - quiet corridor, find gear)
    scenes.push_back(new PuzzleScene(
        2,
        "You walk into a small room.\n"
        "A stone door blocks the way forward.\n"
        "A sign on the door reads: Solve this to open the door.",
        "Answer the question",
        "Try to break the door",
        "You think carefully...",
        "You smash the door open. Your hands hurt.",
        3, 4,
        "A farmer has 10 sheep. All but 6 run away. How many sheep are left?",
        "6",
        10, 10
    ));

    // ---- SCENE 3: Skeleton Behind the Door (Combat) ----
    // Solving the puzzle opened the door - something was waiting inside
    // Both -> Scene 6
    scenes.push_back(new CombatScene(
        3,
        "The door swings open.\n"
        "A skeleton warrior was chained behind it - now it is free.\n"
        "It raises its rusty sword and charges at you!",
        "Fight the skeleton",
        "Try to run back",
        "You draw your weapon and face it!",
        "You try to escape...",
        6, 6,
        Enemy("Skeleton Warrior", 35, 12, 2, 15,
            Item("Bone Sword", ItemType::WEAPON, 3, "A cracked blade. Attack +3", 6))
    ));

    // ---- SCENE 4: Quiet Corridor (Item) ----
    // Breaking the door led you around - quiet path, find an item
    // Both -> Scene 6
    scenes.push_back(new ItemScene(
        4,
        "You squeeze through a side passage.\n"
        "The corridor is quiet. No enemies here.\n"
        "On the floor you spot two items left by a previous adventurer.",
        "Take the torch shield",
        "Take the leather vest",
        "You pick up the shield. It is light but solid.",
        "You put on the vest. It fits well.",
        6, 6,
        Item("Torch Shield", ItemType::ARMOUR, 4, "Light protection. Defense +4", 8),
        Item("Leather Vest", ItemType::ARMOUR, 6, "Decent armour. Defense +6", 10)
    ));

    // ---- SCENE 6: Old Storage Room (Item) ----
    // Both -> Scene 7
    scenes.push_back(new ItemScene(
        6,
        "You find an old storage room.\n"
        "Shelves line the walls. Most are empty.\n"
        "But you spot two items - a weapon on a rack and a locked chest.",
        "Take the iron sword from the rack",
        "Force open the locked chest",
        "You grab a solid iron sword.",
        "You break the lock. Inside is a health potion.",
        7, 7,
        Item("Iron Sword",    ItemType::WEAPON, 6, "A solid blade. Attack +6", 10),
        Item("Health Potion", ItemType::FOOD,   30, "Restores health. Health +30", 0)
    ));

    // ---- SCENE 7: Map Riddle Gate (Puzzle) ----
    // Solved -> Scene 8 (combat - ambush, two goblins were hiding behind gate)
    // Failed/skipped -> Scene 9 (lore - ghost of old soldier gives you sword)
    scenes.push_back(new PuzzleScene(
        7,
        "You reach an iron gate blocking the corridor.\n"
        "A riddle is carved above it:\n"
        "I have cities but no houses. Mountains but no trees.\n"
        "Water but no fish. What am I?",
        "Answer the riddle",
        "Look for another way around",
        "You speak the answer. The gate clicks open...",
        "You find a loose brick in the wall and crawl through.",
        8, 9,
        "What am I?",
        "map",
        15, 15
    ));

    // ---- SCENE 8: Ambush Behind the Gate (Combat) ----
    // Goblins were hiding - solving puzzle let them out
    // Both -> Scene 23
    scenes.push_back(new CombatScene(
        8,
        "The gate swings open - two goblins leap out from behind it!\n"
        "They were hiding, waiting for someone to open the door.\n"
        "They screech and attack!",
        "Fight them both",
        "Try to dodge past them",
        "You raise your weapon and charge!",
        "You try to slip past...",
        23, 23,
        Enemy("Goblin Ambushers", 45, 14, 3, 20)
    ));

    // ---- SCENE 9: Ghost of the Old Soldier (Item) ----
    // Crawling through the wall you find a hidden chamber with a ghost
    // Both -> Scene 23
        scenes.push_back(new ItemScene(
        9,
        "You crawl through the wall into a hidden chamber.\n"
        "A faint blue glow fills the room.\n"
        "The ghost of an old soldier stands before you.\n"
        "He says: I died here a hundred years ago. Take my sword.\n"
        "A glowing sword appears on the floor before you.",
        "Take the ghost sword", "Leave it and move on",
        "You pick up the sword. It hums with energy.",
        "You leave it. The ghost fades silently.",
        23, 23,
        Item("Ghost Sword", ItemType::WEAPON, 8, "Hums with energy. Attack +8", 12),
        Item("",            ItemType::FOOD,   0, "", 0)
    ));

    // ---- SCENE 23: Goblin Patrol (Combat) ----
    // Both east paths merge here before the final east boss
    // Both -> Scene 14
    scenes.push_back(new CombatScene(
        23,
        "A goblin patrol rounds the corner ahead.\n"
        "Three goblins with spears. They spot you immediately.\n"
        "There is nowhere to hide.",
        "Fight the patrol",
        "Try to run back",
        "You grip your weapon and charge!",
        "You turn and run...",
        14, 14,
        Enemy("Goblin Patrol", 50, 13, 2, 20,
            Item("Goblin Spear", ItemType::WEAPON, 4, "A crude spear. Attack +4", 7))
    ));

    // ---- SCENE 14: Skeleton Captain (Combat) ----
    // East Wing final boss
    scenes.push_back(new CombatScene(
        14,
        "You reach the east entrance of the throne room.\n"
        "A skeleton captain in full armour blocks the door.\n"
        "He raises a massive axe and lets out a hollow roar.",
        "Fight the Skeleton Captain",
        "Try to find a weakness",
        "You charge at the captain with everything you have!",
        "You circle him slowly, looking for an opening...",
        99, 99,
        Enemy("Skeleton Captain", 70, 18, 8, 50,
            Item("Captain's Axe", ItemType::WEAPON, 10, "A heavy battle axe. Attack +10", 12))
    ));

    // ==================== WEST WING ====================

    // ---- SCENE 10: The Prisoner (Lore) ----
    // A (free him) -> Scene 11 (combat - prisoner panics, alerts goblins)
    // B (leave him) -> Scene 12 (item - sneak past, find weapon)
    scenes.push_back(new Scene(
        10,
        "You enter the west corridor and find a man locked in a cage.\n"
        "He whispers: Hey! Let me out - I know this dungeon well.\n"
        "There is a key hanging on the wall next to the cage.",
        "Free the prisoner",
        "Leave him and move on",
        "You unlock the cage. The man runs out - and trips over a barrel.\n"
        "The noise echoes through the corridor. You hear goblins shouting.",
        "You walk away quietly. The man watches you go in silence.",
        11, 12
    ));

    // ---- SCENE 11: Alerted Goblins (Combat) ----
    // Prisoner panicked and alerted the goblins - harder fight
    // Both -> Scene 13
    scenes.push_back(new CombatScene(
        11,
        "Three goblins come running around the corner.\n"
        "The prisoner runs the other way screaming.\n"
        "The goblins are angry and ready for a fight.",
        "Fight all three",
        "Try to run",
        "You stand your ground!",
        "You turn and run...",
        13, 13,
        Enemy("Alerted Goblins", 55, 16, 3, 20)
    ));

    // ---- SCENE 12: Quiet Sneak (Item) ----
    // Left the prisoner - sneaked past quietly, found a weapon
    // Both -> Scene 13
    scenes.push_back(new ItemScene(
        12,
        "You move through the corridor quietly.\n"
        "No one heard you. On a dead goblin on the floor\n"
        "you find two useful items.",
        "Take the goblin axe",
        "Take the goblin armour",
        "You pick up the axe. It is crude but effective.",
        "You put on the goblin armour. Smells bad but works.",
        13, 13,
        Item("Goblin Axe",   ItemType::WEAPON, 7, "Crude but sharp. Attack +7", 8),
        Item("Goblin Armour",ItemType::ARMOUR, 5, "Smells terrible. Defense +5", 7)
    ));

    // ---- SCENE 13: 6x7 Door Puzzle (Puzzle) ----
    // Solved -> Scene 15 (lore - trap room, take damage but find item)
    // Failed -> Scene 16 (item - fall through trap door, find chest below)
    scenes.push_back(new PuzzleScene(
        13,
        "You arrive at a heavy door with a number lock.\n"
        "An inscription reads: Only those who know the answer may pass.",
        "Try to solve the inscription",
        "Look for another way",
        "You study the inscription carefully...",
        "You look around and find a trapdoor in the floor.",
        15, 16,
        "What is 6 x 7?",
        "42",
        10, 0
    ));

    // ---- SCENE 15: Pressure Plate Room (Lore) ----
    // Solved puzzle - door opened but room has pressure plates
    // Both -> Scene 24
    scenes.push_back(new Scene(
        15,
        "The door opens into a wide room.\n"
        "Too late you notice the floor is covered in pressure plates.\n"
        "Click. Click. Click. Arrows fire from the walls.\n"
        "You sprint through, taking hits along the way.\n"
        "You take 20 damage but make it through.\n"
        "On the other side you find a health potion on a shelf.",
        "Grab the potion and keep moving",
        "Ignore it and move on quickly",
        "You snatch the potion. Health +25.",
        "You run past it. No time.",
        24, 24
    ));

    // ---- SCENE 16: Trap Door Below (Item) ----
    // Failed puzzle - fell through the floor
    // Both -> Scene 24
    scenes.push_back(new ItemScene(
        16,
        "The trapdoor drops you into a lower room.\n"
        "Soft landing - you are not hurt.\n"
        "The room is dusty and forgotten.\n"
        "In the corner you find an old chest with two items inside.",
        "Take the steel gauntlets",
        "Take the war hammer",
        "You put on the gauntlets. Your fists feel stronger.",
        "You lift the war hammer. It is heavy but powerful.",
        24, 24,
        Item("Steel Gauntlets", ItemType::ARMOUR, 7, "Heavy hand armour. Defense +7", 10),
        Item("War Hammer",      ItemType::WEAPON, 8, "Slow but devastating. Attack +8", 10)
    ));

    // ---- SCENE 24: Skeleton Archer (Combat) ----
    // Both west paths merge here
    // Both -> Scene 18
    scenes.push_back(new CombatScene(
        24,
        "A skeleton archer stands at the end of the corridor.\n"
        "It draws its bow and fires before you can react.\n"
        "The arrow grazes your arm. It steps closer.",
        "Fight the archer",
        "Try to dodge and close the distance",
        "You charge at the skeleton!",
        "You weave between arrows and rush it...",
        18, 18,
        Enemy("Skeleton Archer", 40, 15, 1, 20,
            Item("Elven Bow", ItemType::WEAPON, 5, "A fine bow. Attack +5", 10))
    ));

    // ---- SCENE 18: Clock Riddle (Puzzle) ----
    // Solved -> Scene 19 (combat - goblin shaman was guarding the passage)
    // Failed -> Scene 20 (item - long way around, find armour)
    scenes.push_back(new PuzzleScene(
        18,
        "You reach a large ornate door.\n"
        "A riddle is written in glowing letters:\n"
        "I have hands but cannot clap. What am I?",
        "Answer the riddle",
        "Look for another way around",
        "You speak your answer confidently...",
        "You search the walls for a hidden passage...",
        19, 20,
        "What am I?",
        "clock",
        15, 0
    ));

    // ---- SCENE 19: Goblin Shaman (Combat) ----
    // Solving puzzle opened passage - shaman was guarding it
    // Both -> Scene 22
    scenes.push_back(new CombatScene(
        19,
        "The door swings open to reveal a goblin shaman.\n"
        "He was guarding this passage.\n"
        "He raises his staff and launches a fireball at you!",
        "Fight the shaman",
        "Try to dodge the fireball and run past",
        "You deflect the fireball and charge!",
        "You roll to the side...",
        22, 22,
        Enemy("Goblin Shaman", 45, 17, 2, 25,
            Item("Shaman Staff", ItemType::WEAPON, 6, "Crackles with energy. Attack +6", 9))
    ));

    // ---- SCENE 20: Long Way Around (Item) ----
    // Failed riddle - took the long corridor, found armour on a dead adventurer
    // Both -> Scene 22
    scenes.push_back(new ItemScene(
        20,
        "You find a hidden passage along the wall.\n"
        "It is long and narrow.\n"
        "At the end you find the body of a dead adventurer.\n"
        "He has two items you can use.",
        "Take the chainmail vest",
        "Take the battle axe",
        "You put on the chainmail. Solid protection.",
        "You pick up the axe. Well balanced.",
        22, 22,
        Item("Chainmail Vest", ItemType::ARMOUR, 8, "Strong protection. Defense +8", 12),
        Item("Battle Axe",     ItemType::WEAPON, 7, "Well balanced axe. Attack +7", 10)
    ));

    // ---- SCENE 22: Dark Wizard (Combat) ----
    // West Wing final boss -> Victory 2 (101)
    scenes.push_back(new CombatScene(
        22,
        "You burst into the throne room from the west.\n"
        "A dark wizard stands at the throne, the crown floating above his hand.\n"
        "He turns and smiles. You will not leave here alive.\n"
        "He raises his staff and the room fills with dark energy.",
        "Fight the Dark Wizard",
        "Try to grab the crown and run",
        "You charge at the wizard with everything you have!",
        "You sprint for the crown...",
        99, 99,
        Enemy("Dark Wizard", 80, 20, 5, 60,
            Item("Wizard's Staff", ItemType::WEAPON, 12, "Ancient and powerful. Attack +12", 15))
        ));
}

void GameManager::showMainMenu() {
    cout << "\n========================================" << endl;
    cout << "       DEPTHS OF KAEL'DRATH" << endl;
    cout << "       A Text Adventure Game" << endl;
    cout << "========================================" << endl;
    cout << "1) New Game" << endl;
    if (save_manager.hasSave()) {
        cout << "2) Load Game" << endl;
        cout << "3) Quit" << endl;
    } else {
        cout << "2) Quit" << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Enter choice: ";
}

void GameManager::setupPlayer() {
    string name;

    cout << "\nEnter your name, brave adventurer: ";

    getline(cin, name);

    while (name.empty()) {
        cout << "Name cannot be empty. Try again: ";
        getline(cin, name);
    }

    player = Player(name);
    current_scene_ID = 0;

    cout << "\nWelcome, " << name << "! Your quest begins..." << endl;
}

void GameManager::gameLoop() {
    while (player.isAlive()) {
        cout << "\n[C] Continue   [I] Inventory & Stats: ";
        char opt;
        bool validInput = false;

        while (!validInput) {
            string line;
            getline(cin, line);

            if (line.empty()) {
                cout << "Input cannot be empty. Enter C or I: ";
            } else {
                opt = toupper(line[0]);

                if (opt == 'C' || opt == 'I') {
                    validInput = true;
                } else {
                    cout << "Invalid input. Enter C or I: ";
                }
            }
        }

        if (opt == 'I') {
            player.showInventory();
            player.showPlayerStats();
        } else {
            Scene* current = nullptr;

            for (int i = 0; i < scenes.size(); i++) {
                if (scenes[i]->getSceneId() == current_scene_ID) {
                    current = scenes[i];
                    break;
                }
            }

            if (current == nullptr) {
                cout << "Error: scene not found." << endl;
                break;
            }

            int next = current->play(player);

            if (!player.isAlive()) {
                break;
            }
            current_scene_ID = next;
        }
    }

    if (!player.isAlive()) {
        cout << "\n========================================" << endl;
        cout << "          *** GAME OVER ***" << endl;
        cout << "========================================" << endl;
        cout << "You ran out of lives, " << player.getName() << "." << endl;
        cout << "Final Score: " << player.getScore() << endl;
    }
}

void GameManager::run() {
    showMainMenu();

    int menuChoice = 0;
    bool validInput = false;
    int maxChoice = save_manager.hasSave() ? 3 : 2;

    while (!validInput) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            cout << "Input cannot be empty. Enter 1 or 2: ";
        } else {
            try {
                size_t pos;
                menuChoice = stoi(line, &pos);

                if (pos != line.size()) {
                    cout << "Invalid input. Enter a number: ";
                } else if (menuChoice < 1 || menuChoice > maxChoice) {
                    cout << "Invalid choice. Enter 1-" << maxChoice;
                } else {
                    validInput = true;
                }
            } catch (...) {
                cout << "Invalid input. Enter 1 or 2: ";
            }
        }
    }

    if (save_manager.hasSave()) {
        if (menuChoice == 3) {
            cout << "\nGoodbye!" << endl;
        }
        else if (menuChoice == 2) {
            save_manager.loadGame(player, current_scene_ID);
            gameLoop();
        }
        else {
            setupPlayer();
            gameLoop();
        }
    }
    else {
        if (menuChoice == 2) {
            cout << "\nGoodbye!" << endl;
        }
        else {
            setupPlayer();
            gameLoop();
        }
    }
}