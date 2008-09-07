/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2003-02-17
 * Description : a kipi plugin to slide images.
 *
 * Copyright (C) 2006-2008 by Valerio Fuoglio <valerio dot fuoglio at gmail dot com>
 * Copyright (C) 2003-2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
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

#ifndef SLIDESHOWCONFIG_H
#define SLIDESHOWCONFIG_H

// Qt includes.

#include <Q3ListBox>
#include <QString>
#include <QPixmap>

// KDE includes

#include <kconfig.h>
#include <kio/previewjob.h>
#include <kurl.h>

// libkipi includes

#include <libkipi/interface.h>

// Local includes

#include "ui_slideshowconfigbase.h"

namespace KIPISlideShowPlugin
{

class SlideShowConfig : public QDialog, Ui::SlideShowConfigBase
{
    Q_OBJECT

public:

    SlideShowConfig(bool allowSelectedOnly, KIPI::Interface* interface,
                    QWidget *parent, const char* name, bool ImagesHasComments,
                    KUrl::List* urlList);
    ~SlideShowConfig();

private slots:

    void slotStartClicked();
    void slotHelp();
    void slotOpenGLToggled();
    void slotEffectChanged();
    void slotDelayChanged();
    void slotUseMillisecondsToggled();
    void slotPrintCommentsToggled();
    void slotCommentsFontColorChanged();
    void slotCommentsBgColorChanged();
    void slotTransparentBgToggled();

    void slotSelection();
    void slotCacheToggled();

    void SlotPortfolioDurationChanged ( int );
    void slotImagesFilesSelected( Q3ListBoxItem *item );
    void slotAddDropItems(KUrl::List filesUrl);
    void slotImagesFilesButtonAdd( void );
    void slotImagesFilesButtonDelete( void );
    void slotImagesFilesButtonUp( void );
    void slotImagesFilesButtonDown( void );
    void slotGotPreview(const KFileItem& , const QPixmap &pixmap);
    void slotFailedPreview(const KFileItem&);

signals:

    void buttonStartClicked(); // Signal needed by plugin_slideshow class

private:

    void loadEffectNames();
    void loadEffectNamesGL();
    void readSettings();
    void saveSettings();

    void ShowNumberImages( int Number );
    void addItems(const KUrl::List& fileList);

private:

    int              m_delayMsMaxValue;
    int              m_delayMsMinValue;
    int              m_delayMsLineStep;

    uint             m_cacheSize;

    KConfig*         m_config;

    QString          m_effectName;
    QString          m_effectNameGL;

    KIO::PreviewJob* m_thumbJob;
    KUrl::List*      m_urlList;

    KIPI::Interface* m_interface;
};

}  // NameSpace KIPISlideShowPlugin

#endif // SLIDESHOWCONFIG_H
