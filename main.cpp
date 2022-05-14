#include <httpserver.hpp>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

using namespace httpserver;

constexpr const auto NUMBER_OF_ZONES = 2;

struct sprinkler_resource
    : public http_resource {
    const std::shared_ptr< http_response > render_GET( const http_request& in_request ) {

        auto argsCount = in_request.get_args().size();

        if ( argsCount > 1 ) {
            return std::shared_ptr< http_response >( new string_response( "bad request", 400, "text/plain" ) );
        }

        if ( 0 == in_request.get_args().size() ) {
            // handle a GET of all zones
            const auto json = R"([ { "zone" : "0", "state": "off" }, { "zone" : "1", "state" : "on" } ])";
            return std::shared_ptr< http_response >( new string_response( json, 200, "application/json" ) );
        }
        else
        {
            // handle a GET of a particular zone
            const auto& zoneId = in_request.get_args().at("zoneId");
            if ( zoneId == "0" ) {
                bool state = false;
                // Get the state from the daemon
                const auto jsonFmt = R"( "zone": "1", "state": "%s" })";
                char buffer[ 1024 ] = {0,};
                sprintf(buffer, jsonFmt, state ? "on" : "off");
                return std::shared_ptr< http_response >( new string_response( buffer, 200, "application/json" ) );
            } else if (zoneId == "1" ) {
                bool state = true;
                // Get the state from the daemon
                const auto jsonFmt = R"( { "zone": "1", "state": "%s" })";
                char buffer[ 1024 ] = {0,};
                sprintf(buffer, jsonFmt, state ? "on" : "off");
                return std::shared_ptr< http_response >( new string_response( buffer, 200, "application/json" ) );
            } else {
                return std::shared_ptr< http_response >( new string_response( "unknown zone", 404, "text/plain" ) );
            }
        }
        const char* json = R"({ "key": "not that one", "value": "another value" })";
        rapidjson::Document dd;
        dd.Parse( json );

        rapidjson::StringBuffer buffer;
        rapidjson::Writer< rapidjson::StringBuffer > writer( buffer );
        dd.Accept( writer );
        return std::shared_ptr< http_response >( new string_response( buffer.GetString() ) );
    }

    const std::shared_ptr< http_response > render_PUT( const http_request& in_request ) {
        return std::shared_ptr< http_response >( new string_response( "hello hello" ) );
    };
};

int main() {
    std::cout << "hello, world!" << std::endl;

    uint16_t port = 8080;

    webserver ws = create_webserver( port );

    sprinkler_resource sprinklers;
    sprinklers.disallow_all();
    sprinklers.set_allowing( "GET", true );
    sprinklers.set_allowing( "PUT", true );
    ws.register_resource("/zone", &sprinklers);
    ws.register_resource( "/zone/{zoneId}", &sprinklers );
    ws.start( true );

    std::cout << "goodbye, yellow brick road" << std::endl;
    return 0;
}
