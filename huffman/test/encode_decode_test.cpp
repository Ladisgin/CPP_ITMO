//
// Created by Vladislav Kalugin on 30/06/2018.
//

#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

void generate_file(const std::string &generate_file_name);

bool is_equal(const std::string &generate_file_name);

void generate_big_file(const std::string &generate_file_name);

void generate_good_file(const std::string &generate_file_name);

int main() {

    std::string generate_file_name = "testing_file.in";
    size_t count_test = 0;
    for (size_t i = 0; i < 25; i++) {
        std::cout << "start test: " << i + 1 << std::endl;
        generate_file(generate_file_name);
        if (is_equal(generate_file_name)) {
            std::cout << "test: " << i + 1 << " complete" << std::endl;
            count_test++;
        } else {
            std::cout << "test: " << i + 1 << " error :(" << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "start test: " << 26 << std::endl;
    generate_big_file(generate_file_name);
    if (is_equal(generate_file_name)) {
        std::cout << "test: " << 26 << " complete" << std::endl;
        count_test++;
    } else {
        std::cout << "test: " << 26 << " error :(" << std::endl;
    }
    std::cout << std::endl;


    std::cout << "start test: " << 27 << std::endl;
    generate_good_file(generate_file_name);
    if (is_equal(generate_file_name)) {
        std::cout << "test: " << 27 << " complete" << std::endl;
        count_test++;
    } else {
        std::cout << "test: " << 27 << " error :(" << std::endl;
    }
    std::cout << std::endl;


    if (count_test == 27) {
        std::cout << "test complited";
    } else {
        std::cout << "test not complited :(";
    }
    return 0;
}

bool is_equal(const std::string &generate_file_name) {
    std::__1::string encd;
    encd = "/Users/kalugin/CLionProjects/huffman/cmake-build-release/encode ";
    encd += generate_file_name;
    system(encd.c_str());

    std::__1::string decd;
    decd = "/Users/kalugin/CLionProjects/huffman/cmake-build-release/decode ";
    decd += generate_file_name + ".huff";
    system(decd.c_str());

    std::__1::ifstream original_file(generate_file_name, std::__1::ios_base::out | std::__1::ios_base::binary);
    std::__1::ifstream decode_file(generate_file_name + ".decode",
                                   std::__1::ios_base::out | std::__1::ios_base::binary);

    std::__1::vector<char> buffer(8192);
    std::__1::vector<char> buffer_2(8192);
    long gc;
    bool flag = true;
    while (!original_file.eof() && !decode_file && flag) {
        original_file.read(buffer.data(), buffer.size());
        gc = original_file.gcount();
        decode_file.read(buffer_2.data(), buffer_2.size());
        if (gc != decode_file.gcount() || buffer != buffer_2) {
            flag = false;
        }
    }
    return flag;
}

void generate_file(const std::string &generate_file_name) {
    srand(time(0));
    std::__1::ofstream fout(generate_file_name, std::__1::ios_base::out | std::__1::ios_base::binary);
    std::__1::vector<char> buffer(rand() % 8000);
    for (size_t l = 0; l < (rand() % 8000); l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = static_cast<char>((rand() % 256) - 128);
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}

void generate_big_file(const std::string &generate_file_name) {
    srand(time(0));
    std::__1::ofstream fout(generate_file_name, std::__1::ios_base::out | std::__1::ios_base::binary);
    std::__1::vector<char> buffer(8000);
    for (size_t l = 0; l < 10000; l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = static_cast<char>((rand() % 256) - 128);
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}

void generate_good_file(const std::string &generate_file_name) {
    srand(time(0));
    std::__1::ofstream fout(generate_file_name, std::__1::ios_base::out | std::__1::ios_base::binary);
    std::__1::vector<char> buffer(8000);
    for (size_t l = 0; l < 10000; l++) {
        for (size_t j = 0; j < buffer.size(); j++) {
            buffer[j] = 33;
        }
        fout.write(buffer.data(), buffer.size());
    }
    fout.close();
}