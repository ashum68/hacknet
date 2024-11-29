#ifndef CELL_H
#define CELL_H

class Link;

class Cell {
    Link* link;
    int row, col, serverPort;
    bool firewallOn1, firewallOn2;;
    bool isBlocked;

public:
    Cell(Link* link, int row, int col);
    
    bool canOccupy(Link* incomingLink) const;
    void setLink(Link* newLink);
    Link* getLink() const;
    void emptyCell();
    
    int getRow() const;
    int getCol() const;
    bool isCellBlocked() const;
    void setBlocked(bool blocked);
    bool isFirewallOn1() const;
    bool isFirewallOn2() const;
    void setFirewall1();
    void setFirewall2();
    int getServerPort() const; // int for player 1 vs 2
    void setServerPort(int status);
};

#endif
