#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"

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

	// Deserialize login
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buf);

	// Login the user through login manager who uses the Database
	if (m_loginManager.login(loginRequest.username, loginRequest.password))
	{	// Succeful Login

		// Change to menu request handler with current user
		LoggedUser curUser(loginRequest.username);
		MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(curUser);
		requestResult.newHandler = menu;
	}
	else
	{	//Failed to Login

		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;
	}

	// Create response
	LoginResponse loginResponse;
	loginResponse.status = TEMP_LOGIN_STATUS;
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

	// Deserialize signup
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buf);

	// Signup the user through login manager who uses the Database
	if (m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email))
	{	// Succeful Signup

		// Change to menu request handler with current user
		LoggedUser curUser(signupRequest.username);
		MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(curUser);
		requestResult.newHandler = menu;
	}
	else 
	{	//Faied to Signup

		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;
	}

	// Create response
	SignupResponse signupResponse;
	signupResponse.status = TEMP_SIGNUP_STATUS;
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
