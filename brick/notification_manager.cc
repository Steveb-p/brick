// Copyright (c) 2015 The Brick Authors.

#include "brick/notification_manager.h"

#include "brick/client_handler.h"
#include "brick/event/notification_event.h"

NotificationManager::NotificationManager() :
    notification_(nullptr),
    last_id_(0),
    is_append_supported_(false),
    is_actions_supported_(false),
    is_persistence_supported_(false),
#ifdef  __linux__
    on_kde_(false),
    skip_onclose_(false)
#endif
    {

  InitializeCapabilities();
}

void
NotificationManager::OnClick(const std::string &js_id, bool is_message) {
  CefRefPtr<ClientHandler> client_handler = ClientHandler::GetInstance();
  if (!client_handler)
    return;

  CefRefPtr<BrowserWindow> window = client_handler->GetMainWindowHandle();
  if (!window)
    return;

  window->Present();

  if (!js_id.empty()) {
    NotificationEvent e(js_id, is_message, true);
    EventBus::FireEvent(e);
  }
}

bool
NotificationManager::IsAppendSupported() {
  return is_actions_supported_;
}

bool
NotificationManager::IsActionsSupported() {
  return is_actions_supported_;
}

bool
NotificationManager::IsPersistenceSupported() {
  return is_persistence_supported_;
}
