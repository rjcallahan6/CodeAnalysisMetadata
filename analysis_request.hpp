/*
  @file analysis_request.hpp

  Header for analysis requests
*/

#ifndef INCLUDE_ANALYSIS_REQUEST_HPP
#define INCLUDE_ANALYSIS_REQUEST_HPP

#include <string>

struct analysis_request {
    std::string given_filename;
    std::string entry_filename;
    std::string given_url;
    std::string option_filename;
    std::string option_url;
    std::string option_language;
};

#endif
