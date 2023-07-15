#include"front/lexical.h"
#include"front/syntax.h"
#include"front/semantic.h"
#include"ir/ir.h"
#include"tools/ir_executor.h"

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
 *  -S:  output rv assembly
 *  -e:  get ir::Program and execute it, print the main return value to stdout
 *  -all[FIXME]
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
    
    frontend::Analyzer analyzer;
    auto program = analyzer.get_ir_program(node);
    
    // compiler <src_filename> -s2 -o <output_filename>
    if(step == "-s2") {
        output_file << program.draw();
    }

    // compiler <src_filename> -e -o <output_filename>
    if(step == "-e") {
        auto output_file_name = des;
        auto input_file_name = src.substr(0,src.size()-2) + "in";
        ir::reopen_output_file =  fopen(output_file_name.c_str(), "w");
        ir::reopen_input_file =  fopen(input_file_name.c_str(), "r");

        auto executor = ir::Executor(&program);
        std::cout << program.draw() << "--------------------------- Executor::run() ---------------------------" << std::endl;
        fprintf(ir::reopen_output_file, "\n%d", (uint8_t)executor.run());
    }
    return 0;
}