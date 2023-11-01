/*
 * Copyright (C) 2023 Jean-Pierre Miceli <jean-pierre.miceli@heig-vd.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef EMISO_CONTAINER_H
#define EMISO_CONTAINER_H

#include <iostream>
#include <httpserver.hpp>
#include <json/json.h>

#include "../../daemon/container.hpp"


namespace emiso {

    namespace container {

        class ListHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request &req) {
                std::string payload_str = "";
                Json::Value payload_json;

                payload_json = Json::arrayValue;

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_ok, "application/json");
                return response;
            }
        };


        class CreateHandler : public httpserver::http_resource {
        public:

            const std::shared_ptr<httpserver::http_response> render_POST(const httpserver::http_request &req) {
                std::string payload_str = "";
                Json::Value payload_json;


                // Extract info from body
                const std::string requestBody = req.get_content();

                Json::Value jsonData;
                Json::Reader jsonReader;


                if (!jsonReader.parse(requestBody, jsonData)) {
                    // JSON parsing error
                    // Return error message
                }

                std::string imageName = jsonData["Image"].asString();

                // Remove the image version of the name
                size_t colonPosition = imageName.find(':');
                imageName = imageName.substr(0, colonPosition);

                std::cout << "[Webserver] Create container based on '" << imageName << "' name" << std::endl;

                _container.create(imageName);

                // build the response
                payload_json["Id"] = "12345";
                payload_json["Warnings"] = Json::arrayValue;

                Json::StreamWriterBuilder builder;
                payload_str = Json::writeString(builder, payload_json);

                auto response = std::make_shared<httpserver::string_response>(payload_str,
                           httpserver::http::http_utils::http_created, "application/json");
                return response;
            }

        private:
            daemon::Container _container;

        };

        class ContainerApi {
        public:
            // Constructor
            ContainerApi(httpserver::webserver *server);

            // Destructor
            ~ContainerApi();

        private:
            httpserver::webserver *_server;

            // Handler for the different 'container' routes
            ListHandler *_listHandler;
            CreateHandler *_createHandler;

        };

    }

}

#endif /* EMISO_CONTAINER_H */