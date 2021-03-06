/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "consoleprocess.h"
#include "environment.h"

#include <QTemporaryFile>

#include <QLocalSocket>
#include <QLocalServer>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

#ifdef Q_OS_WIN
#  include <QWinEventNotifier>
#  include <windows.h>
#endif

namespace Utils {

struct ConsoleProcessPrivate {
    ConsoleProcessPrivate();

    static QString m_defaultConsoleProcess;
    ConsoleProcess::Mode m_mode = ConsoleProcess::Run;
    QString m_workingDir;
    Environment m_environment;
    qint64 m_appPid = 0;
    int m_appCode;
    CommandLine m_commandLine;
    QProcess::ExitStatus m_appStatus;
    QLocalServer m_stubServer;
    QLocalSocket *m_stubSocket = nullptr;
    QTemporaryFile *m_tempFile = nullptr;
    QProcess::ProcessError m_error = QProcess::UnknownError;
    QString m_errorString;

#ifdef Q_OS_UNIX
    QProcess m_process;
    QByteArray m_stubServerDir;
    QSettings *m_settings = nullptr;
    bool m_stubConnected = false;
    qint64 m_stubPid = 0;
    QTimer *m_stubConnectTimer = nullptr;
#else
    qint64 m_appMainThreadId = 0;
    PROCESS_INFORMATION *m_pid = nullptr;
    HANDLE m_hInferior = NULL;
    QWinEventNotifier *inferiorFinishedNotifier = nullptr;
    QWinEventNotifier *processFinishedNotifier = nullptr;
#endif
};

} //namespace Utils
