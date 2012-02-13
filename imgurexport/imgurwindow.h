/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2012-02-12
 * Description : a kipi plugin to export images to the Imgur web service
 *
 * Copyright (C) 2012-2012 by Marius Orcsik <marius at habarnam dot ro>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef IMGURWINDOW_H
#define IMGURWINDOW_H

// Qt
#include <QObject>

// KDE
#include <KDialog>
#include <KLocale>

// KIPI
#include "libkipi/interface.h"
#include "imageslist.h"
#include "imgurtalker.h"

namespace KIPIPlugins {
class ImagesList;
}

namespace KIPI
{
class Interface;
}

namespace KIPIImgurExportPlugin
{
class ImgurWindow : public KDialog
{
    Q_OBJECT

public:
    ImgurWindow(KIPI::Interface* interface, QWidget* parent = 0);
    ~ImgurWindow();

    KIPIPlugins::ImagesList* imagesList();
    void reactivate();

private:
    KIPIPlugins::ImagesList* m_imagesList;
    ImgurTalker* m_webServiceTalker;
};
} // namespace KIPIImgurExportPlugin
#endif /* IMGURWINDOW_H */
