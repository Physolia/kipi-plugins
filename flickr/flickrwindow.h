/* ============================================================
 *
 * This file is a part of KDE project
 *
 *
 * Date        : 2005-17-06
 * Description : a kipi plugin to export images to Flickr web service
 *
 * Copyright (C) 2005-2008 by Vardhman Jain <vardhman at gmail dot com>
 * Copyright (C) 2008-2018 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef FLICKRWINDOW_H
#define FLICKRWINDOW_H

// Qt includes

#include <QHash>
#include <QList>
#include <QPair>
#include <QLabel>
#include <QLinkedList>
#include <QLineEdit>
#include <QUrl>
#include <QComboBox>

// Libkipi includes

#include <KIPI/Interface>

// Local includes

#include "kptooldialog.h"
#include "comboboxintermediate.h"

class QProgressDialog;
class QPushButton;
class QSpinBox;
class QCheckBox;
class QUrl;

namespace KIPI
{
    class Interface;
}

namespace KIPIPlugins
{
    class KPAboutData;
}

using namespace KIPI;
using namespace KIPIPlugins;

namespace KIPIFlickrPlugin
{
class SelectUserDlg;
class FlickrWidget;
class FlickrTalker;
class FlickrList;
class FPhotoInfo;
class GPhoto;
class GAlbum;
class NewAlbum;

using namespace KIPI;
using namespace KIPIPlugins;

class FlickrWindow : public KPToolDialog
{
    Q_OBJECT

public:

    FlickrWindow(QWidget* const parent, const QString& serviceName, SelectUserDlg* const dlg);
    ~FlickrWindow();

    /**
     * Use this method to (re-)activate the dialog after it has been created
     * to display it. This also loads the currently selected images.
     */
    void reactivate();

private Q_SLOTS:

    void slotLinkingSucceeded();
    void slotBusy(bool val);
    void slotError(const QString& msg);
    void slotFinished();
    void slotUser1();
    void slotCancelClicked();

    void slotCreateNewPhotoSet();
    void slotUserChangeRequest();
    void slotRemoveAccount();
    void slotPopulatePhotoSetComboBox();
    void slotAddPhotoNext();
    void slotAddPhotoSucceeded();
    void slotAddPhotoFailed(const QString& msg);
    void slotAddPhotoSetSucceeded();
    void slotListPhotoSetsFailed(const QString& msg);
    void slotAddPhotoCancelAndClose();
    void slotAuthCancel();
    void slotImageListChanged();
    void slotReloadPhotoSetRequest();

private:

    QString guessSensibleSetName(const QList<QUrl>& urlList);

    void closeEvent(QCloseEvent*)  override;
    void readSettings(QString uname);
    void writeSettings();

    void setUiInProgressState(bool inProgress);

private:

    unsigned int                           m_uploadCount;
    unsigned int                           m_uploadTotal;

    QString                                m_serviceName;

    QPushButton*                           m_newAlbumBtn;
    QPushButton*                           m_changeUserButton;
    QPushButton*                           m_removeAccount;

    QComboBox*                             m_albumsListComboBox;
    QCheckBox*                             m_publicCheckBox;
    QCheckBox*                             m_familyCheckBox;
    QCheckBox*                             m_friendsCheckBox;
    QCheckBox*                             m_exportHostTagsCheckBox;
    QCheckBox*                             m_stripSpaceTagsCheckBox;
    QCheckBox*                             m_addExtraTagsCheckBox;
    QCheckBox*                             m_originalCheckBox;
    QCheckBox*                             m_resizeCheckBox;

    QSpinBox*                              m_dimensionSpinBox;
    QSpinBox*                              m_imageQualitySpinBox;

    QPushButton*                           m_extendedPublicationButton;
    QPushButton*                           m_extendedTagsButton;
    ComboBoxIntermediate*                  m_contentTypeComboBox;
    ComboBoxIntermediate*                  m_safetyLevelComboBox;

    QString                                m_username;
    QString                                m_userId;
    QString                                m_lastSelectedAlbum;

    QLabel*                                m_userNameDisplayLabel;

    QProgressDialog*                       m_authProgressDlg;

    QList< QPair<QUrl, FPhotoInfo> >       m_uploadQueue;

    QLineEdit*                             m_tagsLineEdit;

    FlickrWidget*                          m_widget;
    FlickrTalker*                          m_talker;

    FlickrList*                            m_imglst;
    SelectUserDlg*                         m_select;
    NewAlbum*                              m_albumDlg;
};

} // namespace KIPIFlickrPlugin

#endif /* FLICKRWINDOW_H */
