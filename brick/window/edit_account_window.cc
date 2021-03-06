// Copyright (c) 2015 The Brick Authors.

#include "brick/window/edit_account_window.h"

#include "include/base/cef_logging.h"
#include "brick/client_handler.h"

void
EditAccountWindow::Init() {
  Init(CefRefPtr<Account> (new Account), false);
}

void
EditAccountWindow::Save(
    bool secure,
    const std::string& domain,
    const std::string& login,
    const std::string& password,
    bool use_app_password) {

  CefRefPtr<Account> account = window_objects_.account;
  bool commit_needed = false;

  if (account->IsExisted()) {

    if (account->IsSecure() != secure) {
      account->SetSecure(secure);
      commit_needed = true;
    }

    if (account->GetDomain() != domain) {
      account->SetDomain(domain);
      commit_needed = true;
    }

    if (account->GetLogin() != login) {
      account->SetLogin(login);
      commit_needed = true;
    }

    if (account->GetPassword() != password) {
      account->SetUseAppPassword(use_app_password);
      account->SetPassword(password);
      commit_needed = true;
    }

  } else {
    commit_needed = true;
    account->SetSecure(secure);
    account->SetLogin(login);
    account->SetDomain(domain);
    account->SetUseAppPassword(use_app_password);
    account->SetPassword(password);
    ClientHandler::GetInstance()->GetAccountManager()->AddAccount(account);
  }

  if (commit_needed) {
    ClientHandler::GetInstance()->GetAccountManager()->Commit();
  }

  if (window_objects_.switch_on_save) {
    ClientHandler::GetInstance()->SwitchAccount(account->GetId());
  }

  Close();
}
