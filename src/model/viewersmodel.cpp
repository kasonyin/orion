#include "viewersmodel.h"

ViewersModel *ViewersModel::instance = 0;

ViewersModel::ViewersModel(QObject *parent) : QObject(parent), netman(NetworkManager::getInstance())
{
    connect(netman, &NetworkManager::chatterListLoadOperationFinished, this, &ViewersModel::processChatterList);
}

void ViewersModel::processChatterList(QMap<QString, QList<QString>> chatters)
{
    QVariantMap out;
    for (auto groupEntry = chatters.constBegin(); groupEntry != chatters.constEnd(); groupEntry++) {
        QVariantList group;
        for (const auto & chatter : groupEntry.value()) {
            group.append(chatter);
        }
        out.insert(groupEntry.key(), group);
    }

    emit chatterListLoaded(out);
}

void ViewersModel::loadChatterList(const QString channel) {
    netman->loadChatterList(channel);
}
