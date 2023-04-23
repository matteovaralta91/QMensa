#ifndef TELEGRAMMANAGER_H
#define TELEGRAMMANAGER_H

#include <td/telegram/Client.h>
#include <td/telegram/td_api.h>
#include <td/telegram/td_api.hpp>

#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <QDate>
#include <QDateTime>
#include <QMap>

#include "menudefs.h"

// overloaded
namespace detail {
template <class... Fs>
struct overload;

template <class F>
struct overload<F> : public F {
  explicit overload(F f) : F(f) {
  }
};
template <class F, class... Fs>
struct overload<F, Fs...>
	: public overload<F>
	, public overload<Fs...> {
  overload(F f, Fs... fs) : overload<F>(f), overload<Fs...>(fs...) {
  }
  using overload<F>::operator();
  using overload<Fs...>::operator();
};
}  // namespace detail

template <class... F>
auto overloaded(F... f) {
  return detail::overload<F...>(f...);
}

namespace td_api = td::td_api;

class TelegramManager
{
public:
	TelegramManager(QMap<QDate, Menu> menus);
	void loop();

private:
 void sendMessages(QMap<QDate, Menu> menus, int64_t chat_id, bool isPrevEvening);

 QMap<QDate, Menu> menus;
 using Object = td_api::object_ptr<td_api::Object>;
 std::unique_ptr<td::ClientManager> client_manager_;
 std::int32_t client_id_{0};

 td_api::object_ptr<td_api::AuthorizationState> authorization_state_;
 bool are_authorized_{false};
 bool need_restart_{false};
 std::uint64_t current_query_id_{0};
 std::uint64_t authentication_query_id_{0};

 std::map<std::uint64_t, std::function<void(Object)>> handlers_;

 std::map<std::int64_t, td_api::object_ptr<td_api::user>> users_;

 std::map<std::int64_t, std::string> chat_title_;

 void restart();

 void send_query(td_api::object_ptr<td_api::Function> f, std::function<void(Object)> handler);

 void process_response(td::ClientManager::Response response);

 std::string get_user_name(std::int64_t user_id) const;

 std::string get_chat_title(std::int64_t chat_id) const;

 void process_update(td_api::object_ptr<td_api::Object> update);

 auto create_authentication_query_handler() {
   return [this, id = authentication_query_id_](Object object) {
	 if (id == authentication_query_id_) {
	   check_authentication_error(std::move(object));
	 }
   };
 }

 void on_authorization_state_update();

 void check_authentication_error(Object object);

 std::uint64_t next_query_id();
};

#endif // TELEGRAMMANAGER_H
