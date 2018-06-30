//
// Created by Vladislav Kalugin on 29/06/2018.
//

#include <fstream>
#include <vector>
#include <string>
#include <decoder.h>
#include <iostream>

int main(int argc, char *argv[]) {
    clock_t start = clock();
    std::string in_file_name = argv[1];
    if (in_file_name.substr(in_file_name.size() - 5, in_file_name.size()) != ".huff") {
        throw std::runtime_error("incorrect file waited *.huff");
    }
    std::string out_file_name = in_file_name.substr(0, in_file_name.size() - 5) + ".decode";
    std::ifstream fin(in_file_name, std::ios::in | std::ios::binary);

    if (!fin) {
        throw std::runtime_error("file not can be open: " + in_file_name);
    }
    long gc = 0;
    uint64_t count_of_char = 0;
    uint64_t len = 0;
    fin.read((char *) &count_of_char, sizeof(uint64_t));
    fin.read((char *) &len, sizeof(uint64_t));
    gc = fin.gcount();
    if(gc == 0){
        throw std::runtime_error("incorrect file");
    }

    std::vector<std::pair<byte, code_len>> v_pair(len);

    fin.read((char *) v_pair.data(), sizeof(std::pair<byte, code_len>) * len);
    gc = fin.gcount();
    if (gc != sizeof(std::pair<byte, code_len>) * len) {
        throw std::runtime_error("incorrect alphabet in file");
    }

    decoder dcdr(v_pair);
    std::vector<byte> buffer(READ_BLOCK);
    std::vector<byte> ans_buffer(0);
    std::ofstream fout(out_file_name, std::ios::out | std::ios::binary);

    while (!fin.eof() && (count_of_char > 0)) {
        fin.read((char *) buffer.data(), READ_BLOCK);
        gc = fin.gcount();
        if (gc != READ_BLOCK) {
            buffer.resize(gc);
        }
        ans_buffer = dcdr.decode(buffer);
        if (ans_buffer.size() < count_of_char) {
            fout.write((char *) ans_buffer.data(), ans_buffer.size());
        } else {
            fout.write((char *) ans_buffer.data(), count_of_char);
        }
        count_of_char -= ans_buffer.size();
    }

    if(count_of_char > 0){
        throw std::runtime_error("give not full file");
    }

    fin.close();
    fout.close();

    clock_t end = clock();
    std::cout << "decode time: " << (double) (end - start) / CLOCKS_PER_SEC << std::endl;
}