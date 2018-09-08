//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "encoder.h"
#include "counter.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>



int getFileSize(const std::string &fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    std::string in_file_name = argv[1];
    std::string out_file_name = in_file_name + ".huff";
    std::ifstream fin(in_file_name, std::ios::in | std::ios::binary);

    if (!fin) {
        throw std::runtime_error("file not can be open: " + in_file_name);
    }

    counter cntr;
    std::vector<byte> buffer(READ_BLOCK);
    long gc = 0;
    while (!fin.eof()) {
        fin.read((char *) buffer.data(), READ_BLOCK);
        gc = fin.gcount();
        if (gc != READ_BLOCK) {
            buffer.resize(gc);
        }
        cntr.update(buffer);
    }

    buffer.resize(READ_BLOCK);

    fin.close();
    fin.open(in_file_name, std::ios::in | std::ios::binary);
    std::ofstream fout(out_file_name, std::ios::out | std::ios::binary);

    if (!fin || !fout) {
        throw std::runtime_error("file not can be open: " + in_file_name + "/" + out_file_name);
    }

    encoder encd(cntr);


    {
        std::vector<std::pair<byte, code_len>> v_pair = encd.give_alphabet();
        uint64_t count_of_char = cntr.get_count_of_char();
        uint64_t len = v_pair.size();
        fout.write((char *) (&count_of_char), sizeof(uint64_t));
        fout.write((char *) (&len), sizeof(uint64_t));
        fout.write((char *) v_pair.data(), sizeof(std::pair<byte, code_len>) * v_pair.size());
    }

    byte_vector bv;
    byte_vector bvn;

    while (!fin.eof()) {
        fin.read((char *) buffer.data(), READ_BLOCK);
        gc = fin.gcount();
        if (gc != READ_BLOCK) {
            buffer.resize(gc);
        }
        bvn = encd.encode(buffer);
        for (int i = 0; i < bvn.data.size() - 1; i++) {
            bv.push_back(bvn.data[i]);
        }
        if (bvn.last_size) {
            bv.push_back(bvn.data.back(), bvn.last_size);
        }
        if (bv.data.size() > 1) {
            fout.write((char *) bv.data.data(), (bv.data.size() - 1));
        }
        if (bv.last_size) {
            byte x = bv.data.back();
            bv.data.resize(1);
            bv.data.back() = x;
        } else {
            bv.set_zero();
        }
    }
    if (bv.last_size) {
        fout.write((char *) bv.data.data(), 1);
    }
    fin.close();
    fout.close();


    clock_t end = clock();
    std::cout << "file size: " << getFileSize(in_file_name) << std::endl;
    std::cout << "encode file size: " << getFileSize(out_file_name) << std::endl;
    std::cout << "encode time: " << (double) (end - start) / CLOCKS_PER_SEC << std::endl;
}