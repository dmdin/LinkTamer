
#ifndef CRUD_URLSERVICE_HPP
#define CRUD_URLSERVICE_HPP

#include "db/UrlDb.hpp"
//#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UrlService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UrlDb>, m_database); // Inject database component
public:

  oatpp::Object<UrlDto> createUrl(const oatpp::Object<UrlDto>& dto);
  oatpp::Object<UrlDto> updateAmount(const oatpp::Object<UrlDto>& dto);
  oatpp::Object<UrlDto> getUrlById(const oatpp::Int32& id, const std::shared_ptr<oatpp::orm::Connection>& connection = nullptr);
  oatpp::Object<UrlDto> getByShorten(const oatpp::String& shorten, const std::shared_ptr<oatpp::orm::Connection>& connection = nullptr);
};

#endif //CRUD_USERSERVICE_HPP
