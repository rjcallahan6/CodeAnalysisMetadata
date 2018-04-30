
# rjcallahan6

## Files
% ls

    Makefile
    README.md
    analysis_request.hpp
    code_analysis.cpp
    code_analysis.hpp
    code_analysis_t.cpp
    get_language_from_filename.cpp
    get_language_from_filename.hpp
    get_language_from_filename_t.cpp

## Changed files
% git diff baa2b2fa58cb52ada94597a9b2e5d687f6a3261f --name-only

    code_analysis.cpp
    code_analysis_t.cpp

## Build
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

## Test
% make test

    ./code_analysis_t
    That file extension is not valid.
    From the code_analysis function: 
    
    Good name: 
    test.cpp
    
    Bad name: 
    That file extension is not valid.
    
    filename test
    
    
    data
    
    language test
    
    Good language: 
    C++
    Bad language: 
    
    url test
    Good url: 
    https://www.test.com
    bad url: 
    https://www.google.com

## Test Oracle: code\_analysis\_t.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis_t.cpp .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% make test

    ./code_analysis_t
    That file extension is not valid.
    ./code_analysis_t: code_analysis_t.cpp:59: main Check `filename == "main.cpp"' failed.
    ./code_analysis_t: code_analysis_t.cpp:61: main Check `analysis_language(request, filename) == "C++"' failed.
    That file extension is not valid.
    ./code_analysis_t: code_analysis_t.cpp:62: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:79: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:96: main Check `code_analysis(request) == true' failed.
    That file extension is not valid.
    Input from stdin requires a valid language to be used.
    ./code_analysis_t: code_analysis_t.cpp:130: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:147: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:164: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:181: main Check `code_analysis(request) == true' failed.

## Test Oracle: code\_analysis.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis.cpp  .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% make test

    ./code_analysis_t
    Extension not supported
    From the code_analysis function: 
    
    Good name: 
    test.cpp
    Assertion failed: (code_analysis(request) == false), function main, file code_analysis_t.cpp, line 36.
    make: *** [test] Abort trap: 6

## Code
% srcml code_analysis.cpp code_analysis_t.cpp -o project.xml
% srcml --xpath="//src:function[src:name='code_analysis']" project.xml | srcml

     1 bool code_analysis(const analysis_request& request)
     2 {
     3 
     4   auto filename = analysis_filename(request);
     5 
     6   auto url = analysis_url(request);
     7 
     8   auto language = analysis_language(request, filename);
     9 
    10   if (language == "" && get_language_from_filename(request.option_filename) == "")
    11     std::cerr << "That file extension is not valid." << std::endl;
    12 
    13   if (request.given_filename == "-" && language == "" && filename == "")
    14     std::cerr << "Input from stdin requires a valid language to be used." << std::endl;
    15 
    16 
    17     return false;
    18 }

% srcml --xpath="//src:function[src:name='analysis_filename']" project.xml | srcml

     1 std::string analysis_filename(const analysis_request& request)
     2 {
     3   
     4   if (request.option_filename != "")
     5     return request.option_filename;
     6 
     7   if(request.option_filename == "" && request.entry_filename != "")
     8     return request.entry_filename;
     9 
    10   if (request.option_filename == "" && request.entry_filename == "data" && request.given_filename != "")
    11     return request.given_filename;
    12 
    13     return "";
    14 }

% srcml --xpath="//src:function[src:name='analysis_url']" project.xml | srcml

     1 std::string analysis_url(const analysis_request& request)
     2 {
     3   
     4   if (request.option_url != "")
     5     return request.option_url;
     6   if(request.option_url == "" && request.given_url != "")
     7     return request.given_url;
     8 
     9   
    10     return "";
    11 }

% srcml --xpath="//src:function[src:name='analysis_language']" project.xml | srcml

     1 std::string analysis_language(const analysis_request& request, const std::string& filename)
     2 {
     3 
     4   if (request.option_language != "")
     5     return request.option_language;
     6   else
     7     return get_language_from_filename(filename);
     8 
     9     return "";
    10 }

## Test Cases 
% srcml code_analysis_t.cpp --xpath="//src:function[src:name='main']/src:block" | srcml

    {
    
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

## Literal Values used in Testing
% srcml code\_analysis_t.cpp --xpath="//src:literal" | srcml | tr '\0' '\n' |grep '"' | sort -u | tr '\n' ','

    "Bad language: " "Bad name: " "C++" "From the code_analysis function: " 
    "Good language: " "Good name: " "Good url: " "bad url: " "data" 
    "filename test" "https://www.google.com" "https://www.test.com" 
    "language test" "test.cpp" "test.wrong" "url test" 

## Error Messages
% srcml code_analysis.cpp --xpath="//src:function[src:name='code_analysis']//src:expr[contains(., 'cerr')]//src:literal" | srcml | tr '\0'  '\n'

    "That file extension is not valid."
    "Input from stdin requires a valid language to be used."

## Commits

### Commit 924a51
% git checkout -q 924a51  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% git show

    commit 924a51dc918a9d988d7527e18c3be103451a0146
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 15:24:37 2018 -0400
    
        Created test for Filename
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 820446d..c8f6fc3 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -6,6 +6,7 @@
     
     #include "code_analysis.hpp"
     
    +#include <iostream>
     #include <string>
     #include <cassert>
     
    @@ -21,11 +22,20 @@ int main() {
             request.option_url      = "";
             request.option_language = "";
     
    -        auto filename = analysis_filename(request);
    +	auto filename = analysis_filename(request);
             assert(filename == "");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
    +
    +	//Tests
    +	std::cout << "From the code_analysis function: " << std::endl;
    +	std::cout << "Good name: " << std::endl;
    +	request.option_filename = "test.cpp";
    +	assert(code_analysis(request) == false);
    +	std::cout << std::endl;
    +
    +	
         }
     
         return 0;


### Commit f06e64
% git checkout -q f06e64  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit f06e64092b3f72f47d5afe536a0d7dcef97f76ce
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 15:29:14 2018 -0400
    
        Created wrong filename test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index c8f6fc3..5b83463 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -35,6 +35,12 @@ int main() {
     	assert(code_analysis(request) == false);
     	std::cout << std::endl;
     
    +	std::cout << "Bad name: " << std::endl;
    +	request.option_filename = "test.wrong";
    +	assert(code_analysis(request) == false);
    +	std::cout << std::endl;
    +	
    +
     	
         }
     


### Commit 9b55c6
% git checkout -q 9b55c6  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 9b55c65b1b80aae84246d715df9c18e42ad7634d
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:03:10 2018 -0400
    
        Added analysis_filename() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b874829..4fe58fc 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -14,15 +14,15 @@
      * @retval true   Valid request
      * @retval false  Invalid filename or unable to deduce language
      */
    -bool code_analysis(const analysis_request& request) {
    +bool code_analysis(const analysis_request& request)
    +{
     
    -    auto filename = analysis_filename(request);
    +  auto filename = analysis_filename(request);
     
    -    auto url = analysis_url(request);
    +  auto url = analysis_url(request);
     
    -    auto language = analysis_language(request, filename);
    +  auto language = analysis_language(request, filename);
     
    -    // code analysis processing that is not yet implemented
     
         return false;
     }
    @@ -31,7 +31,17 @@ bool code_analysis(const analysis_request& request) {
      * @param  request Data that forms the request
      * @retval filename
      */
    -std::string analysis_filename(const analysis_request& request) {
    +std::string analysis_filename(const analysis_request& request)
    +{
    +  
    +  if (request.option_filename != "")
    +    return request.option_filename;
    +
    +  if(request.option_filename == "" && request.entry_filename != "")
    +    return request.entry_filename;
    +
    +  if (request.option_filename == "" && request.entry_filename == "data" && request.given_filename != "")
    +    return request.given_filename;
     
         return "";
     }


### Commit 20e94b
% git checkout -q 20e94b  
% make  
error: The following untracked working tree files would be overwritten by checkout:
	code_analysis_t
Please move or remove them before you switch branches.
Aborting

    make: Nothing to be done for `all'.

% git show

    commit 9b55c65b1b80aae84246d715df9c18e42ad7634d
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:03:10 2018 -0400
    
        Added analysis_filename() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b874829..4fe58fc 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -14,15 +14,15 @@
      * @retval true   Valid request
      * @retval false  Invalid filename or unable to deduce language
      */
    -bool code_analysis(const analysis_request& request) {
    +bool code_analysis(const analysis_request& request)
    +{
     
    -    auto filename = analysis_filename(request);
    +  auto filename = analysis_filename(request);
     
    -    auto url = analysis_url(request);
    +  auto url = analysis_url(request);
     
    -    auto language = analysis_language(request, filename);
    +  auto language = analysis_language(request, filename);
     
    -    // code analysis processing that is not yet implemented
     
         return false;
     }
    @@ -31,7 +31,17 @@ bool code_analysis(const analysis_request& request) {
      * @param  request Data that forms the request
      * @retval filename
      */
    -std::string analysis_filename(const analysis_request& request) {
    +std::string analysis_filename(const analysis_request& request)
    +{
    +  
    +  if (request.option_filename != "")
    +    return request.option_filename;
    +
    +  if(request.option_filename == "" && request.entry_filename != "")
    +    return request.entry_filename;
    +
    +  if (request.option_filename == "" && request.entry_filename == "data" && request.given_filename != "")
    +    return request.given_filename;
     
         return "";
     }


### Commit 7cdf09
% git checkout -q 7cdf09  
% make  
error: The following untracked working tree files would be overwritten by checkout:
	code_analysis_t
Please move or remove them before you switch branches.
Aborting

    make: Nothing to be done for `all'.

% git show

    commit 9b55c65b1b80aae84246d715df9c18e42ad7634d
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:03:10 2018 -0400
    
        Added analysis_filename() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b874829..4fe58fc 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -14,15 +14,15 @@
      * @retval true   Valid request
      * @retval false  Invalid filename or unable to deduce language
      */
    -bool code_analysis(const analysis_request& request) {
    +bool code_analysis(const analysis_request& request)
    +{
     
    -    auto filename = analysis_filename(request);
    +  auto filename = analysis_filename(request);
     
    -    auto url = analysis_url(request);
    +  auto url = analysis_url(request);
     
    -    auto language = analysis_language(request, filename);
    +  auto language = analysis_language(request, filename);
     
    -    // code analysis processing that is not yet implemented
     
         return false;
     }
    @@ -31,7 +31,17 @@ bool code_analysis(const analysis_request& request) {
      * @param  request Data that forms the request
      * @retval filename
      */
    -std::string analysis_filename(const analysis_request& request) {
    +std::string analysis_filename(const analysis_request& request)
    +{
    +  
    +  if (request.option_filename != "")
    +    return request.option_filename;
    +
    +  if(request.option_filename == "" && request.entry_filename != "")
    +    return request.entry_filename;
    +
    +  if (request.option_filename == "" && request.entry_filename == "data" && request.given_filename != "")
    +    return request.given_filename;
     
         return "";
     }


### Commit a525ff
% git checkout -q a525ff  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit a525ffe3847c8277c42d41c211dfd914982e7758
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:29:28 2018 -0400
    
        removed accidental code_analysis_t
    
    diff --git a/code_analysis_t b/code_analysis_t
    deleted file mode 100755
    index bf4fbce..0000000
    Binary files a/code_analysis_t and /dev/null differ


### Commit a5f294
% git checkout -q a5f294  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit a5f294624363e13fc161f5ecdf993ef94f0c22d5
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:39:06 2018 -0400
    
        added code_analysis() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 4fe58fc..5d4821d 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -7,6 +7,7 @@
     #include "code_analysis.hpp"
     #include "get_language_from_filename.hpp"
     
    +#include <iostream>
     #include <string>
     
     /** Generate source analysis based on the request
    @@ -23,6 +24,12 @@ bool code_analysis(const analysis_request& request)
     
       auto language = analysis_language(request, filename);
     
    +  if (language == "" && get_language_from_filename(request.option_filename) == "")
    +    std::cerr << "That file extension is not valid." << std::endl;
    +
    +  if (request.given_filename == "-" && language == "" && filename == "")
    +    std::cerr << "Input from stdin requires a valid language to be used." << std::endl;
    +
     
         return false;
     }


### Commit 7d08ce
% git checkout -q 7d08ce  
% make  

    make: Nothing to be done for `all'.

% git show

    commit 7d08ce81f557d75e9b2a5f4facecaa264222b576
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:43:28 2018 -0400
    
        added analysis_url() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 5d4821d..0ada622 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -57,8 +57,15 @@ std::string analysis_filename(const analysis_request& request)
      * @param  request Data that forms the request
      * @retval URL
      */
    -std::string analysis_url(const analysis_request& request) {
    +std::string analysis_url(const analysis_request& request)
    +{
    +  
    +  if (request.option_url != "")
    +    return request.option_url;
    +  if(request.option_url == "" && request.given_url != "")
    +    return request.given_url;
     
    +  
         return "";
     }
     


### Commit f61a5f
% git checkout -q f61a5f  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit f61a5f33dc894cc1d074324706db903b4d0ba082
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:50:23 2018 -0400
    
        added analysis_language() implementation
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 0ada622..b0857ae 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -74,7 +74,13 @@ std::string analysis_url(const analysis_request& request)
      * @param  filename Filename extracted from the request
      * @retval language
      */
    -std::string analysis_language(const analysis_request& request, const std::string& filename) {
    +std::string analysis_language(const analysis_request& request, const std::string& filename)
    +{
    +
    +  if (request.option_language != "")
    +    return request.option_language;
    +  else
    +    return get_language_from_filename(filename);
     
         return "";
     }


### Commit 2c6451
% git checkout -q 2c6451  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 2c64511e486ee4b9ec1d0829c2e7c7d8a4d7ad20
    Author: Ryan <rjc84@zips.uakron.edu>
    Date:   Fri Apr 6 16:58:39 2018 -0400
    
        cleaned up spacing
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index a93c6b1..30e23fd 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -29,7 +29,7 @@ int main() {
             assert(code_analysis(request) == false);
     
     	//Tests
    -	std::cout << "From the code_analysis function: " << std::endl;
    +	std::cout << "From the code_analysis function: " << std::endl << std::endl;
     	std::cout << "Good name: " << std::endl;
     	std::cout << "test.cpp" << std::endl;
     	request.option_filename = "test.cpp";
    @@ -37,19 +37,18 @@ int main() {
     	std::cout << std::endl;
     
     	std::cout << "Bad name: " << std::endl;
    -	std::cout << "test.wrong" << std::endl;
     	request.option_filename = "test.wrong";
     	assert(code_analysis(request) == false);
     	std::cout << std::endl;
     
    -	std::cout << "filename test" << std::endl;
    +	std::cout << "filename test" << std::endl << std::endl << std::endl;
     
     	request.option_filename = "";
     	request.entry_filename = "data";
     	request.given_filename = "test.cpp";
    -	std::cout << analysis_filename(request) << std::endl;
    +	std::cout << analysis_filename(request) << std::endl << std::endl;
     
    -	std::cout << "language test" << std::endl;
    +	std::cout << "language test" << std::endl << std::endl;
     
     	std::cout << "Good language: " << std::endl;
     	request.option_language = "C++";
    @@ -60,8 +59,8 @@ int main() {
     
     	std::cout << "url test" << std::endl;
     
    -	request.given_url = "https://google.com";
    -	request.option_url = "www.test.com";
    +	request.given_url = "https://www.google.com";
    +	request.option_url = "https://www.test.com";
     	std::cout << "Good url: " << std::endl;
     	std::cout<< analysis_url(request) << std::endl;
     	std::cout << "bad url: " << std::endl;

