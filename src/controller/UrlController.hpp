
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

  ADD_CORS(createUrl)
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

  ADD_CORS(getUrlById)
  ENDPOINT("GET", "urlId/{urlId}", getUrlById,
           PATH(Int32, urlId)) {
    return createDtoResponse(Status::CODE_200, m_urlService.getUrlById(urlId));
  }

  ADD_CORS(getByShorten)
  ENDPOINT_INFO(getByShorten) {
    info->summary = "Get one Url by Shorten";

    info->addResponse < Object < UrlDto >> (Status::CODE_200, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_404, "application/json");
    info->addResponse < Object < StatusDto >> (Status::CODE_500, "application/json");

    info->pathParams["UrlId"].description = "Url Identifier";
  }

  ENDPOINT("GET", "url/{shorten}", getByShorten,
           PATH(String, shorten)) {
    return createDtoResponse(Status::CODE_200, m_urlService.getByShorten(shorten));
  }
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* UserController_hpp */

