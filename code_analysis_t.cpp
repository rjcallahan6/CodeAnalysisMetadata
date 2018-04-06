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
	std::cout << "From the code_analysis function: " << std::endl << std::endl;
	std::cout << "Good name: " << std::endl;
	std::cout << "test.cpp" << std::endl;
	request.option_filename = "test.cpp";
	assert(code_analysis(request) == false);
	std::cout << std::endl;

	std::cout << "Bad name: " << std::endl;
	request.option_filename = "test.wrong";
	assert(code_analysis(request) == false);
	std::cout << std::endl;

	std::cout << "filename test" << std::endl << std::endl << std::endl;

	request.option_filename = "";
	request.entry_filename = "data";
	request.given_filename = "test.cpp";
	std::cout << analysis_filename(request) << std::endl << std::endl;

	std::cout << "language test" << std::endl << std::endl;

	std::cout << "Good language: " << std::endl;
	request.option_language = "C++";
	std::cout << analysis_language(request, analysis_filename(request)) << std::endl;
	std::cout << "Bad language: " << std::endl;
	request.option_language = "";
	std::cout << analysis_language(request, analysis_filename(request)) << std::endl;

	std::cout << "url test" << std::endl;

	request.given_url = "https://www.google.com";
	request.option_url = "https://www.test.com";
	std::cout << "Good url: " << std::endl;
	std::cout<< analysis_url(request) << std::endl;
	std::cout << "bad url: " << std::endl;
	request.option_url = "";
	std::cout << analysis_url(request) << std::endl;
	
	
	
    }

    return 0;
}
