/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2008-12-26
 * Description : a kipi plugin to import/export images to Facebook web service
 *
 * Copyright (C) 2008-2009 by Luka Renko <lure at kubuntu dot org>
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

#include "fbwidget.h"

// Qt includes

#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QApplication>
#include <QStyle>

// KDE includes

#include <klocalizedstring.h>
#include <KGuiItem>

// Libkipi includes

#include <KIPI/Interface>
#include <KIPI/UploadWidget>
#include <KIPI/ImageCollection>

// Local includes

#include "kpimageslist.h"
#include "kpprogresswidget.h"

namespace KIPIFacebookPlugin
{

FbWidget::FbWidget(QWidget* const parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("FbWidget"));

    QHBoxLayout* const mainLayout = new QHBoxLayout(this);

    // -------------------------------------------------------------------

    m_imgList = new KIPIPlugins::KPImagesList(this);
    m_imgList->setControlButtonsPlacement(KIPIPlugins::KPImagesList::ControlButtonsBelow);
    m_imgList->setAllowRAW(true);
    m_imgList->loadImagesFromCurrentSelection();
    m_imgList->listView()->setWhatsThis(i18n("This is the list of images to upload to your Facebook account."));

    QWidget* const settingsBox           = new QWidget(this);
    QVBoxLayout* const settingsBoxLayout = new QVBoxLayout(settingsBox);

    m_headerLbl = new QLabel(settingsBox);
    m_headerLbl->setWhatsThis(i18n("This is a clickable link to open the Facebook home page in a web browser."));
    m_headerLbl->setOpenExternalLinks(true);
    m_headerLbl->setFocusPolicy(Qt::NoFocus);

    // ------------------------------------------------------------------------

    QGroupBox* const accountBox         = new QGroupBox(i18n("Account"), settingsBox);
    accountBox->setWhatsThis(i18n("This is the Facebook account that is currently logged in."));
    QGridLayout* const accountBoxLayout = new QGridLayout(accountBox);

    QLabel* const userNameLbl   = new QLabel(i18nc("facebook account settings", "Name:"), accountBox);
    m_userNameDisplayLbl        = new QLabel(accountBox);
    QLabel* const permissionLbl = new QLabel(i18n("Permission:"), accountBox);
    permissionLbl->setWhatsThis(i18n("Permission of KIPI Plugin application to upload photos directly. "
                                     "If not, user will need to manually approve uploaded photos in Facebook."));
    m_permissionLbl         = new QLabel(accountBox);
    m_changeUserBtn         = new QPushButton(accountBox);
    KGuiItem::assign(m_changeUserBtn,
                     KGuiItem(i18n("Change Account"), QStringLiteral("system-switch-user"),
                              i18n("Logout and change Facebook Account used for transfer")));

    accountBoxLayout->addWidget(userNameLbl,            0, 0, 1, 2);
    accountBoxLayout->addWidget(m_userNameDisplayLbl,   0, 2, 1, 2);
    accountBoxLayout->addWidget(permissionLbl,          1, 0, 1, 2);
    accountBoxLayout->addWidget(m_permissionLbl,        1, 2, 1, 2);
    accountBoxLayout->addWidget(m_changeUserBtn,        2, 0, 1, 2);
    accountBoxLayout->setSpacing(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));
    accountBoxLayout->setMargin(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));

    // ------------------------------------------------------------------------

    QGroupBox* const albBox    = new QGroupBox(settingsBox);


    albBox->setTitle(i18n("Destination"));
    albBox->setWhatsThis(i18n("This is the Facebook album to which selected photos will be uploaded."));
        
    QGridLayout* const albumsBoxLayout  = new QGridLayout(albBox);

    QLabel* const albLbl = new QLabel(i18n("Album:"), albBox);
    m_albumsCoB          = new QComboBox(albBox);
    m_albumsCoB->setEditable(false);

    m_newAlbumBtn     = new QPushButton(accountBox);
    KGuiItem::assign(m_newAlbumBtn, KGuiItem(i18n("New Album"), QStringLiteral("list-add"),
                                             i18n("Create new Facebook album")));

    m_reloadAlbumsBtn = new QPushButton(accountBox);
    KGuiItem::assign(m_reloadAlbumsBtn,
                     KGuiItem(i18nc("facebook album list", "Reload"), QStringLiteral("view-refresh"),
                              i18n("Reload album list")));

    albumsBoxLayout->addWidget(albLbl,              0, 0, 1, 1);
    albumsBoxLayout->addWidget(m_albumsCoB,         0, 1, 1, 4);
    albumsBoxLayout->addWidget(m_newAlbumBtn,       1, 3, 1, 1);
    albumsBoxLayout->addWidget(m_reloadAlbumsBtn,   1, 4, 1, 1);

    // ------------------------------------------------------------------------

    QGroupBox* const optionsBox         = new QGroupBox(i18n("Options"), settingsBox);
    optionsBox->setWhatsThis(i18n("These are options that will be applied to photos before upload."));
    QGridLayout* const optionsBoxLayout = new QGridLayout(optionsBox);

    m_resizeChB     = new QCheckBox(optionsBox);
    m_resizeChB->setText(i18n("Resize photos before uploading"));
    m_resizeChB->setChecked(false);

    m_dimensionSpB  = new QSpinBox(optionsBox);
    m_dimensionSpB->setMinimum(0);
    m_dimensionSpB->setMaximum(5000);
    m_dimensionSpB->setSingleStep(10);
    m_dimensionSpB->setValue(600);
    m_dimensionSpB->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_dimensionSpB->setEnabled(false);
    QLabel* const dimensionLbl = new QLabel(i18n("Maximum dimension:"), optionsBox);

    m_imageQualitySpB = new QSpinBox(optionsBox);
    m_imageQualitySpB->setMinimum(0);
    m_imageQualitySpB->setMaximum(100);
    m_imageQualitySpB->setSingleStep(1);
    m_imageQualitySpB->setValue(85);
    m_imageQualitySpB->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QLabel* const imageQualityLbl = new QLabel(i18n("JPEG quality:"), optionsBox);

    optionsBoxLayout->addWidget(m_resizeChB,        0, 0, 1, 5);
    optionsBoxLayout->addWidget(imageQualityLbl,    1, 1, 1, 1);
    optionsBoxLayout->addWidget(m_imageQualitySpB,  1, 2, 1, 1);
    optionsBoxLayout->addWidget(dimensionLbl,       2, 1, 1, 1);
    optionsBoxLayout->addWidget(m_dimensionSpB,     2, 2, 1, 1);
    optionsBoxLayout->setRowStretch(3, 10);
    optionsBoxLayout->setSpacing(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));
    optionsBoxLayout->setMargin(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));

    m_progressBar = new KIPIPlugins::KPProgressWidget(settingsBox);
    m_progressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_progressBar->hide();

    // ------------------------------------------------------------------------

    settingsBoxLayout->addWidget(m_headerLbl);
    settingsBoxLayout->addWidget(accountBox);
    settingsBoxLayout->addWidget(albBox);
//     settingsBoxLayout->addWidget(uploadBox);
    settingsBoxLayout->addWidget(optionsBox);
    settingsBoxLayout->addWidget(m_progressBar);
    settingsBoxLayout->setSpacing(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));
    settingsBoxLayout->setMargin(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));

    // ------------------------------------------------------------------------

    mainLayout->addWidget(m_imgList);
    mainLayout->addWidget(settingsBox);
    mainLayout->setSpacing(QApplication::style()->pixelMetric(QStyle::PM_DefaultLayoutSpacing));
    mainLayout->setMargin(0);

    updateLabels();  // use empty labels until login

    // ------------------------------------------------------------------------

    connect(m_reloadAlbumsBtn, SIGNAL(clicked()),
            this, SLOT(slotReloadAlbumsRequest()));

    connect(m_resizeChB, SIGNAL(clicked()),
            this, SLOT(slotResizeChecked()));

    // ------------------------------------------------------------------------
}

FbWidget::~FbWidget()
{
}

KIPIPlugins::KPImagesList* FbWidget::imagesList() const
{
    return m_imgList;
}

KIPIPlugins::KPProgressWidget* FbWidget::progressBar() const
{
    return m_progressBar;
}

QString FbWidget::getDestinationPath() const
{
    return m_uploadWidget->selectedImageCollection().uploadUrl().toLocalFile();
}

void FbWidget::updateLabels(const QString& name, const QString& url, bool uplPerm)
{
    QString web(QStringLiteral("http://www.facebook.com"));

    if (!url.isEmpty())
        web = url;

    m_headerLbl->setText(QStringLiteral(
        "<b><h2><a href='%1'>"
        "<font color=\"#3B5998\">facebook</font>"
        "</a></h2></b>").arg(web));
    if (name.isEmpty())
    {
        m_userNameDisplayLbl->clear();
        m_permissionLbl->clear();
    }
    else
    {
        m_userNameDisplayLbl->setText(QStringLiteral("<b>%1</b>").arg(name));

        if (uplPerm)
        {
            m_permissionLbl->setText(i18n("Direct upload"));
            m_permissionLbl->setWhatsThis(
                i18n("Uploaded photos will not need manual approval by user."));
        }
        else
        {
            m_permissionLbl->setText(i18n("Manual upload approval"));
            m_permissionLbl->setWhatsThis(i18n("Uploaded photos will wait in pending state until manually approved by user."));
        }
    }
}

void FbWidget::slotReloadAlbumsRequest()
{

    emit reloadAlbums(0);
}

void FbWidget::slotResizeChecked()
{
    m_dimensionSpB->setEnabled(m_resizeChB->isChecked());
    m_imageQualitySpB->setEnabled(m_resizeChB->isChecked());
}

QString FbWidget::getAlbumID() const
{
    return m_albumsCoB->itemData(m_albumsCoB->currentIndex()).toString();
}

} // namespace KIPIFacebookPlugin
