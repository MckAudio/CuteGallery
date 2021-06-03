#include "imagegallerymodel.h"

#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>

ImageGalleryModel::ImageGalleryModel(QObject *parent)
    : QStandardItemModel(parent)
{
    watcher = new QFileSystemWatcher(this);
    connect(watcher, &QFileSystemWatcher::directoryChanged,
            this, &ImageGalleryModel::onDirectoryChanged);
}

QHash<int, QByteArray> ImageGalleryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PathRole] = "path";
    return roles;
}

void ImageGalleryModel::setRootPath(const QString &p)
{
    this->clear();

    if (path != "")
    {
        watcher->removePath(path);
    }
    path = p;
    watcher->addPath(path);
    onDirectoryChanged(path);
}

void ImageGalleryModel::onDirectoryChanged(const QString &p)
{
    QStringList nameFilters;
    nameFilters << "*.png" << "*.jpg";
    QDir directory(p);
    directory.setNameFilters(nameFilters);
    QStringList files = directory.entryList();

    QHash<QString, int> fileIndexes;

    for (int i = 0; i < rowCount(); i++)
    {
        QString absolutePath = data(index(i, 0), PathRole).toString();
        QString name = directory.relativeFilePath(absolutePath);
        if (files.contains(name) == false)
        {
            removeRow(i);
            i--;
            continue;
        }
        fileIndexes[absolutePath] = i;
    }

    for(auto &file : files)
    {
        QString absolutePath = directory.absoluteFilePath(file);
        if (fileIndexes.contains(absolutePath) == false)
        {
            QStandardItem *item = new QStandardItem();
            item->setData(absolutePath, PathRole);
            appendRow(item);
        }
    }
}
