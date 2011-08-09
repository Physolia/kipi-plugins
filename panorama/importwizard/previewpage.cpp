/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2011-05-23
 * Description : a plugin to create panorama by fusion of several images.
 *
 * Copyright (C) 2011 by Benjamin Girault <benjamin dot girault at gmail dot com>
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

#include "previewpage.moc"

// Qt includes

#include <QLabel>

// KDE includes

#include <kstandarddirs.h>
#include <kapplication.h>
#include <kvbox.h>
#include <klocale.h>
#include <kdialog.h>
#include <kdebug.h>

// Local includes

#include "outputdialog.h"
#include "manager.h"
#include "previewmanager.h"

namespace KIPIPanoramaPlugin
{

struct PreviewPage::PreviewPagePriv
{
    PreviewPagePriv(Manager *m)
        : title(0), previewWidget(0), mngr(m)
    {}

    QLabel*         title;
    QUrl            previewUrl;
    PreviewManager* previewWidget;

    QString         output;

    Manager*        mngr;
};

PreviewPage::PreviewPage(Manager* mngr, KAssistantDialog* dlg)
        : KIPIPlugins::WizardPage(dlg, i18n("Preview")),
          d(new PreviewPagePriv(mngr))
{
    KVBox *vbox   = new KVBox(this);
    d->title = new QLabel(i18n("<qt><p>Panorama Preview</p></qt>"), vbox);
    d->title->setOpenExternalLinks(true);
    d->title->setWordWrap(true);

    d->previewWidget  = new PreviewManager(vbox);
    d->previewWidget->setButtonText(i18n("Details..."));
    d->previewWidget->show();

    vbox->setSpacing(KDialog::spacingHint());
    vbox->setMargin(KDialog::spacingHint());

    setPageWidget(vbox);

    //QPixmap leftPix = KStandardDirs::locate("data", "kipiplugin_panorama/pics/assistant-xxx.png");
    //setLeftBottomPix(leftPix.scaledToWidth(128, Qt::SmoothTransformation));

    connect(d->mngr->thread(), SIGNAL(starting(KIPIPanoramaPlugin::ActionData)),
            this, SLOT(slotAction(KIPIPanoramaPlugin::ActionData)));
}

PreviewPage::~PreviewPage()
{
    delete d;
}

void PreviewPage::slotAction(const KIPIPanoramaPlugin::ActionData& ad)
{
    QString text;

    if (!ad.starting)           // Something is complete...
    {
        if (!ad.success)        // Something is failed...
        {
            switch (ad.action)
            {
                case(PREVIEW):
                {
                    d->previewWidget->setBusy(true, i18n("Processing Panorama Preview..."));
                    d->output = ad.message;
                    emit signalPreviewGenerated(KUrl());
                    break;
                }
                default:
                {
                    kWarning() << "Unknown action";
                    break;
                }
            }
        }
        else                    // Something is done...
        {
            switch (ad.action)
            {
                case(PREVIEW):
                {
                    d->previewUrl = ad.outUrl;
                    d->mngr->setPreviewUrl(ad.outUrl);
                    qDebug() << "Preview URL: " << ad.outUrl.toLocalFile();

                    QImage image(ad.outUrl.toLocalFile());
                    d->previewWidget->setBusy(false);
                    d->previewWidget->setImage(image, true);

                    emit signalPreviewGenerated(ad.outUrl);
                    break;
                }
                default:
                {
                    kWarning() << "Unknown action";
                    break;
                }
            }
        }
    }
}

void PreviewPage::computePreview()
{
    connect(d->mngr->thread(), SIGNAL(finished(KIPIPanoramaPlugin::ActionData)),
            this, SLOT(slotAction(KIPIPanoramaPlugin::ActionData)));

    emit signalPreviewGenerating();
    d->mngr->thread()->generatePanoramaPreview(d->mngr->autoOptimiseUrl(), d->mngr->preProcessedMap());
}

}   // namespace KIPIPanoramaPlugin
