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

std::string JsonRequestPacketDeserializer::binaryDecoder(std::string buf)
{
    std::string output;
    int pos = 0;
    while (pos < buf.size())
    {
        std::string word = buf.substr(pos, 8);
        pos += 8;
        std::bitset<8> bits(word);
        int n = bits.to_ulong();

        output += char(n);
    }

    return output;
}