//////////////////////////////////////////////////////////////////////////////
//
//    PLUGIN_BATCHPROCESSIMAGES.CPP
//
//    Copyright (C) 2003-2004 Gilles Caulier <caulier dot gilles at free.fr>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//////////////////////////////////////////////////////////////////////////////

// C Ansi includes

extern "C"
{
#include <unistd.h>
}

// Qt Includes

#include <qimage.h>

// KDE includes

#include <klocale.h>
#include <kapplication.h>
#include <kglobal.h>
#include <kaction.h>
#include <kgenericfactory.h>
#include <klibloader.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kiconloader.h>
#include <kinstance.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>
#include <ktempfile.h>

// KIPI includes

#include <libkipi/interface.h>

// Local includes

#include "plugin_batchprocessimages.h"
#include "borderimagesdialog.h"
#include "colorimagesdialog.h"
#include "convertimagesdialog.h"
#include "effectimagesdialog.h"
#include "filterimagesdialog.h"
#include "renameimagesdialog.h"
#include "recompressimagesdialog.h"
#include "resizeimagesdialog.h"

typedef KGenericFactory<Plugin_BatchProcessImages> Factory;

K_EXPORT_COMPONENT_FACTORY( kipiplugin_batchprocessimages,
                            Factory("kipiplugin_batchprocessimages"));

// -----------------------------------------------------------
Plugin_BatchProcessImages::Plugin_BatchProcessImages(QObject *parent, const char*, const QStringList&)
            : KIPI::Plugin( Factory::instance(), parent, "BatchProcessImages")
{
    kdDebug( 51001 ) << "Plugin_BatchProcessImages plugin loaded" << endl;

}

void Plugin_BatchProcessImages::setup( QWidget* widget )
{
    KIPI::Plugin::setup( widget );

    m_action_borderimages = new KAction (i18n("Border Images..."),           // Menu message.
                                        "borderimages",                      // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_border_images");

    m_action_colorimages = new KAction (i18n("Color Images..."),             // Menu message.
                                        "colorimages",                       // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_color_images");

    m_action_convertimages = new KAction (i18n("Convert Images..."),         // Menu message.
                                        "convertimages",                     // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_convert_images");

    m_action_effectimages = new KAction (i18n("Effect Images..."),           // Menu message.
                                        "effectimages",                      // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_effect_images");

    m_action_filterimages = new KAction (i18n("Filter Images..."),           // Menu message.
                                        "filterimages",                      // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_filter_images");

    m_action_renameimages = new KAction (i18n("Rename Images..."),           // Menu message.
                                        "renameimages",                      // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_rename_images");

    m_action_recompressimages = new KAction (i18n("Recompress Images..."),   // Menu message.
                                        "recompressimages",                  // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_recompress_images");

    m_action_resizeimages = new KAction (i18n("Resize Images..."),           // Menu message.
                                        "resizeimages",                      // Menu icon.
                                        0,                                   // default shortcut.
                                        this,
                                        SLOT(slotActivate()),
                                        actionCollection(),
                                        "batch_resize_images");

    addAction( m_action_borderimages );
    addAction( m_action_colorimages );
    addAction( m_action_convertimages );
    addAction( m_action_effectimages );
    addAction( m_action_filterimages );
    addAction( m_action_renameimages );
    addAction( m_action_recompressimages );
    addAction( m_action_resizeimages );
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

Plugin_BatchProcessImages::~Plugin_BatchProcessImages()
{
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

void Plugin_BatchProcessImages::slotActivate()
{
    KIPI::Interface* interface = static_cast<KIPI::Interface*>( parent() );
    KIPI::ImageCollection images = interface->currentScope();
    if ( !images.isValid() )
        return;

    KURL::List urlList = images.images();

    QString from(sender()->name());

    if (from == "batch_convert_images")
        {
        m_ConvertImagesDialog = new ConvertImagesDialog( urlList, interface);
        m_ConvertImagesDialog->show();
        }
    else if (from == "batch_rename_images")
        {
        m_RenameImagesDialog = new RenameImagesDialog( urlList, interface);
        m_RenameImagesDialog->show();
        }
    else if (from == "batch_border_images")
        {
        m_BorderImagesDialog = new BorderImagesDialog( urlList, interface);
        m_BorderImagesDialog->show();
        }
    else if (from == "batch_color_images")
        {
        m_ColorImagesDialog = new ColorImagesDialog( urlList, interface);
        m_ColorImagesDialog->show();
        }
    else if (from == "batch_filter_images")
        {
        m_FilterImagesDialog = new FilterImagesDialog( urlList, interface);
        m_FilterImagesDialog->show();
        }
    else if (from == "batch_effect_images")
        {
        m_EffectImagesDialog = new EffectImagesDialog( urlList, interface);
        m_EffectImagesDialog->show();
        }
    else if (from == "batch_recompress_images")
        {
        m_RecompressImagesDialog = new RecompressImagesDialog( urlList, interface);
        m_RecompressImagesDialog->show();
        }
    else if (from == "batch_resize_images")
        {
        m_ResizeImagesDialog = new ResizeImagesDialog( urlList, interface);
        m_ResizeImagesDialog->show();
        }
    else
        {
        kdWarning( 51000 ) << "The impossible happened... unknown batch action specified" << endl;
        return;
        }
}

KIPI::Category Plugin_BatchProcessImages::category( KAction* action ) const
{
    if ( action == m_action_borderimages )
       return KIPI::BATCHPLUGIN;
    else if ( action == m_action_colorimages )
       return KIPI::BATCHPLUGIN;
    else if ( action == m_action_convertimages )
       return KIPI::BATCHPLUGIN;       
    else if ( action == m_action_effectimages )
       return KIPI::BATCHPLUGIN;       
    else if ( action == m_action_filterimages )
       return KIPI::BATCHPLUGIN;       
    else if ( action == m_action_renameimages )
       return KIPI::BATCHPLUGIN;       
    else if ( action == m_action_recompressimages )
       return KIPI::BATCHPLUGIN;       
    else if ( action == m_action_resizeimages )
       return KIPI::BATCHPLUGIN;     

    kdWarning( 51000 ) << "Unrecognized action for plugin category identification" << endl;
    return KIPI::BATCHPLUGIN; // no warning from compiler, please
}

#include "plugin_batchprocessimages.moc"
