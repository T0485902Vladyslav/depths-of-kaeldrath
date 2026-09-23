# Depths of Kael'Drath

A branching text-based dungeon adventure written in **C++20**.

Descend into the depths of Kael'Drath, fight your way past hostile creatures, solve puzzles blocking your path, find keys to unlock sealed doors, and manage a limited inventory of weapons, armour and supplies as you try to survive the dungeon. Right from the start you pick one of two entirely separate paths into the dungeon, and every scene after that keeps branching the same way — the two routes lead to different enemies, puzzles and rooms, not just the same content in a different order. Your health, lives, items and score all decide how far you get and how your run ends.

I built this as a university coursework project to properly practise OOP in C++ — scenes, combat, items and saving are all separate classes that plug into a shared `Scene` interface, so adding a new type of scene or enemy doesn't require touching the game loop itself.

---

## 📖 Table of Contents

- [Features](#-features)
- [Built With](#-built-with)
- [Usage](#-usage)
- [Screenshots](#-screenshots)
- [Installation](#-installation)
- [Project Structure](#-project-structure)

---

## ✨ Features

- **Two branching starting paths** — the very first choice sends you down one of two genuinely different routes, each with its own scenes and content, and every scene after keeps branching the same way.
- **Turn-based combat** — randomised attack damage, enemy stats, weapon durability loss on hits, and a lost fight costs a life instead of ending the run.
- **Loot on defeat** — enemies can drop items on death, with keys dropping more often than other loot.
- **Escape or fight** — some encounters let you try to flee instead of fighting; if the escape chance fails, the enemy strikes first and you're forced into combat anyway.
- **Locked doors** — the main path through some doors needs a matching key; without one you can try to force it open for a small chance of success, otherwise you take damage and get rerouted. There's always a second path too, one that skips the door but costs you a fixed chunk of health.
- **Puzzle scenes** — riddle-style Q&A that rewards score for a correct answer and damage for a wrong one.
- **Inventory & equipment** — weapons, armour, food and keys with a capped inventory; equip gear to boost stats, eat food to heal, durability breaks equipment over time.
- **Health & lives system** — health resets after a lost fight, but lives don't — run out of lives and it's game over.
- **Score tracking** — earned from defeating enemies and solving puzzles.
- **Multiple endings** — your ending depends on your final score and the items you've collected.
- **Save/Load system** — save your run to a file and continue later.

---

## 🛠️ Built With

- **C++20**
- **CMake**
- Standard C++ libraries (no external dependencies)
- File I/O for save/load functionality

---

## 🎮 Usage

Enter your character's name when prompted, then make your way through the dungeon one scene at a time. Each scene shows a short description followed by two choices (A/B).

During normal exploration you can:

- **Choose A or B** to move forward and trigger that path's consequence.
- Depending on the scene, you may be dropped into **combat**, a **puzzle**, offered an **item**, or stopped by a **locked door**.

During combat:

- Attacking deals damage with some random variance and wears down your equipped weapon.
- Choosing not to fight gives you a chance to escape, but if it fails, the enemy strikes first and you're forced into combat anyway.
- Losing all your health in a fight costs a life, and your health resets so you can try the fight again.

Between scenes you can open your **inventory** at almost any time to:

- Browse your full inventory list, with durability shown next to each weapon and armour piece.
- See what's currently equipped, or that nothing is if you're going in bare-handed.
- Equip a different weapon or armour piece to swap out your current gear.
- Use a food item on the spot to heal, which removes it from your inventory afterwards.

You can also **save** your progress to a file at any point and **load** it later from the main menu.

Your final score, along with the items and keys you've collected along the way, determines how the run ends.

---

## 📸 Screenshots

<!-- Add screenshots to a docs/ folder and update the paths below -->

### Main Menu

![а](/Users/dushesssx/CLionProjects/T0485902projectC++%231/docs/screenshot-menu.png)

### Story Scene

![пва](/Users/dushesssx/CLionProjects/T0485902projectC++%231/docs/screenshot-scene.png)




### Combat

![Shows the enemy's stats header and an attack exchange mid-fight.](/Users/dushesssx/CLionProjects/T0485902projectC++%231/docs/screenshot-combat.png)


### Inventory

![Shows the inventory list with durability and the equipped weapon/armour section.](/Users/dushesssx/CLionProjects/T0485902projectC++%231/docs/screenshot-inventory.png)


---

## 💻 Installation

### Requirements

Before building the project, make sure you have:

- **CMake** (version 4.1 or later)
- A **C++20-compatible compiler**
  - **Windows:** MSVC (Visual Studio) or MinGW (`g++`)
  - **macOS:** Apple Clang (included with Xcode Command Line Tools) or `clang++`
  - **Linux:** `g++` or `clang++`

### 1. Clone the repository

```bash
git clone https://github.com/T0485902Vladyslav/depths-of-kaeldrath.git
cd depths-of-kaeldrath
```

### 2. Create a build directory

```bash
mkdir build
cd build
```

### 3. Generate the build files

```bash
cmake ..
```

### 4. Build the project

```bash
cmake --build .
```

### 5. Run the game

#### Linux / macOS

```bash
./depths-of-kaeldrath
```

#### Windows

```powershell
.\depths-of-kaeldrath.exe
```

> **Note:** Depending on your compiler or IDE, the executable may be placed inside a `Debug` or `Release` folder.

---

## 🗂️ Project Structure

| Component         | Responsibility                                                                                                 |
| ----------------- | -------------------------------------------------------------------------------------------------------------- |
| `GameManager`     | Owns the list of scenes and the player, runs the main menu and the game loop, tracks the current scene         |
| `Scene`           | Base class for all scene types — holds the description, both choices/consequences, and presents the A/B prompt |
| `CombatScene`     | Turn-based battles against an `Enemy`, including escape attempts and loot drops                                |
| `PuzzleScene`     | Question-and-answer puzzles that reward or punish the player based on their answer                             |
| `ItemScene`       | Awards the player one of two possible items depending on their choice                                          |
| `LockedDoorScene` | Gates a path behind a required key, with a fallback route if the player doesn't have it                        |
| `Player`          | Tracks health, lives, score, equipped weapon/armour and inventory; handles damage, healing and equipping       |
| `Item`            | Represents weapons, armour, food and keys, including durability and effect values                              |
| `Enemy`           | Stores an enemy's combat stats, score reward and optional item drop                                            |
| `SaveManager`     | Reads and writes the player's full state to and from a save file                                               |

---

*Developed in C++ as a text-based dungeon adventure featuring branching scenes, turn-based combat, puzzles, locked-door progression, an inventory/equipment system, and persistent save functionality.*
