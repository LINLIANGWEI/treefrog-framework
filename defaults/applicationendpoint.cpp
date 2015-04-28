#include "applicationendpoint.h"


ApplicationEndpoint::ApplicationEndpoint()
    : TWebSocketEndpoint()
{ }

ApplicationEndpoint::ApplicationEndpoint(const ApplicationEndpoint &)
    : TWebSocketEndpoint()
{ }

void ApplicationEndpoint::onOpen(const TSession &)
{ }

void ApplicationEndpoint::onClose(int)
{ }

void ApplicationEndpoint::onTextReceived(const QString &)
{ }

void ApplicationEndpoint::onBinaryReceived(const QByteArray &)
{ }

void ApplicationEndpoint::onPing(const QByteArray &data)
{
    TWebSocketEndpoint::onPing(data);
}

void ApplicationEndpoint::onPong(const QByteArray &)
{ }

int ApplicationEndpoint::keepAliveInterval() const
{
    return 0;
}

bool ApplicationEndpoint::transactionEnabled() const
{
    return TWebSocketEndpoint::transactionEnabled();
}
