#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer bufLoginRequest)
{
    // Convert std::vector<unsigned char> (Buffer) to std::string
    std::string jsonStr(bufLoginRequest.data.begin(), bufLoginRequest.data.end());

    // Parse the JSON string into a json object
    json j = json::parse(jsonStr);

    // Extract values and init LoginRequest
    LoginRequest request;
    request.username = j.at("username").get<std::string>();
    request.password = j.at("password").get<std::string>();

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer bufSignupRequest)
{
    // Convert std::vector<unsigned char> (Buffer) to std::string
    std::string jsonStr(bufSignupRequest.data.begin(), bufSignupRequest.data.end());

    // Parse the JSON string into a json object
    json j = json::parse(jsonStr);

    // Extract values and init SignupRequest
    SignupRequest request;
    request.username = j.at("username").get<std::string>();
    request.password = j.at("password").get<std::string>();
    request.email = j.at("email").get<std::string>();

    return request;
}

