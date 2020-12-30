
#ifndef UrlController_hpp
#define UrlController_hpp

#include "service/UrlService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Url REST controller.
 */
class UrlController : public oatpp::web::server::api::ApiController {
public:
  UrlController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  UrlService m_urlService; // Create url service.
public:

  static std::shared_ptr<UrlController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<UrlController>(objectMapper);
  }
  
  ENDPOINT_INFO(createUrl) {
    info->summary = "Create new Url";

    info->addConsumes<Object<UrlDto>>("application/json");

    info->addResponse<Object<UrlDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "url", createUrl,
           BODY_DTO(Object<UrlDto>, UrlDto))
  {
    return createDtoResponse(Status::CODE_200, m_UrlService.createUrl(UrlDto));
  }
  
  
//  ENDPOINT_INFO(putUser) {
//    info->summary = "Update User by userId";
//
//    info->addConsumes<Object<UserDto>>("application/json");
//
//    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
//    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
//    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
//
//    info->pathParams["userId"].description = "User Identifier";
//  }
//  ENDPOINT("PUT", "users/{userId}", putUser,
//           PATH(Int32, userId),
//           BODY_DTO(Object<UserDto>, userDto))
//  {
//    userDto->id = userId;
//    return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
//  }
  
  
  ENDPOINT_INFO(getUrlById) {
    info->summary = "Get one Url by UrlId";

    info->addResponse<Object<UrlDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["UrlId"].description = "Url Identifier";
  }
  ENDPOINT("GET", "url/{shorten}", getByShorten,
           PATH(String, shorten))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getByShorten(userId));
  }
  
  
  ENDPOINT_INFO(getUsers) {
    info->summary = "get all stored users";

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getAllUsers(offset, limit));
  }
  
  
  ENDPOINT_INFO(deleteUser) {
    info->summary = "Delete User by userId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "users/{userId}", deleteUser,
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* UserController_hpp */
