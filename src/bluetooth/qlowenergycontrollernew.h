/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QLOWENERGYCONTROLLERNEW_H
#define QLOWENERGYCONTROLLERNEW_H

#include <QObject>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothUuid>
#include <QtBluetooth/QLowEnergyService>

QT_BEGIN_NAMESPACE

class QLowEnergyControllerNewPrivate;
class Q_BLUETOOTH_EXPORT QLowEnergyControllerNew : public QObject
{
    Q_OBJECT
public:
    enum Error {
        NoError,
        UnknownError,
        UnknownRemoteDeviceError,
        NetworkError,
        InvalidBluetoothAdapterError
    };

    enum ControllerState {
        UnconnectedState = 0,
        ConnectingState,
        ConnectedState,
        ClosingState,
    };

    explicit QLowEnergyControllerNew(const QBluetoothAddress &remoteDevice,
                                     QObject *parent = 0);
    explicit QLowEnergyControllerNew(const QBluetoothAddress &remoteDevice,
                                     const QBluetoothAddress &localDevice,
                                     QObject *parent = 0);
    ~QLowEnergyControllerNew();

    QBluetoothAddress localAddress() const;
    QBluetoothAddress remoteAddress() const;

    ControllerState state() const;

    void connectToDevice();
    void disconnectFromDevice();

    // TODO add a way of detecting whether discoverDetails() as already called
    void discoverServices();
    QList<QBluetoothUuid> services() const;
    QLowEnergyService *createServiceObject(
            const QBluetoothUuid &service, QObject *parent = 0);

    Error error() const;
    QString errorString() const;

Q_SIGNALS:
    void connected();
    void disconnected();
    void stateChanged(QLowEnergyControllerNew::ControllerState state);
    void error(QLowEnergyControllerNew::Error newError);

    void serviceDiscovered(const QBluetoothUuid &newService);
    void discoveryFinished();

private:
    Q_DECLARE_PRIVATE(QLowEnergyControllerNew)
    QLowEnergyControllerNewPrivate *d_ptr;
};

QT_END_NAMESPACE

#endif // QLOWENERGYCONTROLLERNEW_H