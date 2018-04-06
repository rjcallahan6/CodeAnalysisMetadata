/*
  @file code_analysis.cpp

  Implementation of analysis requests
*/

#include "code_analysis.hpp"
#include "get_language_from_filename.hpp"

#include <iostream>
#include <string>

/** Generate source analysis based on the request
 * @param request Data that forms the request
 * @retval true   Valid request
 * @retval false  Invalid filename or unable to deduce language
 */
bool code_analysis(const analysis_request& request)
{

  auto filename = analysis_filename(request);

  auto url = analysis_url(request);

  auto language = analysis_language(request, filename);

  if (language == "" && get_language_from_filename(request.option_filename) == "")
    std::cerr << "That file extension is not valid." << std::endl;

  if (request.given_filename == "-" && language == "" && filename == "")
    std::cerr << "Input from stdin requires a valid language to be used." << std::endl;


    return false;
}

/** Filename extracted from the request
 * @param  request Data that forms the request
 * @retval filename
 */
std::string analysis_filename(const analysis_request& request)
{
  
  if (request.option_filename != "")
    return request.option_filename;

  if(request.option_filename == "" && request.entry_filename != "")
    return request.entry_filename;

  if (request.option_filename == "" && request.entry_filename == "data" && request.given_filename != "")
    return request.given_filename;

    return "";
}

/** URL extracted from the request
 * @param  request Data that forms the request
 * @retval URL
 */
std::string analysis_url(const analysis_request& request)
{
  
  if (request.option_url != "")
    return request.option_url;
  if(request.option_url == "" && request.given_url != "")
    return request.given_url;

  
    return "";
}

/** Language extracted from the request and the filename
 * @param  request Data that forms the request
 * @param  filename Filename extracted from the request
 * @retval language
 */
std::string analysis_language(const analysis_request& request, const std::string& filename) {

    return "";
}
