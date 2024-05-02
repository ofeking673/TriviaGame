#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
	return  (requestInfo.id == Login || requestInfo.id == SignUp);
}

RequestResult LoginRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	if (isRequestRelevant(requestInfo))
	{

		if (requestInfo.id == Login)
		{
			// Login
			requestResult = login(requestInfo);
		}
		else if (requestInfo.id == SignUp)
		{
			// Signup
			requestResult = signup(requestInfo);
		}
		else
		{
			// Error
			requestResult = error(requestInfo);
		}

	}
	else
	{
		// Error
		requestResult = error(requestInfo);
	}

	return requestResult;
}

/// <summary>
/// Login a user into the system
/// Gets Request info, parse its' data. 
/// Sends the data to loginMannager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::login(Requestinfo requestInfo)
{
	RequestResult requestResult;
	LoginResponse loginResponse;

	// Deserialize login
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buf);

	// Login the user through login manager who uses the Database
	if (m_loginManager.login(loginRequest.username, loginRequest.password))
	{	// Succeful Login

		// Change to menu request handler with current user
		LoggedUser curUser(loginRequest.username);
		MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(curUser);
		requestResult.newHandler = menu;

		// Status of succeful login
		loginResponse.status = TEMP_LOGIN_RESPONSE_STATUS;
	}
	else
	{	//Failed to Login

		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;

		// Fail code status
		loginResponse.status = TEMP_FAIL_LOGIN_RESPONSE_STATUS;
	}



	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);

	return requestResult;
}

/// <summary>
/// Signup a user into the system
/// Gets Request info, parse its' data. 
/// Sends the data to loginMannager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::signup(Requestinfo requestInfo)
{
	RequestResult requestResult;
	SignupResponse signupResponse;

	// Deserialize signup
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buf);

	// Signup the user through login manager who uses the Database
	if (m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email))
	{	// Succeful Signup

		// Change to menu request handler with current user
		LoggedUser curUser(signupRequest.username);
		MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(curUser);
		requestResult.newHandler = menu;

		// Status of succeful signup
		signupResponse.status = TEMP_SIGNUP_RESPONSE_STATUS;
	}
	else 
	{	//Faied to Signup

		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;

		// Fail code status
		signupResponse.status = TEMP_FAIL_SIGNUP_RESPONSE_STATUS;
	}

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	return requestResult;
}


/// <summary>
/// Error in login request handler
/// Create error response to send back to client
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Login Request Handler.";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}
