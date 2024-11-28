#include "download.h"
using namespace std;

Download::Download(Player *player) : Ability{player} {}

bool Download::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    bool isVirus = link->getIsVirus();
    link->setDownloaded();
    isVirus ? player->incDownloadedViruses() : player->incDownloadedData();
}

string Download::getName() const { return "Download"; }
