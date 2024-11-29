#include "download.h"
#include "player.h"

Download::Download(Player* player) : Ability{player} {}

bool Download::use(Cell* cell) {
    if (!cell || !cell->getLink()) return false;
    
    Link* targetLink = cell->getLink();
    bool isVirus = targetLink->getIsVirus();
    
    if (isVirus) {
        player->incDownloadedViruses();
    } else {
        player->incDownloadedData();
    }
    targetLink->setDownloaded();
    
    return true;
}

string Download::getName() const { return "Download"; }
