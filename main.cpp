#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

enum class ItemType {
    WEAPON,
    ARMOUR,
    FOOD,
};

static const int MAX_HEALTH = 100;
static const int MAX_INVENTORY = 10;

class Item {
private:
    ItemType type;
    string name;
    int effect_value;
    string description;
public:
    Item(string cname, ItemType ctype, int ceffect_value, string cdescription) {
        name = cname;
        type = ctype;
        effect_value = ceffect_value;
        description = cdescription;
    }
    ItemType getType() const{
        return type;
    }
    string getName() const{
        return name;
    }
    int getEffectValue() const{
        return effect_value;
    }
    string getDescription() const{
        return description;
    }
    void printItemInfo() const{
        cout << "{" << name << "}" << description << endl;
        cout << "Effect: " << effect_value << endl;
    }
};

class Player {
private:
    string name;
    int health;
    int lives;
    int attack_damage;
    int defense;
    int score;
    vector<Item> inventory;

public:
    Player(string cname) {
        name = cname;
        health = MAX_HEALTH;
        lives = 3;
        attack_damage = 15;
        defense = 0;
        score = 0;
    }

    Player() {
        name = "";
        health = MAX_HEALTH;
        lives = 3;
        attack_damage = 15;
        defense = 0;
        score = 0;
    }

    string getName() {
        return name;
    }
    int getHealth() {
        return health;
    }
    int getLives() {
        return lives;
    }
    int getAttackDamage() {
        return attack_damage;
    }
    int getDefense() {
        return defense;
    }
    int getScore() {
        return score;
    }

    void heal(int amount) {
        health += amount;
        if (health > MAX_HEALTH) {
            health = MAX_HEALTH;
        }
    }

    void takeDamage(int amount) {
        int actualDamage = amount - defense;
        if (actualDamage < 0) {
            actualDamage = 0;
        }
        health -= actualDamage;
        if (health <= 0) {
            health = 0;
            lives--;
            if (lives > 0) {
                health = MAX_HEALTH;
                cout << "You lost a life! Life remaining: " << lives << endl;
            }
        }
    }

    bool isAlive() const {
        return lives > 0;
    }

    void addScore(int amount) {
        score += amount;
    }

    bool addItem(const Item& item) {
        bool success = false;
        if (inventory.size() < MAX_INVENTORY) {
            inventory.push_back(item);
            switch (item.getType()) {
                case ItemType::WEAPON: attack_damage += item.getEffectValue();
                    break;
                case ItemType::ARMOUR: defense += item.getEffectValue();
                    break;
                case ItemType::FOOD: health += item.getEffectValue();
                    break;
            }
            cout << "You picked up: " << item.getName() << endl;
            success = true;
        }else {
            cout << "Inventory is full." << endl;
        }
        return success;
    }

    void showInventory() {
        if (inventory.empty()) {
            cout << "Your inventory is empty" << endl;
            return;
        }
        cout << "=== Inventory ===" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            inventory[i].printItemInfo();
        }
    }

    void showPlayerStats() const {
        cout << "===" << name << "'s Stats ===" << endl;
        cout << "Health: " << health << endl;
        cout << "Attack damage: " << attack_damage << endl;
        cout << "Defense: " << defense << endl;
        cout << "Lives: " << lives << endl;
        cout << "Score: " << score << endl;
    }
};

class Enemy {
private:
    string name;
    int health;
    int attack;
    int defense;
    int scoreReward;
    bool hasDrop;
    Item dropItem;
public:
    Enemy(string cname, int chealth, int cattack, int cdefense,int cscoreReward)
        : dropItem("", ItemType::WEAPON, 0, "") {
        name = cname;
        health = chealth;
        attack = cattack;
        defense = cdefense;
        scoreReward = cscoreReward;
        hasDrop = false;
    }

    Enemy(string cname, int chealth, int cattack, int cdefense,int cscoreReward, Item cdropItem)
       : dropItem(cdropItem) {
        name = cname;
        health = chealth;
        attack = cattack;
        defense = cdefense;
        scoreReward = cscoreReward;
        hasDrop = true;
    }

    string getName() const {
        return name;
    }
    int getHealth() const {
        return health;
    }
    int getAttack() const {
        return attack;
    }
    int getDefense() const {
        return defense;
    }
    int getScoreReward() const {
        return scoreReward;
    }
    bool getHasDrop() const {
        return hasDrop;
    }
    Item getDropItem() const {
        return dropItem;
    }
    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage) {
        int actualDamage = damage - defense;
        if (actualDamage < 0) {
            actualDamage = 0;
        }
        health -= actualDamage;
        if (health < 0) {
            health = 0;
        }
    }
};

class Scene {
protected:
    int sceneId;
    string description;
    string choiceA;
    string choiceB;
    string consequenceA;
    string consequenceB;
    int nextSceneIdA;
    int nextSceneIdB;
public:
    Scene(int cscene_id, string ccene_description, string cchoiceA,
        string cchoiceB, string cconsequenceA, string cconsequenceB, int cnextIdA, int cnextIdB) {
        sceneId = cscene_id;
        description = ccene_description;
        choiceA = cchoiceA;
        choiceB = cchoiceB;
        consequenceA = cconsequenceA;
        consequenceB = cconsequenceB;
        nextSceneIdA = cnextIdA;
        nextSceneIdB = cnextIdB;
    }

    virtual ~Scene(){}

    int getSceneId() const {
        return sceneId;
    }

    virtual int play(Player& player) {
        cout << "\n" << description << endl;
        return presentChoices(player);
    }

    int presentChoices(Player& player) {
        cout << "\nA) " << choiceA << endl;
        cout << "B) " << choiceB << endl;
        cout << "----------------------------------------------" << endl;

        char userChoice;
        do {
            cout << player.getName() << ", what do you do? (A/B): ";
            cin >> userChoice;
            userChoice = toupper(userChoice);

            if (userChoice != 'A' && userChoice != 'B')
                cout << "Invalid input. Please enter A or B.\n";

        } while (userChoice != 'A' && userChoice != 'B');
        if (userChoice == 'A') {
            cout << "\n>> " << consequenceA << endl;
            return nextSceneIdA;
        }else {
            cout << "\n>> " << consequenceB << endl;
            return nextSceneIdB;
        }
    }
};

class PuzzleScene : public Scene {
private:
    string question;
    string answer;
    int scoreReward;
    int damageOnFail;
public:
    PuzzleScene(int cindex, const string& cdescription,
        const string& cchoiceA, const string& cchoiceB,
        const string& cconsequenceA, const string& cconsequenceB,
        int cnextSceneA, int cnextSceneB,
        const string& cquestion, const string& canswer,
        int cscoreReward, int cdamageOnFail)
    : Scene(cindex, cdescription,
        cchoiceA, cchoiceB,
        cconsequenceA, cconsequenceB,
        cnextSceneA, cnextSceneB) {
        question = cquestion;
        answer = canswer;
        scoreReward = cscoreReward;
        damageOnFail = cdamageOnFail;
        }

    int play(Player& player) override {
        cout << "\n" << description << endl;

        int next = presentChoices(player);
        if (next == nextSceneIdA) {
            cout << "\n" << question << endl;
            cout << "\n" << player.getName()<< ", you must answer to proceed."<< endl;
            cout << "Your answer: ";

            string userAnswer;
            cin >> userAnswer;

            for (int i = 0; i < answer.size(); i++) {
                answer[i] = tolower(answer[i]);
            }
            for (int i = 0; i < userAnswer.size(); i++) {
                userAnswer[i] = tolower(userAnswer[i]);
            }

            if (userAnswer == answer) {
                cout << "\n>> Correct! Well done, " << player.getName() << endl;
                player.addScore(scoreReward);
                cout << "Your score has increased by " << scoreReward << endl;
            }else {
                cout << "Wrong! The answer was: " << answer << endl;
                player.takeDamage(15);
                cout << "You take 15 damage for wrong answer";
            }
        }else {
            player.takeDamage(damageOnFail);
            cout << "You take " << damageOnFail << " damage!" << endl;
        }

        return next;
    }
};

class ItemScene : public Scene {
private:
    Item itemA;
    Item itemB;
public:
    ItemScene(int cindex, string cdescription,
          string cchoiceA,      string cchoiceB,
          string cconsequenceA, string cconsequenceB,
          int cnextSceneA,      int cnextSceneB,
          Item citemA,          Item citemB)
    : Scene(cindex, cdescription,
            cchoiceA, cchoiceB,
            cconsequenceA, cconsequenceB,
            cnextSceneA, cnextSceneB),
            itemA(citemA), itemB(citemB) {}

    int play(Player& player) override {
        cout << "\n" << description << endl;
        int next = presentChoices(player);
        if (next == nextSceneIdA) {
            player.addItem(itemA);
        }else{
            player.addItem(itemB);
        }

        return next;
    }
};

class CombatScene : public Scene {
private:
    Enemy enemy;

    void runCombat(Player& player) {
        cout << "\n-----Your enemy" << enemy.getName() << "'s stats-----"<< endl;
        cout << "| HP:  " << enemy.getHealth() << endl;
        cout << "| ATK: " << enemy.getAttack() << endl;
        cout << "| DEF: " << enemy.getDefense() << endl;

        Enemy currentEnemy = enemy;
        while (currentEnemy.isAlive() && player.isAlive()) {
            int playerDamage = player.getAttackDamage() + (rand() % 5) - 2;
            if (playerDamage < 0) {
                playerDamage = 0;
            }
            currentEnemy.takeDamage(playerDamage);
            cout << "\nYou attack " << currentEnemy.getName() << " for " << playerDamage << " damage!" <<
                " (Enemy HP: " << currentEnemy.getHealth() << ")" << endl;

            if (!currentEnemy.isAlive()) {
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(800)); // pause for better effect of fight

            int enemyDamage = currentEnemy.getAttack() + (rand() % 5) - 2;
            if (enemyDamage < 0) {
                enemyDamage = 0;
            }
            player.takeDamage(enemyDamage);
            cout << currentEnemy.getName() << " attacks you for " << enemyDamage << " damage!" <<
                " (Your HP: " << player.getHealth() << ")" << endl;

            this_thread::sleep_for(chrono::milliseconds(800));
        }
        if (currentEnemy.isAlive()) {
            cout << "\nYou were defeated by " << enemy.getName() << "..." << endl;
        }else {
            cout << "\nYou defeated " << enemy.getName() << "!" << endl;
            player.addScore(currentEnemy.getScoreReward());
            cout << "Your score increased by " << currentEnemy.getScoreReward() << endl;

            if (currentEnemy.getHasDrop()) {
                int dropRoll = rand() % 10;
                if (dropRoll < 4) {
                    cout << "After defeating the " << currentEnemy.getName() << " you receive loot "
                    << currentEnemy.getDropItem().getName() << "!" << endl;
                    player.addItem(currentEnemy.getDropItem());
                }
            }
        }
    }

public:
    CombatScene(int cindex, string cdescription,string cchoiceA, string cchoiceB,
        string cconsequenceA, string cconsequenceB, int cnextSceneA, int cnextSceneB, Enemy cenemy)
    : Scene(cindex, cdescription,cchoiceA, cchoiceB,
                cconsequenceA, cconsequenceB,cnextSceneA, cnextSceneB), enemy(cenemy){}

    int play(Player& player) override {
        cout << "\n" << description << endl;
        int next = presentChoices(player);
        if (next == nextSceneIdB) {
            int roll = rand() % 10;
            if (roll < 3) {
                cout << "\nYou managed to escape, but not without a hit..." << endl;
                player.takeDamage(10);
                cout << "You take 15 damage while running" << endl;
            }else {
                cout << "\nYou failed to avoid fight! The enemy attacks!" << endl;
                int enemyDamage = enemy.getAttack() + (rand() % 5) - 2;
                player.takeDamage(enemyDamage);
                cout << enemy.getName() << " hits you for " << enemyDamage << " damage." << endl;
                cout << "You are forced to fight!" << endl;
                runCombat(player);
            }
        }else {
            runCombat(player);
        }
        return next;
    }
};


class GameManager {
private:
    vector<Scene*> scenes;
    Player player;
    int currentSceneID;

    void setupScenes() {

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
        Item("Old Sword", ItemType::WEAPON, 5,  "A heavy sword. Attack +5"),
        Item("Bread",     ItemType::FOOD,   20, "Restores health. Health +20")
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
            Item("Bone Sword", ItemType::WEAPON, 3, "A cracked blade. Attack +3"))
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
        Item("Torch Shield", ItemType::ARMOUR, 4, "Light protection. Defense +4"),
        Item("Leather Vest", ItemType::ARMOUR, 6, "Decent armour. Defense +6")
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
        Item("Iron Sword",    ItemType::WEAPON, 6, "A solid blade. Attack +6"),
        Item("Health Potion", ItemType::FOOD,   30, "Restores health. Health +30")
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
        15, 0
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

    // ---- SCENE 9: Ghost of the Old Soldier (Lore) ----
    // Crawling through the wall you find a hidden chamber with a ghost
    // Both -> Scene 23
    scenes.push_back(new Scene(
        9,
        "You crawl through the wall into a hidden chamber.\n"
        "A faint blue glow fills the room.\n"
        "The ghost of an old soldier stands before you.\n"
        "He says: I died here a hundred years ago. Take my sword.\n"
        "It will serve you better than it served me.\n"
        "A glowing sword appears on the floor before you.",
        "Take the ghost sword",
        "Leave it and move on",
        "You pick up the sword. It hums with energy. Attack +8",
        "You leave it. The ghost fades silently.",
        23, 23
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
            Item("Goblin Spear", ItemType::WEAPON, 4, "A crude spear. Attack +4"))
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
            Item("Captain's Axe", ItemType::WEAPON, 10, "A heavy battle axe. Attack +10"))
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
        Item("Goblin Axe",   ItemType::WEAPON, 7, "Crude but sharp. Attack +7"),
        Item("Goblin Armour",ItemType::ARMOUR, 5, "Smells terrible. Defense +5")
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
        Item("Steel Gauntlets", ItemType::ARMOUR, 7, "Heavy hand armour. Defense +7"),
        Item("War Hammer",      ItemType::WEAPON, 8, "Slow but devastating. Attack +8")
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
            Item("Elven Bow", ItemType::WEAPON, 5, "A fine bow. Attack +5"))
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
            Item("Shaman Staff", ItemType::WEAPON, 6, "Crackles with energy. Attack +6"))
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
        Item("Chainmail Vest", ItemType::ARMOUR, 8, "Strong protection. Defense +8"),
        Item("Battle Axe",     ItemType::WEAPON, 7, "Well balanced axe. Attack +7")
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
            Item("Wizard's Staff", ItemType::WEAPON, 12, "Ancient and powerful. Attack +12"))
        ));
    }

    void showMainMenu() {
        cout << "\n========================================" << endl;
        cout << "       DEPTHS OF KAEL'DRATH" << endl;
        cout << "       A Text Adventure Game" << endl;
        cout << "========================================" << endl;
        cout << "1) New Game" << endl;
        cout << "2) Quit" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Enter choice (1/2): ";
    }
public:
    GameManager() {
        currentSceneID = 0;
        setupScenes();
    }

    ~GameManager() {
        for (int i = 0; i < scenes.size(); i++) {
            delete scenes[i];
        }
    }

    void run() {
        showMainMenu();
        int menuChoice;
        cin >> menuChoice;
        while (menuChoice < 1 || menuChoice > 2) {
            cout << "Invalid choice. Enter 1 or 2: ";
            cin >> menuChoice;
        }

        if (menuChoice == 2) {
            cout << "\nGoodbye!" << endl;
            return;
        }

        string name;
        cout << "\nEnter your name, brave adventurer: ";
        cin.ignore();
        getline(cin, name);
        while (name.empty()) {
            cout << "Name cannot be empty. Try again: ";
            getline(cin, name);
        }
        player = Player(name);
        currentSceneID = 0;
        cout << "\nWelcome, " << name << "! Your quest begins..." << endl;

        while (player.isAlive()) {
            cout << "\n[C] Continue   [I] Inventory & Stats: ";
            char opt;
            cin >> opt;
            opt = toupper(opt);

            while (opt != 'C' && opt != 'I') {
                cout << "Invalid input. Enter C or I: ";
                cin >> opt;
                opt = toupper(opt);
            }

            if (opt == 'I') {
                player.showInventory();
                player.showPlayerStats();
                continue;
            }

            Scene* current = nullptr;
            for (int i = 0; i < scenes.size(); i++) {
                if (scenes[i]->getSceneId() == currentSceneID) {
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
            currentSceneID = next;
        }

        if (!player.isAlive()) {
            cout << "\n========================================" << endl;
            cout << "          *** GAME OVER ***" << endl;
            cout << "========================================" << endl;
            cout << "You ran out of lives, " << player.getName() << "." << endl;
            cout << "Final Score: " << player.getScore() << endl;
        }
    }
};

int main() {
    GameManager game;
    game.run();
    return 0;
}