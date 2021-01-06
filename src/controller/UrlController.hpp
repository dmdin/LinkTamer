
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
      : oatpp::web::server::api::ApiController(objectMapper) {}

private:
  UrlService m_urlService; // Create url service.
public:

  static std::shared_ptr<UrlController> createShared(
      OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                      objectMapper) // Inject objectMapper component here as default parameter
  ) {
    return std::make_shared<UrlController>(objectMapper);
  }

  ENDPOINT_INFO(createUrl) {
    info->summary = "Create new Url";

    info->addConsumes < Object < UrlDto >> ("application/json");

    info->addResponse < Object < UrlDto >> (Status::CODE_200, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_404, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_500, "application/json");
  }

  ENDPOINT("POST", "url", createUrl,
           BODY_DTO(Object < UrlDto > , urlDto)) {
    return createDtoResponse(Status::CODE_200, m_urlService.createUrl(urlDto));
  }

  ENDPOINT_INFO(getUrlById) {
    info->summary = "Get one Url by urlId";

    info->addResponse < Object < UrlDto >> (Status::CODE_200, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_404, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_500, "application/json");

    info->pathParams["UrlId"].description = "Url Identifier";
  }

  ENDPOINT("GET", "url/{urlId}", getUrlById, PATH(Int32, urlId),
           BODY_DTO(Object < UrlDto > , urlDto)) {
    return createDtoResponse(Status::CODE_200, m_urlService.getUrlById(urlId));
  }

  ENDPOINT_INFO(getByShorten) {
    info->summary = "Get one Url by Shorten";

    info->addResponse < Object < UrlDto >> (Status::CODE_200, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_404, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_500, "application/json");

    info->pathParams["UrlId"].description = "Url Identifier";
  }

  ENDPOINT("GET", "u/{shorten}", getByShorten,
           PATH(String, shorten)) {
    return createDtoResponse(Status::CODE_200, m_urlService.getByShorten(shorten));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* UserController_hpp */
