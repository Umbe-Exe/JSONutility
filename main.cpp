#include <iostream>
#include "Json.h"

int main() {

	std::string raw = R"(
		
	[
        {
    
                5,
                 [
                     "564",
                     545 ,
                     "ciao" :
                              "ciao" :
                                       [
                                           "ok",
                                           "gg",
                                           "ciao" :
                                                    [
                                                        "ok",
                                                        "gg"
                                                    ]
                                       ],
                     "ciao" :
                              "ciao" :
                                       [
                                           "ok",
                                           "gg",
                                           "ciao" :
                                                    [
                                                        "ok",
                                                        "gg"
                                                    ]
                                       ]
                 ]
    }
]

	)";

	Json json(raw);

	/*Json &myPair = json.putArray().putObject().putPair();

    std::cout << json.prettyPrint() << "\n\n\n\n\n\n";

	myPair.setKey("ciao");

    std::cout << json.prettyPrint() << "\n\n\n\n\n\n";
	
	Json &array = myPair.putArray();

    std::cout << json.prettyPrint() << "\n\n\n\n\n\n";

	array.putString("ok");
	array.putString("gg");

    std::cout << json.prettyPrint() << "\n\n\n\n\n\n";

    array.putObject(json[0][0]);

    std::cout << json.prettyPrint() << "\n\n\n\n\n\n";

	array.putObject(array[2]);*/

	std::cout << json.prettyPrint();

}