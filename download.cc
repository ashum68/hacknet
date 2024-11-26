#include "download.h"
using namespace std;

void Download::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    bool isVirus = link->isVirus();
    ln->setDownloaded();
    Player* player = link->getOwner();

    oldData = player->getDownloadedData();
    oldViruses = player->getDownloadedViruses();
    isVirus ? player->setDownloadedViruses(oldViruses + 1) : player->setDownloadedData(oldData + 1)
}

string Download::getName() const { return "Download"; }
