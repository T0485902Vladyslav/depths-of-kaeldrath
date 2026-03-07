#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class ItemType {
    WEAPON,
    ARMOR,
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
                case ItemType::ARMOR: defense += item.getEffectValue();
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
        cout << "===" << name << " 's Stats ===" << endl;
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

    virtual void play(Player& player) = 0;

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
public:
    PuzzleScene(int cindex, const string& cdescription,
            const string& cchoiceA, const string& cchoiceB,
            const string& cconsequenceA, const string& cconsequenceB,
            int cnextSceneA, int cnextSceneB,
            const string& cquestion,const string& canswer,
            int cscoreReward)
    : Scene(cindex, cdescription,
            cchoiceA, cchoiceB,
            cconsequenceA, cconsequenceB,
            cnextSceneA, cnextSceneB) {
        question = cquestion;
        answer = canswer;
        scoreReward = cscoreReward;
    }

    void play(Player& player) override {
        cout << "\n========================================" << endl;
        cout << description << endl;
        cout << "========================================" << endl;
        cout << "\n" << player.getName()<< "You must answer to proceed: "<< endl;
        cout << question << endl;

        string userAnswer;
        cout << "\nYour answer: ";
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
            cout << "You take 15 damage for wrong answer"

        }
    }

};

int main() {

}