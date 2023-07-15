#include"front/lexical.h"
#include"front/syntax.h"

#include<string>
#include<vector>
#include<cassert>
#include<fstream>
#include<iostream>

using std::string;
using std::vector;

/**
 * commad line:
 * compiler <src_filename> -step -o <output_filename> [opt]
 * 
 * step:
 *  -s0: output of scanner
 *  -s1: output of parser, should be a json file 
 *  -s2: output IR
 *  -S: output rv assembly
 * 
 * opt:
 * [FIXME]
 */

int main(int argc, char** argv) {
    assert((argc == 5 || argc == 6) && "command line should be: compiler <src_filename> -step -o <output_filename> [opt]");
    string src = argv[1];
    string step = argv[2];
    string des = argv[4];
    std::ofstream output_file = std::ofstream(des);
    assert(output_file.is_open() && "output file can not open");

    frontend::Scanner scanner(src);
    vector<frontend::Token> tk_stream = scanner.run();

    // compiler <src_filename> -s0 -o <output_filename>
    if(step == "-s0"){
        for(const auto& tk: tk_stream){
            output_file << frontend::toString(tk.type) << "\t" << tk.value << std::endl;
        }
        return 0;
    }
    
    frontend::Parser parser(tk_stream);
    frontend::CompUnit* node = parser.get_abstract_syntax_tree();

    // compiler <src_filename> -s1 -o <output_filename>
    if(step == "-s1") {
        Json::Value json_output;
        Json::StyledWriter writer;
        node->get_json_output(json_output);
        output_file << writer.write(json_output);
        return 0;
    }

   // compiler <src_filename> -s2 -o <output_filename>
    if(step == "-s2") {
        std::cout << "todo";
        return 0;
    }

    // compiler <src_filename> -S -o <output_filename>
    if(step == "-S") {
        std::cout << "todo";
        return 0;
    }

    // should not reach here, invaild commad
    return -1;
}