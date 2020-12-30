
#include "UrlService.hpp"

oatpp::Object<UserDto> UrlService::createUrl(const oatpp::Object<UserDto>& dto) {

  auto dbResult = m_database->createUrl(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto userId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

  return getUrlById((v_int32) userId);
}


oatpp::Object<UrlDto> UrlService::updateAmount(const oatpp::Object<UrlDto>& dto) {
  auto dbResult = m_database->updateUser(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  return getUserById(dto->id);
}

oatpp::Object<UrlDto> UrlService::getUserById(const oatpp::Int32& id, const std::shared_ptr<oatpp::orm::Connection>& connection) {

  auto dbResult = m_database->getUrlById(id, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Url not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UrlDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<UrlDto> getByShorten(const oatpp::String& shorten, const std::shared_ptr<oatpp::orm::Connection>& connection) {
  auto dbResult = m_database->getByShorten(shorten, connection);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Url not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UrlDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];
}
