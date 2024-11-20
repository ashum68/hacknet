# RAIInet UML Analysis and Improvements

## Current UML Review
The current UML shows basic class relationships but is missing several crucial components needed to implement the full game functionality.

## Missing Classes
1. `CommandInterpreter`
   - Responsible for parsing and executing commands
   - Methods: `parseCommand()`, `executeCommand()`
   - Relationships: Aggregation with `Game`

2. `Square`
   - Represents a board position
   - Attributes: `row`, `col`, `occupant` (Link*)
   - Methods: `isEmpty()`, `getOccupant()`, `setOccupant()`

3. `ServerPort` (extends Square)
   - Special square type for server ports
   - Methods: `downloadLink()`

## Class Improvement

### Game Class
Add:
- `currentPlayer: Player*`
- `board: Board*`
- `isGameOver(): bool`
- `switchTurn()`
- `processMove(Link*, Direction)`
- `processAbility(int abilityId, vector<int> params)`
- `loadGame(string config)`

### Board Class
Add:
- `grid: vector<vector<Square*>>`
- `size: const int`
- `placeLink(Link*, int row, int col)`
- `moveLink(Link*, Direction)`
- `isValidMove(Link*, Direction): bool`
- `battle(Link*, Link*)`
- `checkWinCondition(): bool`
- `getSquare(int row, int col): Square*`

### Player Class
Add:
- `name: string`
- `downloadedData: int`
- `downloadedViruses: int`
- `abilities: vector<Ability*>`
- `links: vector<Link*>`
- `useAbility(int id, vector<int> params)`
- `downloadLink(Link*)`
- `hasLost(): bool`
- `hasWon(): bool`

### Link Class
Add:
- `strength: int`
- `owner: Player*`
- `position: Square*`
- `isRevealed: bool`
- `getStrength(): int`
- `battle(Link*): bool`
- `reveal()`
- `move(Direction)`

### Observer Pattern Improvements
- Add `Subject` interface
- Add concrete update methods in observers
- Add specific notification methods for different game events

### Ability Classes
Common interface:
```cpp
class Ability {
    virtual bool canUse() const = 0;
    virtual void use(vector<int> params) = 0;
    virtual string getName() const = 0;
    virtual bool isUsed() const = 0;
protected:
    bool used = false;
    Player* owner;
};
```

## New Relationships
1. Board aggregates Squares
2. Square has optional association with Link
3. Player owns Links and Abilities
4. CommandInterpreter has association with Game
5. ServerPort inherits from Square

## Design Pattern Additions
1. **Factory Pattern** for creating Links and Abilities
2. **Command Pattern** for command interpretation
3. **State Pattern** for game state management
4. **Strategy Pattern** for different ability behaviors

## Additional Considerations
1. Exception handling classes for invalid moves/commands
2. Interface for saving/loading game state
3. Support for custom ability types
4. Support for the suggested 4-player variant

## Implementation Notes
1. All pointer members should use smart pointers
2. Virtual destructors for base classes
3. Rule of five implementation where necessary
4. const-correctness throughout
5. Clear separation of interface and implementation


# Detailed Class Specifications

## Square Hierarchy
Square should be an abstract base class with specialized types:

```cpp
class Square {
public:
    virtual ~Square() = default;
    virtual bool canOccupy(const Link* link) const = 0;
    virtual void occupy(Link* link) = 0;
    virtual void vacate() = 0;
    virtual bool isServerPort() const { return false; }
    virtual bool isFirewall() const { return false; }
    
    Position getPosition() const;
    Link* getOccupant() const;
    
protected:
    Position pos;
    Link* occupant;
};

class BasicSquare : public Square {
public:
    bool canOccupy(const Link* link) const override;
    void occupy(Link* link) override;
    void vacate() override;
};

class ServerPort : public Square {
public:
    bool canOccupy(const Link* link) const override;
    void occupy(Link* link) override;  // Triggers download
    void vacate() override;
    bool isServerPort() const override { return true; }
    
    Player* getOwner() const;
private:
    Player* owner;
};

class FirewallSquare : public Square {
public:
    bool canOccupy(const Link* link) const override;
    void occupy(Link* link) override;  // Triggers virus check
    void vacate() override;
    bool isFirewall() const override { return true; }
    
    Player* getOwner() const;
    void expire();  // Remove firewall effect
private:
    Player* owner;
};
```

## Link Class Hierarchy
```cpp
class Link {
public:
    virtual ~Link() = default;
    virtual bool isVirus() const = 0;
    
    // Core functionality
    bool move(Direction dir);
    bool battle(Link* other);
    void reveal();
    void download(Player* player);
    void boost();  // Apply LinkBoost
    
    // Getters
    int getStrength() const;
    Player* getOwner() const;
    Position getPosition() const;
    bool isRevealed() const;
    bool isBoosted() const;
    char getIdentifier() const;
    
protected:
    int strength;
    Player* owner;
    Position pos;
    bool revealed;
    bool boosted;
    char identifier;
};

class Data : public Link {
public:
    bool isVirus() const override { return false; }
    void polarize();  // Convert to Virus
};

class Virus : public Link {
public:
    bool isVirus() const override { return true; }
    void polarize();  // Convert to Data
};
```

## Ability Class Hierarchy
```cpp
class Ability {
public:
    virtual ~Ability() = default;
    virtual bool canUse() const;
    virtual void use(const vector<int>& params) = 0;
    virtual string getName() const = 0;
    virtual char getIdentifier() const = 0;
    virtual string getDescription() const = 0;
    
    bool isUsed() const;
    Player* getOwner() const;
    
protected:
    bool used = false;
    Player* owner;
};

class LinkBoost : public Ability {
public:
    void use(const vector<int>& params) override;
    string getName() const override { return "Link Boost"; }
    char getIdentifier() const override { return 'L'; }
    string getDescription() const override;
    
private:
    void applyBoost(Link* target);
};

class Firewall : public Ability {
public:
    void use(const vector<int>& params) override;
    string getName() const override { return "Firewall"; }
    char getIdentifier() const override { return 'F'; }
    string getDescription() const override;
    
private:
    void placeFirewall(Position pos);
};

class Download : public Ability {
public:
    void use(const vector<int>& params) override;
    string getName() const override { return "Download"; }
    char getIdentifier() const override { return 'D'; }
    string getDescription() const override;
    
private:
    void downloadLink(Link* target);
};

class Polarize : public Ability {
public:
    void use(const vector<int>& params) override;
    string getName() const override { return "Polarize"; }
    char getIdentifier() const override { return 'P'; }
    string getDescription() const override;
    
private:
    void polarizeLink(Link* target);
};

class Scan : public Ability {
public:
    void use(const vector<int>& params) override;
    string getName() const override { return "Scan"; }
    char getIdentifier() const override { return 'S'; }
    string getDescription() const override;
    
private:
    void revealLink(Link* target);
};
```

## Example of New Ability Implementation
Here's how you could implement one of the three required new abilities:

```cpp
class Mirror : public Ability {
public:
    void use(const vector<int>& params) override {
        // Copies the last ability used by the opponent
        auto lastAbility = owner->getOpponent()->getLastUsedAbility();
        if (lastAbility) {
            lastAbility->use(params);
        }
    }
    string getName() const override { return "Mirror"; }
    char getIdentifier() const override { return 'M'; }
    string getDescription() const override {
        return "Copies and uses the opponent's last used ability";
    }
};

class Teleport : public Ability {
public:
    void use(const vector<int>& params) override {
        // Swaps positions of two links owned by the same player
        Link* link1 = board->getLinkAt(Position(params[0], params[1]));
        Link* link2 = board->getLinkAt(Position(params[2], params[3]));
        if (link1 && link2 && link1->getOwner() == link2->getOwner()) {
            Position temp = link1->getPosition();
            link1->setPosition(link2->getPosition());
            link2->setPosition(temp);
        }
    }
    string getName() const override { return "Teleport"; }
    char getIdentifier() const override { return 'T'; }
    string getDescription() const override {
        return "Swap positions of two friendly links";
    }
};

class Shield : public Ability {
public:
    void use(const vector<int>& params) override {
        // Makes target link immune to next battle/ability
        Link* target = board->getLinkAt(Position(params[0], params[1]));
        if (target && target->getOwner() == owner) {
            target->setShielded(true);
        }
    }
    string getName() const override { return "Shield"; }
    char getIdentifier() const override { return 'H'; }
    string getDescription() const override {
        return "Target link is immune to next battle or ability";
    }
};
```

## Key Design Considerations

1. **Square Hierarchy**:
   - Abstract base class with virtual interface
   - Specialized squares inherit and override behavior
   - Enables polymorphic behavior for different square types

2. **Link Properties**:
   - Strength and type are immutable after construction
   - State changes (revealed, boosted) are tracked
   - Battle logic considers both strength and type

3. **Ability System**:
   - Common interface for all abilities
   - Parameter validation in each ability
   - Clear separation of targeting and effect
   - Easy to add new abilities

4. **State Management**:
   - All game state changes go through proper channels
   - Observer pattern notifies of relevant changes
   - Clear ownership and lifecycle management

5. **Error Handling**:
   - Parameter validation in ability use
   - Clear failure conditions
   - Exception safety guarantees