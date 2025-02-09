/* ============================================================
 *
 * This file is a part of KDE project
 * http://www.kipi-plugins.org
 *
 * Date        : 2010-02-04
 * Description : a tool to export images to imgur.com
 *
 * Copyright (C) 2010-2012 by Marius Orcsik <marius at habarnam dot ro>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef PLUGIN_IMGUR_H
#define PLUGIN_IMGUR_H

// Qt includes

#include <QVariant>

// Libkipi includes

#include <KIPI/Plugin>

// Local includes

#include "imgurwindow.h"

using namespace KIPI;

namespace KIPIImgurPlugin
{

class Plugin_Imgur : public Plugin
{
    Q_OBJECT

public:

    explicit Plugin_Imgur(QObject* const parent, const QVariantList& args);
    ~Plugin_Imgur();

    void setup(QWidget* const) override;

public Q_SLOTS:

    void slotActivate();

private:

    void setupActions();

private:

    class Private;
    Private* const d;
};

} // namespace KIPIImgurPlugin

#endif // PLUGIN_IMGUREXPORT_H
