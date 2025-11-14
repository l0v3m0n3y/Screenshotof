#ifndef SCREENSHOTOF_H
#define SCREENSHOTOF_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Screenshotof {
private:
    std::string api_base = "https://screenshotof.com";
    http_client_config client_config;
    
    http_request create_request(const std::string& path, method m) {
        http_request request(m);
        
        // Полный набор браузерных заголовков
        request.headers().add("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
        request.headers().add("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0");
        
        request.set_request_uri(utility::conversions::to_string_t(path));
        return request;
    }

public:
    Screenshotof() {
        // Disable SSL certificate verification to fix handshake errors
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> make_screenshot(const std::string& url) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        
        std::string path = "/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(url))) + "?f=json";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
    pplx::task<json::value> get_screenshot_by_data(const std::string& url,const std::string& data) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        
        std::string path = "/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(url))) + "/" + data + "?f=json";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
};

#endif
