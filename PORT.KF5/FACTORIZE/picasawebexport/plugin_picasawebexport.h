/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2007-17-07
 * Description : a kipi plugin to export images to Picasa web service
 *
 * Copyright (C) 2007-2008 by Vardhman Jain <vardhman at gmail dot com>
 * Copyright (C) 2008-2015 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef PLUGIN_PICASAWEBEXPORT_H
#define PLUGIN_PICASAWEBEXPORT_H

// Libkipi includes

#include <plugin.h>

// Local includes

#include "picasawebwindow.h"

class QAction;

using namespace KIPI;

namespace KIPIPicasawebExportPlugin
{

class Plugin_PicasawebExport : public Plugin
{
    Q_OBJECT

public:

    Plugin_PicasawebExport(QObject* const parent, const QVariantList& args);
    ~Plugin_PicasawebExport();

    void setup(QWidget* const);

public Q_SLOTS:

    void slotExport();
    void slotImport();

private:

    void setupActions();

private:

    QAction *         m_actionExport;
    QAction *         m_actionImport;

    PicasawebWindow* m_dlgExport;
    PicasawebWindow* m_dlgImport;
};

} // namespace KIPIPicasawebExportPlugin

#endif // PLUGIN_PICASAWEBEXPORT_H
