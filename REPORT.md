| Module Code        | IY453                              |
| ------------------ | ---------------------------------- |
| Group              | A                                  |
| Module Title       | Software Design and Implementation |
| Assessment Type    | Coursework Stage 3                 |
| Module Tutor Name  | Mustafa Ghashim                    |
| Student ID Number  | P485902                            |
| Date of Submission | 15/03/2025                         |

☒ *I confirm that this assignment is my own work. Where I have referred to academic
sources, I have provided in-text citations and included the sources in the
final reference list.*

 ☒ *Where I have used AI, I have cited and
referenced appropriately.*

# **Introduction**

This project is a text-based "choose your own adventure" game where the player finds themselves at the centre of an interactive storyline. The game relies entirely on text descriptions and user choices to create an immersive experience, allowing the player to explore the world, make decisions and influence the storyline.
The adventure is built on branching storylines, where each choice has its own weight and leads to different consequences, paths, and endings. Instead of graphics, the focus of program is on atmosphere, storytelling, and the player's imagination, as the program is entirely text-based. The goal of this project is to create a simple but engaging game that demonstrates logical structure, decision-making, and narrative flow in a text-based environment.

## 

---

### Program Specification

---

## Core functionality

- The program should provide a text-based “choose your own adventure” game where the player navigates the story using text input and output only.

- The program should prompt the player to enter their name at the start of the game and use this name within game dialogue and messages to personalise the experience.

- The game should present the player with binary choices (two options) in each scenario, with each choice leading to different consequences.

- Some choices lead to the game ending, forcing the player to start over, while other choices allow the player to progress towards completing the game.

- The program should provide clear feedback of each player choice, describing the outcome.

- The game should maintain player statistics, including health, attack power, defence, inventory, and score, which are updated throughout gameplay.

- The program should include an inventory system that allows the player to collect, store, and manage items found during the adventure.

- Items such as weapons, clothing, food, potions, and keys should influence the rest of the game by unlocking or adding new choices and paths, as well as changing the player's stats.

- The game should include combat-based scenarios where the outcome of battles is influenced by player stats and collected items.

- The game shall include puzzle-based scenarios, such as riddles, anagrams, or logic-based challenges, which must be solved to progress.

- The program should allow the player to save their game progress to a file and load a saved game, restoring all relevant game state data (player name, current scene,
   inventory, stats, and score).

- The game should implement a scoring system that rewards the player for defeating enemies, solving puzzles, and completing challenges.

- The program shall display the current score at key points in the game and present a final score screen at the end of the game.

- The program should validate all user input to ensure reliability and prevent crashes, displaying clear error messages when invalid data is entered by user.

### System constraints

- System should compile and run in the CLion IDE using the C++17standard or later and must ensure cross-platform compatibility.

- The program should be a console-based application and must not use any graphical user interface.

- All interaction between the player and the game should be performed using text input and text output.

- Each game scenario should give the player exactly two choices, ensuring binary decision-making throughout the game.

- The game should have at least 30 binary choices across the full gameplay experience.

- The program should use either text files or binary files to store game data and give opportunity to resume game.

- The program should handle invalid input correctly and should not terminate unexpectedly due to incorrect user input.

#### 

---

### Input/Process/Output table

---

| *Feature/Task*        | *Inputs*                   | *Process*                                                                  | *Output*                                  |
| --------------------- | -------------------------- | -------------------------------------------------------------------------- | ----------------------------------------- |
| *Start game*          | *None (program launch)*    | *Initialise game variables, set default player stats, prepare first scene* | *Welcome message*                         |
| *Enter player name*   | *Player name (text input)* | *Validate name input and store player name*                                | *Personalised greeting with player*       |
| *Display scene*       | *None*                     | *Load scenario description and available choices*                          | *Scenario text and two choices displayed* |
| *Player choice*       | *Player choice (1 or 2)*   | Validate input and determine next scene based on choice                    | *Outcome description or next scenario*    |
| *Save game*           | *Save option*              | *Save player data, inventory, stats, score and current scene to file.*     | *Successful or error message*             |
| *Load game*           | *Load option*              | *Read saved data from file and resume the game.*                           | *Successful or error message*             |
| *Display score*       | *Results during the game*  | *Calculate and update score*                                               | *Current score*                           |
| *Combat encounter*    | *Player and enemy stats*   | *Calculate combat outcome*                                                 | *Victory, defeat, or game over message*   |
| *Update player stats* | *Choice result*            | *Update health, inventory, score, etc.*                                    | *Updated player stats*                    |
| *Use item*            | *Item stats*               | *Apply item effects (heal, boost stats, unlock path)*                      | *Updated stats or unlocked option.*       |
| *End game*            | *Final scene*              | *Calculate final score and end the game.*                                  | *Victory message and final score*         |

### Algorithm

![gfd](/Users/dushesssx/Downloads/453%20algorithm%20-%20Frame%202.jpg)

![hgf](/Users/dushesssx/Downloads/453%20algorithm%20-%20Frame%203.jpg)

![gfgf](/Users/dushesssx/Downloads/453%20algorithm%20-%20Frame%202-2.jpg)

### Class Digram

![gf](/Users/dushesssx/Downloads/class%20diagram%20453.png)

### Program code

```c++
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <limits>
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
    int durability;
    int maxDurability;
public:
    Item(string cname, ItemType ctype, int ceffect_value, string cdescription, int cdurability = 0) {
        name = cname;
        type = ctype;
        effect_value = ceffect_value;
        description = cdescription;
        durability = cdurability;
        maxDurability = cdurability;
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
    int getDurability() const {
        return durability;
    }
    int getMaxDurability() const {
        return maxDurability;
    }
    bool isBroken() const {
        bool broken = false;

        if (type != ItemType::FOOD && durability <= 0) {     //food has no durability
            broken = true;
        }
        return broken;
    }

    void reduceDurability() {
        if (durability > 0) {
            durability--;
        }
    }

    void printItemInfo() const{
        cout << "{" << name << "} " << description << endl;
        cout << "Effect: " << effect_value << endl;
    }
};

class Player {
private:
    string name;
    int health;
    int lives;
    int baseAttack;
    int defense;
    int score;
    vector<Item> inventory;
    int equipped_weapon_index = -1;
    int equipped_armour_index = -1;

public:
    Player(string cname) {
        name = cname;
        health = MAX_HEALTH;
        lives = 3;
        baseAttack = 10;
        defense = 0;
        score = 0;
        equipped_weapon_index = -1;
        equipped_armour_index = -1;
    }

    Player() {
        name = "";
        health = MAX_HEALTH;
        lives = 3;
        baseAttack = 10;
        defense = 0;
        score = 0;
        equipped_weapon_index = -1;
        equipped_armour_index = -1;
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

    int getAttackDamage() const {
        int attack = baseAttack;
        if (equipped_weapon_index != -1
            && !inventory[equipped_weapon_index].isBroken()) {
            attack = baseAttack
                   + inventory[equipped_weapon_index].getEffectValue();
            }
        return attack;
    }

    int getDefense() const {
        int actual_defense = 0;
        if (equipped_armour_index != -1
            && !inventory[equipped_armour_index].isBroken()) {
            actual_defense = inventory[equipped_armour_index].getEffectValue();
            }
        return actual_defense;
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
        int actualDamage = amount - getDefense();
        if (actualDamage < 0) {
            actualDamage = 0;
        }
        health -= actualDamage;

        if (equipped_armour_index != -1) {
            inventory[equipped_armour_index].reduceDurability();
            if (inventory[equipped_armour_index].isBroken()) {
                cout << "Your " << inventory[equipped_armour_index].getName() << " broke" << endl;
                equipped_armour_index = -1;
            }
        }

        if (health <= 0) {
            health = 0;
            lives--;
            if (lives > 0) {
                health = MAX_HEALTH;
                cout << "You lost a life! Life remaining: " << lives << endl;
            }
        }
    }

    void reduceWeaponDurability() {
        if (equipped_weapon_index != -1) {
            inventory[equipped_weapon_index].reduceDurability();
            if (inventory[equipped_weapon_index].isBroken()) {
                cout << "Your " << inventory[equipped_weapon_index].getName() << " broke" << endl;
                equipped_weapon_index = -1;
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
            cout << "You picked up: " << item.getName() << endl;
            cout << "To equip, use or swap the item, open your inventory" << endl;
            success = true;
        }else {
            cout << "Inventory is full." << endl;
        }
        return success;
    }

    void equipItem(int index) {

        if (index < 0 || index >= (int)inventory.size()) {
            cout << "\nInvalid item index." << endl;
        }
        else {

            Item& item = inventory[index];
            ItemType type = item.getType();

            if (type == ItemType::WEAPON) {
                equipped_weapon_index = index;
                cout << "\nEquipped weapon: " << item.getName() << endl;
            }
            else if (type == ItemType::ARMOUR) {
                equipped_armour_index = index;
                cout << "\nEquipped armour: " << item.getName() << endl;
            }
            else {
                cout << "\nThis item cannot be equipped." << endl;
            }
        }
    }

    void useFood(int index) {
        if (index < 0 || index >= (int)inventory.size()) {
            cout << "Invalid item." << endl;
        } else if (inventory[index].getType() != ItemType::FOOD) {
            cout << "You can only use food items." << endl;
        } else {
            Item& item = inventory[index];
            heal(item.getEffectValue());
            cout << "You used " << item.getName() << ". Health +" << item.getEffectValue() << endl;
            cout << "Current health: " << health << "/" << MAX_HEALTH << endl;
            inventory.erase(inventory.begin() + index);

            if (equipped_weapon_index > index) {
                equipped_weapon_index--;
            } else if (equipped_weapon_index == index) {
                equipped_weapon_index = -1;
            }

            if (equipped_armour_index > index) {
                equipped_armour_index--;
            } else if (equipped_armour_index == index) {
                equipped_armour_index = -1;
            }
        }
    }

    void showInventory() {

        char opt = ' ';

        while (opt != 'B') {

            cout << "\n=== Inventory ===" << endl;

            if (inventory.empty()) {
                cout << "Your inventory is empty\n";
            }
            else {
                for (int i = 0; i < (int)inventory.size(); i++) {
                   cout << i + 1 << ") ";
                    inventory[i].printItemInfo();

                    if (inventory[i].getType() == ItemType::WEAPON || inventory[i].getType() == ItemType::ARMOUR) {
                        cout << "Durability: " << inventory[i].getDurability() << "/" << inventory[i].getMaxDurability() << "\n";
            }
                }
            }

            cout << "\n=== Equipped ===" << endl;

            if (equipped_weapon_index != -1) {
                Item& w = inventory[equipped_weapon_index];
                cout << "Weapon: " << w.getName() << " (Durability: " << w.getDurability() << "/" << w.getMaxDurability() << ")" << endl;
            }
            else {
                cout << "Weapon: none (base attack: " << baseAttack << ")" << endl;
            }

            if (equipped_armour_index != -1) {
                Item& a = inventory[equipped_armour_index];
                cout << "Armour: " << a.getName() << " (Durability: " << a.getDurability() << "/" << a.getMaxDurability() << ")" << endl;
            }
            else {
                cout << "Armour: none" << endl;
            }

            cout << "\nE) Equip item   U) Use food   B) Back" << endl;
            cout << "Choice: ";

            if (!(cin >> opt)) {

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid input." << endl;
                continue;
            }

            opt = toupper(opt);

            if (opt == 'E' || opt == 'U') {

                int num;
                bool valid = false;

                while (!valid) {

                    cout << "Enter item number: ";

                    if (!(cin >> num)) {

                        cout << "Invalid input. Enter a number.\n";

                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if (num <= 0) {
                        cout << "Number must be greater than 0.\n";
                    }
                    else {
                        valid = true;
                    }
                }

                if (opt == 'E') equipItem(num - 1);
                else useFood(num - 1);
            }
            else if (opt != 'B') {
                cout << "Invalid choice. Enter E, U or B." << endl;
            }
        }
    }

    void showPlayerStats() const {
        cout << "===" << name << "'s Stats ===" << endl;
        cout << "Health: " << health << "/" << MAX_HEALTH << endl;
        cout << "Damage: " << getAttackDamage() << endl;
        cout << "Defense: " << getDefense() << endl;
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
    char lastChoice = ' ';
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

        char userChoice = ' ';
        bool validInput = false;

        while (!validInput) {
            cout << player.getName() << ", what do you do? (A/B): ";

            string line;
            getline(cin, line);

            if (line.empty()) {
                cout << "Input cannot be empty. Please enter A or B.\n";
            } else {
                userChoice = toupper(line[0]);

                if (userChoice == 'A' || userChoice == 'B') {
                    validInput = true;
                } else {
                    cout << "Invalid input. Please enter A or B.\n";
                }
            }
        }

        lastChoice = userChoice;

        int result;
        if (userChoice == 'A') {
            cout << "\n>> " << consequenceA << endl;
            result = nextSceneIdA;
        } else {
            cout << "\n>> " << consequenceB << endl;
            result = nextSceneIdB;
        }

        return result;
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
            cout << "\n" << player.getName() << ", you must answer to proceed." << endl;

            string userAnswer;
            bool validInput = false;

            while (!validInput) {
                cout << "Your answer: ";
                getline(cin, userAnswer);

                if (userAnswer.empty()) {
                    cout << "Answer cannot be empty. Try again.\n";
                } else {
                    validInput = true;
                }
            }

            for (int i = 0; i < (int)answer.size(); i++) {
                answer[i] = tolower(answer[i]);
            }
            for (int i = 0; i < (int)userAnswer.size(); i++) {
                userAnswer[i] = tolower(userAnswer[i]);
            }

            if (userAnswer == answer) {
                cout << "\n>> Correct! Well done, " << player.getName() << endl;
                player.addScore(scoreReward);
                cout << "Your score has increased by " << scoreReward << endl;
            } else {
                cout << "Wrong! The answer was: " << answer << endl;
                player.takeDamage(damageOnFail);
                cout << "You take " << damageOnFail << " damage for wrong answer!" << endl;
            }
        } else {
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

        if (lastChoice == 'A') {
            player.addItem(itemA);
        } else {
            player.addItem(itemB);
        }

        return next;
    }
};

class CombatScene : public Scene {
private:
    Enemy enemy;

    void runCombat(Player& player) {
        cout << "\n-----Your enemy " << enemy.getName() << "'s stats-----"<< endl;
        cout << "| HP:  " << enemy.getHealth() << endl;
        cout << "| ATK: " << enemy.getAttack() << endl;
        cout << "| DEF: " << enemy.getDefense() << endl;

        Enemy currentEnemy = enemy;

        this_thread::sleep_for(chrono::milliseconds(1500));

        while (currentEnemy.isAlive() && player.isAlive()) {
            int playerDamage = player.getAttackDamage() + (rand() % 5) - 2;
            if (playerDamage < 0) {
                playerDamage = 0;
            }
            currentEnemy.takeDamage(playerDamage);
            player.reduceWeaponDurability();
            cout << "\nYou attack " << currentEnemy.getName() << " for " << playerDamage << " damage!" <<
                " (Enemy HP: " << currentEnemy.getHealth() << ")" << endl;

            if (!currentEnemy.isAlive()) {
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(1000)); // pause for better effect of fight

            int enemyDamage = currentEnemy.getAttack() + (rand() % 5) - 2;
            if (enemyDamage < 0) {
                enemyDamage = 0;
            }
            player.takeDamage(enemyDamage);
            cout << currentEnemy.getName() << " attacks you for " << enemyDamage << " damage!" <<
                " (Your HP: " << player.getHealth() << ")" << endl;

            this_thread::sleep_for(chrono::milliseconds(1000));
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

        if (lastChoice == 'A') {
            runCombat(player);
        } else {
            int roll = rand() % 10;
            if (roll < 3) {
                cout << "\nYou managed to escape, but not without a hit..." << endl;
                player.takeDamage(15);
                cout << "You take 15 damage while running" << endl;
            } else {
                cout << "\nYou failed to avoid fight! The enemy attacks!" << endl;
                int enemyDamage = enemy.getAttack() + (rand() % 5) - 2;
                player.takeDamage(enemyDamage);
                cout << enemy.getName() << " hits you for " << enemyDamage << " damage." << endl;
                cout << "You are forced to fight!" << endl;
                runCombat(player);
            }
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

    void setupPlayer() {
        string name;

        cout << "\nEnter your name, brave adventurer: ";

        getline(cin, name);

        while (name.empty()) {
            cout << "Name cannot be empty. Try again: ";
            getline(cin, name);
        }

        player = Player(name);
        currentSceneID = 0;

        cout << "\nWelcome, " << name << "! Your quest begins..." << endl;
    }

    void gameLoop() {
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

    void run() {
        showMainMenu();

        int menuChoice;
        bool validInput = false;

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
                        cout << "Invalid input. Enter 1 or 2: ";
                    } else if (menuChoice < 1 || menuChoice > 2) {
                        cout << "Invalid choice. Enter 1 or 2: ";
                    } else {
                        validInput = true;
                    }
                } catch (...) {
                    cout << "Invalid input. Enter 1 or 2: ";
                }
            }
        }

        if (menuChoice == 2) {
            cout << "\nGoodbye!" << endl;
        }
        else {
            setupPlayer();
            gameLoop();
        }
    }
};

int main() {
    srand(time(0));
    GameManager game;
    game.run();
    return 0;
}
```

### Testing

<style>
</style>

| **Test No.** | **Item to test**       | **Test Description (with example data)**                                     | **Expected Result**                       | **Actual Result**                         | **Comments / Actions** |
| ------------ | ---------------------- | ---------------------------------------------------------------------------- | ----------------------------------------- | ----------------------------------------- | ---------------------- |
| 1            | Main menu              | Valid - Enter 1                                                              | Game starts, asks for  player name        | Game starts, asks for player name         | Test passed            |
| 2            | Main menu              | Invalid - Enter abc                                                          | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 3            | Main menu              | Extreme valid - Enter 2                                                      | Prints "Goodbye!" and exits               | Prints "Goodbye!" and exits               | Test passed            |
| 4            | Main menu              | Extreme invalid - Enter 999                                                  | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 5            | Main menu              | Error - Press Enter with no  input                                           | Prints error, asks again                  | Prints error, asks again                  | Test  passed           |
| 6            | Player name            | Valid - Enter Vlad                                                           | Prints "Welcome, Vlad!"                   | Prints "Welcome, Vlad!"                   | Test passed            |
| 7            | Player name            | Invalid - Enter only spaces                                                  | Prints error, asks again                  | Accept name                               | Test failed            |
| 8            | Player name            | Extreme valid - Enter very long name Aaaaaaaaaaaaaaaaaaaaaa                  | Name accepted and used in dialogue        | Name accepted and used in dialogue        | Test passed            |
| 9            | Player name            | Extreme invalid - Enter special characters @#$%                              | Accepted as name                          | Accepted as name                          | Test passed            |
| 10           | Player name            | Error - Press Enter with no input                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 11           | Game loop (C/I)        | Valid - Enter C                                                              | Moves to next scene                       | Moves to next scene                       | Test passed            |
| 12           | Game loop (C/I)        | Invalid - Enter X                                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 13           | Game loop (C/I)        | Extreme valid - Enter lowercase i                                            | Accepted, opens inventory                 | Accepted, opens inventory                 | Test passed            |
| 14           | Game loop (C/I)        | Extreme invalid - Enter 999                                                  | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 15           | Game loop (C/I)        | Error - Press Enter with no input                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 16           | Scene choice (A/B)     | Valid - Enter A                                                              | Prints consequence A, correct scene loads | Prints consequence A, correct scene loads | Test passed            |
| 17           | Scene choice (A/B)     | Invalid - Enter Z                                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 18           | Scene choice (A/B)     | Extreme valid - Enter lowercase b                                            | Accepted, same as B                       | Accepted, same as B                       | Test passed            |
| 19           | Scene choice (A/B)     | Extreme invalid - Enter 999                                                  | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 20           | Scene choice (A/B)     | Error - Press Enter with no input                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 21           | Puzzle answer          | Valid - Enter 6 (sheep puzzle)                                               | Prints "Correct!", score +10              | Prints "Correct!", score +10              | Test passed            |
| 22           | Puzzle answer          | Invalid - Enter abc                                                          | Prints "Wrong!", player takes 15 damage   | Prints "Wrong!", player takes 15 damage   | Test passed            |
| 23           | Puzzle answer          | Extreme valid - Enter MAP uppercase (riddle)                                 | Accepted as correct                       | Accepted as correct                       | Test passed            |
| 24           | Puzzle answer          | Extreme invalid - Enter 99999                                                | Prints "Wrong!", player takes damage      | Prints "Wrong!", player takes damage      | Test passed            |
| 25           | Puzzle answer          | Error - Press Enter with no input                                            | Prints "Wrong!", player takes damage      | Prints "Wrong!", player takes damage      | Test passed            |
| 26           | Inventory menu (E/U/B) | Valid - Enter E                                                              | Asks for item number                      | Asks for item number                      | Test passed            |
| 27           | Inventory menu (E/U/B) | Invalid - Enter X                                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 28           | Inventory menu (E/U/B) | Extreme valid - Enter lowercase b                                            | Accepted, returns to game loop            | Accepted, returns to game loop            | Test passed            |
| 29           | Inventory menu (E/U/B) | Extreme invalid - Enter 999                                                  | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 30           | Inventory menu (E/U/B) | Error - Press Enter with no input                                            | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 31           | Inventory item number  | Valid - Enter 1 (with items in inventory)                                    | Equips/uses item 1                        | Equips/uses item 1                        | Test passed            |
| 32           | Inventory item number  | Invalid - Enter abc                                                          | Prints error, asks again                  | Prints error, asks again                  | Test passed            |
| 33           | Inventory item number  | Extreme valid - Enter last valid index, for example 3 (3 items in inventory) | Equips/uses item 3                        | Equips/uses item 3                        | Test passed            |
| 34           | Inventory item number  | Extreme invalid - Enter 99                                                   | Prints "Invalid item index"               | Prints "Invalid item index"               | Test passed            |
| 35           | Inventory item number  | Error - Enter 0                                                              | Prints error, asks again                  | Prints error, asks again                  | Test passed            |

## Annoteted screenshots

![gf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=EB033C14-708B-4DA3-87F4-7B8A02302841&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.43.png)

Screenshot 1: Main menu validation for empty and invalid inputs, program proceed after valid input 

![fd](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=850FCCD5-296E-4F41-A745-6E6B4AA7AEF4&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.43.png)

Screenshot 2: Player name validation preventing empty input

![gf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=437FDFBE-7239-46D4-9CFD-EEBA6FA95795&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.44.png)

Screenshot 3: Game loop validation for invalid inputs

![gf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=D14AC947-78BE-4CD4-973D-390CA5BEB2CA&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.45.png)

Screenshot 4: Scene choice validation  

![gf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=6D5E32E5-E2EF-45D3-8237-C9F2AAD452DF&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.49.png)

Screenshot 5: Puzzle scene validation for empty input

![gdf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=C3E2BD6B-0280-4EF8-B631-179FA0367A51&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.54.png)

Screenshot 6: Inventory validation for invalid item indexes

![gfd](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=B7C137AF-03F0-4A20-8FA6-E801E16F520C&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2021.53.png)

Screenshot 7: Inventory system validation for invalid inputs

![gdf](/private/var/folders/60/82cg9ybd2bg7kgrh339d3zpr0000gn/T/TemporaryItems/com.apple.Photos.NSItemProvider/uuid=5F1F4424-95A5-45DD-B900-761D0FD61DE7&code=001&library=1&type=1&mode=1&loc=true&cap=true.png/Image%2015-03-2026%20at%2022.20.png)

Screenshot 8: Game over output after player loses all lives

### Technical elements

**Constants**

Two global constants control the game's limits. MAX_HEALTH is set to 100 and
defines the maximum health a player can have, preventing healing beyond this
value. MAX_INVENTORY is set to 10 and defines the maximum number of items a player can carry.

**Enum ItemType**

An enumeration that defines for now the three categories an item can belong to: WEAPON, ARMOUR, and FOOD. This makes the code more readable and allows the program to handle each item type differently without relying on raw numbers or strings.

**Class Item**

Represents a collectable object in the game. Each item stores a name, type, effect value, description, current durability, and maximum durability. Items of type WEAPON increase attack damage, items of type ARMOUR reduce incoming damage, and items of type FOOD restore health when used. The class provides getter
methods to access its data and methods to reduce durability and check if an
item is broken.

**Class Player**

Represents the human player and holds all player state including name, health, lives, base attack, score, and inventory. The inventory is stored as a vector of Item objects. Two integer fields equipped_weapon_index and equipped_armour_index track
which inventory slots are currently equipped, using -1 to indicate nothing is equipped. Key methods include takeDamage() which reduces health and handles life loss, heal() which restores health up to the maximum, addItem() which adds items to the inventory, equipItem() which sets the equipped index for a weapon or armour, useFood() which consumes a food item and heals the player, and showInventory() and showPlayerStats() which display information to the player.

**Class Enemy**

Represents an enemy the player can fight. Stores name, health, attack, defense, score reward, and an optional drop item. The takeDamage() method reduces enemy health accounting for its defense value. The isAlive() method returns whether the enemy still has health remaining. Some enemies are constructed with a drop item that has a chance to be awarded to the player after defeat.

**Class Scene (Parent Class)**

The base class for all scene types. Stores a scene ID, description text, two choices (A and B), their consequence messages, and the next scene IDs they lead to. Also stores lastChoice which records whether the player selected A or B, used by subclasses to determine outcomes. The virtual play() method is overridden by each subclass to define specific behaviour. The presentChoices() method handles displaying options and reading validated player input.

**Class PuzzleScene (inherits Scene)**

A scene type where the player is presented with a riddle or maths challenge. If the
player chooses to attempt the puzzle (choice A), they must enter the correct
answer. A correct answer awards score points. An incorrect answer or skipping
the puzzle (choice B) deals damage to the player. Both outcomes progress to the
next scene.

**Class ItemScene (inherits Scene)**

A scene type where the player chooses between two items to pick up. The lastChoice field from the base class determines which item is added to the player's inventory.

**Class CombatScene (inherits Scene)**

A scene type where the player encounters an enemy. Choice A initiates direct combat with the private runCombat() method. Choice B attempts an escape, with a
random roll determining whether the player escapes with minor damage or is
forced to fight anyway. The runCombat() method runs an automatic turn-based battle loop where both the player and enemy deal randomised damage
each round until one is defeated.

**Class GameManager**

The central controller of the game. It owns a vector of Scene pointers and a Player object. The setupScenes() method initialises all scenes and adds them to the
vector. The setupPlayer() method reads the player's name and creates their character. The gameLoop() method runs the main game loop, finding the current scene by ID and calling its play() method until the player runs out of lives. The run() method displays the main menu and starts the game.

**Data Structures**

A vector<Item> is
used for the player's inventory, allowing items to be added and removed
dynamically. A vector<Scene*> is used in GameManager to store pointers to all scenes, enabling polymorphism so that play() calls the correct overridden version for each scene type.

**Input Validation**

All user input throughout the program is read using getline() to capture the
full line including empty input. Each input point validates against expected
values and displays a specific error message if the input is empty, non-numeric
where a number is expected, or outside the valid range, prompting the user to
try again.
