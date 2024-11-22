#include "download.h"
using namespace std;

void Download::use(Cell* c1, Cell* c2) {
    Link *link = c1->getLink();
    bool isVirus = link->isVirus();
    ln->setDownloaded(true);
    Player* player = link->getOwner();

    oldData = player->getDownloadedData();
    oldViruses = player->getDownloadedViruses();
    isVirus ? player->setDownloadedViruses(oldViruses + 1) : player->setDownloadedData(oldData + 1)
}

string Download::getName() const { return "Download"; }
