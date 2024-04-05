#include "JsonResponsePacketSerializer.h"
#include "json.hpp"

using json = nlohmann::json;

/// <summary>
/// Serialize Error response from JSON format to binary
/// </summary>
/// <param name="errorResponse">Error response object</param>
/// <returns>Buffer contains binary format of JSON error response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
    Buffer buffer;

    // Convert ErrorResponse to JSON
    json j;
    j["message"] = errorResponse.message;

    // Serialize the JSON object to a string
    std::string serializedString = j.dump();

    // Convert the string to Buffer
    for (auto& ch : serializedString)
    {
        buffer.data.push_back(static_cast<unsigned char>(ch));
    }

    return buffer;
}

/// <summary>
/// Serialize Login response from JSON format to binary
/// </summary>
/// <param name="loginResponse">Login response object</param>
/// <returns>Buffer contains binary format of JSON login response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
    Buffer buffer;

    // Convert LoginResponse to JSON
    json j;
    j["status"] = loginResponse.status;

    // Serialize the JSON object to a string
    std::string serializedString = j.dump();

    // Convert the string to Buffer
    for (auto& ch : serializedString)
    {
        buffer.data.push_back(static_cast<unsigned char>(ch));
    }

    return buffer;
}

/// <summary>
/// Serialize Signup response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Signup response object</param>
/// <returns>Buffer contains binary format of JSON signup response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
    Buffer buffer;

    // Convert SignupResponse to JSON
    json j;
    j["status"] = signupResponse.status;

    // Serialize the JSON object to a string
    std::string serializedString = j.dump();
    std::cout << serializedString;
    // Convert the string to Buffer
    for (auto& ch : serializedString)
    {
        buffer.data.push_back(static_cast<unsigned char>(ch));
    }

    return buffer;
}
