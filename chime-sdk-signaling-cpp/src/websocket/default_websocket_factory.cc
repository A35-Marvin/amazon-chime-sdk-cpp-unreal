// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#include "default_websocket_factory.h"
#include "websocket.h"
#include "libwebsockets_websocket.h"

namespace chime {

std::unique_ptr<Websocket> DefaultWebsocketFactory::CreateWebsocket(WebsocketConfiguration configuration,
                                                                    WebsocketObserver* observer) {
  LibwebsocketsWebsocketConfiguration aws_lws_configuration = {};
  aws_lws_configuration.protocol_name = configuration.protocol_name;
  aws_lws_configuration.url = configuration.url;
  aws_lws_configuration.additional_headers = configuration.additional_headers;
  aws_lws_configuration.level = configuration.level;
  return std::make_unique<LibwebsocketsWebsocket>(aws_lws_configuration, observer);
}

}  // namespace chime
