#include "GameManager.h"
#include "ItemScene.h"
#include "PuzzleScene.h"
#include "CombatScene.h"
#include "SaveManager.h"
#include "LockedDoorScene.h"
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

    // ==================== SHARED START ====================

    // ---- SCENE 0: Dungeon Entrance (Item) ----
    // Both -> Scene 1
    scenes.push_back(new ItemScene(
        0,
        "You stand at the entrance of Kael'Drath dungeon.\n"
        "A dead adventurer lies near the door.\n"
        "He has two items. You can only take one.",
        "Take the old sword",
        "Take the leather vest",
        "You take the sword. It is heavy but sharp.",
        "You put on the vest. It fits well.",
        1, 1,
        Item("Old Sword",    ItemType::WEAPON, 5, "A heavy sword. Attack +5", 10),
        Item("Leather Vest", ItemType::ARMOUR, 4, "Light armour. Defense +4", 10)
    ));

    // ---- SCENE 1: The Dark Hall (Lore) ----
    // A -> East Wing (2), B -> West Wing (10)
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

    // ---- SCENE 2: Stone Door Puzzle ----
    // A (answer) -> 4 Item (door opens quietly, safe path)
    // B (smash)  -> 3 Combat (noise attracts skeleton)
    scenes.push_back(new PuzzleScene(
        2,
        "You walk into a small room.\n"
        "A stone door blocks the way forward.\n"
        "A sign reads: Solve this to open the door.",
        "Answer the riddle",
        "Smash the door open",
        "You think carefully...",
        "You smash the door. The noise echoes through the dungeon.",
        4, 3,
        "I have keys but no locks. I have space but no room.\n"
        "You can enter but cannot go inside. What am I?",
        "keyboard",
        15, 10
    ));

    // ---- SCENE 3: Skeleton Warrior (Combat) ----
    // Smashing attracted it
    // Both -> 6
    scenes.push_back(new CombatScene(
        3,
        "The noise from the door attracts something from the shadows.\n"
        "A skeleton warrior charges at you, rusty sword raised!\n"
        "It was patrolling nearby and heard the commotion.",
        "Fight the skeleton",
        "Try to run back",
        "You draw your weapon and face it!",
        "You try to escape...",
        6, 6,
        Enemy("Skeleton Warrior", 40, 14, 2, 15,
            Item("Bone Sword", ItemType::WEAPON, 3, "A cracked blade. Attack +3", 6))
    ));

    // ---- SCENE 4: Side Passage (Item) ----
    // Solved riddle - door opened quietly, safe path
    // Both -> 6
    scenes.push_back(new ItemScene(
        4,
        "The door opens silently. No enemies here.\n"
        "You find a quiet side passage.\n"
        "On the floor you spot two items left by a previous adventurer.",
        "Take the chain gloves",
        "Take the bread loaf",
        "You put on the gloves. Solid hand protection.",
        "You pick up the bread. Better than nothing.",
        6, 6,
        Item("Chain Gloves", ItemType::ARMOUR, 3, "Hand protection. Defense +3", 8),
        Item("Bread Loaf",   ItemType::FOOD,   25, "Restores health. Health +25", 0)
    ));

    // ---- SCENE 6: Iron Gate Puzzle ----
    // A (answer) -> 8 Item (gate opens silently, hidden chamber)
    // B (crawl)  -> 7 Combat (goblins on the other side spot you)
    scenes.push_back(new PuzzleScene(
        6,
        "You reach an iron gate blocking the corridor.\n"
        "A riddle is carved above it:\n"
        "I have cities but no houses. Mountains but no trees.\n"
        "Water but no fish. What am I?",
        "Answer the riddle",
        "Look for another way around",
        "You speak the answer. The gate clicks open silently...",
        "You find a loose brick and crawl through.\n"
        "Two goblins on the other side spot you immediately!",
        8, 7,
        "What am I?",
        "map",
        15, 15
    ));

    // ---- SCENE 7: Goblin Ambush (Combat) ----
    // Crawled through - goblins spotted you
    // Both -> 9
    scenes.push_back(new CombatScene(
        7,
        "The two goblins screech and attack!\n"
        "They were patrolling this side of the wall.\n"
        "You have no choice but to fight.",
        "Fight them",
        "Try to dodge past them",
        "You raise your weapon and charge!",
        "You try to slip past...",
        9, 9,
        Enemy("Goblin Ambushers", 50, 15, 3, 20,
            Item("Goblin Rations", ItemType::FOOD, 20, "Smells bad but edible. Health +20", 0))
    ));

    // ---- SCENE 8: Hidden Chamber (Item) ----
    // Gate opened silently - ghost's chamber revealed
    // Both -> 9
    scenes.push_back(new ItemScene(
        8,
        "The gate swings open to reveal a hidden chamber.\n"
        "A faint blue glow fills the room.\n"
        "The ghost of an old soldier stands before you.\n"
        "He says: Take my equipment. You will need it.",
        "Take the ghost sword",
        "Take the ghost armour",
        "You pick up the sword. It hums with energy.",
        "You pick up the ghost armour. It feels strangely warm.",
        9, 9,
        Item("Ghost Sword",  ItemType::WEAPON, 8, "Hums with energy. Attack +8", 12),
        Item("Ghost Armour", ItemType::ARMOUR, 7, "Glows faintly. Defense +7", 12)
    ));

    // ---- SCENE 9: Goblin Patrol (Combat) ----
    // Drop: Dungeon Key (40% chance)
    // Both -> 25 LockedDoor
    scenes.push_back(new CombatScene(
        9,
        "A goblin patrol rounds the corner ahead.\n"
        "Three goblins with spears. They spot you immediately.\n"
        "There is nowhere to hide.",
        "Fight the patrol",
        "Try to run back",
        "You grip your weapon and charge!",
        "You turn and run...",
        25, 25,
        Enemy("Goblin Patrol", 55, 14, 2, 20,
            Item("Dungeon Key", ItemType::KEY, 0, "A rusty key. Opens dungeon doors.", 0))
    ));

    // ---- SCENE 25: Locked Door (East Wing) ----
    // Has key -> 26 Puzzle, no key -> 27 Combat (harder path)
    scenes.push_back(new LockedDoorScene(
        25,
        "You reach a heavy iron door blocking the corridor.\n"
        "A large keyhole is set into the door.\n"
        "There is no other obvious way through.",
        "Use a key to open the door",
        "Try to find another way around",
        "You check your inventory for a key...",
        "You search the walls for another passage.\n"
        "You find a narrow crack but have to squeeze through, taking damage.",
        26, 27,
        "Dungeon Key", 27, 20
    ));

    // ---- SCENE 26: Anagram Puzzle ----
    // A (answer) -> 28 East Mini-Boss
    // B (skip)   -> 27 Combat (harder path)
    scenes.push_back(new PuzzleScene(
        26,
        "Beyond the door you find a chamber with a strange inscription.\n"
        "It reads: Unscramble this word to disable the trap ahead.\n"
        "The word is: DSWOR",
        "Try to unscramble it",
        "Ignore it and move on",
        "You study the letters carefully...",
        "You walk past. Suddenly arrows fire from the walls!",
        28, 27,
        "What is the unscrambled word?",
        "sword",
        15, 15
    ));

    // ---- SCENE 27: Skeleton Guards (Combat) ----
    // Harder path - no key or skipped puzzle
    // Both -> 14
    scenes.push_back(new CombatScene(
        27,
        "Two skeleton guards block the passage.\n"
        "They raise their weapons and advance.\n"
        "You have no choice but to fight.",
        "Fight the skeletons",
        "Try to run past",
        "You charge at the skeletons!",
        "You try to dodge past...",
        45, 45,
        Enemy("Skeleton Guards", 55, 14, 2, 25,
            Item("Stale Bread", ItemType::FOOD, 15, "Old but edible. Health +15", 0))
    ));

    // ---- SCENE 28: Stone Troll - East Mini-Boss (Combat) ----
    // Both -> 14
    scenes.push_back(new CombatScene(
        28,
        "You enter a large chamber.\n"
        "A massive stone troll sits in the centre, guarding the passage.\n"
        "It roars and picks up a giant club.",
        "Fight the troll",
        "Try to sneak past while it is distracted",
        "You charge at the troll with everything you have!",
        "You attempt to creep past...",
        45, 45,
        Enemy("Stone Troll", 60, 15, 3, 35,
            Item("Troll Club", ItemType::WEAPON, 9, "Massive and heavy. Attack +9", 10))
    ));

    // ---- SCENE 45: Fallen Knight (Item) ----
    // Before East Wing Boss
    // Both -> 14
    scenes.push_back(new ItemScene(
        45,
        "Before the throne room door you find the body of a fallen knight.\n"
        "He died fighting the same enemy you are about to face.\n"
        "He has two items you can take.",
        "Take the enchanted blade",
        "Take the knight's shield",
        "You pick up the blade. It feels powerful.",
        "You put on the shield. Heavy but solid.",
        14, 14,
        Item("Enchanted Blade",  ItemType::WEAPON, 10, "Glows with power. Attack +10", 12),
        Item("Knight's Shield",  ItemType::ARMOUR,  9, "Heavy and solid. Defense +9",  12)
    ));

    // ---- SCENE 14: Skeleton Captain - East Wing Boss (Combat) ----
    // Both -> 99
    scenes.push_back(new CombatScene(
        14,
        "You reach the east entrance of the throne room.\n"
        "A skeleton captain in full armour blocks the door.\n"
        "He raises a massive axe and lets out a hollow roar.",
        "Fight the Skeleton Captain",
        "Try to find a weakness first",
        "You charge at the captain with everything you have!",
        "You circle him slowly, looking for an opening...",
        99, 99,
        Enemy("Skeleton Captain", 75, 16, 4, 50)
    ));

    // ==================== WEST WING ====================

    // ---- SCENE 10: The Prisoner (Lore) ----
    // A (free) -> 11 Combat (noise alerts goblins)
    // B (leave) -> 12 Item (sneak past quietly)
    scenes.push_back(new Scene(
        10,
        "You enter the west corridor and find a man locked in a cage.\n"
        "He whispers: Hey! Let me out - I know this dungeon well.\n"
        "There is a key hanging on the wall next to the cage.",
        "Free the prisoner",
        "Leave him and move on",
        "You unlock the cage. The man runs out - and trips over a barrel.\n"
        "The noise echoes. You hear goblins shouting.",
        "You walk away quietly. The man watches you go in silence.",
        11, 12
    ));

    // ---- SCENE 11: Alerted Goblins (Combat) ----
    // Freeing prisoner caused noise
    // Both -> 13
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
        Enemy("Alerted Goblins", 50, 14, 2, 20,
            Item("Goblin Rations", ItemType::FOOD, 20, "Smells bad but edible. Health +20", 0))
    ));

    // ---- SCENE 12: Quiet Sneak (Item) ----
    // Left prisoner - sneaked past quietly
    // Both -> 13
    scenes.push_back(new ItemScene(
        12,
        "You move through the corridor quietly.\n"
        "No one heard you. On a dead goblin on the floor\n"
        "you find two useful items.",
        "Take the goblin axe",
        "Take the goblin armour",
        "You pick up the axe. Crude but effective.",
        "You put on the armour. Smells bad but works.",
        13, 13,
        Item("Goblin Axe",    ItemType::WEAPON, 7, "Crude but sharp. Attack +7", 8),
        Item("Goblin Armour", ItemType::ARMOUR, 5, "Smells terrible. Defense +5", 7)
    ));

    // ---- SCENE 13: Number Lock Puzzle ----
    // A (answer) -> 15 Scene (door opens, pressure plate room)
    // B (skip)   -> 16 Item (trapdoor drops you below)
    scenes.push_back(new PuzzleScene(
        13,
        "You arrive at a heavy door with a number lock.\n"
        "An inscription reads: Only those who know the answer may pass.\n"
        "What is 6 x 7?",
        "Answer the inscription",
        "Look for another way",
        "You study the inscription carefully...",
        "You look around and find a trapdoor in the floor.",
        15, 16,
        "What is 6 x 7?",
        "42",
        10, 0
    ));

    // ---- SCENE 15: Pressure Plate Room (Item) ----
    // Both -> 17
    scenes.push_back(new ItemScene(
        15,
        "The door opens into a wide room.\n"
        "Too late you notice the floor is covered in pressure plates.\n"
        "You carefully navigate through and make it to the other side.\n"
        "On a shelf you find two useful items.",
        "Take the health potion",
        "Take the iron shield",
        "You grab the potion. It looks potent.",
        "You pick up the shield. Solid protection.",
        17, 17,
        Item("Health Potion", ItemType::FOOD,   30, "Restores health. Health +30", 0),
        Item("Iron Shield",   ItemType::ARMOUR,  6, "Solid protection. Defense +6", 10)
    ));

    // ---- SCENE 16: Trap Door Below (Item) ----
    // Skipped puzzle - fell through floor
    // Both -> 17
    scenes.push_back(new ItemScene(
        16,
        "The trapdoor drops you into a lower room.\n"
        "Soft landing - you are not hurt.\n"
        "The room is dusty and forgotten.\n"
        "In the corner you find an old chest with two items inside.",
        "Take the chainmail vest",
        "Take the war hammer",
        "You put on the chainmail. Solid protection.",
        "You lift the war hammer. Heavy but devastating.",
        17, 17,
        Item("Chainmail Vest", ItemType::ARMOUR, 8, "Strong protection. Defense +8", 12),
        Item("War Hammer",     ItemType::WEAPON, 8, "Slow but devastating. Attack +8", 10)
    ));

    // ---- SCENE 17: Skeleton Archer (Combat) ----
    // Drop: Iron Key (40% chance)
    // Both -> 40 LockedDoor
    scenes.push_back(new CombatScene(
        17,
        "A skeleton archer stands at the end of the corridor.\n"
        "It draws its bow and fires before you can react.\n"
        "The arrow grazes your arm. It steps closer.",
        "Fight the archer",
        "Try to dodge and close the distance",
        "You charge at the skeleton!",
        "You weave between arrows and rush it...",
        40, 40,
        Enemy("Skeleton Archer", 40, 13, 1, 20,
            Item("Iron Key", ItemType::KEY, 0, "A heavy iron key. Opens iron doors.", 0))
    ));

    // ---- SCENE 40: Locked Door (West Wing) ----
    // Has key -> 18 Puzzle, no key -> 41 Combat (harder path)
    scenes.push_back(new LockedDoorScene(
        40,
        "You reach a reinforced iron door blocking the corridor.\n"
        "A heavy lock seals it shut.\n"
        "There is no obvious way through.",
        "Use a key to open the door",
        "Try to find another way around",
        "You check your inventory for a key...",
        "You search for another route.\n"
        "You find a narrow gap but have to force through.",
        18, 41,
        "Iron Key", 41, 20
    ));

    // ---- SCENE 18: Clock Riddle (Puzzle) ----
    // A (answer) -> 19 Combat (door opens, shaman was guarding it)
    // B (skip)   -> 20 Item (long way around)
    scenes.push_back(new PuzzleScene(
        18,
        "You reach a large ornate door.\n"
        "A riddle is written in glowing letters:\n"
        "I have hands but cannot clap. What am I?",
        "Answer the riddle",
        "Look for another way around",
        "You speak your answer. The door swings open...",
        "You search the walls and find a hidden passage.",
        19, 20,
        "What am I?",
        "clock",
        15, 0
    ));

    // ---- SCENE 19: Goblin Shaman (Combat) ----
    // Door opened - shaman was guarding it
    // Both -> 42
    scenes.push_back(new CombatScene(
        19,
        "The door swings open to reveal a goblin shaman.\n"
        "He was guarding this passage.\n"
        "He raises his staff and launches a fireball at you!",
        "Fight the shaman",
        "Try to dodge the fireball and run past",
        "You deflect the fireball and charge!",
        "You roll to the side...",
        42, 42,
        Enemy("Goblin Shaman", 45, 14, 1, 25,
            Item("Shaman Staff", ItemType::WEAPON, 6, "Crackles with energy. Attack +6", 9))
    ));

    // ---- SCENE 20: Long Way Around (Item) ----
    // Skipped puzzle - long corridor, found dead adventurer
    // Both -> 42
    scenes.push_back(new ItemScene(
        20,
        "You find a hidden passage along the wall.\n"
        "It is long and narrow.\n"
        "At the end you find the body of a dead adventurer.\n"
        "He has two items you can use.",
        "Take the battle axe",
        "Take the plate armour",
        "You pick up the axe. Well balanced.",
        "You put on the plate armour. Heavy but solid.",
        42, 42,
        Item("Battle Axe",   ItemType::WEAPON, 7, "Well balanced axe. Attack +7", 10),
        Item("Plate Armour", ItemType::ARMOUR, 9, "Heavy protection. Defense +9", 12)
    ));

    // ---- SCENE 41: Orc Guards (Combat) ----
    // Harder path - no key
    // Both -> 42
    scenes.push_back(new CombatScene(
        41,
        "Two orc guards step out of the shadows.\n"
        "They snarl and raise their axes.\n"
        "You have no choice but to fight.",
        "Fight the orcs",
        "Try to run past",
        "You charge at the orcs!",
        "You try to dodge past...",
        42, 42,
        Enemy("Orc Guards", 55, 15, 3, 25,
            Item("Orc Axe", ItemType::WEAPON, 8, "Heavy and brutal. Attack +8", 10))
    ));

    // ---- SCENE 42: Shadow Riddle (Puzzle) ----
    // A (answer) -> 43 Item (secret armoury revealed)
    // B (skip)   -> 44 Combat (triggered trap, dark knight appears)
    scenes.push_back(new PuzzleScene(
        42,
        "You enter a dimly lit chamber.\n"
        "Words glow on the wall before you:\n"
        "I follow you all day but disappear at night.\n"
        "I copy your every move but make no sound. What am I?",
        "Answer the riddle",
        "Ignore it and push forward",
        "You study the glowing words...",
        "You push forward and trigger a trap!\n"
        "A swinging blade catches you.",
        43, 44,
        "What am I?",
        "shadow",
        15, 15
    ));

    // ---- SCENE 43: Secret Armoury (Item) ----
    // Puzzle solved - secret wall opens
    // Both -> 22
    scenes.push_back(new ItemScene(
        43,
        "The wall slides open revealing a secret armoury.\n"
        "Two powerful items sit on a stone pedestal.\n"
        "A previous adventurer must have hidden them here.",
        "Take the enchanted sword",
        "Take the dragon scale armour",
        "You grab the sword. It feels perfectly balanced.",
        "You put on the armour. Incredibly light yet strong.",
        46, 46,
        Item("Enchanted Sword",     ItemType::WEAPON, 10, "Perfectly balanced. Attack +10", 12),
        Item("Dragon Scale Armour", ItemType::ARMOUR, 10, "Light yet strong. Defense +10", 12)
    ));

    // ---- SCENE 44: Dark Knight - West Mini-Boss (Combat) ----
    // Triggered trap
    // Both -> 22
    scenes.push_back(new CombatScene(
        44,
        "A dark knight steps out from behind a pillar.\n"
        "He was waiting for intruders to trigger the trap.\n"
        "He raises a black sword and charges!",
        "Fight the dark knight",
        "Try to dodge and find an opening",
        "You meet his charge head on!",
        "You sidestep and look for a gap in his armour...",
        46, 46,
        Enemy("Dark Knight", 65, 15, 3, 35,
            Item("Black Sword", ItemType::WEAPON, 9, "Dark and sharp. Attack +9", 12))
    ));

    // ---- SCENE 46: Abandoned Pack (Item) ----
    // Before West Wing Boss
    // Both -> 22
    scenes.push_back(new ItemScene(
        46,
        "You spot an abandoned adventurer's pack near the throne room entrance.\n"
        "Someone left in a hurry - or didn't make it back.\n"
        "Inside you find two useful items.",
        "Take the runic sword",
        "Take the runic armour",
        "You grab the sword. It hums with ancient power.",
        "You put on the armour. Surprisingly light.",
        22, 22,
        Item("Runic Sword",  ItemType::WEAPON, 10, "Ancient and powerful. Attack +10", 12),
        Item("Runic Armour", ItemType::ARMOUR,  9, "Light yet strong. Defense +9",     12)
    ));

    // ---- SCENE 22: Dark Wizard - West Wing Boss (Combat) ----
    // Both -> 99
    scenes.push_back(new CombatScene(
        22,
        "You burst into the throne room from the west.\n"
        "A dark wizard stands at the throne, the crown floating above his hand.\n"
        "He turns and smiles coldly.\n"
        "You will not leave here alive.\n"
        "He raises his staff and the room fills with dark energy.",
        "Fight the Dark Wizard",
        "Try to grab the crown and run",
        "You charge at the wizard with everything you have!",
        "You sprint for the crown...",
        99, 99,
        Enemy("Dark Wizard", 80, 17, 3, 60)
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
        cout << "\n[C] Continue   [I] Inventory & Stats   [S] Save & Exit: ";
        char opt;
        bool valid_input = false;

        while (!valid_input) {
            string line;
            getline(cin, line);

            if (line.empty()) {
                cout << "Input cannot be empty. Enter C, I or S: ";
            } else {
                opt = toupper(line[0]);

                if (opt == 'C' || opt == 'I' || opt == 'S') {
                    valid_input = true;
                } else {
                    cout << "Invalid input. Enter C, I or S: ";
                }
            }
        }

        if (opt == 'I') {
            player.showInventory();
            player.showPlayerStats();
        }
        else if (opt == 'S') {
            save_manager.saveGame(player, current_scene_ID);
            cout << "Goodbye, " << player.getName() << "! See you next time." << endl;
            break;
        }
        else {
            Scene* current = nullptr;

            for (auto & scene : scenes) {
                if (scene->getSceneId() == current_scene_ID) {
                    current = scene;
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

            if (next == 99) {
                cout << "\n========================================" << endl;
                cout << "         *** VICTORY! ***" << endl;
                cout << "========================================" << endl;
                cout << "You have conquered the dungeon, " << player.getName() << "!" << endl;
                cout << "Final Score: " << player.getScore() << endl;
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

    int menu_choice = 0;
    bool valid_input = false;
    int max_choice = save_manager.hasSave() ? 3 : 2;

    while (!valid_input) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            cout << "Input cannot be empty. Enter 1 to " << max_choice << ": ";
        } else {
            try {
                size_t pos;
                menu_choice = stoi(line, &pos);

                if (pos != line.size()) {
                    cout << "Invalid input. Enter 1 to " << max_choice << ": ";
                } else if (menu_choice < 1 || menu_choice > max_choice) {
                    cout << "Invalid choice. Enter 1 to " << max_choice << ": ";
                } else {
                    valid_input = true;
                }
            } catch (...) {
                cout << "Invalid input. Enter 1 to " << max_choice << ": ";
            }
        }
    }

    if (save_manager.hasSave()) {
        if (menu_choice == 3) {
            cout << "\nGoodbye!" << endl;
        }
        else if (menu_choice == 2) {
            save_manager.loadGame(player, current_scene_ID);
            gameLoop();
        }
        else {
            setupPlayer();
            gameLoop();
        }
    }
    else {
        if (menu_choice == 2) {
            cout << "\nGoodbye!" << endl;
        }
        else {
            setupPlayer();
            gameLoop();
        }
    }
}