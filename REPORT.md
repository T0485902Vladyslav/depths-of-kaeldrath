| Module Code        | IY453                              |
| ------------------ | ---------------------------------- |
| Group              | A                                  |
| Module Title       | Software Design and Implementation |
| Assessment Type    | Coursework Stage 1                 |
| Module Tutor Name  | Mustafa Ghashim                    |
| Student ID Number  | P485902                            |
| Date of Submission | 29/01/2025                         |

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
                case ItemType::FOOD: score += item.getEffectValue();
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

        return presentChoices(player);
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

class GameManager {
private:
    vector<Scene*> scenes;
    Player player;
    int currentSceneID;

    void setupScenes() {
        //SCENE 0: Dungeon Entrance (ItemScene)
        scenes.push_back(new ItemScene(
            0,
            "You are at the entrance of the dungeon.\n"
            "A dead adventurer is lying near the door.\n"
            "He has two items. You can only take one.",
            "Take the old sword",
            "Take the bread",
            "You take the sword. It is heavy but sharp.",
            "You eat the bread. You feel better.",
            1, 1,
            Item("Old Sword", ItemType::WEAPON, 5,  "A heavy sword. Attack +5"),
            Item("Bread",     ItemType::FOOD,   20, "Restores health. Health +20")
        ));

        //SCENE 1: First Room (PuzzleScene)
        scenes.push_back(new PuzzleScene(
            1,
            "You walk into a small room.\n"
            "A stone door blocks the way forward.\n"
            "A sign on the door says: Solve this to open the door.\n",
            "Answer the question",
            "Try to break the door",
            "You decide to try to answer ",
            "You hit the door. It does not move. Your hands hurt.",
            2, 2,
            "A farmer has 10 sheep. All but 6 run away. How many sheep are left?",
            "6",
            10, 15
        ));

        //SCENE 2: The Dark Hall (DefaultScene)
        scenes.push_back(new Scene(
            2,
            "You enter a long dark hall.\n"
            "There are old paintings on the walls.\n"
            "At the end of the hall there are two doors.\n"
            "One door is big and made of iron.\n"
            "The other door is small and made of wood.",
            "Go through the iron door",
            "Go through the wooden door",
            "You push the iron door open. It is very heavy.",
            "You open the wooden door. It creaks loudly.",
            3, 3
        ));

        //SCENE 3: Old Storage Room (ItemScene)
        scenes.push_back(new ItemScene(
            3,
            "You find an old storage room.\n"
            "There are two items on the floor.\n"
            "A metal shield and a piece of armour.\n"
            "You can only carry one.",
            "Take the metal shield",
            "Take the armour",
            "You pick up the shield. It will protect you.",
            "You put on the armour. It fits well.",
            4, 4,
            Item("Metal Shield", ItemType::ARMOUR, 5, "Blocks some damage. Defense +5"),
            Item("Armour",       ItemType::ARMOUR, 8, "Good protection. Defense +8")
        ));

        //SCENE 4: The Bridge Room (PuzzleScene)
        scenes.push_back(new PuzzleScene(
            4,
            "You come to a bridge over a deep hole.\n"
            "A guard is standing in front of the bridge.\n"
            "He says: Answer my question and you may pass.\n",
            "Guard begins to speak...",
            "Try to sneak past the guard",
            "You think for a moment...",
            "The guard sees you. He hits you with his stick.",
            5, 5,
            "I have 3 apples. I eat 1 and find 2 more.How many apples?",
            "4",
            10, 15
        ));

        //SCENE 5: A Friendly Prisoner (DefaultScene)
        scenes.push_back(new Scene(
            5,
            "You see a man sitting in a cage.\n"
            "He says: Hey! Let me out and I will help you.\n"
            "I know this dungeon very well.\n"
            "There is a key on the wall next to the cage.",
            "Free the prisoner",
            "Leave him and move on",
            "You unlock the cage. The man says: Thank you!\n"
            "The next room has a number puzzle. The answer is always double the first number.",
            "You walk away. The man shouts: You will regret this!",
            6, 6
        ));

        //SCENE 6: The Number Door (PuzzleScene)
        scenes.push_back(new PuzzleScene(
            6,
            "You are in a room with a locked door.\n"
            "You see a inscription with a simple equation.\n",
            "Try to solve",
            "Look for another way out",
            "You say the number out loud...",
            "You search the room but find nothing. A trap door opens under your feet!",
            7, 7,
            "What is 6 * 7?",
            "42",
            10, 10
        ));

        //SCENE 7 Riddle (PuzzleScene)
        scenes.push_back(new PuzzleScene(
            7,
            "You reach a big room at the end of the dungeon.\n"
            "There is a large chest in the middle of the room.\n"
            "The chest has a lock with a question on it:\n"
            "What are you planning to do?",
            "Answer the riddle",
            "Try to force the chest open",
            "You think carefully...",
            "You try to break the lock. It shocks you with a spark of magic!",
            8, 8,
            "What has 4 legs in the morning, 2 legs at noon, and 3 legs at night?",
            "man",
            15, 20
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
            cout << "Goodbye!" << endl;
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

        // if (!player.isAlive()) {
        //     cout << "\n========================================" << endl;
        //     cout << "          *** GAME OVER ***" << endl;
        //     cout << "========================================" << endl;
        //     cout << "You ran out of lives, " << player.getName() << "." << endl;
        //     cout << "Final Score: " << player.getScore() << endl;
        // }
    }
};

int main() {
    GameManager game;
    game.run();
    return 0;
}
```
