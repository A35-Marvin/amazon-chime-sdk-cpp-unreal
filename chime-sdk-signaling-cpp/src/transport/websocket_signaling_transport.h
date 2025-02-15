// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
/* @unstable */

#ifndef CHIME_SIGNALING_WEBSOCKET_SIGNALING_TRANSPORT_H_
#define CHIME_SIGNALING_WEBSOCKET_SIGNALING_TRANSPORT_H_

#include "signaling_transport.h"
#include "signaling_transport_configuration.h"
#include "signaling_transport_observer.h"
#include "websocket/websocket.h"
#include "proto/video_control.pb.h"

#include <thread>

namespace chime {

static std::unordered_map<signal_rtc::SignalFrame_Type, std::string> signal_frame_type_strings = {
    { signal_rtc::SignalFrame_Type_JOIN, "Join" },
    { signal_rtc::SignalFrame_Type_JOIN_ACK, "JoinAck" },
    { signal_rtc::SignalFrame_Type_SUBSCRIBE, "Subscribe" },
    { signal_rtc::SignalFrame_Type_SUBSCRIBE_ACK, "SubscribeAck" },
    { signal_rtc::SignalFrame_Type_INDEX, "Index" },
    { signal_rtc::SignalFrame_Type_PAUSE, "Pause" },
    { signal_rtc::SignalFrame_Type_RESUME, "Resume" },
    { signal_rtc::SignalFrame_Type_LEAVE, "Leave" },
    { signal_rtc::SignalFrame_Type_LEAVE_ACK, "LeaveAck" },
    { signal_rtc::SignalFrame_Type_BITRATES, "Bitrates" },
    { signal_rtc::SignalFrame_Type_AUDIO_CONTROL, "AudioControl" },
    { signal_rtc::SignalFrame_Type_AUDIO_METADATA, "AudioMetadata" },
    { signal_rtc::SignalFrame_Type_AUDIO_STREAM_ID_INFO, "AudioStreamIdInfo" },
    { signal_rtc::SignalFrame_Type_PING_PONG, "PingPong" },
    { signal_rtc::SignalFrame_Type_AUDIO_STATUS, "AudioStatus" },
    { signal_rtc::SignalFrame_Type_CLIENT_METRIC, "ClientMetric" },
    { signal_rtc::SignalFrame_Type_DATA_MESSAGE, "DataMassage" },
    { signal_rtc::SignalFrame_Type_AUDIO_TRANSCRIPT, "AudioTranscript" }
};

class WebsocketSignalingTransport : public SignalingTransport, public WebsocketObserver {
 public:
  // WebsocketSignalingTransport
  WebsocketSignalingTransport(SignalingTransportConfiguration configuration,
                              SignalingTransportObserver* transport_observer,
                              std::unique_ptr<WebsocketFactory> websocket_factory);

  void Start() override;
  void Stop() override;
  void Poll() override;

  bool SendSignalFrame(signal_rtc::SignalFrame& frame) override;

  ~WebsocketSignalingTransport() override;
  void StopRun() override;
  bool IsPollable() override;

  // WebsocketObserver
  void OnWebsocketConnected() override;
  void OnWebsocketBinaryReceived(const std::vector<uint8_t>& data) override;
  void OnWebsocketClosed(WebsocketStatus status) override;
  void OnWebsocketError(WebsocketErrorStatus error) override;
  void Run() override;

 private:
  std::string signaling_url_;
  std::string join_token_;
  SignalingTransportObserver* observer_ = nullptr;
  std::unique_ptr<Websocket> websocket_;

  // Defines the state whether websocket transport has stopped.
  // This will be useful to not start multiple times if Start() is called
  bool is_stopped_ = true;
};

}  // namespace chime
#endif  // CHIME_SIGNALING_WEBSOCKET_SIGNALING_TRANSPORT_H_
