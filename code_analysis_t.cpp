/*
  @file code_analysis_t.cpp

  Test program for analysis requests
*/

#include "code_analysis.hpp"

#include <iostream>
#include <string>
#include <cassert>

int main() {

    // all parts of the request are empty
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

	auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);

	//Tests
	std::cout << "From the code_analysis function: " << std::endl;
	std::cout << "Good name: " << std::endl;
	request.option_filename = "test.cpp";
	assert(code_analysis(request) == false);
	std::cout << std::endl;

	std::cout << "Bad name: " << std::endl;
	request.option_filename = "test.wrong";
	assert(code_analysis(request) == false);
	std::cout << std::endl;
	

	
    }

    return 0;
}
