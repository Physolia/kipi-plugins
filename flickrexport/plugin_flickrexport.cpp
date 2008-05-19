/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2005-17-06
 * Description : a kipi plugin to export images to Flickr web service
 *
 * Copyright (C) 2005-2008 by Vardhman Jain <vardhman at gmail dot com>
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

extern "C"
{
#include <unistd.h>
}
	
// KDE includes.

#include <klocale.h>
#include <kaction.h>
#include <kgenericfactory.h>
#include <klibloader.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kapplication.h>
#include <kstandarddirs.h>

// libkipi includes.

#include <libkipi/interface.h>

// Local includes.

#include "flickrwindow.h"
#include "plugin_flickrexport.h"
#include "plugin_flickrexport.moc"

typedef KGenericFactory<Plugin_FlickrExport> Factory;

K_EXPORT_COMPONENT_FACTORY(kipiplugin_flickrexport, Factory("kipiplugin_flickrexport"))

Plugin_FlickrExport::Plugin_FlickrExport(QObject *parent, const char*, const QStringList&)
                   : KIPI::Plugin(Factory::instance(), parent, "FlickrExport")
{
    kdDebug(51001) << "Plugin_FlickrExport plugin loaded" << endl;
}

void Plugin_FlickrExport::setup(QWidget* widget)
{
    KIPI::Plugin::setup(widget);
    
    m_action = new KAction(i18n("Export to Flickr..."),
                           0,
                           this,
                           SLOT(slotActivate()),
                           actionCollection(),
                           "flickrexport");

    KIPI::Interface* interface = dynamic_cast<KIPI::Interface*>(parent());
    
    if (!interface) 
    {
        kdError( 51000 ) << "Kipi interface is null!" << endl;
        m_action->setEnabled(false);
        return;
    }

    m_action->setEnabled(true);
    addAction(m_action);
}

Plugin_FlickrExport::~Plugin_FlickrExport()
{
}

void Plugin_FlickrExport::slotActivate()
{
    KIPI::Interface* interface = dynamic_cast<KIPI::Interface*>(parent());
    if (!interface) 
    {
        kdError( 51000 ) << "Kipi interface is null!" << endl;
        return;
    }
	KStandardDirs dir;
	QString Tmp = dir.saveLocation("tmp", "kipi-flickrexportplugin-" + QString::number(getpid()) + "/");

    //We clean it up in the close button
    dlg = new KIPIFlickrExportPlugin::FlickrWindow(interface,Tmp,kapp->activeWindow());
    dlg->show();
}

KIPI::Category Plugin_FlickrExport::category( KAction* action ) const
{
    if (action == m_action)
        return KIPI::EXPORTPLUGIN;
    
    kdWarning(51000) << "Unrecognized action for plugin category identification" << endl;
    return KIPI::EXPORTPLUGIN;
}
